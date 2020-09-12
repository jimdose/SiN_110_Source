//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/mover.cpp                        $
// $Revision:: 18                                                             $
//   $Author:: Jimdose                                                        $
//     $Date:: 10/24/98 8:30p                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/mover.cpp                             $
// 
// 18    10/24/98 8:30p Jimdose
// fixed door revolving bug
// 
// 17    9/03/98 9:08p Jimdose
// Added checks for negative speeds in MoveTo
// 
// 16    8/29/98 9:44p Jimdose
// Made SV_ commands begin with G_
// 
// 15    5/03/98 4:36p Jimdose
// Changed Vector class
// 
// 14    4/06/98 6:42p Jimdose
// the minimum movetime is now FRAMETIME so that we don't get into any infinite
// loops with scripts
// 
// 13    4/05/98 1:58a Jimdose
// Mover now only modifies avelocity  if there's angular movement and velocity
// if there's translational movement.  This allows us to move and have
// continual rotation
// 
// 12    3/24/98 5:00p Jimdose
// Made MoveDone post a new EV_MoveDone instead of postponing the old one
// (which had already been executed, oops!)
// 
// 11    3/23/98 1:31p Jimdose
// Revamped event and command system
// 
// 10    3/11/98 2:24p Jimdose
// Now quantize movetimes to nearest multiple of FRAMETIME
// 
// 9     3/02/98 8:49p Jimdose
// Changed the classid parameter of CLASS_DECLARATION to a quoted string so
// that you could have a NULL classid.
// 
// 8     2/21/98 1:12p Jimdose
// Fixed bug where EVENT_MOVEDONE was allowing the event to pass to the
// superclass
// 
// 7     2/18/98 8:01p Jimdose
// Pending EVENT_MOVEDONEs are cancelled when starting a new move.
// 
// 6     2/16/98 2:12p Jimdose
// Made MoveDone do a PushMove instead of a setOrigin so that blocking works
// correctly at the end of moves
// 
// 5     2/03/98 10:45a Jimdose
// Updated to work with Quake 2 engine
// Made changeover from hackthinker to events
// 
// 3     10/27/97 3:29p Jimdose
// Removed dependency on quakedef.h
// 
// 2     9/26/97 5:23p Jimdose
// Added standard Ritual headers
//
// DESCRIPTION:
// Base class for any object that needs to move to specific locations over a
// period of time.  This class is kept separate from most entities to keep
// class size down for objects that don't need such behavior.
// 

#include "g_local.h"
#include "entity.h"
#include "trigger.h"
#include "mover.h"

#define MOVE_ANGLES 1
#define MOVE_ORIGIN 2

CLASS_DECLARATION( Trigger, Mover, "mover" );

ResponseDef Mover::Responses[] =
	{
	   { &EV_MoveDone, ( Response )Mover::MoveDone },
		{ NULL, NULL }
	};

EXPORT_FROM_DLL void Mover::MoveDone
	(
	Event *ev
	)

	{
	Vector move;
	Vector amove;

	// zero out the movement
	if ( moveflags & MOVE_ANGLES )
		{
		avelocity = vec_zero;
		amove = angledest - angles;
		}
	else
		{
		amove = vec_zero;
		}

	if ( moveflags & MOVE_ORIGIN )
		{
		velocity	= vec_zero;
		move = finaldest - origin;
		}
	else
		{
		move = vec_zero;
		}

	if ( !G_PushMove( this, move, amove ) )
		{
		// Delay finish till we can move into the final position
		PostEvent( EV_MoveDone, FRAMETIME );
		return;
		}

	//
	// After moving, set origin to exact final destination
	//
	if ( moveflags & MOVE_ORIGIN )
		{
		setOrigin( finaldest );
		}

	if ( moveflags & MOVE_ANGLES )
		{
		angles = angledest;

		if ( ( angles.x >= 360 ) || ( angles.x < 0 ) )
			{
			angles.x -= ( (int)angles.x / 360 ) * 360;
			}
		if ( ( angles.y >= 360 ) || ( angles.y < 0 ) )
			{
			angles.y -= ( (int)angles.y / 360 ) * 360;
			}
		if ( ( angles.z >= 360 ) || ( angles.z < 0 ) )
			{
			angles.z -= ( (int)angles.z / 360 ) * 360;
			}
		}

	ProcessEvent( endevent );
	}

/*
=============
MoveTo

calculate self.velocity and self.nextthink to reach dest from
self.origin traveling at speed
===============
*/
EXPORT_FROM_DLL void Mover::MoveTo
	( 
	Vector	tdest,
	Vector	angdest,
	float		tspeed,
	Event		&event
	)

	{
	Vector vdestdelta;
	Vector angdestdelta;
	float  len;
	float  traveltime;
	
	assert( tspeed >= 0 );

	if ( !tspeed )
		{
		error( "MoveTo", "No speed is defined!" );
		}

	if ( tspeed < 0 )
		{
		error( "MoveTo", "Speed is negative!" );
		}

	// Cancel previous moves
	CancelEventsOfType( EV_MoveDone );

	moveflags = 0;

	endevent = event;
	finaldest = tdest;
	angledest = angdest;

	if ( finaldest != origin )
		{
		moveflags |= MOVE_ORIGIN;
		}
	if ( angledest != angles )
		{
		moveflags |= MOVE_ANGLES;
		}

   if ( !moveflags )
      {
      // stop the object from moving
      velocity = vec_zero;
      avelocity = vec_zero;

      // post the event so we don't wait forever
   	PostEvent( EV_MoveDone, FRAMETIME );
      return;
      }

	// set destdelta to the vector needed to move
	vdestdelta = tdest - origin;
	angdestdelta = angdest - angles;

	if ( tdest == origin )
		{
		// calculate length of vector based on angles
		len = angdestdelta.length();
		}
	else
		{
		// calculate length of vector based on distance
		len = vdestdelta.length();
		}

	// divide by speed to get time to reach dest
	traveltime = len / tspeed;

	// Quantize to FRAMETIME
	traveltime *= ( 1 / FRAMETIME );
	traveltime = ( float )( (int)traveltime ) * FRAMETIME;
	if ( traveltime < FRAMETIME )
		{
		traveltime = FRAMETIME;
		vdestdelta = vec_zero;
      angdestdelta = vec_zero;
		}

	// scale the destdelta vector by the time spent traveling to get velocity
	if ( moveflags & MOVE_ORIGIN )
		{
		velocity = vdestdelta * ( 1 / traveltime );
		}

	if ( moveflags & MOVE_ANGLES )
		{
		avelocity = angdestdelta * ( 1 / traveltime );
		}

	PostEvent( EV_MoveDone, traveltime );
	}

/*
=============
LinearInterpolate
===============
*/
EXPORT_FROM_DLL void Mover::LinearInterpolate
	( 
	Vector tdest,
	Vector angdest,
	float time,
	Event &event
	)

	{
	Vector vdestdelta;
	Vector angdestdelta;
	float t;

	endevent = event;
	finaldest = tdest;
	angledest = angdest;

	// Cancel previous moves
	CancelEventsOfType( EV_MoveDone );

	// Quantize to FRAMETIME
	time *= ( 1 / FRAMETIME );
	time = ( float )( (int)time ) * FRAMETIME;
	if ( time < FRAMETIME )
		{
		time = FRAMETIME;
		}
	
	moveflags = 0;
	t = 1 / time;
	// scale the destdelta vector by the time spent traveling to get velocity
	if ( finaldest != origin )
		{
		vdestdelta = tdest - origin;
		velocity = vdestdelta * t;
		moveflags |= MOVE_ORIGIN;
		}

	if ( angledest != angles )
		{
		angdestdelta = angdest - angles;
		avelocity = angdestdelta * t;
		moveflags |= MOVE_ANGLES;
		}

	PostEvent( EV_MoveDone, time );
	}
