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


#ifndef AUX_FUNC_H
#define AUX_FUNC_H

#include <string.h>

#include "eflags.h"

bool ModifiesFlags (enum ud_mnemonic_code M);

bool TestsFlags (enum ud_mnemonic_code M);

void ExtractAddr (const char* s_buf, char* d_buf, const unsigned int d_buf_len, const unsigned short upper_limit);

#endif //AUX_FUNC_H
