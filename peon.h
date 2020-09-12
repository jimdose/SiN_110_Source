//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/peon.h                           $
// $Revision:: 3                                                              $
//   $Author:: Jimdose                                                        $
//     $Date:: 11/08/98 10:52p                                                $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/peon.h                                $
// 
// 3     11/08/98 10:52p Jimdose
// added archive functions
// 
// 2     10/23/98 10:03p Markd
// First check in
// 
// 1     10/23/98 8:20p Markd
// 
// 2     10/23/98 3:41p Markd
// incremental check in
// 
// 1     10/23/98 5:06a Markd
// 
// DESCRIPTION:
// Eon and Peon
// 

#ifndef __PEON_H__
#define __PEON_H__

#include "g_local.h"
#include "actor.h"

class EXPORT_FROM_DLL Peon : public Actor
	{
   private:
      float             gootime;

	public:
		CLASS_PROTOTYPE( Peon );
		
								Peon::Peon();
      virtual void      Prethink( void );
		virtual void		SpawnGoo( Event *ev );
	   virtual void      Archive( Archiver &arc );
      virtual void      Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Peon::Archive
	(
	Archiver &arc
	)

   {
   Actor::Archive( arc );

   arc.WriteFloat( gootime );
   }

inline EXPORT_FROM_DLL void Peon::Unarchive
	(
	Archiver &arc
	)

   {
   Actor::Unarchive( arc );

   arc.ReadFloat( &gootime );
   }

#endif /* peon.h */
