//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/pulserifle.h                     $
// $Revision:: 14                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 10/09/98 11:56p                                                $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/pulserifle.h                          $
// 
// 14    10/09/98 11:56p Markd
// Added GenericPulseRifle
// 
// 13    9/29/98 11:46p Aldie
// New effects
// 
// 12    9/22/98 12:49p Markd
// Put in archive and unarchive functions
// 
// 11    8/29/98 5:27p Markd
// added specialfx, replaced misc with specialfx where appropriate
// 
// 10    8/18/98 8:13p Aldie
// Added dual mode weapons to base class
// 
// 9     6/17/98 5:42p Aldie
// Made beam do a trace attack
// 
// 8     6/15/98 10:40a Aldie
// New version of pulserifle
// 
// 7     5/13/98 6:22p Markd
// Added Beam pointer
// 
// 6     3/30/98 2:36p Jimdose
// Changed from subclass of Magnum to subclass of BulletWeapon
// 
// 5     3/28/98 8:55p Jimdose
// Created file
// 
// DESCRIPTION:
// Pulse rifle
// 

#ifndef __PULSERIFLE_H__
#define __PULSERIFLE_H__

#include "g_local.h"
#include "item.h"
#include "weapon.h"
#include "bullet.h"
#include "specialfx.h"

class EXPORT_FROM_DLL PulseRifle : public BulletWeapon
	{
      int      beam_modelindex;

	public:
		CLASS_PROTOTYPE( PulseRifle );
		
								PulseRifle();
		virtual void		Shoot( Event *ev );
      void              TraceAttack( Vector start,
                                     Vector end,
                                     int damage,
                                     trace_t *trace,
                                     int numricochets,
                                     int kick,
                                     int dflags );
      void              PulseExplosion(trace_t *trace);
	   virtual void      Archive( Archiver &arc );
      virtual void      Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void PulseRifle::Archive
	(
	Archiver &arc
	)
   {
   BulletWeapon::Archive( arc );

   arc.WriteInteger( beam_modelindex );
   }

inline EXPORT_FROM_DLL void PulseRifle::Unarchive
	(
	Archiver &arc
	)
   {
   BulletWeapon::Unarchive( arc );

   arc.ReadInteger( &beam_modelindex );
   }

class EXPORT_FROM_DLL GenericPulseRifle : public PulseRifle
	{
	public:
		CLASS_PROTOTYPE( GenericPulseRifle );

								GenericPulseRifle();
	};



#endif /* pulserifle.h */
