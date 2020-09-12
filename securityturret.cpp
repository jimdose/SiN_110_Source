//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/securityturret.cpp               $
// $Revision:: 25                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 9/19/98 6:13p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/securityturret.cpp                    $
// 
// 25    9/19/98 6:13p Aldie
// Made wakeupdistance and firingdistance spawn args
// 
// 24    9/15/98 6:45p Aldie
// Fixed some stuff for Richard
// 
// 23    9/11/98 3:52p Aldie
// Put in wakeupdistance and firingdistance
// 
// 22    7/07/98 4:11p Aldie
// Updated to new class hierarchy
// 
// 21    6/24/98 12:39p Markd
// Added default tesselation percentage
// 
// 20    6/18/98 2:00p Markd
// rewrote tesselation code
// 
// 19    5/24/98 1:04a Jimdose
// Added sound events for ai
// 
// 18    5/13/98 4:57p Jimdose
// Startup event is now posted 0 in the future
// 
// 17    5/11/98 2:19p Markd
// Fixed randomsound stuff
// 
// 16    5/09/98 7:11p Markd
// Removed sound parameter from tesselate command
// 
// 15    5/03/98 4:37p Jimdose
// Changed Vector class
// 
// 14    5/01/98 11:09a Markd
// Added sound to tesselation event
// 
// 13    4/18/98 5:45p Markd
// Removed SINED calls, because they are now in DEF file format
// 
// 12    4/14/98 6:56p Markd
// Added thickness to tesselation
// 
// 11    4/10/98 4:53p Jimdose
// no longer binding base to top
// 
// 10    4/10/98 1:23a Markd
// Added FL_SPARKS as its default
// 
// 9     4/10/98 12:35a Jimdose
// made turret "New and Improved!"
// 
// 8     4/09/98 7:37p Markd
// 
// 7     4/08/98 4:22p Jimdose
// Getting ready to conver to Q2
// 
// 5     12/14/97 4:23p Jimdose
// Changed from monster_turret to trap_securityturret
// 
// 4     12/13/97 6:00p Jimdose
// Changed the base from a Sentient to an Entity
// 
// 3     12/13/97 3:47p Jimdose
// Finished implementing behaviour
// 
// 2     12/09/97 3:00p Jimdose
// Created file
//
// DESCRIPTION:
// Security turret.  Senses when player is near and raises up, searches for player,
// and fires.  When player is dead or not near, it lowers down and goes back to
// sleep.
// 

#include "securityturret.h"

CLASS_DECLARATION( Turret, TurretTop, "trap_securityturret" )

ResponseDef TurretTop::Responses[] =
	{
		{ NULL, NULL }
	};

TurretTop::TurretTop
	(
	void
	)

	{
	setModel( "turtop.def" );
	setSize( "-16 -16 0", "16 16 26" );
	RandomAnimate( "down_idle", NULL );

   gunoffset      = "0 0 0";

	neworientation = angles.yaw();

	setMoveType( MOVETYPE_NONE );
	setSolidType( SOLID_BBOX );

   health         = G_GetFloatArg( "health", 100 );
   takedamage     = DAMAGE_YES;
   flags         |= FL_SPARKS;

   wakeupdistance = G_GetFloatArg( "wakeupdistance", 750 );
   firingdistance = G_GetFloatArg( "firingdistance", 800 );

	SetupBase();
	}

void TurretTop::SetupBase
	(
   void
   )

	{
	TurretBase *baseptr;

	baseptr = new TurretBase;
	baseptr->setOrigin( worldorigin );

	base = baseptr->entnum;
	}

CLASS_DECLARATION( Entity, TurretBase, NULL )

ResponseDef TurretBase::Responses[] =
	{
	   { &EV_Turret_GoUp,	( Response )TurretBase::GoUp },
	   { &EV_Turret_GoDown,	( Response )TurretBase::GoDown },
		{ NULL, NULL }
	};

TurretBase::TurretBase()
	{
	setModel( "turbase.def" );
	setSize( "-16 -16 0", "16 16 1" );
	setMoveType( MOVETYPE_NONE );
	setSolidType( SOLID_BBOX );
	RandomAnimate( "down_idle", NULL );
   takedamage = DAMAGE_NO;
	}

void TurretBase::GoUp
	(
	Event *ev
	)

	{
	RandomAnimate( "raise", NULL );
	}

void TurretBase::GoDown
	(
	Event *ev
	)

	{
	RandomAnimate( "lower", NULL );
	}
