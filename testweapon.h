//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/testweapon.h                     $
// $Revision:: 3                                                              $
//   $Author:: Jimdose                                                        $
//     $Date:: 5/25/98 6:47p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/testweapon.h                          $
// 
// 3     5/25/98 6:47p Jimdose
// Made animateframe, prethink and posthink into functions built into the base
// entity class
// 
// 2     4/14/98 9:58p Jimdose
// Created file
//
// DESCRIPTION:
// Weapon for testing view models
// 

#ifndef __TESTWEAPON_H__
#define __TESTWEAPON_H__

#include "g_local.h"
#include "item.h"
#include "weapon.h"

class EXPORT_FROM_DLL TestWeapon : public Weapon
	{
	public:
		CLASS_PROTOTYPE( TestWeapon );
		
								TestWeapon();
      virtual void		Prethink( void );
      virtual void		Shoot( Event *ev );
      virtual void		Done( Event *ev );
	};

#endif /* testweapon.h */
