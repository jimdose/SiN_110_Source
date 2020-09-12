//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/deadbody.h                       $
// $Revision:: 5                                                              $
//   $Author:: Jimdose                                                        $
//     $Date:: 11/18/98 9:18p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/deadbody.h                            $
// 
// 5     11/18/98 9:18p Jimdose
// lowered number of bodies to 4
// 
// 4     11/11/98 11:13p Aldie
// Made deadbodies blood and gib properly
// 
// 3     8/29/98 9:48p Jimdose
// Added bodyqueue code to deadbody
// 
// 2     7/13/98 5:01p Aldie
// Added dead player bodies with gibbing
//
// DESCRIPTION:
// Dead body

#ifndef __DEADBODY_H__
#define __DEADBODY_H__

#include "g_local.h"
#include "sentient.h"

#define BODY_QUEUE_SIZE		4

EXPORT_FROM_DLL void InitializeBodyQueue( void );
EXPORT_FROM_DLL void CopyToBodyQueue( edict_t *ent );

class EXPORT_FROM_DLL Deadbody : public Sentient
	{
	public:
      CLASS_PROTOTYPE( Deadbody );
   
      virtual void   GibEvent( Event *ev );
	};

#endif /* deadbody.h */
