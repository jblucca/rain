#**************************************************************************
#   Copyright (C) 2013 by:                                                *
#   Edson Borin (edson@ic.unicamp.br)                                     *
#                                                                         *
#   This program is free software; you can redistribute it and/or modify  *
#   it under the terms of the GNU General Public License as published by  *
#   the Free Software Foundation; either version 2 of the License, or     *
#   (at your option) any later version.                                   *
#                                                                         *
#   This program is distributed in the hope that it will be useful,       *
#   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
#   GNU General Public License for more details.                          *
#                                                                         *
#   You should have received a copy of the GNU General Public License     *
#   along with this program; if not, write to the                         *
#   Free Software Foundation, Inc.,                                       *
#   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
#**************************************************************************
cmake_minimum_required (VERSION 2.6)

project (RAIn)

# Add libraries
add_subdirectory(arglib)
add_subdirectory(tracelib)
add_subdirectory(rainlib)

include_directories ("${PROJECT_SOURCE_DIR}/arglib")
include_directories ("${PROJECT_SOURCE_DIR}/tracelib")
include_directories ("${PROJECT_SOURCE_DIR}/rainlib")
include_directories ("${PROJECT_SOURCE_DIR}/udis86/include")

# Must be placed before defining the targets
link_directories(${PROJECT_SOURCE_DIR}/udis86/lib)

# Add executable
add_executable(rain_tool.bin main.cpp aux_functions.cpp eflags.cpp)
add_executable(filter_tool.bin filter.cpp aux_functions.cpp eflags.cpp)


target_link_libraries (rain_tool.bin arglib tracelib rainlib udis86)
target_link_libraries (filter_tool.bin arglib tracelib udis86)
