//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/turret.h                         $
// $Revision:: 14                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 10/15/98 3:37p                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/turret.h                              $
// 
// 14    10/15/98 3:37p Markd
// Added forcefield to turrets with no health
// 
// 13    10/09/98 4:55p Markd
// Added ExecuteThread
// 
// 12    9/30/98 4:37p Aldie
// Fixed some weirdness with turrets not responding
// 
// 11    9/22/98 4:57p Aldie
// Moved lagtime check right before firing
// 
// 10    9/21/98 4:21p Markd
// Put in archive functions and rewrote all archive routines
// 
// 9     9/20/98 9:11p Aldie
// Added lagtime and patience
// 
// 8     9/20/98 5:13p Aldie
// Fixed some stuff with thread and target when turret sees player
// 
// 7     9/19/98 6:15p Aldie
// Added thread to turrets
// 
// 6     7/10/98 3:08p Aldie
// Activate and deactivate turrets
// 
// 5     7/07/98 4:12p Aldie
// Updated to new class hierarchy
// 
// 3     10/27/97 2:59p Jimdose
// Removed dependency on quakedef.h
// 
// 2     9/26/97 5:23p Jimdose
// Added standard Ritual headers
//
// DESCRIPTION:
// Script controlled turret.
// 

#ifndef __TURRET_H__
#define __TURRET_H__

#include "sentient.h"

#define TURRET_OUTOFRANGE		0
#define TURRET_WAKEUPRANGE		1
#define TURRET_FIRERANGE		2

class EXPORT_FROM_DLL Turret : public Sentient
	{
	protected:
		int				base;
		int				enemy;
		float				lastSightTime;
		qboolean			active;
		qboolean			attacking;
		qboolean			turning;
		float				neworientation;
		float				turntime;
      float          lagtime;
      float          firetime;
      float          patience;
      int            wakeupdistance;
      int            firingdistance;
      qboolean       activated;
      str            thread;
      str            sight_target;

	public:
      CLASS_PROTOTYPE( Turret );

							         Turret();
								
		virtual qboolean			CanSee( Entity *ent );
		virtual int				   Range( float dist );
		virtual float				Distance( Entity *targ );
		virtual void				Pain( Event *ev );
		virtual void				Killed( Event *ev );
		virtual qboolean			FindTarget( void );
		virtual float				AdjustAngle( float maxadjust, float currangle, float targetangle );
		virtual void				Seek( Event *ev );
		virtual void				Fire( Event *ev );
		virtual void				Turn( Event *ev );
		virtual void				EndSeek( Event *ev );
		virtual void				CheckVicinity( Event *ev );
		virtual void				GoUp( Event *ev );
		virtual void				GoDown( Event *ev );
		virtual void				Down( Event *ev );
		virtual void				AttackStart( Event *ev );
		virtual void				AttackFinished( Event *ev );
      virtual void				Activate( Event *ev );
      virtual void				Deactivate( Event *ev );
      virtual void            Lagtime( Event *ev );
      virtual void            SetSightTime( Event *ev );
      virtual void            Archive(	Archiver &arc );
      virtual void            Unarchive( Archiver &arc );
	};

extern Event EV_Turret_GoUp;
extern Event EV_Turret_GoDown;
extern Event EV_Turret_Turn;
extern Event EV_Turret_Seek;
extern Event EV_Turret_Attack;

inline EXPORT_FROM_DLL void Turret::Archive
	(
	Archiver &arc
	)
   {
   Sentient::Archive( arc );
   arc.WriteInteger( base );
   arc.WriteInteger( enemy );
   arc.WriteFloat( lastSightTime );
   arc.WriteBoolean( active );
   arc.WriteBoolean( attacking );
   arc.WriteBoolean( turning );
   arc.WriteFloat( neworientation );
   arc.WriteFloat( turntime );
   arc.WriteFloat( lagtime );
   arc.WriteFloat( firetime );
   arc.WriteFloat( patience );
   arc.WriteInteger( wakeupdistance );
   arc.WriteInteger( firingdistance );
   arc.WriteBoolean( activated );
   arc.WriteString( thread );
   arc.WriteString( sight_target );
   }

inline EXPORT_FROM_DLL void Turret::Unarchive
	(
	Archiver &arc
	)
   {
   Sentient::Unarchive( arc );
   arc.ReadInteger( &base );
   arc.ReadInteger( &enemy );
   arc.ReadFloat( &lastSightTime );
   arc.ReadBoolean( &active );
   arc.ReadBoolean( &attacking );
   arc.ReadBoolean( &turning );
   arc.ReadFloat( &neworientation );
   arc.ReadFloat( &turntime );
   arc.ReadFloat( &lagtime );
   arc.ReadFloat( &firetime );
   arc.ReadFloat( &patience );
   arc.ReadInteger( &wakeupdistance );
   arc.ReadInteger( &firingdistance );
   arc.ReadBoolean( &activated );
   arc.ReadString( &thread );
   arc.ReadString( &sight_target );
   }


#endif /* turret.h */
