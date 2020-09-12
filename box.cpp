//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/box.cpp                          $
// $Revision:: 36                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 11/15/98 7:51p                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/box.cpp                               $
// 
// 36    11/15/98 7:51p Markd
// fixed boxes so that they wouldn't be case as Item's 
// 
// 35    11/13/98 2:41p Markd
// fixed box precaching
// 
// 34    11/09/98 12:13a Aldie
// Do a modelindex on stuff in boxes
// 
// 33    10/26/98 12:28a Markd
// Put in no jc support
// 
// 32    10/25/98 2:38a Markd
// put in dialog time in box code
// 
// 31    10/25/98 12:47a Markd
// fixed mutant flag for dialog
// 
// 30    10/25/98 12:24a Markd
// Put in sounds when blade blows up boxes
// 
// 29    10/19/98 12:10a Jimdose
// made all code use fast checks for inheritance (no text lookups when
// possible)
// isSubclassOf no longer requires ::_classinfo()
// 
// 28    10/17/98 7:35p Jimdose
// Changed G_CallSpawn to G_CallSpawn2
// 
// 27    8/29/98 5:27p Markd
// added specialfx, replaced misc with specialfx where appropriate
// 
// 26    8/18/98 11:08p Markd
// Added new Alias System
// 
// 25    8/18/98 5:50p Aldie
// Added target activation to box killed function
// 
// 24    8/12/98 3:18p Aldie
// 
// 23    8/09/98 6:10p Aldie
// New box behavior
// 
// 22    8/08/98 9:02p Aldie
// Removed unused var
// 
// 21    8/08/98 8:22p Markd
// Took out random items from box code
// 
// 20    7/14/98 6:56p Aldie
// Updated healths
// 
// 19    6/24/98 12:39p Markd
// Added default tesselation percentage
// 
// 18    6/18/98 5:41p Markd
// Fixed crash with boxes
// 
// 17    6/18/98 2:00p Markd
// rewrote tesselation code
// 
// 16    6/10/98 1:19p Markd
// Removed 357 bullets
// 
// 15    5/27/98 9:04p Markd
// weighted boxes with more ammo
// 
// 14    5/27/98 8:34p Markd
// Put more health in boxes
// 
// 13    5/27/98 5:01a Markd
// Put in dynamic spawning of goodies when box is destroyed
// 
// 12    5/25/98 7:51p Jimdose
// Made TellNeighborsToFall use G_NextEntity to check all entities
// 
// 11    5/24/98 8:46p Jimdose
// Made a lot of functions more str-friendly.
// Got rid of a lot of char * based strings
// Cleaned up get spawn arg functions and sound functions
// sound functions now use consistant syntax
// 
// 10    5/24/98 1:03a Jimdose
// Added breaking sound event when killed
// 
// 9     5/11/98 3:51p Markd
// Changed crate blowup sound
// 
// 8     5/01/98 11:09a Markd
// Added sound to tesselation event
// 
// 7     4/14/98 6:55p Markd
// Added thickness to tesselation
// 
// 6     4/08/98 4:19p Jimdose
// Converted to Q2
// 
// 4     10/31/97 7:18p Markd
// Changed triagulate call and added a hidemodel call when blowing up
// 
// 3     10/31/97 4:32p Markd
// Added shatter sound and also fixed a swapped MOVETYPE/SOLIDTYPE bug
// 
// 2     10/30/97 7:42p Jimdose
// Created file
//
// DESCRIPTION:
// Explodable box that falls when boxes below it are destroyed.
// 

#include "g_local.h"
#include "entity.h"
#include "box.h"
#include "ammo.h"
#include "health.h"
#include "specialfx.h"

Event EV_Box_Think( "think" );

ResponseDef Box::Responses[] =
	{
	   { &EV_Box_Think,			( Response )Box::Falling },
	   { &EV_Killed,				( Response )Box::Killed },
		{ NULL, NULL }
	};

/*****************************************************************************/
/*SINED func_box (0 .5 .8) ?

  Explodable box that falls when boxes below it are destroyed.  
"items" - List of classnames to spawn when the box is destroyed.  Separate
each classname by spaces (E.g. Adrenaline RocketLauncher).  Default is NULL.
"angles" - Orientation of the item that is spawned.
"health" - Health of the box ( default is 60 )
/*****************************************************************************/

CLASS_DECLARATION( Entity, Box, "func_box" );

EXPORT_FROM_DLL void Box::StartFalling
	(
	void
	)

	{
	movetime = 0;
	velocity += "0 0 100";
	setMoveType( MOVETYPE_TOSS );
	setSolidType( SOLID_BBOX );
	setOrigin( worldorigin + Vector( 0, 0, 1 ) );
	PostEvent( EV_Box_Think, FRAMETIME );
	}

EXPORT_FROM_DLL void Box::Falling
	(
	Event *ev
	)

	{
	if ( velocity != vec_zero )
		{
		movetime = level.time + 1;
		}

	if ( movetime < level.time )
		{
		setMoveType( MOVETYPE_PUSH );
		setSolidType( SOLID_BSP );
		}
	else
		{
		PostEvent( EV_Box_Think, FRAMETIME );
		}
	}

void Box::TellNeighborsToFall
	(
	void
	)

	{
	Entity	*ent;
	//Event		*e;
	Vector	min;
	Vector	max;
	Entity	*next;

	min = absmin + Vector( 6, 6, 6 );
	max = absmax + Vector( -6, -6, 0 );

	for( ent = G_NextEntity( world ); ent != NULL; ent = next )
		{
		next = G_NextEntity( ent );

		if ( ( ent != this ) && ent->isSubclassOf( Box ) )
			{
			if ( !( ( ent->absmax[ 0 ] < min[ 0 ] ) ||
				( ent->absmax[ 1 ] < min[ 1 ] ) ||
				( ent->absmax[ 2 ] < min[ 2 ] ) ||
				( ent->absmin[ 0 ] > max[ 0 ] ) ||
				( ent->absmin[ 1 ] > max[ 1 ] ) ||
				( ent->absmin[ 2 ] > max[ 2 ] ) ) )

				{
				if ( ent->takedamage != DAMAGE_NO )
					( ( Box * )ent )->StartFalling();
				// Ok, it's a hack.
				//if ( ent->takedamage != DAMAGE_NO )
				//	{
				//	e = new Event( ev );
				//	ent->ProcessEvent( e );
				//	}
				}
			}
		}
	}

void Box::Killed
	(
	Event *ev
	)

	{
   Entity      *attacker;
   Vector      dir;
   Vector      org;
   Entity      *ent;
   const char  *s;
   const char  *token;
   int         width = 0;
   int         depth = 0;
   int         boxwidth;
   char        temp[ 128 ];
   const char	*name;
   int         num;
   Event       *event;
   qboolean    spawned;
   static float last_dialog_time = 0;

   hideModel();
	RandomGlobalSound( "impact_crateexplo", 1, CHAN_BODY, ATTN_NORM );

	takedamage = DAMAGE_NO;

	TellNeighborsToFall();
	
	ProcessEvent( EV_BreakingSound );

   attacker = ev->GetEntity( 1 );
   dir = worldorigin - attacker->worldorigin;
   TesselateModel
      (
      this,
      tess_min_size,
      tess_max_size,
      dir,
      ev->GetInteger( 2 ),
      tess_percentage,
      tess_thickness,
      vec3_origin
      );

   //
   // fire off targets
   //
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
			event->AddEntity( attacker );
			ent->PostEvent( event, 0 );
			}
		while ( 1 );
		}



   // items holds the list of def files to spawn
   s = items.c_str();
   
   G_InitSpawnArguments();

   if ( setangles )
      {
      sprintf( temp, "%f %f %f", angles[ 0 ],angles[ 1 ],angles[ 2 ] );
      G_SetSpawnArg( "angles", temp );
      }

   spawned = false;
   boxwidth = maxs[0];
   while (1)
      {
      token = COM_Parse(&s);
      
      if (!token[0])
         break;

      G_SetSpawnArg( "model", token );

      if ( ( width * 32 ) > boxwidth )
         {
         width = 0;
         depth++;
         }

      // Calculate and set the origin
      org = worldorigin + Vector("0 0 32") + Vector("32 0 0") * width + Vector("0 32 0") * depth;
      width++;
      sprintf( temp, "%f %f %f", org[ 0 ], org[ 1 ], org[ 2 ] );
      G_SetSpawnArg( "origin", temp );
      
      // Create the item
      ent = ( Entity * )G_CallSpawn();
      spawned = true;

      // Postpone the Drop because the box is still there.
      ent->PostponeEvent( EV_Item_DropToFloor, 0.1f );
      }   
   G_InitSpawnArguments();

   if ( 
         spawned && 
         attacker->isClient() && 
         ( last_dialog_time < level.time ) &&
         ( !( attacker->flags & FL_SP_MUTANT ) ) && 
         ( !deathmatch->value )
      )
      {
      char name[ 128 ];
      int num;

      last_dialog_time = level.time + 25;
      if ( level.no_jc )
         {
         num = (int)G_Random( 3 ) + 1;
         }
      else
         {
         num = (int)G_Random( 5 ) + 1;
         }
      sprintf( name, "global/universal_script.scr::blade_finds_item%d", num );
      ExecuteThread( name, true );
      }
   PostEvent( EV_Remove, 0 );
	}

Box::Box()
	{
   const char  *text;
   const char  *s;
   char        token[ MAX_TOKEN_CHARS ];

   movetime = 0;
	showModel();
	setMoveType( MOVETYPE_PUSH );
	setSolidType( SOLID_BSP );
	setOrigin( origin );

	health = G_GetIntArg( "health", 60 );
	max_health = health;
	takedamage = DAMAGE_YES;
   tess_thickness = 20;
   text = G_GetSpawnArg( "items" );
   
   if ( text )
      {
      items = text;
      s = items.c_str();
      while ( 1 )
         {
         strcpy( token, COM_Parse(&s) );
         if ( !token[0] )
            break;
         modelIndex( token );
         }
      }

   setangles = ( G_GetSpawnArg( "angle" ) || G_GetSpawnArg( "angles" ) );
	if ( setangles )
		{
		float angle;
		angle = G_GetFloatArg( "angle", 0 );
		angles = G_GetVectorArg( "angles", Vector( 0, angle, 0 ) );
		}
   }
