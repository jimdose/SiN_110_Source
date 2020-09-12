//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/rocketlauncher.cpp               $
// $Revision:: 84                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 3/02/99 9:14p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/rocketlauncher.cpp                    $
// 
// 84    3/02/99 9:14p Aldie
// Added CTF game code
// 
// 2     2/16/99 4:09p Aldie
// 
// 1     2/11/99 1:39p Aldie
// 
// 83    11/15/98 12:22a Markd
// Fixed pre-caching issues
// 
// 82    11/13/98 3:30p Markd
// put in more precaching on weapons
// 
// 81    10/26/98 2:50p Aldie
// Fixed a bug with checking of NULL owners
// 
// 80    10/24/98 12:42a Markd
// changed origins to worldorigins where appropriate
// 
// 79    10/23/98 5:38a Jimdose
// Added SpawnBlastDamage
// 
// 78    10/22/98 7:57p Markd
// put in proper pre-caching in all the classes
// 
// 77    10/20/98 8:26p Markd
// Added Attacker to DamageSurface stuff
// 
// 76    10/19/98 12:07a Jimdose
// made all code use fast checks for inheritance (no text lookups when
// possible)
// isSubclassOf no longer requires ::_classinfo()
// 
// 75    10/16/98 10:22p Aldie
// Updated single player damage settings
// 
// 74    10/12/98 8:55p Aldie
// Tweak damage
// 
// 73    10/05/98 10:43p Aldie
// Updated rank
// 
// 72    10/05/98 10:20p Aldie
// Removed flash - changed rank
// 
// 71    10/04/98 10:28p Aldie
// Added multiple weapon changes.  Damage, flashes, quantum stuff
// 
// 70    9/18/98 8:14p Markd
// rewrote surface system so that surfaces are now damaged by surface name
// instead of by surfinfo
// 
// 69    9/01/98 3:05p Markd
// Rewrote explosion code
// 
// 68    8/29/98 5:27p Markd
// added specialfx, replaced misc with specialfx where appropriate
// 
// 67    8/10/98 6:53p Aldie
// Increased the knockback for the rocket direct hit.
// 
// 66    8/06/98 6:58p Jimdose
// Added min/max range, and projectile speed
// 
// 65    8/01/98 3:03p Aldie
// Client side muzzle flash (dynamic light)
// 
// 64    7/25/98 8:00p Aldie
// Spawn explosion offset of origin
// 
// 63    7/25/98 7:19p Aldie
// Client side explosion
// 
// 62    7/23/98 6:17p Aldie
// Updated damage system and fixed some damage related bugs.  Also put tracers
// back to the way they were, and added gib event to funcscriptmodels
// 
// 61    7/23/98 4:39p Markd
// got rid of smoke trail
// 
// 60    7/22/98 9:57p Markd
// Defined weapon type
// 
// 59    7/21/98 1:10p Aldie
// Added meansofdeath to obituaries
// 
// 58    7/01/98 4:38p Aldie
// changed explsion mods
// 
// 57    6/30/98 12:40p Aldie
// New explosion effect
// 
// 56    6/29/98 8:19p Aldie
// Updated effect
// 
// 55    6/19/98 9:30p Jimdose
// Moved gun orientation code to Weapon
// 
// 54    6/11/98 12:40a Markd
// made rocketlauncher use new MuzzlePosition functions
// 
// 53    6/10/98 2:10p Aldie
// Updated damage function.
// 
// 52    5/28/98 1:24p Aldie
// Added particles to rocket explosion
// 
// 51    5/27/98 7:00p Aldie
// Added rocket trails
// 
// 50    5/27/98 4:55p Markd
// spruced it up
// 
// 49    5/27/98 5:33a Markd
// Re-added smoke trails
// 
// 48    5/24/98 1:04a Jimdose
// Made rocket use MASK_PROJECTILE
// 
// 47    5/23/98 10:39p Markd
// fixed it up a bunch, temprorarily commented out smoke trail
// 
// 46    5/06/98 10:17a Markd
// Removed sound precache
// 
// 45    5/05/98 8:37p Aldie
// Fixed oldorigin.
// 
// 44    5/05/98 5:34p Aldie
// Updated damage surfaces.
// 
// 43    5/03/98 8:13p Markd
// Took out TE_BLAster crap
// 
// 42    5/03/98 4:36p Jimdose
// Changed Vector class
// 
// 41    4/28/98 6:24p Jimdose
// upped rocket speed
// 
// 40    4/28/98 5:32p Jimdose
// Changed speed and damage of rocket.  Got rid of unused vars.
// 
// 39    4/20/98 1:56p Markd
// SINED decelration is now in def file
// 
// 38    4/18/98 3:12p Markd
// Changed view weapon naming convention
// 
// 37    4/10/98 1:23a Markd
// Blastmarks are only left if FL_BLASTMARK is flagged
// 
// 36    4/09/98 3:26p Jimdose
// took out randomsound from shoot
// 
// 35    4/07/98 9:18p Jimdose
// Added new ammo
// 
// 34    4/07/98 6:43p Jimdose
// Rewrote weapon code.
// Added order to rank
// 
// 33    4/05/98 5:05a Jimdose
// Fixed null surface bug in rocket Explode
// 
// 32    4/04/98 7:28p Jimdose
// Rockets don't explode against sky anymore
// 
// 31    4/04/98 6:07p Jimdose
// Moved Smoke to misc.cpp
// 
// 30    4/02/98 4:20p Jimdose
// Tweaked for DM
// 
// 29    3/31/98 1:52p Jimdose
// fixed rocket start position
// 
// 28    3/30/98 11:39p Markd
// Added modelIndex stuff
// 
// 27    3/30/98 9:55p Jimdose
// Changed location of .def files
// 
// 26    3/30/98 2:59p Jimdose
// Fixed problem where missiles flew through people
// 
// 25    3/30/98 2:34p Jimdose
// Added ammo
// Changed blast radius
// 
// 24    3/29/98 9:40p Jimdose
// Made rockets use MASK_SHOT
// 
// 23    3/28/98 8:55p Jimdose
// Testing smoke trail
// 
// 22    3/27/98 11:03p Jimdose
// Added muzzle flash
// 
// 21    3/27/98 6:35p Jimdose
// Added new rocket model
// Rocket no longer spawns beyond gun position
// 
// 20    3/26/98 8:17p Jimdose
// Precached sounds
// 
// 19    3/23/98 1:31p Jimdose
// Revamped event and command system
// 
// 18    3/18/98 7:20p Jimdose
// Made work with new animation system
// added model
// 
// 17    3/07/98 2:04p Markd
// Commented out animate
// 
// 16    3/05/98 3:48p Aldie
// Added a small effect when a surface gets damaged.
// 
// 15    3/04/98 8:00p Aldie
// More support for damage surfaces.
// 
// 14    3/02/98 8:49p Jimdose
// Changed the classid parameter of CLASS_DECLARATION to a quoted string so
// that you could have a NULL classid.
// 
// 13    2/19/98 2:35p Jimdose
// Updated to work with Q2 based progs
// 
// 11    12/15/97 4:37p Aldie
// Added support for gunoffset.
// 
// 10    12/15/97 12:47p Markd
// Changed aiming of rocket launcher
// 
// 9     12/14/97 7:43p Markd
// fixed missile angle setting
// 
// 8     12/14/97 7:36p Markd
// Fixed "vanishing point" issues
// 
// 7     12/14/97 5:34p Markd
// Tweaked Rocket
// 
// 6     12/13/97 5:42p Markd
// Added acceleration to rocketlauncher
// 
// 5     12/12/97 2:10p Markd
// Changed RocketLauncher to new rocket launcher
// 
// 4     10/31/97 4:28p Jimdose
// Removed redefinition of owner in base class Weapon, so any reference to
// gunoffset through owner had to use type overriding.
// 
// 3     10/27/97 3:30p Jimdose
// Removed dependency on quakedef.h
// 
// 2     9/26/97 4:46p Jimdose
// Added standard Ritual header
//
// DESCRIPTION:
// Standard rocketlauncher, similar to the Quake and Doom rocketlaunchers.
// 

#include "g_local.h"
#include "explosion.h"
#include "rocketlauncher.h"
#include "worldspawn.h"
#include "specialfx.h"
#include "misc.h"
#include "surface.h"
#include "thrall.h"
#include "ctf.h"

#define ROCKET_SPEED		1000
#define ROCKET_RADIUS	150	// FIXME: max damage (90 +rand(20)) + 40 == 150... hard coded.  gotta pass this in

CLASS_DECLARATION( Projectile, Rocket, NULL );

Event EV_Rocket_Explode( "explode" );

ResponseDef Rocket::Responses[] =
	{
	   { &EV_Touch,				( Response )Rocket::Explode },
	   { &EV_Rocket_Explode,	( Response )Rocket::Explode },
		{ NULL, NULL }
	};

EXPORT_FROM_DLL void Rocket::Explode
	(
	Event *ev
	)

	{
	int	 damg;
	Vector v;
	Entity *other;
   Entity *owner;

	other = ev->GetEntity( 1 );
	assert( other );

	if ( other->isSubclassOf( Teleporter ) )
		{
		return;
		}

	if ( other->entnum == this->owner )
		{
		return;
		}

   stopsound( CHAN_VOICE );

	setSolidType( SOLID_NOT );
	hideModel();
	if ( HitSky() )
		{
		PostEvent( EV_Remove, 0 );
		return;
		}

	damg = 90 + ( int )G_Random( 25 );

   owner = G_GetEntity( this->owner );

   if ( !owner )
      owner = world;

   // Single player packs a bigger punch
   if ( !deathmatch->value && owner->isClient() )
      damg *= 1.5;

   if (other->takedamage)
   	other->Damage( this, owner, damg, worldorigin, velocity, level.impact_trace.plane.normal, 200, 0, MOD_ROCKET, -1, -1, 1.0f );

   SpawnBlastDamage( &level.impact_trace, damg, owner );

	v = velocity;
	v.normalize();
	
	// don't do radius damage to the other, because all the damage
	// was done in the impact
	v = worldorigin - v * 36;
	CreateExplosion( v, damg, 1.0f, true, this, owner, other );
	PostEvent( EV_Remove, 0.1 );
	}

EXPORT_FROM_DLL void Rocket::Setup
	(
	Entity *owner,
	Vector pos,
	Vector dir
	)

	{
	Event *ev;

	this->owner = owner->entnum;
	edict->owner = owner->edict;

	setMoveType( MOVETYPE_FLYMISSILE );
	setSolidType( SOLID_BBOX );
	edict->clipmask = MASK_PROJECTILE;

	angles = dir.toAngles();
	angles[ PITCH ] = - angles[ PITCH ];
	setAngles( angles );

	speed = ROCKET_SPEED;
   velocity = dir * ROCKET_SPEED;

	// set missile duration
	ev = new Event( EV_Remove );
	ev->AddEntity( world );
	PostEvent( ev, 20 );

	takedamage = DAMAGE_YES;
	health = 10;

   setModel( "rocket.def" );
   edict->s.renderfx |= RF_DLIGHT;
   edict->s.effects  |= EF_ROCKET;
   edict->s.effects  |= EF_EVERYFRAME;
   edict->s.angles[ROLL] = rand() % 360;
	avelocity = "0 0 90";
	gravity = 0;
   edict->s.color_r      = 0.8;
   edict->s.color_g      = 0.4;
   edict->s.color_b      = 0;
   edict->s.radius       = 200;

	// setup ambient thrust
	ev = new Event( EV_RandomEntitySound );
	ev->AddString( "thrust" );
   ProcessEvent( ev );

	setSize( "-1 -1 -1", "1 1 1" );
	setOrigin( pos );
   worldorigin.copyTo(edict->s.old_origin);
	}

CLASS_DECLARATION( Weapon, RocketLauncher, "weapon_rocketlauncher" );

ResponseDef RocketLauncher::Responses[] =
	{
	   { &EV_Weapon_Shoot,	( Response )RocketLauncher::Shoot },
		{ NULL, NULL }
	};

RocketLauncher::RocketLauncher()
	{
	SetModels( "rlaunch.def", "view_rlaunch.def" );
	modelIndex( "rocket.def" );
	modelIndex( "rockets.def" );
	modelIndex( "sprites/blastmark.spr" );
   gi.soundindex( "weapons/rlaunch/stmmchn.wav" );
	SetAmmo( "Rockets", 1, 5 );
	SetRank( 70, 70 );
   SetType( WEAPON_2HANDED_LO );

	SetMinRange( ROCKET_RADIUS );
	SetProjectileSpeed( ROCKET_SPEED );

   if ( ctf->value )
		{
		// CTF rocketlauncher has alternate fire mode
		modelIndex( "sprites/thrallpulse.spr" );
		SetSecondaryAmmo( "Rockets", 10, 0);
		dualmode = true;
		alternate_fire = true;
		}
	}

void RocketLauncher::Shoot
	(
	Event *ev
	)

	{
	Rocket	      *rocket;
   ThrallPulse    *pulse;
   Vector	      pos;
	Vector	      dir;

	assert( owner );
	if ( !owner )
		{
		return;
		}

	GetMuzzlePosition( &pos, &dir );
   
   if ( weaponmode == PRIMARY )
      {
   	rocket = new Rocket;
	   rocket->Setup( owner, pos, dir );
	   NextAttack( 1.0 );
      }
   else
      {
      pulse = new ThrallPulse;
	   pulse->Setup( owner, pos, dir );
	   NextAttack( 1.0 );
      SetPrimaryMode();
      }
   }
