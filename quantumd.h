//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/quantumd.h                       $
// $Revision:: 17                                                             $
//   $Author:: Jimdose                                                        $
//     $Date:: 11/08/98 10:54p                                                $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/quantumd.h                            $
// 
// 17    11/08/98 10:54p Jimdose
// trapped_sent wasn't being archived
// 
// 16    10/16/98 9:50p Aldie
// Added second attack
// 
// 15    10/10/98 5:58p Aldie
// More quantumdestab fixes
// 
// 14    10/05/98 10:42p Aldie
// Fixed dropping bug
// 
// 13    10/04/98 10:28p Aldie
// Added multiple weapon changes.  Damage, flashes, quantum stuff
// 
// 12    9/23/98 10:08p Aldie
// Added self destruct mechanism
// 
// 11    9/22/98 12:49p Markd
// Put in archive and unarchive functions
// 
// 10    9/21/98 1:54a Aldie
// Made quantum eat ammo
// 
// 9     9/16/98 8:58p Aldie
// Added ability to do a hold down weapon charge
// 
// 8     9/11/98 3:54p Aldie
// Put in release fire
// 
// 7     8/18/98 8:13p Aldie
// Added dual mode weapons to base class
// 
// 6     8/18/98 7:39p Aldie
// Added dual weapon modes to base class
// 
// 5     8/06/98 10:53p Aldie
// Added weapon tweaks and kickback.  Also modified blast radius damage and
// rocket jumping.
// 
// 4     7/29/98 5:56p Aldie
// Added header
//
// DESCRIPTION:
// Quantum Destabilizer

#ifndef __QUANTUMD_H__
#define __QUANTUMD_H__

#include "g_local.h"
#include "item.h"
#include "weapon.h"
#include "bullet.h"

class EXPORT_FROM_DLL QuantumDestabilizer : public BulletWeapon
	{
   private:
      float             power;
      SentientPtr       trapped_sent;

	public:
		CLASS_PROTOTYPE( QuantumDestabilizer );
		
								QuantumDestabilizer();
		virtual void		Shoot( Event *ev );
      virtual void		ReleaseFire( float holdfiretime );
      void              EatAmmo( Event *ev );
      void              Destruct( Event *ev );
      void              StartSelfDestruct( Event *ev );
      void              SuckSentient( Vector pos, Vector org );
      qboolean          ShootSentient( Vector pos, Vector dir );
      void              SentientOverload( Event *ev );
      void              TraceAttack( Vector start,
                                     Vector end,
                                     int damage,
                                     trace_t	*trace,
                                     int numricochets,
                                     int kick,
                                     int dflags );
      virtual qboolean  Drop( void );
	   virtual void      Archive( Archiver &arc );
      virtual void      Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void QuantumDestabilizer::Archive
	(
	Archiver &arc
	)
   {
   BulletWeapon::Archive( arc );

   arc.WriteFloat( power );
   arc.WriteSafePointer( trapped_sent );
   }

inline EXPORT_FROM_DLL void QuantumDestabilizer::Unarchive
	(
	Archiver &arc
	)
   {
   BulletWeapon::Unarchive( arc );

   arc.ReadFloat( &power );
   arc.ReadSafePointer( &trapped_sent );
   }

#endif /* quantumd.h */
