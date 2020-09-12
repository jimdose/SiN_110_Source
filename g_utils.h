//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/g_utils.h                        $
// $Revision:: 17                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 5/19/99 4:57p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/g_utils.h                             $
// 
// 17    5/19/99 4:57p Markd
// fixed some errors
// 
// 16    3/02/99 9:16p Aldie
// Added CTF game code
// 
// 2     2/16/99 4:08p Aldie
// 
// 1     2/11/99 1:38p Aldie
// 
// 15    10/26/98 3:50a Markd
// put in prediction
// 
// 14    10/18/98 3:23a Jimdose
// Added G_Milliseconds and G_DebugPrintf
// 
// 13    10/16/98 7:18p Markd
// Changed ExecuteThread a little bit
// 
// 12    10/10/98 1:34a Jimdose
// added edict archiving functions
// 
// 11    10/09/98 4:54p Markd
// Added ExecuteThread
// 
// 10    10/07/98 11:48p Jimdose
// Added G_FixSlashes
// 
// 9     10/03/98 1:10p Aldie
// added findclientsinradius
// 
// 8     9/14/98 5:41p Jimdose
// Added G_CalcBoundsOfMove
// 
// 7     8/29/98 9:50p Jimdose
// Moved prototypes from g_local.h
// Moved all debugline functions from g_main.cpp
// Added trace info to G_Trace
// 
// 6     8/27/98 9:05p Jimdose
// Moved several short functions to g_utils.h as inline
// 
// 5     8/24/98 4:55p Markd
// Added G_CalculateImpulse
// 
// 4     2/18/98 8:08p Jimdose
// Prototyped IsNumeric
// 
// 3     2/06/98 5:51p Jimdose
// Added KillBox
// Changed G_TouchTriggers and M_CheckBottom to be .cpp compatible
// 
// 2     2/03/98 10:49a Jimdose
// Created file.
//
// DESCRIPTION:
// 

#ifndef __G_UTILS_H__
#define __G_UTILS_H__

class Archiver;

EXPORT_FROM_DLL void       G_ArchiveEdict( Archiver &arc, edict_t *edict );
EXPORT_FROM_DLL void       G_UnarchiveEdict( Archiver &arc, edict_t *edict );

#include "entity.h"

EXPORT_FROM_DLL void			G_InitEdict (edict_t *e);
EXPORT_FROM_DLL edict_t		*G_Spawn (void);
EXPORT_FROM_DLL void			G_FreeEdict (edict_t *e);

EXPORT_FROM_DLL void			G_TouchTriggers (Entity *ent);
EXPORT_FROM_DLL void			G_TouchSolids (Entity *ent);

EXPORT_FROM_DLL char			*G_CopyString (const char *in);

EXPORT_FROM_DLL int			G_FindClass( int entnum, const char *classname );
EXPORT_FROM_DLL Entity		*G_NextEntity( Entity *ent );

EXPORT_FROM_DLL void       G_CalcBoundsOfMove( Vector &start, Vector &end, Vector &mins, Vector &maxs, Vector *minbounds, Vector *maxbounds );

EXPORT_FROM_DLL void			G_ShowTrace( trace_t *trace, edict_t *passent, const char *reason );
EXPORT_FROM_DLL trace_t		G_Trace( Vector &start, Vector &mins, Vector &maxs, Vector &end, Entity *passent, int contentmask, const char *reason );
EXPORT_FROM_DLL trace_t		G_Trace( vec3_t start, vec3_t mins, vec3_t maxs, vec3_t end, edict_t *passent, int contentmask, const char *reason );
EXPORT_FROM_DLL trace_t		G_FullTrace( Vector &start, Vector &mins, Vector &maxs, Vector &end, float radius, Entity *passent, int contentmask,	const char *reason );
EXPORT_FROM_DLL trace_t		G_FullTrace( vec3_t start, vec3_t mins, vec3_t maxs, vec3_t end, float radius, edict_t *passent, int contentmask,	const char *reason );

EXPORT_FROM_DLL void			SelectSpawnPoint( Vector &origin, Vector &angles, edict_t *edcit, int *gravaxis = NULL );

EXPORT_FROM_DLL int			G_FindTarget( int entnum, const char *name );
EXPORT_FROM_DLL Entity		*G_NextEntity( Entity *ent );

EXPORT_FROM_DLL qboolean	M_CheckBottom( Entity *ent );

EXPORT_FROM_DLL Vector		G_GetMovedir( void );
EXPORT_FROM_DLL qboolean	KillBox( Entity *ent );
EXPORT_FROM_DLL qboolean	IsNumeric( const char *str );

EXPORT_FROM_DLL Entity		*findradius( Entity *startent, Vector org, float rad );
EXPORT_FROM_DLL Entity		*findclientsinradius( Entity *startent, Vector org, float rad );
EXPORT_FROM_DLL const char	*G_GetNameForSurface( csurface_t *s );

EXPORT_FROM_DLL Vector		G_CalculateImpulse( Vector start, Vector end, float speed, float gravity );
EXPORT_FROM_DLL Vector     G_PredictPosition( Vector start, Vector target, Vector targetvelocity, float speed );

EXPORT_FROM_DLL void G_InitDebugLines( void );
EXPORT_FROM_DLL void G_DebugLine( Vector start, Vector end, float r, float g, float b, float alpha );
EXPORT_FROM_DLL void G_Color3f( float r, float g, float b	);
EXPORT_FROM_DLL void G_Color3v( Vector color );
EXPORT_FROM_DLL void G_Color4f( float r, float g,	float b,	float alpha	);
EXPORT_FROM_DLL void G_Color3vf( Vector color, float alpha );
EXPORT_FROM_DLL void G_BeginLine( void );
EXPORT_FROM_DLL void G_Vertex( Vector v );
EXPORT_FROM_DLL void G_EndLine( void );
EXPORT_FROM_DLL void G_DebugBBox( Vector origin, Vector mins, Vector maxs, float r, float g, float b, float alpha );
EXPORT_FROM_DLL void G_DrawDebugNumber( Vector org, float number, float scale, float r, float g, float b, int precision = 0 );

EXPORT_FROM_DLL void G_LoadAndExecScript( const char *filename, const char *label = NULL );
EXPORT_FROM_DLL ScriptThread *ExecuteThread( str thread_name, qboolean start = true );

EXPORT_FROM_DLL int  G_Milliseconds( void );
EXPORT_FROM_DLL void G_DebugPrintf( const char *fmt, ... );

//==================================================================
//
// Inline functions
//
//==================================================================

inline EXPORT_FROM_DLL float angmod
	(
	float v
	)

	{
	int b;

	b = ( int )v;

	b = b - ( b % 360 );
	if ( b < 0 )
		{
		b -= 360;
		}

	return v - ( float )b;
	}

/*
=================
G_GetEntity

Takes an index to an entity and returns pointer to it.
=================
*/

inline EXPORT_FROM_DLL Entity *G_GetEntity
	(
	int entnum
	)

	{
	if ( ( entnum < 0 ) || ( entnum >= globals.max_edicts ) )
		{
		gi.error ("G_GetEntity: %d out of valid range.", entnum );
		}

	return ( Entity * )g_edicts[ entnum ].entity;
	}

/*
=================
G_Random

Returns a number from 0<= num < 1

random()
=================
*/

inline EXPORT_FROM_DLL float G_Random
	(
	void
	)

	{
	return ( ( float )( rand() & 0x7fff ) ) / ( ( float )0x8000 );
	}

/*
=================
G_Random

Returns a number from 0 <= num < n

random()
=================
*/

inline EXPORT_FROM_DLL float G_Random
	(
	float n
	)

	{
	return G_Random() * n;
	}

/*
=================
G_CRandom

Returns a number from -1 <= num < 1

crandom()
=================
*/

inline EXPORT_FROM_DLL float G_CRandom
	(
	void
	)

	{
	return G_Random( 2 ) - 1;
	}

/*
=================
G_CRandom

Returns a number from -n <= num < n

crandom()
=================
*/

inline EXPORT_FROM_DLL float G_CRandom
	(
	float n
	)

	{
	return G_CRandom() * n;
	}

/*
=================
G_FixSlashes

Converts all backslashes in a string to forward slashes.
Used to make filenames consistant.
=================
*/

inline EXPORT_FROM_DLL str G_FixSlashes
   (
   const char *filename
   )

   {
	int i;
	int len;
	str text;

   if ( filename )
      {
	   // Convert all forward slashes to back slashes
	   text = filename;
	   len = text.length();
	   for( i = 0; i < len; i++ )
		   {
		   if ( text[ i ] == '\\' )
			   {
			   text[ i ] = '/';
			   }
		   }
      }

   return text;
   }

#endif /* g_utils.h */
