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


#include "block_coll_result_group_class.hpp"
#include "level_stuff/active_level_class.hpp"

#include "block_stuff/block_stuff.hpp"
#include "sprite_stuff/sprite_class.hpp"

block_coll_result::block_coll_result( const vec2_s32& s_coord )
	: coord(s_coord)
{
	the_block = &active_level::the_block_data_at_coord(coord);
	the_bbvt = get_behavior_type_of_block_type(get_block_type());
}
block_coll_result::block_coll_result( const vec2_f24p8& s_coord_f24p8 )
	: block_coll_result(active_level::get_block_coord_of_point
	(s_coord_f24p8))
{
}



u32 block_coll_result_group::temp_debug_thing;


block_coll_result_group::block_coll_result_group()
{
	arr_memfill32( bcr_arr_2d_helper_data, 0, max_size );
	start_pos = vec2_s32( 0, 0 );
	real_size_2d = vec2_s32( 1, 1 );
	
	moving_left = moving_right = false;
	
	init_bcr_arr_2d_helper();
	
	for ( s32 j=0; j<real_height(); ++j )
	{
		for ( s32 i=0; i<real_width(); ++i )
		{
			data_at( i, j ) = block_coll_result( tl_corner() 
				+ vec2_s32( i, j ) );
		}
	}
}

block_coll_result_group::block_coll_result_group
	( const coll_box& the_coll_box, u32 s_moving_left, u32 s_moving_right )
{
	arr_memfill32( bcr_arr_2d_helper_data, 0, max_size );
	
	start_pos = active_level::get_block_coord_of_point( vec2_f24p8
		( the_coll_box.left(), the_coll_box.top() ) );
	const vec2_s32 end_pos = active_level::get_block_coord_of_point
		( vec2_f24p8( the_coll_box.right(), the_coll_box.bot() ) );
	real_size_2d = end_pos - start_pos + vec2_s32( 1, 1 );
	
	moving_left = s_moving_left;
	moving_right = s_moving_right;
	
	init_bcr_arr_2d_helper();
	
	for ( s32 j=0; j<real_height(); ++j )
	{
		for ( s32 i=0; i<real_width(); ++i )
		{
			data_at( i, j ) = block_coll_result( tl_corner() 
				+ vec2_s32( i, j ) );
		}
	}
	
}
block_coll_result_group::block_coll_result_group
	( const block_coll_result_group& to_copy )
{
	*this = to_copy;
}
block_coll_result_group& block_coll_result_group::operator = 
	( const block_coll_result_group& to_copy )
{
	arr_memcpy32( (block_coll_result*)bcr_arr_2d_helper_data, 
		to_copy.bcr_arr_2d_helper_data, max_size );
	
	start_pos = to_copy.start_pos;
	
	real_size_2d = to_copy.real_size_2d;
	
	moving_left = to_copy.moving_left;
	moving_right = to_copy.moving_right;
	
	init_bcr_arr_2d_helper();
	
	return *this;
}


