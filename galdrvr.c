// license:BSD-3-Clause
// copyright-holders:EmiDev
/***************************************************************************

 Emi Etsuko

 A Brand New Classic 80's Arcade Games for Emi Etsuko.
 Manufacturer: EmiDev (Konami License)
 Year: 1982
 Genre: Action/Platform (Vertical Screen)
 Player: 1-2
 Hardware: Scramble
 Control: 4-Way Joystick, 2 Button
 Source Driver Files: galdrvr.c
 Emulator: MAME4Droid (0.139u1)

***************************************************************************/

#include "emu.h"
#include "scramble.h"


// Placeholder ROM definitions - these will need to be updated with actual ROM data
ROM_START( emietsko )
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD( "emietsko.bin", 0x0000, 0x10000, NO_DUMP )

	ROM_REGION( 0x1000, "gfx1", 0 )
	ROM_LOAD( "emietsko.gfx", 0x0000, 0x1000, NO_DUMP )

	ROM_REGION( 0x0020, "proms", 0 )
	ROM_LOAD( "emietsko.prom", 0x0000, 0x0020, NO_DUMP )
ROM_END

ROM_START( emietskj )
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD( "emietskj.bin", 0x0000, 0x10000, NO_DUMP )

	ROM_REGION( 0x1000, "gfx1", 0 )
	ROM_LOAD( "emietskj.gfx", 0x0000, 0x1000, NO_DUMP )

	ROM_REGION( 0x0020, "proms", 0 )
	ROM_LOAD( "emietskj.prom", 0x0000, 0x0020, NO_DUMP )
ROM_END


// Placeholder Input Ports - based on scramble
static INPUT_PORTS_START( emietsuko )
	PORT_INCLUDE(scramble)
INPUT_PORTS_END


// Placeholder GFXDECODE - based on scramble
static GFXDECODE_START( gfx_emietsuko )
	GFXDECODE_ENTRY( "gfx1", 0x0000, scramble_charlayout,   0, 8 )
	GFXDECODE_ENTRY( "gfx1", 0x0000, scramble_spritelayout, 0, 8 )
GFXDECODE_END


// Game definitions
GAME( 1982, emietsko, 0, scramble, emietsuko, scramble_state, init_scramble_ppi, ROT90, "EmiDev (Konami License)", "Emi Etsuko (US)", MACHINE_SUPPORTS_SAVE )
GAME( 1982, emietskj, emietsko, scramble, emietsuko, scramble_state, init_scramble_ppi, ROT90, "EmiDev (Konami License)", "Emi Etsuko (Japan)", MACHINE_SUPPORTS_SAVE )
