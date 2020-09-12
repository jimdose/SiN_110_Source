//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/shield.cpp                       $
// $Revision:: 7                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 10/01/98 4:01p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/shield.cpp                            $
// 
// 7     10/01/98 4:01p Markd
// Added Archive and Unarchive functions
// 
// 6     9/23/98 5:19p Markd
// Put DAMAGE_NO in killed functions of these classes
// 
// 5     8/29/98 5:27p Markd
// added specialfx, replaced misc with specialfx where appropriate
// 
// 4     6/30/98 6:48p Aldie
// Updated shield with sined stuff
// 
// 3     6/30/98 12:41p Aldie
// If you touch a shield, then it does an effect.
// 
// 2     6/29/98 8:19p Aldie
// First version of a shield
//
// DESCRIPTION:
// Shields

#include "g_local.h"
#include "misc.h"
#include "specialfx.h"

class EXPORT_FROM_DLL Shield : public Entity
	{
   private:
      float       hitalpha;
      float       clearalpha;
	public:
      CLASS_PROTOTYPE( Shield );
                     
                     Shield();
		virtual void	ShieldFade( Event *ev );
      virtual void	ShieldDamage( Event *ev );
      virtual void	ShieldKilled( Event *ev );
      virtual void   ShieldTouch( Event *ev );
	   virtual void   Archive( Archiver &arc );
      virtual void   Unarchive( Archiver &arc );
	};

EXPORT_FROM_DLL void Shield::Archive
	(
	Archiver &arc
	)
   {
   Entity::Archive( arc );

   arc.WriteFloat( hitalpha );
   arc.WriteFloat( clearalpha );
   }

EXPORT_FROM_DLL void Shield::Unarchive
	(
	Archiver &arc
	)
   {
   Entity::Unarchive( arc );

   arc.ReadFloat( &hitalpha );
   arc.ReadFloat( &clearalpha );
   }

CLASS_DECLARATION( Entity, Shield, "shield" );

Event EV_ShieldFade( "shieldfade" );

ResponseDef Shield::Responses[] =
	{
      { &EV_Damage,        ( Response )Shield::ShieldDamage },
      { &EV_Touch,         ( Response )Shield::ShieldTouch },
      { &EV_Killed,        ( Response )Shield::ShieldKilled },
      { &EV_ShieldFade,    ( Response )Shield::ShieldFade },
      { NULL, NULL }
	};

/*****************************************************************************/
/*SINED func_shield (0 0 .5)
 "health" Health of the shield (Default is 100)
 "hitalpha" Alpha when the shield is hit or touched
 "clearalpha" Alpha when the shield is not hit or touched
/*****************************************************************************/

Shield::Shield
   (
   )

   {
	showModel();
   setSolidType( SOLID_BSP );
   setMoveType( MOVETYPE_NONE );
   hitalpha           = G_GetFloatArg( "hitalpha", 0.2 );
   clearalpha         = G_GetFloatArg( "clearalpha", 1.0 );
   health             = G_GetFloatArg( "health", 100 );
	max_health         = health;
	takedamage         = DAMAGE_YES;
   edict->s.renderfx |= RF_TRANSLUCENT;
   }

void Shield::ShieldKilled
   (
   Event *ev
   )

   {
   takedamage = DAMAGE_NO;
   TesselateModel
      (
      this,
      tess_min_size,
      tess_max_size,
      Vector( "0 0 1" ),
      ev->GetInteger( 2 ),
      tess_percentage,
      tess_thickness,
      vec3_origin
      );
   PostEvent( EV_Remove, 0 );
   }

void Shield::ShieldDamage
   (
   Event *ev
   )

   {
   int         damage;
   Entity      *inflictor, *attacker;

	damage		= ev->GetInteger( 1 );
	inflictor	= ev->GetEntity( 2 );
	attacker		= ev->GetEntity( 3 );
   health      -= damage;

   if ( health <= 0 )
      {
      PostEvent( EV_Remove, 0.1f );
      return;
      }

   CancelEventsOfType( EV_ShieldFade );
   edict->s.alpha = hitalpha;
   PostEvent( EV_ShieldFade, 0.1f );
   }

void Shield::ShieldTouch
   (
   Event *ev
   )

   {  
   CancelEventsOfType( EV_ShieldFade );
   edict->s.alpha = hitalpha;
   PostEvent( EV_ShieldFade, 0.3f );
   }

void Shield::ShieldFade
   (
   Event *ev
   )

   {   
   edict->s.alpha = clearalpha;
   }