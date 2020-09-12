//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/stungun.h                        $
// $Revision:: 2                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 10/21/98 1:15a                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/stungun.h                             $
// 
// 2     10/21/98 1:15a Markd
// Added stungun
// 
// 1     10/21/98 12:22a Markd
// 
// DESCRIPTION:
// Stungun weapon
// 

#ifndef __STUNGUN_H__
#define __STUNGUN_H__

#include "g_local.h"
#include "item.h"
#include "weapon.h"
#include "bullet.h"
#include "specialfx.h"

class EXPORT_FROM_DLL Stungun : public BulletWeapon
	{
	public:
		CLASS_PROTOTYPE( Stungun );
		
								Stungun();
		virtual void		Shoot( Event *ev );
      void              TraceAttack( Vector start,
                                     Vector end,
                                     int damage,
                                     trace_t *trace,
                                     int numricochets,
                                     int kick,
                                     int dflags );
	};


#endif /* stungun.h */
