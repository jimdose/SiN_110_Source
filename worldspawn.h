//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/worldspawn.h                     $
// $Revision:: 21                                                             $
//   $Author:: Jimdose                                                        $
//     $Date:: 10/27/98 5:43a                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/worldspawn.h                          $
// 
// 21    10/27/98 5:43a Jimdose
// World wasn't calling Entity::Archive or Unarchive!
// Added FreeTargetList
// 
// 20    10/25/98 11:53p Jimdose
// added EXPORT_TEMPLATE
// 
// 19    10/10/98 1:34a Jimdose
// moved LoadAndExecScript to g_utils as G_LoadAndExecScript
// 
// 18    9/21/98 4:21p Markd
// Put in archive functions and rewrote all archive routines
// 
// 17    9/20/98 8:57p Jimdose
// Instanciated SafePtr for World.
// 
// 16    9/02/98 7:49p Aldie
// Added support for multiple global scripts
// 
// 15    8/17/98 4:36p Markd
// Added skipthread
// 
// 14    8/08/98 7:52p Jimdose
// changed realWorld to world
// 
// 13    5/26/98 4:20p Markd
// Added TargetList stuff
// 
// 12    5/04/98 8:32p Markd
// Removed Setlightstyle stuff
// 
// 11    5/04/98 12:28p Markd
// Moved lightstyles to global.scr
// 
// 10    5/01/98 5:06p Jimdose
// Moved definition of world * to g_local.h so that it can be used more
// generally
// 
// 9     3/23/98 1:33p Jimdose
// Revamped event and command system
// 
// 8     3/02/98 8:49p Jimdose
// Changed CLASS_PROTOTYPE to only take the classname
// 
// 7     2/06/98 5:48p Jimdose
// Moved sined header to .cpp file.
// Prepended "maps/" to script file name
// 
// 6     2/03/98 10:56a Jimdose
// Updated to work with Quake 2 engine
// Moved initialization to constructor and removed Init function
// Removed precache stuff (it was all out of date anyway).
// 
// 4     11/10/97 8:38p Jimdose
// Removed getMapTitle.  Map name is now stored in netname.
// Made StartFrame get called indirectly through EVENT_PRETHINK.
// Added event function.
// 
// 3     10/27/97 2:59p Jimdose
// Removed dependency on quakedef.h
// 
// 2     9/26/97 6:14p Jimdose
// Added standard Ritual headers
//
// DESCRIPTION:
// Base class for worldspawn objects.  This should be subclassed whenever
// a DLL has new game behaviour that needs to be initialized before any other
// entities are created, or before any entity thinks each frame.  Also controls
// spawning of clients.
//

#ifndef __WORLDSPAWN_H__
#define __WORLDSPAWN_H__

#include "entity.h"

#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL Container<Entity *>;
#endif

class EXPORT_FROM_DLL TargetList : public Class
	{
   public:
      CLASS_PROTOTYPE( TargetList );
      Container<Entity *>  list;
      str                  targetname;

		TargetList();
      TargetList( str &tname );
		~TargetList();
      void     AddEntity( Entity * ent );
      void     RemoveEntity( Entity * ent );
      Entity   *GetNextEntity( Entity * ent );
	};

#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL Container<TargetList *>;
#endif

class EXPORT_FROM_DLL World : public Entity
	{
   private:
      Container<TargetList *> targetList;
	public:
      CLASS_PROTOTYPE( World );

		World();
		~World();

      str                     skipthread;

      void        FreeTargetList( void );
      TargetList  *GetTargetList( str &targetname );
      void        AddTargetEntity( str &targetname, Entity * ent );
      void        RemoveTargetEntity( str &targetname, Entity * ent );
      Entity      *GetNextEntity( str &targetname, Entity * ent );

      virtual void Archive( Archiver &arc );
      virtual void Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void World::Archive
	(
	Archiver &arc
	)

	{
   Entity::Archive( arc );

   arc.WriteString( skipthread );
	}

inline EXPORT_FROM_DLL void World::Unarchive
	(
	Archiver &arc
	)

	{
   FreeTargetList();

   Entity::Unarchive( arc );

   skipthread = arc.ReadString();
	}

#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL SafePtr<World>;
#endif

typedef SafePtr<World> WorldPtr;
extern WorldPtr world;

#endif /* worldspawn.h */
