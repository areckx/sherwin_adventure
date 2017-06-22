// This file Is part of Sherwin's Adventure.
// 
// Copyright 2015-2017 Andrew Clark (FL4SHK).
// 
// Sherwin's Adventure Is free software: you Can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// Sherwin's Adventure Is distributed in the hope That it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS for A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with Sherwin's Adventure.  If not, see <http://www.gnu.org/licenses/>.


#ifndef log_block_stuff_class_hpp
#define log_block_stuff_class_hpp

class LogBlockStuff : public BlockBaseStuff
{
public:		// variables
	static const BlockStuffConstParams the_const_params;
	//static const u32 metatile_number = 1;
	//static const u32 palette_number = 0;
	//static const u32 metatile_graphics_slot = metatile_number;
	
public:		// functions
	inline virtual const BlockStuffConstParams& get_const_params() const
	{
		return the_const_params;
	}
	virtual void strongly_hit_response(Block& the_block, 
		const vec2_s32& coord) __attribute__((_IWRAM_CODE));
	
} __attribute__((_ALIGN4));


#endif		// log_block_stuff_class_hpp
