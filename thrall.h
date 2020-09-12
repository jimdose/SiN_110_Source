//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/thrall.h                         $
// $Revision:: 6                                                              $
//   $Author:: Aldie                                                          $
//     $Date:: 11/08/98 8:30p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/thrall.h                              $
// 
// 6     11/08/98 8:30p Aldie
// Added gibfest for thrall
// 
// 5     10/27/98 10:17p Jimdose
// better aiming by walls
// more damage from pulse
// precached models
// 
// 4     10/27/98 5:56a Jimdose
// added Chatter
// 
// 3     10/27/98 3:52a Jimdose
// got pulse weapon working
// 
// 2     10/23/98 5:37a Jimdose
// Created file
// 
// 1     10/22/98 10:19p Jimdose
// 
// DESCRIPTION:
// ThrallMaster
// 

#ifndef __THRALLMASTER_H__
#define __THRALLMASTER_H__

#include "g_local.h"
#include "actor.h"
#include "specialfx.h"

class EXPORT_FROM_DLL ThrallMaster : public Actor
	{
   protected:
      weaponmode_t      weaponmode;
      str               gunbone;

	public:
		CLASS_PROTOTYPE( ThrallMaster );
		
								ThrallMaster();
      virtual Vector    GunPosition( void );
      virtual qboolean  CanShootFrom( Vector pos, Entity *ent, qboolean usecurrentangles );
		virtual void		Chatter( const char *sound, float chance = 10, float volume = 1.0f, int channel = CHAN_VOICE );
      virtual void		WeaponUse( Event *ev );
		virtual void		FirePulse( Event *ev );
		virtual void		FireRockets( Event *ev );
		virtual void		GibFest( Event *ev );
      virtual void      Archive(	Archiver &arc );
      virtual void      Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void ThrallMaster::Archive
	(
	Archiver &arc
	)

   {
   Actor::Archive( arc );

   arc.WriteInteger( weaponmode );
   arc.WriteString( gunbone );
   }


inline EXPORT_FROM_DLL void ThrallMaster::Unarchive
	(
	Archiver &arc
	)

   {
   Actor::Unarchive( arc );

   weaponmode = ( weaponmode_t )arc.ReadInteger();
   arc.ReadString( &gunbone );
   }

class EXPORT_FROM_DLL ThrallGun : public Weapon
	{
	public:
		CLASS_PROTOTYPE( ThrallGun );

                        ThrallGun();
		virtual void		Shoot( Event *ev );
      virtual void      SecondaryUse( Event *ev );
	};

class EXPORT_FROM_DLL DrunkMissile : public Projectile
	{
	private:
		EntityPtr target;

	public:
		CLASS_PROTOTYPE( DrunkMissile );

		float	         AdjustAngle( float maxadjust, float currangle, float targetangle );
		void	         Explode( Event *ev );
		float	         ResolveMinimumDistance( Entity *potential_target, float currmin );
		void	         HeatSeek( Event *ev);
		void	         Prethink( void );
		void	         Setup( Entity *owner, Vector pos, Vector dir );
      virtual void   Archive( Archiver &arc );
      virtual void   Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void DrunkMissile::Archive
	(
	Archiver &arc
	)

   {
   Projectile::Archive( arc );

   arc.WriteSafePointer( target );
   }

inline EXPORT_FROM_DLL void DrunkMissile::Unarchive
	(
	Archiver &arc
	)

   {
   Projectile::Unarchive( arc );

   arc.ReadSafePointer( &target );
   }

class EXPORT_FROM_DLL ThrallPulse : public Projectile
	{
	public:
		CLASS_PROTOTYPE( ThrallPulse );

		void	   Explode( Event *ev );
		void	   Setup( Entity *owner, Vector pos, Vector dir );
	};

class EXPORT_FROM_DLL ThrallPulseDebris : public Projectile
	{
   private:
      float    size;
      float    spawntime;
      float    nexttouch;

	public:
		CLASS_PROTOTYPE( ThrallPulseDebris );

		void	   Touch( Event *ev );
      void     Prethink( void );
		void	   Setup( Entity *owner, Vector pos, float size );
      virtual void   Archive( Archiver &arc );
      virtual void   Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void ThrallPulseDebris::Archive
	(
	Archiver &arc
	)

   {
   Projectile::Archive( arc );

   arc.WriteFloat( size );
   arc.WriteFloat( spawntime );
   arc.WriteFloat( nexttouch );
   }


inline EXPORT_FROM_DLL void ThrallPulseDebris::Unarchive
	(
	Archiver &arc
	)

   {
   Projectile::Unarchive( arc );

   arc.ReadFloat( &size );
   arc.ReadFloat( &spawntime );
   arc.ReadFloat( &nexttouch );
   }

#endif /* thrall.h */
