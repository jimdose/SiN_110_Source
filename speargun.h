//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/speargun.h                       $
// $Revision:: 8                                                              $
//   $Author:: Aldie                                                          $
//     $Date:: 10/06/98 10:52p                                                $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/speargun.h                            $
// 
// 8     10/06/98 10:52p Aldie
// Moved bubble trail to client
// 
// 7     9/21/98 4:50p Markd
// Fixed projectile owner
// 
// 6     8/29/98 5:27p Markd
// added specialfx, replaced misc with specialfx where appropriate
// 
// 5     4/04/98 6:12p Jimdose
// Created file
// 
// DESCRIPTION:
// Fires a spear.  Used by Seabonites.
// 

#ifndef __SPEARGUN_H__
#define __SPEARGUN_H__

#include "g_local.h"
#include "item.h"
#include "weapon.h"
#include "specialfx.h"

class EXPORT_FROM_DLL Spear : public Projectile
	{
	public:
		CLASS_PROTOTYPE( Spear );

		void					Hit( Event *ev );
		void					Setup( Entity *owner, Vector pos, Vector dir );
	};


class EXPORT_FROM_DLL SpearGun : public Weapon
	{
	public:
		CLASS_PROTOTYPE( SpearGun );
		
								SpearGun ();
      virtual void		Shoot( Event *ev );
	};

#endif /* speargun.h */
