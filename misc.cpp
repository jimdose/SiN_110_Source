//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/misc.cpp                         $
// $Revision:: 152                                                            $
//   $Author:: Jimdose                                                        $
//     $Date:: 11/19/98 9:29p                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/misc.cpp                              $
// 
// 152   11/19/98 9:29p Jimdose
// fixed telefrags
// 
// 151   11/18/98 6:26p Markd
// Took out fov update for non zero gravaxis 
// 
// 150   11/16/98 11:15p Markd
// made shatter sound not use PHS
// 
// 149   11/16/98 12:57a Markd
// made teleporters work with gravaxis
// 
// 148   11/14/98 11:17p Markd
// bullet proofed glass sounds
// 
// 147   11/14/98 7:57p Markd
// fixed some global alias problems
// 
// 146   11/14/98 1:33a Markd
// fixed shatter using randomglobal sound instead of just normal sound
// 
// 145   11/13/98 6:28p Aldie
// Make Oxygenator only respond to players
// 
// 144   11/11/98 10:02p Jimdose
// added ClipBox
// 
// 143   10/26/98 4:29p Aldie
// Changed misc_oxygen timer
// 
// 142   10/25/98 9:11p Markd
// put in null other protection for activate targets
// 
// 141   10/24/98 12:42a Markd
// changed origins to worldorigins where appropriate
// 
// 140   10/19/98 12:07a Jimdose
// made all code use fast checks for inheritance (no text lookups when
// possible)
// isSubclassOf no longer requires ::_classinfo()
// 
// 139   10/17/98 9:42p Markd
// got rid of event
// 
// 138   10/17/98 8:14p Jimdose
// Changed Damage to DamgeEvent
// 
// 137   10/16/98 12:58a Aldie
// Null check for shatter damage
// 
// 136   10/14/98 12:12a Aldie
// Added intermission file ability
// 
// 135   10/07/98 11:53p Jimdose
// Added BloodSplat
// 
// 134   10/06/98 10:51p Aldie
// Created an oxygenator
// 
// 133   10/05/98 11:29p Markd
// Added MakeBreakingSound
// 
// 132   10/05/98 4:35p Markd
// Made Teleport check for NULL entity
// 
// 131   9/18/98 8:14p Markd
// rewrote surface system so that surfaces are now damaged by surface name
// instead of by surfinfo
// 
// 130   9/17/98 4:11p Aldie
// Teleport objects and a fix for damage_surfaces
// 
// 129   9/15/98 6:37p Markd
// Added RotatedBounds flag support
// 
// 128   9/14/98 3:12p Markd
// replaced zombie/z_hit with debris_generic
// 
// 127   9/09/98 5:06p Markd
// change fov when teleporting
// 
// 126   9/08/98 4:06p Markd
// Fixed damagable surfaces
// 
// 125   9/02/98 12:54p Markd
// fixed teleporters for players
// 
// 124   9/01/98 3:05p Markd
// Rewrote explosion code
// 
// 123   8/31/98 7:45p Aldie
// Updated surface data structure and removed surfinfo field
// 
// 122   8/29/98 9:44p Jimdose
// Added call info to G_Trace
// Moved bodyque to deadbody.cpp
// 
// 121   8/29/98 5:27p Markd
// added specialfx, replaced misc with specialfx where appropriate
// 
// 120   8/29/98 2:53p Aldie
// Updated printing of location based damage
// 
// 119   8/29/98 1:02p Markd
// objects won't shatter unless they hit the world
// 
// 118   8/29/98 12:59p Markd
// Fixed func_explodingwall stuff
// 
// 117   8/27/98 9:02p Jimdose
// Changed centroid to a variable
// 
// 116   8/27/98 3:56p Jimdose
// Fixed NULL pointer bug in DamageSpecificSurface
// 
// 115   8/26/98 5:37p Aldie
// Removed damage_threshold field from surfinfo
// 
// 114   8/24/98 6:52p Jimdose
// Added SetGravityAxis
// 
// 113   8/22/98 9:36p Jimdose
// Added support for alternate gravity axis
// 
// 112   8/20/98 8:38p Jimdose
// DamageSpecificSurface now generates an AI sound event
// 
// 111   8/19/98 8:49p Aldie
// Added random particles for server use
// 
// 110   8/18/98 11:08p Markd
// Added new Alias System
// 
// 109   8/17/98 4:34p Markd
// Added SendOverlay
// 
// 108   8/08/98 9:03p Aldie
// Removed printf
// 
// 107   8/08/98 8:51p Aldie
// Added func_spawnchain and changed spawns to entities
// 
// 106   8/08/98 3:16p Aldie
// Added func_spawnoutofsight to spawn things out of sight of the player.
// 
// 105   8/04/98 5:56p Markd
// Added FuncRemove
// 
// 104   8/02/98 9:00p Markd
// Merged code 3.17
// 
// 103   7/29/98 2:31p Aldie
// Changed health to a float
// 
// 102   7/26/98 5:16a Aldie
// Fixed angle on the func_spawn
// 
// 101   7/25/98 8:00p Aldie
// Move lightstyle client side
// 
// 100   7/25/98 2:09a Jimdose
// Added an assertion to Projectile::Setup
// 
// 99    7/23/98 6:17p Aldie
// Updated damage system and fixed some damage related bugs.  Also put tracers
// back to the way they were, and added gib event to funcscriptmodels
// 
// 98    7/22/98 11:44a Aldie
// Updated doc for func_spawn stuff
// 
// 97    7/21/98 4:22p Aldie
// Put some error checking in func_spawn and func_respawn
// 
// 96    7/21/98 1:10p Aldie
// Added meansofdeath to obituaries
// 
// 95    7/20/98 5:45p Markd
// Put in new shooting out light behaviors
// 
// 94    7/19/98 10:42p Aldie
// Check for weird happenings of dead bodies.
// 
// 93    7/17/98 6:08p Aldie
// Changed func_spawn targetname to spawntargetname
// 
// 92    7/17/98 4:40p Aldie
// Added targetnames to func_spawn
// 
// 91    7/15/98 6:27p Aldie
// Changed func spawn to get a string arg.
// 
// 90    7/15/98 6:18p Markd
// re-ordered SpawnTempDlight arguments
// 
// 89    7/14/98 3:53p Markd
// fixed velocity[2] factor of exploding stuff
// 
// 88    7/13/98 4:59p Aldie
// Added dead player bodies with gibbing
// 
// 87    7/11/98 4:26p Aldie
// Sined fix for func_spawn and func_respawn
// 
// 86    7/11/98 4:12p Aldie
// Dialog layouts
// 
// 85    7/11/98 2:49p Markd
// Added SendDialog event
// 
// 84    7/10/98 10:00p Markd
// made func_explodingwalls work better
// 
// 83    7/10/98 7:07p Aldie
// fixed bug with other not being set for explosion
// 
// 82    7/10/98 4:10p Markd
// Revamped func_explodingwall
// 
// 81    7/08/98 3:11p Aldie
// Added a func_respawn that triggers when the thing it spawns is killed.
// 
// 80    7/03/98 4:10p Jimdose
// Fixed Detail brushes so they aren't removed twice (causing a crash)
// 
// 79    7/02/98 7:57p Markd
// redid func_explodingwall and func_glass
// 
// 78    6/30/98 4:37p Markd
// Added "noise" to func_shatter and func_glass
// 
// 77    6/29/98 8:18p Aldie
// 
// 76    6/25/98 8:47p Markd
// Added keyed items for Triggers, Rewrote Item class, rewrote every pickup
// method
// 
// 75    6/24/98 5:08p Aldie
// Removed some warnings from func_spawn
// 
// 74    6/24/98 4:50p Aldie
// Made func_spawn work.
// 
// 73    6/24/98 12:39p Markd
// Added default tesselation percentage
// 
// 72    6/18/98 6:20p Markd
// put in support for breakable lights
// 
// 71    6/18/98 2:00p Markd
// rewrote tesselation code
// 
// 70    6/17/98 7:40p Markd
// Put in ActivateTargets for both func_shatter and func_glass
// 
// 69    6/17/98 6:31p Aldie
// Put start and end back into beams.
// 
// 68    6/16/98 10:04p Markd
// Put in generic function for DamageSpecificSurface, reworked older two
// 
// 67    6/15/98 12:25p Aldie
// Updated pulse beam
// 
// 66    6/15/98 10:37a Aldie
// Added SpawnPulseBeam
// 
// 65    6/10/98 2:10p Aldie
// Updated damage function.
// 
// 64    6/08/98 7:22p Aldie
// Added in Damage surface by name
// 
// 63    5/28/98 1:23p Aldie
// Added SpawnRocketExplosion to do particles.
// 
// 62    5/27/98 6:56p Markd
// Forgot to remove smoke after creating  tempmodel
// 
// 61    5/27/98 6:10p Markd
// temporarily took out blood splats
// 
// 60    5/27/98 6:06p Aldie
// 
// 59    5/27/98 4:55p Markd
// stopped rotating blood splat
// 
// 58    5/27/98 4:25a Markd
// added bloodspray to SpawnBlood
// 
// 57    5/26/98 11:38p Aldie
// Updated func_spawn
// 
// 56    5/26/98 9:26p Aldie
// Added func_spawn
// 
// 55    5/25/98 12:22p Aldie
// Added func_electrocute
// 
// 54    5/25/98 7:04p Markd
// Fixed up TempModel command
// 
// 53    5/25/98 5:39p Markd
// Fixed SpawnBlood, SpawnSparks and SpawnDlight
// 
// 52    5/24/98 8:46p Jimdose
// Made a lot of functions more str-friendly.
// Got rid of a lot of char * based strings
// Cleaned up get spawn arg functions and sound functions
// sound functions now use consistant syntax
// 
// 51    5/24/98 3:48p Jimdose
// maxhealth was supposed to be max_health
// 
// 50    5/24/98 3:36p Markd
// Added impact sounds for glass
// 
// 49    5/24/98 1:03a Jimdose
// Added sound events for ai
// 
// 48    5/23/98 10:39p Markd
// Added TempModel call
// 
// 47    5/20/98 1:33p Markd
// Changed func_shatter behavior
// 
// 46    5/18/98 8:13p Jimdose
// Renamed Navigator back to PathManager
// 
// 45    5/16/98 4:59p Markd
// Changed func_shatter
// 
// 44    5/13/98 6:19p Markd
// Added BurnWall
// 
// 43    5/13/98 4:46p Aldie
// Fixed damage surfaces.
// 
// 42    5/12/98 1:21p Aldie
// Update damage surfaces
// 
// 41    5/06/98 7:48p Markd
// Added state and light style support to damaged textures
// 
// 40    5/05/98 8:37p Aldie
// Added virtual setup function to Projectile.
// 
// 39    5/05/98 5:34p Aldie
// Updated damage surfaces
// 
// 38    5/05/98 2:38p Jimdose
// Disabled spawnblood
// 
// 37    5/03/98 8:10p Markd
// Added SpawnSparks and patched SpawnBlood
// 
// 36    5/03/98 4:35p Jimdose
// Changed Vector class
// 
// 35    5/02/98 8:48p Markd
// Added lightstyle for blood
// 
// 34    5/01/98 11:09a Markd
// Added sound to tesselation event
// 
// 33    4/28/98 4:04p Jimdose
// Fixed typo in docs for func_shatter and func_glass
// 
// 32    4/27/98 3:52p Jimdose
// Teleporters inform Navigator when used so that paths may be generated
// through them
// 
// 31    4/18/98 2:32p Jimdose
// Added ExplodingWall, Shatter, and Glass
// 
// 30    4/10/98 4:57p Jimdose
// Made bubbles work better
// 
// 29    4/07/98 11:54p Jimdose
// Changed beams to use color_r, color_g, and color_b
// 
// 28    4/05/98 5:05a Jimdose
// fixed teleport not responding bug
// 
// 27    4/05/98 1:57a Jimdose
// Fixed bug in DamageSurface where the surface was referenced without checking
// for a null pointer
// 
// 26    4/04/98 6:06p Jimdose
// Added Bubble, Projectile, and Smoke
// Made response from EV_Trigger_ActivateTargets to EV_Trigger_Effect
// 
// 25    4/01/98 6:05p Jimdose
// Made setBeam use setOrigin
// 
// 24    3/30/98 2:40p Jimdose
// Made teleporters handle non-clients
// Reenabled spawnblood
// 
// 23    3/29/98 9:41p Jimdose
// Changed killed to an event
// 
// 22    3/28/98 6:39p Jimdose
// Left some code commented out.  oops! :P
// 
// 21    3/28/98 6:37p Jimdose
// Made teleporters work
// 
// 20    3/23/98 1:31p Jimdose
// Revamped event and command system
// 
// 19    3/11/98 2:23p Jimdose
// Moved AreaPortals to areaportal.cpp
// Breakaway walls now use areaportals
// 
// 18    3/05/98 3:48p Aldie
// More damage surfaces stuff.
// 
// 17    3/04/98 8:01p Aldie
// More support for damage surfaces.
// 
// 16    3/02/98 8:49p Jimdose
// Changed the classid parameter of CLASS_DECLARATION to a quoted string so
// that you could have a NULL classid.
// 
// 15    3/02/98 5:42p Jimdose
// Moved light entities to light.cpp
// 
// 14    2/27/98 12:50p Jimdose
// Added Light, LightRamp, and TriggerLightStyle
// 
// 13    2/21/98 1:07p Jimdose
// Added Beam class
// 
// 12    2/17/98 8:09p Jimdose
// Changed Detail to print a warning if it has a null model
// 
// 11    2/06/98 5:39p Jimdose
// Moved Sined definitions into file
// 
// 9     2/03/98 10:43a Jimdose
// Updated to work with Quake 2 engine
// 
// 7     11/11/97 10:22a Markd
// Added precache for zombie/z_hit.wav
// 
// 6     10/29/97 4:18p Jimdose
// Bubbles can now only exist in water.
// 
// 5     10/28/97 8:20p Jimdose
// added Bubble
// 
// 4     10/27/97 3:29p Jimdose
// Removed dependency on quakedef.h
// 
// 3     10/01/97 11:24a Markd
// moved viewthing to its own file
// 
// 2     9/26/97 6:14p Jimdose
// Added standard Ritual headers
//
// DESCRIPTION:
// Basically the big stew pot of the DLLs, or maybe a garbage bin, whichever
// metaphore you prefer.  This really should be cleaned up.  Anyway, this
// should contain utility functions that could be used by any entity.
// Right now it contains everything from entities that could be in their
// own file to my mother's pot roast recipes.
// 

#include "g_local.h"
#include "entity.h"
#include "trigger.h"
#include "explosion.h"
#include "areaportal.h"
#include "misc.h"
#include "navigate.h"
#include "deadbody.h"
#include "specialfx.h"
#include "player.h"

/*
================
SendDialog
================
*/
void SendDialog
	(
   const char *icon_name,
   const char *dialog_text
	)
	{
   char imageindex;
   char temp[ 1024 ];

   imageindex = gi.imageindex( icon_name );
   Com_sprintf( temp, sizeof( temp ), "dia %d \"%s\"", imageindex, dialog_text );
	gi.WriteByte( svc_console_command );
   gi.WriteString( temp );
	gi.multicast( vec3_origin, MULTICAST_ALL );
	}

/*
================
SendOverlay
================
*/
void SendOverlay
	(
   Entity *ent,
   str overlayname
	)
   {
   if ( ent )
      {
      gi.WriteByte( svc_console_command );
      gi.WriteString( va( "lo %s",overlayname.c_str() ) );
   	gi.unicast ( ent->edict, true);
      }
   else
      {
      gi.WriteByte( svc_console_command );
      gi.WriteString( va( "lo %s",overlayname.c_str() ) );
      gi.multicast( NULL, MULTICAST_ALL );
      }
   }

/*
================
SendIntermission
================
*/
void SendIntermission
	(
   Entity *ent,
   str intermissionname
	)
   {
   if ( ent )
      {
      gi.WriteByte( svc_console_command );
      gi.WriteString( va( "imf %s",intermissionname.c_str() ) );
   	gi.unicast ( ent->edict, true);
      }
   else
      {
      gi.WriteByte( svc_console_command );
      gi.WriteString( va( "imf %s",intermissionname.c_str() ) );
      gi.multicast( NULL, MULTICAST_ALL );
      }
   }

/*****************************************************************************/
/*SINED func_group (0 0 0) ?

Used to group brushes together just for editor convenience.

/*****************************************************************************/

/*****************************************************************************/
/*SINED func_remove (0 0.5 0) ?

Used for lighting and such

/*****************************************************************************/

CLASS_DECLARATION( Entity, FuncRemove, "func_remove" );

ResponseDef FuncRemove::Responses[] =
	{
		{ NULL, NULL }
	};

FuncRemove::FuncRemove()
	{
	ProcessEvent( EV_Remove );
	}


/*****************************************************************************/
/*SINED info_null (0 0.5 0) (-4 -4 -4) (4 4 4)

Used as a positional target for spotlights, etc.

/*****************************************************************************/

CLASS_DECLARATION( Entity, InfoNull, "info_null" );

ResponseDef InfoNull::Responses[] =
	{
		{ NULL, NULL }
	};

InfoNull::InfoNull()
	{
	ProcessEvent( EV_Remove );
	}

/*****************************************************************************/
/*SINED info_notnull (0 0.5 0) (-4 -4 -4) (4 4 4)

Used as a positional target for lightning.

/*****************************************************************************/

CLASS_DECLARATION( Entity, InfoNotNull, "info_notnull" );

ResponseDef InfoNotNull::Responses[] =
	{
		{ NULL, NULL }
	};

/*****************************************************************************/
/*SINED func_electrocute (0 .5 .8) ?
"radius" - range of the effect (Default is 500)
"key"    The item needed to activate this. (default nothing)
  Electrocutes everything it can see if it is in the water
/*****************************************************************************/

CLASS_DECLARATION( Trigger, Electrocute, "func_electrocute" );

ResponseDef Electrocute::Responses[] =
	{
      { &EV_Trigger_Effect,				( Response )Electrocute::KillSight },
      { NULL, NULL }
	};

Electrocute::Electrocute()
	{
	setOrigin( origin );
	setSolidType( SOLID_NOT );
	setMoveType( MOVETYPE_NONE );

   radius = G_GetFloatArg("radius", 500);
	}

void Electrocute::KillSight(Event *ev)
   {
   Entity *other = ev->GetEntity( 1 );
   Entity *ent;

   ent = findradius( NULL, worldorigin, radius );
	while( ent )
		{
		if ( ( ent != this ) && ( !ent->deadflag ) )
			{
         if (ent->waterlevel)
            {
			   ent->Damage( this, other, ent->health, ent->worldorigin, vec_zero, vec_zero, 0, DAMAGE_NO_ARMOR, MOD_ELECTRIC, -1, -1, 1.0f );
            }
			}
		ent = findradius( ent, worldorigin, radius );
		}
   }



/*****************************************************************************/
/*SINED func_spawn(0 .5 .8) (-8 -8 -8) (8 8 8)
"modelname" The name of the .def file you wish to spawn. (Required)
"spawntargetname" This will be the targetname of the spawned model. (default is null)
"key"       The item needed to activate this. (default nothing)
"attackmode" Attacking mode of the spawned actor (default 0)
/*****************************************************************************/

CLASS_DECLARATION( Entity, Spawn, "func_spawn" );

ResponseDef Spawn::Responses[] =
	{
      { &EV_Activate,         ( Response )Spawn::DoSpawn },
      { NULL, NULL }
	};

Spawn::Spawn()
	{
	setSolidType( SOLID_NOT );
	setMoveType( MOVETYPE_NONE );
   hideModel();
   modelname = G_GetStringArg( "modelname", NULL );
   angles = Vector( va( "0 %f 0", G_GetFloatArg( "angle", 0 ) ) );

   if ( !modelname.length() )
      warning("Spawn", "modelname not set" );

   spawntargetname = G_GetStringArg( "spawntargetname", NULL );
   attackmode      = G_GetIntArg( "attackmode", 0 );
   }

void Spawn::DoSpawn( Event *ev )
   {   
   char			         temp[ 128 ];

   // Clear the spawn args
   G_InitSpawnArguments();
   
   sprintf( temp, "%f %f %f", worldorigin[ 0 ], worldorigin[ 1 ], worldorigin[ 2 ] );
   G_SetSpawnArg( "origin", temp );
   sprintf( temp, "%f", angles[ 1 ] );
   G_SetSpawnArg( "angle", temp );
   G_SetSpawnArg( "model", modelname.c_str() );
   G_SetSpawnArg( "targetname", spawntargetname.c_str() );
   G_SetSpawnArg( "attackmode", va( "%i",attackmode ) );

   G_CallSpawn();
   // Clear the spawn args
   G_InitSpawnArguments();
   }

/*****************************************************************************/
/*SINED func_respawn(0 .5 .8) (-8 -8 -8) (8 8 8) 
When the thing that is spawned is killed, this func_respawn will get 
triggered.
"modelname"   The name of the .def file you wish to spawn. (Required)
"spawntargetname" This will be the targetname of the spawned model. (default is null)
"key"         The item needed to activate this. (default nothing)
/*****************************************************************************/

CLASS_DECLARATION( Spawn, ReSpawn, "func_respawn" );

ResponseDef ReSpawn::Responses[] =
	{
      { NULL, NULL }
	};

void ReSpawn::DoSpawn( Event *ev )
   {
   char			         temp[ 128 ];

   // Clear the spawn args
   G_InitSpawnArguments();
   
   sprintf( temp, "%f %f %f", worldorigin[ 0 ], worldorigin[ 1 ], worldorigin[ 2 ] );
   G_SetSpawnArg( "origin", temp );
   sprintf( temp, "%f", angles[ 1 ] );
   G_SetSpawnArg( "angle", temp );
   G_SetSpawnArg( "model", modelname.c_str() );
   
   // This will trigger the func_respawn when the thing dies
   G_SetSpawnArg( "targetname", TargetName() );
   G_SetSpawnArg( "target", TargetName() );

   G_CallSpawn();
   // Clear the spawn args
   G_InitSpawnArguments();
   }

/*****************************************************************************/
/*SINED func_spawnoutofsight(0 .5 .8) (-8 -8 -8) (8 8 8) 
Will only spawn something out of sight of its targets.
"modelname"   The name of the .def file you wish to spawn. (Required)
"spawntargetname" This will be the targetname of the spawned model. (default is null)
"key"         The item needed to activate this. (default nothing)
/*****************************************************************************/

CLASS_DECLARATION( Spawn, SpawnOutOfSight, "func_spawnoutofsight" );

ResponseDef SpawnOutOfSight::Responses[] =
	{
      { NULL, NULL }
	};

void SpawnOutOfSight::DoSpawn
	(
	Event *ev
	)

   {
   char     temp[ 128 ];
   int      i;
   Entity	*ent;
	edict_t	*ed;
   trace_t  trace;
   qboolean seen = false;

   // Check to see if I can see any players before spawning
 	for( i = 0; i < game.maxclients; i++ )
      {
		ed = &g_edicts[ 1 + i ];
		if ( !ed->inuse || !ed->entity )
			{
			continue;
			}

		ent = ed->entity;
	   if ( ( ent->health < 0 ) || ( ent->flags & FL_NOTARGET ) )
			{
			continue;
			}

      trace = G_Trace( worldorigin, vec_zero, vec_zero, ent->centroid, this, MASK_OPAQUE, "SpawnOutOfSight::DoSpawn" );
      if ( trace.fraction == 1.0 )
         {
         seen = true;
         break;
         }
      }

   if ( seen )
      return;

   // Clear the spawn args
   G_InitSpawnArguments();
   
   sprintf( temp, "%f %f %f", worldorigin[ 0 ], worldorigin[ 1 ], worldorigin[ 2 ] );
   G_SetSpawnArg( "origin", temp );
   sprintf( temp, "%f", angles[ 1 ] );
   G_SetSpawnArg( "angle", temp );
   G_SetSpawnArg( "model", modelname.c_str() );
   G_SetSpawnArg( "targetname", spawntargetname.c_str() );

   G_CallSpawn();
   // Clear the spawn args
   G_InitSpawnArguments();
   }


/*****************************************************************************/
/*SINED func_spawnchain(0 .5 .8) (-8 -8 -8) (8 8 8) 
Tries to spawn something out of the sight of players.  If it fails, it will
trigger its targets. 
"modelname"   The name of the .def file you wish to spawn. (Required)
"spawntargetname" This will be the targetname of the spawned model. (default is null)
"key"         The item needed to activate this. (default nothing)
/*****************************************************************************/

CLASS_DECLARATION( Spawn, SpawnChain, "func_spawnchain" );

ResponseDef SpawnChain::Responses[] =
	{
      { NULL, NULL }
	};

void SpawnChain::DoSpawn
	(
	Event *ev
	)

   {
   char        temp[ 128 ];
   int         i,num;
   Entity	   *ent;
	edict_t	   *ed;
   trace_t     trace;
   qboolean    seen = false;
   const char  *name;
   Event       *event;

   // Check to see if this can see any players before spawning
 	for( i = 0; i < game.maxclients; i++ )
      {
		ed = &g_edicts[ 1 + i ];
		if ( !ed->inuse || !ed->entity )
			{
			continue;
			}

		ent = ed->entity;
	   if ( ( ent->health < 0 ) || ( ent->flags & FL_NOTARGET ) )
			{
			continue;
			}

      trace = G_Trace( worldorigin, vec_zero, vec_zero, ent->centroid, this, MASK_OPAQUE, "SpawnChain::DoSpawn" );
      if ( trace.fraction == 1.0 )
         {
         seen = true;
         break;
         }
      }

   // Couldn't spawn anything, so activate targets
   if ( seen )
      {   
   	name = Target();
	   if ( name && strcmp( name, "" ) )
		   {
		   num = 0;
		   do            
			   {
			   num = G_FindTarget( num, name );
			   if ( !num )
				   {
				   break;
				   }
   			ent = G_GetEntity( num );
		
		   	event = new Event( EV_Activate );	   		
            event->AddEntity( world );
			   ent->PostEvent( event, 0 );
            } while ( 1 );
         }
      return;
      }

   // Can't see the player, so do the spawn
   G_InitSpawnArguments();
   sprintf( temp, "%f %f %f", worldorigin[ 0 ], worldorigin[ 1 ], worldorigin[ 2 ] );
   G_SetSpawnArg( "origin", temp );
   sprintf( temp, "%f", angles[ 1 ] );
   G_SetSpawnArg( "angle", temp );
   G_SetSpawnArg( "model", modelname.c_str() );
   G_SetSpawnArg( "targetname", spawntargetname.c_str() );
   G_CallSpawn();
   G_InitSpawnArguments();
   }

/*****************************************************************************/
/*SINED func_wall (0 .5 .8) ?

This is just a solid wall if not inhibitted

/*****************************************************************************/

CLASS_DECLARATION( Entity, Wall, "func_wall" );

ResponseDef Wall::Responses[] =
	{
		{ NULL, NULL }
	};

Wall::Wall()
	{
	setOrigin( origin );
	setSolidType( SOLID_BSP );
	setMoveType( MOVETYPE_PUSH );
	}

/*****************************************************************************/
/*SINED func_illusionary (0 .5 .8) ?

A simple entity that looks solid but lets you walk through it.

/*****************************************************************************/

CLASS_DECLARATION( Entity, IllusionaryWall, "func_illusionary" );

ResponseDef IllusionaryWall::Responses[] =
	{
		{ NULL, NULL }
	};

IllusionaryWall::IllusionaryWall()
	{
	setSolidType( SOLID_NOT );
	setMoveType( MOVETYPE_NONE );
	}

/*****************************************************************************/
/*SINED func_breakawaywall (0 .5 .8) ? x x NOT_PLAYERS MONSTERS PROJECTILES

Special walltype that removes itself when triggered.  Will also trigger
any func_areaportals that it targets.

"key"          The item needed to activate this. (default nothing)

If NOT_PLAYERS is set, the trigger does not respond to players
If MONSTERS is set, the trigger will respond to monsters
If PROJECTILES is set, the trigger will respond to projectiles (rockets, grenades, etc.)

/*****************************************************************************/

CLASS_DECLARATION( TriggerOnce, BreakawayWall, "func_breakawaywall" );

Event EV_BreakawayWall_Setup( "BreakawayWall_Setup" );

ResponseDef BreakawayWall::Responses[] =
	{
		{ &EV_Touch,							NULL },
	   { &EV_Trigger_Effect,				( Response )BreakawayWall::BreakWall },
	   { &EV_BreakawayWall_Setup,			( Response )BreakawayWall::Setup },
		{ NULL, NULL }
	};

void BreakawayWall::BreakWall
	(
	Event *ev
	)

	{
	SetAreaPortals( Target(), true );
	ActivateTargets( ev );
	}

void BreakawayWall::Setup
	(
	Event *ev
	)

	{
	SetAreaPortals( Target(), false );
	}

BreakawayWall::BreakawayWall()
	{
	showModel();
	setMoveType( MOVETYPE_PUSH );
	setSolidType( SOLID_BSP );
	PostEvent( EV_BreakawayWall_Setup, 0.1 );
	respondto = spawnflags ^ TRIGGER_PLAYERS;
	};

/*****************************************************************************/
/*SINED func_explodingwall (0 .5 .8) ? RANDOMANGLES LANDSHATTER NOT_PLAYERS MONSTERS PROJECTILES INVISIBLE ACCUMALATIVE TWOSTAGE

Blows up on activation or when attacked

"explosions"   number of explosions to spawn ( default 1 )
"land_angles"  The angles you want this piece to\
               orient to when it lands on the ground
"land_radius"  The distance of the ground the piece\
               should be when on the ground ( default 0 )
"anglespeed"   Speed at which pieces rotate ( default 100 ) \
               if RANDOMANGLES ( default is 600 )
"key"          The item needed to activate this. (default nothing)

IF RANDOMANGLES is set, object randomly spins while in the air.
IF LANDSHATTER is set, object shatters when it hits the ground.
IF TWOSTAGE is set, object can be shattered once it lands on the ground.
IF ACCUMALATIVE is set, damage is accumlative not threshold
IF INVISIBLE is set, these are invisible and not solid until triggered
If NOT_PLAYERS is set, the trigger does not respond to players
If MONSTERS is set, the trigger will respond to monsters
If PROJECTILES is set, the trigger will respond to projectiles (rockets, grenades, etc.)

/*****************************************************************************/
#define RANDOMANGLES ( 1 << 0 )
#define LANDSHATTER  ( 1 << 1 )
#define INVISIBLE    ( 1 << 5 )
#define ACCUMULATIVE ( 1 << 6 )
#define TWOSTAGE     ( 1 << 7 )

CLASS_DECLARATION( Trigger, ExplodingWall, "func_explodingwall" );

Event EV_ExplodingWall_StopRotating( "stoprotating" );
Event EV_ExplodingWall_OnGround( "checkonground" );

ResponseDef ExplodingWall::Responses[] =
	{
		{ &EV_Trigger_Effect,	( Response )Explode },
		{ &EV_Damage,				( Response )DamageEvent },
		{ &EV_Touch,				( Response )TouchFunc },
		{ &EV_ExplodingWall_StopRotating, ( Response )StopRotating },
		{ &EV_ExplodingWall_OnGround, ( Response )CheckOnGround },
		{ NULL, NULL }
	};

void ExplodingWall::Explode
	(
	Event *ev
	)

	{
	Entity		*other;
	Vector		pos;
   Vector      mins, maxs;
	int			i;

   if ( spawnflags & INVISIBLE )
      {
	   showModel();
	   setSolidType( SOLID_BSP );
   	takedamage = DAMAGE_YES;
      }

	if ( takedamage == DAMAGE_NO )
		{
		return;
		}

	other = ev->GetEntity( 1 );

	health = 0;
	takedamage = DAMAGE_NO;

	// Create explosions
	for( i = 0; i < explosions; i++ )
		{
		pos[ 0 ] = absmin[ 0 ] + G_Random( size[ 0 ] );
		pos[ 1 ] = absmin[ 1 ] + G_Random( size[ 1 ] );
		pos[ 2 ] = absmin[ 2 ] + G_Random( size[ 2 ] );

		CreateExplosion( pos, dmg, 1.0f, true, this, other, this );
		}
	
	// throw itself
   state = 1;
   on_ground = false;
   PostEvent( EV_ExplodingWall_OnGround, 0.1f );
	velocity[ 0 ] = G_CRandom( 70 );
	velocity[ 1 ] = G_CRandom( 70 );
	velocity[ 2 ] = 140 + G_Random( 70 );
	setMoveType( MOVETYPE_BOUNCE );
	setSolidType( SOLID_BBOX );
   if ( spawnflags & RANDOMANGLES )
      {
	   avelocity[ 0 ] = G_Random( angle_speed );
	   avelocity[ 1 ] = G_Random( angle_speed );
	   avelocity[ 2 ] = G_Random( angle_speed );
      }
   else
      {
      Vector delta;
      float most;
      float time;
      int   t;

      delta = land_angles - worldangles;
      if ( delta[ 0 ] > 180 )
         delta[ 0 ] -= 360;
      if ( delta[ 0 ] < -180 )
         delta[ 0 ] += 360;
      if ( delta[ 1 ] > 180 )
         delta[ 1 ] -= 360;
      if ( delta[ 1 ] < -180 )
         delta[ 1 ] += 360;
      if ( delta[ 2 ] > 180 )
         delta[ 2 ] -= 360;
      if ( delta[ 2 ] < -180 )
         delta[ 2 ] += 360;
      most = MaxValue( delta );
      if ( !angle_speed )
         angle_speed = 1;
      t = 10 * most / angle_speed;
      time = (float)t / 10;
      delta = delta * (1.0/time);
      avelocity = delta;
      PostEvent( EV_ExplodingWall_StopRotating, time );
      state = 2;
      }

	ActivateTargets( ev );

   if ( land_radius > 0 )
      {
      mins[0] = mins[1] = mins[2] = -land_radius;
      maxs[0] = maxs[1] = maxs[2] = land_radius;
	   setSize( mins, maxs );
      }

	attack_finished = 0;
	}

void ExplodingWall::DamageEvent
	(
	Event *ev
	)

	{
	Event			*event;
	Entity		*inflictor;
	Entity		*attacker;
	int			damage;

	if ( takedamage == DAMAGE_NO )
		{
		return;
		}

   if ( on_ground )
      {
      GroundDamage( ev );
      return;
      }

	damage		= ev->GetInteger( 1 );
	inflictor	= ev->GetEntity( 2 );
	attacker		= ev->GetEntity( 3 );

   if ( spawnflags & ACCUMULATIVE )
      {
      health -= damage;
      if ( health > 0 )
         return;
      }
   else
      {
	   if ( damage < health )
		   {
		   return;
		   }
      }

	event = new Event( EV_Activate );
	event->AddEntity( attacker );
	ProcessEvent( event );
	}

void ExplodingWall::GroundDamage
	(
	Event *ev
	)

	{
   Vector      dir;
	Entity		*inflictor;
	Entity		*attacker;
	Vector		pos;
	int			damage;

	if ( takedamage == DAMAGE_NO )
		{
		return;
		}

	damage		= ev->GetInteger( 1 );
	inflictor	= ev->GetEntity( 2 );
	attacker		= ev->GetEntity( 3 );

   if ( spawnflags & ACCUMULATIVE )
      {
      health -= damage;
      if ( health > 0 )
         return;
      }
   else
      {
	   if ( damage < health )
		   {
		   return;
		   }
      }

   if ( explosions )
      {
		pos[ 0 ] = absmin[ 0 ] + G_Random( size[ 0 ] );
		pos[ 1 ] = absmin[ 1 ] + G_Random( size[ 1 ] );
		pos[ 2 ] = absmin[ 2 ] + G_Random( size[ 2 ] );

		CreateExplosion( pos, damage, 1.0f, true, this, attacker, this );
      }
   takedamage = DAMAGE_NO;
   hideModel();
   dir = worldorigin - attacker->worldorigin;
   TesselateModel
      (
      this,
      tess_min_size,
      tess_max_size,
      dir,
      damage,
      tess_percentage,
      tess_thickness,
      vec3_origin
      );
	ProcessEvent( EV_BreakingSound );
   PostEvent( EV_Remove, 0 );
	}

void ExplodingWall::SetupSecondStage
	(
   void
	)

	{
   health = max_health;
	takedamage = DAMAGE_YES;
	}

void ExplodingWall::StopRotating
	(
	Event *ev
	)

	{
   avelocity = vec_zero;
   setAngles( land_angles );
   if ( spawnflags & TWOSTAGE )
      SetupSecondStage();
	}

void ExplodingWall::CheckOnGround
	(
	Event *ev
	)

	{
   if ( ( velocity == vec_zero ) && groundentity )
      {
      Vector delta;
      float most;
      float time;
      int   t;

      delta = land_angles - worldangles;
      if ( delta.length() > 1 )
         {
         if ( delta[ 0 ] > 180 )
            delta[ 0 ] -= 360;
         if ( delta[ 0 ] < -180 )
            delta[ 0 ] += 360;
         if ( delta[ 1 ] > 180 )
            delta[ 1 ] -= 360;
         if ( delta[ 1 ] < -180 )
            delta[ 1 ] += 360;
         if ( delta[ 2 ] > 180 )
            delta[ 2 ] -= 360;
         if ( delta[ 2 ] < -180 )
            delta[ 2 ] += 360;
         most = MaxValue( delta );
         if ( angle_speed > 3 )
            t = 10.0f * most / ( angle_speed / 3 );
         else
            t = 10.0f * most;
         time = (float)t / 10;
         delta = delta * (1.0/time);
         avelocity = delta;
         PostEvent( EV_ExplodingWall_StopRotating, time );
         }
      state = 2;
	   setSize( orig_mins, orig_maxs );
      on_ground = true;
      }
   else
      PostEvent( ev, 0.1f );
	}

void ExplodingWall::TouchFunc
	(
	Event *ev
	)

	{
	Entity *other;

	if ( ( velocity == vec_zero ) || ( level.time < attack_finished ) )
		{
		return;
		}

   other = ev->GetEntity( 1 );

   if ( ( spawnflags & LANDSHATTER ) && ( other == world ) )
      {
      Vector pos;

   	takedamage = DAMAGE_NO;

      if ( explosions )
         {
		   pos[ 0 ] = absmin[ 0 ] + G_Random( size[ 0 ] );
		   pos[ 1 ] = absmin[ 1 ] + G_Random( size[ 1 ] );
		   pos[ 2 ] = absmin[ 2 ] + G_Random( size[ 2 ] );

		   CreateExplosion( pos, dmg, 1.0f, true, this, other, this );
         }
      hideModel();
      TesselateModel
         (
         this,
         tess_min_size,
         tess_max_size,
         vec_zero,
         100,
         tess_percentage,
         tess_thickness,
         vec3_origin
         );
		ProcessEvent( EV_BreakingSound );
      PostEvent( EV_Remove, 0 );
      return;
      }

	if ( other->takedamage )
		{
		other->Damage( this, activator, dmg, worldorigin, vec_zero, vec_zero, 20, 0, MOD_EXPLODEWALL, -1, -1, 1.0f );
		RandomGlobalSound( "debris_generic", 1, CHAN_WEAPON, ATTN_NORM );
		attack_finished = level.time + 0.1;
		}
	}

ExplodingWall::ExplodingWall()
	{
   if ( spawnflags & INVISIBLE )
      {
	   if ( Targeted() )
   	  	takedamage = DAMAGE_YES;
      else
         takedamage = DAMAGE_NO;
      hideModel();
	   setSolidType( SOLID_NOT );
      }
   else
      {
	   showModel();
	   setSolidType( SOLID_BSP );
     	takedamage = DAMAGE_YES;
      }
	setMoveType( MOVETYPE_PUSH );
	setOrigin( origin );

	health = G_GetFloatArg( "health", 60 );
	max_health = health;
   on_ground = false;

   state = 0;
   if ( spawnflags & RANDOMANGLES )
   	angle_speed = G_GetFloatArg( "anglespeed", 600 );
   else
   	angle_speed = G_GetFloatArg( "anglespeed", 100 );

	land_radius = G_GetFloatArg( "land_radius", 0 );
	land_angles = G_GetVectorArg( "land_angles" );
	dmg = G_GetIntArg( "dmg", 10 );
	explosions = G_GetIntArg( "explosions", 1 );

   orig_mins = mins;
   orig_maxs = maxs;

	respondto = spawnflags ^ TRIGGER_PLAYERS;
	}

/*****************************************************************************/
/*SINED detail (0.5 0 1.0) ?

Used to fake details before the Quake 2 merge.

/*****************************************************************************/

CLASS_DECLARATION( Entity, Detail, "detail" );

ResponseDef Detail::Responses[] =
	{
		{ NULL, NULL }
	};

Detail::Detail()
	{
	// Be an asshole to the level designers so that they make the change asap.
	gi.dprintf( "Detail brushes are no longer needed.  Use Surface attributes.\n" );

	if ( !G_GetSpawnArg( "model" ) )
		{
		gi.dprintf( "Detail brush with NULL model removed!!!\n" );
		ProcessEvent( EV_Remove );
		}
	else
		{
		ProcessEvent( EV_Remove );
		}
	}

/*****************************************************************************/
/*SINED misc_oxygen (1 0 0) ? VISIBLE

Touching this entity will reset the drowning time - only
responds to players.

"key" The item needed to activate this. (default nothing)
/*****************************************************************************/

CLASS_DECLARATION( Trigger, Oxygenator, "misc_oxygen" );

ResponseDef Oxygenator::Responses[] =
	{
	   { &EV_Trigger_Effect,	( Response )Oxygenator::Oxygenate },
		{ NULL, NULL }
	};

Oxygenator::Oxygenator()
	{
	if ( spawnflags & 1 )
		{
		showModel();
		}

   time = 20;
	respondto = TRIGGER_PLAYERS;
	}

EXPORT_FROM_DLL void Oxygenator::Oxygenate
	(
	Event *ev
	)

   {
   Entity *other;
   Player *player;

   other = ev->GetEntity( 1 );

   if ( !other )
      return;

   player = ( Player * )( Sentient * )other;
   player->GiveOxygen( time );
   }

/*****************************************************************************/
/*SINED misc_teleporter (1 0 0) ? VISIBLE x NOT_PLAYERS NOT_MONSTERS NOT_PROJECTILES

Touching this entity will teleport players to the targeted object.

"key" The item needed to activate this. (default nothing)

If NOT_PLAYERS is set, the teleporter does not teleport players
If NOT_MONSTERS is set, the teleporter does not teleport monsters
If NOT_PROJECTILES is set, the teleporter does not teleport projectiles (rockets, grenades, etc.)

/*****************************************************************************/

CLASS_DECLARATION( Trigger, Teleporter, "misc_teleporter" );

ResponseDef Teleporter::Responses[] =
	{
	   { &EV_Trigger_Effect,	( Response )Teleporter::Teleport },
		{ NULL, NULL }
	};

EXPORT_FROM_DLL void Teleporter::Teleport
	(
	Event *ev
	)

	{
	gclient_t	*client;
	Entity		*dest;
	int			num;
	int			i;
	Entity		*other;
	Vector		mid;

	other = ev->GetEntity( 1 );

   if ( !other || ( other == world ) )
      return;

	num = G_FindTarget( 0, Target() );
	if ( !num )
		{
		warning( "Teleport", "Couldn't find destination\n" );
		return;
		}

	dest = G_GetEntity( num );
	assert( dest );

   other->RandomGlobalSound( "snd_teleport" );

	// unlink to make sure it can't possibly interfere with KillBox
	other->unlink();

	if ( other->isSubclassOf( Sentient ) )
		{
		PathManager.Teleport( other, other->worldorigin, dest->worldorigin );
		other->worldorigin = dest->worldorigin + Vector( 0, 0, 1 );
		other->velocity = vec_zero;
		}
	else
		{
		mid = ( absmax - absmin ) * 0.5;
		other->worldorigin = dest->worldorigin + Vector( 0, 0, 1 );
      other->origin += mid;
		}

	// draw the teleport splash at the destination
	//other->edict->s.event = EV_PLAYER_TELEPORT;

   // set angles
	other->setAngles( dest->angles );

	// set their gravity axis
	other->SetGravityAxis( gravaxis );

   if ( other->client )
		{
      Event * ev;
		client = other->client;

      if ( !gravaxis )
         {
		   // clear the velocity and hold them in place briefly
		   client->ps.pmove.pm_time = 100;
         client->ps.pmove.pm_flags |= PMF_TIME_TELEPORT;

         ev = new Event( EV_Player_SaveFov );
         other->ProcessEvent( ev );

         ev = new Event( EV_Player_Fov );
         ev->AddFloat( 180 );
         other->ProcessEvent( ev );
         }

      /*
      if ( gravaxis )
         {
         ev = new Event( EV_Player_RestoreFov );
         other->PostEvent( ev, 0.1f );
         }
      */

		for( i = 0; i < 3; i++ )
			{
			client->ps.pmove.delta_angles[ i ] = ANGLE2SHORT( dest->angles[ i ] - client->resp.cmd_angles[ i ] );
			}

		VectorCopy( angles.vec3(), client->ps.viewangles );
		}

	if ( dest->isSubclassOf( TeleporterDestination ) && !gravaxis )
		{
		float len;

		len = other->velocity.length();
      //
      // give them a bit of a push
      //
      if ( len < 400 )
         len = 400;
		other->velocity = ( ( TeleporterDestination * )dest )->movedir * len;
		}

	// kill anything at the destination
	KillBox( other );

	other->setOrigin( other->worldorigin );
	other->worldorigin.copyTo( other->edict->s.old_origin );
	}

Teleporter::Teleporter()
	{
	if ( !Target() )
		{
		gi.dprintf( "teleporter without a target.\n" );
		ProcessEvent( EV_Remove );
		return;
		}

	if ( spawnflags & 1 )
		{
		showModel();
		}

	respondto = spawnflags ^ ( TRIGGER_PLAYERS | TRIGGER_MONSTERS | TRIGGER_PROJECTILES );
	}

/*****************************************************************************/
/*SINED misc_teleporter_dest (1 0 0) (-32 -32 0) (32 32 8)

Point teleporters at these.

/*****************************************************************************/

CLASS_DECLARATION( Entity, TeleporterDestination, "misc_teleporter_dest" );

ResponseDef TeleporterDestination::Responses[] =
	{
		{ NULL, NULL }
	};

TeleporterDestination::TeleporterDestination()
	{
	movedir = G_GetMovedir();
	setAngles( movedir.toAngles() );
	}

/*****************************************************************************/
/*SINED waypoint (0 0.5 0) (-8 -8 -8) (8 8 8)

Used as a positioning device for objects

/*****************************************************************************/

CLASS_DECLARATION( Entity, Waypoint, "waypoint" );

ResponseDef Waypoint::Responses[] =
	{
		{ NULL, NULL }
	};

/*****************************************************************************/
/*SINED func_shatter (0 .5 .8) ? x x NOT_PLAYERS NOT_MONSTERS NOT_PROJECTILES HURT_SHATTER THRESHOLD

For shattering objects.  Triggers only when a threshold of damage is exceeded.
Will also trigger any targeted func_areaportals when not invisible.

"health" specifies how much damage must occur before trigger fires.  Default is 20.
"percentage" specifies how much of the thing to shatter. Default is 50
"minsize" specifies minsize for tesselation, default based off size
"maxsize" specifies maxsize for tesselation, default based off size
"thickness" specifies thickness for tesselation, default same as minsize
"key"     The item needed to activate this. (default nothing)
"noise" sound to play when shattered, defaults to nothing

HURT_SHATTER - when the thing gets hurt, spawn pieces of itself
THRESHOLD - damage threshold behavior

If NOT_PLAYERS is set, the trigger does not respond to damage caused by players
If NOT_MONSTERS is set, the trigger does not respond to damage caused by monsters
If NOT_PROJECTILES is set, the trigger does not respond to damage caused by projectiles

/*****************************************************************************/

CLASS_DECLARATION( Trigger, Shatter, "func_shatter" );

ResponseDef Shatter::Responses[] =
	{
	   { &EV_Trigger_Effect,			( Response )Shatter ::DoShatter },
	   { &EV_Damage,						( Response )Shatter ::DamageEvent },
		{ NULL, NULL }
	};

void Shatter::DamageEvent
	(
	Event *ev
	)

	{
	Event			*event;
	Entity		*inflictor;
	Entity		*attacker;
	int			damage;

	if ( takedamage == DAMAGE_NO )
		{
		return;
		}

	damage		= ev->GetInteger( 1 );
	inflictor	= ev->GetEntity( 2 );
	attacker		= ev->GetEntity( 3 );

   if ( threshold && damage < health )
		{
		return;
		}
   else if ( !threshold )
      {
      health -= damage;
      if (health > 0 )
         {
      	damage_taken += damage;
         return;
         }
      }

	damage_taken += damage;

   if ( attacker )
      {
   	event = new Event( EV_Activate );
	   event->AddEntity( attacker );
	   ProcessEvent( event );
      }
   else
      {
      warning("Damage", "Attacker is null\n" );
      }
	}

void Shatter::DoShatter
	(
	Event *ev
	)

	{
	Entity	*other;
	Event		*event;
   Vector   dir;

	if ( takedamage == DAMAGE_NO )
		{
		return;
		}

   if ( noise.length() > 1 )
      {
      sound( noise.c_str(), 1, CHAN_VOICE + CHAN_NO_PHS_ADD );
      }

	other = ev->GetEntity( 1 );

	takedamage = DAMAGE_NO;

   dir = worldorigin - other->worldorigin;

   TesselateModel
      (
      this,
      tess_min_size,
      tess_max_size,
      dir,
      damage_taken,
      tess_percentage,
      tess_thickness,
      vec3_origin
      );

	SetAreaPortals( Target(), true );

	event = new Event( EV_Trigger_ActivateTargets );
	event->AddEntity( other );
	ProcessEvent( event );

	ProcessEvent( EV_BreakingSound );

	PostEvent( EV_Remove, 0 );
	}

Shatter::Shatter()
	{
	//
	// Can only be used once
	//
	count = -1;
   threshold = false;

	// Since we're a subclass of DamageThreshold, override the invisible behaviour
	showModel();
	PostEvent( Event( "setup" ), 0 );

   tess_percentage = G_GetFloatArg( "percentage", tess_percentage*100 ) / 100.0f;
   tess_min_size = G_GetIntArg( "minsize", tess_min_size );
   tess_max_size = G_GetIntArg( "maxsize", tess_max_size );
   tess_thickness = G_GetIntArg( "thickness", tess_thickness );

	health = G_GetFloatArg( "health", 20 );
	max_health = health;

	noise = str( G_GetSpawnArg( "noise", "" ) );

   if ( spawnflags & (1<<5) )
      flags |= FL_TESSELATE;

   if ( spawnflags & (1<<6) )
      threshold = true;

   tess_thickness = 10;

	respondto = spawnflags ^ ( TRIGGER_PLAYERS | TRIGGER_MONSTERS | TRIGGER_PROJECTILES );
	}

/*****************************************************************************/
/*SINED func_glass (0 .5 .8) ? x x NOT_PLAYERS NOT_MONSTERS NOT_PROJECTILES HURT_SHATTER THRESHOLD

For glass objects.  Shatters when the accumulated damage is exceeded, or when activated

"health" specifies how much damage must occur before the glass shatters.  Default is 60.
"percentage" specifies how much of the thing to shatter. Default is 50
"minsize" specifies minsize for tesselation, default based off size
"maxsize" specifies maxsize for tesselation, default based off size
"thickness" specifies thickness for tesselation, default same as minsize
"key"     The item needed to activate this. (default nothing)
"noise" sound to play when shattered, defaults to glass breaking

If NOT_PLAYERS is set, the trigger does not respond to events caused by players
If NOT_MONSTERS is set, the trigger does not respond to events caused by monsters
If NOT_PROJECTILES is set, the trigger does not respond to events caused by projectiles

/*****************************************************************************/

CLASS_DECLARATION( Shatter, Glass, "func_glass" );

ResponseDef Glass::Responses[] =
	{
		{ NULL, NULL }
	};

Glass::Glass()
	{
   if ( !noise.length() )
      {
      const char * realname;

      if (max_health <= 60)
         {
         realname = gi.GlobalAlias_FindRandom( "impact_smlglass" );
         if ( realname )
            noise = str( realname );
         }
      else
         {
         realname = gi.GlobalAlias_FindRandom( "impact_lrgglass" );
         if ( realname )
            noise = str( realname );
         }
      }
   gi.soundindex( noise.c_str() );
	}

//
// MadeBreakingSound
//
// Entity-less notifier for AI
//
void MadeBreakingSound
	(
   Vector pos,
   Entity * activator
	)

	{
	Entity	*ent;
	Event		*ev;

   //
   // make sure activator is valid
   //

   if ( !activator )
      activator = world;

	ent = NULL;
	while( ent = findradius( ent, pos.vec3(), SOUND_BREAKING_RADIUS ) )
		{
		if ( !ent->deadflag && ent->isSubclassOf( Sentient ) && ( ent != activator ) &&
			gi.inPHS( pos.vec3(), ent->centroid.vec3() ) 
			)
			{
			ev = new Event( EV_HeardBreaking );
			ev->AddEntity( activator );
			ev->AddVector( pos );
			ent->PostEvent( ev, 0 );
			}
		}
   }

CLASS_DECLARATION( Entity, BloodSplat, NULL );

ResponseDef BloodSplat::Responses[] =
	{
		{ NULL, NULL }
	};

int BloodSplat::numBloodSplats = 0;
Queue BloodSplat::queueBloodSplats;

BloodSplat::BloodSplat
   (
   Vector pos,
   Vector ang,
   float scale
   )

	{
   BloodSplat *fadesplat;

   if ( numBloodSplats > sv_maxbloodsplats->value )
      {
      // Fade one out of the list.
      fadesplat = ( BloodSplat * )queueBloodSplats.Dequeue();
      fadesplat->ProcessEvent( EV_FadeOut );
      numBloodSplats--;

      // Don't spawn one until we others have faded
      PostEvent( EV_Remove, 0 );
      return;
      }

	setMoveType( MOVETYPE_NONE );
	setSolidType( SOLID_NOT );
   setModel( "sprites/bloodsplat.spr" );
	edict->s.frame = G_Random( 4 );
	setSize( "0 0 0", "0 0 0" );

   queueBloodSplats.Enqueue( this );
   numBloodSplats++;

   edict->s.scale = scale * edict->s.scale;
	setAngles( ang );
   setOrigin( pos );
	}

BloodSplat::~BloodSplat()
   {
   if ( queueBloodSplats.Inqueue( this ) )
      {
      queueBloodSplats.Remove( this );
      numBloodSplats--;
      }
   }

/*****************************************************************************/
/*SINED func_clipbox (0 .5 .8) (-16 -16 -16) (16 16 16)

Invisible bounding box used like a clip brush.  This is mainly used for blocking
off areas or improving clipping without having to recompile the map.  Because of
this, it will most likely only be spawned via script.
age is exceeded, or when activated

"mins" min point of the clip.
"maxs" max point of the clip.
"type" -
0 Monster and Player clip
1 Monster clip
2 Player clip

/*****************************************************************************/

CLASS_DECLARATION( Entity, ClipBox, "func_clipbox" );

ResponseDef ClipBox::Responses[] =
	{
		{ NULL, NULL }
	};

ClipBox::ClipBox()
	{
   int type;

	setMoveType( MOVETYPE_NONE );
	setSolidType( SOLID_BBOX );
	hideModel();

   type = G_GetIntArg( "type" );

   edict->clipmask = MASK_SOLID;
   switch( type )
      {
      case 1 :
         edict->svflags |= SVF_MONSTERCLIP;
         break;

      case 2 :
         edict->svflags |= SVF_PLAYERCLIP;
         break;

      default :
         edict->svflags |= SVF_PLAYERCLIP|SVF_MONSTERCLIP;
         break;
      }

   mins = G_GetVectorArg( "mins" );
   maxs = G_GetVectorArg( "maxs" );

   origin = ( mins + maxs ) * 0.5;

   setSize( mins - origin, maxs - origin );
	setOrigin( origin );
   }
