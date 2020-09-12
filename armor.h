//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/armor.h                          $
// $Revision:: 11                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 7/24/98 5:03p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/armor.h                               $
// 
// 11    7/24/98 5:03p Aldie
// Armor never adds, only replaces
// 
// 10    6/28/98 4:13p Markd
// simplified setup
// 
// 9     6/25/98 8:48p Markd
// Rewrote Item class, added keyed items to triggers, cleaned up item system
// 
// 8     6/24/98 1:38p Aldie
// Implementation of inventory system and picking stuff up
// 
// 7     6/17/98 1:16a Jimdose
// Moved setOwner to Item.  
// Added EV_Item_Pickup
// 
// 6     6/15/98 3:36p Aldie
// Updated armor for maxout values
// 
// 5     6/05/98 2:45p Aldie
// New version of armor
// 
// 3     10/27/97 2:48p Jimdose
// 
// 2     9/26/97 5:30p Jimdose
// Added standard Ritual headers
//
// DESCRIPTION:
// Standard armor that prevents a percentage of damage per hit.
// 

#ifndef __ARMOR_H__
#define __ARMOR_H__

#include "item.h" 

#define MAX_ARMOR 100

class EXPORT_FROM_DLL Armor : public Item
	{
	protected:

		virtual void      Setup( const char *model, int amount );
      virtual void      Add( int amount );
	public:
      CLASS_PROTOTYPE( Armor );
                        Armor( );
      virtual qboolean  Pickupable( Entity *other );
   };

class EXPORT_FROM_DLL RiotHelmet : public Armor
	{
	public:
      CLASS_PROTOTYPE( RiotHelmet );
		RiotHelmet();
	};

class EXPORT_FROM_DLL FlakJacket : public Armor
	{
	public:
      CLASS_PROTOTYPE( FlakJacket );
		FlakJacket();
	};

class EXPORT_FROM_DLL FlakPants : public Armor
	{
	public:
      CLASS_PROTOTYPE( FlakPants );
		FlakPants();
	};

#endif /* armor.h */
