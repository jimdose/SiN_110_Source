//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/inventoryitem.h                  $
// $Revision:: 5                                                              $
//   $Author:: Aldie                                                          $
//     $Date:: 10/09/98 2:07a                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/inventoryitem.h                       $
// 
// 5     10/09/98 2:07a Aldie
// Updated DMFLAGS
// 
// 4     6/25/98 8:48p Markd
// Rewrote Item class, added keyed items to triggers, cleaned up item system
// 
// 3     6/24/98 1:38p Aldie
// Implementation of inventory system and picking stuff up
// 
// 2     6/19/98 6:38p Aldie
// Inventory item first version
//
// DESCRIPTION:
// Items that are visible in the player's inventory


#ifndef __INVITEM_H__
#define __INVITEM_H__

#include "item.h"

class EXPORT_FROM_DLL InventoryItem : public Item
	{
	public:
      CLASS_PROTOTYPE( InventoryItem );
   
                     InventoryItem();
      virtual void   Use( Event *ev );
	};

extern Event EV_InventoryItem_Use;


#endif /* inventoryitem.h */
