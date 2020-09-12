//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/lensflare.h                      $
// $Revision:: 9                                                              $
//   $Author:: Aldie                                                          $
//     $Date:: 10/09/98 9:02p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/lensflare.h                           $
// 
// 9     10/09/98 9:02p Aldie
// Lightstyle on lensflare from Lights
// 
// 8     10/09/98 5:23p Aldie
// Added some new commands (lightstyle)
// 
// 7     9/28/98 9:12p Markd
// Put in archive and unarchive functions
// 
// 6     9/25/98 3:00p Aldie
// Prototypes
// 
// 5     3/23/98 1:33p Jimdose
// Revamped event and command system
// 
// 4     3/13/98 7:25p Aldie
// Updated lensflare to have dlights, color, and radius.
// 
// 3     3/10/98 7:45p Aldie
// 
// 2     3/06/98 7:16p Aldie
// First try at LensFlare.
//
// DESCRIPTION:LensFlare effect
// 

#ifndef __LENSFLARE_H__
#define __LENSFLARE_H__

#include "g_local.h"
#include "entity.h"


class EXPORT_FROM_DLL LensFlare : public Entity
	{
	public:
      CLASS_PROTOTYPE( LensFlare );
      LensFlare( void );

      void        Activate( Event *ev );
      void        Deactivate( Event *ev );
      void        Lightstyle( Event *ev );
      void        SetLightstyle( Event *ev );
   };


#endif /* lensflare.h */
