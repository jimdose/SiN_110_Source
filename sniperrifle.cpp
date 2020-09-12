//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/sniperrifle.cpp                  $
// $Revision:: 28                                                             $
//   $Author:: Jimdose                                                        $
//     $Date:: 3/12/99 8:15p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/sniperrifle.cpp                       $
// 
// 28    3/12/99 8:15p Jimdose
// made weapons fire 1/10th of a second sooner on clients
// 
// 27    3/02/99 9:15p Aldie
// Added CTF game code
// 
// 2     2/16/99 4:09p Aldie
// 
// 1     2/11/99 1:39p Aldie
// 
// 26    11/13/98 3:30p Markd
// put in more precaching on weapons
// 
// 25    10/10/98 5:58p Aldie
// More quantumdestab fixes
// 
// 24    8/14/98 6:19p Aldie
// Tweaked damage setting
// 
// 23    8/06/98 10:53p Aldie
// Added weapon tweaks and kickback.  Also modified blast radius damage and
// rocket jumping.
// 
// 22    8/01/98 3:24p Aldie
// Added server effects flag for specific weapons
// 
// 21    7/23/98 6:36p Aldie
// Increase damage
// 
// 20    7/22/98 9:57p Markd
// Defined weapon type
// 
// 19    7/21/98 1:10p Aldie
// Added meansofdeath to obituaries
// 
// 18    7/10/98 12:05a Aldie
// Added autochange support
// 
// 17    6/19/98 9:30p Jimdose
// Moved gun orientation code to Weapon
// 
// 16    6/17/98 10:55a Aldie
// Changed back to regular bulletweapon
// 
// 15    6/15/98 9:10p Aldie
// Added silenced effect
// 
// 14    6/10/98 2:10p Aldie
// Updated damage function.
// 
// 13    4/20/98 1:57p Markd
// SINED decelration is now in def file
// 
// 12    4/18/98 3:13p Markd
// Changed view weapon naming convention
// 
// 11    4/09/98 3:26p Jimdose
// took out sound from shoot since anim plays it
// 
// 10    4/07/98 6:43p Jimdose
// Rewrote weapon code.
// Added order to rank
// 
// 9     4/06/98 7:10p Aldie
// Added zooming for SniperRifle
// 
// 8     4/04/98 6:11p Jimdose
// Made animation control the sequence of becoming ready to fire
// 
// 7     4/02/98 4:20p Jimdose
// Tweaked for DM
// 
// 6     3/30/98 9:55p Jimdose
// Changed location of .def files
// 
// 5     3/30/98 2:37p Jimdose
// Moved firing to BulletWeapon to make more general
// Added Ammo
// Added world models
// 
// 4     3/27/98 11:03p Jimdose
// Added muzzle flash
// 
// 3     3/23/98 1:31p Jimdose
// Revamped event and command system
// 
// 2     3/18/98 2:39p Jimdose
// created file
// 
// DESCRIPTION:
// Sniper rifle
// 

#include "g_local.h"
#include "bullet.h"
#include "sniperrifle.h"
#include "player.h"

CLASS_DECLARATION( BulletWeapon, SniperRifle, "weapon_sniperrifle" );

Event EV_SniperRifle_Ready( "sniperrifle_ready" );

ResponseDef SniperRifle::Responses[] =
	{
	   { &EV_Weapon_SecondaryUse,	( Response )SniperRifle::SecondaryUse },
	   { &EV_SniperRifle_Ready,	( Response )SniperRifle::DoneRaising },
	   { &EV_Weapon_DoneRaising,	( Response )SniperRifle::Open },
	   { &EV_Weapon_Shoot,			( Response )SniperRifle::Shoot },
		{ NULL, NULL }
	};

SniperRifle::SniperRifle()
	{
	SetModels( "sniperrifle.def", "view_srifle.def" );
	SetAmmo( "BulletSniper", 1, 5 );
	modelIndex( "sniper_ammo.def" );
	SetRank( 100, 0 );	
   SetType( WEAPON_2HANDED_HI );
	}

// CTF - Fire upon release of the weapon
void SniperRifle::ReleaseFire
   (
   float holdfiretime
   )

   {
   StopAnimating();
   RandomAnimate( "releasefire", EV_Weapon_DoneFiring );
   last_animation_time = ( level.framenum + 1 ) * FRAMETIME;
   }

void SniperRifle::Shoot
	(
	Event *ev
	)

	{
	assert( owner );
	if ( !owner )
		{
		return;
      }

	if ( ctf->value )
		{
		// CTF - kill the target
		FireBullets( 1, vec_zero, 10000, 10000, DAMAGE_BULLET|DAMAGE_NO_ARMOR, MOD_SNIPER, false );
		}
   else if ( deathmatch->value )
		{
   	FireBullets( 1, vec_zero, 105, 135, DAMAGE_BULLET|DAMAGE_NO_ARMOR, MOD_SNIPER, false );
		}
   else
		{
      FireBullets( 1, vec_zero, 105, 135, DAMAGE_BULLET, MOD_SNIPER, false );
		}
   
	NextAttack( 1.5 );
	}

void SniperRifle::DoneRaising
	(
	Event *ev
	)

	{
	BulletWeapon::DoneRaising( ev );
	}

void SniperRifle::Open
	(
	Event *ev
	)

	{
	RandomAnimate( "open", EV_SniperRifle_Ready );
	}

void SniperRifle::SecondaryUse
   (
   Event *ev
   )
   {
   Entity *ent;
   Event *event;

   event = new Event(EV_Player_ToggleZoomMode);
   ent = ev->GetEntity(1);
   ent->ProcessEvent(event);
   }

void SniperRifle::DoneLowering
   (
   Event *ev
   )
   {
   Event *event;

	assert( owner );
	if ( !owner )
		{
		return;
		}

   event = new Event( EV_Player_ZoomOut );
   owner->ProcessEvent( event );

   Weapon::DoneLowering( ev );
   }

qboolean SniperRifle::AutoChange
   (
   void
   )

   {
   return false;
   }