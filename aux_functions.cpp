/***************************************************************************
 *   Copyright (C) 2013 by:                                                *
 *   Lord Astrogildo Girafales                                             *
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


#include "aux_functions.h"


//ModifiesFlags description: check if M modifies some flag - it searches flags
//info. on EFLAGS array.

bool ModifiesFlags (enum ud_mnemonic_code M) {
	short pos = 0; 
	short i_pos = 0;
	short prod = 1;

	while ( pos < sizeof (EFLAGS) ) {
		if (EFLAGS[pos] == M) {
			for (i_pos = (pos+1); i_pos < (pos+12); ++i_pos) { prod *= EFLAGS[i_pos]; }
			
			if ( 
				(prod%__UNDEFINED == 0) ||
				(prod%__RESETS == 0) 	||
				(prod%__SETS == 0) 		||
				(prod%__RESTORES == 0)
			) { return true; }
			
			else {return false;}
		}
		pos += 12; //12 is number of line elements of EFLAGS; 1 mnemonic + 11 flags
	}

	return false;	
}


//TestsFlags description: check if M tests some flag - it searches flags info.
//on EFLAGS array.

bool TestsFlags (enum ud_mnemonic_code M) {
	short pos = 0; 
	short i_pos = 0;
	short prod = 1;

	while ( pos < sizeof (EFLAGS) ) {
		if (EFLAGS[pos] == M) {
			for (i_pos = (pos+1); i_pos < (pos+12); ++i_pos) { prod *= EFLAGS[i_pos]; }
			
			if (prod%__TESTS == 0) { return true; }
			else {return false;}
		}
		pos += 12; //12 is number of line elements of EFLAGS; 1 mnemonic + 11 flags
	}

	return false;
}


//ExtractAddr description: it extracts an address hex value as string (without 0x prefix) from decoded opcode.
//s_buf is a string that represents opcode in mnemonic high-level way; d_buf is the target buffer;
//d_buf_len is sizeof(d_buf); upper_limit is a limit for search - all jump instructions with offset as parameter
//are structured like 'jXXX 0x*****', so uppper_limit is the max position to search for 0x.

void ExtractAddr (const char* s_buf, char* d_buf, const unsigned int d_buf_len, const unsigned short upper_limit) {
	short pos_s = 2; //no jump instruction has mnemonic length < 2
	short pos_a = 0;
	bool addr_found = false;

	for (; pos_s < upper_limit; ++pos_s) {
		if ( (s_buf[pos_s] == '0') && (s_buf[pos_s+1] == 'x') )  {
			pos_s += 2;
			addr_found = true;
			break;
		}
	}
	
	if (addr_found == true) {
		
		memset(d_buf,0,d_buf_len);
		
		while ( (s_buf[pos_s] != 0) && (pos_a < d_buf_len) ) { //memcpy could be used, but in a 'unsafe' manner...
			d_buf[pos_a] = s_buf[pos_s];
			++pos_a;
			++pos_s;
		}	
	}
}
