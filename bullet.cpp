//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/bullet.cpp                       $
// $Revision:: 71                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 10/22/98 7:57p                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/bullet.cpp                            $
// 
// 71    10/22/98 7:57p Markd
// put in proper pre-caching in all the classes
// 
// 70    10/20/98 8:26p Markd
// Added Attacker to DamageSurface stuff
// 
// 69    10/13/98 5:27p Markd
// revamped ricochet stuff
// 
// 68    10/13/98 12:35p Markd
// Fixed tracers and bullet holes on non-player guys
// 
// 67    10/05/98 11:30p Markd
// Added MakeBreakingSound when firing at things
// 
// 66    10/04/98 10:36p Markd
// put in ricochet code
// 
// 65    9/27/98 3:53p Aldie
// Put in some debugging information
// 
// 64    9/18/98 8:14p Markd
// rewrote surface system so that surfaces are now damaged by surface name
// instead of by surfinfo
// 
// 63    8/31/98 7:45p Aldie
// Updated surface data structure and removed surfinfo field
// 
// 62    8/29/98 9:39p Jimdose
// Added call info to G_Trace
// 
// 61    8/29/98 5:27p Markd
// added specialfx, replaced misc with specialfx where appropriate
// 
// 60    8/25/98 7:55p Markd
// Fixed weapon angles
// 
// 59    8/19/98 6:38p Markd
// Moved Assault rifle tracer into def file
// 
// 58    8/14/98 5:37p Aldie
// Moved blood stuff to sentient
// 
// 57    8/13/98 8:09p Aldie
// Moved blood particles to armor damage.
// 
// 56    8/10/98 6:52p Aldie
// Added scale to bloodsplats
// 
// 55    8/06/98 10:53p Aldie
// Added weapon tweaks and kickback.  Also modified blast radius damage and
// rocket jumping.
// 
// 54    8/04/98 3:27p Aldie
// Revert back to sending PITCH and YAW
// 
// 53    8/03/98 3:28p Aldie
// Only send over the PITCH of the gun when firing it
// 
// 52    8/01/98 4:39p Aldie
// Put some debug prints
// 
// 51    8/01/98 3:24p Aldie
// Added server effects flag for specific weapons
// 
// 50    7/31/98 7:42p Aldie
// Client side bullet effects
// 
// 49    7/25/98 5:48p Aldie
// Remove shotgun effect
// 
// 48    7/24/98 10:03p Aldie
// Fixed bullet damage with invalid traces
// 
// 47    7/23/98 6:17p Aldie
// Updated damage system and fixed some damage related bugs.  Also put tracers
// back to the way they were, and added gib event to funcscriptmodels
// 
// 46    7/22/98 10:41p Aldie
// Fixed tracers
// 
// 45    7/21/98 1:10p Aldie
// Added meansofdeath to obituaries
// 
// 44    7/17/98 7:57p Markd
// Added radius to FullTrace
// 
// 43    7/15/98 9:57p Markd
// Added shields support
// 
// 42    6/20/98 7:48p Markd
// using FullTrace now, also checking to make sure we have a valid intersection
// before trying to determine group num etc.
// 
// 41    6/19/98 9:29p Jimdose
// Moved gun orientation code to Weapon
// 
// 40    6/15/98 10:52p Jimdose
// Disabled fulltrace until bmodels are checked.
// 
// 39    6/15/98 10:07p Jimdose
// Made bullet weapons use G_FullTrace
// 
// 38    6/11/98 3:34p Jimdose
// TraceAttack was damaging the entity before checking the blood and sparks
// flags, so if the entity died before the check, we got a NULL pointer
// TraceAttack was doing the ricochet trace before checking if it should
// ricochet
// 
// 37    6/10/98 2:10p Aldie
// Updated damage function.
// 
// 36    6/08/98 11:35a Aldie
// Updated location based damage stuff
// 
// 35    6/05/98 6:23p Aldie
// Added location to AddMultiDamage
// 
// 34    5/27/98 7:34p Markd
// commented out damage reduction if not hitting body part
// 
// 33    5/27/98 5:21p Markd
// fixed up ray intersection a bit
// 
// 32    5/27/98 5:02a Markd
// increased nominal multiplier to 0.5f
// 
// 31    5/26/98 8:44p Markd
// Put in DamageSkin suport
// 
// 30    5/26/98 4:22p Markd
// Working on tri-ray intersection stuff
// 
// 29    5/23/98 4:46p Aldie
// Added bulletholes.
// 
// 28    5/05/98 7:38p Markd
// Added timeofs to ricochets in bulllet smoke events
// 
// 27    5/03/98 8:08p Markd
// Took out old code
// 
// 26    5/03/98 4:30p Jimdose
// Changed Vector class
// 
// 25    5/02/98 8:41p Markd
// Put in recursive bullet attacks and got rid of ricochets
// 
// 24    4/10/98 1:22a Markd
// Added FL_BLOOD support
// 
// 23    4/07/98 6:42p Jimdose
// Rewrote weapon code.
// Added order to rank
// 
// 22    4/06/98 7:52p Aldie
// Increased range of bullets.
// 
// 21    4/04/98 7:31p Jimdose
// Bullets don't spark or ricochet against sky
// 
// 20    4/02/98 4:48p Jimdose
// Changed TraceAttack to properly place bloodsplats
// 
// 19    3/30/98 2:35p Jimdose
// Moved firing from Magnum to make more general
// Added Ammo
// Added world models
// 
// 18    3/27/98 6:34p Jimdose
// Added sparks to show impact of bullets
// 
// 17    3/26/98 8:16p Jimdose
// Added precaching of sounds
// 
// 16    3/23/98 1:31p Jimdose
// Revamped event and command system
// 
// 15    3/05/98 5:44p Aldie
// Support for ricochet flag.
// 
// 14    3/04/98 8:02p Aldie
// More support for damage surfaces.
// 
// 13    3/04/98 5:12p Aldie
// Added support for damage surfaces.
// 
// 12    2/19/98 2:35p Jimdose
// Updated to work with Q2 based progs
// 
// 10    12/11/97 3:30p Markd
// Moved SpawnBlood to Weapon
// 
// 9     11/18/97 5:28p Markd
// Commented out shotgun
// 
// 8     11/11/97 9:41p Markd
// tweaked minimum scale in blood splats
// 
// 7     11/11/97 9:38p Markd
// made blood splats be based off of distance as well as damage.
// 
// 6     10/31/97 9:02p Jimdose
// Made it so that bsp objects don't leave bloodsplats
// 
// 5     10/31/97 7:18p Markd
// Put in BloodSpray
// 
// 4     10/31/97 4:28p Jimdose
// Removed redefinition of owner in base class Weapon, so any reference to
// gunoffset through owner had to use type overriding.
// 
// 3     10/27/97 3:29p Jimdose
// Removed dependency on quakedef.h
// 
// 2     9/26/97 4:43p Jimdose
// Added standard Ritual header
//
// DESCRIPTION:
// Base class for all bullet (hitscan) weapons.  Includes definition for shotgun.
// 

#include "g_local.h"
#include "specialfx.h"
#include "misc.h"
#include "bullet.h"
#include "q_shared.h"
#include "surface.h"

CLASS_DECLARATION( Weapon, BulletWeapon, NULL );

ResponseDef BulletWeapon::Responses[] =
	{
		{ NULL, NULL }
	};

BulletWeapon::BulletWeapon()
	{
   modelIndex( "sprites/tracer.spr" );
   modelIndex( "sprites/bullethole.spr" );
	}

void BulletWeapon::TraceAttack
	(
	Vector	start,
	Vector	end,
	int		damage,
	trace_t	*trace,
   int      numricochets,
   int      kick,
   int      dflags,
   int      meansofdeath,
   qboolean server_effects
	)
	
	{
	Vector		org;
	Vector		dir;
   Vector		endpos;
   int			surfflags;
   int			surftype;
   int			timeofs;
	Entity		*ent;
   qboolean    ricochet;

	if ( HitSky( trace ) )
		{
		return;
		}

   ricochet = false;
	dir = end - start;
	dir.normalize();

	org = end - dir;

	ent = trace->ent->entity;

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

      if ( surfflags & SURF_RICOCHET )
         ricochet = true;
      }
   if ( trace->intersect.valid && ent )
      {
      //
      // see if the parent group has ricochet turned on
      //
      if ( trace->intersect.parentgroup >= 0 )
         {
         int flags;

         flags = gi.Group_Flags( ent->edict->s.modelindex, trace->intersect.parentgroup );
         if ( flags & MDL_GROUP_RICOCHET )
            {
            surftype = ( flags >> 8 ) & 0xf;
            ricochet = true;
            }
         }
      }

	if ( ent )
		{
	   if ( !(ent->flags & FL_SHIELDS) )
		   {
		   if ( ent->flags & FL_SPARKS )
			   {
            // Take care of ricochet effects on the server
            if ( server_effects && !ricochet )
               {
		         timeofs = MAX_RICOCHETS - numricochets;
		         if ( timeofs > 0xf )
			         {
			         timeofs = 0xf;
			         }
               gi.WriteByte( svc_temp_entity );
	   		   gi.WriteByte( TE_GUNSHOT );
		   	   gi.WritePosition( org.vec3() );
			      gi.WriteDir( trace->plane.normal );
			      gi.WriteByte( 0 );
			      gi.multicast( org.vec3(), MULTICAST_PVS );
			      }
            MadeBreakingSound( org, owner );
            }

		   if ( ent->takedamage )
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
                            meansofdeath,
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
                            meansofdeath,
                            -1,
                            -1,
                            1 );
               }
			   }
		   }
	   else
		   {
         surftype = SURF_TYPE_METAL;
         ricochet = true;
         }
      }

   if ( ricochet && ( server_effects || ( numricochets < MAX_RICOCHETS ) ) )
      {
		timeofs = MAX_RICOCHETS - numricochets;
		if ( timeofs > 0xf )
			{
			timeofs = 0xf;
			}
      gi.WriteByte( svc_temp_entity );
	   gi.WriteByte( TE_GUNSHOT );
		gi.WritePosition( org.vec3() );
		gi.WriteDir( trace->plane.normal );
		gi.WriteByte( timeofs );
		gi.multicast( org.vec3(), MULTICAST_PVS );
      }

	if ( 
      ricochet &&
      numricochets && 
      damage
      )
      {
      dir += Vector( trace->plane.normal ) * 2;
  		endpos = org + dir * 8192;

      //
      // since this is a ricochet, we don't ignore the wewapon owner this time.
      //
      *trace = G_FullTrace( org, vec_zero, vec_zero, endpos, 5, NULL, MASK_SHOT, "BulletWeapon::TraceAttack" );
		if ( trace->fraction != 1.0 )
			{
			endpos = trace->endpos;
			TraceAttack( org, endpos, damage * 0.8f, trace, numricochets - 1, kick, dflags, meansofdeath, true );
			}
      }
	}

void BulletWeapon::FireBullets
	(
	int numbullets,
	Vector spread,
	int mindamage,
	int maxdamage,
   int dflags,
   int meansofdeath,
   qboolean server_effects
	)

	{
	Vector	src;
	Vector	dir;
	Vector	end;
	trace_t	trace;
	Vector	right;
	Vector	up;
	int		i;

	assert( owner );
	if ( !owner )
		{
		return;
		}

	GetMuzzlePosition( &src, &dir );

	owner->angles.AngleVectors( NULL, &right, &up );

   angles = dir.toAngles();
   setAngles( angles );

	for( i = 0; i < numbullets; i++ )
		{
  		end = src + 
            dir       * 8192 +  
			   right     * G_CRandom() * spread.x + 
            up        * G_CRandom() * spread.y;

      trace = G_FullTrace( src, vec_zero, vec_zero, end, 5, owner, MASK_SHOT, "BulletWeapon::FireBullets" );
#if 0
      Com_Printf("Server OWNER  Angles:%0.2f %0.2f %0.2f\n",owner->angles[0],owner->angles[1],owner->angles[2]);
      Com_Printf("Server Bullet Angles:%0.2f %0.2f %0.2f\n",angles[0],angles[1],angles[2]);
      Com_Printf("Right               :%0.2f %0.2f %0.2f\n",right[0],right[1],right[2]);
      Com_Printf("Up                  :%0.2f %0.2f %0.2f\n",up[0],up[1],up[2]);
      Com_Printf("Direction           :%0.2f %0.2f %0.2f\n",dir[0],dir[1],dir[2]);
      Com_Printf("Endpoint            :%0.2f %0.2f %0.2f\n",end[0],end[1],end[2]);
      Com_Printf("Server Trace Start  :%0.2f %0.2f %0.2f\n",src[0],src[1],src[2]);
      Com_Printf("Server Trace End    :%0.2f %0.2f %0.2f\n",trace.endpos[0],trace.endpos[1],trace.endpos[2]);
      Com_Printf("\n");
#endif
      if ( trace.fraction != 1.0 )
			{
			TraceAttack( src, trace.endpos, mindamage + (int)G_Random( maxdamage - mindamage + 1 ), &trace, MAX_RICOCHETS, kick, dflags, meansofdeath, server_effects );
			}
		}
   }

void BulletWeapon::FireTracer( void )
   {
   Entity   *tracer;
   Vector   src,dir,end;
   trace_t  trace;

	GetMuzzlePosition( &src, &dir );
	end = src + dir * 8192;
   trace = G_Trace( src, vec_zero, vec_zero, end, owner, MASK_SHOT, "BulletWeapon::FireTracer" );

   tracer = new Entity;

   tracer->angles = dir.toAngles();
	tracer->angles[ PITCH ] = -tracer->angles[ PITCH ] + 90;
	//tracer->angles[PITCH] *= -1;

   tracer->setAngles( tracer->angles );

 	tracer->setMoveType( MOVETYPE_NONE );
	tracer->setSolidType( SOLID_NOT );
   tracer->setModel( "sprites/tracer.spr" );
	tracer->setSize( "0 0 0", "0 0 0" );
   tracer->setOrigin( trace.endpos );
   tracer->edict->s.renderfx &= ~RF_FRAMELERP;

   VectorCopy( src, tracer->edict->s.old_origin );
   tracer->PostEvent(EV_Remove,0.1f);
   }