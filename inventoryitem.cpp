//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/inventoryitem.cpp                $
// $Revision:: 7                                                              $
//   $Author:: Aldie                                                          $
//     $Date:: 10/09/98 2:06a                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/inventoryitem.cpp                     $
// 
// 7     10/09/98 2:06a Aldie
// Updated DMFLAGS
// 
// 6     7/19/98 5:40p Markd
// Removed constructor again
// 
// 5     7/19/98 5:38p Markd
// Made constructor process all initcommands
// 
// 4     6/25/98 8:47p Markd
// Added keyed items for Triggers, Rewrote Item class, rewrote every pickup
// method
// 
// 3     6/24/98 1:36p Aldie
// Implementation of inventory system and picking stuff up
// 
// 2     6/19/98 6:38p Aldie
// Inventory item subclass of Item
//
// DESCRIPTION:
// Inventory items

#include "inventoryitem.h"

CLASS_DECLARATION( Item, InventoryItem, NULL );

Event EV_InventoryItem_Use( "useinvitem" );

ResponseDef InventoryItem::Responses[] =
	{
      { &EV_InventoryItem_Use,   (Response)InventoryItem::Use },
      { NULL, NULL }
   };


InventoryItem::InventoryItem
   (
   )

   {
   // All powerups are inventory items
   if ( DM_FLAG( DF_NO_POWERUPS ) )
	   {
	   PostEvent( EV_Remove, 0 );
	   return;
	   }
   }

void InventoryItem::Use
   (
   Event *ev
   )

   {
   }
