//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/health.cpp                       $
// $Revision:: 20                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 3/19/99 5:03p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/health.cpp                            $
// 
// 20    3/19/99 5:03p Aldie
// Added REGENERATION TECH support
// 
// 19    11/17/98 6:08a Jimdose
// made PickupHealth take health from player's inventory before checking if
// they can pick it up.  Fixes bug where player can't pickup health due to
// health somehow being in their inventory.
// 
// 18    10/27/98 5:19p Aldie
// Added a few items for health
// 
// 17    10/09/98 2:06a Aldie
// Updated DMFLAGS
// 
// 16    8/27/98 2:33p Aldie
// Changed adrenaline to megahealth
// 
// 15    7/23/98 11:25p Aldie
// Fixed health for hopefully the last time.
// 
// 14    7/15/98 11:22p Markd
// Don't set the model unless one hasn't been setup yet
// 
// 13    7/14/98 6:58p Aldie
// Updated healths
// 
// 12    6/25/98 8:47p Markd
// Added keyed items for Triggers, Rewrote Item class, rewrote every pickup
// method
// 
// 11    6/24/98 1:36p Aldie
// Implementation of inventory system and picking stuff up
// 
// 10    5/27/98 7:33p Markd
// clear out damage if healed
// 
// 9     5/24/98 8:46p Jimdose
// Made a lot of functions more str-friendly.
// Got rid of a lot of char * based strings
// Cleaned up get spawn arg functions and sound functions
// sound functions now use consistant syntax
// 
// 8     5/13/98 4:45p Jimdose
// Startup event is now posted with 0 delay
// 
// 7     5/08/98 2:56p Markd
// Put in health pickup sounds
// 
// 6     4/18/98 3:41p Markd
// Changed health types to health_ instead of item_health_
// 
// 5     4/07/98 6:43p Jimdose
// turned off respawn in single player
// 
// 4     4/04/98 6:04p Jimdose
// Made response from EV_Trigger_ActivateTargets to EV_Trigger_Effect
// 
// 3     3/30/98 9:54p Jimdose
// Changed location of .def files
// 
// 2     3/30/98 2:30p Jimdose
// Created file
// 
// DESCRIPTION:
// Health powerup 
// 

#include "g_local.h"
#include "item.h"
#include "sentient.h"
#include "health.h"
#include "ctf.h"

CLASS_DECLARATION( Item, Health, "health_020" );

ResponseDef Health::Responses[] =
	{
      { &EV_Item_Pickup,      				( Response )Health::PickupHealth },
		{ NULL, NULL }
	};

Health::Health()
	{
	if ( DM_FLAG( DF_NO_HEALTH ) )
		{
		PostEvent( EV_Remove, 0 );
		return;
		}

   Set( 20 );
   if ( !edict->s.modelindex )
	   setModel( "health.def" );
	}

void Health::PickupHealth
	(
	Event *ev
	)
	
	{
	Sentient *sen;
   Item * item;
	Entity *other;

	other = ev->GetEntity( 1 );
   if ( !other || !other->isSubclassOf( Sentient ) )
      {
      return;
      }

	sen = ( Sentient * )other;

   //
   // We don't want the player to hold on to a box of health!
   // This can happen if a player is given a health object,
   // so as a precaution, get rid of any health he's carrying.
   //
   item = sen->FindItem( getClassname() );
   if ( item )
      {
      sen->RemoveItem( item );
      item->PostEvent( EV_Remove, 0 );
      }

   if ( !ItemPickup( other ) )
      {
      return;
      }

	sen->health += amount;
   if ( ctf->value && sen->HasItem( "CTF_Tech_Regeneration" ) )
      {
		if ( sen->health > CTF_TECH_REGENERATION_HEALTH )
			{
			sen->health = CTF_TECH_REGENERATION_HEALTH;
			}
      }
   else if ( sen->health > 200 )
		{
		sen->health = 200;
		}

   //
   // clear out damage if healed
   //
   if ( sen->health > 90 )
      {
      // clear the damage states
      memset( sen->edict->s.groups, 0, sizeof( sen->edict->s.groups ) );
      }

   //
   // we don't want the player to hold on to a box of health!
   //
   item = sen->FindItem( getClassname() );
   if ( item )
      {
      sen->RemoveItem( item );
      item->PostEvent( EV_Remove, 0 );
      }
	}



CLASS_DECLARATION( Health, SmallHealth, "health_005" );

ResponseDef SmallHealth::Responses[] =
	{
		{ NULL, NULL }
	};

SmallHealth::SmallHealth()
	{
	Set( 5 );
	setModel( "health_small.def" );
	}

CLASS_DECLARATION( Health, LargeHealth, "health_050" );

ResponseDef LargeHealth::Responses[] =
	{
		{ NULL, NULL }
	};

LargeHealth::LargeHealth()
	{
	Set( 50 );
	setModel( "health_large.def" );
	}

CLASS_DECLARATION( Health, MegaHealth, "health_100" );

ResponseDef MegaHealth::Responses[] =
	{
		{ NULL, NULL }
	};

MegaHealth::MegaHealth()
	{
	Set( 100 );
	setModel( "health_medkit.def" );
	}

CLASS_DECLARATION( Health, Apple, NULL );

ResponseDef Apple::Responses[] =
	{
		{ NULL, NULL }
	};

Apple::Apple()
	{
	setModel( "health_apple.def" );
	}

CLASS_DECLARATION( Health, Banana, NULL );

ResponseDef Banana::Responses[] =
	{
		{ NULL, NULL }
	};

Banana::Banana()
	{
	setModel( "health_banana.def" );
	}

CLASS_DECLARATION( Health, Sandwich, NULL );

ResponseDef Sandwich::Responses[] =
	{
		{ NULL, NULL }
	};

Sandwich::Sandwich()
	{
	setModel( "health_sandwich.def" );
	}

CLASS_DECLARATION( Health, Soda, NULL );

ResponseDef Soda::Responses[] =
	{
		{ NULL, NULL }
	};

Soda::Soda()
	{
	setModel( "health_soda.def" );
	}

