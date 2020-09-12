//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/fists.h                             $
// $Revision:: 7                                                              $
//   $Author:: Aldie                                                          $
//     $Date:: 10/11/98 5:34p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/fists.h                                  $
// 
// 7     10/11/98 5:34p Aldie
// Added meansofdeath
// 
// 6     9/28/98 9:12p Markd
// Put in archive and unarchive functions
// 
// 5     6/10/98 10:02p Markd
// put reach and damage into fists
// 
// 4     5/25/98 1:08a Markd
// Made fists a Weapon, not a BulletWeapon
// 
// 3     5/20/98 10:43p Markd
// made fists into bullets!
// 
// 2     5/11/98 11:25a Markd
// First time
// 
// 1     5/11/98 10:28a Markd
// 
// 1     5/11/98 10:20a Markd
// 
// 1     5/11/98 10:18a Markd
// 
// 1     5/11/98 9:55a Markd
// 
// DESCRIPTION:
// Mutant Hands
// 

#ifndef __FISTS_H__
#define __FISTS_H__

#include "g_local.h"
#include "item.h"
#include "weapon.h"

class EXPORT_FROM_DLL Fists : public Weapon
	{
	public:
      float             strike_reach;
      float             strike_damage;
      int               meansofdeath;

		CLASS_PROTOTYPE( Fists );
		
								Fists::Fists();
		virtual void		Shoot( Event *ev );
	   virtual void      Archive( Archiver &arc );
      virtual void      Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Fists::Archive
	(
	Archiver &arc
	)
   {
   Weapon::Archive( arc );

   arc.WriteFloat( strike_reach );
   arc.WriteFloat( strike_damage );
   arc.WriteInteger( meansofdeath );
   }

inline EXPORT_FROM_DLL void Fists::Unarchive
	(
	Archiver &arc
	)
   {
   Weapon::Unarchive( arc );

   arc.ReadFloat( &strike_reach );
   arc.ReadFloat( &strike_damage );
   arc.ReadInteger( &meansofdeath );
   }

#endif /* Fists.h */
