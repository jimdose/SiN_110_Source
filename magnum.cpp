//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/magnum.cpp                       $
// $Revision:: 46                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 11/13/98 3:30p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/magnum.cpp                            $
// 
// 46    11/13/98 3:30p Markd
// put in more precaching on weapons
// 
// 45    10/19/98 12:06a Jimdose
// made all code use fast checks for inheritance (no text lookups when
// possible)
// isSubclassOf no longer requires ::_classinfo()
// Added Drop
// 
// 44    10/05/98 10:38p Aldie
// Fixed rank
// 
// 43    10/05/98 10:18p Aldie
// Covnverted over to new silencer methods
// 
// 42    8/06/98 10:53p Aldie
// Added weapon tweaks and kickback.  Also modified blast radius damage and
// rocket jumping.
// 
// 41    8/01/98 3:24p Aldie
// Added server effects flag for specific weapons
// 
// 40    8/01/98 3:03p Aldie
// Client side muzzle flash (dynamic light)
// 
// 39    7/22/98 9:57p Markd
// Defined weapon type
// 
// 38    7/21/98 1:10p Aldie
// Added meansofdeath to obituaries
// 
// 37    7/20/98 3:53p Aldie
// Fixed the icon
// 
// 36    7/14/98 5:50p Aldie
// Tweaked the magnum
// 
// 35    6/25/98 7:31p Aldie
// Changed the icon
// 
// 34    6/24/98 1:36p Aldie
// Implementation of inventory system and picking stuff up
// 
// 33    6/19/98 9:30p Jimdose
// Moved gun orientation code to Weapon
// 
// 32    6/17/98 10:54a Aldie
// Updated silenced stuff
// 
// 31    6/15/98 9:09p Aldie
// Added SilencedBullet class for silencers
// 
// 30    6/10/98 7:53p Markd
// reduced time till next attack
// 
// 29    6/10/98 2:10p Aldie
// Updated damage function.
// 
// 28    6/10/98 1:19p Markd
// Made magnum use 10mm bullets instead of 357
// 
// 27    6/08/98 8:18p Markd
// set ammo_clip_size
// 
// 26    5/08/98 2:56p Markd
// took out dbshotgn sound
// 
// 25    4/20/98 1:56p Markd
// SINED decelration is now in def file
// 
// 24    4/18/98 3:07p Markd
// Changed view weapon naming convention
// 
// 23    4/16/98 7:46p Aldie
// Updated magnum to 100 bullets temporarily
// 
// 22    4/09/98 3:28p Jimdose
// Removed sound from shoot since anim plays it
// 
// 21    4/07/98 6:43p Jimdose
// Rewrote weapon code.
// Added order to rank
// 
// 20    4/02/98 4:48p Jimdose
// Balanced for DM
// 
// 19    3/30/98 9:55p Jimdose
// Changed location of .def files
// 
// 18    3/30/98 2:33p Jimdose
// Moved firing to BulletWeapon to make more general
// Added Ammo
// Added world models
// 
// 17    3/29/98 9:41p Jimdose
// Reduced the amount of damage bullets do
// 
// 16    3/27/98 11:03p Jimdose
// Added muzzle flash
// 
// 15    3/26/98 8:17p Jimdose
// Precached sounds
// 
// 14    3/23/98 1:31p Jimdose
// Revamped event and command system
// 
// 13    3/18/98 2:39p Jimdose
// Added the new model and made work with the new animation system
// 
// 12    3/05/98 5:44p Aldie
// Removed gunshot temporarily.
// 
// 11    3/02/98 8:49p Jimdose
// Changed the classid parameter of CLASS_DECLARATION to a quoted string so
// that you could have a NULL classid.
// 
// 10    2/19/98 2:35p Jimdose
// Updated to work with Q2 based progs
// 
// 8     12/11/97 7:41p Markd
// moved note processing into setmodel
// 
// 7     12/09/97 7:47p Markd
// Moved some of the init stuff above the initial init call
// 
// 6     11/18/97 5:31p Markd
// Changed Fire to Shoot
// Got rid of some thinking funciotns
// 
// 5     10/31/97 4:28p Jimdose
// Removed redefinition of owner in base class Weapon, so any reference to
// gunoffset through owner had to use type overriding.
// 
// 4     10/30/97 6:55p Jimdose
// Increased the damage for testing
// 
// 3     10/28/97 8:36p Jimdose
// Moved model
// 
// 2     10/24/97 8:13p Jimdose
// Created file.
//
// DESCRIPTION:
// Magnum.
// 

#include "g_local.h"
#include "magnum.h"

CLASS_DECLARATION( BulletWeapon, Magnum, "weapon_magnum" );

ResponseDef Magnum::Responses[] =
	{
	   { &EV_Weapon_Shoot, ( Response )Magnum::Shoot },
		{ NULL, NULL }
	};

Magnum::Magnum()
	{
	SetModels( "magnum.def", "view_magnum.def" );
	SetAmmo( "Bullet10mm", 1, 100 );
	SetRank( 20, 20 );	
   SetType( WEAPON_1HANDED );
   modelIndex( "10mm.def" );
   silenced = true;
	}

void Magnum::Shoot
	(
	Event *ev
	)

	{
	NextAttack( 0.20 );
	FireBullets( 1, "10 10 10", 12, 24, DAMAGE_BULLET, MOD_MAGNUM, false );
	}

qboolean Magnum::Drop
   (
   void
   )

   {
   // Don't leave magnums around
   if ( owner && owner->deadflag && deathmatch->value )
      {
      return false;
      }

   return BulletWeapon::Drop();
   }
