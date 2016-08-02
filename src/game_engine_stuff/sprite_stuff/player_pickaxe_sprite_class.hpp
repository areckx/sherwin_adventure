// This file is part of GBA Project Template.
// 
// Copyright 2015-2016 by Andrew Clark (FL4SHK).
// 
// GBA Project Template is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// GBA Project Template is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with GBA Project Template.  If not, see <http://www.gnu.org/licenses/>.


#ifndef player_pickaxe_sprite_class_hpp
#define player_pickaxe_sprite_class_hpp


#include "../../gfx/the_16x16_secondary_sprites_gfx.h"

class player_pickaxe_sprite : public sprite
{
public:		// enums
	// "Global" graphics frames
	enum frame
	{
		frm_angle_0 = 0,
		frm_angle_23 = 1, 
		frm_angle_45 = 2,
		frm_angle_90 = 3,
	} alignas(4);
	
	// This enum allows multiple frame_slot's to be represented by the same
	// frame.
	enum frame_slot
	{
		frm_slot_angle_0,
		frm_slot_angle_23, 
		frm_slot_angle_45,
		frm_slot_angle_90,
		
		// frm_slot_count is the amount of frame_slot's.  It is
		// automatically updated by the compiler.
		frm_slot_count,
	} alignas(4);
	
	
	// These are used to access misc_data_u and misc_data_s
	enum udata_index
	{
		udi_curr_frame_slot
	} alignas(4);
	
	
public:		// variables
	// Graphics constants
	
	// A constant array that is intended to be indexed with a frame_slot,
	// such that a frame_slot can be mapped to a frame.
	static constexpr u32 frame_slot_to_frame_arr_size = frm_slot_count;
	static const frame frame_slot_to_frame_arr
		[frame_slot_to_frame_arr_size];
	
	static constexpr sprite_type the_const_sprite_type = st_player_pickaxe;
	static constexpr sprite_palette_slot the_palette_slot 
		= sps_secondary_0;
	
	static constexpr u32 num_active_gfx_tiles 
		= gfx_manager::num_tiles_in_ss_16x16;
	
	static constexpr tile* tile_arr = const_cast<tile*>
		(reinterpret_cast<const tile*>
		(the_16x16_secondary_sprites_gfxTiles));
	
	static const oam_entry::shape_size the_initial_shape_size 
		= oam_entry::ss_16x16;
	
	static const vec2_f24p8 the_initial_coll_box_size,
		the_initial_cb_pos_offset;
	
	
public:		// functions
	inline player_pickaxe_sprite( bool facing_left )
	{
		shared_constructor_code_part_1();
		shared_constructor_code_part_2(facing_left);
		shared_constructor_code_part_3();
	}
	
	inline virtual const sprite_type get_const_sprite_type() const
	{
		return the_const_sprite_type;
	}
	
	virtual void update_part_1();
	
	//virtual void update_part_2( bg_point& camera_pos,
	//	const vec2_u32& the_level_size_2d ) __attribute__((_iwram_code));
	
	
	// Graphics stuff
	//virtual const u32 get_curr_tile_slot();
	
	inline virtual const sprite_palette_slot get_palette_slot()
	{
		return the_palette_slot;
	}
	virtual const u32 get_curr_relative_tile_slot();
	
	inline virtual const u32 get_num_active_gfx_tiles()
	{
		return num_active_gfx_tiles;
	}
	
	inline virtual const tile* get_tile_arr() const
	{
		return tile_arr;
	}
	
	inline virtual const oam_entry::shape_size get_the_initial_shape_size() 
		const
	{
		return the_initial_shape_size;
	}
	
	inline virtual const vec2_f24p8& get_the_initial_coll_box_size() const
	{
		return the_initial_coll_box_size;
	}
	inline virtual const vec2_f24p8& get_the_initial_cb_pos_offset() const
	{
		return the_initial_cb_pos_offset;
	}
	
	
	// Physics and collision stuff
	virtual void block_collision_stuff() __attribute__((_iwram_code));
	
	
protected:		// functions
	
	virtual void block_coll_response_left_16x16_old
		( const block_coll_result& lt_coll_result, 
		const block_coll_result& lb_coll_result );
	virtual void block_coll_response_top_16x16_old
		( const block_coll_result& tl_coll_result,
		const block_coll_result& tm_coll_result,
		const block_coll_result& tr_coll_result );
	virtual void block_coll_response_right_16x16_old
		( const block_coll_result& rt_coll_result,
		const block_coll_result& rb_coll_result );
	virtual void non_slope_block_coll_response_bot_16x16_old
		( const block_coll_result& bl_coll_result,
		const block_coll_result& bm_coll_result, 
		const block_coll_result& br_coll_result );
	
	
} __attribute__((_align4));


#endif		// player_pickaxe_sprite_class_hpp
