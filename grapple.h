//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/grapple.h                        $
// $Revision:: 1                                                              $
//   $Author:: Aldie                                                          $
//     $Date:: 3/02/99 9:24p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/grapple.h                             $
// 
// 1     3/02/99 9:24p Aldie
// 
// 2     2/16/99 4:08p Aldie
// 
// 1     2/11/99 1:38p Aldie
// 
// 2     2/10/99 9:35p Aldie
// First Version
//
// DESCRIPTION:
// Grappling Hook

#ifndef __GRAPPLE_H__
#define __GRAPPLE_H__

#include "g_local.h"
#include "item.h"
#include "weapon.h"
#include "specialfx.h"

class EXPORT_FROM_DLL Hook : public Projectile
	{
   private:
      float					speed;

	public:
		CLASS_PROTOTYPE( Hook );

		void					Setup( Entity *owner, Vector pos, Vector dir );
	   virtual void      Archive( Archiver &arc );
      virtual void      Unarchive( Archiver &arc );
		virtual void      Touch( Event *ev );
	};

inline EXPORT_FROM_DLL void Hook::Archive
	(
	Archiver &arc
	)
   {
   Projectile::Archive( arc );

   arc.WriteFloat( speed );
   }

inline EXPORT_FROM_DLL void Hook::Unarchive
	(
	Archiver &arc
	)
   {
   Projectile::Unarchive( arc );

   arc.ReadFloat( &speed );
   }

typedef SafePtr<Hook> HookPtr;
typedef SafePtr<Beam> BeamPtr;

class EXPORT_FROM_DLL Grapple : public Weapon
	{
	private:
		HookPtr				hook;
		BeamPtr           beam;

	public:
		CLASS_PROTOTYPE( Grapple );
		
								Grapple();
								~Grapple();
		virtual void		Shoot( Event *ev );
		virtual qboolean  HasAmmo( void );
		virtual void      ReleaseFire( float t );
		virtual void      UpdateBeam( Event *ev );
	};


#endif /* grapple.h */