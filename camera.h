//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/camera.h                         $
// $Revision:: 27                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 5/19/99 11:30a                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/camera.h                              $
// 
// 27    5/19/99 11:30a Markd
// Added new camera support 
// 
// 26    3/19/99 8:59p Aldie
// Added SetCurrentDistance
// 
// 25    10/25/98 11:53p Jimdose
// added EXPORT_TEMPLATE
// 
// 24    9/29/98 5:58p Markd
// put in archive and unarchive
// 
// 23    9/24/98 1:19a Markd
// bullet proofed some equating bspline code
// 
// 22    9/20/98 6:49p Markd
// Added Thread ability to cameras when they are looked through
// 
// 21    8/17/98 7:42p Markd
// Added SetOverlay
// 
// 20    8/17/98 6:20p Markd
// Changed SetCamera to a Player method
// 
// 19    8/17/98 4:35p Markd
// Added SecurityCamera
// 
// 18    8/14/98 8:18p Markd
// reworked camera class
// 
// 17    8/08/98 7:29p Aldie
// Added intermissions for deathmatch
// 
// 16    7/22/98 5:22p Markd
// Added MoveToPos and TurnTo
// 
// 15    7/22/98 4:12p Markd
// Redid camera stuff
// 
// 14    7/18/98 6:14p Markd
// Added optional watch commands at the end of follow and orbit events
// 
// 13    7/13/98 12:58p Markd
// added fixed_position
// 
// 12    7/11/98 6:31p Markd
// removed valid orientation, simplified code
// 
// 11    7/10/98 1:12p Markd
// Added more functionality to camera stuff
// 
// 10    7/08/98 12:42p Markd
// Removed CameraPath with SplinePath
// 
// 9     7/02/98 9:48p Markd
// Added orientation support to cameras
// 
// 8     5/27/98 3:18a Jimdose
// cameras can now watch specific entities
// 
// 7     5/26/98 8:49p Jimdose
// Added yaw commands
// 
// 6     5/26/98 8:18p Jimdose
// added height event
// 
// 5     5/26/98 7:56p Jimdose
// added scripted cameras
// 
// 4     5/13/98 4:55p Jimdose
// now uses SafePtrs
// 
// 3     5/07/98 10:41p Jimdose
// fleshed out functionality a bit more
// 
// 2     5/05/98 2:37p Jimdose
// Created file
// 
// DESCRIPTION:
// Camera.  Duh.
// 

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "g_local.h"
#include "entity.h"
#include "bspline.h"

#define ORBIT		1
#define START_ON	2
#define PANNING	4

extern Event EV_Camera_FollowingPath;
extern Event EV_Camera_StartMoving;
extern Event EV_Camera_Pause;
extern Event EV_Camera_Continue;
extern Event EV_Camera_StopMoving;
extern Event EV_Camera_SetSpeed;
extern Event EV_Camera_SetDistance;
extern Event EV_Camera_SetHeight;
extern Event EV_Camera_SetYaw;
extern Event EV_Camera_FixedYaw;
extern Event EV_Camera_RelativeYaw;
extern Event EV_Camera_SetFOV;
extern Event EV_Camera_Orbit;
extern Event EV_Camera_Follow;
extern Event EV_Camera_Watch;
extern Event EV_Camera_LookAt;
extern Event EV_Camera_TurnTo;
extern Event EV_Camera_MoveToEntity;
extern Event EV_Camera_MoveToPos;
extern Event EV_Camera_NoWatch;
extern Event EV_Camera_IgnoreAngles;
extern Event EV_Camera_UseAngles;
extern Event EV_Camera_SplineAngles;
extern Event EV_Camera_NormalAngles;
extern Event EV_Camera_FixedPosition;
extern Event EV_Camera_NoFixedPosition;
extern Event EV_Camera_JumpTime;
extern Event EV_Camera_JumpCut;
extern Event EV_Camera_Pan;
extern Event EV_Camera_StopPan;
extern Event EV_Camera_PanSpeed;
extern Event EV_Camera_PanMax;
extern Event EV_Camera_SetPanAngles;


class EXPORT_FROM_DLL CameraMoveState
   {
   public:
      Vector            pos;

	   BSpline				cameraPath;
	   float					cameraTime;

	   EntityPtr			followEnt;
      EntityPtr         orbitEnt;

      qboolean          followingpath;
	   float					speed;
      qboolean          fixed_position;
	   float					fov;
		float					height;
		float					follow_dist;
		int					follow_mask;

		void		      operator=( CameraMoveState &newstate );
	   virtual void   Archive( Archiver &arc );
      virtual void   Unarchive( Archiver &arc );
   };

inline void CameraMoveState::operator=
	(
	CameraMoveState &newstate
	)

	{
   pos = newstate.pos;

   cameraPath = newstate.cameraPath;

   cameraTime = newstate.cameraTime;

   followEnt = newstate.followEnt;
   orbitEnt = newstate.orbitEnt;

   followingpath = newstate.followingpath;
   speed = newstate.speed;
   fixed_position = newstate.fixed_position;
   fov = newstate.fov;
   height = newstate.height;
   follow_dist = newstate.follow_dist;
   follow_mask = newstate.follow_mask;
	}

inline EXPORT_FROM_DLL void CameraMoveState::Archive
	(
	Archiver &arc
	)
   {
   arc.WriteVector( pos );

   cameraPath.Archive( arc );

   arc.WriteFloat( cameraTime );

   arc.WriteSafePointer( followEnt );
   arc.WriteSafePointer( orbitEnt );

   arc.WriteBoolean( followingpath );
   arc.WriteFloat( speed );
   arc.WriteBoolean( fixed_position );

   arc.WriteFloat( fov );
   arc.WriteFloat( height );
   arc.WriteFloat( follow_dist );
   arc.WriteInteger( follow_mask );
   }

inline EXPORT_FROM_DLL void CameraMoveState::Unarchive
	(
	Archiver &arc
	)
   {
   arc.ReadVector( &pos );

   cameraPath.Unarchive( arc );

   arc.ReadFloat( &cameraTime );

   arc.ReadSafePointer( &followEnt );
   arc.ReadSafePointer( &orbitEnt );

   arc.ReadBoolean( &followingpath );
   arc.ReadFloat( &speed );
   arc.ReadBoolean( &fixed_position );

   arc.ReadFloat( &fov );
   arc.ReadFloat( &height );
   arc.ReadFloat( &follow_dist );
   arc.ReadInteger( &follow_mask );
   }

class EXPORT_FROM_DLL CameraWatchState
   {
   public:
      Vector            dir;

	   EntityPtr			watchEnt;

      qboolean          ignoreangles;
      qboolean          splineangles;
      qboolean          panning;

      float             pan_offset;
      float             pan_dir;
      float             pan_max;
      float             pan_speed;
      Vector            pan_angles;

	   float					yaw;
	   qboolean				fixedyaw;

	   virtual void      Archive( Archiver &arc );
      virtual void      Unarchive( Archiver &arc );
   };

inline EXPORT_FROM_DLL void CameraWatchState::Archive
	(
	Archiver &arc
	)
   {
   arc.WriteVector( dir );
   arc.WriteSafePointer( watchEnt );

   arc.WriteBoolean( ignoreangles );
   arc.WriteBoolean( splineangles );
   arc.WriteBoolean( panning );

   arc.WriteFloat( pan_offset );
   arc.WriteFloat( pan_dir );
   arc.WriteFloat( pan_max );
   arc.WriteFloat( pan_speed );
   arc.WriteVector( pan_angles );

   arc.WriteFloat( yaw );
   arc.WriteBoolean( fixedyaw );
   }

inline EXPORT_FROM_DLL void CameraWatchState::Unarchive
	(
	Archiver &arc
	)
   {
   arc.ReadVector( &dir );
   arc.ReadSafePointer( &watchEnt );

   arc.ReadBoolean( &ignoreangles );
   arc.ReadBoolean( &splineangles );
   arc.ReadBoolean( &panning );

   arc.ReadFloat( &pan_offset );
   arc.ReadFloat( &pan_dir );
   arc.ReadFloat( &pan_max );
   arc.ReadFloat( &pan_speed );
   arc.ReadVector( &pan_angles );

   arc.ReadFloat( &yaw );
   arc.ReadBoolean( &fixedyaw );
   }

class EXPORT_FROM_DLL CameraState
   {
   public:
      CameraMoveState   move;
      CameraWatchState  watch;

	   virtual void      Archive( Archiver &arc );
      virtual void      Unarchive( Archiver &arc );
   };

inline EXPORT_FROM_DLL void CameraState::Archive
	(
	Archiver &arc
	)
   {
   move.Archive( arc );
   watch.Archive( arc );
   }

inline EXPORT_FROM_DLL void CameraState::Unarchive
	(
	Archiver &arc
	)
   {
   move.Unarchive( arc );
   watch.Unarchive( arc );
   }

class EXPORT_FROM_DLL Camera : public Entity
	{
   private:
      float default_fov;
      float default_yaw;
      float default_follow_dist;
      float default_height;
      float default_speed;
      float default_pan_max;
      float default_pan_speed;

      Vector default_angles;

	protected:
      CameraState       currentstate;
      CameraState       newstate;

      float             watchTime;
      float             followTime;
      float             jumpTime;

		EntityPtr			targetEnt;
		EntityPtr			targetWatchEnt;

      str               nextCamera;
      str               overlay;
      str               thread;

		qboolean				showcamera;

		Event					moveevent;

		void					FollowingPath( Event *ev );
		void					CreateOribit( Vector pos, float radius );
		void					CreatePath( SplinePath *path, splinetype_t type );
      void              InitializeMoveState( CameraMoveState &movestate );
      void              InitializeWatchState( CameraWatchState &watchstate );
      void              InitializeState( CameraState &state );

	public:
      CLASS_PROTOTYPE( Camera );

      float             fov;

								Camera();
		void					Stop( void );
		void					FollowPath( SplinePath *path, qboolean loop, Entity *watch );
		void					Orbit( Entity *ent, float dist, Entity *watch );
		void					FollowEntity( Entity *ent, float dist, int mask, Entity *watch = NULL );
		void					StartMoving( Event *ev );
		void					StopMoving( Event *ev );
		void					Pause( Event *ev );
		void					Continue( Event *ev );
		void					SetSpeed( Event *ev );
		void					SetDistance( Event *ev );
		void					SetHeight( Event *ev );
		void					SetYaw( Event *ev );
		void					FixedYaw( Event *ev );
		void					RelativeYaw( Event *ev );
		void					SetFOV( Event *ev );
		void					OrbitEvent( Event *ev );
		void					FollowEvent( Event *ev );
		void					WatchEvent( Event *ev );
		void					NoWatchEvent( Event *ev );
		void					LookAt( Event *ev );
		void					MoveToEntity( Event *ev );
		void					MoveToPos( Event *ev );
		void					IgnoreAngles( Event *ev );
		void					UseAngles( Event *ev );
		void					SplineAngles( Event *ev );
		void					NormalAngles( Event *ev );
		void					FixedPosition( Event *ev );
		void					NoFixedPosition( Event *ev );
		void					JumpCut( Event *ev );
		void					JumpTime( Event *ev );
		void					TurnTo( Event *ev );
      void              EvaluatePosition( CameraState &state );
      void              PanEvent( Event *ev );
      void              StopPanEvent( Event *ev );
      void              PanSpeedEvent( Event *ev );
      void              PanMaxEvent( Event *ev );
      void              SetPanAngles( Event *ev );
      void              SetNextCamera( Event *ev );
      void              SetOverlay( Event *ev );
      void              SetThread( Event *ev );

      str               &NextCamera( void );
      str               &Thread( void );
      str               &Overlay( void );
      void              SetCurrentDistance( float dist );

      void              Reset( Vector org, Vector ang );

	   virtual void      Archive( Archiver &arc );
      virtual void      Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Camera::Archive
	(
	Archiver &arc
	)
   {
   Entity::Archive( arc );

   arc.WriteFloat( default_fov );
   arc.WriteFloat( default_yaw );
   arc.WriteFloat( default_follow_dist );
   arc.WriteFloat( default_height );
   arc.WriteFloat( default_speed );
   arc.WriteFloat( default_pan_max );
   arc.WriteFloat( default_pan_speed );
   arc.WriteVector( default_angles );

   // currentstate
   currentstate.Archive( arc );
   // newstate
   newstate.Archive( arc );

   arc.WriteFloat( watchTime );
   arc.WriteFloat( followTime );
   arc.WriteFloat( jumpTime );

   arc.WriteSafePointer( targetEnt );
   arc.WriteSafePointer( targetWatchEnt );

   arc.WriteString( nextCamera );
   arc.WriteString( overlay );
   arc.WriteString( thread );

   arc.WriteBoolean( showcamera );
   arc.WriteEvent( moveevent );
   arc.WriteFloat( fov );
   }

inline EXPORT_FROM_DLL void Camera::Unarchive
	(
	Archiver &arc
	)
   {
   Entity::Unarchive( arc );

   arc.ReadFloat( &default_fov );
   arc.ReadFloat( &default_yaw );
   arc.ReadFloat( &default_follow_dist );
   arc.ReadFloat( &default_height );
   arc.ReadFloat( &default_speed );
   arc.ReadFloat( &default_pan_max );
   arc.ReadFloat( &default_pan_speed );
   arc.ReadVector( &default_angles );

   // currentstate
   currentstate.Unarchive( arc );
   // newstate
   newstate.Unarchive( arc );

   arc.ReadFloat( &watchTime );
   arc.ReadFloat( &followTime );
   arc.ReadFloat( &jumpTime );

   arc.ReadSafePointer( &targetEnt );
   arc.ReadSafePointer( &targetWatchEnt );

   arc.ReadString( &nextCamera );
   arc.ReadString( &overlay );
   arc.ReadString( &thread );

   arc.ReadBoolean( &showcamera );
   arc.ReadEvent( &moveevent );
   arc.ReadFloat( &fov );
   }

void SetCamera( Entity *ent );

#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL SafePtr<Camera>;
#endif
typedef SafePtr<Camera> CameraPtr;

class EXPORT_FROM_DLL SecurityCamera : public Camera
	{
	public:
      CLASS_PROTOTYPE( SecurityCamera );

							SecurityCamera();
	};


class CameraManager : public Listener
   {
   protected:
      SplinePathPtr     path;
      SplinePathPtr     current;
      float             speed;
      int               watch;
      CameraPtr         cam;

      void              NewPath( Event *ev );
      void              SetPath( Event *ev );
      void              SetTargetName( Event *ev );
      void              SetTarget( Event *ev );
      void              AddPoint( Event *ev );
      void              ReplacePoint( Event *ev );
      void              DeletePoint( Event *ev );
      void              MovePlayer( Event *ev );
      void              NextPoint( Event *ev );
      void              PreviousPoint( Event *ev );
      void              ShowPath( Event *ev );
      void              HidePath( Event *ev );
      void              StopPlayback( Event *ev );
      void              PlayPath( Event *ev );
      void              LoopPath( Event *ev );
      void              Watch( Event *ev );
      void              NoWatch( Event *ev );
      void              Speed( Event *ev );
      void              Save( Event *ev );
      void              Load( Event *ev );
      void              SaveMap( Event *ev );

   public:
      CLASS_PROTOTYPE( CameraManager );

                        CameraManager();
      void              SetPath( SplinePath *node );
	   virtual void      Archive( Archiver &arc );
      virtual void      Unarchive( Archiver &arc );
   };

inline void CameraManager::Archive
	(
	Archiver &arc
	)

   {
   Listener::Archive( arc );

   arc.WriteSafePointer( path );
   arc.WriteSafePointer( current );
   arc.WriteFloat( speed );
   arc.WriteInteger( watch );
   arc.WriteSafePointer( cam );
   }

inline void CameraManager::Unarchive
	(
	Archiver &arc
	)

   {
   Listener::Unarchive( arc );

   arc.ReadSafePointer( &path );
   arc.ReadSafePointer( &current );
   arc.ReadFloat( &speed );
   arc.ReadInteger( &watch );
   arc.ReadSafePointer( &cam );
   }

extern CameraManager CameraMan;

#endif /* camera.h */
