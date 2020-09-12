//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/pulserifle.cpp                   $
// $Revision:: 69                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 3/02/99 9:14p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/pulserifle.cpp                        $
// 
// 69    3/02/99 9:14p Aldie
// Added CTF game code
// 
// 68    11/16/98 3:11a Jimdose
// pulse now takes gravity of owner
// 
// 67    11/16/98 2:11a Jimdose
// removed unused variable in Shoot
// 
// 66    11/15/98 12:22a Markd
// Fixed pre-caching issues
// 
// 65    11/13/98 3:30p Markd
// put in more precaching on weapons
// 
// 64    10/26/98 2:50p Aldie
// Fixed a bug with checking of NULL owners
// 
// 63    10/24/98 12:42a Markd
// changed origins to worldorigins where appropriate
// 
// 62    10/22/98 7:57p Markd
// put in proper pre-caching in all the classes
// 
// 61    10/20/98 8:26p Markd
// Added Attacker to DamageSurface stuff
// 
// 60    10/19/98 12:07a Jimdose
// made all code use fast checks for inheritance (no text lookups when
// possible)
// isSubclassOf no longer requires ::_classinfo()
// 
// 59    10/16/98 10:22p Aldie
// Updated single player damage settings
// 
// 58    10/16/98 9:50p Aldie
// Added SecondaryAmmo command
// 
// 57    10/15/98 2:32p Aldie
// Updated model name for pulsebomb
// 
// 56    10/10/98 9:18p Aldie
// Tweak damage
// 
// 55    10/10/98 5:58p Aldie
// More quantumdestab fixes
// 
// 54    10/09/98 11:56p Markd
// Added GenericPulseRifle
// 
// 53    10/06/98 2:49p Aldie
// Tweak NextAttack
// 
// 52    10/05/98 10:39p Aldie
// Fixed rank and updated damage.
// 
// 51    10/04/98 10:28p Aldie
// Added multiple weapon changes.  Damage, flashes, quantum stuff
// 
// 50    10/03/98 1:09p Aldie
// Tweak the effects again
// 
// 49    10/02/98 7:19p Aldie
// Orient the shockwave
// 
// 48    10/02/98 5:47p Aldie
// New effects - yet again
// 
// 47    10/01/98 4:01p Markd
// Added Archive and Unarchive functions
// 
// 46    9/29/98 11:45p Aldie
// New effect for mode1
// 
// 45    9/21/98 5:31p Markd
// took out owner out of projectile subclasses, working on archive and
// unarchive
// 
// 44    9/18/98 8:14p Markd
// rewrote surface system so that surfaces are now damaged by surface name
// instead of by surfinfo
// 
// 43    9/16/98 8:58p Aldie
// Added ability to do a hold down weapon charge
// 
// 42    9/09/98 3:56p Aldie
// New lightning effect
// 
// 41    9/01/98 3:05p Markd
// Rewrote explosion code
// 
// 40    8/31/98 7:45p Aldie
// Updated surface data structure and removed surfinfo field
// 
// 39    8/29/98 9:45p Jimdose
// Added call info to G_Trace
// 
// 38    8/29/98 5:27p Markd
// added specialfx, replaced misc with specialfx where appropriate
// 
// 37    8/18/98 8:12p Aldie
// Added dual mode weapons to base class
// 
// 36    8/01/98 3:03p Aldie
// Client side muzzle flash (dynamic light)
// 
// 35    7/25/98 7:10p Markd
// Put in EV_Removes for demo
// 
// 34    7/23/98 6:17p Aldie
// Updated damage system and fixed some damage related bugs.  Also put tracers
// back to the way they were, and added gib event to funcscriptmodels
// 
// 33    7/22/98 9:57p Markd
// Defined weapon type
// 
// 32    7/22/98 5:14p Aldie
// Fixed NextAttack time
// 
// 31    7/21/98 1:10p Aldie
// Added meansofdeath to obituaries
// 
// 30    7/01/98 4:39p Aldie
// Put Beaus' model explosion back in
// 
// 29    6/30/98 6:48p Aldie
// Removed a printf
// 
// 28    6/30/98 12:40p Aldie
// Fixed some bugs with vid_restart issue
// 
// 27    6/29/98 8:19p Aldie
// Updated shockwave
// 
// 26    6/25/98 7:32p Aldie
// Adding damage wall 
// 
// 25    6/19/98 9:30p Jimdose
// Moved gun orientation code to Weapon
// 
// 24    6/17/98 6:30p Aldie
// Updated ammo requirements
// 
// 23    6/17/98 5:42p Aldie
// Updated lots and made the beam do some damage.
// 
// 22    6/15/98 9:09p Aldie
// Updated the special fx for beams trailing from the pulse.
// 
// 21    6/15/98 12:25p Aldie
// Updated pulse beam parms
// 
// 20    6/15/98 10:38a Aldie
// New version of pulse stuff
// 
// 19    6/10/98 2:10p Aldie
// Updated damage function.
// 
// 18    5/14/98 9:14p Markd
// Changed models
// 
// 17    5/13/98 6:21p Markd
// Made pulse rifle burn wall as well as retrigger more often
// 
// 16    5/03/98 4:36p Jimdose
// Changed Vector class
// 
// 15    4/20/98 1:56p Markd
// SINED decelration is now in def file
// 
// 14    4/18/98 3:12p Markd
// Changed view weapon naming convention
// 
// 13    4/08/98 12:06a Jimdose
// Added temporary beam effect
// 
// 12    4/07/98 6:41p Jimdose
// Rewrote weapon code.
// Added order to rank
// 
// 11    4/02/98 4:20p Jimdose
// Tweaked for DM
// 
// 10    3/30/98 9:55p Jimdose
// Changed location of .def files
// 
// 9     3/30/98 2:34p Jimdose
// Moved firing to BulletWeapon to make more general
// Added Ammo
// Added world models
// 
// 8     3/28/98 8:55p Jimdose
// Created file
// 
// DESCRIPTION:
// Pulse rifle
// 

#include "g_local.h"
#include "bullet.h"
#include "pulserifle.h"
#include "specialfx.h"
#include "misc.h"
#include "explosion.h"
#include "surface.h"

#define PULSE_MODE 0

// Projectile portion of the pulse rifle

template class EXPORT_FROM_DLL SafePtr<Beam>;
typedef SafePtr<Beam> BeamPtr;

class EXPORT_FROM_DLL Pulse : public Projectile
   {
	public:
      CLASS_PROTOTYPE( Pulse );

                     Pulse();
      virtual void   Setup( Entity *owner, Vector pos, Vector dir );
      virtual void   Explode( Event *ev );
  	};

CLASS_DECLARATION( Projectile, Pulse, NULL );

Event EV_Pulse_UpdateBeams("update_beams");
Event EV_Pulse_Remove("remove_beams");

ResponseDef Pulse::Responses[] =
	{
      { &EV_Touch,                           ( Response )Pulse::Explode },
      { NULL, NULL }
	};

Pulse::Pulse()
   {
   }

void Pulse::Explode
   (
   Event *ev
   )

   {
   Entity      *other;
   Entity      *owner;
   int         damg;
   Vector      v;
   Vector      norm;
   Vector      shockangles;
   Entity      *pulseexpl;

   other = ev->GetEntity( 1 );
	assert( other );

	if ( other->isSubclassOf( Teleporter ) )
		{
		return;
		}

	if ( other->entnum == this->owner )
		{
		return;
		}

   owner = G_GetEntity( this->owner );

   if ( !owner )
      owner = world;

   stopsound( CHAN_VOICE );
	setSolidType( SOLID_NOT );

   // Hit the shy, so remove everything
	if ( HitSky() )
		{
		PostEvent( EV_Remove, 0 );
		return;
		}

  	damg = 50 + ( int )G_Random( 25 );
	
   // Single player packs a bigger punch
   if ( !deathmatch->value && owner->isClient() )
      damg *= 1.5;
   
   if ( other->takedamage )
   	other->Damage( this, owner, damg, worldorigin, velocity, level.impact_trace.plane.normal, 32, 0, MOD_PULSE, -1, -1, 1.0f );

   // Damage the surface
   surfaceManager.DamageSurface ( &level.impact_trace, damg, owner );

   damg = 100;

   // Single player packs a bigger punch
   if ( !deathmatch->value && owner->isClient() )
      damg *= 1.5;
   
   // Do an explosion but don't hurt other, since he already took damage.
   RadiusDamage( this, owner, damg, other, MOD_PULSE );
   
   v = velocity;
	v.normalize();
   v = worldorigin - v * 36;
  
   norm           = level.impact_trace.plane.normal;
   norm.x         = -norm.x;
   norm.y         = -norm.y;
   shockangles    = norm.toAngles();
	shockangles.z  = G_Random( 360 );

   // Start up the shockwave effect

   pulseexpl = new Entity;
   pulseexpl->setModel( "pulseshock.def" );
   pulseexpl->setOrigin( v );
   pulseexpl->worldorigin.copyTo(pulseexpl->edict->s.old_origin);
   pulseexpl->setAngles( shockangles );
   pulseexpl->setMoveType( MOVETYPE_NONE );
   pulseexpl->setSolidType( SOLID_NOT );
   pulseexpl->RandomAnimate( "pulseexplode", NULL );
   pulseexpl->PostEvent( EV_Remove, 0.1f );
   FlashPlayers(v, 0.1, 0.1, 1, 0.5, 500 );

   PostEvent( EV_Remove, 0 );
   }
     
void Pulse::Setup
   (
   Entity *owner,
   Vector pos, 
   Vector dir
   )

   {
   Event *ev1, *ev2;
   Vector forward, right, up;
   Vector end, delta;

	this->owner = owner->entnum;
	edict->owner = owner->edict;

   // Align the projectile
  	angles = dir.toAngles();
	angles[ PITCH ] = -angles[ PITCH ];
   setAngles( angles );
   edict->s.angles[ROLL] = rand() % 360;

   // Flies like a rocket
	setMoveType( MOVETYPE_TOSS );
	setSolidType( SOLID_BBOX );
	edict->clipmask = MASK_PROJECTILE;
   setModel( "sprites/pulsebomb.spr" );
	edict->s.effects |= EF_AUTO_ANIMATE;
     
   // Set the flying velocity
   velocity = dir * 1000;
   gravity = 0.7;

   SetGravityAxis( owner->gravaxis );

	takedamage = DAMAGE_NO;

   // Set the light and effects
   edict->s.renderfx |= RF_DLIGHT;
   edict->s.effects  |= EF_PULSE;
   edict->s.radius    = 100;
   edict->s.color_r   = 0.1f;
   edict->s.color_g   = 0.1f;
   edict->s.color_b   = 0.9f;

   // setup ambient thrust sound
	ev1 = new Event( EV_RandomEntitySound );
	ev1->AddString( "thrust" );
   ProcessEvent( ev1 ); 

   // Set size and origin
   setSize( "-1 -1 -1", "1 1 1" );
	setOrigin( pos );
   worldorigin.copyTo(edict->s.old_origin);
   
   // Remove the projectile in the future
	ev2 = new Event( EV_Pulse_Remove );
	PostEvent( ev2, 30 );
   }

CLASS_DECLARATION( BulletWeapon, PulseRifle, "weapon_pulserifle" );

ResponseDef PulseRifle::Responses[] =
	{
	   { &EV_Weapon_Shoot,              ( Response )PulseRifle::Shoot },
		{ NULL, NULL }
	};

PulseRifle::PulseRifle()
	{
#ifdef SIN_DEMO
   PostEvent( EV_Remove, 0 );
   return;
#endif
	SetModels( "pulse2.def", "view_pulse2.def" );
	SetAmmo( "BulletPulse", 10, 50 );
	SetSecondaryAmmo( "BulletPulse", 5, 50 );
   SetRank( 80, 80 );	
   SetType( WEAPON_2HANDED_LO );
   dualmode = true;
	modelIndex( "pulse_ammo.def" );
	modelIndex( "beam.def" );
   modelIndex( "pulseshock.def" );
   modelIndex( "sprites/pulsebomb.spr" );
   modelIndex( "sprites/pulse_muzzle.spr" );
	}


// This is the trace that the laser portion of this weapon does.
void PulseRifle::TraceAttack
   (	   
   Vector	start,
	Vector	end,
	int		damage,
	trace_t	*trace,
   int      numricochets,
   int      kick,
   int      dflags
	)
	
	{
	Vector   org;
	Vector   dir;
   int      surfflags;
   int      surftype;
   Entity    *ent;

	if ( HitSky( trace ) )
		{
		return;
		}

	dir = end - start;
	dir.normalize();

	org = end - dir * 4;

	if ( !trace->surface )
		{
      surfflags = 0;
      surftype = 0;
		}
   else
      {
      surfflags = trace->surface->flags;
      surftype = SURFACETYPE_FROM_FLAGS( surfflags );
      surfaceManager.DamageSurface( trace, damage, owner );
      }

	ent = trace->ent->entity;

	if ( ent && ent->takedamage )
		{
      if ( trace->intersect.valid )
         {
   	   // We hit a valid group so send in location based damage
         ent->Damage( this,
                      owner,
                      damage,
                      trace->endpos,
                      dir,
                      trace->plane.normal,
                      kick,
                      dflags,
                      MOD_PULSELASER,
                      trace->intersect.parentgroup,
                      -1,
                      trace->intersect.damage_multiplier );
         }
      else
         {
         // We didn't hit any groups, so send in generic damage
   		ent->Damage( this,
                      owner,
                      damage,
                      trace->endpos,
                      dir,
                      trace->plane.normal,
                      kick,
                      dflags,
                      MOD_PULSELASER,
                      -1,
                      -1,
                      1 );
         }
      }
   }


void PulseRifle::PulseExplosion
   (
   trace_t *trace
   )

   {
   Vector      org, v;
  	float       damg;
   Entity      *ent;   
   float       kick = 250;
   Vector      shockangles;
   Vector      norm;
   Vector      tempvec;
   float       points;
   Vector      endpos;
   float       radius;

   damg = 50 + ( int )G_Random( 20 );
	RadiusDamage( this, owner, damg, NULL, MOD_PULSE );

   VectorCopy( trace->dir, tempvec.vec3() );
   endpos = trace->endpos - ( tempvec * 8 );

   norm           = trace->plane.normal;
   norm.x         = -norm.x;
   norm.y         = -norm.y;
   shockangles    = norm.toAngles();
	shockangles.z  = G_Random( 360 );

   RandomPositionedSound( endpos, "impact_smallexplosion", 1.0, CHAN_AUTO, ATTN_NORM );
  
   radius = damg + 50;
   ent = findradius( NULL, endpos, radius );
	while( ent )
		{
		if ( ( ent->takedamage ) &&
           ( ent->movetype != MOVETYPE_NONE ) && 
		     ( ent->movetype != MOVETYPE_BOUNCE ) && 
		     ( ent->movetype != MOVETYPE_PUSH ) && 
		     ( ent->movetype != MOVETYPE_STOP ) )
			{
			org = ent->centroid;
			v = org - endpos;
         points = v.length();
         v.normalize();
         ent->velocity += (v * kick);

         points *= (float)0.5;

         if ( points < 0 )
				{
				points = 0;
				}

			points = damg - points;
			
         if ( points > 0 )
				{
				if ( this->CanDamage( ent ) )
					{
               ent->Damage(this, owner, points,
                           org, v, vec_zero, points, 
                           DAMAGE_RADIUS, MOD_PULSE,
                           -1, -1, 1.0f );
					}
				}
         }
		ent = findradius( ent, endpos, radius );
      }
   }

void PulseRifle::Shoot
	(
	Event *ev
	)

	{

   Vector   pos;
   Vector   end;
   Vector   dir;
   Vector   delta;
   trace_t  trace;
   float    dist;
   float    length;  
   float    damg;

	assert( owner );
	if ( !owner )
		{
		return;
      }      

	GetMuzzlePosition( &pos, &dir );

   if ( weaponmode == PRIMARY )
      {
      Pulse *pulse;

      pulse = new Pulse;
      pulse->Setup( owner, pos, dir );
      NextAttack( 0.5 );
      }
   else
      {
      // Fire the beam
      length = ev->GetInteger( 1 );
      end   = pos + dir * length;
 	   trace = G_Trace( pos, vec_zero, vec_zero, end, owner, MASK_SHOT, "PulseRifle::Shoot" );
      delta = trace.endpos - pos;
      dist  = delta.length();

      // Set the pitch of this weapon so the client can use it to fire bullets in the right directions   
      dir = Vector( owner->orientation[ 0 ] );
      angles = dir.toAngles();
      setAngles( angles );
      
		if ( ctf->value )
			damg = 30;
		else
	      damg = 15;
      TraceAttack( pos, trace.endpos, damg, &trace, 0, 0, 0 );
      NextAttack( 0 );
      }
	}

CLASS_DECLARATION( PulseRifle, GenericPulseRifle, "weapon_genericpulserifle" );

ResponseDef GenericPulseRifle::Responses[] =
	{
		{ NULL, NULL }
	};

GenericPulseRifle::GenericPulseRifle()
	{
	SetModels( NULL, "view_pulse2.def" );
	}

