//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/ammo.h                           $
// $Revision:: 19                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 10/24/98 2:09p                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/ammo.h                                $
// 
// 19    10/24/98 2:09p Aldie
// Moved pickupable out of ammo
// 
// 18    10/21/98 10:39p Aldie
// Added spears
// 
// 17    10/21/98 5:29p Aldie
// Added a pickupable function to ammo which restricts mutants
// 
// 16    6/28/98 4:13p Markd
// simplified setup
// 
// 15    6/25/98 8:48p Markd
// Rewrote Item class, added keyed items to triggers, cleaned up item system
// 
// 14    6/24/98 1:38p Aldie
// Implementation of inventory system and picking stuff up
// 
// 13    6/17/98 1:16a Jimdose
// Moved setOwner to Item.  
// Added EV_Item_Pickup
// 
// 12    6/10/98 1:18p Markd
// Added SetAmmoAmount and SetAmmoName, also removed 357 bullets
// 
// 11    6/08/98 7:22p Aldie
// Added spidermines
// 
// 10    5/26/98 4:44p Aldie
// Added remove ammo
// 
// 9     5/24/98 4:48p Jimdose
// Made char *'s const
// 
// 8     5/08/98 2:57p Markd
// Added pickup sound
// 
// 7     4/18/98 3:29p Markd
// Added new shotgunclip ammo
// 
// 6     4/07/98 9:19p Jimdose
// Added rockets
// 
// 5     3/30/98 2:31p Jimdose
// Created file
// 
// DESCRIPTION:
// Base class for all ammunition for entities derived from the Weapon class.
// 

#ifndef __AMMO_H__
#define __AMMO_H__

#include "g_local.h"
#include "item.h"
#include "sentient.h"
#include "item.h"

class EXPORT_FROM_DLL Ammo : public Item
	{
	protected:
      virtual void		Setup( const char *model );

	public:
      CLASS_PROTOTYPE( Ammo );

								Ammo();
	};

class EXPORT_FROM_DLL Bullet10mm : public Ammo
	{
	public:
      CLASS_PROTOTYPE( Bullet10mm );

		Bullet10mm();
	};

class EXPORT_FROM_DLL Bullet50mm : public Ammo
	{
	public:
      CLASS_PROTOTYPE( Bullet50mm );

		Bullet50mm();
	};

class EXPORT_FROM_DLL BulletPulse : public Ammo
	{
	public:
      CLASS_PROTOTYPE( BulletPulse );

		BulletPulse();
	};

class EXPORT_FROM_DLL BulletSniper : public Ammo
	{
	public:
      CLASS_PROTOTYPE( BulletSniper );

		BulletSniper();
	};

class EXPORT_FROM_DLL Rockets : public Ammo
	{
	public:
      CLASS_PROTOTYPE( Rockets );

		Rockets();
	};

class EXPORT_FROM_DLL Spears : public Ammo
	{
	public:
      CLASS_PROTOTYPE( Spears );

		Spears();
	};

class EXPORT_FROM_DLL ShotgunClip : public Ammo
	{
	public:
      CLASS_PROTOTYPE( ShotgunClip );

		ShotgunClip();
	};

class EXPORT_FROM_DLL SpiderMines : public Ammo
	{
	public:
      CLASS_PROTOTYPE( SpiderMines );

		SpiderMines();
	};

#endif /* ammo.h */
