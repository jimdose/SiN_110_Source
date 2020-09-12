//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/genericrocket.h                  $
// $Revision:: 3                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 10/04/98 10:26p                                                $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/genericrocket.h                       $
// 
// 3     10/04/98 10:26p Markd
// Made it a subclass of RocketLauncher
// 
// 2     9/15/98 6:47p Aldie
// Generic rocket for pinphat
//
// DESCRIPTION:
// Generic Rocket Launcher - to be used on monsters that have rocket launchers
// shown in their models

#ifndef __GENERIC_ROCKET_H__
#define __GENERIC_ROCKET_H__

#include "g_local.h"
#include "item.h"
#include "weapon.h"
#include "rocketlauncher.h"

class EXPORT_FROM_DLL GenericRocket : public RocketLauncher
	{
	public:
		CLASS_PROTOTYPE( GenericRocket );
		
								GenericRocket::GenericRocket();
		virtual void		Shoot( Event *ev );
	};

#endif /* genericrocket.h */
