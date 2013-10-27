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

#ifndef EFLAGS_H
#define EFLAGS_H

#include <cstring>

//The table below is based on Intel(R) 64 and IA-32 Architectures Software
//Developer's Manual - Volume 1: Basic Architecture [from September/2013]

//Note (1): MOV instruction can 'undefine' some flags, if its operation is
//to/from control/debug registers - you can comment or discomment the line of
//UD_Imov below to take this behaviour in mind.

//Note (2): RCL/RCR/ROL/ROR/SAL/SAR/SHL/SHR behavior is different about flag OF 
//based on operator - anyway, those instructions potentially modify OF always.

//Note (3): Instructions IRETW and SCASQ exist on libUdis86 sources but not on
//the Intel's Manual, so they are commented below. SCASQ exists on AMD's manual.

//Note (4): Instruction SAL exists on Intel's Manual but not on libUdis86
//sources, so it's commented below.

//Note (5): //one can do mnemonic search based on modular arithmetic, like
//	for (pos = 0; pos < sizeof(eflags); pos+=12 )
//		if (eflags[pos] == mnemonic) {insn_alter_or_test_flag = true;} 


#define __NONE			1
#define __RESETS		2
#define __SETS			3
#define __MODIFIES		__RESETS * __SETS
#define	__TESTS			5
#define __T_AND_M		__MODIFIES * __TESTS
#define __RESTORES		7
#define __UNDEFINED		11


// ATTENTION: This took me more than an hour to get right:
// The include order is important
// If you don't include types.h before itab.h, the linkage will fail with multiple definitions of UD_ATTR_PACKED
extern "C"
{
#include "libudis86/types.h"
#include "libudis86/itab.h"
}

// Exporting Constants:
// http://stackoverflow.com/questions/1433204/how-do-i-share-a-variable-between-source-files-in-c-with-extern-but-how
extern short EFLAGS[];
extern size_t EFLAGS_SIZE;


#endif

