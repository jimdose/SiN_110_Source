//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/shotgun.cpp                      $
// $Revision:: 25                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 11/13/98 3:30p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/shotgun.cpp                           $
// 
// 25    11/13/98 3:30p Markd
// put in more precaching on weapons
// 
// 24    10/27/98 3:44a Aldie
// Tweak damage
// 
// 23    10/16/98 10:22p Aldie
// Updated single player damage settings
// 
// 22    10/05/98 10:19p Aldie
// Changed rank
// 
// 21    8/19/98 8:50p Aldie
// Decrease attack time
// 
// 20    8/06/98 10:53p Aldie
// Added weapon tweaks and kickback.  Also modified blast radius damage and
// rocket jumping.
// 
// 19    8/01/98 3:24p Aldie
// Added server effects flag for specific weapons
// 
// 18    8/01/98 3:03p Aldie
// Client side muzzle flash (dynamic light)
// 
// 17    7/22/98 9:57p Markd
// Defined weapon type
// 
// 16    7/22/98 8:40p Aldie
// Tweak damage and spread
// 
// 15    7/21/98 1:10p Aldie
// Added meansofdeath to obituaries
// 
// 14    7/07/98 4:11p Aldie
// Increased damage and spread
// 
// 13    6/19/98 9:30p Jimdose
// Moved gun orientation code to Weapon
// 
// 12    6/10/98 2:10p Aldie
// Updated damage function.
// 
// 11    4/20/98 1:56p Markd
// SINED decelration is now in def file
// 
// 10    4/18/98 3:28p Markd
// Fixed shotgun ammo
// 
// 9     4/18/98 3:13p Markd
// Changed view weapon naming convention
// 
// 8     4/18/98 2:35p Jimdose
// Changed spread and number of bullets on the shotgun
// 
// 7     4/15/98 11:02p Jimdose
// Changed ammo requirement to 1 shell
// 
// 6     4/09/98 3:28p Jimdose
// Removed sound from shoot since anim plays it
// 
// 5     4/07/98 6:43p Jimdose
// Rewrote weapon code.
// Added order to rank
// 
// 4     4/04/98 6:07p Jimdose
// Created file
// 
// DESCRIPTION:
// Shotgun
// 

#include "g_local.h"
#include "bullet.h"
#include "shotgun.h"


CLASS_DECLARATION( BulletWeapon, Shotgun, "weapon_shotgun" );

ResponseDef Shotgun::Responses[] =
	{
	   { &EV_Weapon_Shoot, ( Response )Shotgun::Shoot },
		{ NULL, NULL }
	};

Shotgun::Shotgun()
	{
	SetModels( "shotgun.def", "view_shotgun.def" );
	SetAmmo( "ShotgunClip", 1, 10 );
	SetRank( 30, 30 );
   SetType( WEAPON_2HANDED_HI );
   modelIndex( "shotgunclip.def" );
	}

void Shotgun::Shoot
	(
	Event *ev
	)

	{
	// Non clients use a toned down version of the shotgun
   if ( owner->isClient() )
      FireBullets( 10, "375 375 375", 8, 16, DAMAGE_BULLET, MOD_SHOTGUN, false );	
   else
      FireBullets( 5, "100 100 100", 5, 10, DAMAGE_BULLET, MOD_SHOTGUN, false );	
   
   NextAttack( 0.95f );
	}
