//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/gibs.cpp                         $
// $Revision:: 21                                                             $
//   $Author:: Jimdose                                                        $
//     $Date:: 11/19/98 9:29p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/gibs.cpp                              $
// 
// 21    11/19/98 9:29p Jimdose
// gibs copy gravaxis
// 
// 20    11/09/98 1:09a Aldie
// Changed fadesplat to fade in 30 secs
// 
// 19    11/08/98 8:31p Aldie
// Added ability to not fade splats
// 
// 18    10/22/98 9:30p Aldie
// Modified gib physics a little
// 
// 17    10/07/98 11:51p Jimdose
// moved body_parts out of game structure
// 
// 16    9/22/98 5:26p Markd
// fixed small gib bug
// 
// 15    9/22/98 5:19p Markd
// Put in new consolidated gib function
// 
// 14    9/20/98 5:11p Aldie
// Added blood trail to gib constructor
// 
// 13    8/29/98 9:43p Jimdose
// Added call info to G_Trace
// 
// 12    8/27/98 9:02p Jimdose
// Changed centroid to a variable
// 
// 11    8/19/98 8:49p Aldie
// Increased gibbage velocity
// 
// 10    8/10/98 6:52p Aldie
// Changed the gib throwing code
// 
// 9     7/29/98 2:31p Aldie
// Changed health to a float
// 
// 8     7/26/98 3:58p Aldie
// Reversed a logic bug 
// 
// 7     7/25/98 8:39p Aldie
// Bloodsplat only in single player
// 
// 6     7/24/98 10:04p Aldie
// Changed the gibs layout
// 
// 5     7/23/98 6:55p Aldie
// Fun with gibs
// 
// 4     7/23/98 6:17p Aldie
// Updated damage system and fixed some damage related bugs.  Also put tracers
// back to the way they were, and added gib event to funcscriptmodels
// 
// 3     6/30/98 12:40p Aldie
// Changed bloodsplat scale.
// 
// 2     5/27/98 5:03a Aldie
// First version of gibs
//
// DESCRIPTION:
// Gibs - nuff said

#include "gibs.h"

const char *body_parts[] = 
	{
    "gib1.def", "gibtorso.def", "gibhead.def", "gibleg.def" 
	 //"gib1.def", "gib2.def", "gibhead.def", "gibleg.def", "gibarm.def", "gibribs.def"
	};

const int num_body_parts = ( sizeof( body_parts ) / sizeof( body_parts[ 0 ] ) );

CLASS_DECLARATION( Entity, Gib, "gib" );

Event EV_ThrowGib("throwgib");

ResponseDef Gib::Responses[] =
	{
      { &EV_ThrowGib, ( Response )Gib::Throw },
      { &EV_Touch,    ( Response )Gib::Splat },
      { NULL, NULL }
	};

Gib::Gib
	(
	const char *name,
   qboolean blood_trail
	)

   {
   setSize("0 0 0", "0 0 0");
   setModel(name);
	setMoveType( MOVETYPE_BOUNCE );
	setSolidType( SOLID_BBOX );	
   if ( blood_trail )
      edict->s.effects |= EF_GIB;
   sprayed     = false;
   fadesplat   = true;
   }

Gib::Gib()
   {
   setSize("0 0 0", "0 0 0");
   setModel("gib1.def");
	setMoveType( MOVETYPE_BOUNCE );
	setSolidType( SOLID_BBOX );	
   edict->s.effects |= EF_GIB;
   sprayed           = false;
   fadesplat         = true;
   }

void Gib::Splat
	(
	Event *ev
	)

   {
   Vector end;

   if (deathmatch->value)
      return;
   
   if (!sv_gore->value)
      return;

   if (sprayed)
      return;

   sprayed = true;
   end = origin;
   end.z -= 1024;

   SprayBlood(origin, end, 25);

   setSolidType(SOLID_NOT);
   }

void Gib::SprayBlood
	(
	Vector start,
	Vector end,
	int damage
	)

   {
	trace_t     trace;
   float       dist;
   float       scale;
   Entity      *splat;
   Vector      norm;

   trace = G_Trace( start, vec_zero, vec_zero, end, NULL, MASK_SOLIDNONFENCE, "Gib::SprayBlood" );

	if ( HitSky( &trace ) || ( trace.ent->solid != SOLID_BSP ) )
		{
		return;
		}

   dist = ( Vector( trace.endpos ) - start ).length();
   scale = ( float )damage / ( dist * 0.3 );
   if ( scale > 0.6 )
		{
      scale = 0.6;
		}
   if ( scale < 0.02 )
		{
      return;
		}

   // Do a bloodsplat
   splat = new Entity;
	splat->setMoveType( MOVETYPE_NONE );
	splat->setSolidType( SOLID_NOT );
   splat->setModel( "sprites/bloodsplat.spr" );
	splat->edict->s.frame = G_Random( 4 );
	splat->setSize( "0 0 0", "0 0 0" );
	splat->edict->s.scale = scale * this->edict->s.scale;
   norm = trace.plane.normal;
   norm.x = -norm.x;
   norm.y = -norm.y;
   splat->angles = norm.toAngles();
   splat->angles.z = G_Random( 360 );
	splat->setAngles( splat->angles );
   splat->setOrigin( Vector( trace.endpos ) + ( Vector( trace.plane.normal ) * 0.2 ) );
	
   if ( fadesplat )
      splat->PostEvent( EV_FadeOut, 3 );
   else
      splat->PostEvent( EV_FadeOut, 30 );
   }

void Gib::ClipGibVelocity
	(
	void
	)

	{
	if (velocity[0] < -400)
		velocity[0] = -400;
	else if (velocity[0] > 400)
		velocity[0] = 400;
	if (velocity[1] < -400)
		velocity[1] = -400;
	else if (velocity[1] > 400)
		velocity[1] = 400;
	if (velocity[2] < 200)
		velocity[2] = 200;	// always some upwards
	else if (velocity[2] > 600)
		velocity[2] = 600;
}

void Gib::SetVelocity
	(
	float damage
	)

   {
   velocity[0] = 100.0 * crandom();
	velocity[1] = 100.0 * crandom();
	velocity[2] = 200.0 + 100.0 * random();
   
   avelocity = Vector( G_Random( 600 ), G_Random( 600 ), G_Random( 600 ) );
   
   if ( ( damage < -150 )  && ( G_Random() > 0.95f ) )
      velocity *= 2.0f;
   else if ( damage < -100 )
      velocity *= 1.5f;
   
   ClipGibVelocity();
   }

void Gib::Throw
	(
	Event *ev
	)

   {
   Entity *ent;

   ent = ev->GetEntity(1);    
   setOrigin(ent->centroid);
   worldorigin.copyTo(edict->s.old_origin);
   SetVelocity(ev->GetInteger(2));
   edict->s.scale = ev->GetFloat(3);
   PostEvent(EV_FadeOut, 10 + G_Random(5));
   }


void CreateGibs
   ( 
   Entity * ent, 
   float damage, 
   float scale, 
   int num, 
   const char * modelname
   )
   {
   int i;
   Gib * gib;

   assert( ent );

   if ( !ent )
      return;

   ent->RandomGlobalSound( "impact_gib" );
   for ( i = 0; i < num; i++ )
      {
      if ( modelname )
         {
         gib = new Gib( modelname );
         }
      else
         {
         gib = new Gib( body_parts[ i % num_body_parts ] );
         }
      gib->setOrigin(ent->centroid);
      gib->worldorigin.copyTo(gib->edict->s.old_origin);
      gib->SetVelocity( damage );
      gib->edict->s.scale = scale + G_Random( scale * 0.3 );
      gib->SetGravityAxis( ent->gravaxis );
      gib->PostEvent(EV_FadeOut, 10 + G_Random(5));
      }
   }
