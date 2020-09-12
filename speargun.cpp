//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/speargun.cpp                     $
// $Revision:: 42                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 11/15/98 11:32p                                                $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/speargun.cpp                          $
// 
// 42    11/15/98 11:32p Markd
// fixed spear gun stuff
// 
// 41    11/13/98 3:30p Markd
// put in more precaching on weapons
// 
// 40    11/12/98 11:31p Jimdose
// changed impact_bodyimpact to impact_goryimpact
// 
// 39    10/24/98 12:42a Markd
// changed origins to worldorigins where appropriate
// 
// 38    10/22/98 9:40p Markd
// Changed damage on spear
// 
// 37    10/22/98 5:56p Markd
// Made a bunch of global sounds local to that entity
// 
// 36    10/22/98 12:19a Jimdose
// Made the spears not go through walls if very close to a wall
// 
// 35    10/21/98 10:40p Aldie
// Added spears ammotype
// 
// 34    10/19/98 12:07a Jimdose
// made all code use fast checks for inheritance (no text lookups when
// possible)
// isSubclassOf no longer requires ::_classinfo()
// 
// 33    10/07/98 12:14a Aldie
// Took out some more bubbles
// 
// 32    10/06/98 10:51p Aldie
// Moved bubbletrail to client
// 
// 31    10/05/98 10:32p Markd
// Set minimum attack range
// 
// 30    10/03/98 7:34p Markd
// Increased damage of speargun
// 
// 29    8/29/98 5:27p Markd
// added specialfx, replaced misc with specialfx where appropriate
// 
// 28    8/18/98 11:08p Markd
// Added new Alias System
// 
// 27    8/01/98 3:03p Aldie
// Client side muzzle flash (dynamic light)
// 
// 26    7/25/98 7:10p Markd
// Put in EV_Removes for demo
// 
// 25    7/23/98 6:17p Aldie
// Updated damage system and fixed some damage related bugs.  Also put tracers
// back to the way they were, and added gib event to funcscriptmodels
// 
// 24    7/22/98 9:57p Markd
// Defined weapon type
// 
// 23    7/21/98 1:10p Aldie
// Added meansofdeath to obituaries
// 
// 22    6/19/98 9:30p Jimdose
// Moved gun orientation code to Weapon
// 
// 21    6/15/98 8:02p Markd
// made spears stick in guys
// 
// 20    6/10/98 2:10p Aldie
// Updated damage function.
// 
// 19    5/25/98 5:39p Markd
// Changed spawn sparks call
// 
// 18    5/11/98 3:20p Markd
// Made impact sounds for spear
// 
// 17    5/05/98 8:37p Aldie
// Fixed oldorigin.
// 
// 16    5/03/98 8:12p Markd
// Changed sparks call to SpawnSparks call
// 
// 15    4/20/98 1:57p Markd
// SINED decelration is now in def file
// 
// 14    4/18/98 3:14p Markd
// Changed view weapon naming convention
// 
// 13    4/18/98 2:34p Jimdose
// Made spear check for FL_BLOOD and FL_SPARKS
// 
// 12    4/10/98 4:53p Jimdose
// Changed timing on bubble spawning
// 
// 11    4/07/98 9:48p Jimdose
// spears work a little better.
// 
// 10    4/07/98 6:43p Jimdose
// Rewrote weapon code.
// Added order to rank
// 
// 9     4/04/98 6:07p Jimdose
// Created file
// 
// DESCRIPTION:
// Fires a spear.  Used by Seabonites.
// 

#include "g_local.h"
#include "SpearGun.h"
#include "worldspawn.h"
#include "specialfx.h"

CLASS_DECLARATION( Projectile, Spear, NULL );

ResponseDef Spear::Responses[] =
	{
	   { &EV_Touch,				( Response )Spear::Hit },
		{ NULL, NULL }
	};

EXPORT_FROM_DLL void Spear::Hit
	(
	Event *ev
	)

	{
	Entity *other;
	Vector org;
   int damg;

	other = ev->GetEntity( 1 );

	if ( other->isSubclassOf( Teleporter ) )
		{
		return;
		}

	if ( other->entnum == owner )
		{
		return;
		}

	setSolidType( SOLID_NOT );

	if ( HitSky() || ( velocity == vec_zero ) )
		{
		PostEvent( EV_Remove, 0 );
		return;
		}

   RandomAnimate( "idle", NULL );

	org = worldorigin + velocity * 0.01f;
	if ( other->takedamage )
      {
		if ( other->flags & FL_BLOOD )
			{
			SpawnBlood( org, level.impact_trace.plane.normal, 10 );
			}

   	damg = 30 + ( int )G_Random( 50 );
		other->Damage( this, G_GetEntity( owner ), damg,  
                     level.impact_trace.endpos, velocity, 
                     level.impact_trace.plane.normal, 10, 0, MOD_SPEARGUN, -1, -1, 1.0f );
		//FIXME
		// do this based on the surface flag
		RandomGlobalSound( "impact_goryimpact", 1 );
      if ( level.impact_trace.intersect.valid )
         {
         vec3_t mins, maxs;

   		setMoveType( MOVETYPE_NONE );
         gi.CalculateBounds( edict->s.modelindex, edict->s.scale, mins, maxs );
         origin = "0 0 0";
         origin[0] = (Vector(maxs) - Vector(mins)).length() * 0.3f;
         setOrigin( origin );
         velocity = "0 0 0";
         attach
            ( 
            other->entnum, 
            level.impact_trace.intersect.group,
            level.impact_trace.intersect.tri_num,
            vec_zero
            );
      	CancelEventsOfType( EV_Remove );
   		PostEvent( EV_FadeOut, 45 );
         return;
         }
      }
	else
		{
		RandomSound( "spear_impact", 1 );
		}

	if ( other->flags & FL_SPARKS )
      SpawnSparks( org, level.impact_trace.plane.normal, 4 );

	if ( other->getSolidType() == SOLID_BSP )
		{
		// Stick it into the wall
		velocity = "0 0 0";
		//bind( other );
		setMoveType( MOVETYPE_NONE );
		PostEvent( EV_FadeOut, 10 );
		}
	else
		{
		PostEvent( EV_Remove, 0 );
		}
	}

EXPORT_FROM_DLL void Spear::Setup
	(
	Entity *owner,
	Vector pos,
	Vector dir
	)

	{
   trace_t trace;

	this->owner = owner->entnum;
	edict->owner = owner->edict;

	setMoveType( MOVETYPE_FLYMISSILE );
	setSolidType( SOLID_BBOX );
	edict->clipmask = MASK_SHOT;

	// set missile speed
	velocity = dir;
	velocity.normalize();
	velocity *= 500;

	angles = dir.toAngles();
	angles[ PITCH ] = - angles[ PITCH ];
	setAngles( angles );

	setModel( "spear.def" );
   RandomAnimate( "fly", NULL );

	setSize( "-2 -2 -2", "2 2 2" );
   trace = G_Trace( pos - Vector( orientation[ 0 ] ) * 48, mins, maxs, pos, owner, MASK_SHOT, "Spear::Setup" );
	setOrigin( trace.endpos );
   worldorigin.copyTo(edict->s.old_origin);

	PostEvent( EV_Remove, 5 );
	}

CLASS_DECLARATION( Weapon, SpearGun, "weapon_speargun" );

ResponseDef SpearGun::Responses[] =
	{
	   { &EV_Weapon_Shoot,	( Response )SpearGun::Shoot },
		{ NULL, NULL }
	};

SpearGun::SpearGun()
	{
#ifdef SIN_DEMO
   PostEvent( EV_Remove, 0 );
   return;
#endif
	SetModels( "speargun.def", "view_spgun.def" );
	modelIndex( "spear.def" );
	modelIndex( "spear_ammo.def" );
	SetAmmo( "Spears", 1, 10 );
	SetRank( 99, 70 );
   SetType( WEAPON_2HANDED_LO );
	SetMinRange( 100 );
	}

void SpearGun::Shoot
	(
	Event *ev
	)

	{
	Vector	pos;
	Spear		*spear;
	Vector	dir;

	assert( owner );
	if ( !owner )
		{
		return;
		}

	GetMuzzlePosition( &pos, &dir );

	spear = new Spear;
	spear->Setup( owner, pos, dir );

	NextAttack( 0.8 );
	}
