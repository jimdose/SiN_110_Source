//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/explosion.cpp                    $
// $Revision:: 51                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 3/30/99 4:51p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/explosion.cpp                         $
// 
// 51    3/30/99 4:51p Aldie
// 
// 50    3/11/99 3:45p Aldie
// Added meansofdeath to explosion
// 
// 49    3/11/99 2:03p Aldie
// Added mod to explosion damage
// 
// 48    10/24/98 12:42a Markd
// changed origins to worldorigins where appropriate
// 
// 47    10/22/98 7:57p Markd
// put in proper pre-caching in all the classes
// 
// 46    10/22/98 5:03p Jimdose
// Made MakeExplosion properly use the activator
// 
// 45    10/19/98 12:07a Jimdose
// made all code use fast checks for inheritance (no text lookups when
// possible)
// isSubclassOf no longer requires ::_classinfo()
// 
// 44    10/14/98 10:55p Jimdose
// made CreateExplosion not ignore the explosion if attacker and ignore are not
// set
// 
// 43    10/07/98 11:47p Jimdose
// made FlashPlayers only check clients instead of using findradius
// 
// 42    10/05/98 10:23p Aldie
// Made flash based on distance
// 
// 41    10/04/98 10:28p Aldie
// Added multiple weapon changes.  Damage, flashes, quantum stuff
// 
// 40    10/02/98 7:19p Aldie
// Added FlashPlayers to do blinding flashes
// 
// 39    9/05/98 12:09p Aldie
// Made RadiusDamage non static
// 
// 38    9/01/98 3:05p Markd
// Rewrote explosion code
// 
// 37    8/30/98 7:06p Markd
// forgot to put scale into func_exploder
// 
// 36    8/29/98 7:15p Markd
// Added big explosion support
// 
// 35    8/29/98 5:27p Markd
// added specialfx, replaced misc with specialfx where appropriate
// 
// 34    8/27/98 9:01p Jimdose
// Changed centroid to a variable
// 
// 33    8/17/98 2:55p Aldie
// Increased splash damage a little
// 
// 32    8/06/98 10:53p Aldie
// Added weapon tweaks and kickback.  Also modified blast radius damage and
// rocket jumping.
// 
// 31    7/26/98 1:18a Aldie
// Put explosion stuff back in
// 
// 30    7/25/98 7:59p Aldie
// Moved more stuff client side.
// 
// 29    7/23/98 6:17p Aldie
// Updated damage system and fixed some damage related bugs.  Also put tracers
// back to the way they were, and added gib event to funcscriptmodels
// 
// 28    7/21/98 1:10p Aldie
// Added meansofdeath to obituaries
// 
// 27    7/15/98 9:58p Markd
// changed syntax of TempDLight
// 
// 26    7/09/98 12:02a Jimdose
// Changed remove event to be posted instead of processed
// 
// 25    6/29/98 8:21p Aldie
// Updated explosion methods
// 
// 24    6/25/98 8:47p Markd
// Added keyed items for Triggers, Rewrote Item class, rewrote every pickup
// method
// 
// 23    6/15/98 10:37a Aldie
// Made explosion more generic
// 
// 22    6/10/98 2:10p Aldie
// Updated damage function.
// 
// 21    5/25/98 8:00p Markd
// Accidentally left AUTO_ANIMATE on
// 
// 20    5/25/98 7:58p Markd
// Cleaned it up a bunch
// 
// 19    5/25/98 7:04p Markd
// Changed to TE_TEMPMODEL system
// 
// 18    5/24/98 11:01p Markd
// made sure activator is valid
// 
// 17    5/24/98 8:46p Jimdose
// Made a lot of functions more str-friendly.
// Got rid of a lot of char * based strings
// Cleaned up get spawn arg functions and sound functions
// sound functions now use consistant syntax
// 
// 16    5/24/98 2:47p Markd
// Made char *'s into const char *'s
// 
// 15    5/24/98 1:03a Jimdose
// Added sound events for ai
// 
// 14    5/23/98 6:28p Jimdose
// Fixed bug in RadiusDamage where the entity could be freed by damage and the
// pointer then used in findradius.  Damage is now posted as an event
// 
// 13    5/03/98 4:31p Jimdose
// Changed Vector class.  No longer includes PointsTo
// 
// 12    4/28/98 5:32p Jimdose
// Changed the radius back again
// 
// 11    4/18/98 2:31p Jimdose
// Changed radius of splash damage from explosion
// 
// 10    4/06/98 5:30p Jimdose
// Fixed NULL attacker bug in MakeExplosion
// 
// 9     4/05/98 6:42p Jimdose
// Added Exploders and MultiExploders
// 
// 8     3/27/98 11:03p Jimdose
// changed explode.def to explode.spr
// 
// 7     3/23/98 1:31p Jimdose
// Revamped event and command system
// 
// 6     3/18/98 2:27p Jimdose
// Converted to work with new sin
// 
// 4     10/27/97 3:30p Jimdose
// Removed dependency on quakedef.h
// 
// 3     10/03/97 12:45a Jimdose
// Made explosion give off Redish-orange flash
// 
// 2     9/26/97 5:23p Jimdose
// Added standard Ritual headers
//
// DESCRIPTION:
// Standard explosion object that is spawned by other entites and not map designers.
// Explosion is used by many of the weapons for the blast effect, but is also used
// by the Exploder and MultiExploder triggers.  These triggers create one or more
// explosions each time they are activated.
// 

#include "g_local.h"
#include "entity.h"
#include "trigger.h"
#include "explosion.h"
#include "specialfx.h"
#include "player.h"

#define RANDOM_TIME (1<<1)
#define RANDOM_SCALE (1<<2)
#define BIG_EXPLOSION (1<<3)

void FlashPlayers
   (
   Vector org,
   float r,
   float g, 
   float b,
   float a,
   float rad
   )

   {
   Event    *ev1;
   trace_t  trace;
   Vector   delta;
   float    length;
   Player   *player;
   edict_t  *edict;
   int      i;

	for( i = 0; i < maxclients->value; i++ )
		{
		edict = g_edicts + 1 + i;
      if ( !edict->inuse || !edict->client || !edict->entity || !edict->entity->isSubclassOf( Player ) ||
         !edict->entity->WithinDistance( org, rad ) )
			{
			continue;
			}

      player = ( Player * )edict->entity;

      trace = G_Trace( org, vec_zero, vec_zero, player->worldorigin + player->eyeposition, player, MASK_OPAQUE, "FlashPlayers" );      
      if ( trace.fraction != 1.0 )
         {
         continue;
         }

      delta = org - trace.endpos;
      length = delta.length();

      a = a * ( 1 - length / rad );

      ev1 = new Event( EV_Player_SetFlashColor );
      ev1->AddFloat( r );
      ev1->AddFloat( g );
      ev1->AddFloat( b );
      ev1->AddFloat( a );
      player->ProcessEvent( ev1 );
      }
   }
   
void RadiusDamage
	(
	Entity *inflictorent, 
	Entity *attackerent, 
	int damage, 
	Entity *ignoreent,
   int mod
	)

	{
	float		points;
	Entity	*ent;
	Vector	org;
	Vector	v;
	float		rad;

	rad = ( float )( damage + 60 );

	ent = findradius( NULL, inflictorent->worldorigin.vec3(), rad );
	while( ent )
		{
		if ( ( ent != ignoreent ) && ( ent->takedamage ) )
			{
			org = ent->centroid;
			v = org - inflictorent->worldorigin;
			points = v.length() * 0.5f;
			if ( points < 0 )
				{
				points = 0;
				}
			points = damage - points;
			if ( ent == attackerent  )
				{
				points *= 0.5;
				}

			if ( points > 0 )
				{
				if ( inflictorent->CanDamage( ent ) )
					{
               ent->Damage(inflictorent, attackerent, points,
                           org, v, vec_zero, points, 
                           DAMAGE_RADIUS, mod,
                           -1, -1, 1.0f );
					}
				}
			}
		ent = findradius( ent, inflictorent->worldorigin.vec3(), rad );
		}
	}

void CreateExplosion
   (
   Vector pos, 
   float  damage,
   float  scale, 
   qboolean bigexplosion,
   Entity *inflictor,
   Entity *attacker,
   Entity *ignore, 
	int    meansofdeath,
   float  volume,
   float  attenuation,
   float  r,
   float  g,
   float  b,
   float  light_radius,
   float  life,
   float  decay
   )

   {
   assert( inflictor );

   if ( !inflictor )
      {
      return;
      }

   if ( !attacker )
      {
      attacker = world;
      }
   
   if ( volume > 4.0f )
      volume = 4.0f;

	if ( damage < 120 )
		{
		inflictor->RandomPositionedSound( pos, "impact_smallexplosion", volume, CHAN_AUTO, attenuation );
		}
	else
		{
		inflictor->RandomPositionedSound( pos, "impact_bigexplosion", volume, CHAN_AUTO, attenuation );
		}

	RadiusDamage( inflictor, attacker, damage, ignore, meansofdeath );
	if ( inflictor )
      inflictor->ProcessEvent( EV_WeaponSound );

   if ( bigexplosion )
      SpawnScaledExplosion( pos, scale );
   else
      TempModel( NULL, pos, "0 0 0", "sprites/explode.spr", 0, scale, 1.0f, TEMPMODEL_ANIMATE_ONCE, 10 );
   }

/*****************************************************************************/
/*SINED func_exploder (0.4 0 0) (0 0 0) (8 8 8) x x x BIG_EXPLOSION

  Spawns an explosion when triggered.  Triggers any targets.

  "dmg" specifies how much damage to cause. Default indicates 120.
  "volume" volume at which to play explosions (default 1.0)
  "attenuation" attenuation for explosions (default normal)
  "key" The item needed to activate this. (default nothing)
/*****************************************************************************/

ResponseDef Exploder::Responses[] =
	{
		{ &EV_Touch,				NULL },
		{ &EV_Trigger_Effect,	( Response )Exploder::MakeExplosion },
		{ NULL, NULL }
	};

CLASS_DECLARATION( Trigger, Exploder, "func_exploder" );

void Exploder::MakeExplosion
	(
	Event *ev
	)

	{
   CreateExplosion
      ( 
      worldorigin, 
      edict->s.scale * damage, 
      edict->s.scale, 
      ( spawnflags & BIG_EXPLOSION ), 
      this, 
      ev->GetEntity( 1 ), 
      this,
      volume * edict->s.scale,
      attenuation
      );
	} 

Exploder::Exploder()
	{
	damage = G_GetIntArg( "dmg", 120 );
	if ( damage < 0 )
		{
		damage = 0;
		}

   modelIndex( "sprites/explode.spr" );
	attenuation = G_GetFloatArg( "attenuation", 1.0 );
	volume = G_GetFloatArg( "volume", 1.0 );
	respondto = TRIGGER_PLAYERS | TRIGGER_MONSTERS | TRIGGER_PROJECTILES;
	}

/*****************************************************************************/
/*SINED func_multi_exploder (0.4 0 0) ? x RANDOM_TIME RANDOM_SCALE BIG_EXPLOSION

  Spawns an explosion when triggered.  Triggers any targets.
  size of brush determines where explosions will occur.

  "dmg" specifies how much damage to cause from each explosion. (Default 120)
  "delay" delay before exploding (Default 0 seconds)
  "duration" how long to explode for (Default 1 second)
  "wait" time between each explosion (default 0.25 seconds)
  "volume" volume to play explosion sound at (default 0.5)
  "attenuation" attenuation for explosions (default normal)
  "random" random factor (default 0.25)
  "key" The item needed to activate this. (default nothing)

  RANDOM_TIME adjusts the wait between each explosion by the random factor
  RANDOM_SCALE adjusts the size of each explosion by the random factor

/*****************************************************************************/

CLASS_DECLARATION( Trigger, MultiExploder, "func_multi_exploder" );

ResponseDef MultiExploder::Responses[] =
	{
		{ &EV_Touch,				NULL },
		{ &EV_Trigger_Effect,	( Response )MultiExploder::MakeExplosion },
		{ NULL, NULL }
	};

void MultiExploder::MakeExplosion
	(
	Event *ev
	)

	{
	Vector pos;
	float t;
	float r;
	float v;
   Entity *other;
   Event *event;

	other = ev->GetEntity( 1 );

   // make sure other is valid
   if ( !other )
      {
      other = world;
      }

	// prevent the trigger from triggering again
	trigger_time = -1;

	if ( !explode_time )
		{
		explode_time = level.time + duration;
		}
   
	if ( spawnflags & RANDOM_TIME )
		{
		t = explodewait * ( 1 + G_CRandom( randomness ) );
		}
	else
		{
		t = explodewait;
		}

	event = new Event( EV_Trigger_Effect );
	event->AddEntity( other );
   PostEvent( event, t );

	if ( level.time > explode_time )
		{
		PostEvent( EV_Remove, 0 );
		return;
		}

	pos[ 0 ] = absmin[ 0 ] + G_Random( absmax[ 0 ] - absmin[ 0 ] );
	pos[ 1 ] = absmin[ 1 ] + G_Random( absmax[ 1 ] - absmin[ 1 ] );
	pos[ 2 ] = absmin[ 2 ] + G_Random( absmax[ 2 ] - absmin[ 2 ] );

	if ( spawnflags & RANDOM_SCALE )
		{
		r = edict->s.scale + G_CRandom( randomness );
		}
	else 
		{
		r = edict->s.scale;
		}

	if ( r < 1 )
		{
		v = volume * r;
		}
	else
		{
		v = volume;
		}
   CreateExplosion
      ( 
      pos, 
      damage * r, 
      r, 
      ( spawnflags & BIG_EXPLOSION ), 
      this, 
      other, 
      this,
      volume,
      attenuation
      );
	}

MultiExploder::MultiExploder()
	{
	damage = G_GetIntArg( "dmg", 120 );
	if ( damage < 0 )
		{
		damage = 0;
		}

	attenuation		= G_GetFloatArg( "attenuation", 1.0 );
	volume			= G_GetFloatArg( "volume", 1.0 );
	duration			= G_GetFloatArg( "duration", 1.0 );
	explodewait		= G_GetFloatArg( "wait", 0.25 );
	randomness		= G_GetFloatArg( "random", 0.25 );
	explode_time	= 0;

	// So that we don't get deleted after we're triggered
	count = -1;

	respondto = TRIGGER_PLAYERS | TRIGGER_MONSTERS | TRIGGER_PROJECTILES;
   modelIndex( "sprites/explode.spr" );
	}
