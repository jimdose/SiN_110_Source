//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/misc.h                           $
// $Revision:: 71                                                             $
//   $Author:: Jimdose                                                        $
//     $Date:: 11/11/98 10:02p                                                $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/misc.h                                $
// 
// 71    11/11/98 10:02p Jimdose
// added ClipBox
// 
// 70    10/17/98 8:12p Jimdose
// Changed Damage to DamgeEvent
// 
// 69    10/14/98 12:13a Aldie
// Proto for intermission
// 
// 68    10/09/98 4:34p Aldie
// Added OnSameTeam
// 
// 67    10/07/98 11:53p Jimdose
// Added BloodSplat
// 
// 66    10/06/98 10:52p Aldie
// Created an oxygenator
// 
// 65    10/05/98 11:23p Markd
// Added MadeBreakingSound
// 
// 64    9/28/98 9:12p Markd
// Put in archive and unarchive functions
// 
// 63    9/18/98 8:14p Markd
// rewrote surface system so that surfaces are now damaged by surface name
// instead of by surfinfo
// 
// 62    8/29/98 5:27p Markd
// added specialfx, replaced misc with specialfx where appropriate
// 
// 61    8/29/98 2:53p Aldie
// Updated printing of location based damage
// 
// 60    8/29/98 12:59p Markd
// Fixed func_explodingwall stuff
// 
// 59    8/24/98 5:44p Aldie
// Added fov to projectiles
// 
// 58    8/19/98 8:50p Aldie
// Added randomparticles
// 
// 57    8/17/98 4:35p Markd
// Added SendOverlay
// 
// 56    8/08/98 8:51p Aldie
// Added func_spawnchain and changed spawns to entities
// 
// 55    8/08/98 6:24p Aldie
// Added spawnoutofsight
// 
// 54    8/04/98 5:56p Markd
// Added FuncRemove
// 
// 53    7/21/98 4:23p Aldie
// Make icons work for locks
// 
// 52    7/17/98 6:08p Aldie
// Added spawntargetname to func_spawn
// 
// 51    7/15/98 6:18p Markd
// re-ordered SpawnTempDlight arguments
// 
// 50    7/13/98 5:01p Aldie
// Added dead player bodies with gibbing
// 
// 49    7/11/98 2:49p Markd
// Added SendDialog event
// 
// 48    7/10/98 4:11p Markd
// Revamped func_explodingwall
// 
// 47    7/08/98 3:12p Aldie
// Added func_respawn
// 
// 46    7/02/98 7:57p Markd
// Redid func_explodingwall and func_glass
// 
// 45    6/30/98 4:37p Markd
// Added noise to func_glass and func_shatter
// 
// 44    6/24/98 4:51p Aldie
// Updated func_spawn
// 
// 43    6/24/98 12:38p Markd
// SpawnParticles conflicted with the entity function of the same name
// 
// 42    6/24/98 12:23p Markd
// Added SpawnParticles
// 
// 41    6/18/98 2:00p Markd
// rewrote tesselation code
// 
// 40    6/15/98 12:25p Aldie
// Updated pulse beam parms
// 
// 39    6/15/98 10:39a Aldie
// Added SpawnPulseBeam
// 
// 38    6/08/98 7:23p Aldie
// Added DamageSurfaceByName
// 
// 37    5/28/98 1:26p Aldie
// Added rocket explosion particles
// 
// 36    5/27/98 4:54p Markd
// Changed Smoke Setup method
// 
// 35    5/26/98 9:27p Aldie
// Typo
// 
// 34    5/26/98 9:26p Aldie
// Added func_spawn
// 
// 33    5/25/98 12:22p Aldie
// Added func_electrocute
// 
// 32    5/25/98 7:15p Markd
// Changed TempModel stuff
// 
// 31    5/25/98 5:42p Markd
// Added SpawnDlight and fixed other stuff
// 
// 30    5/23/98 10:38p Markd
// Added TempModel call
// 
// 29    5/20/98 1:32p Markd
// changed func_shatter a bit
// 
// 28    5/13/98 6:22p Markd
// Added BurnWall
// 
// 27    5/05/98 8:38p Aldie
// Added virtual setup to Projectile.
// 
// 26    5/05/98 5:35p Aldie
// Updated damage surfaces
// 
// 25    5/03/98 8:12p Markd
// Added SpawnSparks call
// 
// 24    4/18/98 2:32p Jimdose
// Added ExplodingWall, Shatter, and Glass
// 
// 23    4/07/98 11:55p Jimdose
// SetBeam now accepts r, g, b, and alpha for color
// 
// 22    4/04/98 6:13p Jimdose
// Added Bubble, Smoke, and Projectile
// 
// 21    3/30/98 2:39p Jimdose
// Made teleporters handle non-clients
// 
// 20    3/29/98 9:39p Jimdose
// Changed killed to a damage event
// 
// 19    3/28/98 6:37p Jimdose
// Made teleporters work
// 
// 18    3/23/98 1:33p Jimdose
// Revamped event and command system
// 
// 17    3/11/98 2:23p Jimdose
// Moved AreaPortals to areaportal.cpp
// 
// 16    3/05/98 3:49p Aldie
// More support for damage surfaces.
// 
// 15    3/04/98 8:00p Aldie
// More support for damage surfaces.
// 
// 14    3/02/98 8:49p Jimdose
// Changed CLASS_PROTOTYPE to only take the classname
// 
// 13    3/02/98 5:42p Jimdose
// Moved light entities to light.cpp
// 
// 12    2/27/98 12:50p Jimdose
// Added Light, LightRamp, and TriggerLightStyle
// 
// 11    2/21/98 1:07p Jimdose
// Added Beam class
// 
// 10    2/06/98 5:43p Jimdose
// Added Teleporter and AreaPortal.
// Added constructor to Detail
// 
// 8     2/03/98 10:43a Jimdose
// Updated to work with Quake 2 engine
// 
// 6     10/31/97 4:26p Jimdose
// Removed owner from HackThinker since it was already defined in Entity
// 
// 5     10/28/97 8:20p Jimdose
// added Bubble
// 
// 4     10/27/97 2:59p Jimdose
// Removed dependency on quakedef.h
// 
// 3     10/01/97 11:25a Markd
// moved viewthing to its own file
// 
// 2     9/26/97 6:14p Jimdose
// Added standard Ritual headers
//
// DESCRIPTION:
// Basically the big stew pot of the DLLs, or maybe a garbage bin, whichever
// metaphore you prefer.  This really should be cleaned up.  Anyway, this
// should contain utility functions that could be used by any entity.
// Right now it contains everything from entities that could be in their
// own file to my mother pot roast recipes.
// 

#ifndef __MISC_H__
#define __MISC_H__

#include "g_local.h"
#include "entity.h"
#include "trigger.h"
#include "queue.h"

void SendOverlay
	(
   Entity *ent,
   str overlayname
	);

void SendIntermission
	(
   Entity *ent,
   str intermissionname
	);

void SendDialog
	(
   const char *icon_name,
   const char *dialog_text
	);

const char *ExpandLocation
   (
   const char *location
   );

void MadeBreakingSound
	(
   Vector pos,
   Entity * activator
	);

qboolean OnSameTeam
   (
   Entity *ent1,
   Entity *ent2
   );

class EXPORT_FROM_DLL InfoNull : public Entity
	{
	public:
      CLASS_PROTOTYPE( InfoNull );
		
		InfoNull();
	};

class EXPORT_FROM_DLL FuncRemove : public Entity
	{
	public:
      CLASS_PROTOTYPE( FuncRemove );
		
		FuncRemove();
	};

class EXPORT_FROM_DLL InfoNotNull : public Entity
	{
	public:
      CLASS_PROTOTYPE( InfoNotNull );
	};

class EXPORT_FROM_DLL Wall : public Entity
	{
	private:

	public:
      CLASS_PROTOTYPE( Wall );

		Wall();
	};

class EXPORT_FROM_DLL IllusionaryWall : public Entity
	{
	private:

	public:
      CLASS_PROTOTYPE( IllusionaryWall );
		IllusionaryWall();
	};

class EXPORT_FROM_DLL BreakawayWall : public TriggerOnce
	{
	private:

	public:
      CLASS_PROTOTYPE( BreakawayWall );

		void	BreakWall( Event *ev );
		void	Setup( Event *ev );
				BreakawayWall();
	};

class EXPORT_FROM_DLL ExplodingWall : public Trigger
	{
	protected:
		int      dmg;
		int      explosions;
		float    attack_finished;
      Vector   land_angles;
      float    land_radius;
      float    angle_speed;
      int      state;
      Vector   orig_mins, orig_maxs;
      qboolean on_ground;

	public:
      CLASS_PROTOTYPE( ExplodingWall );

							ExplodingWall();
      virtual void   SetupSecondStage( void );
		virtual void	Explode( Event *ev );
		virtual void	DamageEvent( Event *ev );
		virtual void	GroundDamage( Event *ev );
		virtual void	TouchFunc( Event *ev );
		virtual void	StopRotating( Event *ev );
		virtual void	CheckOnGround( Event *ev );
	   virtual void   Archive( Archiver &arc );
      virtual void   Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void ExplodingWall::Archive
	(
	Archiver &arc
	)
   {
   Trigger::Archive( arc );

   arc.WriteInteger( dmg );
   arc.WriteInteger( explosions );
   arc.WriteFloat( attack_finished );
   arc.WriteVector( land_angles );
   arc.WriteFloat( land_radius );
   arc.WriteFloat( angle_speed );
   arc.WriteInteger( state );
   arc.WriteVector( orig_mins );
   arc.WriteVector( orig_maxs );
   arc.WriteBoolean( on_ground );
   }

inline EXPORT_FROM_DLL void ExplodingWall::Unarchive
	(
	Archiver &arc
	)
   {
   Trigger::Unarchive( arc );

   arc.ReadInteger( &dmg );
   arc.ReadInteger( &explosions );
   arc.ReadFloat( &attack_finished );
   arc.ReadVector( &land_angles );
   arc.ReadFloat( &land_radius );
   arc.ReadFloat( &angle_speed );
   arc.ReadInteger( &state );
   arc.ReadVector( &orig_mins );
   arc.ReadVector( &orig_maxs );
   arc.ReadBoolean( &on_ground );
   }

class EXPORT_FROM_DLL Electrocute : public Trigger
	{
   private:
      float radius;
      
	public:
      CLASS_PROTOTYPE( Electrocute );

							Electrocute();
		virtual void	KillSight( Event *ev );
	   virtual void   Archive( Archiver &arc );
      virtual void   Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Electrocute::Archive
	(
	Archiver &arc
	)
   {
   Trigger::Archive( arc );

   arc.WriteFloat( radius );
   }

inline EXPORT_FROM_DLL void Electrocute::Unarchive
	(
	Archiver &arc
	)
   {
   Trigger::Unarchive( arc );

   arc.ReadFloat( &radius );
   }


class EXPORT_FROM_DLL Detail : public Wall
	{
	public:
      CLASS_PROTOTYPE( Detail );

		Detail();
	};

class EXPORT_FROM_DLL Teleporter : public Trigger
	{
	public:
      CLASS_PROTOTYPE( Teleporter );
		
								Teleporter();
		virtual void		Teleport( Event *ev );
	};

class EXPORT_FROM_DLL TeleporterDestination : public Entity
	{
	public:
		Vector				movedir;

      CLASS_PROTOTYPE( TeleporterDestination );

						TeleporterDestination();
	   virtual void      Archive( Archiver &arc );
      virtual void      Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void TeleporterDestination::Archive
	(
	Archiver &arc
	)
   {
   Entity::Archive( arc );

   arc.WriteVector( movedir );
   }

inline EXPORT_FROM_DLL void TeleporterDestination::Unarchive
	(
	Archiver &arc
	)
   {
   Entity::Unarchive( arc );

   arc.ReadVector( &movedir );
   }

class EXPORT_FROM_DLL Waypoint : public Entity
	{
	public:
      CLASS_PROTOTYPE( Waypoint );
	};

class EXPORT_FROM_DLL Shatter : public DamageThreshold
	{
   protected:
      qboolean       threshold;
      str            noise;
	public:
      CLASS_PROTOTYPE( Shatter );

		virtual void	DamageEvent( Event *ev );
		virtual void	DoShatter( Event *ev );
							Shatter();
	   virtual void   Archive( Archiver &arc );
      virtual void   Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Shatter::Archive
	(
	Archiver &arc
	)
   {
   DamageThreshold::Archive( arc );

   arc.WriteBoolean( threshold );
   arc.WriteString( noise );
   }

inline EXPORT_FROM_DLL void Shatter::Unarchive
	(
	Archiver &arc
	)
   {
   DamageThreshold::Unarchive( arc );

   arc.ReadBoolean( &threshold );
   arc.ReadString( &noise );
   }

class EXPORT_FROM_DLL Glass : public Shatter
	{
	public:
      CLASS_PROTOTYPE( Glass );
							Glass();
	};

class EXPORT_FROM_DLL Spawn : public Entity
	{
   protected:
  		str      modelname;
      str      spawntargetname;
      int      attackmode;

	public:
      CLASS_PROTOTYPE( Spawn );

		virtual void	DoSpawn( Event *ev );
							Spawn();
	   virtual void   Archive( Archiver &arc );
      virtual void   Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Spawn::Archive
	(
	Archiver &arc
	)
   {
   Entity::Archive( arc );

   arc.WriteString( modelname );
   arc.WriteString( spawntargetname );
   arc.WriteInteger( attackmode );
   }

inline EXPORT_FROM_DLL void Spawn::Unarchive
	(
	Archiver &arc
	)
   {
   Entity::Unarchive( arc );

   arc.ReadString( &modelname );
   arc.ReadString( &spawntargetname );
   arc.ReadInteger( &attackmode );
   }

class EXPORT_FROM_DLL ReSpawn : public Spawn
	{
 	public:
      CLASS_PROTOTYPE( ReSpawn );

		virtual void	DoSpawn( Event *ev );
	};

class EXPORT_FROM_DLL SpawnOutOfSight : public Spawn
	{
 	public:
      CLASS_PROTOTYPE( SpawnOutOfSight );

		virtual void	DoSpawn( Event *ev );
	};

class EXPORT_FROM_DLL SpawnChain : public Spawn
	{
 	public:
      CLASS_PROTOTYPE( SpawnChain );

		virtual void	DoSpawn( Event *ev );
	};

class EXPORT_FROM_DLL Oxygenator : public Trigger
	{
   private:
      float             time;

   public:
      CLASS_PROTOTYPE( Oxygenator );
		
							Oxygenator();
		virtual void   Oxygenate( Event *ev );
	   virtual void   Archive( Archiver &arc );
      virtual void   Unarchive( Archiver &arc );
   };

inline EXPORT_FROM_DLL void Oxygenator::Archive
	(
	Archiver &arc
	)
   {
   Trigger::Archive( arc );

   arc.WriteFloat( time );
   }

inline EXPORT_FROM_DLL void Oxygenator::Unarchive
	(
	Archiver &arc
	)
   {
   Trigger::Unarchive( arc );

   arc.ReadFloat( &time );
   }

class EXPORT_FROM_DLL BloodSplat : public Entity
	{
   private:
      // No archive function is declared since the class automaintains itself.
      // Just spawning and freeing maintains the queue.

      static int     numBloodSplats;
      static Queue   queueBloodSplats;

 	public:
      CLASS_PROTOTYPE( BloodSplat );

                     BloodSplat( Vector pos = "0 0 0", Vector ang = "0 0 0", float scale = 1 );
                     ~BloodSplat();
	};

class EXPORT_FROM_DLL ClipBox : public Entity
	{
 	public:
      CLASS_PROTOTYPE( ClipBox );

                     ClipBox();
	};

#endif /* misc.h */
