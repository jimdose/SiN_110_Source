//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/health.h                         $
// $Revision:: 6                                                              $
//   $Author:: Aldie                                                          $
//     $Date:: 10/27/98 5:18p                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/health.h                              $
// 
// 6     10/27/98 5:18p Aldie
// Added a few items for health
// 
// 5     8/27/98 2:32p Aldie
// Changed health adrenaline to megahealth
// 
// 4     7/14/98 6:59p Aldie
// Updated healths
// 
// 3     6/25/98 8:48p Markd
// Rewrote Item class, added keyed items to triggers, cleaned up item system
// 
// 2     3/30/98 2:30p Jimdose
// Created file
// 
// 1     3/30/98 1:47a Jimdose
// 
// DESCRIPTION:
// Health powerup
// 

#ifndef __HEALTH_H__
#define __HEALTH_H__

#include "g_local.h"
#include "item.h"
#include "sentient.h"
#include "item.h"

class EXPORT_FROM_DLL Health : public Item
	{
	public:
      CLASS_PROTOTYPE( Health );

								Health();
		virtual void		PickupHealth( Event *ev );
	};

class EXPORT_FROM_DLL SmallHealth : public Health
	{
	public:
      CLASS_PROTOTYPE( SmallHealth );
								SmallHealth();
	};

class EXPORT_FROM_DLL LargeHealth : public Health
	{
	public:
      CLASS_PROTOTYPE( LargeHealth );
								LargeHealth();
	};

class EXPORT_FROM_DLL MegaHealth : public Health
	{
	public:
      CLASS_PROTOTYPE( MegaHealth );
								MegaHealth();
	};

class EXPORT_FROM_DLL Apple : public Health
	{
	public:
      CLASS_PROTOTYPE( Apple );
								Apple();
	};

class EXPORT_FROM_DLL Banana : public Health
	{
	public:
      CLASS_PROTOTYPE( Banana );
								Banana();
	};

class EXPORT_FROM_DLL Sandwich : public Health
	{
	public:
      CLASS_PROTOTYPE( Sandwich );
								Sandwich();
	};

class EXPORT_FROM_DLL Soda : public Health
	{
	public:
      CLASS_PROTOTYPE( Soda );
								Soda();
	};

#endif /* health.h */
