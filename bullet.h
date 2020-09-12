//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/bullet.h                         $
// $Revision:: 22                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 2/26/99 5:54p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/bullet.h                              $
// 
// 22    2/26/99 5:54p Markd
// Re-arranged for better sub-classing
// 
// 21    8/06/98 10:53p Aldie
// Added weapon tweaks and kickback.  Also modified blast radius damage and
// rocket jumping.
// 
// 20    8/01/98 3:24p Aldie
// Added server effects flag for specific weapons
// 
// 19    7/22/98 10:41p Aldie
// Fixed tracers
// 
// 18    7/21/98 1:10p Aldie
// Added meansofdeath to obituaries
// 
// 17    6/10/98 2:10p Aldie
// Updated damage function.
// 
// 16    5/05/98 7:38p Markd
// Got rid of RicochetSound from header
// 
// 15    5/02/98 8:44p Markd
// Got rid of RicochetSound, modified TraceAttack
// 
// 14    4/02/98 4:51p Jimdose
// Changed TraceAttack
// 
// 13    3/30/98 2:38p Jimdose
// Moved firing to BulletWeapon to make more general
// Added Ammo
// Added world models
// 
// 12    3/26/98 8:10p Jimdose
// Added constructor
// 
// 11    3/23/98 1:33p Jimdose
// Revamped event and command system
// 
// 10    3/05/98 6:06p Aldie
// Added ricochet sounds.
// 
// 9     3/02/98 8:49p Jimdose
// Changed CLASS_PROTOTYPE to only take the classname
// 
// 8     2/19/98 2:35p Jimdose
// Updated to work with Q2 based progs
// 
// 6     12/11/97 3:31p Markd
// Removed SpawnBlood
// 
// 5     11/18/97 5:27p Markd
// Commented out ShotGun
// 
// 4     10/31/97 7:18p Markd
// Added bloodspray
// 
// 3     10/27/97 2:48p Jimdose
// Removed dependency on quakedef.h
// 
// 2     9/26/97 4:44p Jimdose
// Added standard Ritual header
//
// DESCRIPTION:
// Base class for all bullet (hitscan) weapons.  Includes definition for shotgun.
// 

#ifndef __BULLET_H__
#define __BULLET_H__

#include "g_local.h"
#include "item.h"
#include "weapon.h"

#define MAX_RICOCHETS 10

class EXPORT_FROM_DLL BulletWeapon : public Weapon
	{
	protected:
		virtual void	TraceAttack( Vector start, Vector end, int damage, trace_t *trace, int numricochets, int kick, int dflags, int meansofdeath, qboolean server_effects );
      virtual void   FireTracer( void );

	public:
      CLASS_PROTOTYPE( BulletWeapon );

							BulletWeapon();
		virtual void	FireBullets( int numbullets, Vector spread, int mindamage, int maxdamage, int dflags, int meansofdeath, qboolean server_effects );
	};

#endif /* BULLET.h */
