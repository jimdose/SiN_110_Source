//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/g_spawn.h                        $
// $Revision:: 18                                                             $
//   $Author:: Jimdose                                                        $
//     $Date:: 11/07/98 10:01p                                                $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/g_spawn.h                             $
// 
// 18    11/07/98 10:01p Jimdose
// added G_GetClassFromArgs
// 
// 17    10/25/98 11:53p Jimdose
// added EXPORT_TEMPLATE
// 
// 16    10/17/98 8:12p Jimdose
// Changed G_CallSpawn2 to G_CallSpawn
// 
// 15    10/17/98 12:21a Jimdose
// Added G_ResetEdicts
// 
// 14    10/15/98 7:13p Jimdose
// Overrode = for SpawnArgGroup.  Fixes crash on level change with multiplayer
// 
// 13    10/14/98 10:58p Jimdose
// added archive functions to spawnargs classes
// G_MapInit now accepts mapname
// 
// 12    10/14/98 1:20a Jimdose
// Got cross-level persistant info working
// 
// 11    10/10/98 1:33a Jimdose
// Added G_LevelStart and G_Precache
// 
// 10    10/07/98 11:47p Jimdose
// Added G_LevelShutdown and G_MapInit
// 
// 9     8/29/98 9:49p Jimdose
// Moved prototypes from g_local.h
// 
// 8     8/27/98 9:05p Jimdose
// Moved some prototypes that didn't belong here to g_utils.h
// 
// 7     8/12/98 3:19p Aldie
// Added G_CallSpawn2 that returns pointer to entity created.
// 
// 6     5/24/98 8:46p Jimdose
// Made a lot of functions more str-friendly.
// Got rid of a lot of char * based strings
// Cleaned up get spawn arg functions and sound functions
// sound functions now use consistant syntax
// 
// 5     5/24/98 4:48p Jimdose
// Made char *'s const
// 
// 4     5/24/98 2:46p Markd
// Made char *'s into const char *'s
// 
// 3     3/13/98 7:25p Aldie
// Added GetVector
// 
// 2     2/03/98 11:06a Jimdose
// Converted to work with Sin progs
//
// DESCRIPTION:
// 

#ifndef __G_SPAWN_H__
#define __G_SPAWN_H__

#ifdef __cplusplus

#include "entity.h"

// spawnflags
// these are set with checkboxes on each entity in the map editor
#define	SPAWNFLAG_NOT_EASY			0x00000100
#define	SPAWNFLAG_NOT_MEDIUM			0x00000200
#define	SPAWNFLAG_NOT_HARD			0x00000400
#define	SPAWNFLAG_NOT_DEATHMATCH	0x00000800
#define	SPAWNFLAG_NOT_COOP			0x00001000
#define	SPAWNFLAG_DEVELOPMENT		0x00002000
#define	SPAWNFLAG_DETAIL		      0x00004000

class EXPORT_FROM_DLL SpawnArg : public Class
   {
   public:
	   char           key[ 64 ];
	   char           value[ 256 ];

                     CLASS_PROTOTYPE( SpawnArg );

                     SpawnArg();
                     SpawnArg( SpawnArg &arg );
		friend	int   operator==(	SpawnArg a, SpawnArg b );
	   virtual void   Archive( Archiver &arc );
      virtual void   Unarchive( Archiver &arc );

	};

inline int operator==
	(
	SpawnArg a,
	SpawnArg b
	)

	{
   int i;

   i = strcmp( a.key, b.key );
   if ( i )
      {
      return i;
      }

   return strcmp( a.value, b.value );
	}

#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL Container<SpawnArg>;
#endif

class EXPORT_FROM_DLL SpawnArgs : public Class
   {
   public:
      Container<SpawnArg> argList;

                     CLASS_PROTOTYPE( SpawnArgs );

                     SpawnArgs();
                     SpawnArgs( SpawnArgs &arglist );
      int            NumArgs( void );
      void           SetArgs( void );
      void           RestoreArgs( void );
		void           operator=( SpawnArgs &a );
		friend	int   operator==(	SpawnArgs a, SpawnArgs b );
	   virtual void   Archive( Archiver &arc );
      virtual void   Unarchive( Archiver &arc );
	};

inline int operator==
	(
	SpawnArgs a,
	SpawnArgs b
	)

	{
   return -1;
	}

#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL Container<SpawnArgs>;
#endif

class EXPORT_FROM_DLL SpawnArgGroup : public Class
   {
   public:
      Container<SpawnArgs> spawnArgList;

                     CLASS_PROTOTYPE( SpawnArgGroup );

                     SpawnArgGroup();
                     SpawnArgGroup( SpawnArgGroup &group );
      int            NumInGroup( void );
      void           AddArgs( void );
      void           RestoreArgs( int i );
		void           operator=( SpawnArgGroup &a );
      friend	int   operator==(	SpawnArgGroup a, SpawnArgGroup b );
	   virtual void   Archive( Archiver &arc );
      virtual void   Unarchive( Archiver &arc );
	};

inline int operator==
	(
	SpawnArgGroup a,
	SpawnArgGroup b
	)

	{
   return -1;
	}

#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL Container<SpawnArgGroup>;
#endif

class EXPORT_FROM_DLL SpawnArgsForEntity : public Class
   {
   public:
      Container<SpawnArgGroup>   groupList;
      Container<int>             entnumList;

                     CLASS_PROTOTYPE( SpawnArgsForEntity );

      void           Reset( void );
      void           AddEnt( Entity *ent );
      qboolean       RestoreEnt( Entity *ent );
      void           RestoreEnts( void );
	   virtual void   Archive( Archiver &arc );
      virtual void   Unarchive( Archiver &arc );
	};

extern SpawnArgsForEntity PersistantData;

void			G_SetFloatArg( const char *key, double value	);
void			G_SetIntArg( const char *key, int value );
qboolean		G_SetSpawnArg( const char *keyname, const char *value );

void			G_DefaultArg( const char *key, const char *defaultvalue );
void			G_DefaultFloatArg( const char *key, double defaultvalue );
void			G_DefaultIntArg( const char *key, int defaultvalue );

float			G_GetFloatArg( const char *key, double defaultvalue = 0 );
Vector		G_GetVectorArg( const char *key, Vector defaultvalue = Vector( 0, 0, 0 ) );
int			G_GetIntArg( const char *key, int defaultvalue = 0 );
str			G_GetStringArg( const char *key, const char *defaultvalue = NULL );
const char	*G_GetSpawnArg( const char *key, const char *defaultvalue = NULL );

void			G_InitSpawnArguments( void );
int			G_GetNumSpawnArgs( void );

void			G_InitClientPersistant( gclient_t *client );
void			G_InitClientResp( gclient_t *client );

ClassDef    *G_GetClassFromArgs( void );
Entity		*G_CallSpawn( void );
const char	*G_ParseEdict( const char *data, edict_t *ent);
void			G_FindTeams( void );

void        G_LevelShutdown( void );
void        G_ResetEdicts( void );
void        G_MapInit( const char *mapname );
void        G_LevelStart( void );
void        G_Precache( void );

#endif

#ifdef __cplusplus
extern "C" {
#endif

EXPORT_FROM_DLL void	G_SpawnEntities( const char *mapname, const char *entities, const char *spawnpoint );

#ifdef __cplusplus
	}
#endif

#endif
