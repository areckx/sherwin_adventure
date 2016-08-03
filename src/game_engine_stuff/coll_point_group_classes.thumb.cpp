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


#include "coll_point_group_classes.hpp"
#include "sprite_stuff/sprite_class.hpp"

// Thursday, July 23, 2015 (9:35 PM EST) Note: I will use a top middle coll
// point and a bottom middle coll point, starting tomorrow.  

// The top middle coll point will be used for checking the type of block
// that has been hit by a sprite that has jumped.  

// The bottom middle coll point will be used
// as the primary thing for checking if a sprite is on the ground.


// Friday, October 23, 2015 (12:10 PM CST) Lol, I forgot that the first
// comment was there.

#define generate_pt(name) \
	vec2_f24p8 & pt_##name = get_pt_##name();
#define X(name) \
	pt_##name.x =
#define Y(name) \
	pt_##name.y =


void coll_point_group_base::assign_vert_side_x_positions
	( const coll_box& the_coll_box, vec2_f24p8& pt_lt, vec2_f24p8& pt_lm, 
	vec2_f24p8& pt_lb, vec2_f24p8& pt_rt, vec2_f24p8& pt_rm, 
	vec2_f24p8& pt_rb )
{
	//pt_lt.x = pt_lm.x = pt_lb.x = the_coll_box.left();
	
	//pt_rt.x = pt_rm.x = pt_rb.x = the_coll_box.right();
	list_of_shared_left_side_coll_point_names(X)
		the_coll_box.left();
	
	list_of_shared_right_side_coll_point_names(X)
		the_coll_box.right();
	
	//list_of_shared_middle_vert_line_coll_point_names(X)
	//	the_coll_box.left() + (fixed24p8){ the_coll_box.size.x.data / 2 };
	
}
void coll_point_group_base::assign_horiz_side_y_positions
	( const sprite& the_sprite, const coll_box& the_coll_box, 
	vec2_f24p8& pt_tl, vec2_f24p8& pt_tm, vec2_f24p8& pt_tr, 
	vec2_f24p8& pt_bl, vec2_f24p8& pt_bm, vec2_f24p8& pt_br )
{
	list_of_shared_top_side_coll_point_names(Y)
		the_coll_box.top();
	
	// This is a special case that covers walking down a slope.  However,
	// it would be good if I could make this not needed.
	if ( the_sprite.get_curr_on_ground() 
		&& the_sprite.vel.y >= (fixed24p8){0} )
	{
		list_of_shared_bot_side_coll_point_names(Y)
			the_coll_box.bot() + sprite::cpg_on_slope_threshold_abs;
			//the_coll_box.bot() + (fixed24p8){0x400};
			//the_coll_box.bot() + (fixed24p8){0x200};
			//the_coll_box.bot() + (fixed24p8){0x300};
	}
	else //if (!the_sprite.get_curr_on_ground())
	{
		list_of_shared_bot_side_coll_point_names(Y)
			the_coll_box.bot();
	}
}


void coll_point_group_base::assign_vert_side_mid_y_positions
	( const coll_box& the_coll_box, vec2_f24p8& pt_lm, vec2_f24p8& pt_rm )
{
	list_of_shared_vert_side_ypos_mid_coll_point_names(Y)
		the_coll_box.top() + (fixed24p8){ the_coll_box.size.y.data / 2 };
}
void coll_point_group_base::assign_horiz_side_mid_x_positions
	( const coll_box& the_coll_box, vec2_f24p8& pt_tm, vec2_f24p8& pt_bm )
{
	list_of_shared_horiz_side_xpos_mid_coll_point_names(X)
		the_coll_box.left() + (fixed24p8){ the_coll_box.size.x.data / 2 };
}



coll_point_group_16x16::coll_point_group_16x16( const sprite& the_sprite )
{
	const coll_box& the_coll_box = the_sprite.the_coll_box;
	
	// The collision points
	list_of_shared_coll_point_names(generate_pt)
	
	
	// Left and Right
	assign_vert_side_x_positions( the_coll_box, pt_lt, pt_lm, pt_lb, pt_rt, 
		pt_rm, pt_rb );
	
	assign_vert_side_top_y_positions( the_coll_box, pt_lt, pt_rt );
	assign_vert_side_mid_y_positions( the_coll_box, pt_lm, pt_rm );
	assign_vert_side_bot_y_positions( the_coll_box, pt_lb, pt_rb );
	
	
	// Top and Bottom
	assign_horiz_side_left_x_positions( the_coll_box, pt_tl, pt_bl );
	assign_horiz_side_mid_x_positions( the_coll_box, pt_tm, pt_bm );
	assign_horiz_side_right_x_positions( the_coll_box, pt_tr, pt_br );
	
	assign_horiz_side_y_positions( the_sprite, the_coll_box, pt_tl, pt_tm, 
		pt_tr, pt_bl, pt_bm, pt_br );
}

void coll_point_group_16x16::assign_vert_side_top_y_positions
	( const coll_box& the_coll_box, vec2_f24p8& pt_lt, vec2_f24p8& pt_rt )
{
	list_of_shared_vert_side_ypos_top_coll_point_names(Y) 
		the_coll_box.top() + (fixed24p8){ the_coll_box.size.y.data / 4 };
}
void coll_point_group_16x16::assign_vert_side_bot_y_positions
	( const coll_box& the_coll_box, vec2_f24p8& pt_lb, vec2_f24p8& pt_rb )
{
	list_of_shared_vert_side_ypos_bot_coll_point_names(Y) 
		the_coll_box.bot() - (fixed24p8){ the_coll_box.size.y.data / 4 };
}


void coll_point_group_16x16::assign_horiz_side_left_x_positions
	( const coll_box& the_coll_box, vec2_f24p8& pt_tl, vec2_f24p8& pt_bl )
{
	list_of_shared_horiz_side_xpos_left_coll_point_names(X)
		the_coll_box.left() + (fixed24p8){ the_coll_box.size.x.data / 4 };
}
void coll_point_group_16x16::assign_horiz_side_right_x_positions
	( const coll_box& the_coll_box, vec2_f24p8& pt_tr, vec2_f24p8& pt_br )
{
	list_of_shared_horiz_side_xpos_right_coll_point_names(X)
		the_coll_box.right() - (fixed24p8){ the_coll_box.size.x.data / 4 };
}



coll_point_group_16x32::coll_point_group_16x32( const sprite& the_sprite )
{
	const coll_box& the_coll_box = the_sprite.the_coll_box;
	
	// The collision_points
	list_of_shared_coll_point_names(generate_pt)
	
	// Left and Right
	assign_vert_side_x_positions( the_coll_box, pt_lt, pt_lm, pt_lb, pt_rt, 
		pt_rm, pt_rb );
	
	assign_vert_side_top_y_positions( the_coll_box, pt_lt, pt_rt );
	assign_vert_side_mid_y_positions( the_coll_box, pt_lm, pt_rm );
	assign_vert_side_bot_y_positions( the_coll_box, pt_lb, pt_rb );
	
	
	
	// Top and Bottom
	assign_horiz_side_left_x_positions( the_coll_box, pt_tl, pt_bl );
	assign_horiz_side_mid_x_positions( the_coll_box, pt_tm, pt_bm );
	assign_horiz_side_right_x_positions( the_coll_box, pt_tr, pt_br );
	
	assign_horiz_side_y_positions( the_sprite, the_coll_box, pt_tl, pt_tm, 
		pt_tr, pt_bl, pt_bm, pt_br );
}

void coll_point_group_16x32::assign_vert_side_top_y_positions
	( const coll_box& the_coll_box, vec2_f24p8& pt_lt, vec2_f24p8& pt_rt )
{
	list_of_shared_vert_side_ypos_top_coll_point_names(Y)
		the_coll_box.top() + sprite::cpg_16x32_threshold_abs.y;
}
void coll_point_group_16x32::assign_vert_side_bot_y_positions
	( const coll_box& the_coll_box, vec2_f24p8& pt_lb, vec2_f24p8& pt_rb )
{
	list_of_shared_vert_side_ypos_bot_coll_point_names(Y)
		the_coll_box.bot() - sprite::cpg_16x32_threshold_abs.y;
}


void coll_point_group_16x32::assign_horiz_side_left_x_positions
	( const coll_box& the_coll_box, vec2_f24p8& pt_tl, vec2_f24p8& pt_bl )
{
	list_of_shared_horiz_side_xpos_left_coll_point_names(X)
		the_coll_box.left() + sprite::cpg_16x32_threshold_abs.x;
}
void coll_point_group_16x32::assign_horiz_side_right_x_positions
	( const coll_box& the_coll_box, vec2_f24p8& pt_tr, vec2_f24p8& pt_br )
{
	list_of_shared_horiz_side_xpos_right_coll_point_names(X)
		the_coll_box.right() - sprite::cpg_16x32_threshold_abs.x;
}


#undef generate_pt
#undef X
#undef Y


