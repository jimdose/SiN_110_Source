//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/rocketlauncher.h                 $
// $Revision:: 20                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 9/22/98 12:49p                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/rocketlauncher.h                      $
// 
// 20    9/22/98 12:49p Markd
// Put in archive and unarchive functions
// 
// 19    9/21/98 4:50p Markd
// Fixed projectile owner
// 
// 18    8/29/98 5:27p Markd
// added specialfx, replaced misc with specialfx where appropriate
// 
// 17    7/23/98 4:39p Markd
// Got rid of smoke trail
// 
// 16    4/28/98 5:33p Jimdose
// Got rid of unused vars.
// 
// 15    4/04/98 6:12p Jimdose
// Changed Rocket into a projectile
// 
// 14    3/30/98 2:36p Jimdose
// Changed from subclass of Magnum to subclass of BulletWeapon
// 
// 13    3/28/98 8:55p Jimdose
// Testing smoke trail
// 
// 12    3/23/98 1:33p Jimdose
// Revamped event and command system
// 
// 11    3/18/98 7:20p Jimdose
// Made work with new animation system
// added model
// 
// 10    3/02/98 8:49p Jimdose
// Changed CLASS_PROTOTYPE to only take the classname
// 
// 9     2/19/98 2:35p Jimdose
// Updated to work with Q2 based progs
// 
// 7     12/15/97 12:48p Markd
// added flydir
// 
// 6     12/14/97 5:34p Markd
// Tweaked Rocket
// 
// 5     12/13/97 5:42p Markd
// Added acceleration to RocketLauncher
// 
// 4     12/12/97 2:11p Markd
// Changed Rocket Launcher to new type
// 
// 3     10/27/97 2:59p Jimdose
// Removed dependency on quakedef.h
// 
// 2     9/26/97 4:46p Jimdose
// Added standard Ritual header
//
// DESCRIPTION:
// Standard rocketlauncher, similar to the Quake and Doom rocketlaunchers.
// 

#ifndef __ROCKETLAUNCHER_H__
#define __ROCKETLAUNCHER_H__

#include "g_local.h"
#include "item.h"
#include "weapon.h"
#include "specialfx.h"

class EXPORT_FROM_DLL Rocket : public Projectile
	{
   private:
      float					speed;

	public:
		CLASS_PROTOTYPE( Rocket );

		void					Explode( Event *ev );
		void					Setup( Entity *owner, Vector pos, Vector dir );
	   virtual void      Archive( Archiver &arc );
      virtual void      Unarchive( Archiver &arc );
};


inline EXPORT_FROM_DLL void Rocket::Archive
	(
	Archiver &arc
	)
   {
   Projectile::Archive( arc );

   arc.WriteFloat( speed );
   }

inline EXPORT_FROM_DLL void Rocket::Unarchive
	(
	Archiver &arc
	)
   {
   Projectile::Unarchive( arc );

   arc.ReadFloat( &speed );
   }


class EXPORT_FROM_DLL RocketLauncher : public Weapon
	{
	public:
		CLASS_PROTOTYPE( RocketLauncher );
		
								RocketLauncher();
      virtual void		Shoot( Event *ev );
	};

#endif /* rocketlauncher.h */
