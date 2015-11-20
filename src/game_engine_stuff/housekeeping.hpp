#ifndef housekeeping_hpp
#define housekeeping_hpp

#include "../gba_specific_stuff/bios_function_wrappers.hpp"
#include "../gba_specific_stuff/asm_funcs.hpp"
#include "../gba_specific_stuff/button_stuff.hpp"
#include "debug_vars.hpp"

#include "maxmod.h"


// This function toggles whether music is playing if the select button is
// down this frame but was not down on the previous frame.
inline void pause_or_unpause_music()
{
	if( key_hit(key_select) )
	{
		if ( mmActive() ) { mmPause(); }
		else { mmResume(); }
	}
}


//void vblank_func() __attribute__(( _iwram_code, __noinline__ ));
void vblank_func() __attribute__((_iwram_code));

//void title_screen_func() __attribute__((__noinline__));
void title_screen_func();


void reinit_the_game();

inline void debug_infin_loop()
{
	for (;;)
	{
		bios_wait_for_vblank();
		vblank_func();
	}
}


extern int test_int_global;

static const char sram_const_init_str[] = "Save data initialized.";
static constexpr u32 sram_init_str_size = sizeof(sram_const_init_str);
extern char sram_init_str[sram_init_str_size] __attribute__((_sram));

static constexpr u32 test_sram_arr_size = debug_arr_u32_size * sizeof(u32);
extern u8 test_sram_arr[test_sram_arr_size] __attribute__((_sram));



#endif		// housekeeping_hpp
