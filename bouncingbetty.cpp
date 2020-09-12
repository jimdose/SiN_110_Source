//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/bouncingbetty.cpp                $
// $Revision:: 24                                                             $
//   $Author:: Jimdose                                                        $
//     $Date:: 11/12/98 11:30p                                                $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/bouncingbetty.cpp                     $
// 
// 24    11/12/98 11:30p Jimdose
// changed impact_bodyimpact to impact_goryimpact
// 
// 23    10/26/98 2:17p Aldie
// Upped the damage
// 
// 22    10/24/98 12:50a Aldie
// Made betty launcher take damage
// 
// 21    10/22/98 7:57p Markd
// put in proper pre-caching in all the classes
// 
// 20    10/07/98 8:04p Aldie
// Move bubbles to client
// 
// 19    9/01/98 3:05p Markd
// Rewrote explosion code
// 
// 18    8/29/98 5:27p Markd
// added specialfx, replaced misc with specialfx where appropriate
// 
// 17    8/18/98 11:08p Markd
// Added new Alias System
// 
// 16    7/23/98 6:17p Aldie
// Updated damage system and fixed some damage related bugs.  Also put tracers
// back to the way they were, and added gib event to funcscriptmodels
// 
// 15    7/21/98 1:10p Aldie
// Added meansofdeath to obituaries
// 
// 14    7/09/98 12:09a Jimdose
// explode no longer scales the explosion (explosion creates a temp entity now)
// 
// 13    6/10/98 2:10p Aldie
// Updated damage function.
// 
// 12    5/11/98 2:19p Markd
// Fixed randomsound stuff
// 
// 11    5/03/98 4:30p Jimdose
// Changed Vector class.  No longer includes PointsTo
// 
// 10    4/18/98 5:45p Markd
// Removed SINED calls, because they are now in DEF file format
// 
// 9     4/10/98 4:54p Jimdose
// made bubbles work
// 
// 8     4/10/98 2:36a Jimdose
// Works with Q2
// 
// 7     4/08/98 4:22p Jimdose
// Getting ready to conver to Q2
// 
// 5     12/15/97 3:33p Jimdose
// BettyLauncher first switches to the betty model before going to the iris
// model in order to precache the sounds that the betty model uses.
// 
// 4     12/15/97 1:34a Jimdose
// Increased splash damage from betty exploding
// 
// 3     12/14/97 5:48p Jimdose
// Finished basic behaviour code
// 
// 2     12/13/97 4:43p Jimdose
// Created file
//
// DESCRIPTION:
// 

#include "g_local.h"
#include "bouncingbetty.h"
#include "explosion.h"
#include "specialfx.h"

Event EV_Betty_CheckVicinity( "checkvicinity" );
Event EV_Betty_Launch( "launch" );
Event EV_Betty_AttackFinished( "attack_finished" );
Event EV_Betty_Fire( "fire" );
Event EV_Betty_Detonate( "detonate" );
Event EV_Betty_Explode( "explode" );
Event EV_BettySpike_Bubbles( "bubble" );

CLASS_DECLARATION( Entity, BettyLauncher, "trap_bouncingbetty" );

ResponseDef BettyLauncher::Responses[] =
	{
		{ &EV_Betty_CheckVicinity,		( Response )BettyLauncher::CheckVicinity },
		{ &EV_Activate,					( Response )BettyLauncher::Launch },
		{ &EV_Betty_Launch,				( Response )BettyLauncher::Launch },
		{ &EV_Betty_AttackFinished,	( Response )BettyLauncher::AttackFinished },
		{ &EV_Betty_Fire,					( Response )BettyLauncher::ReleaseBetty },
		{ &EV_Killed,  					( Response )BettyLauncher::Killed },
		{ NULL, NULL }
	};

BettyLauncher::BettyLauncher
   (
   )

	{
	setModel( "iris.def" );
	modelIndex( "betty.def" );
	modelIndex( "bettyspike.def" );
	RandomAnimate( "idle", NULL );
	
	setSize( "-16 -16 0", "16 16 2" );

	setMoveType( MOVETYPE_NONE );
	setSolidType( SOLID_BBOX );
   health = G_GetFloatArg( "health", 200 );

   takedamage = DAMAGE_YES;
   flags |= FL_SPARKS;

	firing = false;
	activator = 0;

	if ( !Targeted() )
		{
		PostEvent( EV_Betty_CheckVicinity, 0.3f );
		}
	}

void BettyLauncher::Killed
   (
   Event *ev
   )

   {
   takedamage = DAMAGE_NO;
	CreateExplosion( worldorigin, 30, 0.5, true, this, this, this );
   PostEvent( EV_Remove, 0 );
   }

qboolean	BettyLauncher::inRange
	( 
	Entity *ent 
	)

	{
	Vector delta;
	float dist;

	delta = worldorigin - ent->worldorigin;
	dist = delta.length();

	if ( dist > BOUNCINGBETTY_RANGE )
		{
		return false;
		}
	return true;
	}

void BettyLauncher::CheckVicinity
	(
	Event *ev
	)

	{
   Entity	*ent;
	edict_t	*ed;
	int		i;
	Event		*e;

	if ( firing )
		{
		return;
		}

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

		if ( inRange( ent ) )
			{
			e = new Event( EV_Betty_Launch );
			e->AddEntity( ent );
			ProcessEvent( e );

			// wait a couple seconds before checking again
			PostEvent( EV_Betty_CheckVicinity, 2 );
			return;
			}
		}

	PostEvent( EV_Betty_CheckVicinity, 0.3f );
	}

void BettyLauncher::Launch
	(
	Event *ev
	)

	{
	if ( !firing )
		{
		firing = true;
		activator = ( int )ev->GetEntity( 1 )->entnum;
		RandomAnimate( "open", NULL );
		}
	}

void BettyLauncher::AttackFinished
	(
	Event *ev
	)

	{
	firing = false;
	}

void BettyLauncher::ReleaseBetty
	(
	Event *ev
	)

	{
	BouncingBetty *betty;

	betty = new BouncingBetty;
	betty->Launch( worldorigin, activator );
	activator = 0;
   }

CLASS_DECLARATION( Entity, BouncingBetty, NULL );

ResponseDef BouncingBetty::Responses[] =
	{
		{ &EV_Betty_Detonate,			( Response )BouncingBetty::Detonate },
		{ &EV_Betty_Explode,				( Response )BouncingBetty::Explode },
		{ NULL, NULL }
	};

BouncingBetty::BouncingBetty()
	{
	setModel( "betty.def" );
	setSize( "-4 -4 0", "4 4 8" );

	setMoveType( MOVETYPE_BOUNCE );
	setSolidType( SOLID_BBOX );
	activator = 0;
	}

void BouncingBetty::Launch
	(
	Vector pos,
	int activatorEnt
	)

	{
	activator = activatorEnt;

	setOrigin( pos );
	worldorigin.copyTo( edict->s.old_origin );
	velocity = "0 0 400";
	avelocity = "0 180 0";
	watertype = gi.pointcontents( worldorigin.vec3() );

	RandomAnimate( "detonate", NULL );			
	}

void BouncingBetty::Detonate
	(
	Event *ev
	)

	{
	RandomAnimate( "detonate", NULL );
	}

void BouncingBetty::Explode
	(
	Event *ev
	)

	{
	BettySpike	*spike;
	Entity		*ent;
	Vector		vec;
	Vector		v;
	int			i;
	float			r;

	ent = G_GetEntity( activator );

   CreateExplosion( worldorigin, 150, 1.0f, true, this, ent, this );

	vec = Vector( 25, 0, 0 );

	r = G_Random( 360 );
	for( i = 0; i < 12; i++ )
		{
		vec[ 1 ] = r;
		vec.AngleVectors( &v, NULL, NULL );
		
		spike = new BettySpike;
		spike->Setup( worldorigin + v * 8, v );

		r += 360.0 / 12.0;
		}

	PostEvent( EV_Remove, 0 );
   }

CLASS_DECLARATION( Entity, BettySpike, NULL );

ResponseDef BettySpike::Responses[] =
	{
		{ &EV_Touch,					( Response )BettySpike::SpikeTouch },
		{ NULL, NULL }
	};

EXPORT_FROM_DLL void BettySpike::SpikeTouch
	(
	Event *ev
	)

	{
	Entity *other;
   int kick = 10;

	if ( HitSky() )
		{
		PostEvent( EV_Remove, 0 );
		return;
		}

	other = ev->GetEntity( 1 );
	assert( other );

	if ( other->health )
      {     
      other->Damage( this, this, 10, worldorigin, velocity, level.impact_trace.plane.normal, kick, 0, MOD_BETTYSPIKE, -1, -1, 1.0f);
		RandomGlobalSound( "impact_goryimpact", 1 );
      }
	else
		{
		RandomGlobalSound( "impact_bulletcase", 0.3 );
		}

	PostEvent( EV_Remove, 0 );
	}

EXPORT_FROM_DLL void BettySpike::Setup
	(
	Vector pos,
	Vector dir
	)

	{
	setModel( "bettyspike.def" );
	setMoveType( MOVETYPE_FLYMISSILE );
	setSolidType( SOLID_BBOX );
	setSize( "0 0 0", "0 0 0" );
	setOrigin( pos );
	worldorigin.copyTo( edict->s.old_origin );
	watertype = gi.pointcontents( worldorigin.vec3() );

	// set missile speed
	velocity = dir;
	velocity.normalize();
	velocity *= 500 + G_CRandom( 100 );

	angles = dir.toAngles();
	angles[ PITCH ] = - angles[ PITCH ];
	setAngles( angles );

	PostEvent( EV_Remove, 5 );
	}
