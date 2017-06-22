// This file Is part of Sherwin's Adventure.
// 
// Copyright 2015-2017 by Andrew Clark (FL4SHK).
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


#include "generic_funcptr_stuff.hpp"


extern "C"
{

void generic_binary_func_shared_backend( void* a, void* b,
	generic_void_2arg_fp the_fp )
{
	(*the_fp)( a, b );
}

u32 generic_u32_func_shared_backend( void* a, void* b,
	generic_u32_2arg_fp the_fp )
{
	return (*the_fp)( a, b );
}

}
