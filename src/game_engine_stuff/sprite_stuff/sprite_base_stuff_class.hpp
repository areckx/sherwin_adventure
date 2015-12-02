#ifndef sprite_base_stuff_class_hpp
#define sprite_base_stuff_class_hpp

#include "../gfx_manager_class.hpp"
#include "../level_stuff/active_level_class.hpp"
//#include "sprite_manager_class.hpp"

#include "../../gfx/sherwin_gfx.h"


class sprite_base_stuff
{
public:		// variables
	
	static constexpr fixed24p8 grav_acc = {0x80};
	static constexpr fixed24p8 max_y_vel = {0x400};
	
	static constexpr sprite_palette_slot the_palette_slot = sps_player;
	//static constexpr u32 the_relative_metatile_slot = 7,
	//	num_active_gfx_tiles = gfx_manager::num_tiles_in_ss_16x16;
	
	static constexpr u32 the_relative_metatile_slot = 0,
		num_active_gfx_tiles = gfx_manager::num_tiles_in_ss_16x16;
	
	static constexpr tile* tile_arr = const_cast<tile*>
		(reinterpret_cast<const tile*>(sherwin_gfxTiles));
	
	static const oam_entry::shape_size the_initial_shape_size;
	
	static const vec2_f24p8 the_initial_coll_box_size,
		the_initial_cb_pos_offset;
	
public:		// functions
	// This is the default form of init().
	virtual void init( sprite& the_sprite, bool facing_left=true );
	
	// This form of init() might eventually become the default form of
	// init().
	virtual void init( sprite& the_sprite, 
		const vec2_f24p8& s_in_level_pos, const bg_point& camera_pos,
		bool facing_left=false );
	
	// This form of init() is primarily intended to be used by the_player.
	virtual void init( sprite& the_sprite, 
		const vec2_f24p8& s_in_level_pos, 
		const vec2_u32& the_level_size_2d, bg_point& camera_pos,
		bool facing_left=false );
	
	virtual const sprite_type get_sprite_type() const;
	
	inline virtual const tile* get_tile_arr() const
	{
		return tile_arr;
	}
	
	virtual void set_initial_shape_size_of_sprite( sprite& the_sprite ) 
		const;
	inline virtual const oam_entry::shape_size get_the_initial_shape_size() 
		const
	{
		return the_initial_shape_size;
	}
	
	virtual void set_initial_coll_box_stuff_of_sprite( sprite& the_sprite )
		const;
	
	inline virtual const vec2_f24p8& get_the_initial_coll_box_size() const
	{
		return the_initial_coll_box_size;
	}
	inline virtual const vec2_f24p8& get_the_initial_cb_pos_offset() const
	{
		return the_initial_cb_pos_offset;
	}
	
	
	
	
	virtual void gfx_update( sprite& the_sprite )
		__attribute__((_iwram_code));
	
	
	virtual void update_part_1( sprite& the_sprite )
		__attribute__((_iwram_code));
	
	
	
	// The player_sprite_stuff class is the primary user of this function.
	virtual void update_part_2( sprite& the_sprite, bg_point& camera_pos,
		const vec2_u32& the_level_size_2d ) __attribute__((_iwram_code));
	
	virtual void update_part_2( sprite& the_sprite, 
		const bg_point& camera_pos, int& next_oam_index )
		__attribute__((_iwram_code));
	
	
	
	
	// Graphics stuff
	//virtual const u32 get_curr_tile_slot_old( sprite& the_sprite )
	//	__attribute__((_iwram_code));
	
	virtual const u32 get_curr_tile_slot( sprite& the_sprite )
		__attribute__((_iwram_code));
	
	virtual const sprite_palette_slot get_palette_slot 
		( sprite& the_sprite ) __attribute__((_iwram_code));
	virtual const u32 get_curr_relative_tile_slot( sprite& the_sprite )
		__attribute__((_iwram_code));
	inline virtual const u32 get_num_active_gfx_tiles()
	{
		return num_active_gfx_tiles;
	}
	
	// Physics and collision stuff
	virtual void block_collision_stuff( sprite& the_sprite )
		__attribute__((_iwram_code));
	
	virtual void apply_gravity( sprite& the_sprite )
		__attribute__((_iwram_code));
	virtual void handle_jumping_stuff( sprite& the_sprite, 
		u32 is_jump_key_hit, u32 is_jump_key_held )
		__attribute__((_iwram_code));
	
	
	
	
protected:		// functions
	
	// Here are a lot of block collision functions.  It is recommended that
	// they be stored in IWRAM for as much speed as possible.
	void get_basic_block_coll_results_left_16x16
		( coll_point_group& the_pt_group, 
		block_coll_result& lt_coll_result, 
		block_coll_result& lb_coll_result ) __attribute__((_iwram_code));
	void get_basic_block_coll_results_top_16x16
		( coll_point_group& the_pt_group, 
		block_coll_result& tl_coll_result, 
		block_coll_result& tm_coll_result, 
		block_coll_result& tr_coll_result ) __attribute__((_iwram_code));
	void get_basic_block_coll_results_right_16x16
		( coll_point_group& the_pt_group, 
		block_coll_result& rt_coll_result, 
		block_coll_result& rb_coll_result ) __attribute__((_iwram_code));
	void get_basic_block_coll_results_bot_16x16
		( coll_point_group& the_pt_group, 
		block_coll_result& bl_coll_result, 
		block_coll_result& bm_coll_result, 
		block_coll_result& br_coll_result ) __attribute__((_iwram_code));
	
	
	void get_basic_block_coll_results_left_16x32
		( coll_point_group& the_pt_group, 
		block_coll_result& lt_coll_result, 
		block_coll_result& lm_coll_result,
		block_coll_result& lb_coll_result ) __attribute__((_iwram_code));
	void get_basic_block_coll_results_top_16x32
		( coll_point_group& the_pt_group, 
		block_coll_result& tl_coll_result, 
		block_coll_result& tm_coll_result,
		block_coll_result& tr_coll_result ) __attribute__((_iwram_code));
	void get_basic_block_coll_results_right_16x32
		( coll_point_group& the_pt_group, 
		block_coll_result& rt_coll_result,
		block_coll_result& rm_coll_result,
		block_coll_result& rb_coll_result ) __attribute__((_iwram_code));
	void get_basic_block_coll_results_bot_16x32
		( coll_point_group& the_pt_group, 
		block_coll_result& bl_coll_result, 
		block_coll_result& bm_coll_result,
		block_coll_result& br_coll_result ) __attribute__((_iwram_code));
	
	
	virtual void block_coll_response_left_16x16( sprite& the_sprite, 
		const block_coll_result& lt_coll_result, 
		const block_coll_result& lb_coll_result )
		__attribute__((_iwram_code));
	virtual void block_coll_response_top_16x16( sprite& the_sprite, 
		const block_coll_result& tl_coll_result,
		const block_coll_result& tm_coll_result,
		const block_coll_result& tr_coll_result )
		__attribute__((_iwram_code));
	virtual void block_coll_response_right_16x16( sprite& the_sprite, 
		const block_coll_result& rt_coll_result,
		const block_coll_result& rb_coll_result )
		__attribute__((_iwram_code));
	virtual void non_slope_block_coll_response_bot_16x16
		( sprite& the_sprite, const block_coll_result& bl_coll_result,
		const block_coll_result& bm_coll_result, 
		const block_coll_result& br_coll_result )
		__attribute__((_iwram_code));
	virtual block_type slope_block_coll_response_bot_16x16
		( sprite& the_sprite, coll_point_group& the_pt_group,
		block_coll_result& bl_coll_result,
		block_coll_result& bm_coll_result,
		block_coll_result& br_coll_result, bool hitting_tltr=false )
		__attribute__((_iwram_code));
	
	
	virtual void block_coll_response_left_16x32( sprite& the_sprite, 
		const block_coll_result& lt_coll_result,
		const block_coll_result& lm_coll_result, 
		const block_coll_result& lb_coll_result )
		__attribute__((_iwram_code));
	virtual void block_coll_response_top_16x32( sprite& the_sprite, 
		const block_coll_result& tl_coll_result,
		const block_coll_result& tm_coll_result, 
		const block_coll_result& tr_coll_result )
		__attribute__((_iwram_code));
	virtual void block_coll_response_right_16x32( sprite& the_sprite, 
		const block_coll_result& rt_coll_result,
		const block_coll_result& rm_coll_result, 
		const block_coll_result& rb_coll_result )
		__attribute__((_iwram_code));
	virtual void non_slope_block_coll_response_bot_16x32
		( sprite& the_sprite, const block_coll_result& bl_coll_result,
		const block_coll_result& bm_coll_result, 
		const block_coll_result& br_coll_result )
		__attribute__((_iwram_code));
	virtual block_type slope_block_coll_response_bot_16x32
		( sprite& the_sprite, coll_point_group& the_pt_group,
		block_coll_result& bl_coll_result,
		block_coll_result& bm_coll_result,
		block_coll_result& br_coll_result, bool hitting_tltr=false )
		__attribute__((_iwram_code));
	
	
	virtual void block_collision_stuff_16x16( sprite& the_sprite )
		__attribute__((_iwram_code));
	virtual void block_collision_stuff_16x32( sprite& the_sprite )
		__attribute__((_iwram_code));
	virtual void block_collision_stuff_32x16( sprite& the_sprite )
		__attribute__((_iwram_code));
	virtual void block_collision_stuff_32x32( sprite& the_sprite )
		__attribute__((_iwram_code));
	
	
	
} __attribute__((_align4));




#endif		// sprite_base_stuff_class_hpp
