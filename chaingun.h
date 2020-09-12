//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/chaingun.h                          $
// $Revision:: 10                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 3/19/99 3:43p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/chaingun.h                               $
// 
// 10    3/19/99 3:43p Aldie
// Changed ammo check for chaingun
// 
// 9     11/18/98 6:12p Jimdose
// fix problems with gravaxis
// 
// 8     9/21/98 4:50p Markd
// Fixed projectile owner
// 
// 7     8/29/98 5:27p Markd
// added specialfx, replaced misc with specialfx where appropriate
// 
// 6     8/18/98 8:12p Aldie
// Added dual mode weapons to base class
// 
// 5     8/06/98 10:53p Aldie
// Added weapon tweaks and kickback.  Also modified blast radius damage and rocket
// jumping.
// 
// 4     6/10/98 2:10p Aldie
// Updated damage function.
// 
// 3     6/09/98 12:54p Aldie
// Added grenade launcher alternate use function
// 
// 2     5/11/98 11:24a Markd
// First time
// 
// 1     5/11/98 11:13a Markd
// 
// 1     5/11/98 9:55a Markd
// 
// DESCRIPTION:
// High Velocity Gun
// 

#ifndef __CHAINGUN_H__
#define __CHAINGUN_H__

#include "g_local.h"
#include "item.h"
#include "weapon.h"
#include "bullet.h"
#include "specialfx.h"

class EXPORT_FROM_DLL Grenade : public Projectile
   {
   public:
      CLASS_PROTOTYPE( Grenade );

      virtual void      Explode( Event *ev );
      virtual void      Grenade_Touch( Event *ev );
      void					Setup( Entity *owner, Vector pos, Vector forward, Vector up, Vector right );

   };

class EXPORT_FROM_DLL ChainGun : public BulletWeapon
	{
	public:
		CLASS_PROTOTYPE( ChainGun );
		
								ChainGun::ChainGun();
		virtual void		Shoot( Event *ev );
      virtual qboolean  HasAmmo( Event *ev );
	};

#endif /* ChainGun.h */
