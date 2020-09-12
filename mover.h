//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/mover.h                          $
// $Revision:: 10                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 9/28/98 9:12p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/mover.h                               $
// 
// 10    9/28/98 9:12p Markd
// Put in archive and unarchive functions
// 
// 9     4/05/98 2:00a Jimdose
// added moveflags
// 
// 8     3/23/98 1:33p Jimdose
// Revamped event and command system
// 
// 7     3/02/98 8:49p Jimdose
// Changed CLASS_PROTOTYPE to only take the classname
// 
// 6     2/16/98 2:13p Jimdose
// Changed EVENT_MOVER_MOVEDONE to EVENT_MOVEDONE so that physics can delay the
// movedone events
// Removed unused variables
// 
// 5     2/03/98 10:45a Jimdose
// Updated to work with Quake 2 engine
// Made changeover from hackthinker to events
// 
// 3     10/27/97 2:59p Jimdose
// Removed dependency on quakedef.h
// 
// 2     9/26/97 5:23p Jimdose
// Added standard Ritual headers
//
// DESCRIPTION:
// Base class for any object that needs to move to specific locations over a
// period of time.  This class is kept separate from most entities to keep
// class size down for objects that don't need such behavior.
// 

#ifndef __MOVER_H__
#define __MOVER_H__

#include "g_local.h"
#include "entity.h"
#include "trigger.h"

class EXPORT_FROM_DLL Mover : public Trigger
	{
	private:
		Vector				finaldest;
		Vector				angledest;
		Event					endevent;
		int					moveflags;

	public:
		CLASS_PROTOTYPE( Mover );

		void					MoveDone( Event *ev );
		void					MoveTo( Vector tdest, Vector angdest, float tspeed, Event &event );
		void					LinearInterpolate( Vector tdest, Vector angdest, float time, Event &event );
	   virtual void      Archive( Archiver &arc );
      virtual void      Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Mover::Archive
	(
	Archiver &arc
	)
   {
   Trigger::Archive( arc );

   arc.WriteVector( finaldest );
   arc.WriteVector( angledest );
   arc.WriteEvent( endevent );
   arc.WriteInteger( moveflags );
   }

inline EXPORT_FROM_DLL void Mover::Unarchive
	(
	Archiver &arc
	)
   {
   Trigger::Unarchive( arc );

   arc.ReadVector( &finaldest );
   arc.ReadVector( &angledest );
   arc.ReadEvent( &endevent );
   arc.ReadInteger( &moveflags );
   }

#endif
