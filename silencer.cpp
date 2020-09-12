//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/silencer.cpp                     $
// $Revision:: 10                                                             $
//   $Author:: Jimdose                                                        $
//     $Date:: 10/19/98 12:07a                                                $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/silencer.cpp                          $
// 
// 10    10/19/98 12:07a Jimdose
// made all code use fast checks for inheritance (no text lookups when
// possible)
// isSubclassOf no longer requires ::_classinfo()
// 
// 9     10/07/98 9:06p Aldie
// Changed silencer model
// 
// 8     10/05/98 10:19p Aldie
// Covnverted over to new silencer methods
// 
// 7     9/21/98 5:01p Markd
// Took out unused variable
// 
// 6     6/25/98 8:47p Markd
// Added keyed items for Triggers, Rewrote Item class, rewrote every pickup
// method
// 
// 5     6/24/98 1:37p Aldie
// Implementation of inventory system and picking stuff up
// 
// 4     6/19/98 6:37p Aldie
// Using silencer for inventory test
// 
// 3     6/18/98 9:26p Aldie
// Made silencer a test for inventory.
// 
// 2     6/15/98 9:10p Aldie
// First version of silenced weapons
//
// DESCRIPTION:
// Silencer Powerup

#include "silencer.h"
#include "sentient.h"

CLASS_DECLARATION( InventoryItem, Silencer, "powerups_silencer" )

ResponseDef Silencer::Responses[] =
	{
	   { &EV_Trigger_Effect,					( Response )Silencer::PickupSilencer },
		{ NULL, NULL }
	};

Silencer::Silencer
	(
	)

	{
	setModel( "silencer.def" );
   icon_name  = "i_silencer";
   icon_index = gi.imageindex( icon_name.c_str() );
   Set( 1 );
	}

Silencer::~Silencer()
   {
   }

void Silencer::PickupSilencer
   (
   Event *ev
   )

   {
	Sentient    *sen;
	Entity      *other;

	other = ev->GetEntity( 1 );
   if ( ItemPickup( other ) )
      {
      if ( other->isSubclassOf( Sentient ) )
         {
         sen = ( Sentient * )other;
         // Make the user lower and raise the weapon so that the silencer will attach
         sen->UpdateSilencedWeapons();

         sen->flags |= FL_SILENCER;
         }
      }
   }