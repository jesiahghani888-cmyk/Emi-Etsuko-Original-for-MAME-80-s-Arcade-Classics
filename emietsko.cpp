// license:BSD-3-Clause
// copyright-holders:EmiDev
/***************************************************************************

  Emi Etsuko

  A Brand New Classic 80's Arcade Games for Emi Etsuko.
  Manufacturer: EmiDev
  Year: 1982
  Genre: Action/Platform (Vertical Screen)
  Player: 1-2
  Hardware: Scramble
  Control: 4-Way Joystick, 2 Button
  Source Driver Files: emietsko.cpp
  Emulator: MAME4Droid (0.139u1)

  Emi Etsuko: Rom Parent = emietsko.zip

***************************************************************************/

#include "emu.h"
#include "cpu/z80/z80.h"
#include "machine/i8255.h"
#include "sound/ay8910.h"
#include "includes/galaxian.h"

class emietsko_state : public galaxian_state
{
public:
	emietsko_state(const machine_config &mconfig, device_type type, const char *tag)
		: galaxian_state(mconfig, type, tag) { }

	void emietsko(machine_config &config);

private:
	void emietsko_map(address_map &map);
	void emietsko_sound_map(address_map &map);
	void emietsko_sound_io_map(address_map &map);
};

void emietsko_state::emietsko_map(address_map &map)
{
	map(0x0000, 0x3fff).rom();
	map(0x4000, 0x47ff).ram();
	map(0x4800, 0x4bff).ram().w(FUNC(emietsko_state::galaxian_videoram_w)).share("videoram");
	map(0x5000, 0x503f).ram().w(FUNC(emietsko_state::galaxian_attributesram_w)).share("attributesram");
	map(0x5040, 0x505f).ram().share("spriteram");
	map(0x5060, 0x507f).ram().share("bulletsram");
	map(0x6801, 0x6801).w(FUNC(emietsko_state::galaxian_nmi_enable_w));
	map(0x6802, 0x6802).w(FUNC(emietsko_state::galaxian_coin_counter_w));
	map(0x6804, 0x6804).w(FUNC(emietsko_state::galaxian_stars_enable_w));
	map(0x6806, 0x6806).w(FUNC(emietsko_state::galaxian_flip_screen_x_w));
	map(0x6807, 0x6807).w(FUNC(emietsko_state::galaxian_flip_screen_y_w));
	map(0x7000, 0x7000).r("watchdog", FUNC(watchdog_timer_device::reset_r));
	map(0x8100, 0x8103).rw("ppi8255_0", FUNC(i8255_device::read), FUNC(i8255_device::write));
	map(0x8200, 0x8203).rw("ppi8255_1", FUNC(i8255_device::read), FUNC(i8255_device::write));
}

void emietsko_state::emietsko_sound_map(address_map &map)
{
	map(0x0000, 0x1fff).rom();
	map(0x8000, 0x83ff).ram();
}

void emietsko_state::emietsko_sound_io_map(address_map &map)
{
	map.global_mask(0xff);
	map(0x10, 0x10).w("ay1", FUNC(ay8910_device::address_w));
	map(0x20, 0x20).rw("ay1", FUNC(ay8910_device::data_r), FUNC(ay8910_device::data_w));
	map(0x40, 0x40).w("ay2", FUNC(ay8910_device::address_w));
	map(0x80, 0x80).rw("ay2", FUNC(ay8910_device::data_r), FUNC(ay8910_device::data_w));
}

static INPUT_PORTS_START( emietsko )
	PORT_START("IN0")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_4WAY PORT_PLAYER(1)
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(1)
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_SERVICE1 )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(1)
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_4WAY PORT_PLAYER(1)
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_4WAY PORT_PLAYER(1)
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_COIN2 )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_COIN1 )

	PORT_START("IN1")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_DIPSWITCH_NAME ) PORT_NAME("DIP Switch 1") PORT_CODE(KEYCODE_F1) PORT_TOGGLE
	PORT_DIPSETTING(    0x01, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(2)
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_START2 )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(2)
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_4WAY PORT_PLAYER(2)
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_4WAY PORT_PLAYER(2)
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_START1 )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_4WAY PORT_PLAYER(1)

	PORT_START("IN2")
	PORT_DIPNAME( 0x01, 0x00, DEF_STR( Cabinet ) )
	PORT_DIPSETTING(    0x00, DEF_STR( Upright ) )
	PORT_DIPSETTING(    0x01, DEF_STR( Cocktail ) )
	PORT_DIPNAME( 0x06, 0x00, DEF_STR( Lives ) )
	PORT_DIPSETTING(    0x00, "3" )
	PORT_DIPSETTING(    0x02, "4" )
	PORT_DIPSETTING(    0x04, "5" )
	PORT_DIPSETTING(    0x06, "255 (Cheat)" )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_4WAY PORT_PLAYER(2)
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_4WAY PORT_PLAYER(2)
INPUT_PORTS_END

void emietsko_state::emietsko(machine_config &config)
{
	/* basic machine hardware */
	Z80(config, m_maincpu, 18432000/6);
	m_maincpu->set_addrmap(AS_PROGRAM, &emietsko_state::emietsko_map);

	Z80(config, "audiocpu", 14318180/8);
	config.device_add<z80_device>("audiocpu", 14318180/8)->set_addrmap(AS_PROGRAM, &emietsko_state::emietsko_sound_map);
	config.device_add<z80_device>("audiocpu", 14318180/8)->set_addrmap(AS_IO, &emietsko_state::emietsko_sound_io_map);

	/* video hardware */
	SCREEN(config, m_screen, SCREEN_TYPE_RASTER);
	m_screen->set_refresh_hz(60.606060);
	m_screen->set_vblank_time(ATTOSECONDS_IN_USEC(2500));
	m_screen->set_size(32*8, 32*8);
	m_screen->set_visarea(0*8, 32*8-1, 2*8, 30*8-1);
	m_screen->set_screen_update(FUNC(emietsko_state::screen_update_galaxian));
	m_screen->set_palette("palette");

	GFXDECODE(config, "gfxdecode", "palette", galaxian_state::gfx_galaxian);
	PALETTE(config, "palette", FUNC(emietsko_state::galaxian_palette), 32);

	/* sound hardware */
	SPEAKER(config, "mono").front_center();
	AY8910(config, "ay1", 14318180/8).add_route(ALL_OUTPUTS, "mono", 0.50);
	AY8910(config, "ay2", 14318180/8).add_route(ALL_OUTPUTS, "mono", 0.50);

	/* devices */
	I8255(config, "ppi8255_0");
	I8255(config, "ppi8255_1");
}

ROM_START( emietsko )
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD( "emietsko.1", 0x0000, 0x1000, CRC(c71c0011) SHA1(1ceaf73df40e531df3bfb26b4fb7cd95fb7bff1d) )
	ROM_LOAD( "emietsko.2", 0x1000, 0x1000, CRC(c71c0011) SHA1(1ceaf73df40e531df3bfb26b4fb7cd95fb7bff1d) )
	ROM_LOAD( "emietsko.3", 0x2000, 0x1000, CRC(c71c0011) SHA1(1ceaf73df40e531df3bfb26b4fb7cd95fb7bff1d) )
	ROM_LOAD( "emietsko.4", 0x3000, 0x1000, CRC(c71c0011) SHA1(1ceaf73df40e531df3bfb26b4fb7cd95fb7bff1d) )

	ROM_REGION( 0x10000, "audiocpu", 0 )
	ROM_LOAD( "emietsko.s1", 0x0000, 0x1000, CRC(c71c0011) SHA1(1ceaf73df40e531df3bfb26b4fb7cd95fb7bff1d) )

	ROM_REGION( 0x1000, "gfx1", 0 )
	ROM_LOAD( "emietsko.g1", 0x0000, 0x0800, CRC(f1e8ba9e) SHA1(605db3fdbaff4ba13729371ad0c4fbab3889378e) )
	ROM_LOAD( "emietsko.g2", 0x0800, 0x0800, CRC(f1e8ba9e) SHA1(605db3fdbaff4ba13729371ad0c4fbab3889378e) )

	ROM_REGION( 0x0020, "proms", 0 )
	ROM_LOAD( "emietsko.clr", 0x0000, 0x0020, CRC(190a55ad) SHA1(de8a847bff8c343d69b853a215e6ee775ef2ef96) )
ROM_END

GAME( 1982, emietsko, 0, emietsko, emietsko, emietsko_state, empty_init, ROT90, "EmiDev", "Emi Etsuko", MACHINE_SUPPORTS_SAVE )
