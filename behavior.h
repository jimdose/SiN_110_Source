//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/behavior.h                       $
// $Revision:: 55                                                             $
//   $Author:: Jimdose                                                        $
//     $Date:: 10/27/98 8:02p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/behavior.h                           $
// 
// 55    10/27/98 8:02p Jimdose
// added PlayAnimSeekEnemy
// 
// 54    10/27/98 12:42a Jimdose
// added animprefix to AimAndShoot
// 
// 53    10/25/98 11:52p Jimdose
// added EXPORT_TEMPLATE
// 
// 52    10/25/98 4:59a Jimdose
// Added lastSearchNode and lastSearchPos to chase
// archived howclose in GetCloseToEnemy
// 
// 51    10/22/98 11:44p Jimdose
// Added GetCloseToEnemy
// 
// 50    10/20/98 11:30p Markd
// Added aim_time to aimandshoot
// 
// 49    10/20/98 2:38a Markd
// Added goal variable to Jump
// 
// 48    10/17/98 4:41p Markd
// Added curioustime to Investigate behavior
// 
// 47    10/16/98 7:20p Markd
// Added maxshots and numshots to AimAndMelee
// 
// 46    10/14/98 9:02p Markd
// Made the Jump behavior more robust, and added landing
// 
// 45    10/14/98 5:22p Markd
// Moved jump definition
// 
// 44    10/13/98 7:38p Markd
// Created behaviors for Wander, FLy, FlyCloseAttack and WanderCloseAttack
// 
// 43    10/10/98 6:08p Markd
// Added FleeAndRemove, FindFlee, fixed max_ainode bug
// 
// 42    10/10/98 1:25a Jimdose
// Removed unneccesary definition stack template
// 
// 41    10/05/98 3:04p Markd
// Added enemy_health variable to AimAndShoot
// 
// 40    10/04/98 3:01p Markd
// fixed swimming behavior
// 
// 39    10/03/98 7:27p Markd
// working on swimming character and redid some weapon aiming stuff
// 
// 38    10/01/98 8:01p Markd
// Added AimAndMelee
// 
// 37    9/29/98 5:58p Markd
// put in archive and unarchive
// 
// 36    9/22/98 1:55a Jimdose
// Completed ShowInfo for all behaviors
// Added StrafeTo
// 
// 35    9/18/98 10:56p Jimdose
// Separated steering behaviors into their own file
// 
// 34    9/14/98 5:27p Jimdose
// Added SetPathRate to Chase so that actors can choose how often they search
// for a new path
// 
// 33    8/31/98 7:48p Jimdose
// Simplified FollowPath
// 
// 32    8/26/98 11:13p Jimdose
// Added StrafeAttack
// 
// 31    8/19/98 8:47p Jimdose
// Added Jump behavior
// 
// 30    8/14/98 6:25p Jimdose
// Got rid of decelleration for steering
// Added GoalEnt to GotoPathNode
// 
// 29    8/08/98 8:24p Markd
// added pickupandthrow
// 
// 28    8/07/98 6:02p Jimdose
// Rewrote AimAndShoot
// 
// 27    8/06/98 6:57p Jimdose
// Removed FireFromCover (now done in script)
// Added SetArgs to AimAndShoot
// 
// 26    8/03/98 7:58p Aldie
// Added a first attempt at wander behavior
// 
// 25    7/26/98 11:44a Jimdose
// Added FindClosestSightNode
// 
// 24    7/22/98 10:51p Jimdose
// Added repel behavior
// 
// 23    7/08/98 9:00p Jimdose
// Made OpenDoor script callable
// 
// 22    7/06/98 1:06p Jimdose
// working on ai
// 
// 21    6/30/98 6:03p Jimdose
// Chase and GotoPathNode now can use vectors for goals
// Investigate no longer needs currentEnemy to be set
// 
// 20    6/24/98 4:26p Jimdose
// Fixed bugs in TurnTo
// 
// 19    6/17/98 1:18a Jimdose
// Removed TargetEnemies.  Moved it back into actor
// 
// 18    6/15/98 10:47p Jimdose
// Added Hide and CoverFire
// 
// 17    6/13/98 8:21p Jimdose
// Added FindCover
// 
// 16    6/11/98 12:44a Jimdose
// behaviors now get info from the script at startup
// 
// 15    6/10/98 10:25p Jimdose
// added priority based state system
// 
// 14    6/09/98 4:24p Jimdose
// worked on ai
// 
// 13    6/04/98 10:48p Jimdose
// Fixed a bunch of things that got broken just in time for E3.  Paths and
// scripting actually work now.
// 
// 12    6/03/98 5:44p Jimdose
// Fixed spelling of behavior. :)
// 
// 11    5/27/98 7:12a Jimdose
// ai ai ai
// 
// 10    5/27/98 6:39a Jimdose
// working on ai
// 
// 9     5/27/98 5:11a Jimdose
// working on ai
// 
// 8     5/25/98 5:31p Jimdose
// Pathnodes are no longer a subclass of Entity.  This was done to save on
// edicts
// 
// 7     5/25/98 1:06a Jimdose
// Added chatter
// 
// 6     5/24/98 1:02a Jimdose
// Added Investigate
// 
// 5     5/23/98 6:29p Jimdose
// Added Aim
// 
// 4     5/22/98 9:39p Jimdose
// Worked on ai
// 
// 3     5/20/98 6:38p Jimdose
// working on ai
// 
// 2     5/18/98 8:15p Jimdose
// Created file
// 
// DESCRIPTION:
// Standard class for creating AI behaviors
//

#ifndef __BEHAVIOR_H__
#define __BEHAVIOR_H__

#include "g_local.h"
#include "entity.h"
#include "path.h"
#include "steering.h"

extern Event EV_Behavior_Args;
extern Event EV_Behavior_AnimDone;

class Actor;

class EXPORT_FROM_DLL Behavior : public Listener
	{
	protected:
		PathNodePtr				movegoal;

	public:
      CLASS_PROTOTYPE( Behavior );

									Behavior();

      virtual void         ShowInfo( Actor &self );
		virtual void			Begin( Actor &self );
		virtual qboolean		Evaluate( Actor &self );
		virtual void			End( Actor &self );
	   virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Behavior::Archive
	(
	Archiver &arc
	)
   {
   Listener::Archive( arc );

   arc.WriteSafePointer( movegoal );
   }

inline EXPORT_FROM_DLL void Behavior::Unarchive
	(
	Archiver &arc
	)
   {
   Listener::Unarchive( arc );

   arc.ReadSafePointer( &movegoal );
   }

#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL SafePtr<Behavior>;
#endif
typedef SafePtr<Behavior> BehaviorPtr;

class EXPORT_FROM_DLL Idle : public Behavior
	{
	private:
		float						nexttwitch;
		str						anim;

	public:
      CLASS_PROTOTYPE( Idle );

		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Idle::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.WriteFloat( nexttwitch );
   arc.WriteString( anim );
   }

inline EXPORT_FROM_DLL void Idle::Unarchive
	(
	Archiver &arc
	)
   {
   Behavior::Unarchive( arc );

   arc.ReadFloat( &nexttwitch );
   arc.ReadString( &anim );
   }

class EXPORT_FROM_DLL Aim : public Behavior
	{
	private:
		Seek						seek;
		EntityPtr				target;

	public:
      CLASS_PROTOTYPE( Aim );

		void						SetTarget( Entity *ent );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Aim::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.WriteObject( &seek );
   arc.WriteSafePointer( target );
   }

inline EXPORT_FROM_DLL void Aim::Unarchive
	(
	Archiver &arc
	)
   {
   Behavior::Unarchive( arc );

   arc.ReadObject( &seek );
   arc.ReadSafePointer( &target );
   }

class EXPORT_FROM_DLL FireOnSight : public Behavior
	{
	private:
		Chase						chase;
		Aim						aim;
		int						mode;
		str						anim;

	public:
      CLASS_PROTOTYPE( FireOnSight );

		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void FireOnSight::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.WriteObject( &chase );
   arc.WriteObject( &aim );
   arc.WriteInteger( mode );
   arc.WriteString( anim );
   }

inline EXPORT_FROM_DLL void FireOnSight::Unarchive
	(
	Archiver &arc
	)
   {
   Behavior::Unarchive( arc );

   arc.ReadObject( &chase );
   arc.ReadObject( &aim );
   arc.ReadInteger( &mode );
   arc.ReadString( &anim );
   }

class EXPORT_FROM_DLL TurnTo : public Behavior
	{
	private:
		Seek						seek;
		EntityPtr				ent;
		Vector					dir;
		float						yaw;
		int						mode;

	public:
      CLASS_PROTOTYPE( TurnTo );

									TurnTo();
		void						SetDirection( float yaw );
		void						SetTarget( Entity *ent );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void TurnTo::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.WriteObject( &seek );
   arc.WriteSafePointer( ent );
   arc.WriteVector( dir );
   arc.WriteFloat( yaw );
   arc.WriteInteger( mode );
   }

inline EXPORT_FROM_DLL void TurnTo::Unarchive
	(
	Archiver &arc
	)
   {
   Behavior::Unarchive( arc );

   arc.ReadObject( &seek );
   arc.ReadSafePointer( &ent );
   arc.ReadVector( &dir );
   arc.ReadFloat( &yaw );
   arc.ReadInteger( &mode );
   }

class EXPORT_FROM_DLL Jump : public Behavior
	{
	private:
		float						endtime;
		float						speed;
		str						anim;
      int                  state;
		qboolean					animdone;
      Vector               goal;

	public:
      CLASS_PROTOTYPE( Jump );

									Jump();
		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
		void						AnimDone( Event *ev );
	   virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Jump::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.WriteFloat( endtime );
   arc.WriteFloat( speed );
   arc.WriteString( anim );
   arc.WriteInteger( state );
   arc.WriteBoolean( animdone );
   arc.WriteVector( goal );
   }

inline EXPORT_FROM_DLL void Jump::Unarchive
	(
	Archiver &arc
	)
   {
   Behavior::Unarchive( arc );

   arc.ReadFloat( &endtime );
   arc.ReadFloat( &speed );
   arc.ReadString( &anim );
   arc.ReadInteger( &state );
   arc.ReadBoolean( &animdone );
   arc.ReadVector( &goal );
   }


class EXPORT_FROM_DLL GotoPathNode : public Behavior
	{
	private:
		TurnTo					turnto;
		Chase						chase;
		int						state;
		qboolean					usevec;
		float						time;
		str						anim;
		EntityPtr				goalent;
		Vector					goal;

	public:
      CLASS_PROTOTYPE( GotoPathNode );

									GotoPathNode();
		void						SetArgs( Event *ev );
		void						SetGoal( PathNode *node );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void GotoPathNode::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.WriteObject( &turnto );
   arc.WriteObject( &chase );
   arc.WriteInteger( state );
   arc.WriteBoolean( usevec );
   arc.WriteFloat( time );
   arc.WriteString( anim );
   arc.WriteSafePointer( goalent );
   arc.WriteVector( goal );
   }

inline EXPORT_FROM_DLL void GotoPathNode::Unarchive
	(
	Archiver &arc
	)
   {
   Behavior::Unarchive( arc );

   arc.ReadObject( &turnto );
   arc.ReadObject( &chase );
   arc.ReadInteger( &state );
   arc.ReadBoolean( &usevec );
   arc.ReadFloat( &time );
   arc.ReadString( &anim );
   arc.ReadSafePointer( &goalent );
   arc.ReadVector( &goal );
   }

class EXPORT_FROM_DLL Investigate : public Behavior
	{
	private:
		Chase						chase;
		str						anim;
		Vector					goal;
      float                curioustime;

		qboolean					Done( Actor &self );

	public:
      CLASS_PROTOTYPE( Investigate );

		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Investigate::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.WriteObject( &chase );
   arc.WriteString( anim );
   arc.WriteVector( goal );
   arc.WriteFloat( curioustime );
   }

inline EXPORT_FROM_DLL void Investigate::Unarchive
	(
	Archiver &arc
	)
   {
   Behavior::Unarchive( arc );

   arc.ReadObject( &chase );
   arc.ReadString( &anim );
   arc.ReadVector( &goal );
   arc.ReadFloat( &curioustime );
   }

class EXPORT_FROM_DLL Flee : public Behavior
	{
	private:
		FollowPath				follow;
		PathPtr					path;
		ObstacleAvoidance		avoid;
		float						avoidtime;
		str						anim;

	public:
      CLASS_PROTOTYPE( Flee );

		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Flee::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.WriteObject( &follow );
   arc.WriteSafePointer( path );
   arc.WriteObject( &avoid );
   arc.WriteFloat( avoidtime );
   arc.WriteString( anim );
   }

inline EXPORT_FROM_DLL void Flee::Unarchive
	(
	Archiver &arc
	)
   {
   Behavior::Unarchive( arc );

   arc.ReadObject( &follow );
   arc.ReadSafePointer( &path );
   arc.ReadObject( &avoid );
   arc.ReadFloat( &avoidtime );
   arc.ReadString( &anim );
   }

class EXPORT_FROM_DLL OpenDoor : public Behavior
	{
	private:
		float						time;
		float						endtime;
		qboolean					usedir;
		Vector					dir;

	public:
      CLASS_PROTOTYPE( OpenDoor );

									OpenDoor();
		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void OpenDoor::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.WriteFloat( time );
   arc.WriteFloat( endtime );
   arc.WriteBoolean( usedir );
   arc.WriteVector( dir );
   }

inline EXPORT_FROM_DLL void OpenDoor::Unarchive
	(
	Archiver &arc
	)
   {
   Behavior::Unarchive( arc );

   arc.ReadFloat( &time );
   arc.ReadFloat( &endtime );
   arc.ReadBoolean( &usedir );
   arc.ReadVector( &dir );
   }

class EXPORT_FROM_DLL PlayAnim : public Behavior
	{
	private:
		str						anim;
		
	public:
      CLASS_PROTOTYPE( PlayAnim );

		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void PlayAnim::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.WriteString( anim );
   }

inline EXPORT_FROM_DLL void PlayAnim::Unarchive
	(
	Archiver &arc
	)
   {
   Behavior::Unarchive( arc );

   arc.ReadString( &anim );
   }

class EXPORT_FROM_DLL FindCover : public Behavior
	{
	private:
		str						anim;
		Chase						chase;
		int						state;
		float						nextsearch;
		
	public:
      CLASS_PROTOTYPE( FindCover );

		void						SetArgs( Event *ev );
		PathNode					*FindCoverNode( Actor &self );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void FindCover::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.WriteString( anim );
   arc.WriteObject( &chase );
   arc.WriteInteger( state );
   arc.WriteFloat( nextsearch );
   }

inline EXPORT_FROM_DLL void FindCover::Unarchive
	(
	Archiver &arc
	)
   {
   Behavior::Unarchive( arc );

   arc.ReadString( &anim );
   arc.ReadObject( &chase );
   arc.ReadInteger( &state );
   arc.ReadFloat( &nextsearch );
   }

class EXPORT_FROM_DLL FindFlee : public Behavior
	{
	private:
		str						anim;
		Chase						chase;
		int						state;
		float						nextsearch;
		
	public:
      CLASS_PROTOTYPE( FindFlee );

		void						SetArgs( Event *ev );
		PathNode					*FindFleeNode( Actor &self );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void FindFlee::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.WriteString( anim );
   arc.WriteObject( &chase );
   arc.WriteInteger( state );
   arc.WriteFloat( nextsearch );
   }

inline EXPORT_FROM_DLL void FindFlee::Unarchive
	(
	Archiver &arc
	)
   {
   Behavior::Unarchive( arc );

   arc.ReadString( &anim );
   arc.ReadObject( &chase );
   arc.ReadInteger( &state );
   arc.ReadFloat( &nextsearch );
   }

class EXPORT_FROM_DLL FindEnemy : public Behavior
	{
	private:
		str						anim;
		Chase						chase;
		int						state;
		float						nextsearch;
      PathNodePtr          lastSearchNode;
      Vector               lastSearchPos;
		
	public:
      CLASS_PROTOTYPE( FindEnemy );

		PathNode					*FindClosestSightNode( Actor &self );
		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void FindEnemy::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.WriteString( anim );
   arc.WriteObject( &chase );
   arc.WriteInteger( state );
   arc.WriteFloat( nextsearch );
   arc.WriteSafePointer( lastSearchNode );
   arc.WriteVector( lastSearchPos );
   }

inline EXPORT_FROM_DLL void FindEnemy::Unarchive
	(
	Archiver &arc
	)
   {
   Behavior::Unarchive( arc );

   arc.ReadString( &anim );
   arc.ReadObject( &chase );
   arc.ReadInteger( &state );
   arc.ReadFloat( &nextsearch );
   arc.ReadSafePointer( &lastSearchNode );
   arc.ReadVector( &lastSearchPos );
   }

class EXPORT_FROM_DLL Hide : public Behavior
	{
	private:
		FindCover				hide;
		str						anim;
		int						state;
		float						checktime;
		
	public:
      CLASS_PROTOTYPE( Hide );

		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Hide::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.WriteObject( &hide );
   arc.WriteString( anim );
   arc.WriteInteger( state );
   arc.WriteFloat( checktime );
   }

inline EXPORT_FROM_DLL void Hide::Unarchive
	(
	Archiver &arc
	)
   {
   Behavior::Unarchive( arc );

   arc.ReadObject( &hide );
   arc.ReadString( &anim );
   arc.ReadInteger( &state );
   arc.ReadFloat( &checktime );
   }


class EXPORT_FROM_DLL FleeAndRemove : public Behavior
	{
	private:
		FindFlee				   flee;
		str						anim;
		int						state;
		float						checktime;
		
	public:
      CLASS_PROTOTYPE( FleeAndRemove );

		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void FleeAndRemove::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.WriteObject( &flee );
   arc.WriteString( anim );
   arc.WriteInteger( state );
   arc.WriteFloat( checktime );
   }

inline EXPORT_FROM_DLL void FleeAndRemove::Unarchive
	(
	Archiver &arc
	)
   {
   Behavior::Unarchive( arc );

   arc.ReadObject( &flee );
   arc.ReadString( &anim );
   arc.ReadInteger( &state );
   arc.ReadFloat( &checktime );
   }


class EXPORT_FROM_DLL AimAndShoot : public Behavior
	{
	private:
		Aim						aim;
		int						mode;
		int						maxshots;
		int						numshots;
		qboolean					animdone;
      float                enemy_health;
      float                aim_time;
      str                  animprefix;
      str                  readyfireanim;
      str                  aimanim;
      str                  fireanim;

	public:
      CLASS_PROTOTYPE( AimAndShoot );

									AimAndShoot();
		void						SetMaxShots( int num );
		void						SetArgs( Event *ev );
		void						AnimDone( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void AimAndShoot::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.WriteObject( &aim );
   arc.WriteInteger( mode );
   arc.WriteInteger( maxshots );
   arc.WriteInteger( numshots );
   arc.WriteBoolean( animdone );
   arc.WriteFloat( enemy_health );
   arc.WriteFloat( aim_time );
   arc.WriteString( animprefix );
   arc.WriteString( readyfireanim );
   arc.WriteString( aimanim );
   arc.WriteString( fireanim );
   }

inline EXPORT_FROM_DLL void AimAndShoot::Unarchive
	(
	Archiver &arc
	)
   {
   Behavior::Unarchive( arc );

   arc.ReadObject( &aim );
   arc.ReadInteger( &mode );
   arc.ReadInteger( &maxshots );
   arc.ReadInteger( &numshots );
   arc.ReadBoolean( &animdone );
   arc.ReadFloat( &enemy_health );
   arc.ReadFloat( &aim_time );
   arc.ReadString( &animprefix );
   arc.ReadString( &readyfireanim );
   arc.ReadString( &aimanim );
   arc.ReadString( &fireanim );
   }

class EXPORT_FROM_DLL AimAndMelee : public Behavior
	{
	private:
		Aim						aim;
		int						mode;
		int						maxshots;
		int						numshots;
		qboolean					animdone;

	public:
      CLASS_PROTOTYPE( AimAndMelee );

									AimAndMelee();
		void						SetArgs( Event *ev );
		void						AnimDone( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void AimAndMelee::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.WriteObject( &aim );
   arc.WriteInteger( mode );
   arc.WriteInteger( maxshots );
   arc.WriteInteger( numshots );
   arc.WriteBoolean( animdone );
   }

inline EXPORT_FROM_DLL void AimAndMelee::Unarchive
	(
	Archiver &arc
	)
   {
   Behavior::Unarchive( arc );

   arc.ReadObject( &aim );
   arc.ReadInteger( &mode );
   arc.ReadInteger( &maxshots );
   arc.ReadInteger( &numshots );
   arc.ReadBoolean( &animdone );
   }


class EXPORT_FROM_DLL Melee : public Behavior
	{
	private:
		int						mode;
		qboolean					animdone;

	public:
      CLASS_PROTOTYPE( Melee );

									Melee();
		void						SetArgs( Event *ev );
		void						AnimDone( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Melee::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.WriteInteger( mode );
   arc.WriteBoolean( animdone );
   }

inline EXPORT_FROM_DLL void Melee::Unarchive
	(
	Archiver &arc
	)
   {
   Behavior::Unarchive( arc );

   arc.ReadInteger( &mode );
   arc.ReadBoolean( &animdone );
   }

class EXPORT_FROM_DLL Repel : public Behavior
	{
	private:
		str						anim;
		float						dist;
		float						len;
		float						speed;
		Vector					goal;
		Vector					start;
		Vector					dir;
		
	public:
      CLASS_PROTOTYPE( Repel );

		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Repel::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.WriteString( anim );
   arc.WriteFloat( dist );
   arc.WriteFloat( len );
   arc.WriteFloat( speed );
   arc.WriteVector( goal );
   arc.WriteVector( start );
   arc.WriteVector( dir );
   }

inline EXPORT_FROM_DLL void Repel::Unarchive
	(
	Archiver &arc
	)
   {
   Behavior::Unarchive( arc );

   arc.ReadString( &anim );
   arc.ReadFloat( &dist );
   arc.ReadFloat( &len );
   arc.ReadFloat( &speed );
   arc.ReadVector( &goal );
   arc.ReadVector( &start );
   arc.ReadVector( &dir );
   }


class EXPORT_FROM_DLL PickupAndThrow : public Behavior
	{
	private:
		Aim						aim;
		int						mode;
		qboolean					animdone;
      EntityPtr            pickup_target;


	public:
      CLASS_PROTOTYPE( PickupAndThrow );

									PickupAndThrow();
		void						SetArgs( Event *ev );
		void						AnimDone( Event *ev );
		void						Pickup( Event *ev );
		void						Throw( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void PickupAndThrow::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.WriteObject( &aim );
   arc.WriteInteger( mode );
   arc.WriteBoolean( animdone );
   arc.WriteSafePointer( pickup_target );
   }

inline EXPORT_FROM_DLL void PickupAndThrow::Unarchive
	(
	Archiver &arc
	)
   {
   Behavior::Unarchive( arc );

   arc.ReadObject( &aim );
   arc.ReadInteger( &mode );
   arc.ReadBoolean( &animdone );
   arc.ReadSafePointer( &pickup_target );
   }

class EXPORT_FROM_DLL StrafeAttack : public Behavior
	{
	private:
		int						state;
		TurnTo					turn;

	public:
      CLASS_PROTOTYPE( StrafeAttack );

      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void StrafeAttack::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.WriteInteger( state );
   arc.WriteObject( &turn );
   }

inline EXPORT_FROM_DLL void StrafeAttack::Unarchive
	(
	Archiver &arc
	)
   {
   Behavior::Unarchive( arc );

   arc.ReadInteger( &state );
   arc.ReadObject( &turn );
   }

class EXPORT_FROM_DLL StrafeTo : public Behavior
	{
	private:
      Vector               goal;
      Seek                 seek;
      int                  fail;

	public:
      CLASS_PROTOTYPE( StrafeTo );

      void                 ShowInfo( Actor &self );
      void						SetArgs( Event *ev );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void StrafeTo::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.WriteVector( goal );
   arc.WriteObject( &seek );
   arc.WriteInteger( fail );
   }

inline EXPORT_FROM_DLL void StrafeTo::Unarchive
	(
	Archiver &arc
	)
   {
   Behavior::Unarchive( arc );

   arc.ReadVector( &goal );
   arc.ReadObject( &seek );
   arc.ReadInteger( &fail );
   }

class EXPORT_FROM_DLL Swim : public Behavior
	{
	private:
      Seek                 seek;
		ObstacleAvoidance2   avoid;
		str						anim;
      float                avoidtime;
      Vector               avoidvec;

	public:
      CLASS_PROTOTYPE( Swim );

		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Swim::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.WriteObject( &seek );
   arc.WriteObject( &avoid );
   arc.WriteString( anim );
   arc.WriteFloat( avoidtime );
   arc.WriteVector( avoidvec );
   }

inline EXPORT_FROM_DLL void Swim::Unarchive
	(
	Archiver &arc
	)
   {
   Behavior::Unarchive( arc );

   arc.ReadObject( &seek );
   arc.ReadObject( &avoid );
   arc.ReadString( &anim );
   arc.ReadFloat( &avoidtime );
   arc.ReadVector( &avoidvec );
   }

class EXPORT_FROM_DLL SwimCloseAttack : public Behavior
	{
	private:
      Seek                 seek;
		ObstacleAvoidance2   avoid;
      qboolean             avoiding;
		str						anim;
      float                avoidtime;
      Vector               avoidvec;

	public:
      CLASS_PROTOTYPE( SwimCloseAttack );

		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void SwimCloseAttack::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.WriteObject( &seek );
   arc.WriteObject( &avoid );
   arc.WriteBoolean( avoiding );
   arc.WriteString( anim );
   arc.WriteFloat( avoidtime );
   arc.WriteVector( avoidvec );
   }

inline EXPORT_FROM_DLL void SwimCloseAttack::Unarchive
	(
	Archiver &arc
	)
   {
   Behavior::Unarchive( arc );

   arc.ReadObject( &seek );
   arc.ReadObject( &avoid );
   arc.ReadBoolean( &avoiding );
   arc.ReadString( &anim );
   arc.ReadFloat( &avoidtime );
   arc.ReadVector( &avoidvec );
   }

class EXPORT_FROM_DLL Fly : public Behavior
	{
	private:
      Seek                 seek;
		ObstacleAvoidance2   avoid;
		str						anim;
      float                avoidtime;
      Vector               avoidvec;

	public:
      CLASS_PROTOTYPE( Fly );

		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Fly::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.WriteObject( &seek );
   arc.WriteObject( &avoid );
   arc.WriteString( anim );
   arc.WriteFloat( avoidtime );
   arc.WriteVector( avoidvec );
   }

inline EXPORT_FROM_DLL void Fly::Unarchive
	(
	Archiver &arc
	)
   {
   Behavior::Unarchive( arc );

   arc.ReadObject( &seek );
   arc.ReadObject( &avoid );
   arc.ReadString( &anim );
   arc.ReadFloat( &avoidtime );
   arc.ReadVector( &avoidvec );
   }

class EXPORT_FROM_DLL FlyCloseAttack : public Behavior
	{
	private:
      Seek                 seek;
		ObstacleAvoidance2   avoid;
      qboolean             avoiding;
		str						anim;
      float                avoidtime;
      Vector               avoidvec;

	public:
      CLASS_PROTOTYPE( FlyCloseAttack );

		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void FlyCloseAttack::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.WriteObject( &seek );
   arc.WriteObject( &avoid );
   arc.WriteBoolean( avoiding );
   arc.WriteString( anim );
   arc.WriteFloat( avoidtime );
   arc.WriteVector( avoidvec );
   }

inline EXPORT_FROM_DLL void FlyCloseAttack::Unarchive
	(
	Archiver &arc
	)
   {
   Behavior::Unarchive( arc );

   arc.ReadObject( &seek );
   arc.ReadObject( &avoid );
   arc.ReadBoolean( &avoiding );
   arc.ReadString( &anim );
   arc.ReadFloat( &avoidtime );
   arc.ReadVector( &avoidvec );
   }

class EXPORT_FROM_DLL Wander : public Behavior
	{
	private:
      Seek                 seek;
		ObstacleAvoidance2   avoid;
		str						anim;
      float                avoidtime;
      Vector               avoidvec;

	public:
      CLASS_PROTOTYPE( Wander );

		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Wander::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.WriteObject( &seek );
   arc.WriteObject( &avoid );
   arc.WriteString( anim );
   arc.WriteFloat( avoidtime );
   arc.WriteVector( avoidvec );
   }

inline EXPORT_FROM_DLL void Wander::Unarchive
	(
	Archiver &arc
	)
   {
   Behavior::Unarchive( arc );

   arc.ReadObject( &seek );
   arc.ReadObject( &avoid );
   arc.ReadString( &anim );
   arc.ReadFloat( &avoidtime );
   arc.ReadVector( &avoidvec );
   }


class EXPORT_FROM_DLL WanderCloseAttack : public Behavior
	{
	private:
      Seek                 seek;
		ObstacleAvoidance2   avoid;
      qboolean             avoiding;
		str						anim;
      float                avoidtime;
      Vector               avoidvec;

	public:
      CLASS_PROTOTYPE( WanderCloseAttack );

		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void WanderCloseAttack::Archive
	(
	Archiver &arc
	)
   {
   Behavior::Archive( arc );

   arc.WriteObject( &seek );
   arc.WriteObject( &avoid );
   arc.WriteBoolean( avoiding );
   arc.WriteString( anim );
   arc.WriteFloat( avoidtime );
   arc.WriteVector( avoidvec );
   }

inline EXPORT_FROM_DLL void WanderCloseAttack::Unarchive
	(
	Archiver &arc
	)
   {
   Behavior::Unarchive( arc );

   arc.ReadObject( &seek );
   arc.ReadObject( &avoid );
   arc.ReadBoolean( &avoiding );
   arc.ReadString( &anim );
   arc.ReadFloat( &avoidtime );
   arc.ReadVector( &avoidvec );
   }

class EXPORT_FROM_DLL GetCloseToEnemy : public Behavior
	{
	private:
      float                howclose;
		str						anim;
		Chase						chase;
		int						state;
		float						nextsearch;
		
	public:
      CLASS_PROTOTYPE( GetCloseToEnemy );
                        
                           GetCloseToEnemy();
		void						SetArgs( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void GetCloseToEnemy::Archive
	(
	Archiver &arc
	)

   {
   Behavior::Archive( arc );

   arc.WriteFloat( howclose );
   arc.WriteString( anim );
   arc.WriteObject( &chase );
   arc.WriteInteger( state );
   arc.WriteFloat( nextsearch );
   }

inline EXPORT_FROM_DLL void GetCloseToEnemy::Unarchive
	(
	Archiver &arc
	)

   {
   Behavior::Unarchive( arc );

   arc.ReadFloat( &howclose );
   arc.ReadString( &anim );
   arc.ReadObject( &chase );
   arc.ReadInteger( &state );
   arc.ReadFloat( &nextsearch );
   }

class EXPORT_FROM_DLL PlayAnimSeekEnemy : public Behavior
	{
	private:
		Aim						aim;
		int						mode;
		qboolean					animdone;
      str                  anim;
		str						oldanim;

	public:
      CLASS_PROTOTYPE( PlayAnimSeekEnemy );

		void						SetArgs( Event *ev );
		void						AnimDone( Event *ev );
      void                 ShowInfo( Actor &self );
		void						Begin( Actor &self );
		qboolean					Evaluate( Actor &self );
		void						End( Actor &self );
	   virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void PlayAnimSeekEnemy::Archive
	(
	Archiver &arc
	)

   {
   Behavior::Archive( arc );

   arc.WriteObject( &aim );
   arc.WriteInteger( mode );
   arc.WriteBoolean( animdone );
   arc.WriteString( anim );
   arc.WriteString( oldanim );
   }

inline EXPORT_FROM_DLL void PlayAnimSeekEnemy::Unarchive
	(
	Archiver &arc
	)

   {
   Behavior::Unarchive( arc );

   arc.ReadObject( &aim );
   arc.ReadInteger( &mode );
   arc.ReadBoolean( &animdone );
   arc.ReadString( &anim );
   arc.ReadString( &oldanim );
   }

#endif /* behavior.h */
