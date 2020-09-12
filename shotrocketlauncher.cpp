//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/shotrocketlauncher.cpp           $
// $Revision:: 30                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 11/13/98 3:30p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/shotrocketlauncher.cpp                $
// 
// 30    11/13/98 3:30p Markd
// put in more precaching on weapons
// 
// 29    10/26/98 2:50p Aldie
// Fixed a bug with checking of NULL owners
// 
// 28    10/25/98 10:57p Aldie
// Fixed shotrockets for generic launcher
// 
// 27    10/24/98 12:42a Markd
// changed origins to worldorigins where appropriate
// 
// 26    10/23/98 5:38a Jimdose
// Added SpawnBlastDamage
// 
// 25    10/22/98 7:57p Markd
// put in proper pre-caching in all the classes
// 
// 24    10/20/98 8:26p Markd
// Added Attacker to DamageSurface stuff
// 
// 23    10/19/98 12:07a Jimdose
// made all code use fast checks for inheritance (no text lookups when
// possible)
// isSubclassOf no longer requires ::_classinfo()
// 
// 22    10/17/98 8:14p Jimdose
// Changed Damage to DamgeEvent
// 
// 21    9/18/98 8:14p Markd
// rewrote surface system so that surfaces are now damaged by surface name
// instead of by surfinfo
// 
// 20    9/01/98 3:05p Markd
// Rewrote explosion code
// 
// 19    8/29/98 9:46p Jimdose
// Added call info to G_Trace
// 
// 18    8/29/98 5:27p Markd
// added specialfx, replaced misc with specialfx where appropriate
// 
// 17    8/27/98 9:02p Jimdose
// Changed centroid to a variable
// 
// 16    7/26/98 8:57a Markd
// Put in auto destruct
// 
// 15    7/26/98 4:16a Aldie
// Lowered stay around time to 15 seconds
// 
// 14    7/26/98 1:48a Aldie
// Heat seekers - woohoo
// 
// 13    7/25/98 7:19p Aldie
// Client side explosion
// 
// 12    7/24/98 10:04p Aldie
// More commands for rate and speed control
// 
// 11    7/23/98 6:17p Aldie
// Updated damage system and fixed some damage related bugs.  Also put tracers
// back to the way they were, and added gib event to funcscriptmodels
// 
// 10    7/23/98 4:39p Markd
// Got rid of smoketrail
// 
// 9     7/23/98 2:32p Aldie
// Made speed of rocket a tweak cvar
// 
// 8     7/21/98 1:10p Aldie
// Added meansofdeath to obituaries
// 
// 7     7/17/98 7:57p Markd
// Added server flag SVF_USEBBOX
// 
// 6     7/14/98 5:51p Aldie
// Tweaked the shotrocket.
// 
// 5     7/10/98 2:47p Aldie
// Updated speed and attack time
// 
// 4     7/06/98 6:49p Aldie
// Fiddle with the size of the rocket.
// 
// 3     7/06/98 5:10p Aldie
// Changed the speed.
// 
// 2     7/06/98 4:09p Aldie
// First version of shotrocketlauncher
//
// DESCRIPTION:
// ShotRocketLauncher - Shoots slow moving shootable rockets

#include "g_local.h"
#include "explosion.h"
#include "shotrocketlauncher.h"
#include "rocket_turret.h"
#include "misc.h"
#include "surface.h"

CLASS_DECLARATION( Projectile, ShotRocket, NULL );

Event EV_ShotRocket_Explode( "explode" );
Event EV_ShotRocket_HeatSeek( "heatseek" );

ResponseDef ShotRocket::Responses[] =
	{
	   { &EV_Touch,				      ( Response )ShotRocket::Explode },
      { &EV_Damage,                 ( Response )ShotRocket::DamageEvent },
	   { &EV_ShotRocket_Explode,	   ( Response )ShotRocket::Explode },
  	   { &EV_ShotRocket_HeatSeek,	   ( Response )ShotRocket::HeatSeek },
		{ NULL, NULL }
	};


EXPORT_FROM_DLL void ShotRocket::DamageEvent
   (
   Event *ev
   )

   {
   Entity *other;
   Event *event;
   int damage;

   damage = ev->GetInteger(1);
   
   if (damage <= 0)
      return;

   other = ev->GetEntity(2);
   
   event = new Event(EV_ShotRocket_Explode);
   event->AddEntity(other);
   ProcessEvent(event);
   }

EXPORT_FROM_DLL void ShotRocket::Explode
	(
	Event *ev
	)

	{
	int			damg;
	Vector		v;
	Entity		*other;
   Entity      *owner;
   
	other = ev->GetEntity( 1 );
	assert( other );

   owner = G_GetEntity( this->owner );

   if ( !owner )
      owner = world;

   if ( other->isSubclassOf( Teleporter ) )
		{
		return;
		}

	if ( other == owner )
		{
		return;
		}

   stopsound( CHAN_VOICE );
	setSolidType( SOLID_NOT );
	hideModel();

	if ( HitSky() )
		{
		PostEvent( EV_Remove, 0 );
		return;
		}


   damg = 100 + ( int )G_Random( 20 );

   takedamage = DAMAGE_NO;

   if (other->takedamage)
      other->Damage( this, owner, damg, worldorigin, velocity, level.impact_trace.plane.normal, 32, 0, MOD_SHOTROCKET, -1, -1, 1.0f );

   SpawnBlastDamage( &level.impact_trace, damg, owner );

	v = velocity;
	v.normalize();
	
	// don't do radius damage to the other, because all the damage
	// was done in the impact
	v = worldorigin - v * 36;
	CreateExplosion( v, damg, 1.0f, true, this, owner, other );
	PostEvent( EV_Remove, 0.1 );
	}

float ShotRocket::Distance
	( 
	Entity *targ 
	)

   {
	Vector delta;
	
	delta = worldorigin - targ->centroid;
	return delta.length();
	}

qboolean ShotRocket::CanSee
	(
	Entity *ent
	)

	{
	Vector delta;
	Vector start;
	Vector end;
	trace_t trace;

	start = worldorigin;
	end   = ent->centroid;

	// Check if he's visible
	trace = G_Trace( start, vec_zero, vec_zero, end, this, MASK_OPAQUE, "ShotRocket::CanSee" );
	if ( trace.fraction == 1.0 || trace.ent == ent->edict )
		{
		return true;
		}

	return false;
	}

void ShotRocket::HeatSeek
   (
   Event *ev
   )

   {
   // Seek out the closest client
   
   Entity	*ent;
	edict_t	*ed;
	int		i;
	float		dist;
	float		bestdist = 99999;
   Entity	*bestent;
   Vector   delta;

   bestent = NULL;

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

		dist = Distance( ent );
		if ( ( dist < bestdist ) && CanSee( ent ) )
			{
			bestent = ent;
			bestdist = dist;
			}
		}	
	
   if (!bestent)
      {
      PostEvent( ev, FRAMETIME );
      return;
      }
   if ( bestdist < 16 )
      {
      Event * ev;
      ev = new Event( EV_ShotRocket_Explode );
      ev->AddEntity( bestent );
      PostEvent( ev, 0 );
      }

	delta = bestent->centroid - worldorigin;
   delta.normalize();
   velocity = delta * speed;
   angles = delta.toAngles();
	angles[ PITCH ] = - angles[ PITCH ];
	setAngles( angles );
   PostEvent( ev, FRAMETIME );
   }

void ShotRocket::Setup
	(
	Entity *owner,
	Vector pos,
	Vector dir
	)

	{
	Event *ev;
   RocketTurret *turret;

	this->owner = owner->entnum;
	edict->owner = owner->edict;

   if ( owner->isSubclassOf( RocketTurret ) )
      {
      turret = ( RocketTurret * )owner;
      speed = turret->speed;
      }
   else
      {
      turret = NULL;
      speed = 500;
      }

	setMoveType( MOVETYPE_FLYMISSILE );
	setSolidType( SOLID_BBOX );
	edict->clipmask = MASK_PROJECTILE;

	angles = dir.toAngles();
	angles[ PITCH ] = - angles[ PITCH ];
	setAngles( angles );

   velocity = dir * speed;

	// set missile duration
	ev = new Event( EV_ShotRocket_Explode );
	ev->AddEntity( world );
	PostEvent( ev, 15 );

	takedamage = DAMAGE_YES;
	health = 1;

   setModel( "rocket.def" );
   edict->s.effects  |= EF_ROCKET;
   edict->s.effects  |= EF_EVERYFRAME;
   edict->s.angles[ROLL] = rand() % 360;
	avelocity = "0 0 90";
	gravity = 0;
   edict->svflags |= SVF_USEBBOX;

	// setup ambient thrust
	ev = new Event( EV_RandomEntitySound );
	ev->AddString( "thrust" );
   ProcessEvent( ev );

	setSize( "-8 -8 -8", "8 8 8" );
	setOrigin( pos );
   worldorigin.copyTo(edict->s.old_origin);

   ev = new Event( EV_ShotRocket_HeatSeek );
   PostEvent( ev, FRAMETIME );
	}

CLASS_DECLARATION( Weapon, ShotRocketLauncher, "weapon_shotrocketlauncher" );

ResponseDef ShotRocketLauncher::Responses[] =
	{
	   { &EV_Weapon_Shoot,	( Response )ShotRocketLauncher::Shoot },
		{ NULL, NULL }
	};

ShotRocketLauncher::ShotRocketLauncher()
	{
	SetModels( "rlaunch.def", "view_rlaunch.def" );
	modelIndex( "rockets.def" );
	modelIndex( "rocket.def" );
	modelIndex( "sprites/blastmark.spr" );
	SetAmmo( "Rockets", 1, 5 );
	SetRank( 70, 50 );
	}

void ShotRocketLauncher::Shoot
	(
	Event *ev
	)

	{
	ShotRocket	      *rocket;
	Vector	         pos;
	Vector	         dir;
   RocketTurret      *turret;

	assert( owner );
	if ( !owner )
		{
		return;
		}

   turret = ( RocketTurret * )( Entity *)owner;

	GetMuzzlePosition( &pos, &dir );

	rocket = new ShotRocket;
	rocket->Setup( owner, pos, dir );

	MuzzleFlash( 1.0, 0.1, 0, 400, 0.6, 0.2 );
	NextAttack( turret->rate );
	}
