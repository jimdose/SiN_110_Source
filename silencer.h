//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/silencer.h                       $
// $Revision:: 5                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 9/21/98 5:01p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/silencer.h                            $
// 
// 5     9/21/98 5:01p Markd
// Took out unused variable
// 
// 4     6/19/98 6:40p Aldie
// More changes for inventory test
// 
// 3     6/18/98 9:29p Aldie
// Used silencer for inventory test
// 
// 2     6/15/98 9:13p Aldie
// First version of silenced weapons
//
// DESCRIPTION:
// Silencer Powerup

#ifndef __SILENCER_H__
#define __SILENCER_H__

#include "inventoryitem.h" 

class EXPORT_FROM_DLL Silencer : public InventoryItem
	{
	public:
      CLASS_PROTOTYPE( Silencer );
                  Silencer();
                  ~Silencer();
      void        PickupSilencer( Event *ev );
   };

#endif /* armor.h */

