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


#include "hud_manager_class.hpp"
#include "level_stuff/active_level_manager_class.hpp"

//#include <string>
//#include <sstream>
//using namespace std;

#include <stdlib.h>
#include <string.h>


bool hud_manager::hud_was_generated;

scr_entry hud_manager::bg1_screenblock_mirror[screenblock_size];

array_2d_helper<scr_entry> hud_manager::bg1_screenblock_2d
	( se_ram[bg1_sbb], screenblock_size_2d );
array_2d_helper<scr_entry> hud_manager::bg1_screenblock_mirror_2d 
	( bg1_screenblock_mirror, screenblock_size_2d );

const char hud_manager::char_to_plottable_char_arr
	[char_to_plottable_char_arr_size]
	= { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
	' ', ' ', ' ', ' ', ' ', ' ', '!', '"', '#', '$', '%', '&', '\'', '(',
	')', '*', '+', ',', '-', '.', '/', '0', '1', '2', '3', '4', '5', '6',
	'7', '8', '9', ':', ';', '<', '=', '>', '?', '@', 'A', 'B', 'C', 'D',
	'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
	'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_', '`',
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|',
	'}', '~', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
	' ', ' ', ' ', ' ', ' ' };
	

//void hud_manager::plot_char_8x16_to_screenblock_mirror( u32 the_char, 
//	u32 pos_x, u32 pos_y )
//{
//	bg1_screenblock_mirror_2d.at( pos_x, pos_y )
//		= gfx_manager::hud_vram_as_tiles_start_offset
//		+ ( ( (char)the_char - ' ' ) * gfx_manager::num_tiles_in_ss_8x16 )
//		| se_palbank(bgps_in_level_hud);
//	
//	bg1_screenblock_mirror_2d.at( pos_x, pos_y + 1 )
//		= gfx_manager::hud_vram_as_tiles_start_offset
//		+ ( ( (char)the_char - ' ' ) * gfx_manager::num_tiles_in_ss_8x16 
//		+ 1 ) | se_palbank(bgps_in_level_hud);
//}

void hud_manager::plot_char_8x8_to_screenblock_mirror( u32 the_char,
	u32 pos_x, u32 pos_y )
{
	//// Don't plot ASCII control codes.
	//if ( the_char < ' ' )
	//{
	//	return;
	//}
	
	//// Plot ASCII control codes as ' '.
	//if ( the_char < ' ' )
	//{
	//	bg1_screenblock_mirror_2d.at( pos_x, pos_y )
	//		= gfx_manager::hud_vram_as_tiles_start_offset
	//		| se_palbank(bgps_in_level_hud);
	//	return;
	//}
	//
	//bg1_screenblock_mirror_2d.at( pos_x, pos_y )
	//	= gfx_manager::hud_vram_as_tiles_start_offset
	//	+ ( (char)the_char - ' ' ) | se_palbank(bgps_in_level_hud);
	
	bg1_screenblock_mirror_2d.at( pos_x, pos_y )
		= ( gfx_manager::hud_vram_as_tiles_start_offset
		+ ( char_to_plottable_char_arr[(char)the_char] - ' ' ) )
		| se_palbank(bgps_in_level_hud);
}


void hud_manager::copy_hud_from_array_2d_helper_to_vram()
{
	memcpy32( hud_manager::bg1_screenblock_2d.the_array,
		hud_manager::bg1_screenblock_mirror_2d.the_array,
		sizeof(scr_entry) * hud_manager::bg1_screenblock_mirror_2d
		.get_size() / sizeof(u32) );
}


