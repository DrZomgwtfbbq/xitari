/* *****************************************************************************
 * Xitari
 *
 * Copyright 2014 Google Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 * *****************************************************************************
 * A.L.E (Arcade Learning Environment)
 * Copyright (c) 2009-2013 by Yavar Naddaf, Joel Veness, Marc G. Bellemare and 
 *   the Reinforcement Learning and Artificial Intelligence Laboratory
 * Released under the GNU General Public License; see License.txt for details. 
 *
 * Based on: Stella  --  "An Atari 2600 VCS Emulator"
 * Copyright (c) 1995-2007 by Bradford W. Mott and the Stella team
 *
 * *****************************************************************************
 */
#include "Roms.hpp"
#include "RomSettings.hpp"
#include "RomUtils.hpp"
#include "emucore/OSystem.hxx"

// include the game implementations
#include "supported/AirRaid.hpp"
#include "supported/Alien.hpp"
#include "supported/Amidar.hpp"
#include "supported/Assault.hpp"
#include "supported/Asterix.hpp"
#include "supported/Asteroids.hpp"
#include "supported/Atlantis.hpp"
#include "supported/BankHeist.hpp"
#include "supported/BattleZone.hpp"
#include "supported/BeamRider.hpp"
#include "supported/Berzerk.hpp"
#include "supported/Bowling.hpp"
#include "supported/Boxing.hpp"
#include "supported/Breakout.hpp"
#include "supported/Breakout2Player.hpp"
#include "supported/Carnival.hpp"
#include "supported/Centipede.hpp"
#include "supported/ChopperCommand.hpp"
#include "supported/CrazyClimber.hpp"
#include "supported/Defender.hpp"
#include "supported/DemonAttack.hpp"
#include "supported/DoubleDunk.hpp"
#include "supported/ElevatorAction.hpp"
#include "supported/Enduro.hpp"
#include "supported/FishingDerby.hpp"
#include "supported/Freeway.hpp"
#include "supported/Frostbite.hpp"
#include "supported/Gopher.hpp"
#include "supported/Gravitar.hpp"
#include "supported/Hero.hpp"
#include "supported/IceHockey.hpp"
#include "supported/JamesBond.hpp"
#include "supported/JourneyEscape.hpp"
#include "supported/Kangaroo.hpp"
#include "supported/Krull.hpp"
#include "supported/KungFuMaster.hpp"
#include "supported/MontezumaRevenge.hpp"
#include "supported/MsPacman.hpp"
#include "supported/NameThisGame.hpp"
#include "supported/Pacman.hpp"
#include "supported/Phoenix.hpp"
#include "supported/Pitfall.hpp"
#include "supported/Pong.hpp"
#include "supported/Pong2Player.hpp"
#include "supported/Pooyan.hpp"
#include "supported/PrivateEye.hpp"
#include "supported/QBert.hpp"
#include "supported/RiverRaid.hpp"
#include "supported/RoadRunner.hpp"
#include "supported/RoboTank.hpp"
#include "supported/Seaquest.hpp"
#include "supported/Skiing.hpp"
#include "supported/Solaris.hpp"
#include "supported/SpaceInvaders.hpp"
#include "supported/StarGunner.hpp"
#include "supported/Surround.hpp"
#include "supported/Tennis.hpp"
#include "supported/TimePilot.hpp"
#include "supported/Tutankham.hpp"
#include "supported/UpNDown.hpp"
#include "supported/Venture.hpp"
#include "supported/VideoChess.hpp"
#include "supported/VideoPinball.hpp"
#include "supported/WizardOfWor.hpp"
#include "supported/WizardOfWor2Player.hpp"
#include "supported/YarsRevenge.hpp"
#include "supported/Zaxxon.hpp"


using namespace ale;


/* list of supported games */
static const RomSettings *roms[]  = {
    new AirRaidSettings(),
    new AlienSettings(),
    new AmidarSettings(),
    new AssaultSettings(),
    new AsterixSettings(),
    new AsteroidsSettings(),
    new AtlantisSettings(),
    new BankHeistSettings(),
    new BattleZoneSettings(),
    new BeamRiderSettings(),
    new BerzerkSettings(),
    new BowlingSettings(),
    new BoxingSettings(),
    new BreakoutSettings(),
    new Breakout2PlayerSettings(),
    new CarnivalSettings(),
    new CentipedeSettings(),
    new ChopperCommandSettings(),
    new CrazyClimberSettings(),
    new DefenderSettings(),
    new DemonAttackSettings(),
    new DoubleDunkSettings(),
    new ElevatorActionSettings(),
    new EnduroSettings(),
    new FishingDerbySettings(),
    new FreewaySettings(),
    new FrostbiteSettings(),
    new GopherSettings(),
    new GravitarSettings(),
    new HeroSettings(),
    new IceHockeySettings(),
    new JamesBondSettings(),
    new JourneyEscapeSettings(),
    new KangarooSettings(),
    new KrullSettings(),
    new KungFuMasterSettings(),
    new MontezumaRevengeSettings(),
    new MsPacmanSettings(),
    new NameThisGameSettings(),
    new PacmanSettings(),
    new PhoenixSettings(),
    new PitfallSettings(),
    new PongSettings(),
    new Pong2PlayerSettings(),
    new PooyanSettings(),
    new PrivateEyeSettings(),
    new QBertSettings(),
    new RiverRaidSettings(),
    new RoadRunnerSettings(),
    new RoboTankSettings(),
    new SeaquestSettings(),
    new SkiingSettings(),
    new SolarisSettings(),
    new SpaceInvadersSettings(),
    new StarGunnerSettings(),
    new SurroundSettings(),
    new TennisSettings(),
    new TimePilotSettings(),
    new TutankhamSettings(),
    new UpNDownSettings(),
    new VentureSettings(),
    new VideoChessSettings(),
    new VideoPinballSettings(),
    new WizardOfWorSettings(),
    new WizardOfWor2PlayerSettings(),
    new YarsRevengeSettings(),
    new ZaxxonSettings(),
};


/* looks for the RL wrapper corresponding to a particular rom title */
RomSettings *ale::buildRomRLWrapper(const std::string &rom) {

    size_t slash_ind = rom.find_last_of("/\\");
    std::string rom_str = rom.substr(slash_ind + 1);
    size_t dot_idx = rom_str.find_first_of(".");
    rom_str = rom_str.substr(0, dot_idx);

    for (size_t i=0; i < sizeof(roms)/sizeof(roms[0]); i++) {
        if (rom_str == roms[i]->rom()) return roms[i]->clone();
    }

    return NULL;
}

void ale::applyRomSettings(RomSettings * settings, OSystem * osystem) {

    assert(settings != NULL && osystem != NULL);

    if (settings->swapPorts())
        osystem->console().toggleSwapPorts();
}
