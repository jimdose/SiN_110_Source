//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/assaultrifle.cpp                 $
// $Revision:: 33                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 11/15/98 9:12p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/assaultrifle.cpp                      $
// 
// 33    11/15/98 9:12p Markd
// Put in more precaching for models and sprites
// 
// 32    11/13/98 3:30p Markd
// put in more precaching on weapons
// 
// 31    10/05/98 10:18p Aldie
// Covnverted over to new silencer methods
// 
// 30    8/29/98 5:26p Markd
// added specialfx, replaced misc with specialfx where appropriate
// 
// 29    8/19/98 6:37p Markd
// Moved Assault rifle tracer into def file
// 
// 28    8/06/98 10:53p Aldie
// Added weapon tweaks and kickback.  Also modified blast radius damage and
// rocket jumping.
// 
// 27    8/04/98 11:57a Aldie
// Increased spread
// 
// 26    8/01/98 3:24p Aldie
// Added server effects flag for specific weapons
// 
// 25    8/01/98 3:03p Aldie
// Client side muzzle flash (dynamic light)
// 
// 24    7/26/98 4:06p Aldie
// 
// 23    7/26/98 3:59p Aldie
// Less muzzleflashes
// 
// 22    7/22/98 10:40p Aldie
// Fixed tracers
// 
// 21    7/22/98 9:57p Markd
// Defined weapon type
// 
// 20    7/21/98 1:10p Aldie
// Added meansofdeath to obituaries
// 
// 19    7/12/98 5:48p Jimdose
// changed timing on tracers to once every 5 frames
// 
// 18    7/12/98 5:37p Jimdose
// Recoded the tracer fire based on framenum.  Frametime was being used as if
// it had millisecond precision.
// 
// 17    6/19/98 9:29p Jimdose
// Moved gun orientation code to Weapon
// 
// 16    6/18/98 3:56p Aldie
// Made a tracer for the assaultrifle.
// 
// 15    6/15/98 9:08p Aldie
// Added SilencedBullet class for silencers
// 
// 14    6/10/98 2:10p Aldie
// Updated damage function.
// 
// 13    6/08/98 7:21p Aldie
// Updated attack time
// 
// 12    4/20/98 1:56p Markd
// SINED decelration is now in def file
// 
// 11    4/18/98 3:08p Markd
// Changed view weapon naming convention
// 
// 10    4/09/98 3:29p Jimdose
// Removed sound from shoot since anim plays it
// 
// 9     4/07/98 6:42p Jimdose
// Rewrote weapon code.
// Added order to rank
// 
// 8     4/05/98 2:58a Jimdose
// changed attack time (again)
// 
// 7     4/04/98 6:01p Jimdose
// Changed attack time
// 
// 6     4/02/98 4:20p Jimdose
// Tweaked for DM
// 
// 5     3/30/98 9:54p Jimdose
// Changed location of .def files
// 
// 4     3/30/98 2:34p Jimdose
// Moved firing to BulletWeapon to make more general
// Added Ammo
// Added world models
// 
// 3     3/27/98 11:04p Jimdose
// added muzzle flash
// 
// 2     3/27/98 6:34p Jimdose
// created file
// 
// DESCRIPTION:
// Assault rifle
// 

#include "g_local.h"
#include "assaultrifle.h"

CLASS_DECLARATION( BulletWeapon, AssaultRifle, "weapon_assaultrifle" );

ResponseDef AssaultRifle::Responses[] =
	{
	   { &EV_Weapon_Shoot, ( Response )AssaultRifle::Shoot },
		{ NULL, NULL }
	};

AssaultRifle::AssaultRifle()
	{
	SetModels( "asrifle.def", "view_asrifle.def" );
	SetAmmo( "Bullet10mm", 1, 30 );
	SetRank( 40, 40 );	 
   SetType( WEAPON_2HANDED_LO );
   modelIndex( "10mm.def" );
   modelIndex( "sprites/gunblast.spr" );
   modelIndex( "shell.def" );
   silenced = true;
	}

void AssaultRifle::Shoot
	(
	Event *ev
	)

	{
   FireBullets( 1, "120 120 120", 8, 14, DAMAGE_BULLET, MOD_ASSRIFLE, false );
	NextAttack( 0 );
	}
