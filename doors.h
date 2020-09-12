//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/doors.h                          $
// $Revision:: 26                                                             $
//   $Author:: Jimdose                                                        $
//     $Date:: 11/08/98 10:50p                                                $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/doors.h                               $
// 
// 26    11/08/98 10:50p Jimdose
// reordered archived variables so that they match the order in the struct
// 
// 25    10/25/98 11:53p Jimdose
// added EXPORT_TEMPLATE
// 
// 24    10/23/98 11:10p Jimdose
// removed trigger_finished
// 
// 23    10/21/98 10:58p Jimdose
// fixed (hopefully) most of the door bugs
// 
// 22    9/29/98 5:58p Markd
// put in archive and unarchive
// 
// 21    9/03/98 9:07p Jimdose
// Added CanBeOpenedBy so that the AI can check if a door is useable by an
// actor
// changed owner to master
// Fixed bug with doors that don't stop
// opened doors can be used again to close them
// fixed door blocked
// 
// 20    8/28/98 4:14p Markd
// Added sound_locked to doors
// 
// 19    8/24/98 6:10p Markd
// removed dmg from doors
// 
// 18    8/21/98 3:48p Markd
// Added openthread and closethread events
// 
// 17    8/21/98 1:43a Markd
// Added full ScriptDoor functionality
// 
// 16    7/26/98 3:40p Jimdose
// made locked public
// 
// 15    7/10/98 2:09p Markd
// Added locking capability to doors
// 
// 14    6/25/98 8:48p Markd
// Rewrote Item class, added keyed items to triggers, cleaned up item system
// 
// 13    6/24/98 8:45p Markd
// Rewrote Door Code
// 
// 12    5/13/98 4:54p Jimdose
// now uses SafePtrs
// 
// 11    4/30/98 9:24p Jimdose
// Changed use of string to str class
// 
// 10    3/29/98 9:38p Jimdose
// Changed killed to an event
// 
// 9     3/23/98 1:33p Jimdose
// Revamped event and command system
// 
// 8     3/11/98 2:25p Jimdose
// Updated to work with areaportals
// 
// 7     3/07/98 5:06p Jimdose
// Converted to Quake2
// 
// 5     12/06/97 4:50p Markd
// Added interpretCommands. 
// Added GetArgs as commands for future processing
// Removed dmg,attentuatioin and volume, moved these to Trigger
// 
// 4     10/27/97 2:50p Jimdose
// Removed dependency on quakedef.h
// 
// 3     10/27/97 2:38p Jimdose
// Changed nextdoor from a Door * into an int.
// 
// 2     9/26/97 5:23p Jimdose
// Added standard Ritual headers
//
// DESCRIPTION:
// Doors are environment objects that slide open when activated by triggers
// or when used by the player.
// 

#ifndef __DOORS_H__
#define __DOORS_H__

#include "g_local.h"
#include "entity.h"
#include "trigger.h"
#include "scriptslave.h"

extern Event EV_Door_TryOpen;
extern Event EV_Door_GoDown;
extern Event EV_Door_GoUp;
extern Event EV_Door_HitBottom;
extern Event EV_Door_HitTop;
extern Event EV_Door_Fire;
extern Event EV_Door_Link;
extern Event EV_Door_SetSpeed;
extern Event EV_Door_Lock;
extern Event EV_Door_Unlock;

class Door;
#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL SafePtr<Door>;
#endif
typedef SafePtr<Door> DoorPtr;

class EXPORT_FROM_DLL Door : public ScriptSlave
	{
	protected:
		str			sound_stop;
		str			sound_move;
		str			sound_message;
		str			sound_locked;
      float       lastblocktime;
		float			angle;
		Vector		dir;
		Vector		doormin;
		Vector		doormax;
      float       diropened;
		int			state;
      int         previous_state;
		int			trigger;
		int			nextdoor;
		DoorPtr		master;

		void			OpenEnd( Event *ev );
		void			CloseEnd( Event *ev );
		void			Close( Event *ev );
		void			Open( Event *ev );
		void			DoorUse( Event *ev );
		void			DoorFire( Event *ev );
		void			DoorBlocked( Event *ev );
		void			FieldTouched( Event *ev );
		void			TryOpen( Event *ev );
		void			SpawnTriggerField( Vector fmins, Vector fmaxs );
		qboolean		DoorTouches( Door *e1 );
		void			LinkDoors( Event *ev );	
		void			SetTime( Event *ev );
		void			LockDoor( Event *ev );
		void			UnlockDoor( Event *ev );

	public:
      CLASS_PROTOTYPE( Door );

      qboolean		locked;

						Door();
		qboolean		isOpen( void );
		qboolean		CanBeOpenedBy( Entity *ent );
	   virtual void Archive( Archiver &arc );
      virtual void Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Door::Archive
	(
	Archiver &arc
	)
   {
   ScriptSlave::Archive( arc );

   arc.WriteString( sound_stop );
   arc.WriteString( sound_move );
   arc.WriteString( sound_message );
   arc.WriteString( sound_locked );
   arc.WriteFloat( lastblocktime );
   arc.WriteFloat( angle );
   arc.WriteVector( dir );
   arc.WriteVector( doormin );
   arc.WriteVector( doormax );
   arc.WriteFloat( diropened );
   arc.WriteInteger( state );
   arc.WriteInteger( previous_state );
   arc.WriteInteger( trigger );
   arc.WriteInteger( nextdoor );
   arc.WriteSafePointer( master );
   arc.WriteBoolean( locked );
   }

inline EXPORT_FROM_DLL void Door::Unarchive
	(
	Archiver &arc
	)
   {
   ScriptSlave::Unarchive( arc );

   arc.ReadString( &sound_stop );
   arc.ReadString( &sound_move );
   arc.ReadString( &sound_message );
   arc.ReadString( &sound_locked );
   arc.ReadFloat( &lastblocktime );
   arc.ReadFloat( &angle );
   arc.ReadVector( &dir );
   arc.ReadVector( &doormin );
   arc.ReadVector( &doormax );
   arc.ReadFloat( &diropened );
   arc.ReadInteger( &state );
   arc.ReadInteger( &previous_state );
   arc.ReadInteger( &trigger );
   arc.ReadInteger( &nextdoor );
   arc.ReadSafePointer( &master );
   arc.ReadBoolean( &locked );
   }


class EXPORT_FROM_DLL SlidingDoor : public Door
	{
	protected:
      float    totalmove;
      float    lip;
      Vector   pos1;
      Vector   pos2;

	public:
      CLASS_PROTOTYPE( SlidingDoor );

      void     DoOpen( Event *ev );
      void     DoClose( Event *ev );
	   virtual void Archive( Archiver &arc );
      virtual void Unarchive( Archiver &arc );

					SlidingDoor();
	};

inline EXPORT_FROM_DLL void SlidingDoor::Archive
	(
	Archiver &arc
	)
   {
   Door::Archive( arc );

   arc.WriteFloat( totalmove );
   arc.WriteFloat( lip );
   arc.WriteVector( pos1 );
   arc.WriteVector( pos2 );
   }

inline EXPORT_FROM_DLL void SlidingDoor::Unarchive
	(
	Archiver &arc
	)
   {
   Door::Unarchive( arc );

   arc.ReadFloat( &totalmove );
   arc.ReadFloat( &lip );
   arc.ReadVector( &pos1 );
   arc.ReadVector( &pos2 );
   }

class EXPORT_FROM_DLL RotatingDoor : public Door
	{
	protected:
		float		angle;
      Vector   startangle;
      int      init_door_direction;

	public:
      CLASS_PROTOTYPE( RotatingDoor );

      void     DoOpen( Event *ev );
      void     DoClose( Event *ev );
	   virtual void Archive( Archiver &arc );
      virtual void Unarchive( Archiver &arc );

					RotatingDoor();
	};

inline EXPORT_FROM_DLL void RotatingDoor::Archive
	(
	Archiver &arc
	)
   {
   Door::Archive( arc );

   arc.WriteFloat( angle );
   arc.WriteVector( startangle );
   arc.WriteInteger( init_door_direction );
   }

inline EXPORT_FROM_DLL void RotatingDoor::Unarchive
	(
	Archiver &arc
	)
   {
   Door::Unarchive( arc );

   arc.ReadFloat( &angle );
   arc.ReadVector( &startangle );
   arc.ReadInteger( &init_door_direction );
   }

class EXPORT_FROM_DLL ScriptDoor : public Door
	{
	protected:
		ThreadPtr doorthread;
      str      initthreadname;
      str      openthreadname;
      str      closethreadname;
      float    doorsize;
		Vector	startangle;
      Vector   startorigin;
      Vector   movedir;

	public:
      CLASS_PROTOTYPE( ScriptDoor );

      void     DoInit( Event *ev );
      void     DoOpen( Event *ev );
      void     DoClose( Event *ev );
      void     SetOpenThread( Event *ev );
      void     SetCloseThread( Event *ev );
	   virtual void Archive( Archiver &arc );
      virtual void Unarchive( Archiver &arc );
					ScriptDoor();
	};

inline EXPORT_FROM_DLL void ScriptDoor::Archive
	(
	Archiver &arc
	)
   {
   Door::Archive( arc );

   arc.WriteSafePointer( doorthread );
   arc.WriteString( initthreadname );
   arc.WriteString( openthreadname );
   arc.WriteString( closethreadname );
   arc.WriteFloat( doorsize );
   arc.WriteVector( startangle );
   arc.WriteVector( startorigin );
   arc.WriteVector( movedir );
   }

inline EXPORT_FROM_DLL void ScriptDoor::Unarchive
	(
	Archiver &arc
	)
   {
   Door::Unarchive( arc );

   arc.ReadSafePointer( &doorthread );
   arc.ReadString( &initthreadname );
   arc.ReadString( &openthreadname );
   arc.ReadString( &closethreadname );
   arc.ReadFloat( &doorsize );
   arc.ReadVector( &startangle );
   arc.ReadVector( &startorigin );
   arc.ReadVector( &movedir );
   }
#endif /* doors.h */
