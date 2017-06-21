// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2017 Andrew Clark (FL4SHK).
// 
// Sherwin's Adventure is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// Sherwin's Adventure is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License FOR more details.
// 
// You should have received a copy of the GNU General Public License along
// with Sherwin's Adventure.  If not, see <http://www.gnu.org/licenses/>.


#ifndef gfx_manager_class_hpp
#define gfx_manager_class_hpp


#include "block_stuff/block_stuff.hpp"

#include "../general_utility_stuff/misc_types.hpp"
#include "../gba_specific_stuff/attribute_defines.hpp"
#include "../gba_specific_stuff/gfx_reg_stuff.hpp"

#include "../general_utility_stuff/sa_stack_classes.hpp"

class sprite;



// There are a total of 16 BG palettes provided by the GBA hardware, each
// with 15 colors (and one transparent "color").  This enum is intended to
// be used FOR BG palette slots during these game modes:  gm_loading_level,
// gm_changing_sublevel, and gm_in_sublevel.
enum bg_palette_slot_in_level
{
	// When in a level, blocks use palette slots 0, 1, 2, and 3 FOR now.
	// Perhaps in the future blocks will be able to use more than just
	// these palette slots, what with there being 16 total BG palette
	// slots.
	bgps_in_level_block_0,
	bgps_in_level_block_1,
	bgps_in_level_block_2,
	bgps_in_level_block_3,
	
	// The HUD gets its own palette slot, too.  It is possible that the HUD
	// may eventually need to use more than one palette slot.
	bgps_in_level_hud,
	
	// This is the number of --used-- BG palette slots when in a level,
	// and it is automatically updated by the compiler.  This might count
	// as a simple hack since it basically abuses the way enums work.
	lim_bgps_in_level,
	
} __attribute__((_ALIGN4));


//enum bg_palette_slot_in_overworld



// There are a total of 16 sprite palettes provided by the GBA hardware,
// each with 15 colors (and one transparent "color").  This enum is
// intended to be used FOR sprite palette slots during these game_mode's:
// gm_loading_level, gm_changing_sublevel, and gm_in_sublevel.
enum sprite_palette_slot
{
	// The player uses sprite palette slot 0.
	sps_player,
	
	// Powerup sprites use sprite palette slot 1.
	sps_powerup,
	
	//// Block-like sprites use sprite palette slots 2 and 3.
	//sps_block_like_0,
	//sps_block_like_1,
	
	// Door sprites use sprite palette slot 2.  Eventually, doors might be
	// represented using block stuff.
	sps_door,
	
	//// Enemy sprites use sprite palette slots 4, 5, and 6
	// Enemy sprites use sprite palette slots 3, 4, and 5.  
	// Perhaps there will eventually be a need FOR dynamic enemy palettes,
	// based on which types of enemies are in a particular level.  This
	// would require some changes to the level class.
	sps_enemy_0,
	sps_enemy_1,
	sps_enemy_2,
	
	// Secondary sprites use sprite palette slots 6 and 7
	sps_secondary_0,
	sps_secondary_1,
	
	
	// This is the number of --used-- sprite palette slots when in a level,
	// and it is automatically updated by the compiler.  This might count
	// as a simple hack since it basically abuses the way enums work.
	lim_sps,
} __attribute__((_ALIGN4));


class gfx_manager
{
public:		// variables and constants
	
	static constexpr u32 num_tiles_in_ss_8x8 = ( 8 * 8 ) 
		/ num_pixels_per_tile;
	static constexpr u32 num_tiles_in_ss_16x16 = ( 16 * 16 ) 
		/ num_pixels_per_tile;
	static constexpr u32 num_tiles_in_ss_32x32 = ( 32 * 32 ) 
		/ num_pixels_per_tile;
	static constexpr u32 num_tiles_in_ss_64x64 = ( 64 * 64 ) 
		/ num_pixels_per_tile;
	static constexpr u32 num_tiles_in_ss_16x8 = ( 16 * 8 ) 
		/ num_pixels_per_tile;
	static constexpr u32 num_tiles_in_ss_32x8 = ( 32 * 8 ) 
		/ num_pixels_per_tile;
	static constexpr u32 num_tiles_in_ss_32x16 = ( 32 * 16 ) 
		/ num_pixels_per_tile;
	static constexpr u32 num_tiles_in_ss_64x32 = ( 64 * 32 ) 
		/ num_pixels_per_tile;
	static constexpr u32 num_tiles_in_ss_8x16 = ( 8 * 16 ) 
		/ num_pixels_per_tile;
	static constexpr u32 num_tiles_in_ss_8x32 = ( 8 * 32 ) 
		/ num_pixels_per_tile;
	static constexpr u32 num_tiles_in_ss_16x32 = ( 16 * 32 ) 
		/ num_pixels_per_tile;
	static constexpr u32 num_tiles_in_ss_32x64 = ( 32 * 64 ) 
		/ num_pixels_per_tile;
	
	
	
	static const u32 bgofs_mirror_size = 4;
	
	static bg_point prev_prev_bgofs_mirror[bgofs_mirror_size]
		__attribute__((_IWRAM));
	static prev_curr_pair<bg_point> bgofs_mirror[bgofs_mirror_size]
		__attribute__((_IWRAM));
	
	// Current component arrays, stored in EWRAM as fixed24p8's FOR speed
	// and accuracy reasons.
	static constexpr u32 bg_fade_curr_component_arr_size 
		= num_colors_in_8_palettes;
	
	// -- Switch to linear_memory_allocator --
	static fixed24p8 bg_fade_curr_red_arr
		[bg_fade_curr_component_arr_size] __attribute__((_EWRAM)),
	bg_fade_curr_green_arr
		[bg_fade_curr_component_arr_size] __attribute__((_EWRAM)),
	bg_fade_curr_blue_arr
		[bg_fade_curr_component_arr_size] __attribute__((_EWRAM));

	static constexpr u32 obj_fade_curr_component_arr_size 
		= num_colors_in_8_palettes;
	
	// -- Switch to linear_memory_allocator --
	static fixed24p8 obj_fade_curr_red_arr
		[obj_fade_curr_component_arr_size] __attribute__((_EWRAM)),
	obj_fade_curr_green_arr
		[obj_fade_curr_component_arr_size] __attribute__((_EWRAM)),
	obj_fade_curr_blue_arr
		[obj_fade_curr_component_arr_size] __attribute__((_EWRAM));
	
	
	// Fade out/in step amounts.
	static constexpr u32 bg_fade_step_amount_arr_size 
		= num_colors_in_8_palettes;
	
	// -- Switch to linear_memory_allocator --
	static fixed24p8 bg_fade_red_step_amount_arr
		[bg_fade_step_amount_arr_size] __attribute__((_EWRAM)),
	bg_fade_green_step_amount_arr
		[bg_fade_step_amount_arr_size] __attribute__((_EWRAM)),
	bg_fade_blue_step_amount_arr
		[bg_fade_step_amount_arr_size] __attribute__((_EWRAM));
	
	static constexpr u32 obj_fade_step_amount_arr_size 
		= num_colors_in_8_palettes;
	
	// -- Switch to linear_memory_allocator --
	static fixed24p8 obj_fade_red_step_amount_arr
		[obj_fade_step_amount_arr_size] __attribute__((_EWRAM)),
	obj_fade_green_step_amount_arr
		[obj_fade_step_amount_arr_size] __attribute__((_EWRAM)),
	obj_fade_blue_step_amount_arr
		[obj_fade_step_amount_arr_size] __attribute__((_EWRAM));
	
	
	// Sprite VRAM allocation stuff
	
	// 64 max sprites on screen at once should be plenty.  Sprite
	// VRAM will be allocated in chunks of 32x32 pixels, or 8 tiles of 8x8
	// pixels.  It's unlikely that any sprites larger than 32x32 would be
	// needed.  Also, this is only the case FOR 4bpp graphics.
	static constexpr u32 max_num_32x32_metatiles = 64;
	
	// BG palette stuff
	// -- Switch to linear_memory_allocator --
	static u16 bg_pal_mirror[bg_pal_ram_size_in_u16]
		__attribute__((_EWRAM));
	
	// Sprite palette stuff
	// -- Switch to linear_memory_allocator --
	static u16 obj_pal_mirror[obj_pal_ram_size_in_u16] 
		__attribute__((_EWRAM));
	
	// HUD stuff
	// -- Switch to linear_memory_allocator --
	static u32 hud_vram_as_tiles_start_offset __attribute__((_EWRAM));
	
public:		// functions
	
	static inline void back_up_bgofs_mirror()
	{
		//bgofs_mirror[0].back_up();
		//bgofs_mirror[1].back_up();
		//bgofs_mirror[2].back_up();
		//bgofs_mirror[3].back_up();
		
		FOR ( u32 i=0; i<bgofs_mirror_size; ++i )
		{
			prev_prev_bgofs_mirror[i] = bgofs_mirror[i].prev;
			bgofs_mirror[i].back_up();
		}
	}
	
	static void copy_bgofs_mirror_to_registers();
	
	
	// Block graphics stuff
	//static inline u32 get_metatile_number_of_block_type
	//	( block_type the_block_type ) __attribute__((always_inline));
	static inline u32 get_metatile_number_of_block_type
		( block_type the_block_type )
	{
		return block_stuff_array[the_block_type]->get_metatile_number();
	}
	
	
	
	//static inline const u32 get_graphics_slot_of_block_type 
	//	( block_type the_block_type ) __attribute__((always_inline));
	static inline const u32 get_graphics_slot_of_block_type 
		( block_type the_block_type )
	{
		// This assumes that EVERY block uses 4 graphics slots in VRAM
		//return ( the_block_type * 4 );
		return block_stuff_array[the_block_type]
			->get_metatile_graphics_slot() * num_tiles_in_ss_16x16;
	}
	
	//static inline u32 get_palette_number_of_block_type
	//	( block_type the_block_type ) __attribute__((always_inline));
	static inline u32 get_palette_number_of_block_type
		( block_type the_block_type )
	{
		return block_stuff_array[the_block_type]->get_palette_number();
	}
	
	static void upload_bg_palettes_to_target( vu16* target );
	static inline void upload_bg_palettes_to_target( u16* target )
	{
		upload_bg_palettes_to_target((vu16*)target);
	}
	
	static void copy_bg_pal_mirror_to_bg_pal_ram();
	
	static void upload_bg_tiles_to_vram() __attribute__((_IWRAM_CODE));
	
	
	// Sprite graphics stuff
	static void upload_sprite_palettes_to_target( vu16* target ); 
	static inline void upload_sprite_palettes_to_target( u16* target )
	{
		upload_sprite_palettes_to_target((vu16*)target);
	}
	static void copy_obj_pal_mirror_to_obj_pal_ram();
	
	
	static void upload_sprite_tiles_to_vram( sprite& the_sprite )
		__attribute__((_IWRAM_CODE));
	
	// HUD stuff
	static inline void init_hud_vram_as_tiles_start_offset()
	{
		hud_vram_as_tiles_start_offset = 0;
		FOR ( u32 i=0; i<block_type::lim_bt; ++i )
		{
			u32 graphics_slot = get_graphics_slot_of_block_type 
				( (block_type)i );
			
			if ( hud_vram_as_tiles_start_offset < graphics_slot )
			{
				hud_vram_as_tiles_start_offset = graphics_slot;
			}
		}
		hud_vram_as_tiles_start_offset += num_tiles_in_ss_16x16;
	}
	
	
	// Fading stuff
	static void fade_out_to_black( u32 num_steps, 
		u32 num_frames_to_wait_per_iter=1 ) __attribute__((_IWRAM_CODE));
	
	static void fade_out_to_white( u32 num_steps, 
		u32 num_frames_to_wait_per_iter=1 ) __attribute__((_IWRAM_CODE));
	
	static void fade_in( u32 num_steps, 
		u32 num_frames_to_wait_per_iter=1 ) __attribute__((_IWRAM_CODE));
	
	
	
	
} __attribute__((_ALIGN4));




#endif		// gfx_manager_class_hpp
