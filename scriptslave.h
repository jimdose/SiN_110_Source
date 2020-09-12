//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/scriptslave.h                    $
// $Revision:: 32                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 10/28/98 8:37p                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/scriptslave.h                         $
// 
// 32    10/28/98 8:37p Markd
// Added notshootable functionality
// 
// 31    10/27/98 9:16p Jimdose
// overrode bind and unbind events
// 
// 30    10/24/98 2:09p Aldie
// Added func_volumetric
// 
// 29    10/23/98 10:04p Markd
// Added explode event
// 
// 28    9/23/98 11:00p Markd
// put in some garbage collection on stuff that wasn't freed up
// 
// 27    9/21/98 10:15p Markd
// Putting archiving and unarchiving functions in
// 
// 26    9/21/98 6:05p Markd
// added archive and unarchive functions
// 
// 25    8/21/98 3:48p Markd
// Added new rotate commands
// 
// 24    8/21/98 1:46a Markd
// Added RotateUpTo, RotateDownTo and RotateTo
// 
// 23    7/23/98 6:17p Aldie
// Updated damage system and fixed some damage related bugs.  Also put tracers
// back to the way they were, and added gib event to funcscriptmodels
// 
// 22    7/22/98 3:48p Jimdose
// Changed damage to an event function.  Fixed the slaves not responding to
// damage
// 
// 21    7/11/98 6:32p Markd
// removed valid orientation, simplified code
// 
// 20    7/10/98 1:13p Markd
// Added more functionality to spline based movement
// 
// 19    7/08/98 12:42p Markd
// Added spline based following of paths
// 
// 18    6/18/98 8:49p Jimdose
// Changed all thread variables to ThreadPtrs
// 
// 17    6/11/98 11:53a Aldie
// Updated the damage parms for scriptslave::damage
// 
// 16    5/24/98 8:46p Jimdose
// Made a lot of functions more str-friendly.
// Got rid of a lot of char * based strings
// Cleaned up get spawn arg functions and sound functions
// sound functions now use consistant syntax
// 
// 15    4/29/98 6:29p Jimdose
// Added ScriptOrigin
// 
// 14    4/07/98 8:01p Markd
// Added ScriptModel constructor
// 
// 13    4/06/98 3:55p Jimdose
// Since RF_FRAMELERP is now cleared out every frame, ClearLerp was redundant
// 
// 12    4/05/98 2:00a Jimdose
// added ClearLerp and ScriptModel
// 
// 11    3/24/98 5:03p Jimdose
// Added NewOrders
// 
// 10    3/23/98 1:33p Jimdose
// Revamped event and command system
// 
// 9     3/02/98 8:49p Jimdose
// Changed CLASS_PROTOTYPE to only take the classname
// 
// 8     2/18/98 8:12p Jimdose
// Changed pointers to scriptMaster to entity numbers
// Changed direct calls to the master into events
// 
// 7     2/17/98 7:03p Jimdose
// no longer pass script into interpretCommand
// 
// 6     2/03/98 10:44a Jimdose
// Updated to work with Quake 2 engine
// 
// 4     10/28/97 4:14p Jimdose
// Removed CommandsWaiting
// 
// 3     10/27/97 2:59p Jimdose
// Removed dependency on quakedef.h
// 
// 2     9/26/97 5:23p Jimdose
// Added standard Ritual headers
//
// DESCRIPTION:
// Standard scripted objects.  Controlled by scriptmaster.  These objects
// are bmodel objects created in the editor and controlled by an external
// text based script.  Commands are interpretted on by one and executed
// upon a signal from the script master.  The base script object can
// perform several different relative and specific rotations and translations
// and can cause other parts of the script to be executed when touched, damaged,
// touched, or used.
// 

#ifndef __SCRIPTSLAVE_H__
#define __SCRIPTSLAVE_H__

#include "g_local.h"
#include "entity.h"
#include "trigger.h"
#include "mover.h"
#include "script.h"
#include "scriptmaster.h"
#include "misc.h"
#include "bspline.h"

class EXPORT_FROM_DLL ScriptSlave : public Mover
	{
	protected:
		ThreadPtr			touchthread;
		ThreadPtr			blockthread;
		ThreadPtr			triggerthread;
		ThreadPtr			usethread;
		ThreadPtr			damagethread;
		ThreadPtr			movethread;

		str					touchlabel;
		str					uselabel;
		str					blocklabel;
		str					triggerlabel;
		str					damagelabel;
		
		float					attack_finished;
		int					dmg;

	public:
		qboolean				commandswaiting;
		Vector				TotalRotation;
		Vector				NewAngles;
		Vector				NewPos;
		Vector				ForwardDir;
		float					speed;
		Waypoint				*waypoint;
		float					traveltime;
		BSpline				*splinePath;
      float             splineTime;
      qboolean          splineangles;
      qboolean          ignoreangles;

      CLASS_PROTOTYPE( ScriptSlave );

								ScriptSlave();
								~ScriptSlave();

		void					NewOrders( Event *ev );
		void					BindEvent( Event *ev );
		void					EventUnbind( Event *ev );
		void					DoMove( Event *ev );
		void					MoveEnd( Event *ev );
		void					SetAnglesEvent( Event *ev );
		void					TriggerEvent( Event *ev );
		void					GotoNextWaypoint( Event *ev );
		void					JumpTo( Event *ev );
		void					MoveToEvent( Event *ev );
		void					SetSpeed( Event *ev );
		void					SetTime( Event *ev );
		void					MoveUp( Event *ev );
		void					MoveDown( Event *ev );
		void					MoveNorth( Event *ev );
		void					MoveSouth( Event *ev );
		void					MoveEast( Event *ev );
		void					MoveWest( Event *ev );
		void					MoveForward( Event *ev );
		void					MoveBackward( Event *ev );
		void					MoveLeft( Event *ev );
		void					MoveRight( Event *ev );
		void					RotateXdownto( Event *ev );
		void					RotateYdownto( Event *ev );
		void					RotateZdownto( Event *ev );
		void					RotateAxisdownto( Event *ev );
		void					RotateXupto( Event *ev );
		void					RotateYupto( Event *ev );
		void					RotateZupto( Event *ev );
		void					RotateAxisupto( Event *ev );
		void					Rotateupto( Event *ev );
		void					Rotatedownto( Event *ev );
		void					Rotateto( Event *ev );
		void					RotateXdown( Event *ev );
		void					RotateYdown( Event *ev );
		void					RotateZdown( Event *ev );
		void					RotateAxisdown( Event *ev );
		void					RotateXup( Event *ev );
		void					RotateYup( Event *ev );
		void					RotateZup( Event *ev );
		void					RotateAxisup( Event *ev );
		void					RotateX( Event *ev );
		void					RotateY( Event *ev );
		void					RotateZ( Event *ev );
		void					RotateAxis( Event *ev );
		void					OnTouch( Event *ev );
		void					NoTouch( Event *ev );
		void					TouchFunc( Event *ev );
		void					OnBlock( Event *ev );
		void					NoBlock( Event *ev );
		void					BlockFunc( Event *ev );
		void					OnTrigger( Event *ev );
		void					NoTrigger( Event *ev );
		void					TriggerFunc( Event *ev );
		void					OnUse( Event *ev );
		void					NoUse( Event *ev );
		void					UseFunc( Event *ev );
		void					OnDamage( Event *ev );
		void					NoDamage( Event *ev );
      void              DamageFunc( Event *ev );
      void					SetDamage( Event *ev );
		void					FollowPath( Event *ev );
		void					EndPath( Event *ev );
		void					FollowingPath( Event *ev );
      void              CreatePath( SplinePath *path,	splinetype_t type );
      void              Explode( Event *ev );
      void              NotShootable( Event *ev );
      virtual void      Archive( Archiver &arc );
      virtual void      Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void ScriptSlave::Archive
	(
	Archiver &arc
	)
   {
   Mover::Archive( arc );

   arc.WriteSafePointer( touchthread );
   arc.WriteSafePointer( blockthread );
   arc.WriteSafePointer( triggerthread );
   arc.WriteSafePointer( usethread );
   arc.WriteSafePointer( damagethread );
   arc.WriteSafePointer( movethread );

   arc.WriteString( touchlabel );
   arc.WriteString( uselabel );
   arc.WriteString( blocklabel );
   arc.WriteString( triggerlabel );
   arc.WriteString( damagelabel );

   arc.WriteFloat( attack_finished );
   arc.WriteInteger( dmg );

   arc.WriteBoolean( commandswaiting );
   arc.WriteVector( TotalRotation );
   arc.WriteVector( NewAngles );
   arc.WriteVector( NewPos );
   arc.WriteVector( ForwardDir );
   arc.WriteFloat( speed );
   arc.WriteObjectPointer( waypoint );
   arc.WriteFloat( traveltime );
   arc.WriteFloat( splineTime );
   arc.WriteBoolean( splineangles );
   arc.WriteBoolean( ignoreangles );

   // if it exists, archive it, otherwise place a special NULL ptr tag
   if ( splinePath )
      {
      arc.WriteInteger( ARCHIVE_POINTER_VALID );
      splinePath->Archive( arc );
      }
   else
      {
      arc.WriteInteger( ARCHIVE_POINTER_NULL );
      }
   }

inline EXPORT_FROM_DLL void ScriptSlave::Unarchive
	(
	Archiver &arc
	)
   {
   int i;

   Mover::Unarchive( arc );

   arc.ReadSafePointer( &touchthread );
   arc.ReadSafePointer( &blockthread );
   arc.ReadSafePointer( &triggerthread );
   arc.ReadSafePointer( &usethread );
   arc.ReadSafePointer( &damagethread );
   arc.ReadSafePointer( &movethread );

   arc.ReadString( &touchlabel );
   arc.ReadString( &uselabel );
   arc.ReadString( &blocklabel );
   arc.ReadString( &triggerlabel );
   arc.ReadString( &damagelabel );

   arc.ReadFloat( &attack_finished );
   arc.ReadInteger( &dmg );

   arc.ReadBoolean( &commandswaiting );
   arc.ReadVector( &TotalRotation );
   arc.ReadVector( &NewAngles );
   arc.ReadVector( &NewPos );
   arc.ReadVector( &ForwardDir );
   arc.ReadFloat( &speed );
   arc.ReadObjectPointer( ( Class ** )&waypoint );
   arc.ReadFloat( &traveltime );
   arc.ReadFloat( &splineTime );
   arc.ReadBoolean( &splineangles );
   arc.ReadBoolean( &ignoreangles );

   i = arc.ReadInteger();

   if ( i == ARCHIVE_POINTER_VALID )
      {
      splinePath = new BSpline;
      splinePath->Unarchive( arc );
      }
   else if ( i == ARCHIVE_POINTER_NULL )
      {
      splinePath = NULL;
      }
   else
      {
      warning( "Unarchive", "unable to determine archive type for splinePath" );
      }
   }

class EXPORT_FROM_DLL ScriptModel : public ScriptSlave
	{
   private:
      void              GibEvent(Event *ev);
	public:
      CLASS_PROTOTYPE( ScriptModel );
								ScriptModel();
	};

class EXPORT_FROM_DLL ScriptOrigin : public ScriptSlave
	{
	public:
      CLASS_PROTOTYPE( ScriptOrigin );
								ScriptOrigin();
	};

class EXPORT_FROM_DLL ScriptVolumetric : public ScriptSlave
	{
	public:
      CLASS_PROTOTYPE( ScriptVolumetric );
								ScriptVolumetric();
	};

#endif /* scriptslave.h */
