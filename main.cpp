/***************************************************************************
 *   Copyright (C) 2013 by:                                                *
 *   Edson Borin (edson@ic.unicamp.br)                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


/**
 * See usage() function for a description.
 */


#include <fstream>
#include <string.h>	
#include <stdio.h>

extern "C"
{
#include "udis86.h"
}

#include "arglib.h"
#include "trace_io.h"
#include "rain.h"
#include "rf_techniques.h"
#include "aux_functions.h"


#define LINUX_SYS_THRESHOLD   		0xB2D05E00         // 3000000000
#define WINDOWS_SYS_THRESHOLD		0xF9CCD8A1C5080000 // 18000000000000000000
#define STR_VALUE(arg) 				#arg


using namespace std;
using namespace rain;


clarg::argInt    start_i("-s", "start: first file index ", 0);
clarg::argInt    end_i("-e", "end: last file index", 0);
clarg::argString basename_main("-b", "input file basename", "trace");

clarg::argBool   help("-h",  "display the help message");
clarg::argString reg_stats_fname("-reg_stats", "file name to dump regions statistics in CSV format", "reg_stats.csv");
clarg::argString overall_stats_fname("-overall_stats", "file name to dump overall statistics in CSV format", "overall_stats.csv");

clarg::argString dotgraph("-dot", "file name to dump TEA - Regios Graph", "tea.dot");
clarg::argBool lt("-lt", "linux trace. System/user address threshold = 0xB2D05E00");
clarg::argBool wt("-wt", "windows trace. System/user address threshold = 0xF9CCD8A1C5080000");


void usage(char* prg_name)
{
    cout << "Usage: " << prg_name << " -b basename -s index -e index [-h] [-o stats.csv] {-lt|-wt}"
    << endl << endl;

    cout << "DESCRIPTION:" << endl;

    cout << "This program implements the RAIn (Region Appraisal Infrastructure) and can be" << endl;
    cout << "used to investigate region formation strategies for dynamic binary" << endl;
    cout << "translators. For more information, please, read: Zinsly, R. \"Region formation" << endl;
    cout << "techniques for the design of efficient virtual machines\". MsC" << endl;
    cout << "Thesis. Institute of Computing, 2013 (in portuguese)." << endl;

    cout << "The tool takes as input a trace of instructions, emulate the formation and " << endl;
    cout << "execution of  regions, and generates statistics about the region formation" << endl;
    cout << "techniques. " << endl;
    cout << "The input trace may be store in multiple files, each one" << endl;
    cout << "containing a sub-sequence of the trace. Each file is named" << endl;
    cout << "BASENAME.INDEX.bin.gz, where basename is the basename of" << endl;
    cout << "the trace and INDEX indicates the sequence of the trace." << endl;
    cout << "The user must provide the basename (-b), the start index (-s) and the end " << endl;
    cout << "index (-e)." << endl << endl;

    cout << "ARGUMENTS:" << endl;
    clarg::arguments_descriptions(cout, "  ", "\n");
}


int validate_arguments()
{
    if (!start_i.was_set()) {
        cerr << "Error: you must provide the start file index."
        << "(use -h for help)" << endl;
        return 1;
    }

    if (!end_i.was_set()) {
        cerr << "Error: you must provide the end file index."
        << "(use -h for help)" << endl;
        return 1;
    }

    if (!basename_main.was_set()) {
        cerr << "Error: you must provide the basename."
        << "(use -h for help)" << endl;
        return 1;
    }

    if (end_i.get_value() < start_i.get_value()) {
        cerr << "Error: start index must be less (<) or equal (=) to end index"
        << "(use -h for help)" << endl;
        return 1;
    }

    if (lt.was_set()) {
        if (wt.was_set()) {
            cerr << "Error: both -lt and -lw were set, select only one." << endl;
            return 1;
        }
        else {
            rain::RF_Technique::set_system_threshold(LINUX_SYS_THRESHOLD);
        }
    }
    else {
        if (wt.was_set()) {
            rain::RF_Technique::set_system_threshold(WINDOWS_SYS_THRESHOLD);
        }
        else {
            cerr << "Error: either -lt or -lw must be selected." << endl;
            return 1;
        }
    }

    return 0;
}

int main(int argc,char** argv)
{
    // Parse the arguments
    if (clarg::parse_arguments(argc, argv)) {
        cerr << "Error when parsing the arguments!" << endl;
        return 1;
    }

    if (help.get_value() == true) {
        usage(argv[0]);
        return 1;
    }

    if (validate_arguments())
        return 1;

    // Create the input pipe.
    trace_io::raw_input_pipe_t in(basename_main.get_value(),
                                  start_i.get_value(),
                                  end_i.get_value());

    // Current and next instructions.
    trace_io::trace_item_t current;
    trace_io::trace_item_t next;

    // Fetch the next instruction from the trace
    if (!in.get_next_instruction(current)) {
        cerr << "Error: input trace has no instruction items." << endl;
        return 1;
    }

    rain::RF_Technique* rf = new rf_technique::NET();

    // While there are instructions

    long long int insn_count=0;
    long long int jmps=0;
    long long int jmps_taken=0;
    long long int invalid_insn=0;
    long long int cc_gen=0;
    long long int cc_used=0;
    
    bool was_jump = false;
	
	char addr_decoder[16];
	char addr_trace[16];

    memset(addr_decoder,0,16);
    memset(addr_trace,0,16);
	
    ud_t ud_obj;

    ud_init(&ud_obj);
    ud_set_syntax(&ud_obj, UD_SYN_INTEL); //Intel syntax
    ud_set_mode(&ud_obj, 32); //32-bit
	
    while ( in.get_next_instruction(next) ) {
                     
        ++insn_count;
        
        // Process the trace
        //if (rf) { rf->process(current.addr, current.opcode, current.length, next.addr, next.opcode, next.length); }

        ud_set_input_buffer(&ud_obj,(uint8_t*)current.opcode,(size_t)current.length);
        ud_set_pc(&ud_obj, (uint64_t) current.addr); //set IP/EIP register

        ud_disassemble(&ud_obj);

//LCCE - Lazy Code Condition Evaluation 'prototype' analysis
	
		if (  ModifiesFlags( ud_insn_mnemonic(&ud_obj) ) == true  ) {++cc_gen;}
		if (  TestsFlags( ud_insn_mnemonic(&ud_obj) ) == true  ) {++cc_used;}

		
//Indirect Jump 'pre-prototype' analysis       
        if (was_jump == true)  {
			
			sprintf(addr_trace,"%llx",current.addr);
			
			if ( strcmp(addr_trace,addr_decoder) == 0 ) { ++jmps_taken; }
			
			was_jump = false;
			memset(addr_decoder,0,16);
			memset(addr_trace,0,16);
		}
               
        switch ( ud_insn_mnemonic(&ud_obj) ) { //haow about use a lookup table? It worths?
/*			case UD_Ijmp: //must count jmp ?
				++jmps;
				break;
*/
			case UD_Ijo:
			case UD_Ijno:
			case UD_Ijb:
			case UD_Ijae:
			case UD_Ijz:
			case UD_Ijnz:
			case UD_Ijbe:
			case UD_Ija:
			case UD_Ijs:
			case UD_Ijns:
			case UD_Ijp:
			case UD_Ijnp:
			case UD_Ijl:
			case UD_Ijge:
			case UD_Ijle:
			case UD_Ijg:
			case UD_Ijcxz:
			case UD_Ijecxz:
			case UD_Ijrcxz:
				++jmps;
				was_jump = true;
				ExtractAddr(ud_obj.asm_buf, addr_decoder, sizeof(addr_decoder), 10); //10 can change...it's 'ad-hoc'...
				break;
			
			case UD_Iinvalid:
				++invalid_insn;
			
			default:
				break;
		}
//			

        //printf( "0x%llx: %s\n", current.addr, ud_insn_asm(&ud_obj) ); //prints instruction

        current = next;
        
    }
	
	//printf is just for now - we need to use statistical class and dump on csv, not STDOUT
	printf("\nTotal de inst.\t\t\t= %lld\n", insn_count);
	printf("Inst. mal-decodificadas\t\t= %lld\n", invalid_insn);
	printf("Total de jumps cond.\t\t= %lld\n", jmps);
    printf("Jumps cond. tomados\t\t= %lld\n", jmps_taken);
    printf("Inst. que geram cond. codes\t= %lld\n", cc_gen);
    printf("Inst. que usam cond. codes\t= %lld\n", cc_used);
    
    
    if (rf) rf->finish();

    //Print statistics

    if (rf) {

        ofstream reg_stats_f(reg_stats_fname.get_value().c_str());
        rf->rain.printRAInStats(reg_stats_f);
        reg_stats_f.close();

        ofstream overall_stats_f(overall_stats_fname.get_value().c_str());
        rf->rain.printOverallStats(overall_stats_f);
        overall_stats_f.close();

        // dumping dot regions graph
        if (dotgraph.was_set()) {
            std::string file = dotgraph.get_value();
            rf->rain.printRegionsDOT(file);

            //rf->rain.
        }
    }

    return 0; // Return OK.
}
