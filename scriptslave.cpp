//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/scriptslave.cpp                  $
// $Revision:: 80                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 10/28/98 8:37p                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/scriptslave.cpp                       $
// 
// 80    10/28/98 8:37p Markd
// Added notshootable functionality
// 
// 79    10/27/98 9:15p Jimdose
// overrode bind and unbind events
// 
// 78    10/25/98 4:22a Markd
// Changed explode command for scriptslaves
// 
// 77    10/24/98 2:08p Aldie
// Added func_volumetric
// 
// 76    10/24/98 12:42a Markd
// changed origins to worldorigins where appropriate
// 
// 75    10/23/98 10:04p Markd
// Added explode event
// 
// 74    10/19/98 12:07a Jimdose
// made all code use fast checks for inheritance (no text lookups when
// possible)
// isSubclassOf no longer requires ::_classinfo()
// 
// 73    10/14/98 10:18p Jimdose
// made DoMove not return if event's thread was NULL
// 
// 72    9/23/98 11:00p Markd
// put in some garbage collection on stuff that wasn't freed up
// 
// 71    9/23/98 9:28p Jimdose
// Made thread callback functions clear their labels if the thread is NULL.  
// Also removed assertion from callback functions
// 
// 70    9/22/98 5:20p Markd
// Put in new consolidated gib function
// 
// 69    9/22/98 3:21p Markd
// put in parentmode lockout for blood and gibs
// 
// 68    8/22/98 9:33p Markd
// Put in code which would ensure that threads are valid when gotten from the
// event
// 
// 67    8/21/98 3:47p Markd
// Added new rotation commands
// 
// 66    8/21/98 1:45a Markd
// Added RotateDownTo, RotateUpTo and RotateTo
// 
// 65    8/20/98 4:31p Markd
// Added vector support to moveto and jumpto
// 
// 64    8/17/98 7:31p Jimdose
// DoMove only sets moveThread if the specified thread is waiting for that
// entity
// 
// 63    7/31/98 4:21p Jimdose
// Made events statically created instead of dynamic
// 
// 62    7/24/98 7:37p Aldie
// Added feather gibs
// 
// 61    7/23/98 6:17p Aldie
// Updated damage system and fixed some damage related bugs.  Also put tracers
// back to the way they were, and added gib event to funcscriptmodels
// 
// 60    7/22/98 3:48p Jimdose
// Changed damage to an event function.  Fixed the slaves not responding to
// damage
// 
// 59    7/22/98 12:52p Markd
// tweaked the waitfor on Following Path stuff
// 
// 58    7/21/98 10:05p Markd
// Added starttime to followpath
// 
// 57    7/21/98 5:32p Jimdose
// DoMove now posts a move done event if no commands are waiting so that any
// waitFor's that are called after a slave has finished it's move won't be
// stuck forever
// 
// 56    7/21/98 4:23p Aldie
// Make icons work for locks
// 
// 55    7/21/98 1:10p Aldie
// Added meansofdeath to obituaries
// 
// 54    7/19/98 4:25p Markd
// Added "other" and "key" support to usethread
// 
// 53    7/19/98 3:42p Markd
// Added ondamage variables
// 
// 52    7/18/98 3:53p Markd
// Added key support to scriptslave
// 
// 51    7/11/98 6:31p Markd
// removed valid orientation, simplified code
// 
// 50    7/10/98 1:55p Markd
// when checking for end of spline, had to do a > rather than a >=
// 
// 49    7/10/98 1:11p Markd
// Added some more functionality to spline based movement
// 
// 48    7/09/98 11:53p Markd
// Added non-orientation support for spline_paths
// 
// 47    7/09/98 9:39p Jimdose
// Removed RF_CONSOLE
// 
// 46    7/08/98 8:54p Markd
// maybe I didn't need to invert pitch!
// 
// 45    7/08/98 12:55p Markd
// forgot to invert pitch on spline based stuff
// 
// 44    7/08/98 12:42p Markd
// Added followpath and resumepath and followingpath for spline based movement
// 
// 43    6/18/98 8:47p Jimdose
// Added better event error handling
// Added source info to events
// 
// 42    6/11/98 11:52a Aldie
// Updated scriptslave damage function to use all the same parms as the
// entity::damage function.
// 
// 41    6/10/98 2:10p Aldie
// Updated damage function.
// 
// 40    5/24/98 8:46p Jimdose
// Made a lot of functions more str-friendly.
// Got rid of a lot of char * based strings
// Cleaned up get spawn arg functions and sound functions
// sound functions now use consistant syntax
// 
// 39    5/24/98 4:48p Jimdose
// Made char *'s const
// 
// 38    5/24/98 2:46p Markd
// Made char *'s into const char *'s
// 
// 37    5/23/98 4:48p Aldie
// Removed RF_CONSOLE from script object
// 
// 36    5/20/98 4:32p Markd
// bullet proofed thread code and made sure that thread variable was non-null
// 
// 35    5/19/98 9:52p Markd
// added not_damage flag to objects
// 
// 34    5/03/98 4:37p Jimdose
// Changed Vector class
// 
// 33    5/01/98 5:08p Jimdose
// TriggerEvent now specifies world as the activator
// 
// 32    4/29/98 7:13p Jimdose
// forgot an else. :(
// 
// 31    4/29/98 6:34p Jimdose
// Made ScriptSlave use SOLID_NOT when there's a NULL model
// 
// 30    4/29/98 6:30p Jimdose
// Added ScriptOrigin
// 
// 29    4/25/98 5:09p Markd
// Added up and down support for angles
// 
// 28    4/20/98 11:01a Markd
// Fixed client side prediction of non-solid shootables
// 
// 27    4/18/98 7:30p Markd
// Made func_scriptmodel not have any dimension
// 
// 26    4/18/98 6:10p Aldie
// Added RF_CONSOLE to script objects so users can render consoles on them.
// 
// 25    4/09/98 1:40p Markd
// Added in CONTENTS_SHOOTABLE stuff
// 
// 24    4/08/98 4:20p Jimdose
// Added NOT_SOLID spawnflag
// 
// 23    4/07/98 9:34p Jimdose
// Scriptobjects respond to damage
// 
// 22    4/07/98 8:00p Markd
// removed defhandle, changed all SINMDL calls to modelindex calls, removed
// SINMDL prefix
// 
// 21    4/06/98 3:55p Jimdose
// Since RF_FRAMELERP is now cleared out every frame, ClearLerp was redundant
// 
// 20    4/05/98 1:59a Jimdose
// Made Jumpto prevent lerping of the models position
// Added ScriptModel for amodel-based script objects
// 
// 19    3/31/98 2:27p Jimdose
// Cleared out the angles at start
// 
// 18    3/30/98 8:09p Jimdose
// Made forward and backward use the start angle
// 
// 17    3/24/98 4:58p Jimdose
// Added NewOrders to indicate when the slave should update NewAngles
// Fixed typo related  bugs in touch, block, use, damage callback functions
// 
// 16    3/23/98 1:31p Jimdose
// Revamped event and command system
// 
// 15    3/02/98 8:49p Jimdose
// Changed the classid parameter of CLASS_DECLARATION to a quoted string so
// that you could have a NULL classid.
// 
// 14    2/21/98 1:11p Jimdose
// Fixed bug where EVENT_SCRIPTSLAVE_MOVEDONE was allowing the event to pass to
// the superclass
// 
// 13    2/18/98 8:07p Jimdose
// Changed pointers to scriptMaster to entity numbers
// Changed direct calls to the master into events
// 
// 12    2/17/98 8:34p Jimdose
// Fixed NULL pointer problem in the onTouch, etc, functions
// 
// 11    2/17/98 7:09p Jimdose
// no longer pass script into interpretCommand
// added error handling for invalid labels
// 
// 10    2/16/98 2:15p Jimdose
// Added script commands rotateX, rotateY, and rotateZ for continual arbitrary
// rotation
// 
// 9     2/06/98 5:38p Jimdose
// Added check for null jumpto in onTouch, onBlock, onDamage, etc.
// 
// 8     2/03/98 10:44a Jimdose
// Updated to work with Quake 2 engine
// 
// 6     10/28/97 4:15p Jimdose
// Removed CommandsWaiting.
// Moved "bind" and "unBind" commands into Entity
// Made DoMove be called when "processCommands" message is sent.
// 
// 5     10/27/97 3:29p Jimdose
// Removed dependency on quakedef.h
// 
// 4     10/22/97 12:25p Jimdose
// Fixed bug where slave wouldn't damage other entities when they blocked it.
// 
// 3     9/26/97 5:23p Jimdose
// Added standard Ritual headers
//
// DESCRIPTION:
// Standard scripted objects.  Controlled by ScriptThread.  These objects
// are bmodel objects created in the editor and controlled by an external
// text based script.  Commands are interpretted on by one and executed
// upon a signal from the script master.  The base script object can
// perform several different relative and specific rotations and translations
// and can cause other parts of the script to be executed when touched, damaged,
// touched, or used.
// 

#include "g_local.h"
#include "class.h"
#include "mover.h"
#include "scriptmaster.h"
#include "scriptslave.h"
#include "sentient.h"
#include "item.h"
#include "gibs.h"
#include "explosion.h"

/*****************************************************************************/
/*SINED func_scriptobject (0 .5 .8) ? NOT_SOLID 

/*****************************************************************************/

CLASS_DECLARATION( Mover, ScriptSlave, "func_scriptobject" );

Event EV_ScriptSlave_DoMove( "processCommands" );
Event EV_ScriptSlave_NewOrders( "newOrders" );
Event EV_ScriptSlave_Angles( "angles" );
Event EV_ScriptSlave_Trigger( "trigger" );
Event EV_ScriptSlave_Next( "next" );
Event EV_ScriptSlave_JumpTo( "jumpto" );
Event EV_ScriptSlave_MoveTo( "moveto" );
Event EV_ScriptSlave_Speed( "speed" );
Event EV_ScriptSlave_Time( "time" );
Event EV_ScriptSlave_MoveUp( "moveUp" );
Event EV_ScriptSlave_MoveDown( "moveDown" );
Event EV_ScriptSlave_MoveNorth( "moveNorth" );
Event EV_ScriptSlave_MoveSouth( "moveSouth" );
Event EV_ScriptSlave_MoveEast( "moveEast" );
Event EV_ScriptSlave_MoveWest( "moveWest" );
Event EV_ScriptSlave_MoveForward( "moveForward" );
Event EV_ScriptSlave_MoveBackward( "moveBackward" );
Event EV_ScriptSlave_MoveLeft( "moveLeft" );
Event EV_ScriptSlave_MoveRight( "moveRight" );
Event EV_ScriptSlave_RotateXDownTo( "rotateXdownto" );
Event EV_ScriptSlave_RotateYDownTo( "rotateYdownto" );
Event EV_ScriptSlave_RotateZDownTo( "rotateZdownto" );
Event EV_ScriptSlave_RotateAxisDownTo( "rotateaxisdownto" );
Event EV_ScriptSlave_RotateXUpTo( "rotateXupto" );
Event EV_ScriptSlave_RotateYUpTo( "rotateYupto" );
Event EV_ScriptSlave_RotateZUpTo( "rotateZupto" );
Event EV_ScriptSlave_RotateAxisUpTo( "rotateaxisupto" );
Event EV_ScriptSlave_RotateXDown( "rotateXdown" );
Event EV_ScriptSlave_RotateYDown( "rotateYdown" );
Event EV_ScriptSlave_RotateZDown( "rotateZdown" );
Event EV_ScriptSlave_RotateAxisDown( "rotateaxisdown" );
Event EV_ScriptSlave_RotateXUp( "rotateXup" );
Event EV_ScriptSlave_RotateYUp( "rotateYup" );
Event EV_ScriptSlave_RotateZUp( "rotateZup" );
Event EV_ScriptSlave_RotateAxisUp( "rotateaxisup" );
Event EV_ScriptSlave_RotateX( "rotateX" );
Event EV_ScriptSlave_RotateY( "rotateY" );
Event EV_ScriptSlave_RotateZ( "rotateZ" );
Event EV_ScriptSlave_RotateAxis( "rotateaxis" );
Event EV_ScriptSlave_RotateDownTo( "rotatedownto" );
Event EV_ScriptSlave_RotateUpTo( "rotateupto" );
Event EV_ScriptSlave_RotateTo( "rotateto" );
Event EV_ScriptSlave_OnTouch( "ontouch" );
Event EV_ScriptSlave_NoTouch( "notouch" );
Event EV_ScriptSlave_OnUse( "onuse" );
Event EV_ScriptSlave_NoUse( "nouse" );
Event EV_ScriptSlave_OnBlock( "onblock" );
Event EV_ScriptSlave_NoBlock( "noblock" );
Event EV_ScriptSlave_OnTrigger( "ontrigger" );
Event EV_ScriptSlave_NoTrigger( "notrigger" );
Event EV_ScriptSlave_OnDamage( "ondamage" );
Event EV_ScriptSlave_NoDamage( "nodamage" );
Event EV_ScriptSlave_SetDamage( "setdamage" );
Event EV_ScriptSlave_FollowPath( "followpath" );
Event EV_ScriptSlave_EndPath( "endpath" );
Event EV_ScriptSlave_MoveDone( "scriptslave_movedone" );
Event EV_ScriptSlave_FollowingPath( "scriptslave_followingpath" );
Event EV_ScriptSlave_Explode( "explode" );
Event EV_ScriptSlave_NotShootable( "notshootable" );

ResponseDef ScriptSlave::Responses[] =
	{
	   { &EV_Bind,					            ( Response )ScriptSlave::BindEvent },
	   { &EV_Unbind,				            ( Response )ScriptSlave::EventUnbind },
		{ &EV_ScriptSlave_DoMove,				( Response )ScriptSlave::DoMove },
		{ &EV_ScriptSlave_NewOrders,			( Response )ScriptSlave::NewOrders },
		{ &EV_ScriptSlave_Angles,				( Response )ScriptSlave::SetAnglesEvent },
      { &EV_ScriptSlave_Trigger,				( Response )ScriptSlave::TriggerEvent },
	   { &EV_ScriptSlave_Next,					( Response )ScriptSlave::GotoNextWaypoint },
	   { &EV_ScriptSlave_JumpTo,				( Response )ScriptSlave::JumpTo },
	   { &EV_ScriptSlave_MoveTo,				( Response )ScriptSlave::MoveToEvent },
	   { &EV_ScriptSlave_Speed,				( Response )ScriptSlave::SetSpeed },
	   { &EV_ScriptSlave_Time,					( Response )ScriptSlave::SetTime },
	   { &EV_ScriptSlave_MoveUp,				( Response )ScriptSlave::MoveUp },
	   { &EV_ScriptSlave_MoveDown,			( Response )ScriptSlave::MoveDown },
	   { &EV_ScriptSlave_MoveNorth,			( Response )ScriptSlave::MoveNorth },
	   { &EV_ScriptSlave_MoveSouth,			( Response )ScriptSlave::MoveSouth },
	   { &EV_ScriptSlave_MoveEast,			( Response )ScriptSlave::MoveEast },
	   { &EV_ScriptSlave_MoveWest,			( Response )ScriptSlave::MoveWest },
	   { &EV_ScriptSlave_MoveForward,		( Response )ScriptSlave::MoveForward },
	   { &EV_ScriptSlave_MoveBackward,		( Response )ScriptSlave::MoveBackward },
	   { &EV_ScriptSlave_MoveLeft,			( Response )ScriptSlave::MoveLeft },
	   { &EV_ScriptSlave_MoveRight,			( Response )ScriptSlave::MoveRight },
		{ &EV_ScriptSlave_RotateXDownTo,		( Response )ScriptSlave::RotateXdownto },
	   { &EV_ScriptSlave_RotateYDownTo,		( Response )ScriptSlave::RotateYdownto },
	   { &EV_ScriptSlave_RotateZDownTo,		( Response )ScriptSlave::RotateZdownto },
	   { &EV_ScriptSlave_RotateXUpTo,		( Response )ScriptSlave::RotateXupto },
	   { &EV_ScriptSlave_RotateYUpTo,		( Response )ScriptSlave::RotateYupto },
	   { &EV_ScriptSlave_RotateZUpTo,		( Response )ScriptSlave::RotateZupto },
	   { &EV_ScriptSlave_RotateXDown,		( Response )ScriptSlave::RotateXdown },
	   { &EV_ScriptSlave_RotateYDown,		( Response )ScriptSlave::RotateYdown },
	   { &EV_ScriptSlave_RotateZDown,		( Response )ScriptSlave::RotateZdown },
	   { &EV_ScriptSlave_RotateXUp,			( Response )ScriptSlave::RotateXup },
	   { &EV_ScriptSlave_RotateYUp,			( Response )ScriptSlave::RotateYup },
	   { &EV_ScriptSlave_RotateZUp,			( Response )ScriptSlave::RotateZup },
	   { &EV_ScriptSlave_RotateX,				( Response )ScriptSlave::RotateX },
	   { &EV_ScriptSlave_RotateY,				( Response )ScriptSlave::RotateY },
	   { &EV_ScriptSlave_RotateZ,				( Response )ScriptSlave::RotateZ },
	   { &EV_ScriptSlave_RotateAxisDownTo,	( Response )ScriptSlave::RotateAxisdownto },
	   { &EV_ScriptSlave_RotateAxisUpTo,	( Response )ScriptSlave::RotateAxisupto },
	   { &EV_ScriptSlave_RotateAxisDown,	( Response )ScriptSlave::RotateAxisdown },
	   { &EV_ScriptSlave_RotateAxisUp,		( Response )ScriptSlave::RotateAxisup },
	   { &EV_ScriptSlave_RotateAxis,			( Response )ScriptSlave::RotateZ },
		{ &EV_ScriptSlave_OnTouch,				( Response )ScriptSlave::OnTouch },
	   { &EV_ScriptSlave_NoTouch,				( Response )ScriptSlave::NoTouch },
	   { &EV_ScriptSlave_OnUse,				( Response )ScriptSlave::OnUse },
	   { &EV_ScriptSlave_NoUse,				( Response )ScriptSlave::NoUse },
	   { &EV_ScriptSlave_OnBlock,				( Response )ScriptSlave::OnBlock },
	   { &EV_ScriptSlave_NoBlock,				( Response )ScriptSlave::NoBlock },
	   { &EV_ScriptSlave_OnTrigger,			( Response )ScriptSlave::OnTrigger },
	   { &EV_ScriptSlave_NoTrigger,			( Response )ScriptSlave::NoTrigger },
	   { &EV_ScriptSlave_OnDamage,			( Response )ScriptSlave::OnDamage },
	   { &EV_ScriptSlave_NoDamage,			( Response )ScriptSlave::NoDamage },
	   { &EV_ScriptSlave_SetDamage,			( Response )ScriptSlave::SetDamage },
	   { &EV_ScriptSlave_FollowPath,			( Response )ScriptSlave::FollowPath },
	   { &EV_ScriptSlave_EndPath,			   ( Response )ScriptSlave::EndPath },
	   { &EV_ScriptSlave_FollowingPath,		( Response )ScriptSlave::FollowingPath },
	   { &EV_Touch,								( Response )ScriptSlave::TouchFunc },
	   { &EV_Blocked,								( Response )ScriptSlave::BlockFunc },
	   { &EV_Activate,							( Response )ScriptSlave::TriggerFunc },
	   { &EV_Use,									( Response )ScriptSlave::UseFunc },
	   { &EV_ScriptSlave_MoveDone,			( Response )ScriptSlave::MoveEnd },
		{ &EV_Damage,								( Response )ScriptSlave::DamageFunc },
	   { &EV_ScriptSlave_RotateDownTo,		( Response )ScriptSlave::Rotatedownto },
	   { &EV_ScriptSlave_RotateUpTo,		   ( Response )ScriptSlave::Rotateupto },
	   { &EV_ScriptSlave_RotateTo,		   ( Response )ScriptSlave::Rotateto },
	   { &EV_ScriptSlave_Explode,		      ( Response )ScriptSlave::Explode },
		{ &EV_ScriptSlave_NotShootable,		( Response )ScriptSlave::NotShootable },

		{ NULL, NULL }
	};

ScriptSlave::ScriptSlave()
	{
	float angle;
	const char *m;

	showModel();

	speed = G_GetFloatArg( "speed", 100 );

	angle = G_GetFloatArg( "angle" );
	if ( angle == -1 )
		{
		ForwardDir = Vector( 0, 0, 90 );
		}
	else if ( angle == -2 )
		{
		ForwardDir = Vector( 0, 0, -90 );
		}
	else
		{
		ForwardDir = Vector( 0, angle, 0 );
		}

	setAngles( vec_zero );

	takedamage			= DAMAGE_YES;
	waypoint				= NULL;
	NewAngles			= angles;
	NewPos				= origin;
	traveltime			= 0;
	commandswaiting	= false;
	movethread			= NULL;
	touchthread			= NULL;
	blockthread			= NULL;
	damagethread		= NULL;
	triggerthread		= NULL;
	usethread			= NULL;
   splinePath        = NULL;
   splineangles      = false;

	dmg					= G_GetIntArg( "dmg", 2 );
	attack_finished = 0;

	setMoveType( MOVETYPE_PUSH );

	m = G_GetSpawnArg( "model" );
	if ( !edict->s.modelindex )
		{
		setSolidType( SOLID_NOT );
		}
	else if ( spawnflags & 1 )
		{
      // if it isn't solid, lets still make it shootable
   	edict->svflags |= SVF_SHOOTABLE;
		setSolidType( SOLID_BBOX );
      setOrigin( origin );
		}
	else if ( !m || strstr( m, ".def" ) )
		{
		setSolidType( SOLID_BBOX );
		}
	else
		{
		setSolidType( SOLID_BSP );
		}

	edict->s.effects |= EF_SMOOTHANGLES;
	}

ScriptSlave::~ScriptSlave()
	{
   if ( splinePath )
      {
      delete splinePath;
      splinePath = NULL;
      }
   }

void ScriptSlave::NewOrders
	(
	Event *ev
	)

	{
	// make sure position and angles are current
	NewAngles = angles;
	NewPos = origin;
	}

EXPORT_FROM_DLL void ScriptSlave::BindEvent
	(
	Event *ev
	)

	{
	Entity *ent;

	ent = ev->GetEntity( 1 );
	if ( ent )
		{
		bind( ent );
		}

	// make sure position and angles are current
	NewAngles = angles;
	NewPos = origin;
	}

EXPORT_FROM_DLL void ScriptSlave::EventUnbind
	(
	Event *ev
	)

	{
	unbind();

   // make sure position and angles are current
	NewAngles = angles;
	NewPos = origin;
	}

void ScriptSlave::DoMove
	(
	Event *ev
	)

	{
	float dist;
	ScriptThread *thread;
	Event *event;

	thread = ev->GetThread();
   assert( thread );
   if ( thread && thread->WaitingFor( this ) )
		{
		if ( movethread && ( movethread != thread ) )
			{
			// warn the user
			ev->Error( "Overriding previous move commands for '%s'\n", TargetName() );

			// Yeah, we're not REALLY done, but we tell our old thread
			// that we are so that it doesn't wait forever
			event = new Event( EV_MoveDone );
			event->AddEntity( this );
			movethread->ProcessEvent( event );
			}

		movethread = thread;
		}

	if ( commandswaiting )
		{
      if ( splinePath )
         {
      	PostEvent( EV_ScriptSlave_FollowingPath, 0 );
         }
      else
         {
		   if ( traveltime == 0 )
			   {
			   dist = Vector( NewPos - origin ).length();
			   traveltime = dist / speed;
			   }
		   
		   LinearInterpolate( NewPos, NewAngles, traveltime, EV_ScriptSlave_MoveDone );
         }

		commandswaiting = false;
		}
	else if ( movethread && ( movethread == thread ) )
		{
		// No commands, so tell the master that we're done
		PostEvent( EV_ScriptSlave_MoveDone, 0 );
		}
	}

void ScriptSlave::MoveEnd
	(
	Event *ev
	)

	{
	Event *event;

	commandswaiting = false;
	NewAngles = angles;
	NewPos = origin;

	if ( movethread )
		{
		event = new Event( EV_MoveDone );
		event->AddEntity( this );
		movethread->ProcessEvent( event );
		movethread = NULL;
		}
	}

void ScriptSlave::SetAnglesEvent
	(
	Event *ev
	)

	{
	commandswaiting = true; 
	angles = ev->GetVector( 1 );
	NewAngles = angles;
	}

void ScriptSlave::TriggerEvent
	(
	Event *ev
	)

	{
	Entity *ent;
	Event	 *e;

	ent = ev->GetEntity( 1 );
	if ( ent )
		{
		SetTarget( ent->TargetName() );

		e = new Event( EV_Trigger_ActivateTargets );
		//fixme
		//get "other"
		e->AddEntity( world );
		ProcessEvent( e );
		}
	}

void ScriptSlave::GotoNextWaypoint
	( 
	Event *ev
	)

	{
	int ent;

	commandswaiting = true;

	if ( !waypoint )
		{
		ev->Error( "%s is currently not at a waypoint", TargetName() );
		return;
		}

	ent = G_FindTarget( 0, waypoint->Target() );
	if ( !ent )
		{
		ev->Error( "%s could not find waypoint %s", TargetName(), waypoint->Target() );
		return;
		}

	waypoint = ( Waypoint * )G_GetEntity( ent );
	if ( waypoint )
		{
		NewPos = waypoint->worldorigin;
		}
	}

void ScriptSlave::JumpTo
	(
	Event *ev
	)

	{
	Entity *part;

   //
   // see if it is a vector
   //
   if ( ev->IsVectorAt( 1 ) )
      {
      NewPos = ev->GetVector( 1 );
		if ( bindmaster )
			{
			origin = bindmaster->getLocalVector( NewPos - bindmaster->worldorigin );
			}
		else
			{
			origin = NewPos;
			}

		for( part = this; part; part = part->teamchain )
			{
			part->setOrigin( part->origin );
			part->worldorigin.copyTo( part->edict->s.old_origin );
			part->edict->s.renderfx |= RF_FRAMELERP;
			}
      }
   else
      {
	   waypoint = ( Waypoint * )ev->GetEntity( 1 );
	   if ( waypoint )
		   {
		   NewPos = waypoint->origin;
		   if ( bindmaster )
			   {
			   origin = bindmaster->getLocalVector( NewPos - bindmaster->worldorigin );
			   }
		   else
			   {
			   origin = NewPos;
			   }

		   for( part = this; part; part = part->teamchain )
			   {
			   part->setOrigin( part->origin );
			   part->worldorigin.copyTo( part->edict->s.old_origin );
			   part->edict->s.renderfx |= RF_FRAMELERP;
			   }
		   }
      }
	}

void ScriptSlave::MoveToEvent
	( 
	Event *ev
	)

	{
	commandswaiting = true; 

   //
   // see if it is a vector
   //
   if ( ev->IsVectorAt( 1 ) )
      {
      NewPos = ev->GetVector( 1 );
      }
   else
      {
	   waypoint = ( Waypoint * )ev->GetEntity( 1 );
	   if ( waypoint )
		   {
		   NewPos = waypoint->worldorigin;
		   }
      }
	}

void ScriptSlave::SetSpeed
	(
	Event *ev
	)

	{
	speed = ev->GetFloat( 1 );
	traveltime = 0;
	}

void ScriptSlave::SetTime
	(
	Event *ev
	)

	{
	traveltime = ev->GetFloat( 1 );
	}

// Relative move commands

void ScriptSlave::MoveUp
	(
	Event *ev
	)

	{
	commandswaiting = true; 
	NewPos[ 2 ] += ev->GetDouble( 1 );
	}

void ScriptSlave::MoveDown
	(
	Event *ev
	)

	{
	commandswaiting = true; 
	NewPos[ 2 ] -= ev->GetDouble( 1 );
	}

void ScriptSlave::MoveNorth
	(
	Event *ev
	)

	{
	commandswaiting = true; 
	NewPos[ 1 ] += ev->GetDouble( 1 );
	}

void ScriptSlave::MoveSouth
	(
	Event *ev
	)

	{
	commandswaiting = true; 
	NewPos[ 1 ] -= ev->GetDouble( 1 );
	}

void ScriptSlave::MoveEast
	(
	Event *ev
	)

	{
	commandswaiting = true; 
	NewPos[ 0 ] += ev->GetDouble( 1 );
	}

void ScriptSlave::MoveWest
	(
	Event *ev
	)

	{
	commandswaiting = true; 
	NewPos[ 0 ] -= ev->GetDouble( 1 );
	}

void ScriptSlave::MoveForward
	(
	Event *ev
	)

	{
	Vector v;
	Vector t;

	commandswaiting = true; 

	t = NewAngles + ForwardDir;
	t.AngleVectors( &v, NULL, NULL );

	NewPos += v * ev->GetDouble( 1 );
	}

void ScriptSlave::MoveBackward
	(
	Event *ev
	)

	{
	Vector v;
	Vector t;

	commandswaiting = true;

	t = NewAngles + ForwardDir;
	t.AngleVectors( &v, NULL, NULL );

	NewPos -= v * ev->GetDouble( 1 );
	}

void ScriptSlave::MoveLeft
	(
	Event *ev
	)

	{
	Vector v;
	Vector t;

	commandswaiting = true; 

	t = NewAngles + ForwardDir;
	t.AngleVectors( NULL, &v, NULL );

	NewPos -= v * ev->GetDouble( 1 );
	}

void ScriptSlave::MoveRight
	(
	Event *ev
	)

	{
	Vector t;
	Vector v;

	commandswaiting = true; 

	t = NewAngles + ForwardDir;
	t.AngleVectors( NULL, &v, NULL );

	NewPos += v * ev->GetDouble( 1 );
	}

// exact rotate commands

void ScriptSlave::RotateXdownto
	(
	Event *ev
	)

	{
	commandswaiting = true; 

	NewAngles[ 0 ] = ev->GetFloat( 1 );
	if ( NewAngles[ 0 ] > angles[ 0 ] )
		{
		NewAngles[ 0 ] -= 360;
		}
	}

void ScriptSlave::RotateYdownto
	(
	Event *ev
	)

	{
	commandswaiting = true; 

	NewAngles[ 1 ] = ev->GetFloat( 1 );
	if ( NewAngles[ 1 ] > angles[ 1 ] )
		{
		NewAngles[ 1 ] -= 360;
		}
	}

void ScriptSlave::RotateZdownto
	(
	Event *ev
	)

	{
	commandswaiting = true; 

	NewAngles[ 2 ] = ev->GetFloat( 1 );
	if ( NewAngles[ 2 ] > angles[ 2 ] )
		{
		NewAngles[ 2 ] -= 360;
		}
	}

void ScriptSlave::RotateAxisdownto
	(
	Event *ev
	)

	{
   int axis;
	commandswaiting = true; 

   axis = ev->GetInteger( 1 );
	NewAngles[ axis ] = ev->GetFloat( 2 );
	if ( NewAngles[ axis ] > angles[ axis ] )
		{
		NewAngles[ axis ] -= 360;
		}
	}

void ScriptSlave::RotateXupto
	(
	Event *ev
	)

	{
	commandswaiting = true; 

	NewAngles[ 0 ] = ev->GetFloat( 1 );
	if ( NewAngles[ 0 ] < angles[ 0 ] )
		{
		NewAngles[ 0 ] += 360;
		}
	}

void ScriptSlave::RotateYupto
	(
	Event *ev
	)

	{
	commandswaiting = true; 

	NewAngles[ 1 ] = ev->GetFloat( 1 );
	if ( NewAngles[ 1 ] < angles[ 1 ] )
		{
		NewAngles[ 1 ] += 360;
		}
	}

void ScriptSlave::RotateZupto
	(
	Event *ev
	)

	{
	commandswaiting = true; 

	NewAngles[ 2 ] = ev->GetFloat( 1 );
	if ( NewAngles[ 2 ] < angles[ 2 ] )
		{
		NewAngles[ 2 ] += 360;
		}
	}

void ScriptSlave::RotateAxisupto
	(
	Event *ev
	)

	{
   int axis;
	commandswaiting = true; 

   axis = ev->GetInteger( 1 );
	NewAngles[ axis ] = ev->GetFloat( 2 );
	if ( NewAngles[ axis ] < angles[ axis ] )
		{
		NewAngles[ axis ] += 360;
		}
	}

// full vector rotation

void ScriptSlave::Rotatedownto
	(
	Event *ev
	)

	{
   Vector ang;
	commandswaiting = true; 

   ang = ev->GetVector( 1 );

	NewAngles[ 0 ] = ang[ 0 ];
	if ( NewAngles[ 0 ] > angles[ 0 ] )
		{
		NewAngles[ 0 ] -= 360;
		}
	NewAngles[ 1 ] = ang[ 1 ];
	if ( NewAngles[ 1 ] > angles[ 1 ] )
		{
		NewAngles[ 1 ] -= 360;
		}
	NewAngles[ 2 ] = ang[ 2 ];
	if ( NewAngles[ 2 ] > angles[ 2 ] )
		{
		NewAngles[ 2 ] -= 360;
		}
	}

void ScriptSlave::Rotateupto
	(
	Event *ev
	)

	{
   Vector ang;
	commandswaiting = true; 

   ang = ev->GetVector( 1 );

	NewAngles[ 0 ] = ang[ 0 ];
	if ( NewAngles[ 0 ] < angles[ 0 ] )
		{
		NewAngles[ 0 ] += 360;
		}
	NewAngles[ 1 ] = ang[ 1 ];
	if ( NewAngles[ 1 ] < angles[ 1 ] )
		{
		NewAngles[ 1 ] += 360;
		}
	NewAngles[ 2 ] = ang[ 2 ];
	if ( NewAngles[ 2 ] < angles[ 2 ] )
		{
		NewAngles[ 2 ] += 360;
		}
	}

void ScriptSlave::Rotateto
	(
	Event *ev
	)

	{
   Vector ang;
	commandswaiting = true; 

   ang = ev->GetVector( 1 );

   NewAngles = ang;
	}

// Relative rotate commands

void ScriptSlave::RotateXdown
	(
	Event *ev
	)

	{
	commandswaiting = true; 
	NewAngles[ 0 ] = angles[ 0 ] - ev->GetFloat( 1 );
	}

void ScriptSlave::RotateYdown
	(
	Event *ev
	)

	{
	commandswaiting = true; 
	NewAngles[ 1 ] = angles[ 1 ] - ev->GetFloat( 1 );
	}

void ScriptSlave::RotateZdown
	(
	Event *ev
	)

	{
	commandswaiting = true; 
	NewAngles[ 2 ] = angles[ 2 ] - ev->GetFloat( 1 );
	}

void ScriptSlave::RotateAxisdown
	(
	Event *ev
	)

	{
   int axis;
	commandswaiting = true; 

   axis = ev->GetInteger( 1 );
	NewAngles[ axis ] = angles[ axis ] - ev->GetFloat( 2 );
	}

void ScriptSlave::RotateXup
	(
	Event *ev
	)

	{
 	commandswaiting = true; 
	NewAngles[ 0 ] = angles[ 0 ] + ev->GetFloat( 1 );
	}

void ScriptSlave::RotateYup
	(
	Event *ev
	)

	{
 	commandswaiting = true; 
	NewAngles[ 1 ] = angles[ 1 ] + ev->GetFloat( 1 );
	}

void ScriptSlave::RotateZup
	(
	Event *ev
	)

	{
 	commandswaiting = true; 
	NewAngles[ 2 ] = angles[ 2 ] + ev->GetFloat( 1 );
	}

void ScriptSlave::RotateAxisup
	(
	Event *ev
	)

	{
   int axis;
	commandswaiting = true; 

   axis = ev->GetInteger( 1 );
	NewAngles[ axis ] = angles[ axis ] + ev->GetFloat( 2 );
	}

void ScriptSlave::RotateX
	(
	Event *ev
	)

	{
	avelocity[ 0 ] = ev->GetFloat( 1 );
	}

void ScriptSlave::RotateY
	(
	Event *ev
	)

	{
	avelocity[ 1 ] = ev->GetFloat( 1 );
	}

void ScriptSlave::RotateZ
	(
	Event *ev
	)

	{
	avelocity[ 2 ] = ev->GetFloat( 1 );
	}

void ScriptSlave::RotateAxis
	(
	Event *ev
	)

	{
   int axis;

   axis = ev->GetInteger( 1 );
   avelocity[ axis ] = ev->GetFloat( 2 );
	}


void ScriptSlave::OnTouch
	(
	Event *ev
	)

	{
	const char *jumpto;

	touchlabel = "";

	jumpto = ev->GetString( 1 );
	touchthread = ev->GetThread();

	assert( jumpto && touchthread );
	if ( touchthread && !touchthread->labelExists( jumpto ) )
		{
		ev->Error( "Label '%s' not found", jumpto );
		return;
		}

	touchlabel = jumpto;
	}

void ScriptSlave::NoTouch
	(
	Event *ev
	)

	{
	touchlabel = "";
	}

void ScriptSlave::TouchFunc
	(
	Event *ev
	)

	{
	Event *e;
	Entity *other;

	if ( touchlabel.length() )
		{
      // since we use a SafePtr, the thread pointer will be NULL if the thread has ended
      // so we should just clear our label and continue
      if ( !touchthread )
			{
         touchlabel = "";
         return;
         }

      other = ev->GetEntity( 1 );

		e = new Event( EV_ScriptThread_Callback );
		e->AddEntity( this );
		e->AddString( touchlabel );
		e->AddEntity( other );
  		touchthread->ProcessEvent( e );
		}
	}

void ScriptSlave::OnBlock
	(
	Event *ev
	)

	{
	const char *jumpto;

	blocklabel = "";

	jumpto = ev->GetString( 1 );
	blockthread = ev->GetThread();

	assert( jumpto && blockthread );
	if ( blockthread && !blockthread->labelExists( jumpto ) )
		{
		ev->Error( "Label '%s' not found", jumpto );
		return;
		}

	blocklabel = jumpto;
	}

void ScriptSlave::NoBlock
	(
	Event *ev
	)

	{
	blocklabel = "";
	}

void ScriptSlave::BlockFunc
	(
	Event *ev
	)

	{
	Event *e;
	Entity *other;

	other = ev->GetEntity( 1 );
	if ( level.time >= attack_finished )
		{
		attack_finished = level.time + ( float )0.5;
		if ( dmg != 0 )
			{
			other->Damage( this, this, dmg, origin, vec_zero, vec_zero, 0, 0, MOD_CRUSH, -1, -1, 1.0f );
			}
		}

	if ( blocklabel.length() )
		{
      // since we use a SafePtr, the thread pointer will be NULL if the thread has ended
      // so we should just clear our label and continue
      if ( !blockthread )
			{
         blocklabel = "";
         return;
         }

		e = new Event( EV_ScriptThread_Callback );
		e->AddEntity( this );
		e->AddString( blocklabel );
		e->AddEntity( other );
  		blockthread->ProcessEvent( e );
		}
	}

void ScriptSlave::OnTrigger
	(
	Event *ev
	)

	{
	const char *jumpto;

	triggerlabel = "";

	jumpto = ev->GetString( 1 );
	triggerthread = ev->GetThread();

	assert( jumpto && triggerthread );

	if ( triggerthread && !triggerthread->labelExists( jumpto ) )
		{
		ev->Error( "Label '%s' not found", jumpto );
		return;
		}

	triggerlabel = jumpto;
	}

void ScriptSlave::NoTrigger
	(
	Event *ev
	)

	{
	triggerlabel = "";
	}

void ScriptSlave::TriggerFunc
	(
	Event *ev
	)

	{
	Event *e;
	Entity *other;

	if ( triggerlabel.length() )
		{
      // since we use a SafePtr, the thread pointer will be NULL if the thread has ended
      // so we should just clear our label and continue
      if ( !triggerthread )
			{
         triggerlabel = "";
         return;
         }

		other = ev->GetEntity( 1 );

		e = new Event( EV_ScriptThread_Callback );
		e->AddEntity( this );
		e->AddString( triggerlabel );
		e->AddEntity( other );

      triggerthread->ProcessEvent( e );
		}
	}

void ScriptSlave::OnUse
	(
	Event *ev
	)

	{
	const char *jumpto;

	uselabel = "";

	jumpto = ev->GetString( 1 );
	usethread = ev->GetThread();

	assert( jumpto && usethread );

	if ( usethread && !usethread->labelExists( jumpto ) )
		{
		ev->Error( "Label '%s' not found", jumpto );
		return;
		}

	uselabel = jumpto;
	}

void ScriptSlave::NoUse
	(
	Event *ev
	)

	{
	uselabel = "";
	}

void ScriptSlave::UseFunc
	(
	Event *ev
	)

	{
	Event *e;
	Entity *other;

	other = ev->GetEntity( 1 );

   if ( key.length() )
      {
      if ( !other->isSubclassOf( Sentient ) || !( ( (Sentient *)other )->HasItem( key.c_str() ) ) ) 
         {
         Item        *item;
         ClassDef		*cls;  

         cls = getClass( key.c_str() );
		   if ( !cls )
			   {
			   gi.dprintf( "No item named '%s'\n", key.c_str() );
			   return;
			   }
		   item = ( Item * )cls->newInstance();
         item->CancelEventsOfType( EV_Item_DropToFloor );
	      item->CancelEventsOfType( EV_Remove );
         item->ProcessPendingEvents();
         gi.centerprintf ( other->edict, "jcx yv 20 string \"You need this item:\" jcx yv -20 icon %d", item->GetIconIndex() );
         delete item;
         return;
         }
      }

	if ( uselabel.length() )
		{
     	ScriptVariableList *vars;

      // since we use a SafePtr, the thread pointer will be NULL if the thread has ended
      // so we should just clear our label and continue
      if ( !usethread )
			{
         uselabel = "";
         return;
         }

		e = new Event( EV_ScriptThread_Callback );
		e->AddEntity( this );
		e->AddString( uselabel );
		e->AddEntity( other );

	   vars = usethread->Vars();
      vars->SetVariable( "other", other );
      if ( key.length() )
         {
         vars->SetVariable( "key", key.c_str() );
         }
   	usethread->ProcessEvent( e );
		}
	}

void ScriptSlave::OnDamage
	(
	Event *ev
	)

	{
	const char *jumpto;

	damagelabel = "";

	jumpto = ev->GetString( 1 );
	damagethread = ev->GetThread();

	assert( jumpto && damagethread );

	if ( damagethread && !damagethread->labelExists( jumpto ) )
		{
		ev->Error( "Label '%s' not found", jumpto );
		return;
		}

	damagelabel = jumpto;
	}

void ScriptSlave::NoDamage
	(
	Event *ev
	)

	{
	damagelabel = "";
	}

void ScriptSlave::DamageFunc
	( 
	Event *ev
	)

	{
	Event			*e;
	Entity		*inflictor;
	Entity		*attacker;
	int			damage;
   Vector		position;
   Vector		direction;
  	ScriptVariableList *vars;

	if ( damagelabel.length() )
		{
      // since we use a SafePtr, the thread pointer will be NULL if the thread has ended
      // so we should just clear our label and continue
      if ( !damagethread )
			{
         damagelabel = "";
         return;
         }

		attacker	= ev->GetEntity( 3 );

		e = new Event( EV_ScriptThread_Callback );
		e->AddEntity( this );
		e->AddString( damagelabel );
		e->AddEntity( attacker );

      damage		= ev->GetInteger( 1 );
		inflictor	= ev->GetEntity( 2 );
		position		= ev->GetVector( 4 );
		direction	= ev->GetVector( 5 );

		vars = damagethread->Vars();
      vars->SetVariable( "damage", damage );
      vars->SetVariable( "inflictor", inflictor );
      vars->SetVariable( "attacker", attacker );
      vars->SetVariable( "position", position );
      vars->SetVariable( "direction", direction );
   	damagethread->ProcessEvent( e );
		}
	}

void ScriptSlave::SetDamage
	(
	Event *ev
	)

	{
	dmg = ev->GetInteger( 1 );
	}

void ScriptSlave::CreatePath
	(
	SplinePath *path,
	splinetype_t type
	)

	{
	SplinePath	*node;

   if ( !splinePath )
      {
      splinePath = new BSpline;
      }

	splinePath->Clear();
	splinePath->SetType( type );

	node = path;
	while( node != NULL )
		{
  		splinePath->AppendControlPoint( node->worldorigin, node->angles, node->speed );
		node = node->GetNext();

		if ( node == path )
			{
			break;
			}
		}
	}

void ScriptSlave::FollowPath
	(
	Event *ev
	)

	{
   int i, argnum;
   Entity * ent;
   const char * token;
   SplinePath *path;
   qboolean clamp;
   float starttime;


	ent = ev->GetEntity( 1 );
   argnum = 2;
   starttime = -2;
   clamp = true;
   ignoreangles = false;
   splineangles = true;
   for ( i = argnum; i <= ev->NumArgs() ; i++ )
      {
      token = ev->GetString( i );
      if (!strcmpi( token, "ignoreangles"))
         {
         ignoreangles = true;
         }
      if (!strcmpi( token, "normalangles"))
         {
         splineangles = false;
         }
      else if (!strcmpi (token, "loop"))
         {
         clamp = false;
         }
      else if ( IsNumeric( token ) )
         {
         starttime = atof( token );
         }
      else
         {
         ev->Error( "Unknown followpath command %s.", token );
         }
      }
	if ( ent && ent->isSubclassOf( SplinePath ) )
		{
      commandswaiting = true;
		path = ( SplinePath * )ent;
      if ( clamp )
	      CreatePath( path, SPLINE_CLAMP );
      else
	      CreatePath( path, SPLINE_LOOP );
      splineTime = starttime;
		CancelEventsOfType( EV_ScriptSlave_FollowingPath );
      avelocity = vec_zero;
      velocity = vec_zero;
      }
	}

void ScriptSlave::EndPath
	(
	Event *ev
	)
	{
   if ( !splinePath )
      return;

   delete splinePath;
   splinePath = NULL;
   velocity = vec_zero;
   avelocity = vec_zero;
   }

void ScriptSlave::FollowingPath
	(
	Event *ev
	)
	{
	Vector	pos;
	Vector	orient;
   float    speed_multiplier;

   if ( !splinePath )
      return;

   if ( ( splinePath->GetType() == SPLINE_CLAMP ) && ( splineTime > ( splinePath->EndPoint() - 2 ) ) )
      {
      delete splinePath;
      splinePath = NULL;
      velocity = vec_zero;
      avelocity = vec_zero;
      ProcessEvent( EV_ScriptSlave_MoveDone );
      return;
      }

	speed_multiplier = splinePath->Eval( splineTime, pos, orient );

	splineTime += FRAMETIME * speed_multiplier;

   velocity = ( pos - origin ) * ( 1 / FRAMETIME );
   if ( !ignoreangles )
      {
      if ( splineangles )
         {
         avelocity = ( orient - angles ) * ( 1 / FRAMETIME );
         }
      else
         {
         float len;

         len = velocity.length();
         if ( len > 0.05 )
            {
            Vector ang;
            Vector dir;
            float  aroll;

            aroll = avelocity[ ROLL ];
			   dir = velocity * ( 1 / len );
			   ang = dir.toAngles();
			   ang[ PITCH ] = -ang[ PITCH ];
            avelocity = ( ang - angles ) * ( 1 / FRAMETIME );
            avelocity[ ROLL ] = aroll;
            }
         else
            avelocity = vec_zero;
         }
      }
	PostEvent( EV_ScriptSlave_FollowingPath, FRAMETIME );
	}

void ScriptSlave::Explode
	(
	Event *ev
	)
	{
   float radius;
   float scale;
   float damage;

   if ( ev->NumArgs() )
      {
      damage = ev->GetFloat( 1 );
      if ( ev->NumArgs() > 1 )
         {
         scale = ev->GetFloat( 2 );
         }
      else
         {
         radius = size.length() * 0.5f;
         scale = radius * 0.02f;
         }
      CreateExplosion( worldorigin, damage, scale, true, this, this, this );
      }
   else
      {
      radius = size.length() * 0.5f;
      CreateExplosion( worldorigin, radius*3, radius * 0.02f, true, this, this, this );
      }
   }

void ScriptSlave::NotShootable
	(
	Event *ev
	)
	{
   edict->svflags &= ~SVF_SHOOTABLE;
   }


/*****************************************************************************/
/*SINED func_scriptmodel (0 .5 .8) (0 0 0) (0 0 0) NOT_SOLID

/*****************************************************************************/

CLASS_DECLARATION( ScriptSlave, ScriptModel, "func_scriptmodel" );

ResponseDef ScriptModel::Responses[] =
	{
	   { &EV_Gib,				( Response )ScriptModel::GibEvent },
  		{ NULL, NULL },
	};

ScriptModel::ScriptModel()
	{
   const char * animname;
   const char * skinname;
   Vector defangles;

   if ( (gi.IsModel( edict->s.modelindex )) && !mins.length() && !maxs.length())
      {
      gi.CalculateBounds( edict->s.modelindex, edict->s.scale, mins.vec3(), maxs.vec3() );
      }
   // angles
   defangles = Vector( 0, G_GetFloatArg( "angle", 0 ), 0 );
   if (defangles.y == -1)
      {
      defangles = Vector( -90, 0, 0 );
      }
   else if (defangles.y == -2)
      {
      defangles = Vector( 90, 0, 0 );
      }
   angles = G_GetVectorArg( "angles", defangles );
	setAngles( angles );

   animname = G_GetSpawnArg( "anim" );
   if ( animname && strlen(animname) && gi.IsModel( edict->s.modelindex ) )
      {
      int animnum;

      animnum = gi.Anim_NumForName( edict->s.modelindex, animname );
      if (animnum >= 0)
         NextAnim( animnum );
      StartAnimating();
      }
   skinname = G_GetSpawnArg( "skin" );
   if ( skinname && strlen(skinname) && gi.IsModel( edict->s.modelindex ) )
      {
      int skinnum;

      skinnum = gi.Skin_NumForName( edict->s.modelindex, skinname );
      if (skinnum >= 0)
         edict->s.skinnum = skinnum;
      }
	}

void ScriptModel::GibEvent
   ( 
   Event *ev
   )

   {
   int      num,power;
   float    scale;
   str      gibmodel;

   setSolidType( SOLID_NOT );
   hideModel();

   if ( !sv_gibs->value || parentmode->value )
      {
      PostEvent( EV_Remove, 0 );
      return;
      }

   num = ev->GetInteger( 1 );
   power = ev->GetInteger( 2 );
   scale = ev->GetFloat( 3 );
   gibmodel = ev->GetString( 4 );

   power = -power;

   if ( gibmodel == "organic" )
      CreateGibs( this, power, scale, num );
   else if ( gibmodel == "feather" )
      CreateGibs( this, power, scale, num, "feather.def" );

   PostEvent( EV_Remove, 0 );
   }

/*****************************************************************************/
/*SINED func_scriptorigin (0 .5 .8) (-8 -8 -8) (8 8 8)

Used as an alternate origin for objects.  Bind the object to the func_scriptorigin
in order to simulate changing that object's origin.
/*****************************************************************************/

CLASS_DECLARATION( ScriptSlave, ScriptOrigin, "func_scriptorigin" );

ResponseDef ScriptOrigin::Responses[] =
	{
		{ NULL, NULL }
	};

ScriptOrigin::ScriptOrigin()
	{
   edict->svflags &= ~SVF_SHOOTABLE;
	setSolidType( SOLID_NOT );
	}


/*****************************************************************************/
/*SINED func_volumetric (0 .5 .8) ?

Use this to make non-solid volumes.  You still need to set up the surface
properties with the "add" flag.
/*****************************************************************************/

CLASS_DECLARATION( ScriptSlave, ScriptVolumetric, "func_volumetric" );

ResponseDef ScriptVolumetric::Responses[] =
	{
		{ NULL, NULL }
	};

ScriptVolumetric::ScriptVolumetric()
	{
   edict->svflags &= ~SVF_SHOOTABLE;
	setSolidType( SOLID_NOT );
	}
