// This file is part of Sherwin's Adventure.
// 
// Copyright 2015-2017 by Andrew Clark (FL4SHK).
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


#include "../general_utility_stuff/range_funcs.hpp"
#include "coll_box_class.hpp"
#include "coll_lseg_classes.hpp"


//bool generic_coll_lseg::intersects( const generic_coll_lseg& to_check,
//	vec2_f24p8* ret ) const
//{
//	const vec2_f24p8& p = end_points[0];
//	const vec2_f24p8& r = end_points[1];
//	
//	const vec2_f24p8& q = to_check.end_points[0];
//	const vec2_f24p8& s = to_check.end_points[1];
//	
//	fixed24p8 t, u;
//	
//	const fixed24p8 r_zcross_s = r.zcross(s);
//	
//	const vec2_f24p8 q_minus_p = q - p;
//	
//	const fixed24p8 u_num = q_minus_p.zcross(s);
//	
//	if ( r_zcross_s != (fixed24p8){0} )
//	{
//		const fixed24p8 t_num = q_minus_p.zcross(r);
//		
//		
//		if ( ret != NULL )
//		{
//			
//		}
//	}
//	else if ( u_num == (fixed24p8){0} )
//	{
//		const fixed24p8 r_dot_r = r.dot(r);
//		const fixed24p8 s_dot_r = s.dot(r);
//		const fixed24p8 t_0 = q_minus_p.dot(r) / r_dot_r;
//		const fixed24p8 t_1 = t_0 + ( s_dot_r / r_dot_r );
//		
//		const bool t01_in_range_0_to_1 
//			= in_range_inclusive( t_0, make_f24p8(0), make_f24p8(1) )
//			|| in_range_inclusive( t_1, make_f24p8(0), make_f24p8(1) );
//		
//		if (!t01_in_range_0_to_1)
//		{
//			if ( s_dot_r < make_f24p8(0) )
//			{
//				
//			}
//			else
//			{
//				
//			}
//		}
//		return true;
//	}
//	
//	return false;
//}

bool coll_lseg_extras::collinear_lsegs_intersect
	( const fixed24p8& a_0, const fixed24p8& a_1, const fixed24p8& b_0, 
	const fixed24p8& b_1 )
{
	return ( in_range_inclusive( a_0, a_1, b_0 ) 
		|| in_range_inclusive( a_0, a_1, b_1 )
		|| in_range_inclusive( b_0, b_1, a_0 ) 
		|| in_range_inclusive( b_0, b_1, a_1 ) );
}



// This constructor ONLY sets the array_helpers themselves; it DOES NOT
// touch the arrays being wrapped.
coll_lseg_group_base::coll_lseg_group_base
	( bcr_lseg_group* s_horiz_bcr_lg_arr, 
	bcr_lseg_group* s_vert_bcr_lg_arr, 
	horiz_coll_lseg* s_horiz_clseg_arr, vert_coll_lseg* s_vert_clseg_arr, 
	size_t s_num_horiz_lsegs, size_t s_num_vert_lsegs, u32 s_on_ground )
	: horiz_bcr_lseg_groups( s_horiz_bcr_lg_arr, s_num_horiz_lsegs ),
	vert_bcr_lseg_groups( s_vert_bcr_lg_arr, s_num_vert_lsegs ),
	horiz_clseg_groups( s_horiz_clseg_arr, s_num_horiz_lsegs ),
	vert_clseg_groups( s_vert_clseg_arr, s_num_vert_lsegs ),
	internal_on_ground(s_on_ground)
{
}

// This function should be called only by derived classes, and ONLY AFTER
// setting up internal_horiz_clseg_arr and internal_vert_clseg_arr
void coll_lseg_group_base::init_bcr_lseg_groups_themselves()
{
	for ( size_t i=0; i<horiz_clseg_groups.get_size(); ++i )
	{
		horiz_bcr_lseg_groups[i].init(horiz_clseg_groups[i]);
	}
	
	for ( size_t i=0; i<vert_clseg_groups.get_size(); ++i )
	{
		vert_bcr_lseg_groups[i].init(vert_clseg_groups[i]);
	}
}

const fixed24p8 coll_lseg_group_16x32::offset_y_for_top_hs_og
	= make_f24p8(-4);
const fixed24p8 coll_lseg_group_16x32::offset_y_for_bot_hs_og
	= make_f24p8(4);



coll_lseg_group_16x32::coll_lseg_group_16x32( const coll_box& s_coll_box,
	u32 s_on_ground )
	: coll_lseg_group_base( internal_horiz_bcr_lg_arr,
	internal_vert_bcr_lg_arr, internal_horiz_clseg_arr,
	internal_vert_clseg_arr, internal_num_horiz_lsegs,
	internal_num_vert_lsegs, s_on_ground )
{
	
}

