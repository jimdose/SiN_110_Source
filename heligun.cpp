//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/heligun.cpp                  $
// $Revision:: 11                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 8/06/98 10:53p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/heligun.cpp                              $
// 
// 11    8/06/98 10:53p Aldie
// Added weapon tweaks and kickback.  Also modified blast radius damage and rocket
// jumping.
// 
// 10    8/01/98 3:24p Aldie
// Added server effects flag for specific weapons
// 
// 9     8/01/98 3:03p Aldie
// Client side muzzle flash (dynamic light)
// 
// 8     7/26/98 11:58a Aldie
// Remove tracers
// 
// 7     7/26/98 4:15a Aldie
// Tracers
// 
// 6     7/26/98 12:15a Markd
// removed world model from heli gun
// 
// 5     7/25/98 4:36p Markd
// Doubled bullet damage
// 
// 4     7/21/98 1:10p Aldie
// Added meansofdeath to obituaries
// 
// 3     7/17/98 3:56p Markd
// changed world model 
// 
// 2     7/08/98 11:55p Markd
// first time
// 
// 1     7/08/98 11:33p Markd
// 
// DESCRIPTION:
// Helicopter gun
// 

#include "g_local.h"
#include "bullet.h"
#include "heligun.h"
#include "rocketlauncher.h"
#include "explosion.h"

CLASS_DECLARATION( BulletWeapon, HeliGun, "weapon_heligun" );

ResponseDef HeliGun::Responses[] =
	{
	   { &EV_Weapon_Shoot,           ( Response )HeliGun::Shoot },
		{ NULL, NULL }
	};

HeliGun::HeliGun
   (
   )
	
   {
	SetModels( NULL, "view_heligun.def" );
	SetAmmo( "Bullet50mm", 0, 0 );
	SetRank( 50, 50 );	
	}

void HeliGun::Shoot
	(
	Event *ev
	)

	{
   FireBullets( 1, "20 20 20", 16, 28, DAMAGE_BULLET, MOD_HELIGUN, false );
	NextAttack( 0 );
	}

