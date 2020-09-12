//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/stungun.cpp                      $
// $Revision:: 3                                                              $
//   $Author:: Jimdose                                                        $
//     $Date:: 11/16/98 2:11a                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/stungun.cpp                           $
// 
// 3     11/16/98 2:11a Jimdose
// removed unused variable in Shoot
// 
// 2     10/21/98 1:15a Markd
// Added stungun
// 
// 1     10/21/98 12:22a Markd
// 
// DESCRIPTION:
// Stungun
// 

#include "g_local.h"
#include "bullet.h"
#include "stungun.h"
#include "specialfx.h"
#include "misc.h"
#include "explosion.h"
#include "surface.h"

CLASS_DECLARATION( BulletWeapon, Stungun, "weapon_stungun" );

ResponseDef Stungun::Responses[] =
	{
	   { &EV_Weapon_Shoot,              ( Response )Stungun::Shoot },
		{ NULL, NULL }
	};

Stungun::Stungun()
	{
	SetModels( "stun.def", "stun.def" );
   SetType( WEAPON_2HANDED_LO );
   notdroppable = true;
	SetMaxRange( 480 );
	}


// This is the trace that the laser portion of this weapon does.
void Stungun::TraceAttack
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

void Stungun::Shoot
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

   // Fire the beam
   length = ev->GetInteger( 1 );
   end   = pos + dir * length;
 	trace = G_Trace( pos, vec_zero, vec_zero, end, owner, MASK_SHOT, "Stungun::Shoot" );
   delta = trace.endpos - pos;
   dist  = delta.length();

   // Set the pitch of this weapon so the client can use it to fire bullets in the right directions   
   dir = Vector( owner->orientation[ 0 ] );
   angles = dir.toAngles();
   setAngles( angles );
   
   damg = 35;
   TraceAttack( pos, trace.endpos, damg, &trace, 0, 0, 0 );
   NextAttack( 0 );
	}

