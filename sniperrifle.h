//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/sniperrifle.h                    $
// $Revision:: 11                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 3/02/99 9:16p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/sniperrifle.h                         $
// 
// 11    3/02/99 9:16p Aldie
// Added CTF game code
// 
// 2     2/16/99 4:09p Aldie
// 
// 1     2/11/99 1:39p Aldie
// 
// 10    10/05/98 10:42p Aldie
// Converted over to new silencer methods
// 
// 9     7/10/98 12:06a Aldie
// Autochange support
// 
// 8     6/17/98 10:56a Aldie
// Changed back to regular bullet weapon
// 
// 7     6/15/98 9:13p Aldie
// Updated sniper rifle to have silencer
// 
// 6     4/07/98 6:47p Jimdose
// Rewrote weapon code
// 
// 5     4/06/98 7:10p Aldie
// Added zooming for SniperRifle
// 
// 4     3/30/98 2:36p Jimdose
// Changed from subclass of Magnum to subclass of BulletWeapon
// 
// 3     3/23/98 1:33p Jimdose
// Revamped event and command system
// 
// 2     3/18/98 2:39p Jimdose
// created file
// 
// DESCRIPTION:
// Sniper rifle
// 

#ifndef __SNIPERRIFLE_H__
#define __SNIPERRIFLE_H__

#include "g_local.h"
#include "item.h"
#include "weapon.h"

class EXPORT_FROM_DLL SniperRifle : public BulletWeapon
	{
	public:
		CLASS_PROTOTYPE( SniperRifle );
		
								SniperRifle::SniperRifle();
		virtual void		Shoot( Event *ev );
		virtual void		DoneRaising( Event *ev );
		virtual void		Open( Event *ev );
      virtual void      SecondaryUse(Event *ev);
      virtual void      DoneLowering(Event *ev);
      virtual qboolean  AutoChange( void );
      virtual void      ReleaseFire( float time );
	};

#endif /* sniperrifle.h */
