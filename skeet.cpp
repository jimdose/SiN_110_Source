//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/skeet.cpp                        $
// $Revision:: 24                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 10/24/98 12:42a                                                $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/skeet.cpp                             $
// 
// 24    10/24/98 12:42a Markd
// changed origins to worldorigins where appropriate
// 
// 23    10/23/98 9:58p Aldie
// Removed setsize
// 
// 22    10/22/98 5:56p Markd
// Made a bunch of global sounds local to that entity
// 
// 21    9/23/98 5:19p Markd
// Put DAMAGE_NO in killed functions of these classes
// 
// 20    9/21/98 4:57p Markd
// Added archive and unarchive functions
// 
// 19    8/18/98 11:08p Markd
// Added new Alias System
// 
// 18    6/24/98 12:39p Markd
// Added default tesselation percentage
// 
// 17    6/18/98 9:13p Jimdose
// Removed posting of uninitialized event from Pigeon::Killed
// 
// 16    6/18/98 2:00p Markd
// rewrote tesselation code
// 
// 15    6/15/98 10:38a Aldie
// Removed ref to explosion
// 
// 14    5/24/98 4:48p Jimdose
// Made char *'s const
// 
// 13    5/24/98 1:04a Jimdose
// Added sound events for ai
// 
// 12    5/19/98 4:26p Aldie
// Fixed pigeon death
// 
// 11    5/17/98 8:10p Aldie
// Fixed origin and sound.
// 
// 10    5/15/98 1:02p Aldie
// Moved header to .h
// 
// 9     5/09/98 7:11p Markd
// Removed sound parameter from tesselate command
// 
// 8     5/05/98 8:37p Aldie
// Removed lights from skeet.
// 
// 7     5/03/98 4:33p Jimdose
// Changed Vector class
// 
// 6     5/01/98 11:09a Markd
// Added sound to tesselation event
// 
// 5     4/14/98 6:56p Markd
// Added thickness to tesselation and removed explosion
// 
// 4     4/06/98 7:10p Aldie
// Added zooming for SniperRifle
// 
// 3     4/05/98 11:04p Aldie
// Added tesselation.
// 
// 2     4/04/98 4:19p Aldie
// First version of skeet mod.
//
// DESCRIPTION: Skeet Entity
// 


#include "g_local.h"
#include "item.h"
#include "rocketlauncher.h"
#include "worldspawn.h"
#include "skeet.h"
#include "scriptmaster.h"

CLASS_DECLARATION( Object, Pigeon, "pigeon" );

Event EV_Pigeon_Remove( "pigeonremove" );

ResponseDef Pigeon::Responses[] =
	{
      { &EV_Touch,	         			( Response )Pigeon::RemovePigeon },
      { &EV_Killed,					      ( Response )Pigeon::Killed },
		{ NULL, NULL }
	};

void Pigeon::RemovePigeon(Event *ev)
   {
	setSolidType( SOLID_NOT );
	hideModel();
   PostEvent( EV_Remove, 0 );
   }

void Pigeon::Killed(Event *ev)
   {
	Entity * attacker;
   Vector dir;

   takedamage = DAMAGE_NO;
   setSolidType( SOLID_NOT );
	hideModel();
    
   attacker		= ev->GetEntity( 1 );
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

	ProcessEvent( EV_BreakingSound );
   RandomSound("pig_death",1);

   Director.DeathMessage( name.c_str() );
   PostEvent( EV_Remove, 0 );
   }

void Pigeon::Setup
	(
	Entity *owner,
	Vector pos,
	Vector dir,
   float pspeed,
   float pgrav,
	float pduration,
   const char *pigeon_name
   )
	{
	Event *ev;
   
	this->owner = owner->entnum;
	edict->owner = owner->edict;

   name = str( pigeon_name );
	setMoveType( MOVETYPE_BOUNCE );
	setSolidType( SOLID_BBOX );
	edict->clipmask = MASK_SHOT;

   maxspeed       = 500;
   acceleration   = 150;
	speed          = pspeed;
   velocity       = dir * speed;
   health         = 1;
   gravity        = pgrav;
   takedamage		= DAMAGE_YES;
   
	ev = new Event( EV_Remove );
	ev->AddEntity( world );
	PostEvent( ev, pduration );
   
   setModel("skeet.def");
   setSize( mins, maxs );
	setOrigin( pos );
   worldorigin.copyTo(edict->s.old_origin);
	}

CLASS_DECLARATION( Entity, SkeetLauncher, "skeetlauncher" );

Event EV_SkeetLauncher_Launch( "launch" );
Event EV_SkeetLauncher_SetXdir( "setXdir" );
Event EV_SkeetLauncher_SetYdir( "setYdir" );
Event EV_SkeetLauncher_SetZdir( "setZdir" );
Event EV_SkeetLauncher_SetSpeed( "setSpeed" );
Event EV_SkeetLauncher_SetGravity( "setGravity" );
Event EV_SkeetLauncher_SetDuration( "setDuration" );
Event EV_SkeetLauncher_SetSpeedVar( "setSpeedVar" );
Event EV_SkeetLauncher_SetXvar( "setXvar" );
Event EV_SkeetLauncher_SetYvar( "setYvar" );
Event EV_SkeetLauncher_SetZvar( "setZvar" );

ResponseDef SkeetLauncher::Responses[] =
	{
      { &EV_SkeetLauncher_Launch,				( Response )SkeetLauncher::Launch },
      { &EV_SkeetLauncher_SetXdir,				( Response )SkeetLauncher::SetXdir },
      { &EV_SkeetLauncher_SetYdir,				( Response )SkeetLauncher::SetYdir },
      { &EV_SkeetLauncher_SetZdir,				( Response )SkeetLauncher::SetZdir },
      { &EV_SkeetLauncher_SetSpeed,				( Response )SkeetLauncher::SetSpeed },
      { &EV_SkeetLauncher_SetGravity,	   	( Response )SkeetLauncher::SetGravity },
      { &EV_SkeetLauncher_SetDuration,			( Response )SkeetLauncher::SetDuration },
      { &EV_SkeetLauncher_SetSpeedVar,       ( Response )SkeetLauncher::SetSpeedVar },
      { &EV_SkeetLauncher_SetXvar,           ( Response )SkeetLauncher::SetXvar },
      { &EV_SkeetLauncher_SetYvar,           ( Response )SkeetLauncher::SetYvar },
      { &EV_SkeetLauncher_SetZvar,           ( Response )SkeetLauncher::SetZvar },
		{ NULL, NULL }
	};

SkeetLauncher::SkeetLauncher( )
   {
   showModel();
   setSolidType( SOLID_BSP );
   speed_var = 0;
   x_var = 0;
   y_var = 0;
   z_var = 0;
   }

void SkeetLauncher::SetXdir( Event *ev )
   {
   launchAngle.x = ev->GetFloat( 1 );
   }

void SkeetLauncher::SetYdir( Event *ev )
   {
   launchAngle.y = ev->GetFloat(1);
   }

void SkeetLauncher::SetZdir( Event *ev )
   {
   launchAngle.z = ev->GetFloat(1);
   }

void SkeetLauncher::SetSpeed( Event *ev )
   {
   pspeed = ev->GetFloat(1);
   }

void SkeetLauncher::SetGravity( Event *ev )
   {
   pgravity = ev->GetFloat(1);
   }

void SkeetLauncher::SetDuration( Event *ev )
   {
   pduration = ev->GetFloat(1);
   }

void SkeetLauncher::SetSpeedVar( Event *ev )
   {
   speed_var = ev->GetFloat(1);
   }

void SkeetLauncher::SetXvar( Event *ev )
   {
   x_var = ev->GetFloat(1);
   }

void SkeetLauncher::SetYvar( Event *ev )
   {
   y_var = ev->GetFloat(1);
   }

void SkeetLauncher::SetZvar( Event *ev )
   {
   z_var = ev->GetFloat(1);
   }

void SkeetLauncher::Launch(Event *ev)
   {
   Pigeon		*pigeon;
   Vector		start;
   Vector		end;
   float			sp;
	Vector		ang;
   const char	*name;

   pigeon = new Pigeon;

   name =  ev->GetString(1);
   ang.x = launchAngle.x + G_CRandom(x_var);
   ang.y = launchAngle.y + G_CRandom(y_var);
   ang.z = launchAngle.z + G_CRandom(z_var);
   sp = pspeed + G_CRandom(speed_var);
   pigeon->Setup( this, worldorigin, ang.normalize(), sp, pgravity, pduration, name);
   }

