//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/rocket_turret.h                  $
// $Revision:: 5                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 9/22/98 12:49p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/rocket_turret.h                       $
// 
// 5     9/22/98 12:49p Markd
// Put in archive and unarchive functions
// 
// 4     7/24/98 10:05p Aldie
// Speed and rocket rate
// 
// 3     7/10/98 3:08p Aldie
// Simple prediction for rocket firing
// 
// 2     7/07/98 4:12p Aldie
// Updated to new class hierarchy
//
// DESCRIPTION:
// Rocket based turret

#ifndef __ROCKET_TURRET_H__
#define __ROCKET_TURRET_H__

#include "turret.h"

class EXPORT_FROM_DLL RocketTurret : public Turret
	{
   protected:
      Vector   new_orientation;
      Vector   enemy_oldorigin;

	public:
      CLASS_PROTOTYPE( RocketTurret );

      float          speed;
      float          rate;

                     RocketTurret();   
      virtual void   Seek(	Event *ev );
      virtual void   Turn( Event *ev );
      virtual void   SetSpeed( Event *ev );
      virtual void   SetRate( Event *ev );
	   virtual void   Archive( Archiver &arc );
      virtual void   Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void RocketTurret::Archive
	(
	Archiver &arc
	)
   {
   Turret::Archive( arc );

   arc.WriteVector( new_orientation );
   arc.WriteVector( enemy_oldorigin );
   arc.WriteFloat( speed );
   arc.WriteFloat( rate );
   }

inline EXPORT_FROM_DLL void RocketTurret::Unarchive
	(
	Archiver &arc
	)
   {
   Turret::Unarchive( arc );

   arc.ReadVector( &new_orientation );
   arc.ReadVector( &enemy_oldorigin );
   arc.ReadFloat( &speed );
   arc.ReadFloat( &rate );
   }


#endif // rocket_turret