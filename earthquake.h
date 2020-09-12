//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/earthquake.h                     $
// $Revision:: 8                                                              $
//   $Author:: Jimdose                                                        $
//     $Date:: 11/08/98 10:47p                                                $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/earthquake.h                          $
// 
// 8     11/08/98 10:47p Jimdose
// moved earthquake to level struct
// 
// 7     9/29/98 5:58p Markd
// put in archive and unarchive
// 
// 6     5/22/98 12:35p Aldie
// Removed some unused functions
// 
// 5     5/20/98 10:22p Aldie
// Converted earthquake to new event system.
// 
// 3     12/06/97 4:49p Markd
// Moved duration to Trigger
// Added interpretCommand
// 
// 2     10/27/97 7:32p Jimdose
// Created file
//
// DESCRIPTION:
// Earthquake trigger causes a localized earthquake when triggered.
// The earthquake effect is visible to the user as the shaking of his screen.
// 

#ifndef __EARTHQUAKE_H__
#define __EARTHQUAKE_H__

#include "g_local.h"
#include "trigger.h"

#define EARTHQUAKE_STRENGTH 100

class EXPORT_FROM_DLL Earthquake : public Trigger
	{
	protected:
		qboolean quakeactive;
      float    duration;

	public:
      CLASS_PROTOTYPE( Earthquake )
		Earthquake();
      void Activate(Event *ev);
      void Deactivate(Event *ev);
      qboolean EarthquakeActive() {return quakeactive;};
	   virtual void      Archive( Archiver &arc );
      virtual void      Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Earthquake::Archive
	(
	Archiver &arc
	)
   {
   Trigger::Archive( arc );

   arc.WriteBoolean( quakeactive );
   arc.WriteFloat( duration );
   }

inline EXPORT_FROM_DLL void Earthquake::Unarchive
	(
	Archiver &arc
	)
   {
   Trigger::Unarchive( arc );

   arc.ReadBoolean( &quakeactive );
   arc.ReadFloat( &duration );
   }

#endif /* Earthquake.h */
