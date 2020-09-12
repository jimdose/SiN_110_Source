//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/specialfx.h                      $
// $Revision:: 24                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 11/15/98 11:34p                                                $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/specialfx.h                           $
// 
// 24    11/15/98 11:34p Markd
// Added constructor to projectile
// 
// 23    11/08/98 10:54p Jimdose
// fov wasn't being archived in Projectile
// 
// 22    11/07/98 10:15p Markd
// Added forcemusic support
// 
// 21    10/23/98 5:37a Jimdose
// Added SpawnBlastDamage
// 
// 20    10/12/98 5:49p Aldie
// Added activate and deactivate
// 
// 19    10/10/98 5:58p Aldie
// More quantumdestab fixes
// 
// 18    9/25/98 3:01p Aldie
// Tesselation defaults
// 
// 17    9/21/98 4:50p Markd
// Fixed projectile owner
// 
// 16    9/21/98 4:21p Markd
// Put in archive functions and rewrote all archive routines
// 
// 15    9/21/98 2:51p Aldie
// Added fx_sprite
// 
// 14    9/20/98 9:10p Aldie
// Removed a useless function
// 
// 13    9/20/98 7:30p Aldie
// Added flags to particles
// 
// 12    9/18/98 8:41p Aldie
// Added type to tesselate message
// 
// 11    9/16/98 4:03p Aldie
// Fixed targeting of beams
// 
// 10    9/15/98 7:34p Markd
// Added ChangeMusic and ChangeSoundtrack
// 
// 9     9/13/98 4:35p Aldie
// Added lots of beam stuff
// 
// 8     9/12/98 11:25p Aldie
// Consolidated beams
// 
// 7     9/11/98 11:37p Aldie
// Added activate and deactivate for beam
// 
// 6     9/10/98 8:38p Aldie
// Electrical beam effects
// 
// 5     9/09/98 3:56p Aldie
// New lightning effect
// 
// 4     8/29/98 7:24p Markd
// put in light ability on fx_fire
// 
// 3     8/29/98 7:17p Markd
// Added FireSprite and SpawnScaledExplosion
// 
// 2     8/29/98 5:27p Markd
// added specialfx, replaced misc with specialfx where appropriate
// 
// 1     8/29/98 4:39p Markd
// 
// DESCRIPTION:
// special effects
// 

#ifndef __SPECIAL_FX_H__
#define __SPECIAL_FX_H__

#include "g_local.h"
#include "entity.h"
#include "trigger.h"
#include "light.h"
#include "scriptslave.h"

void SpawnBlastDamage( trace_t *trace, int damage, Entity *attacker );
void Particles( Vector org, Vector norm, int count, int lightstyle, int flags );
void SpawnBlood( Vector org, Vector vel, int damage );
void SpawnSparks( Vector org,	Vector norm, int count );
void BurnWall( Vector org, Vector end, int amount );
void SpawnRocketExplosion( Vector org );
void SpawnScaledExplosion(	Vector org, float scale	);
void SpawnTeleportEffect( Vector org, int lightstyle );
void SpawnBeam	
   (
   Vector   start,
   Vector   end,
   int      parent_entnum,
   int      modelindex,
   float    alpha,
   float    life,
   int      flags
	);

void SpawnTempDlight
   (
   Vector org,
   float r,
   float g, 
   float b,
   float radius, 
   float decay,
   float life
	);

void TempModel
	(
   Entity * parent,
   Vector origin,
   Vector angles,
   const char * modelname, 
   int anim,
   float scale,
   float alpha, 
   int flags,
   float life
	);

void TesselateModel
	(
   Entity * ent,
   int min_size,
   int max_size,
   Vector dir,
   float power,
   float percentage,
   int thickness,
   Vector origin,
   int type=TESS_DEFAULT_TYPE,
   int lightstyle=TESS_DEFAULT_LIGHTSTYLE
   );

void ChangeMusic
	(
   const char *current,
   const char *fallback,
   qboolean force
	);

void ChangeSoundtrack
	(
   const char * soundtrack
	);

class EXPORT_FROM_DLL Bubble : public Entity
	{
	public:
      CLASS_PROTOTYPE( Bubble );

		virtual void Think( Event *ev );
		virtual void Touch( Event *ev );
 		virtual void Setup( Vector pos );
	};

class EXPORT_FROM_DLL Beam : public Entity
	{
	private:
		Vector		start;
		Vector		end;

	public:
      CLASS_PROTOTYPE( Beam );

						Beam();
		void			setBeam( Vector start, Vector end, int diameter, float r, float g, float b, float alpha, float lifespan );
      virtual void Archive( Archiver &arc );
      virtual void Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Beam::Archive
	(
	Archiver &arc
	)
   {
   Entity::Archive( arc );
   arc.WriteVector( start );
   arc.WriteVector( end );
   }

inline EXPORT_FROM_DLL void Beam::Unarchive
	(
	Archiver &arc
	)
   {
   Entity::Unarchive( arc );
   arc.ReadVector( &start );
   arc.ReadVector( &end );
   }

class EXPORT_FROM_DLL Projectile : public Entity
	{
   protected:
      int      owner;

	public:
      CLASS_PROTOTYPE( Projectile );
      float                fov;
						 Projectile();
      virtual void Setup (Entity *owner, Vector pos, Vector dir);
      virtual void Archive( Archiver &arc );
      virtual void Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Projectile::Archive
	(
	Archiver &arc
	)
   {
   Entity::Archive( arc );
   arc.WriteInteger( owner );
   arc.WriteFloat( fov );
   }

inline EXPORT_FROM_DLL void Projectile::Unarchive
	(
	Archiver &arc
	)
   {
   Entity::Unarchive( arc );
   arc.ReadInteger( &owner );
   arc.ReadFloat( &fov );
   }

class EXPORT_FROM_DLL FireSprite : public Light
	{
	public:
      CLASS_PROTOTYPE( FireSprite );

      FireSprite();
      ~FireSprite();
	};

class EXPORT_FROM_DLL FuncBeam : public ScriptSlave
	{
   protected: 
      Entity      *end;
      float       damage;
      float       life;

   public:
      CLASS_PROTOTYPE( FuncBeam );

						FuncBeam();
      void        Activate( Event *ev );
      void        Deactivate( Event *ev );
      void        SetDiameter( Event *ev );
      void        SetLightstyle( Event *ev );
      void        SetMaxoffset( Event *ev );
      void        SetMinoffset( Event *ev );
      void        SetColor( Event *ev );
      void        SetTarget( Event *ev );
      void        Shoot( Vector start, Vector end, int diameter );
      virtual void Archive( Archiver &arc );
      virtual void Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void FuncBeam::Archive
	(
	Archiver &arc
	)
   {
   ScriptSlave::Archive( arc );
   arc.WriteObjectPointer( end );
   arc.WriteFloat( damage );
   arc.WriteFloat( life );
   }

inline EXPORT_FROM_DLL void FuncBeam::Unarchive
	(
	Archiver &arc
	)
   {
   ScriptSlave::Unarchive( arc );
   arc.ReadObjectPointer( ( Class ** )&end );
   arc.ReadFloat( &damage );
   arc.ReadFloat( &life );
   }

class EXPORT_FROM_DLL Sprite : public Trigger
	{
	public:
      CLASS_PROTOTYPE( Sprite );
      Sprite();

      void        Activate( Event *ev );
      void        Deactivate( Event *ev );
	};

#endif /* specialfx.h */
