//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/eonandpeon.h                     $
// $Revision:: 5                                                              $
//   $Author:: Jimdose                                                        $
//     $Date:: 11/08/98 10:51p                                                $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/eonandpeon.h                          $
// 
// 5     11/08/98 10:51p Jimdose
// added archive functions
// 
// 4     10/27/98 3:53a Markd
// Added Killed and Chatter
// 
// 3     10/25/98 4:44a Markd
// incremental
// 
// 2     10/23/98 3:41p Markd
// incremental check in
// 
// 1     10/23/98 5:06a Markd
// 
// DESCRIPTION:
// Eon and Peon
// 

#ifndef __EONANDPEON_H__
#define __EONANDPEON_H__

#include "g_local.h"
#include "actor.h"
#include "peon.h"

class EXPORT_FROM_DLL EonAndPeon : public Peon
	{
   private:
      EntityPtr         eon;

	public:
		CLASS_PROTOTYPE( EonAndPeon );
		
								EonAndPeon::EonAndPeon();
      void              Postthink( void );
		void					Killed( Event *ev );
		virtual void		Chatter( const char *sound, float chance = 10, float volume = 1.0f, int channel = CHAN_VOICE );
	   virtual void      Archive( Archiver &arc );
      virtual void      Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void EonAndPeon::Archive
	(
	Archiver &arc
	)

   {
   Peon::Archive( arc );

   arc.WriteSafePointer( eon );
   }

inline EXPORT_FROM_DLL void EonAndPeon::Unarchive
	(
	Archiver &arc
	)

   {
   Peon::Unarchive( arc );

   arc.ReadSafePointer( &eon );
   }

#endif /* eonandpeon.h */
