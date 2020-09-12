//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/shotrocketlauncher.h             $
// $Revision:: 11                                                             $
//   $Author:: Jimdose                                                        $
//     $Date:: 10/17/98 8:12p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/shotrocketlauncher.h                  $
// 
// 11    10/17/98 8:12p Jimdose
// Changed Damage to DamgeEvent
// 
// 10    9/21/98 5:31p Markd
// took out owner out of projectile subclasses, working on archive and
// unarchive
// 
// 9     9/21/98 4:50p Markd
// Fixed projectile owner
// 
// 8     8/29/98 5:27p Markd
// added specialfx, replaced misc with specialfx where appropriate
// 
// 7     7/26/98 1:49a Aldie
// Heatseekers
// 
// 6     7/23/98 4:39p Markd
// Got rid of smoke trail
// 
// 5     7/23/98 2:32p Aldie
// Made speed of rocket a tweak cvar
// 
// 4     7/17/98 7:52p Aldie
// Changed speed of rocket.
// 
// 3     7/14/98 6:59p Aldie
// Updated rocketspeeds
// 
// 2     7/06/98 4:10p Aldie
// Added header
//
// DESCRIPTION:
// Shootable rockets and a launcher

#ifndef __SHOTROCKETLAUNCHER_H__
#define __SHOTROCKETLAUNCHER_H__

#include "g_local.h"
#include "item.h"
#include "weapon.h"
#include "specialfx.h"

class EXPORT_FROM_DLL ShotRocket : public Projectile
	{
   private:
      float					speed;

	public:
		CLASS_PROTOTYPE( ShotRocket );

      void              DamageEvent( Event *ev );
		void					Explode( Event *ev );
		void					Setup( Entity *owner, Vector pos, Vector dir );
      void              HeatSeek( Event *ev );
      float             Distance( Entity *targ );
      qboolean          CanSee( Entity *ent );
      virtual void      Archive( Archiver &arc );
      virtual void      Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void ShotRocket::Archive
	(
	Archiver &arc
	)
   {
   Projectile::Archive( arc );
   arc.WriteFloat( speed );
   }

inline EXPORT_FROM_DLL void ShotRocket::Unarchive
	(
	Archiver &arc
	)
   {
   Projectile::Unarchive( arc );
   arc.ReadFloat( &speed );
   }

class EXPORT_FROM_DLL ShotRocketLauncher : public Weapon
	{
	public:
		CLASS_PROTOTYPE( ShotRocketLauncher );
		
								ShotRocketLauncher();
      virtual void		Shoot( Event *ev );
	};

#endif // shotrocketlauncher.h