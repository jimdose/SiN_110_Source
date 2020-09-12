//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/chaingun.cpp                 $
// $Revision:: 45                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 3/19/99 3:43p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/chaingun.cpp                             $
// 
// 45    3/19/99 3:43p Aldie
// Changed check for ammo in chaingun
// 
// 44    3/02/99 9:06p Aldie
// Added CTF game code
// 
// 2     2/16/99 4:08p Aldie
// 
// 1     2/11/99 1:38p Aldie
// 
// 43    11/18/98 6:11p Jimdose
// fix problems with gravaxis
// 
// 42    11/15/98 9:12p Markd
// Put in more precaching for models and sprites
// 
// 41    11/13/98 3:30p Markd
// put in more precaching on weapons
// 
// 40    10/27/98 3:43a Aldie
// Tweak damage
// 
// 39    10/26/98 2:50p Aldie
// Fixed a bug with checking of NULL owners
// 
// 38    10/24/98 12:42a Markd
// changed origins to worldorigins where appropriate
// 
// 37    10/23/98 5:38a Jimdose
// Added SpawnBlastDamage
// 
// 36    10/22/98 7:57p Markd
// put in proper pre-caching in all the classes
// 
// 35    10/22/98 5:56p Markd
// Made a bunch of global sounds local to that entity
// 
// 34    10/20/98 8:26p Markd
// Added Attacker to DamageSurface stuff
// 
// 33    10/19/98 12:07a Jimdose
// made all code use fast checks for inheritance (no text lookups when possible)
// isSubclassOf no longer requires ::_classinfo()
// 
// 32    10/16/98 10:22p Aldie
// Updated single player damage settings
// 
// 31    10/16/98 9:49p Aldie
// Added SecondaryAmmo command
// 
// 30    10/10/98 7:40p Aldie
// Added a smoke anim
// 
// 29    10/10/98 7:14p Aldie
// Tweaked damage
// 
// 28    9/27/98 4:19p Aldie
// Increase the damage a little
// 
// 27    9/18/98 8:14p Markd
// rewrote surface system so that surfaces are now damaged by surface name instead
// of by surfinfo
// 
// 26    9/05/98 12:10p Aldie
// Bounce grenades off things with < 0 health
// 
// 25    9/01/98 3:05p Markd
// Rewrote explosion code
// 
// 24    8/29/98 5:27p Markd
// added specialfx, replaced misc with specialfx where appropriate
// 
// 23    8/24/98 6:51p Jimdose
// Added SetGravityAxis
// 
// 22    8/22/98 9:37p Jimdose
// Added support for alternate gravity axis
// 
// 21    8/18/98 11:08p Markd
// Added new Alias System
// 
// 20    8/18/98 8:12p Aldie
// Added dual mode weapons to base class
// 
// 19    8/06/98 10:53p Aldie
// Added weapon tweaks and kickback.  Also modified blast radius damage and rocket
// jumping.
// 
// 18    8/01/98 3:24p Aldie
// Added server effects flag for specific weapons
// 
// 17    8/01/98 3:03p Aldie
// Client side muzzle flash (dynamic light)
// 
// 16    7/25/98 7:19p Aldie
// Client side explosion
// 
// 15    7/25/98 7:10p Markd
// Put in EV_Removes for demo
// 
// 14    7/23/98 6:17p Aldie
// Updated damage system and fixed some damage related bugs.  Also put tracers
// back to the way they were, and added gib event to funcscriptmodels
// 
// 13    7/22/98 9:57p Markd
// Defined weapon type
// 
// 12    7/22/98 5:15p Aldie
// Fixed NextAttack time
// 
// 11    7/21/98 1:10p Aldie
// Added meansofdeath to obituaries
// 
// 10    6/30/98 6:47p Aldie
// Changed damage and explosion effect.
// 
// 9     6/19/98 9:29p Jimdose
// Moved gun orientation code to Weapon
// 
// 8     6/15/98 10:36a Aldie
// Updated the mode setting
// 
// 7     6/10/98 10:03p Aldie
// Updated orientation of shell
// 
// 6     6/10/98 2:10p Aldie
// Updated damage function.
// 
// 5     6/09/98 12:52p Aldie
// Added alternate use - Grenade Launcher
// 
// 4     6/08/98 7:21p Aldie
// Updated attack time
// 
// 3     5/27/98 1:33a Markd
// fixed spawn function name
// 
// 2     5/11/98 11:24a Markd
// First time
// 
// 1     5/11/98 11:13a Markd
// 
// 1     5/11/98 9:55a Markd
// 
// DESCRIPTION:
// High velocity chain gun
// 

#include "g_local.h"
#include "bullet.h"
#include "chaingun.h"
#include "rocketlauncher.h"
#include "explosion.h"
#include "specialfx.h"
#include "misc.h"
#include "surface.h"

#define BULLET_MODE 1


CLASS_DECLARATION( Projectile, Grenade, "grenade" );

Event EV_Grenade_Explode( "grenade_explode" );

ResponseDef Grenade::Responses[] =
	{
	   { &EV_Touch,				( Response )Grenade::Grenade_Touch },
	   { &EV_Grenade_Explode,	( Response )Grenade::Explode },
		{ NULL, NULL }
	};

EXPORT_FROM_DLL void Grenade::Grenade_Touch
	(
	Event *ev
	)

   {
   Entity *other;

   other = ev->GetEntity( 1 );
	assert( other );

   if ( other->entnum == owner )
		return;

   if ( HitSky() )
	   {
	   PostEvent( EV_Remove, 0 );
	   return;
	   }

   if ( !other->takedamage || other->health <= 0 )
		{
		// Play a bouncy sound
		RandomSound( "grenade_bounce", 1 );
		return;
		}

	Explode( ev );
   }

EXPORT_FROM_DLL void Grenade::Explode
	(
	Event *ev
	)

	{
	int			damg;
	Vector		v;
	Entity		*other;
   Entity      *owner;

	other = ev->GetEntity( 1 );
	assert( other );

	if ( other->isSubclassOf( Teleporter ) )
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

   owner = G_GetEntity( this->owner );

   if ( !owner )
      owner = world;

	damg = 75 + ( int )G_Random( 25 );

   if ( !deathmatch->value && owner->isClient() )
      damg *= 1.5;

   if ( other->takedamage )
   	other->Damage( this, owner, damg, worldorigin, velocity, level.impact_trace.plane.normal, 30, 0, MOD_GRENADE, -1, -1, 1.0f );

   SpawnBlastDamage( &level.impact_trace, damg, owner );

	v = velocity;
	v.normalize();
	
	// don't do radius damage to the other, because all the damage
	// was done in the impact
 	v = worldorigin - v * 24;
   CreateExplosion( v, damg, 1.0f, true, this, owner, other );
	PostEvent( EV_Remove, 0.1 );
	}

EXPORT_FROM_DLL void Grenade::Setup
	(
	Entity *owner,
	Vector pos,
   Vector forward,
   Vector right,
   Vector up
	)

	{
	Event *ev;

	setModel( "grenade.def" );
   
   this->owner = owner->entnum;
	edict->owner = owner->edict;
	setMoveType( MOVETYPE_BOUNCE );
	setSolidType( SOLID_BBOX );
	takedamage = DAMAGE_YES;
   edict->clipmask = MASK_PROJECTILE;
	health = 10;
	SetGravityAxis( owner->gravaxis );

   velocity = forward * ( 500 + G_Random( 200 ) );
   velocity += up * ( 200 + crandom() * 10.0 );
   velocity += right * ( crandom() * 10.0 );
   
   avelocity = "575 0 0";
	
   ev = new Event( EV_Grenade_Explode );
	ev->AddEntity( world );

	if ( ctf->value )
		PostEvent( ev, 0.9 );
	else
		PostEvent( ev, 2.5 + G_Random(1.0) );
   
   edict->s.effects  |= EF_ROCKET;
	setOrigin( pos );
   worldorigin.copyTo( edict->s.old_origin );
   setSize( "-4 -4 -4", "4 4 4" );

   edict->s.effects  |= EF_EVERYFRAME;
   RandomAnimate( "smoke", NULL );
	}

CLASS_DECLARATION( BulletWeapon, ChainGun, "weapon_highvelocitygun" );

ResponseDef ChainGun::Responses[] =
	{
	   { &EV_Weapon_Shoot,           ( Response )ChainGun::Shoot },
		{ NULL, NULL }
	};

ChainGun::ChainGun
   (
   )
	
   {
#ifdef SIN_DEMO
   PostEvent( EV_Remove, 0 );
   return;
#endif
	SetModels( "hvgun.def", "view_hvgun.def" );
	SetAmmo( "Bullet50mm", 1, 30 );
   SetSecondaryAmmo( "Rockets", 1, 5);
	SetRank( 50, 50 );	
   SetType( WEAPON_2HANDED_LO );
   dualmode = true;
   modelIndex( "grenade.def" );
   modelIndex( "rocket.def" );
   modelIndex( "rockets.def" );
   modelIndex( "50mm.def" );
   modelIndex( "sprites/blastmark.spr" );
   modelIndex( "sprites/hvblast.spr" );
   modelIndex( "sprites/tracer.spr" );
   modelIndex( "hvshell.def" );

	if ( ctf->value )
	   alternate_fire = true;
	}

void ChainGun::Shoot
	(
	Event *ev
	)

	{
   if ( weaponmode == PRIMARY )
      {
      if ( deathmatch->value )
         FireBullets( 1, "300 300 300", 24, 32, DAMAGE_BULLET, MOD_CHAINGUN, false );
      else
         FireBullets( 1, "300 300 300", 16, 24, DAMAGE_BULLET, MOD_CHAINGUN, false );
	   NextAttack( 0 );
      }
   else
      {
      Grenade *grenade;
      Vector pos;
      Vector forward;
      Vector up;
      Vector right;

		GetMuzzlePosition( &pos, &forward, &up, &right );
	   grenade = new Grenade;
	   grenade->Setup( owner, pos, forward, up, right );
	   NextAttack( 0.8 );
   
		if ( ctf->value )
			SetPrimaryMode();
      }
	}

qboolean ChainGun::HasAmmo
   (
   Event *ev
   )

   {
	if ( !owner )
		{
		return false;
		}
		
   if ( UnlimitedAmmo() )
		{
		return true;
		}

   if ( ( ammo_clip_size && ammo_in_clip >= ammorequired ) || AmmoAvailable() >= ammorequired )
      {
	   return true;
	   }
   else if ( ( ammo_clip_size && ammo_in_clip >= secondary_ammorequired ) || AmmoAvailable() >= secondary_ammorequired )
		{
		return true;
		}

	return false;
   }