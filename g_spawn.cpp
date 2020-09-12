//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/g_spawn.cpp                      $
// $Revision:: 68                                                             $
//   $Author:: Jimdose                                                        $
//     $Date:: 1/29/99 6:14p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/g_spawn.cpp                           $
// 
// 68    1/29/99 6:14p Jimdose
// fixed savegame bug
// 
// 67    1/22/99 8:01p Jimdose
// G_SoawnEntities no longer calls G_LevelStart when loading a savegame.  This
// fixes the Darwin tubes bug in Area57.
// 
// 66    11/07/98 10:01p Jimdose
// added G_GetClassFromArgs
// 
// 65    11/05/98 8:29p Aldie
// Removed checksumming and fixed stuff for loading times
// 
// 64    10/28/98 4:46p Jimdose
// G_ArchiveEdict was accessing edict->owner->entity, which may be cleared out
// when called.
// 
// 63    10/27/98 9:46p Aldie
// Changed training cvar to level.training
// 
// 62    10/26/98 4:20p Markd
// Added game.skill variable
// 
// 61    10/25/98 11:57p Jimdose
// moved playerfrozen from game to level
// 
// 60    10/24/98 11:47p Jimdose
// made RestoreEnt call G_InitSpawnArguments
// 
// 59    10/23/98 3:43a Markd
// put in universal_script support
// 
// 58    10/19/98 11:46p Aldie
// Clear spawn arguments out after spawning things
// 
// 57    10/19/98 12:07a Jimdose
// made all code use fast checks for inheritance (no text lookups when
// possible)
// isSubclassOf no longer requires ::_classinfo()
// 
// 56    10/18/98 8:43p Jimdose
// Started adding check for SOLID_BSP and no model in SpawnEntities
// 
// 55    10/17/98 8:15p Jimdose
// Changed G_CallSpawn2 to G_CallSpawn
// 
// 54    10/17/98 12:21a Jimdose
// Added G_ResetEdicts
// 
// 53    10/16/98 1:50a Jimdose
// Removed G_SaveClientData from G_LevelShutdown
// 
// 52    10/15/98 7:13p Jimdose
// Overrode = for SpawnArgGroup.  Fixes crash on level change with multiplayer
// 
// 51    10/14/98 10:56p Jimdose
// More work on persistant data
// added archive functions for spawnargs classes
// 
// 50    10/14/98 1:18a Jimdose
// Got cross-level persistant info working
// 
// 49    10/11/98 8:51p Jimdose
// Added LoadingServer variable
// 
// 48    10/10/98 12:39p Markd
// Renamed team to moveteam
// 
// 47    10/10/98 1:27a Jimdose
// added G_Precache
// 
// 46    10/07/98 11:47p Jimdose
// Got savegames working
// 
// 45    9/15/98 6:46p Aldie
// Clear out the event list after deleting all the edicts
// 
// 44    9/02/98 3:47p Markd
// Put in precache ability for the main game script
// 
// 43    8/29/98 9:42p Jimdose
// Made all function names consistantly begin with G_
// Added call info to G_Trace
// 
// 42    8/29/98 2:53p Aldie
// Added status meter for loading levels.
// 
// 41    8/27/98 4:18p Jimdose
// Only start script when the world is spawned so that demomap won't start
// scripts
// 
// 40    8/24/98 1:33p Markd
// fixed null string problem with gamescript
// 
// 39    8/24/98 11:32a Markd
// Added Start method to threads, repladed all ProcessEvent(
// EV_ScriptThread_execute) with thread->Start( -1 )
// 
// 38    8/12/98 3:19p Aldie
// Created a G_CallSpawn2 that returns pointer to Entity that is created.
// Currently used with func_box.
// 
// 37    8/04/98 6:05p Aldie
// Relocated DETAIL spawnflag
// 
// 36    7/08/98 12:54p Jimdose
// Made developer c_var global
// 
// 35    7/02/98 5:24p Markd
// Added detail spawning abilities
// 
// 34    6/24/98 4:49p Aldie
// Made it so func_spawn will work.
// 
// 33    6/23/98 9:54p Jimdose
// Fixed infinite loop bug in G_RunFrame
// 
// 32    6/16/98 9:04p Markd
// made objects default to "Object" instead of "entity"
// 
// 31    5/27/98 5:02a Aldie
// Added queue for bloodsplats
// 
// 30    5/26/98 7:56p Jimdose
// added scripted cameras
// 
// 29    5/25/98 6:52a Aldie
// Added ResetBulletHoles to SpawnEntity
// 
// 28    5/24/98 8:46p Jimdose
// Made a lot of functions more str-friendly.
// Got rid of a lot of char * based strings
// Cleaned up get spawn arg functions and sound functions
// sound functions now use consistant syntax
// 
// 27    5/24/98 4:48p Jimdose
// Made char *'s const
// 
// 26    5/24/98 2:47p Markd
// Made char *'s into const char *'s
// 
// 25    5/20/98 11:11a Markd
// removed char * dependency
// 
// 24    5/18/98 8:13p Jimdose
// Renamed Navigator back to PathManager
// 
// 23    5/12/98 7:07p Markd
// Put in Development spawnflag
// 
// 22    5/09/98 8:02p Jimdose
// AI nodes are saved after map changes
// 
// 21    4/30/98 5:28p Jimdose
// Removed check for null models in G_CallSpawn.  If an entity deleted itself
// in its constructor, the check would access deallocated memory
// 
// 20    4/29/98 5:04p Jimdose
// Fixed gi.error so that it doesn't crash when called from C++
// 
// 19    4/28/98 8:13p Jimdose
// Added checks to ensure that SOLID_BSP objects have models
// 
// 18    4/28/98 5:26p Jimdose
// Made spawnflags for !easy, !medium, !hard, !deathmatch and !coop work.
// 
// 17    4/27/98 3:42p Jimdose
// Navigator is initialized in SpawnEntities
// 
// 16    4/18/98 6:53p Markd
// Fixed spawning of new entity classes
// 
// 15    4/16/98 2:04p Jimdose
// Removed pathmanager
// 
// 14    4/07/98 9:18p Jimdose
// Think I found that bug where free_edicts gets put on the active_edicts list.
// 
// 13    4/07/98 8:02p Markd
// Added tons 'o SINMDL prefixed commands
// 
// 12    4/07/98 5:41p Jimdose
// Added assertions to G_Spawn and G_FreeEdict
// 
// 11    4/05/98 1:56a Jimdose
// fixed bug where edicts were being freed, but not entities when the map
// changed
// 
// 10    3/31/98 12:30a Markd
// Added models/ to spawning of model stuff
// 
// 9     3/30/98 9:44p Markd
// Added in proper spawing for classname "model"
// 
// 8     3/27/98 5:37p Jimdose
// SpawnEntities now frees up any entities for when levels change, but the game
// is the same.
// 
// 7     3/26/98 8:19p Jimdose
// G_FreeEdict no longer clears the edicts client variable
// 
// 6     3/13/98 7:24p Aldie
// Added get vector arg.
// 
// 5     3/02/98 5:46p Jimdose
// pathManager frees all cached paths on starting a map.
// 
// 4     2/19/98 5:03p Jimdose
// Moved G_Entity, G_Random, and G_CRandom to g_utils
// 
// 3     2/16/98 2:18p Jimdose
// Made G_FindTeams work
// Added active_edicts and free_edicts for faster entity processing and for
// operations that depend on the order that physics is processed on entities
// (such as binding).
// 
// 2     2/03/98 11:06a Jimdose
// Converted to work with Sin progs
// 
// 1     1/21/98 2:56p Jimdose
// 
// 3     12/30/97 6:04p Jimdose
// Added header text
//
// DESCRIPTION:
// 

#include "g_local.h"
#include "class.h"
#include "Entity.h"
#include "g_spawn.h"
#include "navigate.h"
#include <setjmp.h>
#include "player.h"
#include "gravpath.h"
#include "surface.h"
#include "console.h"
#include "object.h"

void G_ExitWithError( void );
extern jmp_buf	G_AbortGame;

SpawnArgsForEntity PersistantData;

typedef struct 
	{
	char key[ 64 ];
	char value[ 256 ];
	} spawnargs_t;

#define NUM_SPAWN_ARGS 32 

int			numSpawnArgs = 0;
spawnargs_t spawnArgs[ NUM_SPAWN_ARGS ];

/****************************************************************************

  SpawnArg Class Definition

****************************************************************************/

CLASS_DECLARATION( Class, SpawnArg, NULL );

ResponseDef SpawnArg::Responses[] =
	{
      { NULL, NULL }
   };

SpawnArg::SpawnArg()
   {
	memset( key, 0, sizeof( key ) );
	memset( value, 0, sizeof( value ) );
   }

SpawnArg::SpawnArg
   (
   SpawnArg &arg
   )

   {
   strcpy( key, arg.key );
   strcpy( value, arg.value );
   }

void SpawnArg::Archive
   (
   Archiver &arc
   )

   {
   Class::Archive( arc );

   arc.WriteRaw( key, sizeof( key ) );
   arc.WriteRaw( value, sizeof( value ) );
   }

void SpawnArg::Unarchive
   (
   Archiver &arc
   )

   {
   Class::Unarchive( arc );

   arc.ReadRaw( key, sizeof( key ) );
   arc.ReadRaw( value, sizeof( value ) );
   }

/****************************************************************************

  SpawnArgs Class Definition

****************************************************************************/

CLASS_DECLARATION( Class, SpawnArgs, NULL );

ResponseDef SpawnArgs::Responses[] =
	{
      { NULL, NULL }
   };

SpawnArgs::SpawnArgs()
   {
   }

SpawnArgs::SpawnArgs
   (
   SpawnArgs &otherlist
   )

   {
   SpawnArg arg1;
   SpawnArg *arg2;
   int num;
   int i;

   num = otherlist.NumArgs();
   for( i = 1; i <= num; i++ )
      {
      arg2 = otherlist.argList.AddressOfObjectAt( i );

      strcpy( arg1.key, arg2->key );
      strcpy( arg1.value, arg2->value );

      argList.AddObject( arg1 );
      }
   argList.Resize( num );
   }

void SpawnArgs::operator=
	(
	SpawnArgs &otherlist
	)

	{
   SpawnArg arg1;
   SpawnArg *arg2;
   int num;
   int i;

   argList.ClearObjectList();

   num = otherlist.NumArgs();
   for( i = 1; i <= num; i++ )
      {
      arg2 = otherlist.argList.AddressOfObjectAt( i );

      strcpy( arg1.key, arg2->key );
      strcpy( arg1.value, arg2->value );

      argList.AddObject( arg1 );
      }
   argList.Resize( num );
	}

int SpawnArgs::NumArgs
   (
   void
   )

   {
   return argList.NumObjects();
   }

void SpawnArgs::SetArgs
   (
   void
   )

   {
   SpawnArg arg;
   int i;

   for( i = 0; i < numSpawnArgs; i++ )
      {
      strcpy( arg.key, spawnArgs[ i ].key );
      strcpy( arg.value, spawnArgs[ i ].value );
      argList.AddObject( arg );
      }
   argList.Resize( numSpawnArgs );
   }

void SpawnArgs::RestoreArgs
   (
   void
   )

   {
   SpawnArg *arg;
   int i;

   numSpawnArgs = argList.NumObjects();
   for( i = 0; i < numSpawnArgs; i++ )
      {
      arg = &argList.ObjectAt( i + 1 );
      strcpy( spawnArgs[ i ].key, arg->key );
      strcpy( spawnArgs[ i ].value, arg->value );
      }
   }

void SpawnArgs::Archive
   (
   Archiver &arc
   )

   {
   int i;
   int num;

   Class::Archive( arc );

   num = argList.NumObjects();
   arc.WriteInteger( num );
   for( i = 1; i <= num; i++ )
      {
      arc.WriteObject( argList.AddressOfObjectAt( i ) );
      }
   }

void SpawnArgs::Unarchive
   (
   Archiver &arc
   )

   {
   int i;
   int num;

   Class::Unarchive( arc );

   argList.FreeObjectList();

   num = arc.ReadInteger();
   argList.Resize( num );
   for( i = 1; i <= num; i++ )
      {
      arc.ReadObject( argList.AddressOfObjectAt( i ) );
      }
   }

/****************************************************************************

  SpawnArgGroup Class Definition

****************************************************************************/

CLASS_DECLARATION( Class, SpawnArgGroup, NULL );

ResponseDef SpawnArgGroup::Responses[] =
	{
      { NULL, NULL }
   };

SpawnArgGroup::SpawnArgGroup()
   {
   }

SpawnArgGroup::SpawnArgGroup
   (
   SpawnArgGroup &group
   )

   {
   SpawnArgs *arg;
   int num;
   int i;

   num = group.spawnArgList.NumObjects();
   for( i = 1; i <= num; i++ )
      {
      arg = group.spawnArgList.AddressOfObjectAt( i );
      spawnArgList.AddObject( *arg );
      }
   spawnArgList.Resize( num );
   }

void SpawnArgGroup::operator=
	(
	SpawnArgGroup &group
	)

	{
   SpawnArgs *arg;
   int num;
   int i;

   num = group.spawnArgList.NumObjects();
   for( i = 1; i <= num; i++ )
      {
      arg = group.spawnArgList.AddressOfObjectAt( i );
      spawnArgList.AddObject( *arg );
      }
   spawnArgList.Resize( num );
	}

int SpawnArgGroup::NumInGroup
   (
   void
   )

   {
   return spawnArgList.NumObjects();
   }

void SpawnArgGroup::AddArgs
   (
   void
   )

   {
   SpawnArgs args;

   args.SetArgs();
   spawnArgList.AddObject( args );
   spawnArgList.Resize( NumInGroup() );
   }

void SpawnArgGroup::RestoreArgs
   (
   int i
   )

   {
   assert( ( i > 0 ) && ( i <= NumInGroup() ) );
   if ( ( i <= 0 ) || ( i > NumInGroup() ) )
      {
      G_InitSpawnArguments();
      return;
      }

   spawnArgList.ObjectAt( i ).RestoreArgs();
   }

void SpawnArgGroup::Archive
   (
   Archiver &arc
   )

   {
   int i;
   int num;

   Class::Archive( arc );

   num = spawnArgList.NumObjects();
   arc.WriteInteger( num );
   for( i = 1; i <= num; i++ )
      {
      arc.WriteObject( spawnArgList.AddressOfObjectAt( i ) );
      }
   }

void SpawnArgGroup::Unarchive
   (
   Archiver &arc
   )

   {
   int i;
   int num;

   Class::Unarchive( arc );

   spawnArgList.FreeObjectList();

   num = arc.ReadInteger();
   spawnArgList.Resize( num );
   for( i = 1; i <= num; i++ )
      {
      arc.ReadObject( spawnArgList.AddressOfObjectAt( i ) );
      }
   }

/****************************************************************************

  SpawnArgsForEntity Class Definition

****************************************************************************/

CLASS_DECLARATION( Class, SpawnArgsForEntity, NULL );

ResponseDef SpawnArgsForEntity::Responses[] =
	{
      { NULL, NULL }
   };

void SpawnArgsForEntity::Reset
   (
   void
   )

   {
   groupList.FreeObjectList();
   entnumList.FreeObjectList();
   }

void SpawnArgsForEntity::AddEnt
   (
   Entity *ent
   )

   {
   int num;
   SpawnArgGroup group;

   if ( ent && ent->isSubclassOf( Sentient ) )
      {
      G_InitSpawnArguments();

      entnumList.AddObject( ent->entnum );
      groupList.AddObject( group );
      num = groupList.NumObjects();
      groupList.Resize( num );
      entnumList.Resize( num );
      ( ( Sentient * )ent )->WritePersistantData( groupList.ObjectAt( num ) );
      }
   }

qboolean SpawnArgsForEntity::RestoreEnt
   (
   Entity *ent
   )

   {
   int num;
   SpawnArgGroup *group;

   num = entnumList.IndexOfObject( ent->entnum );
   if ( num && ent->isSubclassOf( Sentient ) )
      {
      group = groupList.AddressOfObjectAt( num );
      ( ( Sentient * )ent )->RestorePersistantData( *group );

      G_InitSpawnArguments();

      return true;
	   }

   return false;
   }

void SpawnArgsForEntity::RestoreEnts
   (
   void
   )

   {
   int num;
   int i;
   int entnum;
   edict_t *ent;
   SpawnArgGroup *group;

   num = groupList.NumObjects();
   for( i = 1; i <= num; i++ )
      {
      entnum = entnumList.ObjectAt( i );
      ent = &g_edicts[ entnum ];

      group = groupList.AddressOfObjectAt( i );

      group->RestoreArgs( 1 );

	   game.force_entnum = true;
	   game.spawn_entnum = ent->s.number;
		G_CallSpawn();
	   game.force_entnum = false;

      if ( ent->entity && ent->entity->isSubclassOf( Sentient ) )
         {
         ( ( Sentient * )ent->entity )->RestorePersistantData( *group );
         }
	   }

   Reset();
   }

void SpawnArgsForEntity::Archive
   (
   Archiver &arc
   )

   {
   int i;
   int num;

   Class::Archive( arc );

   num = groupList.NumObjects();
   arc.WriteInteger( num );
   for( i = 1; i <= num; i++ )
      {
      arc.WriteInteger( entnumList.ObjectAt( i ) );
      arc.WriteObject( groupList.AddressOfObjectAt( i ) );
      }
   }

void SpawnArgsForEntity::Unarchive
   (
   Archiver &arc
   )

   {
   int i;
   int num;

   Reset();

   Class::Unarchive( arc );

   num = arc.ReadInteger();
   entnumList.Resize( num );
   groupList.Resize( num );
   for( i = 1; i <= num; i++ )
      {
      arc.ReadInteger( entnumList.AddressOfObjectAt( i ) );
      arc.ReadObject( groupList.AddressOfObjectAt( i ) );
      }
   }

/****************************************************************************

  spawn arg management

****************************************************************************/

void G_SetFloatArg
	(
	const char *key,
	double value
	)

	{
	char text[ 20 ];

	sprintf( text, "%f", value );
	G_SetSpawnArg( key, text );
	}

void G_SetIntArg
	(
	const char *key,
	int value
	)

	{
	char text[ 20 ];

	sprintf( text, "%d", value );
	G_SetSpawnArg( key, text );
	}

void G_DefaultArg
	(
	const char *key,
	const char *defaultvalue
	)

	{
	if ( !G_GetSpawnArg( key ) )
		{
		G_SetSpawnArg( key, defaultvalue );
		}
	}

void G_DefaultFloatArg
	(
	const char *key,
	double defaultvalue
	)

	{
	if ( !G_GetSpawnArg( key ) )
		{
		G_SetFloatArg( key, defaultvalue );
		}
	}

void G_DefaultIntArg
	(
	const char *key,
	int defaultvalue
	)

	{
	if ( !G_GetSpawnArg( key ) )
		{
		G_SetIntArg( key, defaultvalue );
		}
	}

Vector G_GetVectorArg
   (
   const char *key,
   Vector defaultvalue
   )

   {
   const char *text;

   text = G_GetSpawnArg( key );
   if ( text )
		{
	   return Vector(text);
      }
   return defaultvalue;
   }

float G_GetFloatArg
	(
	const char *key,
	double defaultvalue
	)

	{
	const char *text;

	text = G_GetSpawnArg( key );
	if ( text )
		{
		return (float)atof( text );
		}
	return (float)defaultvalue;
	}

int G_GetIntArg
	(
	const char *key,
	int defaultvalue
	)

	{
	const char *text;

	text = G_GetSpawnArg( key );
	if ( text )
		{
		return atoi( text );
		}
	return defaultvalue;
	}

str G_GetStringArg
	(
	const char *key,
	const char *defaultvalue
	)

	{
	const char	*text;
	str			ret;

	text = G_GetSpawnArg( key );
	if ( !text )
		{
		text = defaultvalue;
		}

	if ( text )
		{
		return text;
		}

	return "";
	}

void G_InitSpawnArguments
	(
	void
	)

	{
	int i;

	numSpawnArgs = 0;
	for( i = 0; i < NUM_SPAWN_ARGS; i++ )
		{
		memset( spawnArgs[ i ].key, 0, sizeof( spawnArgs[ i ].key ) );
		memset( spawnArgs[ i ].value, 0, sizeof( spawnArgs[ i ].value ) );
		}
	}

qboolean G_SetSpawnArg
	( 
	const char *keyname, 
	const char *value
	)
	
	{
	int i;

	for( i = 0; i < numSpawnArgs; i++ )
		{
		if ( !strcmp( keyname, spawnArgs[ i ].key ) )
			{
			break;
			}
		}

	if ( i >= NUM_SPAWN_ARGS )
		{
		return false;
		}

   if ( i == numSpawnArgs )
      {
   	strncpy( spawnArgs[ i ].key, keyname, sizeof( spawnArgs[ 0 ].key ) - 1 );
   	numSpawnArgs++;
      }

	strncpy( spawnArgs[ i ].value, value, sizeof( spawnArgs[ 0 ].value ) - 1 );

   return true;
	}

const char *G_GetSpawnArg
	(
	const char *key,
	const char *defaultvalue
	)

	{
	int i;

	for( i = 0; i < numSpawnArgs; i++ )
		{
		if ( !strcmp( key, spawnArgs[ i ].key ) )
			{
			return spawnArgs[ i ].value;
			}
		}
	
	return defaultvalue;
	}

int G_GetNumSpawnArgs
	(
	void
	)

	{
	return numSpawnArgs;
	}

/*
===============
G_GetClassFromArgs

Finds the spawn function for the entity and returns ClassDef *
===============
*/
ClassDef *G_GetClassFromArgs
	(
	void
	)

	{
	const char	*classname;
	ClassDef		*cls = NULL;

	classname = G_GetSpawnArg( "classname" );

	//
	// check normal spawn functions
   // see if the class name is stored within the model
   //
   if ( classname )
      {
      cls = getClassForID( classname );
      if ( !cls )
         {
         cls = getClass( classname );
         }
      }

	if ( !cls )
      {
      const char *model;

      //
      // get Object in case we cannot find an alternative
      //
      cls = &Object::ClassInfo;
	   model = G_GetSpawnArg( "model" );
	   if ( model )
		   {
         sinmdl_cmd_t *cmds;
         int modelindex;
         int i;
	            
         //
         // get handle to def file
         //
         if ( ( strlen( model ) >= 3 ) && ( !strcmpi( &model[ strlen(model) - 3 ], "def" ) ) )
            {
	         if ( !strchr( model, '\\' ) && !strchr( model, '/' ) )
		         {
               char str[128];
		         strcpy( str, "models/" );
		         strcat( str, model );
               modelindex = gi.modelindex( str );
		         }
            else
               modelindex = gi.modelindex( model );
            if ( gi.IsModel( modelindex ) ) 
               {
               cmds = gi.InitCommands( modelindex );
               if (cmds)
                  {
                  for (i=0;i<cmds->num_cmds;i++)
                     {
                     if ( !strcmpi( cmds->cmds[i].args[0], "classname" ) )
                        {
                        cls = getClass( cmds->cmds[i].args[1] );
                        break;
                        }
                     }
                  if ( i == cmds->num_cmds )
                     gi.dprintf( "Classname %s used, but 'classname' was not found in Initialization commands, using Object.\n", classname );
                  }
               else
                  gi.dprintf( "Classname %s used, but SINMDL had no Initialization commands, using Object.\n", classname );
               }
            else
               gi.dprintf( "Classname %s used, but SINMDL was not valid, using Object.\n", classname );
            }
         else
            gi.dprintf( "Classname %s used, but model was not a SINMDL, using Object.\n", classname );
		   }
      else
         {
         gi.dprintf( "Classname %s' used, but no model was set, using Object.\n", classname );
         }
      }

   return cls;
	}

/*
===============
G_CallSpawn

Finds the spawn function for the entity and calls it.
Returns pointer to Entity
===============
*/
Entity *G_CallSpawn
	(
	void
	)

	{
	str      classname;
	ClassDef	*cls;
	Entity	*obj;

	classname = G_GetStringArg( "classname" );
   cls = G_GetClassFromArgs();
	if ( !cls )
		{
		gi.dprintf( "%s doesn't have a spawn function\n", classname.c_str() );
      G_InitSpawnArguments();
		return NULL;
		}
   
	obj = ( Entity * )cls->newInstance();   
   G_InitSpawnArguments();
	if ( !obj )
		{
		gi.dprintf( "%s failed on newInstance\n", classname.c_str() );
   	return NULL;
		}

   return obj;
	}

/*
====================
G_ParseEdict

Parses an edict out of the given string, returning the new position
ed should be a properly initialized empty edict.
====================
*/
const char *G_ParseEdict 
	(
	const char *data
	)

	{
	qboolean		init;
	char			keyname[ 256 ];
	const char	*com_token;

	init = false;

	G_InitSpawnArguments();

	// go through all the dictionary pairs
	while (1)
		{	
		// parse key
		com_token = COM_Parse( &data );
		if ( com_token[ 0 ] == '}' )
			{
			break;
			}

		if ( !data )
			{
			gi.error( "G_ParseEntity: EOF without closing brace" );
			}

		strncpy( keyname, com_token, sizeof( keyname ) - 1 );
		
		// parse value	
		com_token = COM_Parse( &data );
		if ( !data )
			{
			gi.error( "G_ParseEntity: EOF without closing brace" );
			}

		if ( com_token[ 0 ] == '}' )
			{
			gi.error( "G_ParseEntity: closing brace without data" );
			}

		init = true;

		// keynames with a leading underscore are used for utility comments,
		// and are immediately discarded by quake
		if ( keyname[ 0 ] == '_' )
			{
			continue;
			}

		G_SetSpawnArg( keyname, com_token );
		}

	return data;
	}


/*
================
G_FindTeams

Chain together all entities with a matching team field.

All but the first will have the FL_TEAMSLAVE flag set.
All but the last will have the teamchain field set to the next one
================
*/
void G_FindTeams (void)
	{
	edict_t	*e;
	edict_t	*e2;
	edict_t	*next;
	edict_t	*next2;
	Entity	*chain;
	Entity	*ent;
	Entity	*ent2;
	int		c;
	int		c2;

	c = 0;
	c2 = 0;

	for( e = active_edicts.next; e != &active_edicts; e = next )
		{
		assert( e );
		assert( e->inuse );
		assert( e->entity );

		next = e->next;

		if ( e == g_edicts )
			{
			continue;
			}

		ent = e->entity;
		if ( !ent->moveteam.length() )
			{
			continue;
			}

		if ( ent->flags & FL_TEAMSLAVE )
			{
			continue;
			}

		chain = ent;
		ent->teammaster = ent;
		c++;
		c2++;
		for( e2 = next; e2 != &active_edicts; e2 = next2 )
			{
			assert( e2 );
			assert( e2->inuse );
			assert( e2->entity );

			next2 = e2->next;

			ent2 = e2->entity;
			if ( !ent2->moveteam.length() )
				{
				continue;
				}

			if ( ent2->flags & FL_TEAMSLAVE )
				{
				continue;
				}

			if ( ent->moveteam == ent2->moveteam )
				{
				c2++;
				chain->teamchain = ent2;
				ent2->teammaster = ent;
				chain = ent2;
				ent2->flags |= FL_TEAMSLAVE;
				}
			}
		}

	gi.dprintf( "%i teams with %i entities\n", c, c2 );
	}

/*
==============
G_LevelShutdown

Get rid of anything left over from the last level
==============
*/
void G_LevelShutdown
   (
   void
   )

   {
	PathManager.SavePaths();

	assert( active_edicts.next );
	assert( active_edicts.next->prev = &active_edicts );
	assert( active_edicts.prev );
	assert( active_edicts.prev->next = &active_edicts );
	assert( free_edicts.next );
	assert( free_edicts.next->prev == &free_edicts );
	assert( free_edicts.prev );
	assert( free_edicts.prev->next == &free_edicts );

	while( active_edicts.next != &active_edicts )
		{
		assert( active_edicts.next != &free_edicts );
		assert( active_edicts.prev != &free_edicts );

		assert( active_edicts.next );
		assert( active_edicts.next->prev = &active_edicts );
		assert( active_edicts.prev );
		assert( active_edicts.prev->next = &active_edicts );
		assert( free_edicts.next );
		assert( free_edicts.next->prev == &free_edicts );
		assert( free_edicts.prev );
		assert( free_edicts.prev->next == &free_edicts );

		if ( active_edicts.next->entity )
			{
			delete active_edicts.next->entity;
			}
		else
			{
			G_FreeEdict( active_edicts.next );
			}
		}

   globals.num_edicts = game.maxclients + 1;

   // Reset the gravity paths
   gravPathManager.Reset();

   // close all the scripts
	Director.CloseScript();

   // invalidate player readiness
   Director.PlayerNotReady();

   // clearout any waiting events
  	G_ClearEventList();

	gi.FreeTags( TAG_LEVEL );
   }

/*
==============
G_ResetEdicts
==============
*/
void G_ResetEdicts
   (
   void
   )

   {
   int i;

   memset( g_edicts, 0, game.maxentities * sizeof( g_edicts[ 0 ] ) );

	// Add all the edicts to the free list
	LL_Reset( &free_edicts, next, prev );
	LL_Reset( &active_edicts, next, prev );
	for( i = 0; i < game.maxentities; i++ )
		{
		LL_Add( &free_edicts, &g_edicts[ i ], next, prev );
		}

	for (i=0 ; i<game.maxclients ; i++)
		{
     	// set client fields on player ents
		g_edicts[ i + 1 ].client = game.clients + i;
		G_InitClientResp (&game.clients[i]);
		}

   globals.num_edicts = game.maxclients + 1;
   }

/*
==============
G_MapInit

Set up for a new map.  This is called for loading savegames, so anything done here should
be compatible with G_ReadGame.
==============
*/
void G_MapInit
   (
   const char *mapname
   )

   {
	G_ClearEventList();
	PathManager.Init( mapname );

   // init level and console script variables
   consoleVars.ClearList();
	levelVars.ClearList();
   }

/*
==============
G_LevelStart

Does all post-spawning setup.  This is NOT called for savegames.
==============
*/
void G_LevelStart
   (
   void
   )

   {
   ScriptThread *gamescript;
   const char   *scriptname;

   // initialize secrets
   levelVars.SetVariable( "total_secrets", level.total_secrets );
   levelVars.SetVariable( "found_secrets", level.found_secrets );

	G_FindTeams();

   // Create the mission computer
   consoleManager.CreateMissionComputer();

   // call the precache scripts
   G_Precache();

   //
   // start executing the game script
   //
	scriptname = ScriptLib.GetGameScript();
	if ( scriptname && scriptname[ 0 ] )
		{
   	gamescript = Director.CreateThread( scriptname, LEVEL_SCRIPT );
		if ( gamescript )
			{
			// start at the end of this frame
			gamescript->Start( 0 );
			}
		}
   }

/*
==============
G_Precache

Calls precache scripts
==============
*/
void G_Precache
   (
   void
   )

   {
   const char *scriptname;
   int i;

   //
   // load in global0-9.scr
   // 
   for( i = 0; i < 10; i++ )
      {
      G_LoadAndExecScript( va( "global/global%i.scr", i ) );
      }

   //
   // load in precache0-9.scr
   // 
   if ( precache->value )
      {
      for( i = 0; i < 10; i++ )
         {
         G_LoadAndExecScript( va( "global/precache%i.scr", i ) );
         }
      }

   //
   // load in players0-9.scr
   //
   for( i = 0; i< 10; i++ )
      {
      G_LoadAndExecScript( va( "global/players%i.scr", i ) );
      }

   //
   // load in universal_script.scr
   //
   G_LoadAndExecScript( "global/universal_script.scr", "precache:" );

   //
   // precache for the game script
   //
	scriptname = ScriptLib.GetGameScript();
	if ( scriptname && scriptname[ 0 ] )
		{
      G_LoadAndExecScript( scriptname, "precache:" );
		}
   }

/*
==============
G_SpawnEntities

Creates a server's entity / program execution context by
parsing textual entity definitions out of an ent file.
==============
*/
void G_SpawnEntities
	(
	const char *mapname, 
	const char *entities, 
	const char *spawnpoint
	)

	{
	int			inhibit;
	const char	*com_token;
	float			skill_level;
	const char	*value;
	int			spawnflags;
	qboolean		world_spawned;
	cvar_t		*lowdetail;
   int         i=0;
#if 0
   Class       *obj;
   Entity      *ent;
#endif

	// If we get an error, call the server's error function
	if ( setjmp( G_AbortGame ) )
		{
		G_ExitWithError();
		}

	lowdetail = gi.cvar( "r_lowdetail", "0", CVAR_ARCHIVE );

   // Init the level variables
   level = level_locals_t();
   level.mapname = mapname;
	game.spawnpoint = spawnpoint;

   if ( !LoadingServer )
      {
      // Get rid of anything left over from the last level
      G_LevelShutdown();

      G_ResetEdicts();

      // Set up for a new map
      G_MapInit( mapname );
      }

   // Init surface manager & consoles
   surfaceManager.Reset();
   globals.num_surfaces = 0;
   memset (g_surfaces, 0, game.maxsurfaces * sizeof (g_surfaces[0]));
   
   globals.num_consoles = 0;
   memset (g_consoles, 0, game.maxconsoles * sizeof (g_consoles[0]));

	skill_level = floor( skill->value );
   skill_level = bound( skill_level, 0, 3 );
	if ( skill->value != skill_level )
		{
		gi.cvar_forceset( "skill", va( "%f", skill_level ) );
		}

   gameVars.SetVariable( "skill", skill_level );

	// reset out count of the number of game traces
	sv_numtraces = 0;

   level.playerfrozen = false;

	inhibit = 0;
	world_spawned = false;

   // parse ents
	while (1)
		{
		// parse the opening brace	
		com_token = COM_Parse (&entities);
		if (!entities)
			{
			break;
			}
		if (com_token[0] != '{')
			{
			gi.error ("G_LoadFromFile: found %s when expecting {",com_token);
			}

      i++;
      if ( !( i % 20 ) )
         gi.IncrementStatusCount( 20 );

		entities = G_ParseEdict (entities);

		// remove things (except the world) from different skill levels or deathmatch
		value = G_GetSpawnArg( "spawnflags" );
		if ( world_spawned && value )
			{
			spawnflags = atoi( value );
			if (deathmatch->value)
				{
				if ( spawnflags & SPAWNFLAG_NOT_DEATHMATCH )
					{
					inhibit++;
					continue;
					}
				}
			else
				{
				if (
					((skill->value == 0) && (spawnflags & SPAWNFLAG_NOT_EASY)) ||
					((skill->value == 1) && (spawnflags & SPAWNFLAG_NOT_MEDIUM)) ||
					(((skill->value == 2) || (skill->value == 3)) && (spawnflags & SPAWNFLAG_NOT_HARD) ||
					( coop->value && (spawnflags & SPAWNFLAG_NOT_COOP) )) ||
               ( !developer->value && ( spawnflags & SPAWNFLAG_DEVELOPMENT ) ) ||
               ( lowdetail->value && ( spawnflags & SPAWNFLAG_DETAIL ) )
					)
					{
					inhibit++;
					continue;
					}
				}
			}

		game.force_entnum = !world_spawned;
		game.spawn_entnum = 0;
		G_CallSpawn();
		world_spawned = true;

#if 0
      // have to fix G_CallSpawn so that freed entities are accounted for
      if ( obj && obj->isSubclassOf( Entity ) )
         {
         ent = ( Entity * )obj;

	      // Sanity check to see if we're expecting a B-Model
	      assert( !( ( ent->edict->solid == SOLID_BSP ) && !ent->edict->s.modelindex ) );
	      if ( ( ent->edict->solid == SOLID_BSP ) && !ent->edict->s.modelindex )
		      {
		      if ( ent->edict->s.number == 0 )
			      {
			      gi.error( "No model for worldspawn!" );
			      }
		      else
			      {
			      gi.dprintf( "Deleting %s with SOLID_BSP and no model\n", ent->getClassID() );
			      delete ent;
			      }
		      }
         }
#endif
		}	

	game.force_entnum = false;
	gi.dprintf ("%i entities inhibited\n", inhibit);

	G_InitSpawnArguments();

   if ( !LoadingServer || game.autosaved )
      {
      G_LevelStart();
      }
	}

/*
=================
G_Spawn

Either finds a free edict, or allocates a new one.
Try to avoid reusing an entity that was recently freed, because it
can cause the client to think the entity morphed into something else
instead of being removed and recreated, which can cause interpolated
angles and bad trails.
=================
*/
edict_t *G_Spawn
	(
	void
	)

	{
	int		i;
	edict_t	*e;

	e = &g_edicts[ ( int )maxclients->value + 1 ];
	for ( i = maxclients->value + 1; i < globals.num_edicts; i++, e++ )
		{
		// the first couple seconds of server time can involve a lot of
		// freeing and allocating, so relax the replacement policy
		if ( !e->inuse && ( e->freetime < 2 || level.time - e->freetime > 0.5 ) )
			{
			assert( e->next );
			assert( e->prev );
			LL_Remove( e, next, prev );
			G_InitEdict( e );
			assert( active_edicts.next );
			assert( active_edicts.prev );
			LL_Add( &active_edicts, e, next, prev );
			assert( e->next );
			assert( e->prev );
			return e;
			}
		}
	
	if ( i == game.maxentities )
		{
		gi.error( "G_Spawn: no free edicts" );
		}
		
	globals.num_edicts++;
	assert( e->next );
	assert( e->prev );
	LL_Remove( e, next, prev );
	G_InitEdict( e );
	assert( active_edicts.next );
	assert( active_edicts.prev );
	LL_Add( &active_edicts, e, next, prev );
	assert( e->next );
	assert( e->prev );

	assert( e->next != &free_edicts );
	assert( e->prev != &free_edicts );

	return e;
	}

/*
=================
G_FreeEdict

Marks the edict as free
=================
*/
void G_FreeEdict 
	(
	edict_t *ed
	)

	{
	gclient_t *client;

	assert( ed != &free_edicts );

	// unlink from world
	gi.unlinkentity ( ed );

	assert( ed->next );
	assert( ed->prev );

	if ( level.next_edict == ed )
		{
		level.next_edict = ed->next;
		}
	
	LL_Remove( ed, next, prev );

	assert( ed->next == ed );
	assert( ed->prev == ed );
	assert( free_edicts.next );
	assert( free_edicts.prev );

	client = ed->client;
	memset( ed, 0, sizeof( *ed ) );
	ed->client = client;
	ed->freetime = level.time;
	ed->inuse = false;
   ed->s.number = ed - g_edicts;

	assert( free_edicts.next );
	assert( free_edicts.prev );

	LL_Add( &free_edicts, ed, next, prev );

	assert( ed->next );
	assert( ed->prev );
	}

/*
==============
G_InitClientPersistant

This is only called when the game first initializes in single player,
but is called after each death and level change in deathmatch
==============
*/
void G_InitClientPersistant 
	(
	gclient_t *client
	)

	{
	memset( &client->pers, 0, sizeof( client->pers ) );

	client->pers.health		= 100;
	client->pers.max_health	= 100;
	}


void G_InitClientResp
	(
	gclient_t *client
	)

	{
	memset( &client->resp, 0, sizeof( client->resp ) );
	client->resp.enterframe = level.framenum;
	}
