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


#include "sprite_allocator_class.hpp"
#include "sprite_class.hpp"

sprite_allocator::sprite_allocator( int* the_sa_free_list_backend_array, 
	sprite* the_array, u32 s_size )
	: the_sa_free_list_backend_curr_index(0),
	the_sa_free_list_backend( the_sa_free_list_backend_array,
	&the_sa_free_list_backend_curr_index, s_size ),
	array_helper<sprite>( the_array, s_size )
{
}
sprite_allocator::sprite_allocator( int* the_sa_free_list_backend_array,
	const array_helper<sprite>& s_allocatable_sprite_arr )
	: the_sa_free_list_backend_curr_index(0),
	the_sa_free_list_backend( the_sa_free_list_backend_array,
	&the_sa_free_list_backend_curr_index, 
	s_allocatable_sprite_arr.get_size() ),
	array_helper<sprite>(s_allocatable_sprite_arr)
{
}

void* sprite_allocator::allocate_sprite()
{
	// This could definitely be faster
	for ( u32 i=0; i<get_size(); ++i )
	{
		sprite& curr_sprite = data_at(i);
		
		if ( curr_sprite.the_sprite_type == st_default )
		{
			return (void*)(&curr_sprite);
		}
	}
	
	
	// No free sprite found, so at least put something in the debug vars.
	// cout or printf would be nice here.
	//next_debug_u32 = ( ( 'a' << 24 ) | ( 's' << 16 ) | ( 'p' << 8 )
	//	| ( 'r' << 0 ) );
	
	debug_arr_group::write_str_and_inc("NoFreeSprite");
	
	return NULL;
}

void sprite_allocator::deallocate_sprite( sprite*& the_sprite )
{
	if ( the_sprite == NULL )
	{
		return;
	}
	
	
	the_sprite->the_sprite_type = st_default;
	
	
	if ( the_sprite->the_sprite_ipg != NULL )
	{
		if ( the_sprite->the_sprite_ipg->spawn_state == sss_active )
		{
			the_sprite->the_sprite_ipg->spawn_state = sss_not_active;
		}
		the_sprite->the_sprite_ipg = NULL;
	}
	
	//u32 old_vram_chunk_index = the_sprite->get_vram_chunk_index();
	//
	//*the_sprite = sprite();
	//the_sprite->shared_constructor_code();
	//*the_sprite = sprite(the_sprite->get_vram_chunk_index());
	
	
	the_sprite = NULL;
	
	//for ( u32 i=0; i<get_size(); ++i )
	//{
	//	sprite& curr_sprite = data_at(i);
	//	
	//	if ( *the_sprite == &curr_sprite )
	//	{
	//		the_sprite->~sprite();
	//		the_sprite = NULL;
	//		
	//		return;
	//	}
	//}
	
	
	//// No sprite found, so at least put something in the debug vars.
	//// cout or printf would be nice here.
	//next_debug_u32 = ( ( 'd' << 24 ) | ( 's' << 16 ) | ( 'p' << 8 )
	//	| ( 'r' << 0 ) );
}


