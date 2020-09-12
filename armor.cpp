//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/armor.cpp                        $
// $Revision:: 21                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 10/24/98 2:07p                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/armor.cpp                             $
// 
// 21    10/24/98 2:07p Aldie
// Mutants can't pickup armor
// 
// 20    10/19/98 12:07a Jimdose
// made all code use fast checks for inheritance (no text lookups when
// possible)
// isSubclassOf no longer requires ::_classinfo()
// 
// 19    10/09/98 2:05a Aldie
// Updated DMFLAGS
// 
// 18    7/24/98 5:02p Aldie
// Armor never adds, only replaces
// 
// 17    7/24/98 3:46p Aldie
// dmflags - armor
// 
// 16    7/11/98 5:55p Aldie
// Fix pickup for armor
// 
// 15    6/30/98 6:47p Aldie
// If no amount in armor, then you can't pick it up.
// 
// 14    6/28/98 4:13p Markd
// simplified setup
// 
// 13    6/25/98 8:58p Markd
// made Pickupable comparison check for >= 
// 
// 12    6/25/98 8:47p Markd
// Added keyed items for Triggers, Rewrote Item class, rewrote every pickup
// method
// 
// 11    6/25/98 7:31p Aldie
// Changed the icon names
// 
// 10    6/24/98 1:35p Aldie
// Implementation of inventory system and picking stuff up
// 
// 9     6/17/98 1:19a Jimdose
// Moved setOwner to Item.  
// Added EV_Item_Pickup
// 
// 8     6/15/98 3:35p Aldie
// Updated picking up of armor to have a maxout value
// 
// 7     6/05/98 6:22p Aldie
// 
// 6     6/05/98 2:45p Aldie
// New version of armor
// 
// 4     11/07/97 5:59p Markd
// Removed QUAKE specific sound effects
// 
// 3     10/27/97 3:30p Jimdose
// Removed dependency on quakedef.h
// 
// 2     9/26/97 5:30p Jimdose
// Added standard Ritual headers
//
// DESCRIPTION:
// Standard armor that prevents a percentage of damage per hit.
// 

#include "g_local.h"
#include "armor.h"

/*
========
ARMOR
========
*/

CLASS_DECLARATION( Item, Armor, NULL )

ResponseDef Armor::Responses[] =
	{
		{ NULL, NULL }
	};

Armor::Armor
   (
   )
	{
	if ( DM_FLAG( DF_NO_ARMOR ) )
		{
		PostEvent( EV_Remove, 0 );
		return;
		}

   Set( 0 );
	}

void Armor::Setup
	(
	const char *model,
	int amount
	)

	{
	assert( model );
	setModel( model );
   Set( amount );
   }

void Armor::Add
	(
	int num
	)

	{
   // Armor never adds, it only replaces
	amount = num;
   if ( amount >= MaxAmount() )
      amount = MaxAmount();
	}

qboolean Armor::Pickupable
   (
   Entity *other
   )

   {
	if ( !other->isSubclassOf( Sentient ) )
		{
		return false;
		}
   else
      {
      Sentient * sent;
      Item * item;

      sent = ( Sentient * )other;

      // Mutants don't get armor
      if ( sent->flags & ( FL_MUTANT | FL_SP_MUTANT ) )
         {
         return false;
         }

      item = sent->FindItem( getClassname() );
      // If our armor is > than our current armor or armor has no value, then leave it alone.
      if ( item )
         if ( ( item->Amount() >= this->Amount() ) || !this->Amount() )
         {
         return false;
         }
      }
   return true;
   }

CLASS_DECLARATION( Armor, RiotHelmet, "armor_riothelmet" );

ResponseDef RiotHelmet::Responses[] =
	{
		{ NULL, NULL }
	};

RiotHelmet::RiotHelmet()
	{
	Setup( "riothelm.def", MAX_ARMOR );
	}

CLASS_DECLARATION( Armor, FlakJacket, "armor_flakjacket" );

ResponseDef FlakJacket::Responses[] =
	{
		{ NULL, NULL }
	};

FlakJacket::FlakJacket()
	{
	Setup( "flakjack.def", MAX_ARMOR );
	}

CLASS_DECLARATION( Armor, FlakPants, "armor_flakpants" );

ResponseDef FlakPants::Responses[] =
	{
		{ NULL, NULL }
	};

FlakPants::FlakPants()
	{
	Setup( "flakpants.def", MAX_ARMOR );
	}

