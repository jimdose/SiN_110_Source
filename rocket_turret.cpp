//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/rocket_turret.cpp                $
// $Revision:: 14                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 9/22/98 4:56p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/rocket_turret.cpp                     $
// 
// 14    9/22/98 4:56p Aldie
// Moved lagtime check right before firing
// 
// 13    9/20/98 9:10p Aldie
// Added lagtime
// 
// 12    9/19/98 6:12p Aldie
// Made wakeupdistance and firingdistance spawn args
// 
// 11    8/27/98 9:02p Jimdose
// Changed centroid to a variable
// 
// 10    7/24/98 10:04p Aldie
// More commands to control rockets
// 
// 9     7/23/98 2:32p Aldie
// Made speed of rocket a tweak cvar
// 
// 8     7/14/98 5:50p Aldie
// Tweaked the aiming of the turret
// 
// 7     7/10/98 5:38p Aldie
// Updated turret damage
// 
// 6     7/10/98 2:49p Aldie
// Put in some basic rocket shooting prediction.
// 
// 5     7/09/98 10:40p Aldie
// Updated to new model
// 
// 4     7/07/98 4:10p Aldie
// Updated to new class hierarchy
// 
// 3     7/06/98 5:10p Aldie
// Tweaking behavior and changed modelname
// 
// 2     7/06/98 4:08p Aldie
// First version of rocket_turret
//
// DESCRIPTION:
// Rocket Turret - Shoots slow moving shootable rockets at the player

#include "turret.h"
#include "rocket_turret.h"
#include "shotrocketlauncher.h"

CLASS_DECLARATION( Turret, RocketTurret, "trap_rocketturret" );

Event EV_RocketTurret_Rate( "rocketrate" );
Event EV_RocketTurret_Speed( "rocketspeed" );

ResponseDef RocketTurret::Responses[] =
	{
      { &EV_RocketTurret_Rate,         ( Response )RocketTurret::SetRate },
      { &EV_RocketTurret_Speed,        ( Response )RocketTurret::SetSpeed },
      { NULL, NULL }
	};

RocketTurret::RocketTurret
	(
	void
	)

	{
   Entity *base;

	setModel( "launcher_top.def" );
	RandomAnimate( "down_idle", NULL );
	neworientation = angles.yaw();
   setMoveType( MOVETYPE_NONE );
	setSolidType( SOLID_BBOX );
   flags |= FL_SPARKS;
   enemy_oldorigin = vec_zero;
   edict->svflags |= SVF_USEBBOX;

   base = new Entity;
   base->setModel( "launcher_base.def" );
	base->setMoveType( MOVETYPE_NONE );
	base->setSolidType( SOLID_BBOX );
   base->setOrigin( worldorigin );

	health			= 150;
	takedamage		= DAMAGE_YES;
   wakeupdistance = G_GetFloatArg( "wakeupdistance", 1950 );
   firingdistance = G_GetFloatArg( "firingdistance", 2000 );
   rate           = 8.0;
   speed          = 300;
	}

void RocketTurret::Seek
	(
	Event *ev
	)

	{
	Entity	*ent;
	Vector	v;
	Vector	s;
	int		range;
	Vector	f;
	Vector   enemy_velocity;

   active = true;
	ent = NULL;
	if ( enemy )
		{
		ent = G_GetEntity( enemy );
		if ( ( !ent ) || ( ent->health <= 0 ) || ( ent->flags & FL_NOTARGET ) || ( ent == this ) )
			{
			enemy = 0;
         enemy_oldorigin = vec_zero;
			ent = NULL;
			}
		else
			{
         float delta_t;

         // Have an enemy locked on, get the range and calculate velocity
         // based on the old origin and the time difference since last locked
         // onto him.
			range = Range( Distance( ent ) );
         
         delta_t = level.time - lastSightTime;

         if ( delta_t )
            enemy_velocity = ( ent->worldorigin - enemy_oldorigin ) * (1.0f / delta_t);
         else
            enemy_velocity = vec_zero;
         // Update the enemy's origin and the time we last saw him
         enemy_oldorigin = ent->worldorigin;
			}
		}

	if ( ( lastSightTime ) && ( ( lastSightTime + patience ) < level.time ) )
		{
		ProcessEvent( EV_Turret_GoDown );
		}

	if ( !enemy )
		{
		FindTarget();
		PostEvent( EV_Turret_Seek, FRAMETIME * 2 );
		return;
		}

	if ( ( range != TURRET_OUTOFRANGE ) && ent && CanSee( ent ) )
		{
      Vector targ, src, d;

      float dist;

      lastSightTime = level.time;

		// Get distance and orientation to target
      targ  = ent->centroid;
      currentWeapon->GetMuzzlePosition(&src);
      d     = targ-src;
      dist  = d.length();

      targ += ( enemy_velocity * (dist/sv_rocketspeed->value));

      v = targ - src;
      v.normalize();

		new_orientation = v.toAngles();
		}
   
   if ( ( angles[ YAW ] != new_orientation[ YAW ] ) && !turning)
      {
      Event *event;
      event = new Event( EV_Turret_Turn );
      event->AddVector( new_orientation );
      ProcessEvent( event );
      }

	if ( range == TURRET_FIRERANGE ) 
		{
      // Allow some freetime to let player get somewhere before turret fires on him
      if ( level.time < firetime )
         {
    	   PostEvent( EV_Turret_Seek, FRAMETIME );
         return;
         }
      ProcessEvent( EV_Turret_Attack );
      }

	PostEvent( EV_Turret_Seek, FRAMETIME );
	}

void RocketTurret::Turn
   (
   Event *ev
   )

   {
   Vector new_angle = ev->GetVector( 1 );

   if ( angles[ YAW ] != new_angle[ YAW ] )
		{
		turntime = level.time + 0.2;
		turning = true;
		}
	else if ( turntime < level.time )
		{
		turning = false;
      angles[ PITCH ] = -new_angle[ PITCH ];
		return;
		}

   angles[ PITCH ] = -new_angle[ PITCH ];
   angles[ YAW ]   = AdjustAngle( 32, angles[ YAW ], new_angle[ YAW ] );	
	setAngles( angles );
	PostEvent( ev, FRAMETIME );
   }

void RocketTurret::SetRate
   (
   Event *ev
   )

   {
   rate = ev->GetFloat( 1 );
   }

void RocketTurret::SetSpeed
   (
   Event *ev
   )

   {
   speed = ev->GetFloat( 1 );
   }