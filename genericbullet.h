//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/genericbullet.h                  $
// $Revision:: 6                                                              $
//   $Author:: Aldie                                                          $
//     $Date:: 10/23/98 5:09a                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/genericbullet.h                       $
// 
// 6     10/23/98 5:09a Aldie
// Added BeeGun
// 
// 5     10/05/98 11:23p Markd
// Added ReconahGun
// 
// 4     7/22/98 10:41p Aldie
// Fixed tracers
// 
// 3     7/22/98 5:17p Aldie
// Added tracers
// 
// 2     7/08/98 11:23p Markd
// first time
// 
// 1     7/08/98 9:07p Markd
// 
// DESCRIPTION:
// Generic Bullet Weapon.
// 

#ifndef __GENERIC_BULLET_H__
#define __GENERIC_BULLET_H__

#include "g_local.h"
#include "item.h"
#include "weapon.h"
#include "bullet.h"

class EXPORT_FROM_DLL GenericBullet : public BulletWeapon
	{
	public:
		CLASS_PROTOTYPE( GenericBullet );
		
								GenericBullet::GenericBullet();
		virtual void		Shoot( Event *ev );
	};

class EXPORT_FROM_DLL ReconahGun : public GenericBullet
	{
	public:
		CLASS_PROTOTYPE( ReconahGun );
		
		virtual void		Shoot( Event *ev );
	};

class EXPORT_FROM_DLL BeeGun : public GenericBullet
	{
	public:
		CLASS_PROTOTYPE( BeeGun );
		
		virtual void		Shoot( Event *ev );
	};

#endif /* generic bullet.h */
