//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/fists.cpp                           $
// $Revision:: 34                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 11/17/98 1:31a                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/fists.cpp                                $
// 
// 34    11/17/98 1:31a Markd
// took out damage multiplier for fists
// 
// 33    11/12/98 11:31p Jimdose
// changed impact_bodyimpact to impact_goryimpact
// increased kick from melee
// 
// 32    10/20/98 8:26p Markd
// Added Attacker to DamageSurface stuff
// 
// 31    10/20/98 3:59p Aldie
// Tweaked fist radius
// 
// 30    10/14/98 12:12a Aldie
// Tweak damage
// 
// 29    10/11/98 5:35p Aldie
// Added meansofdeath
// 
// 28    10/05/98 10:23p Aldie
// Fixed rank
// 
// 27    10/01/98 3:35p Onethumb
// 
// 26    9/18/98 10:12p Markd
// made fists not use MASK_SHOT, MASK_PROJECTILE instead
// 
// 25    9/18/98 8:14p Markd
// rewrote surface system so that surfaces are now damaged by surface name instead
// of by surfinfo
// 
// 24    8/31/98 7:45p Aldie
// Updated surface data structure and removed surfinfo field
// 
// 23    8/31/98 4:33p Markd
// Made fists use fulltrace
// 
// 22    8/29/98 9:40p Jimdose
// Added call info to G_Trace
// 
// 21    8/29/98 5:27p Markd
// added specialfx, replaced misc with specialfx where appropriate
// 
// 20    8/18/98 11:08p Markd
// Added new Alias System
// 
// 19    8/17/98 3:16p Aldie
// Made fists not ignore armor
// 
// 18    8/06/98 6:58p Jimdose
// Added min/max range, and projectile speed
// 
// 17    7/23/98 6:17p Aldie
// Updated damage system and fixed some damage related bugs.  Also put tracers
// back to the way they were, and added gib event to funcscriptmodels
// 
// 16    7/22/98 9:57p Markd
// Defined weapon type
// 
// 15    7/21/98 1:10p Aldie
// Added meansofdeath to obituaries
// 
// 14    7/19/98 10:33p Aldie
// Update fist damage
// 
// 13    6/19/98 9:29p Jimdose
// Moved gun orientation code to Weapon
// 
// 12    6/10/98 10:03p Markd
// Got working with reach and damage
// 
// 11    6/10/98 4:00p Aldie
// Updated fists to do damage skins
// 
// 10    6/10/98 2:10p Aldie
// Updated damage function.
// 
// 9     5/27/98 5:21a Markd
// changed ranking of fists
// 
// 8     5/26/98 5:42p Markd
// Made fists more realistic damage wise
// 
// 7     5/25/98 7:58p Markd
// Moved TakeDamage a bit
// 
// 6     5/25/98 5:38p Markd
// Put in strike sound and stuff
// 
// 5     5/25/98 1:00a Markd
// Fixed Fists
// 
// 4     5/23/98 5:38p Markd
// slowed down firing rate
// 
// 3     5/20/98 10:43p Markd
// made fists into bullets
// 
// 2     5/11/98 11:24a Markd
// First time
// 
// DESCRIPTION:
// Normal Hands
// 

#include "g_local.h"
#include "fists.h"
#include "misc.h"
#include "specialfx.h"
#include "surface.h"

CLASS_DECLARATION( Weapon, Fists, NULL);

ResponseDef Fists::Responses[] =
	{
	   { &EV_Weapon_Shoot, ( Response )Fists::Shoot },
		{ NULL, NULL }
	};

Fists::Fists()
	{
	SetModels( NULL, "view_punch.def" );
	SetAmmo( NULL, 0, 0 );
	SetRank( 10, 10 );	
   strike_reach = 64;
   strike_damage = 20;
	SetMaxRange( strike_reach );
   SetType( WEAPON_MELEE );
   kick = 40;
   meansofdeath = MOD_FISTS;
	}

void Fists::Shoot( Event * ev )
	{
	trace_t	trace;
	Vector	start;
	Vector	end;
   float    damage;
	Vector   org;
	Vector   dir;
   int      surfflags;
   int      surftype;

	assert( owner );
	if ( !owner )
		{
		return;
		}

	NextAttack( 1 );

   damage = G_Random(strike_damage)+strike_damage;

	GetMuzzlePosition( &start, &dir );
	end	= start + dir * strike_reach;

   trace = G_FullTrace( start, vec_zero, vec_zero, end, 64, owner, MASK_PROJECTILE, "Fists::Shoot" );

	if ( !trace.surface )
		{
      surfflags = 0;
      surftype = 0;
		}
   else
      {
      surfflags = trace.surface->flags;
      surftype = SURFACETYPE_FROM_FLAGS( surfflags );
      surfaceManager.DamageSurface( &trace, damage, owner );
      }
	dir = Vector(trace.endpos) - start;
	dir.normalize();

	org = Vector(trace.endpos) - dir;

   if ( (trace.fraction < 1.0f) )
      {
      if ( trace.ent->entity && trace.ent->entity->takedamage )
		   {
         if ( trace.ent->entity->flags & FL_BLOOD )
	         {
            if ( ( meansofdeath == MOD_MUTANTHANDS ) || ( trace.ent->entity->health < -500 ) )
               {
               owner->RandomGlobalSound("impact_goryimpact");
               }
            else
               {
               owner->RandomGlobalSound("impact_bodyimpact");
               }
	         SpawnBlood( org, trace.plane.normal, damage );
	         }
         else
            {
		      gi.WriteByte( svc_temp_entity );
		      gi.WriteByte( TE_STRIKE );
		      gi.WritePosition( org.vec3() );
		      gi.WriteDir( trace.plane.normal );
		      gi.WriteByte( 120 );
		      gi.WriteByte( surftype );
		      gi.multicast( org.vec3(), MULTICAST_PVS );
            }
         if ( trace.intersect.valid )
            {
            // take the ground out so that the kick works
            trace.ent->entity->groundentity = NULL;

   			// We hit a valid group so send in location based damage
            trace.ent->entity->Damage( this,
                         owner,
                         damage,
                         trace.endpos,
                         dir,
                         trace.plane.normal,
                         kick,
                         0,
                         meansofdeath,
                         trace.intersect.parentgroup,
                         -1,
                         1 );
                         //trace.intersect.damage_multiplier );
            }
         else
            {
            // We didn't hit any groups, so send in generic damage
   			trace.ent->entity->Damage( this,
                         owner,
                         damage,
                         trace.endpos,
                         dir,
                         trace.plane.normal,
                         kick,
                         0,
                         meansofdeath,
                         -1,
                         -1,
                         1 );
            }
		   }
      else
		   {
		   gi.WriteByte( svc_temp_entity );
		   gi.WriteByte( TE_STRIKE );
		   gi.WritePosition( org.vec3() );
		   gi.WriteDir( trace.plane.normal );
		   gi.WriteByte( 120 );
		   gi.WriteByte( surftype );
		   gi.multicast( org.vec3(), MULTICAST_PVS );
		   }
      }
	}
