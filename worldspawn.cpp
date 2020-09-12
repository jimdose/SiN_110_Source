//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/worldspawn.cpp                   $
// $Revision:: 97                                                             $
//   $Author:: Jimdose                                                        $
//     $Date:: 11/08/98 10:49p                                                $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/worldspawn.cpp                        $
// 
// 97    11/08/98 10:49p Jimdose
// moved earthquake to level struct
// 
// 96    10/27/98 9:46p Aldie
// Changed training cvar to level.training
// 
// 95    10/27/98 6:28a Jimdose
// set model to "*1"
// 
// 94    10/27/98 5:43a Jimdose
// World wasn't calling Entity::Archive or Unarchive!
// Added FreeTargetList
// 
// 93    10/27/98 4:36a Markd
// reset the earthquake in worldspawn
// 
// 92    10/26/98 2:16p Aldie
// Added AirClamp
// 
// 91    10/21/98 2:17a Jimdose
// Fixed bug where world wiped out configstrings during loadgame
// 
// 90    10/19/98 9:53p Jimdose
// changed slime variables to lightvolume
// 
// 89    10/10/98 1:31a Jimdose
// moved precache scripts to G_Precache in G_Utils
// some things are no longer initialized during loadgames
// 
// 88    10/08/98 12:37a Jimdose
// Made savegames work
// 
// 87    9/30/98 4:36p Aldie
// Reset gravpaths when worldspawn is destroyed
// 
// 86    9/27/98 6:27p Aldie
// Added water, slime, and lava colors to worldspawn
// 
// 85    9/17/98 5:53p Jimdose
// create level.total_secrets and level.found_secrets on startup
// 
// 84    9/02/98 7:48p Aldie
// Added support for multiple global scripts
// 
// 83    8/29/98 9:48p Jimdose
// included deadbody.h
// 
// 82    8/24/98 11:32a Markd
// Added Start method to threads, repladed all ProcessEvent(
// EV_ScriptThread_execute) with thread->Start( -1 )
// 
// 81    8/22/98 6:34p Markd
// Revamped player readiness for scripting
// 
// 80    8/21/98 5:26p Markd
// Added sv_precache and cl_precache 
// 
// 79    8/17/98 7:33p Jimdose
// skipthread is now initialized with G_GetStringArg since G_GetSpawnArg can
// return NULL, which the str class doesn't like
// 
// 78    8/17/98 4:35p Markd
// Added skipthread and cinematic stuff to worldspawn
// 
// 77    8/08/98 7:51p Jimdose
// changed realWorld to world
// 
// 76    7/26/98 12:35p Jimdose
// Got rid of backslash in filename
// 
// 75    7/24/98 6:22p Jimdose
// Set config string CS_MAXCLIENTS
// removed unused layout stuff
// 
// 74    7/15/98 12:14a Aldie
// Updated worldspawn to send over a deathmatch flag
// 
// 73    7/13/98 5:57p Markd
// Added SetGameScript call
// 
// 72    7/13/98 5:01p Aldie
// Added dead player bodies with gibbing
// 
// 71    7/01/98 7:04p Aldie
// Mission computer stuff
// 
// 70    6/27/98 7:58p Aldie
// Moved status bar to client
// 
// 69    6/27/98 2:15p Aldie
// New status bar stuff
// 
// 68    6/25/98 7:33p Aldie
// New HUD
// 
// 67    6/24/98 1:38p Aldie
// Implementation of inventory system and picking stuff up
// 
// 66    6/20/98 7:06p Aldie
// Updated HUD for inventory
// 
// 65    6/20/98 2:23p Aldie
// Added Inventory to statusbar
// 
// 64    6/19/98 6:38p Aldie
// Updated status bar for inventory
// 
// 63    6/10/98 2:10p Aldie
// Updated damage function.
// 
// 62    6/09/98 4:24p Jimdose
// Added multi-file scripting, so hacks to load multifiles were removed.
// 
// 61    6/05/98 6:26p Aldie
// Updated stats bar for armor.
// 
// 60    5/26/98 4:21p Markd
// Added TargetList stuff
// 
// 59    5/25/98 2:28p Aldie
// Fixed issues with not loading game dll
// 
// 58    5/24/98 2:46p Markd
// Made char *'s into const char *'s
// 
// 57    5/19/98 11:13p Aldie
// Fixed statusbars for higher res
// 
// 56    5/18/98 6:15p Aldie
// Updated ammo bar.
// 
// 55    5/14/98 10:20p Jimdose
// world is now an EntityPtr
// 
// 54    5/04/98 8:32p Markd
// Removed setlightstyle stuff
// 
// 53    5/04/98 11:31a Markd
// Moved lightstyles into global.scr
// 
// 52    5/02/98 9:39p Markd
// Fixed the gunsmoke lightstyle
// 
// 51    5/02/98 8:47p Markd
// Took out a lot of precache stuff
// 
// 50    5/01/98 5:07p Jimdose
// Changed *world to an Entity *
// 
// 49    5/01/98 10:42a Markd
// Put in global.scr and precache.scr parsing
// 
// 48    4/18/98 8:20p Markd
// Fixed sniperrifle precache
// 
// 47    4/18/98 7:43p Markd
// Added correct weapon names to precache section
// 
// 46    4/18/98 6:35p Aldie
// Updated sbar layout
// 
// 45    4/18/98 6:12p Aldie
// Updated ammo stats bar.
// 
// 44    4/16/98 8:40p Aldie
// Added DM status bar to new system
// 
// 43    4/16/98 7:46p Aldie
// Added new status bar
// 
// 42    4/10/98 1:24a Markd
// Added FL_SPARKS and FL_BLASTMARK flags
// 
// 41    4/07/98 8:00p Markd
// removed defhandle, changed all SINMDL calls to modelindex calls, removed
// SINMDL prefix
// 
// 40    4/03/98 3:37p Jimdose
// Got rid of disabled status bar
// 
// 39    4/03/98 2:30p Jimdose
// Temporarily turned off status bar
// 
// 38    4/02/98 4:52p Jimdose
// Changed stat bar layouts
// 
// 37    3/31/98 4:21p Jimdose
// added precaches
// 
// 36    3/31/98 1:19p Jimdose
// Precached footsteps
// 
// 35    3/30/98 11:39p Markd
// Added modelIndex stuff
// 
// 34    3/27/98 11:04p Jimdose
// changed explode.def to explode.spr
// 
// 33    3/26/98 7:15p Aldie
// Added console type vars.
// 
// 32    3/23/98 1:31p Jimdose
// Revamped event and command system
// 
// 31    3/18/98 7:21p Jimdose
// Added precache for explosion sprite
// 
// 30    3/02/98 8:49p Jimdose
// Changed the classid parameter of CLASS_DECLARATION to a quoted string so
// that you could have a NULL classid.
// 
// 29    2/23/98 6:38p Jimdose
// 
// 28    2/17/98 7:00p Jimdose
// levelVars are cleared upon spawning the world
// 
// 27    2/16/98 2:06p Jimdose
// Changed movetype from MOVETYPE_PUSH to MOVETYPE_NONE, since the world
// shouldn't be moving around.
// 
// 26    2/10/98 11:44a Jimdose
// Changed color of worldspawn in Sined
// 
// 25    2/06/98 5:48p Jimdose
// Moved sined header to .cpp file.
// Prepended "maps/" to script file name
// 
// 24    2/03/98 10:56a Jimdose
// Updated to work with Quake 2 engine
// Moved initialization to constructor and removed Init function
// Removed precache stuff (it was all out of date anyway).
// 
// 22    12/15/97 4:32p Jimdose
// Precached new shotgun sounds
// 
// 21    12/15/97 2:51p Markd
// Added speargun firing sounds
// 
// 20    12/15/97 11:56a Markd
// Added speargun sounds
// 
// 19    12/14/97 5:54p Jimdose
// Removed wrong check-in comment #18: " Added BettySpike"
// Changed precache of spear\spear.def to spear.def.
// 
// 17    12/14/97 5:34p Markd
// Put in precaches for rocket launcher stuff
// 
// 16    12/13/97 7:42p Markd
// Added RocketLauncher sound
// 
// 15    12/13/97 6:52p Aldie
// Added precache for shotgun
// 
// 14    12/12/97 1:19p Markd
// Added rocket launcher precache
// 
// 13    12/06/97 12:35p Aldie
// Added tracer sprite to precache
// 
// 12    11/18/97 5:26p Markd
// Changed model from sub-directory to parent directory for magnum.def
// 
// 11    11/10/97 8:38p Jimdose
// Removed getMapTitle.  Map name is now stored in netname.
// Made StartFrame get called indirectly through EVENT_PRETHINK.
// Added event function.
// 
// 10    11/07/97 6:00p Markd
// Removed QUAKE specific sound effects prespawns
// 
// 9     10/31/97 7:19p Markd
// Added precache for sprites
// 
// 8     10/28/97 8:36p Jimdose
// Moved magnum model
// 
// 7     10/28/97 8:20p Jimdose
// Added precache for bubble and spear
// 
// 6     10/28/97 6:54p Markd
// Added precache for darkcaptain sound
// 
// 5     10/27/97 3:29p Jimdose
// Removed dependency on quakedef.h
// 
// 4     10/24/97 8:13p Jimdose
// Added precache for magnum
// 
// 3     9/26/97 6:14p Jimdose
// Added standard Ritual headers
//
// DESCRIPTION:
// Base class for worldspawn objects.  This should be subclassed whenever
// a DLL has new game behaviour that needs to be initialized before any other
// entities are created, or before any entity thinks each frame.  Also controls
// spawning of clients.
//

#include "g_local.h"
#include "entity.h"
#include "scriptmaster.h"
#include "worldspawn.h"
#include "surface.h"
#include "console.h"
#include "deadbody.h"
#include "gravpath.h"
#include "earthquake.h"

extern void CreateMissionComputer( void );

WorldPtr  world;

/*****************************************************************************/
/*SINED worldspawn (0 0 0) ? CINEMATIC

Only used for the world.
"sky"			environment map name
"skyaxis"	vector axis for rotating sky
"skyrotate"	speed of rotation in degrees/second
"cdtrack"	music cd track number
"gravity"	800 is default gravity
"message"	text to print at user logon
"skipthread" thread that is activated to skip this level (if cinematic)

/*****************************************************************************/

#define CINEMATIC 1

CLASS_DECLARATION( Entity, World, "worldspawn" );

ResponseDef World::Responses[] =
	{
		{ NULL, NULL }
	};

World::World()
	{
	const char		*text;
	str            mapname;
	int				i;
   Vector         water_color;
   Vector         lightvolume_color;
   Vector         lava_color;

	world = this;

	setMoveType( MOVETYPE_NONE );
	setSolidType( SOLID_BSP );

	// world model is always index 1
	edict->s.modelindex = 1;
   model = "*1";

   // Anything that modifies configstrings, or spawns things is ignored when loading savegames
   if ( LoadingSavegame )
      {
      return;
      }

   // inform the client that this is deathmatch, and we should
   // draw deathmatch stats.  This goes around what the CS_STATUSBAR
   // used to be used for since we moved all HUDS to the client.
   if ( deathmatch->value )
		{
		gi.configstring( CS_STATUSBAR, "DEATHMATCH" );
		}
	else
		{
		gi.configstring( CS_STATUSBAR, "SINGLE_PLAYER" );
		}

   //
   // see if the level has a soundtrack associated withit
	//
	text = G_GetSpawnArg( "soundtrack" );
	if ( text )
		{
		gi.configstring( CS_SOUNDTRACK, text );
		}

	text = G_GetSpawnArg( "sky" );
	if ( text )
		{
		gi.configstring( CS_SKY, text );
		}
	else
		{
		gi.configstring( CS_SKY, "sky_" );
		}

   text = G_GetSpawnArg( "skyrotate" );
	gi.configstring( CS_SKYROTATE, text ? text : "0" );

	text = G_GetSpawnArg( "skyaxis" );
	gi.configstring( CS_SKYAXIS, text ? text : "0 0 0" );

	text = G_GetSpawnArg( "cdtrack" );
	gi.configstring( CS_CDTRACK, text ? text : "0" );

	gi.configstring (CS_MAXCLIENTS, va("%i", (int)(maxclients->value) ) );

	text = G_GetSpawnArg( "gravity" );
	if ( !text )
		{
		gi.cvar_set( "sv_gravity", "800" );
		}
	else
		{
		gi.cvar_set( "sv_gravity", text );
		}
	
   // get skipthread
	skipthread = G_GetStringArg( "skipthread" );

   // the world takes blast marks and sparks by default
   flags |= FL_BLASTMARK;
   flags |= FL_SPARKS;

   // Reserve some space for dead bodies
   InitializeBodyQueue();

   //
   // see if this is a cinematic level
	//
   if ( spawnflags & CINEMATIC )
      {
      level.cinematic = true;
      }
   else
      {
      level.cinematic = false;
      }

   level.nextmap = G_GetStringArg( "nextmap" );

	// make some data visible to the server
	text = G_GetSpawnArg( "message" );
	if ( text )
		{
		gi.configstring( CS_NAME, text );
		level.level_name = text;
		}
	else
		{
		level.level_name = level.mapname;
		}

	// Set up script
	text = G_GetSpawnArg( "script" );
	if ( !text )
		{
		// No script specified.  Try using the mapname as the script name
      mapname = "maps/";
		mapname += level.mapname;
		for( i = mapname.length() - 1; i >= 0; i-- )
			{
			if ( mapname[ i ] == '.' )
				{
				mapname[ i ] = 0;
				break;
				}
			}

		mapname += ".scr";

		text = &mapname[ 5 ];

		// If there isn't a script with the same name as the map, then don't try to load script
		if ( gi.LoadFile( mapname.c_str(), NULL, 0 ) == -1 )
			{
			text = NULL;
			}
		}

	if ( text )
		{
		gi.dprintf( "Adding script: '%s'\n", text );
		mapname = va( "maps/%s", text );

      // just set the script, we will start it in G_Spawn
      ScriptLib.SetGameScript( mapname.c_str() );
		}

   // Set the color for the blends.
   water_color       = G_GetVectorArg("watercolor",Vector(0,0,1));
   level.water_alpha = G_GetFloatArg("wateralpha",0.1);

   lightvolume_color = G_GetVectorArg("lightcolor",Vector(1,1,1));
   level.lightvolume_alpha = G_GetFloatArg("lightalpha",0.5);

   lava_color        = G_GetVectorArg("lavacolor",Vector(1.0,0.3,0));
   level.lava_alpha  = G_GetFloatArg("lavaalpha",0.6);

   level.water_color = water_color;
   level.lightvolume_color = lightvolume_color;
   level.lava_color = lava_color;

   //
   // reset the earthquake
   //
   level.earthquake = 0;
	}

TargetList * World::GetTargetList( str &targetname )
	{
   TargetList * targetlist;
   int i;

   for( i = 1; i <= targetList.NumObjects(); i++ )
      {
      targetlist = targetList.ObjectAt( i );
      if ( targetname == targetlist->targetname)
         return targetlist;
      }
   targetlist = new TargetList( targetname );
   targetList.AddObject( targetlist );
   return targetlist;
	}

void World::AddTargetEntity( str &targetname, Entity * ent )
   {
   TargetList * targetlist;

   targetlist = GetTargetList( targetname );
   targetlist->AddEntity( ent );
   }

void World::RemoveTargetEntity( str &targetname, Entity * ent )
   {
   TargetList * targetlist;

   targetlist = GetTargetList( targetname );
   targetlist->RemoveEntity( ent );
   }

Entity * World::GetNextEntity( str &targetname, Entity * ent )
   {
   TargetList * targetlist;

   targetlist = GetTargetList( targetname );
   return targetlist->GetNextEntity( ent );
   }

World::~World()
	{
   FreeTargetList();
	}

void World::FreeTargetList
   (
   void
   )

   {
   int i;
   int num;

   num = targetList.NumObjects();
   for( i = 1; i <= num; i++ )
      {
      delete targetList.ObjectAt( i );
      }

   targetList.FreeObjectList();
   }

//
// List stuff for targets
//

CLASS_DECLARATION( Class, TargetList, NULL );

ResponseDef TargetList::Responses[] =
	{
		{ NULL, NULL }
	};

TargetList::TargetList()
   {
   }

TargetList::TargetList( str &tname )
   {
   targetname = tname;
   }

TargetList::~TargetList()
   {
   }

void TargetList::AddEntity( Entity * ent )
   {
	if ( !list.ObjectInList( ent ) )
		{
		list.AddObject( ent );
      }
   }

void TargetList::RemoveEntity( Entity * ent )
   {
	if ( list.ObjectInList( ent ) )
		{
		list.RemoveObject( ent );
      }
   }

Entity * TargetList::GetNextEntity( Entity * ent )
   {
   int index;

   index = 0;
   if ( ent )
      index = list.IndexOfObject( ent );
   index++;
   if ( index > list.NumObjects() )
      return NULL;
   else
      return list.ObjectAt( index );
   }

