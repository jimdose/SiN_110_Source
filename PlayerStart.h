//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/PlayerStart.h                    $
// $Revision:: 10                                                             $
//   $Author:: Jimdose                                                        $
//     $Date:: 12/10/98 1:45p                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/PlayerStart.h                         $
// 
// 10    12/10/98 1:45p Jimdose
// added ProgressiveStart
// 
// 9     8/08/98 7:30p Aldie
// Added intermissions for deathmatch
// 
// 8     3/02/98 8:49p Jimdose
// Changed CLASS_PROTOTYPE to only take the classname
// 
// 7     2/04/98 4:34p Jimdose
// Moved Sined headers to .cpp file
// 
// 6     2/03/98 10:51a Jimdose
// Updated to work with Quake 2 engine
// Moved initialization to constructor and removed Init function
// 
// 5     1/23/98 3:04p Jimdose
// Made compatible with Q2 based progs
// 
// 3     10/27/97 2:46p Jimdose
// Removed dependency on quakedef.h
// 
// 2     9/26/97 6:47p Jimdose
// Added standard Ritual headers
//
// DESCRIPTION:
// Player start location entity declarations
// 

#ifndef __PLAYERSTART_H__
#define __PLAYERSTART_H__

#include "g_local.h"
#include "entity.h"
#include "camera.h"

class EXPORT_FROM_DLL PlayerStart : public Entity
	{
	public:
      CLASS_PROTOTYPE( PlayerStart );
		
		PlayerStart::PlayerStart();
	};

class EXPORT_FROM_DLL ProgressiveStart : public PlayerStart
	{
	public:
      CLASS_PROTOTYPE( ProgressiveStart );
		
		      ProgressiveStart();
      void  SetSpawnpoint( Event *ev );   
	};

class EXPORT_FROM_DLL TestPlayerStart : public PlayerStart
	{
	public:
		CLASS_PROTOTYPE( TestPlayerStart );
	};

class EXPORT_FROM_DLL PlayerDeathmatchStart : public PlayerStart
	{
	public:
		CLASS_PROTOTYPE( PlayerDeathmatchStart );
	};

class EXPORT_FROM_DLL PlayerCoopStart : public PlayerStart
	{
	public:
		CLASS_PROTOTYPE( PlayerCoopStart );
	};

class EXPORT_FROM_DLL PlayerIntermission : public Camera
	{
	public:
		CLASS_PROTOTYPE( PlayerIntermission );
      PlayerIntermission();
	};

#endif /* PlayerStart.h */
