//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/explosion.h                      $
// $Revision:: 15                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 3/11/99 3:48p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/explosion.h                           $
// 
// 15    3/11/99 3:48p Aldie
// Added meansofdeath to explosion
// 
// 14    10/02/98 7:20p Aldie
// Added flashplayers to do blinding flashes
// 
// 13    9/28/98 9:12p Markd
// Put in archive and unarchive functions
// 
// 12    9/05/98 12:13p Aldie
// externed RadiusDamage
// 
// 11    9/01/98 3:05p Markd
// Rewrote explosion code
// 
// 10    6/15/98 10:39a Aldie
// Updated explosion
// 
// 9     5/25/98 7:08p Markd
// commented out some stuff
// 
// 8     4/05/98 6:42p Jimdose
// Added Exploders and MultiExploders
// 
// 7     3/23/98 1:33p Jimdose
// Revamped event and command system
// 
// 6     3/18/98 2:27p Jimdose
// Converted to work with new sin
// 
// 4     12/06/97 4:48p Markd
// Added interpretCommands. 
// Added GetArgs as commands for future processing
// Removed dmg,attentuatioin and volume, moved these to Trigger
// 
// 3     10/27/97 2:59p Jimdose
// Removed dependency on quakedef.h
// 
// 2     9/26/97 5:23p Jimdose
// Added standard Ritual headers
//
// DESCRIPTION:
// Standard explosion object that is spawned by other entites and not map designers.
// Explosion is used by many of the weapons for the blast effect, but is also used
// by the Exploder and MultiExploder triggers.  These triggers create one or more
// explosions each time they are activated.
// 

#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

#include "g_local.h"
#include "entity.h"
#include "trigger.h"

class EXPORT_FROM_DLL Exploder : public Trigger
	{
	private:
		int	damage;
		float	attenuation;
		float volume;

		virtual void MakeExplosion( Event *ev );

	public:
      CLASS_PROTOTYPE( Exploder )
		
		Exploder();
	   virtual void      Archive( Archiver &arc );
      virtual void      Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Exploder::Archive
	(
	Archiver &arc
	)
   {
   Trigger::Archive( arc );

   arc.WriteInteger( damage );
   arc.WriteFloat( attenuation );
   arc.WriteFloat( volume );
   }

inline EXPORT_FROM_DLL void Exploder::Unarchive
	(
	Archiver &arc
	)
   {
   Trigger::Unarchive( arc );

   arc.ReadInteger( &damage );
   arc.ReadFloat( &attenuation );
   arc.ReadFloat( &volume );
   }


class EXPORT_FROM_DLL MultiExploder : public Trigger
	{
	private:
		float	explodewait;
		float	explode_time;
		float duration;
		int	damage;
		float	attenuation;
		float volume;
		float randomness;

		virtual void MakeExplosion( Event *ev );

	public:
      CLASS_PROTOTYPE( MultiExploder );

		MultiExploder();
	   virtual void Archive( Archiver &arc );
      virtual void Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void MultiExploder::Archive
	(
	Archiver &arc
	)
   {
   Trigger::Archive( arc );

   arc.WriteFloat( explodewait );
   arc.WriteFloat( explode_time );
   arc.WriteFloat( duration );
   arc.WriteInteger( damage );
   arc.WriteFloat( attenuation );
   arc.WriteFloat( volume );
   arc.WriteFloat( randomness );
   }

inline EXPORT_FROM_DLL void MultiExploder::Unarchive
	(
	Archiver &arc
	)
   {
   Trigger::Unarchive( arc );

   arc.ReadFloat( &explodewait );
   arc.ReadFloat( &explode_time );
   arc.ReadFloat( &duration );
   arc.ReadInteger( &damage );
   arc.ReadFloat( &attenuation );
   arc.ReadFloat( &volume );
   arc.ReadFloat( &randomness );
   }

void CreateExplosion 
   (
   Vector pos, 
   float  damage = 120,
   float  scale = 1.0f, 
   qboolean bigexplosion = true,
   Entity *inflictor = NULL,
   Entity *attacker = NULL,
   Entity *ignore = NULL, 
	int    meansofdeath = MOD_ROCKETSPLASH,
   float  volume = 1.0f,
   float  attenuation = ATTN_NORM,
   float  r = 1.0f,
   float  g = 0.2f,
   float  b = 0.0f,
   float  light_radius = 240,
   float  life = 1,
   float  decay = 0.95
   );

void RadiusDamage
	(
	Entity *inflictorent, 
	Entity *attackerent, 
	int damage, 
	Entity *ignoreent,
   int mod
	);

void FlashPlayers
   (
   Vector org,
   float r,
   float g, 
   float b,
   float a,
   float rad
   );

#endif /* explosion.h */
