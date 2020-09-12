//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/gibs.h                           $
// $Revision:: 8                                                              $
//   $Author:: Aldie                                                          $
//     $Date:: 11/08/98 8:30p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/gibs.h                                $
// 
// 8     11/08/98 8:30p Aldie
// Added ability to not fade splats
// 
// 7     9/28/98 9:12p Markd
// Put in archive and unarchive functions
// 
// 6     9/22/98 5:19p Markd
// Put in new consolidated gib function
// 
// 5     9/20/98 5:13p Aldie
// Added blood trail to gib
// 
// 4     8/10/98 6:53p Aldie
// Changed the gib throwing
// 
// 3     7/29/98 2:32p Aldie
// Changed health to a float
// 
// 2     5/27/98 5:04a Aldie
// First version of gibs
//
// DESCRIPTION:
// Gibs - nuff said

#ifndef __GIBS_H__
#define __GIBS_H__

#include "g_local.h"

class EXPORT_FROM_DLL Gib : public Entity
   {
   private:
      qboolean sprayed;
   public:
      CLASS_PROTOTYPE( Gib );

      qboolean    fadesplat;
      Gib();
      Gib(const char *name, qboolean blood_trail=true);
      void     SetVelocity( float health );
      void     SprayBlood( Vector start, Vector end, int damage );
      void     Throw(Event *ev);
      void     Splat(Event *ev);
      void     ClipGibVelocity( void );
	   virtual void Archive( Archiver &arc );
      virtual void Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Gib::Archive
	(
	Archiver &arc
	)
   {
   Entity::Archive( arc );

   arc.WriteBoolean( sprayed );
   arc.WriteBoolean( fadesplat );
   }

inline EXPORT_FROM_DLL void Gib::Unarchive
	(
	Archiver &arc
	)
   {
   Entity::Unarchive( arc );

   arc.ReadBoolean( &sprayed );
   arc.ReadBoolean( &fadesplat );
   }

void CreateGibs
   ( 
   Entity * ent, 
   float damage = -50, 
   float scale = 1.0f, 
   int num = 1, 
   const char * modelname = NULL
   );

extern Event EV_ThrowGib;

#endif // gibs.h