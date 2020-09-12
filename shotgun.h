//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/shotgun.h                        $
// $Revision:: 4                                                              $
//   $Author:: Jimdose                                                        $
//     $Date:: 4/04/98 6:12p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/shotgun.h                             $
// 
// 4     4/04/98 6:12p Jimdose
// Created file
// 
// DESCRIPTION:
// Shotgun
// 

#ifndef __SHOTGUN_H__
#define __SHOTGUN_H__

#include "g_local.h"
#include "item.h"
#include "weapon.h"
#include "bullet.h"

class EXPORT_FROM_DLL Shotgun : public BulletWeapon
	{
	public:
		CLASS_PROTOTYPE( Shotgun );
		
								Shotgun();
		virtual void		Shoot( Event *ev );
	};

#endif /* shotgun.h */
