//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/genericbullet.cpp                $
// $Revision:: 16                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 10/27/98 3:44a                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/genericbullet.cpp                     $
// 
// 16    10/27/98 3:44a Aldie
// Tweak damage
// 
// 15    10/23/98 4:45a Aldie
// Added BeeGun for the Beecadrone
// 
// 14    10/13/98 2:28p Aldie
// Do a tracer on every shot
// 
// 13    10/05/98 11:23p Markd
// Added ReconahGun
// 
// 12    10/04/98 10:22p Markd
// Took out NextAttack delerations
// 
// 11    8/26/98 5:36p Aldie
// Don't need a worldmodel for genbullet.
// 
// 10    8/06/98 10:53p Aldie
// Added weapon tweaks and kickback.  Also modified blast radius damage and
// rocket jumping.
// 
// 9     8/01/98 3:24p Aldie
// Added server effects flag for specific weapons
// 
// 8     7/26/98 3:53p Aldie
// Network tweaking
// 
// 7     7/26/98 3:12a Aldie
// Changed muzzle flash
// 
// 6     7/22/98 10:41p Aldie
// Fixed tracers
// 
// 5     7/22/98 5:16p Aldie
// Added tracers
// 
// 4     7/21/98 1:10p Aldie
// Added meansofdeath to obituaries
// 
// 3     7/17/98 4:40p Aldie
// Changed models to genbullet.def
// 
// 2     7/08/98 11:23p Markd
// first time
// 
// 1     7/08/98 9:07p Markd
//
// DESCRIPTION:
// Generic Bullet Weapon.
// 

#include "g_local.h"
#include "genericbullet.h"

CLASS_DECLARATION( BulletWeapon, GenericBullet, "weapon_genericbullet" );

ResponseDef GenericBullet::Responses[] =
	{
	   { &EV_Weapon_Shoot, ( Response )GenericBullet::Shoot },
		{ NULL, NULL }
	};

GenericBullet::GenericBullet()
	{
   SetModels( NULL, "view_genbullet.def" );
	SetAmmo( "Bullet10mm", 1, 100 );
	}

void GenericBullet::Shoot
	(
	Event *ev
	)

	{
   FireTracer();
   FireBullets( 1, "10 10 10", 2, 3, DAMAGE_BULLET, MOD_GENBULLET, true );
   NextAttack( 0 );
	}

CLASS_DECLARATION( GenericBullet, ReconahGun, "weapon_reconahgun" );

ResponseDef ReconahGun::Responses[] =
	{
	   { &EV_Weapon_Shoot, ( Response )ReconahGun::Shoot },
		{ NULL, NULL }
	};

void ReconahGun::Shoot
	(
	Event *ev
	)

	{
	if ( ( level.framenum % 3 ) == ( entnum % 3 ) )
      {
      FireTracer();
      }

	FireBullets( 1, "10 10 10", 14, 26, DAMAGE_BULLET, MOD_GENBULLET, true );
	}

CLASS_DECLARATION( GenericBullet, BeeGun, "weapon_beegun" );

ResponseDef BeeGun::Responses[] =
	{
	   { &EV_Weapon_Shoot, ( Response )BeeGun::Shoot },
		{ NULL, NULL }
	};

void BeeGun::Shoot
	(
	Event *ev
	)

	{
	FireBullets( 1, "10 10 10", 4, 8, DAMAGE_BULLET, MOD_GENBULLET, true );
	}
