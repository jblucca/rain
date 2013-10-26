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
#ifndef UDIS86_H
#define UDIS86_H
#include "libudis86/itab.h"
#endif

#ifndef EFLAGS_H
#define EFLAGS_H




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



short EFLAGS[] = {

//UD_I mnemonic			 OF					 SF					 ZF					 AF					 PF					 CF				   TF			   IF			   DF			   NT			   RF

UD_Iaaa,			__UNDEFINED,		__UNDEFINED,		__UNDEFINED,		__T_AND_M,			__UNDEFINED,		__MODIFIES,			__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Iaad,			__UNDEFINED,		__MODIFIES,			__MODIFIES,			__UNDEFINED,		__MODIFIES,			__UNDEFINED,		__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Iaam,			__UNDEFINED,		__MODIFIES,			__MODIFIES,			__UNDEFINED,		__MODIFIES,			__UNDEFINED,		__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Iaas,			__UNDEFINED,		__UNDEFINED,		__UNDEFINED,		__T_AND_M,			__UNDEFINED,		__MODIFIES,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Iadc,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__T_AND_M,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Iadd,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Iand,			__RESETS,			__MODIFIES,			__MODIFIES,			__UNDEFINED,		__MODIFIES,			__RESETS,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Iarpl,			__NONE,				__NONE,				__MODIFIES,			__NONE,				__NONE,				__NONE,				__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
										
UD_Ibsf,			__UNDEFINED,		__UNDEFINED,		__MODIFIES,			__UNDEFINED,		__UNDEFINED,		__UNDEFINED,		__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Ibsr,			__UNDEFINED,		__UNDEFINED,		__MODIFIES,			__UNDEFINED,		__UNDEFINED,		__UNDEFINED,		__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Ibt,				__UNDEFINED,		__UNDEFINED,		__NONE, 			__UNDEFINED,		__UNDEFINED,		__MODIFIES,			__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Ibts,			__UNDEFINED,		__UNDEFINED,		__NONE, 			__UNDEFINED,		__UNDEFINED,		__MODIFIES,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Ibtr,			__UNDEFINED,		__UNDEFINED,		__NONE, 			__UNDEFINED,		__UNDEFINED,		__MODIFIES,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Ibtc,			__UNDEFINED,		__UNDEFINED,		__NONE, 			__UNDEFINED,		__UNDEFINED,		__MODIFIES,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
											
UD_Iclc,			__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__RESETS,			__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Icld,			__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,			__NONE,			__RESETS,		__NONE,			__NONE,
UD_Icli,			__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,			__RESETS,		__NONE,			__NONE,			__NONE,
UD_Icmc,			__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__MODIFIES,			__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
												
UD_Icmovo,			__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,		 	__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Icmovno,			__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,		 	__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Icmovb,			__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,		 	__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Icmovae,			__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,		 	__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Icmovz,			__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,		 	__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Icmovnz,			__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,		 	__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Icmovbe,			__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,		 	__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Icmova,			__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,		 	__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Icmovs,			__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,		 	__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Icmovns,			__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,		 	__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Icmovp,			__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,		 	__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Icmovnp,			__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,		 	__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Icmovl,			__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,		 	__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Icmovge,			__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,		 	__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Icmovle,			__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,		 	__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Icmovg,			__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,		 	__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
										
UD_Icmp,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Icmpsb,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__NONE,			__NONE, 		__TESTS,		__NONE,			__NONE,
UD_Icmpsw,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__NONE,			__NONE, 		__TESTS,		__NONE,			__NONE,
UD_Icmpsd,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__NONE,			__NONE, 		__TESTS,		__NONE,			__NONE,
UD_Icmpsq,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__NONE,			__NONE, 		__TESTS,		__NONE,			__NONE,

UD_Icmpxchg,		__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Icmpxchg8b,		__NONE,				__NONE, 			__MODIFIES,			__NONE,				__NONE,				__NONE,				__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Icmpxchg16b,		__NONE,				__NONE, 			__MODIFIES,			__NONE,				__NONE,				__NONE,				__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Icomisd,			__RESETS,			__RESETS,			__MODIFIES,			__RESETS,			__MODIFIES,			__MODIFIES,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Icomiss,			__RESETS,			__RESETS,			__MODIFIES,			__RESETS,			__MODIFIES,			__MODIFIES,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
											
UD_Idaa,			__UNDEFINED,		__MODIFIES,			__MODIFIES,			__T_AND_M,			__MODIFIES,			__T_AND_M,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Idas,			__UNDEFINED,		__MODIFIES,			__MODIFIES,			__T_AND_M,			__MODIFIES,			__T_AND_M,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Idec,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__NONE,				__NONE, 		__NONE,			__NONE,			__NONE,			__NONE,
UD_Idiv,			__UNDEFINED,		__UNDEFINED,		__UNDEFINED,		__UNDEFINED,		__UNDEFINED,		__UNDEFINED,		__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
											
UD_Ifcmovb,			__NONE,				__NONE,				__TESTS,			__NONE, 			__TESTS,			__TESTS,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Ifcmove,			__NONE,				__NONE,				__TESTS,			__NONE, 			__TESTS,			__TESTS,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Ifcmovbe,		__NONE,				__NONE,				__TESTS,			__NONE, 			__TESTS,			__TESTS,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Ifcmovu,			__NONE,				__NONE,				__TESTS,			__NONE, 			__TESTS,			__TESTS,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Ifcmovnb,		__NONE,				__NONE,				__TESTS,			__NONE, 			__TESTS,			__TESTS,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Ifcmovne,		__NONE,				__NONE,				__TESTS,			__NONE, 			__TESTS,			__TESTS,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Ifcmovnbe,		__NONE,				__NONE,				__TESTS,			__NONE, 			__TESTS,			__TESTS,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Ifcmovnu,		__NONE,				__NONE,				__TESTS,			__NONE, 			__TESTS,			__TESTS,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
											
UD_Ifcomi,			__RESETS,			__RESETS,			__MODIFIES,			__RESETS,			__MODIFIES,			__MODIFIES,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Ifcomip,			__RESETS,			__RESETS,			__MODIFIES,			__RESETS,			__MODIFIES,			__MODIFIES,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Ifucomi,			__RESETS,			__RESETS,			__MODIFIES,			__RESETS,			__MODIFIES,			__MODIFIES,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Ifucomip,		__RESETS,			__RESETS,			__MODIFIES,			__RESETS,			__MODIFIES,			__MODIFIES,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
										
UD_Iidiv,			__UNDEFINED,		__UNDEFINED,		__UNDEFINED,		__UNDEFINED,		__UNDEFINED,		__UNDEFINED,		__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Iimul,			__MODIFIES,			__UNDEFINED,		__UNDEFINED,		__UNDEFINED,		__UNDEFINED,		__MODIFIES,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Iinc,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__NONE,				__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
												
UD_Iinsb,			__NONE, 			__NONE, 			__NONE, 			__NONE, 			__NONE, 			__NONE, 			__NONE, 		__NONE,			__TESTS,		__NONE, 		__NONE,
UD_Iinsd,			__NONE, 			__NONE, 			__NONE, 			__NONE, 			__NONE, 			__NONE, 			__NONE, 		__NONE,			__TESTS,		__NONE, 		__NONE,
UD_Iinsw,			__NONE, 			__NONE, 			__NONE, 			__NONE, 			__NONE, 			__NONE, 			__NONE, 		__NONE,			__TESTS,		__NONE, 		__NONE,
															
UD_Iint,			__NONE,				__NONE,				__NONE, 			__NONE,				__NONE,				__NONE,				__RESETS,		__NONE,			__NONE, 		__RESETS,		__NONE,
UD_Iinto,			__TESTS,			__NONE,				__NONE, 			__NONE,				__NONE,				__NONE,				__RESETS,		__NONE,			__NONE, 		__RESETS,		__NONE,
										
UD_Iucomisd,		__RESETS,			__RESETS,			__MODIFIES,			__RESETS,			__MODIFIES,			__MODIFIES,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Iucomiss,		__RESETS,			__RESETS,			__MODIFIES,			__RESETS,			__MODIFIES,			__MODIFIES,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Iiretd,			__RESTORES,			__RESTORES,			__RESTORES,			__RESTORES,			__RESTORES,			__RESTORES,			__RESTORES,		__RESTORES,		__RESTORES,		__TESTS,		__NONE,
UD_Iiretq,			__RESTORES,			__RESTORES,			__RESTORES,			__RESTORES,			__RESTORES,			__RESTORES,			__RESTORES,		__RESTORES,		__RESTORES,		__TESTS,		__NONE,
//UD_Iiretw,		__RESTORES,			__RESTORES,			__RESTORES,			__RESTORES,			__RESTORES,			__RESTORES,			__RESTORES,		__RESTORES,		__RESTORES,		__TESTS,		__NONE,			
											
UD_Ijo,				__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,			__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Ijno,			__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,			__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Ijb,				__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,			__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Ijae,			__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,			__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Ijz,				__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,			__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Ijnz,			__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,			__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Ijbe,			__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,			__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Ija,				__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,			__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Ijs,				__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,			__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Ijns,			__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,			__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Ijp,				__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,			__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Ijnp,			__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,			__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Ijl,				__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,			__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Ijge,			__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,			__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Ijle,			__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,			__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Ijg,				__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,			__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Ijecxz,			__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,			__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Ijrcxz,			__TESTS,			__TESTS,			__TESTS,			__NONE, 			__TESTS,			__TESTS,			__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
												
UD_Ilar,			__NONE,				__NONE,				__MODIFIES,			__NONE,				__NONE,				__NONE,				__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Ilodsb,			__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,			__NONE,			__TESTS,		__NONE,			__NONE,
UD_Ilodsw,			__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,			__NONE,			__TESTS,		__NONE,			__NONE,
UD_Ilodsd,			__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,			__NONE,			__TESTS,		__NONE,			__NONE,
UD_Ilodsq,			__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,			__NONE,			__TESTS,		__NONE,			__NONE,
UD_Iloope,			__NONE,				__NONE,				__TESTS,			__NONE,				__NONE,				__NONE,				__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Iloopne,			__NONE,				__NONE,				__TESTS,			__NONE,				__NONE,				__NONE,				__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Ilsl,			__NONE,				__NONE,				__MODIFIES,			__NONE,				__NONE,				__NONE,				__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
										
//UD_Imov,			__UNDEFINED,		__UNDEFINED,		__UNDEFINED,		__UNDEFINED,		__UNDEFINED,		__UNDEFINED,		__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
										
UD_Imovsb,			__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,			__NONE,			__TESTS,		__NONE,			__NONE,
UD_Imovsw,			__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,			__NONE,			__TESTS,		__NONE,			__NONE,
UD_Imovsd,			__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,			__NONE,			__TESTS,		__NONE,			__NONE,
UD_Imovsq,			__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,			__NONE,			__TESTS,		__NONE,			__NONE,
												
UD_Imul,			__MODIFIES,			__UNDEFINED,		__UNDEFINED,		__UNDEFINED,		__UNDEFINED,		__MODIFIES,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Ineg,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Ior,				__RESETS,			__MODIFIES,			__MODIFIES,			__UNDEFINED,		__MODIFIES,			__RESETS,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
												
UD_Ioutsb,			__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,			__NONE,			__TESTS,		__NONE,			__NONE,
UD_Ioutsd,			__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,			__NONE,			__TESTS,		__NONE,			__NONE,
UD_Ioutsw,			__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,			__NONE,			__TESTS,		__NONE,			__NONE,
											
UD_Ipopfd,			__RESTORES,			__RESTORES,			__RESTORES,			__RESTORES,			__RESTORES,			__RESTORES,			__RESTORES,		__RESTORES,		__RESTORES,		__RESTORES,		__NONE,
UD_Ipopfq,			__RESTORES,			__RESTORES,			__RESTORES,			__RESTORES,			__RESTORES,			__RESTORES,			__RESTORES,		__RESTORES,		__RESTORES,		__RESTORES,		__NONE,
UD_Ipopfw,			__RESTORES,			__RESTORES,			__RESTORES,			__RESTORES,			__RESTORES,			__RESTORES,			__RESTORES,		__RESTORES,		__RESTORES,		__RESTORES,		__NONE,
											
UD_Ircl,			__MODIFIES,			__NONE,				__NONE,				__NONE,				__NONE, 			__T_AND_M,			__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Ircr,			__MODIFIES,			__NONE,				__NONE,				__NONE,				__NONE, 			__T_AND_M,			__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Irol,			__MODIFIES,			__NONE,				__NONE,				__NONE,				__NONE, 			__MODIFIES,			__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Iror,			__MODIFIES,			__NONE,				__NONE,				__NONE,				__NONE, 			__MODIFIES,			__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
											
UD_Irsm,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,		__MODIFIES,		__MODIFIES,		__MODIFIES,		__MODIFIES,
												
UD_Isahf,			__NONE,				__RESTORES,			__RESTORES,			__RESTORES,			__RESTORES,			__RESTORES,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
//UD_Isal,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__UNDEFINED,		__MODIFIES,			__MODIFIES,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Isar,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__UNDEFINED,		__MODIFIES,			__MODIFIES,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Ishl,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__UNDEFINED,		__MODIFIES,			__MODIFIES,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Ishr,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__UNDEFINED,		__MODIFIES,			__MODIFIES,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Isbb,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__T_AND_M,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,

UD_Iscasb,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Iscasw,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Iscasd,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
//UD_Iscasq,		__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
											
UD_Iseto,			__TESTS,			__TESTS,			__TESTS,			__NONE,				__TESTS,			__TESTS,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Isetno,			__TESTS,			__TESTS,			__TESTS,			__NONE,				__TESTS,			__TESTS,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Isetb,			__TESTS,			__TESTS,			__TESTS,			__NONE,				__TESTS,			__TESTS,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Isetae,			__TESTS,			__TESTS,			__TESTS,			__NONE,				__TESTS,			__TESTS,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Isetz,			__TESTS,			__TESTS,			__TESTS,			__NONE,				__TESTS,			__TESTS,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Isetnz,			__TESTS,			__TESTS,			__TESTS,			__NONE,				__TESTS,			__TESTS,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Isetbe,			__TESTS,			__TESTS,			__TESTS,			__NONE,				__TESTS,			__TESTS,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Iseta,			__TESTS,			__TESTS,			__TESTS,			__NONE,				__TESTS,			__TESTS,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Isets,			__TESTS,			__TESTS,			__TESTS,			__NONE,				__TESTS,			__TESTS,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Isetns,			__TESTS,			__TESTS,			__TESTS,			__NONE,				__TESTS,			__TESTS,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Isetp,			__TESTS,			__TESTS,			__TESTS,			__NONE,				__TESTS,			__TESTS,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Isetnp,			__TESTS,			__TESTS,			__TESTS,			__NONE,				__TESTS,			__TESTS,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Isetl,			__TESTS,			__TESTS,			__TESTS,			__NONE,				__TESTS,			__TESTS,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Isetge,			__TESTS,			__TESTS,			__TESTS,			__NONE,				__TESTS,			__TESTS,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Isetle,			__TESTS,			__TESTS,			__TESTS,			__NONE,				__TESTS,			__TESTS,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
UD_Isetg,			__TESTS,			__TESTS,			__TESTS,			__NONE,				__TESTS,			__TESTS,			__NONE,			__NONE, 		__NONE,			__NONE,			__NONE,
											
UD_Ishld,			__UNDEFINED,		__MODIFIES,			__MODIFIES,			__UNDEFINED,		__MODIFIES,			__MODIFIES,			__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Ishrd,			__UNDEFINED,		__MODIFIES,			__MODIFIES,			__UNDEFINED,		__MODIFIES,			__MODIFIES,			__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Istc,			__NONE,				__NONE,				__NONE,				__NONE,				__NONE, 			__SETS,				__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Istd,			__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,			__NONE,			__SETS,			__NONE,			__NONE,
UD_Isti,			__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,			__SETS,			__NONE,			__NONE,			__NONE,
										
UD_Istosb,			__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,			__NONE,			__TESTS,		__NONE,			__NONE,
UD_Istosw,			__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,			__NONE,			__TESTS,		__NONE,			__NONE,
UD_Istosd,			__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,			__NONE,			__TESTS,		__NONE,			__NONE,
UD_Istosq,			__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,				__NONE,			__NONE,			__TESTS,		__NONE,			__NONE,
										
UD_Isub,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Itest,			__RESETS,			__MODIFIES,			__MODIFIES,			__UNDEFINED,		__MODIFIES,			__RESETS,			__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Iverr,			__NONE,				__NONE,				__MODIFIES,			__NONE,				__NONE,				__NONE,				__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Iverw,			__NONE,				__NONE,				__MODIFIES,			__NONE,				__NONE,				__NONE,				__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Ixadd, 			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__MODIFIES,			__NONE,			__NONE,			__NONE,			__NONE,			__NONE,
UD_Ixor, 			__RESETS,			__MODIFIES,			__MODIFIES,			__UNDEFINED,		__MODIFIES,			__RESETS,			__NONE,			__NONE,			__NONE,			__NONE,			__NONE

};

#endif //EFLAGS_H
