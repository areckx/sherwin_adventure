// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2016 by Andrew Clark (FL4SHK).
// 
// Sherwin's Adventure is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// Sherwin's Adventure is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with Sherwin's Adventure.  If not, see <http://www.gnu.org/licenses/>.


#ifndef asm_funcs_hpp
#define asm_funcs_hpp

#include "../game_engine_stuff/misc_types.hpp"

extern "C"
{

// lut_udiv should actually take a u16 dem, not a u32 dem
extern u64 lut_udiv( u32 num, u32 dem );

// memcpy32 is from TONC
extern void memcpy32( void* dst, const void* src, u32 wordcount );

// memfill32 is a modified version of memcpy32 to fill an array with a
// constant word.
extern void memfill32( void* dst, u32 src, u32 wordcount );



extern void memcpy8( void* dst, const void* src, u32 bytecount );
extern void memfill8( void* dst, u8 src, u32 bytecount );

}

inline void memcpy32( volatile void* dst, const void* src, 
	u32 wordcount )
{
	memcpy32( (void*)dst, src, wordcount );
}

inline void memfill32( volatile void* dst, u32 src, u32 wordcount )
{
	memfill32( (void*)dst, src, wordcount );
}




inline void memcpy8( volatile void* dst, const void* src, u32 bytecount )
{
	memcpy8( (void*)dst, src, bytecount );
}

inline void memfill8( volatile void* dst, u8 src, u32 bytecount )
{
	memfill8( (void*)dst, src, bytecount );
}



#endif		// asm_funcs_hpp
