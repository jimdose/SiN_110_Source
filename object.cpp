//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/object.cpp                       $
// $Revision:: 48                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 11/13/98 10:00p                                                $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/object.cpp                            $
// 
// 48    11/13/98 10:00p Markd
// increased damage of throwobjects
// 
// 47    10/24/98 12:42a Markd
// changed origins to worldorigins where appropriate
// 
// 46    10/19/98 11:50p Aldie
// Force objects to animate at least one frame, so the edict will have the
// proper value in them.
// 
// 45    10/19/98 12:07a Jimdose
// made all code use fast checks for inheritance (no text lookups when
// possible)
// isSubclassOf no longer requires ::_classinfo()
// 
// 44    9/23/98 5:19p Markd
// Put DAMAGE_NO in killed functions of these classes
// 
// 43    9/22/98 5:19p Markd
// Put in new consolidated gib function
// 
// 42    9/22/98 3:21p Markd
// put in parentmode lockout for blood and gibs
// 
// 41    9/15/98 6:37p Markd
// Added RotatedBounds flag support
// 
// 40    9/01/98 3:05p Markd
// Rewrote explosion code
// 
// 39    8/29/98 7:16p Markd
// Added FireBarrel
// 
// 38    8/29/98 5:27p Markd
// added specialfx, replaced misc with specialfx where appropriate
// 
// 37    8/09/98 6:18p Markd
// put in random yaw
// 
// 36    8/09/98 5:50p Markd
// Rewrote ThrowObjects pickup and throw
// 
// 35    8/08/98 8:47p Markd
// incremental check-in for building purposes
// 
// 34    7/21/98 10:05p Markd
// Added explosion stuff to when things die
// 
// 33    7/12/98 5:39p Markd
// fixed bug with animating world objects
// 
// 32    7/09/98 12:08a Jimdose
// Changed process of remove to a post
// 
// 31    6/24/98 12:39p Markd
// Added default tesselation percentage
// 
// 30    6/18/98 2:00p Markd
// rewrote tesselation code
// 
// 29    6/13/98 7:32p Markd
// Put in default tesselation of 10 thick
// 
// 28    6/10/98 4:42p Markd
// Only tesselate 75% when killed
// 
// 27    5/26/98 1:29a Markd
// fixed bounding box issues
// 
// 26    5/25/98 11:32p Markd
// fixed bug with objects being not_shootable but still blocking bullets
// 
// 25    5/25/98 1:08a Markd
// Fixed killtargets on objects
// 
// 24    5/24/98 2:47p Markd
// Made char *'s into const char *'s
// 
// 23    5/24/98 1:03a Jimdose
// Added sound events for ai
// 
// 22    5/20/98 1:33p Markd
// Added target and killtarget behavior when dead
// 
// 21    5/20/98 11:11a Markd
// removed char * dependency
// 
// 20    5/19/98 9:48p Markd
// fixed object spawning with new spawn flags
// 
// 19    5/13/98 6:19p Markd
// Rotate mins and maxs now in constructor
// 
// 18    5/09/98 7:11p Markd
// Removed sound parameter from tesselate command
// 
// 17    5/08/98 7:01p Markd
// Added FL_DARKEN support
// 
// 16    5/03/98 8:10p Markd
// Took out set bounds code, it is already done in Entity
// 
// 15    5/03/98 4:36p Jimdose
// Changed Vector class
// 
// 14    5/01/98 11:09a Markd
// Added sound to tesselation event
// 
// 13    4/25/98 5:09p Markd
// Added up and down support for angles
// 
// 12    4/20/98 11:01a Markd
// Fixed client side prediction of non-solid shootables
// 
// 11    4/14/98 6:56p Markd
// Added thickness to tesselation
// 
// 10    4/10/98 1:23a Markd
// Got rid of damage function, added FL_TESSELATE and other flags
// 
// 9     4/09/98 1:40p Markd
// Added in CONTENTS_SHOOTABLE stuff
// 
// 8     4/07/98 8:00p Markd
// removed defhandle, changed all SINMDL calls to modelindex calls, removed
// SINMDL prefix
// 
// 7     4/06/98 6:52p Markd
// Put in anim support and skin support
// 
// 6     4/06/98 5:46p Jimdose
// Added "angles" spawn values
// 
// 5     4/06/98 12:02a Markd
// Tweaked damage stuff
// 
// 4     4/05/98 10:54p Markd
// Added Damage event
// 
// 3     4/05/98 10:42p Markd
// Moved tesselate to Entity
// 
// 2     4/05/98 9:41p Markd
// Initial
// 
// 1     4/05/98 9:03p Markd
// 
// 2     4/04/98 4:19p Aldie
// First version of skeet mod.
//
// DESCRIPTION: Skeet Entity
// 


#include "g_local.h"
#include "object.h"
#include "misc.h"
#include "explosion.h"
#include "gibs.h"
#include "specialfx.h"


CLASS_DECLARATION( Entity, Object, "object" );

ResponseDef Object::Responses[] =
	{
      { &EV_Killed,					      ( Response )Object::Killed },
		{ NULL, NULL }
	};

Object::Object()
	{
   const char * animname;
   const char * skinname;
   Vector defangles;

	SetKillTarget( G_GetSpawnArg( "killtarget" ) );
  	setSolidType( SOLID_BBOX );
   // if it isn't solid, lets still make it shootable
	if (spawnflags & 1)
      {
      if ( !(spawnflags & 2) )
         {
   	   edict->svflags |= SVF_SHOOTABLE;
         setOrigin( origin );
         }
      else
        	setSolidType( SOLID_NOT );
      }
   if (!health)
      {
      health = (maxs-mins).length();
      max_health = health;
      }
   takedamage = DAMAGE_YES;
   if ( spawnflags & 2 )
      {
      takedamage = DAMAGE_NO;
      }

   // angles
   defangles = Vector( 0, G_GetFloatArg( "angle", 0 ), 0 );
   if (defangles.y == -1)
      {
      defangles = Vector( -90, 0, 0 );
      }
   else if (defangles.y == -2)
      {
      defangles = Vector( 90, 0, 0 );
      }
   angles = G_GetVectorArg( "angles", defangles );
	setAngles( angles );
   setOrigin( origin );

   //
   // we want the bounds of this model auto-rotated
   //
   flags |= FL_ROTATEDBOUNDS;

   //
   // rotate the mins and maxs for the model
   //
   setSize( mins, maxs );

   animname = G_GetSpawnArg( "anim" );
   if ( animname && strlen(animname) && gi.IsModel( edict->s.modelindex ) )
      {
      int animnum;

      animnum = gi.Anim_NumForName( edict->s.modelindex, animname );
      if (animnum >= 0)
         NextAnim( animnum );
      
      // Sets up the edict
      AnimateFrame();
      StopAnimating();
      // 
      // we only want to start animating if it was explicitly defined in the def file
      //
      //StartAnimating();
      }
   skinname = G_GetSpawnArg( "skin" );
   if ( skinname && strlen(skinname) && gi.IsModel( edict->s.modelindex ) )
      {
      int skinnum;

      skinnum = gi.Skin_NumForName( edict->s.modelindex, skinname );
      if (skinnum >= 0)
         edict->s.skinnum = skinnum;
      }
   if ( parentmode->value )
      {
      flags &= ~FL_BLOOD;
      flags &= ~FL_DIE_GIBS;
      }

   if ( !(flags & (FL_BLOOD|FL_SPARKS|FL_TESSELATE)) )
      {
      flags |= FL_DARKEN;
      flags |= FL_TESSELATE;
      flags |= FL_DIE_TESSELATE;
      }
	}

void Object::Killed(Event *ev)
   {
   Entity * ent;
   Entity * attacker;
   Vector dir;
   Event * event;
   const char * name;
   int num;

   takedamage = DAMAGE_NO;
   setSolidType( SOLID_NOT );
	hideModel();

	attacker		= ev->GetEntity( 1 );

   if (flags & FL_DIE_TESSELATE)
      {
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
      }

   if (flags & FL_DIE_EXPLODE)
      {
	   CreateExplosion( worldorigin, 50, 0.5f, true, this, this, this );
      }

   if (flags & FL_DIE_GIBS)
      {
      setSolidType( SOLID_NOT );
      hideModel();

      CreateGibs( this, -150, edict->s.scale, 3 );
      }

//
// kill the killtargets
//
	name = KillTarget();
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
			ent->PostEvent( EV_Remove, 0 );
			} 
		while ( 1 );
		}
		
//
// fire targets
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
			ent->ProcessEvent( event );
			}
		while ( 1 );
		}

   PostEvent( EV_Remove, 0 );
   }

/*****************************************************************************/
/*SINED func_throwobject (0 .5 .8) (0 0 0) (0 0 0) 

This is an object you can pickup and throw at people
/*****************************************************************************/
CLASS_DECLARATION( Object, ThrowObject, "func_throwobject" );

Event EV_ThrowObject_Pickup( "pickup" );
Event EV_ThrowObject_Throw( "throw" );
Event EV_ThrowObject_PickupOffset( "pickupoffset" );
Event EV_ThrowObject_ThrowSound( "throwsound" );

ResponseDef ThrowObject::Responses[] =
	{
      { &EV_Touch,					      ( Response )ThrowObject::Touch },
      { &EV_ThrowObject_Pickup,	      ( Response )ThrowObject::Pickup },
      { &EV_ThrowObject_Throw,	      ( Response )ThrowObject::Throw },
      { &EV_ThrowObject_PickupOffset,	( Response )ThrowObject::PickupOffset },
      { &EV_ThrowObject_ThrowSound,	   ( Response )ThrowObject::ThrowSound },
		{ NULL, NULL }
	};

ThrowObject::ThrowObject()
	{
   pickup_offset = vec_zero;
	}

void ThrowObject::PickupOffset
	(
	Event *ev
	)
	{
   pickup_offset = edict->s.scale * ev->GetVector( 1 );
   }

void ThrowObject::ThrowSound
	(
	Event *ev
	)
	{
   throw_sound = ev->GetString( 1 );
   }

void ThrowObject::Touch
	(
	Event *ev
	)

	{
   Event * e;
   Entity * other;

	if ( movetype != MOVETYPE_BOUNCE )
      return;

	other = ev->GetEntity( 1 );
	assert( other );

	if ( other->isSubclassOf( Teleporter ) )
		{
		return;
		}

	if ( other->entnum == owner )
		{
		return;
		}

   if ( throw_sound.length() )
      {
	   e = new Event( EV_StopEntitySound );
      ProcessEvent( e );
      }

   if (other->takedamage)
   	other->Damage( this, G_GetEntity( owner ), size.length()*velocity.length()/400, worldorigin, velocity, level.impact_trace.plane.normal, 32, 0, MOD_THROWNOBJECT, -1, -1, 1.0f );
   Damage( this, this, max_health, worldorigin, velocity, level.impact_trace.plane.normal, 32, 0, MOD_THROWNOBJECT, -1, -1 , 1 );
	}

void ThrowObject::Throw
	(
	Event *ev
	)
	{
   Entity *owner;
   Entity *targetent;
   float  speed;
   float traveltime;
   float vertical_speed;
   Vector target, dir;
   float  grav;
   Vector xydir;
   Event * e;

   owner = ev->GetEntity( 1 );
   assert( owner );
   if (!owner)
      return;
   speed = ev->GetFloat( 2 );
   if ( !speed )
      speed = 1;
   targetent = ev->GetEntity( 3 );
   assert( targetent );
   if (!targetent)
      return;
   if ( ev->NumArgs() == 4 ) 
      grav = ev->GetFloat( 4 );
   else
      grav = 1;

   e = new Event( EV_Detach );
   ProcessEvent( e );

	this->owner = owner->entnum;
	edict->owner = owner->edict;

   gravity = grav;

   target = targetent->worldorigin;
   target.z += targetent->viewheight;
	setMoveType( MOVETYPE_BOUNCE );
	setSolidType( SOLID_BBOX );
	edict->clipmask = MASK_PROJECTILE;

   dir = target - worldorigin;
   xydir = dir;
   xydir.z = 0;
   traveltime = xydir.length() / speed;
   vertical_speed = ( dir.z / traveltime ) + ( 0.5f * gravity * sv_gravity->value * traveltime );
   xydir.normalize();

	// setup ambient flying sound
   if ( throw_sound.length() )
      {
	   e = new Event( EV_RandomEntitySound );
	   e->AddString( throw_sound );
      ProcessEvent( e );
      }

   velocity = speed * xydir;
   velocity.z = vertical_speed;
	
 	angles = velocity.toAngles();
	angles[ PITCH ] = - angles[ PITCH ];
	setAngles( angles );

   avelocity.x = crandom() * 200;
   avelocity.y = crandom() * 200;
	takedamage = DAMAGE_YES;

   }

void ThrowObject::Pickup
	(
	Event *ev
	)
	{
   Entity * ent;
   Event * e;
   str bone;

   ent = ev->GetEntity( 1 );
   assert( ent );
   if ( !ent )
      return;
   bone = ev->GetString( 2 );

   e = new Event( EV_Attach );
   e->AddEntity( ent );
   e->AddString( bone );
   setOrigin( pickup_offset );
   ProcessEvent( e );
   edict->s.renderfx &= ~RF_FRAMELERP;
   }

//
// Barrel with fire coming out of it
//
CLASS_DECLARATION( Object, FireBarrel, "world_firebarrel" );

ResponseDef FireBarrel::Responses[] =
	{
		{ NULL, NULL }
	};

FireBarrel::FireBarrel()
	{
   Vector offset;

   fire = new FireSprite;
   // put the fire 3/4 of the way up the barrel
   offset[ 2 ] = (3 * size[ 2 ]) / 4;
   fire->setOrigin( worldorigin + offset );
   fire->setScale( edict->s.scale );
   }

FireBarrel::~FireBarrel()
	{
   fire->PostEvent( EV_Remove, 0 );
   fire = NULL;
   }