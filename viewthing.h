//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/viewthing.h                     $
// $Revision:: 20                                                             $
//   $Author:: Jimdose                                                        $
//     $Date:: 10/08/98 12:35a                                                $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/viewthing.h                          $
// 
// 20    10/08/98 12:35a Jimdose
// Added archive functions
// 
// 19    10/04/98 11:11p Jimdose
// Made current_viewthing part of ViewMaster
// 
// 18    9/09/98 5:57p Markd
// added viewautoanimate
// 
// 17    7/10/98 6:20a Jimdose
// Added viewpitch, viewroll, and viewangles events
// 
// 16    4/08/98 12:21a Jimdose
// Added viewdeleteall command
// 
// 15    3/30/98 10:00a Markd
// Added nextskin and prevskin events
// 
// 14    3/27/98 7:00p Markd
// Added new viewthing commands
// 
// 13    3/23/98 1:33p Jimdose
// Revamped event and command system
// 
// 12    3/12/98 9:49a Markd
// Added YAW event
// 
// 11    3/11/98 11:30a Markd
// Added events and variable
// 
// 10    3/07/98 2:05p Markd
// Fixed Viewthing
// 
// 9     3/05/98 6:48p Markd
// 
// 8     3/05/98 11:03a Markd
// Updated for Q2
// 
// 6     10/28/97 6:55p Markd
// made initialorigin a public variable instead of a private one.
// 
// 5     10/27/97 2:59p Jimdose
// Removed dependency on quakedef.h
// 
// 4     10/23/97 6:37p Markd
// Added initialorigin stuff
// 
// 3     10/01/97 6:37p Markd
// Added viewthing commands (ToggleAnimate and ChangeAnimation)
// 
// 2     10/01/97 2:47p Markd
// working on wander AI
// 
// 1     10/01/97 11:24a Markd
// new viewthing actor code
//
// DESCRIPTION:
// Actor code for the viewthing. 
//

#ifndef __VIEWTHING_H__
#define __VIEWTHING_H__

#include "entity.h"

class EXPORT_FROM_DLL ViewMaster : public Listener
	{
	public:
      CLASS_PROTOTYPE( ViewMaster )

      int  current_viewthing;

           ViewMaster();
		void Next( Event *ev );
		void Prev( Event *ev );
		void DeleteAll( Event *ev );
		void Spawn( Event *ev );
		void SetModelEvent( Event *ev );
		void PassEvent( Event *ev );

      virtual void Archive( Archiver &arc );
      virtual void Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void ViewMaster::Archive
	(
	Archiver &arc
	)

   {
   Listener::Archive( arc );

   arc.WriteInteger( current_viewthing );
   }

inline EXPORT_FROM_DLL void ViewMaster::Unarchive
	(
	Archiver &arc
	)

   {
   Listener::Unarchive( arc );

   arc.ReadInteger( &current_viewthing );
   }

extern ViewMaster Viewmodel;

class EXPORT_FROM_DLL Viewthing : public Entity
	{
	public:
      CLASS_PROTOTYPE( Viewthing )

      int      animstate;
      Vector   baseorigin;

							   Viewthing::Viewthing();
		void					Think( Event *ev );
		void					LastFrameEvent( Event *ev );
		void					ToggleAnimateEvent( Event *ev );
		void					SetModelEvent( Event *ev );
		void					NextFrameEvent( Event *ev );
		void					PrevFrameEvent( Event *ev );
		void					NextAnimEvent( Event *ev );
		void					PrevAnimEvent( Event *ev );
		void					ScaleUpEvent( Event *ev );
		void					ScaleDownEvent( Event *ev );
		void					SetScaleEvent( Event *ev );
		void					SetYawEvent( Event *ev );
		void					SetPitchEvent( Event *ev );
		void					SetRollEvent( Event *ev );
		void					SetAnglesEvent( Event *ev );
      void              AttachModel( Event *ev );
      void              Delete( Event *ev );
      void              DetachAll( Event *ev );
      void              BoneGroup( Event *ev );
      void              BoneNum( Event *ev );
      void              ChangeOrigin( Event *ev );
      void              ChangeBoneAngles( Event *ev );
      void              NextSkinEvent( Event *ev );
      void              PrevSkinEvent( Event *ev );
      void              AutoAnimateEvent( Event *ev );

      virtual void      Archive( Archiver &arc );
      virtual void      Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Viewthing::Archive
	(
	Archiver &arc
	)

   {
   Entity::Archive( arc );

   arc.WriteInteger( animstate );
   arc.WriteVector( baseorigin );
   }

inline EXPORT_FROM_DLL void Viewthing::Unarchive
	(
	Archiver &arc
	)

   {
   Entity::Unarchive( arc );

   arc.ReadInteger( &animstate );
   arc.ReadVector( &baseorigin );
   }

#endif /* viewthing.h */
