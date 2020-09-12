//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/assaultrifle.h                   $
// $Revision:: 7                                                              $
//   $Author:: Aldie                                                          $
//     $Date:: 10/05/98 10:38p                                                $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/assaultrifle.h                        $
// 
// 7     10/05/98 10:38p Aldie
// Converted over to new silencer methods
// 
// 6     7/22/98 10:41p Aldie
// Fixed tracers
// 
// 5     6/18/98 3:57p Aldie
// Made a fire tracer function.
// 
// 4     6/15/98 9:11p Aldie
// Added SilencedBullet calss for silencer
// 
// 3     3/30/98 2:35p Jimdose
// Changed from subclass of Magnum to subclass of BulletWeapon
// 
// 2     3/27/98 6:36p Jimdose
// Created file
// 
// DESCRIPTION:
// Assault rifle
// 

#ifndef __ASSAULTRIFLE_H__
#define __ASSAULTRIFLE_H__

#include "g_local.h"
#include "item.h"
#include "weapon.h"
#include "bullet.h"

class EXPORT_FROM_DLL AssaultRifle : public BulletWeapon
	{
	public:
		CLASS_PROTOTYPE( AssaultRifle );
		
								AssaultRifle::AssaultRifle();
		virtual void		Shoot( Event *ev );
	};

#endif /* assaultrifle.h */
