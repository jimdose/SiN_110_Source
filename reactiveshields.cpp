//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/reactiveshields.cpp              $
// $Revision:: 12                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 3/24/99 4:30p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/reactiveshields.cpp                   $
// 
// 12    3/24/99 4:30p Aldie
// tried to bullet proof certain crash bugs
// 
// 11    10/13/98 2:30p Aldie
// Check for owner
// 
// 10    10/01/98 8:00p Aldie
// Consolidated cprintf
// 
// 9     8/31/98 5:45p Aldie
// Updated timer
// 
// 8     8/18/98 11:08p Markd
// Added new Alias System
// 
// 7     8/12/98 6:04p Aldie
// Added a shield timer
// 
// 6     7/24/98 7:52p Aldie
// Tweaked respawn time
// 
// 5     7/24/98 7:32p Aldie
// Change reactive shields respawn time
// 
// 4     7/20/98 3:54p Aldie
// Fixed the icon
// 
// 3     7/15/98 11:23p Markd
// Took out RF_ENVMAPPED and moved it to player.cpp
// 
// 2     7/15/98 9:58p Markd
// first check in
// 
// 1     7/15/98 5:09p Markd
// 
// DESCRIPTION:
// Reactive Shields

#include "inventoryitem.h" 

Event EV_Item_ReactiveShields_PowerDown( "shields_powerdown" );

class EXPORT_FROM_DLL ReactiveShields : public InventoryItem
	{
	public:
      CLASS_PROTOTYPE( ReactiveShields );
                  ReactiveShields();
      void        Use( Event *ev );
      void        PowerDown( Event *ev );
   };

CLASS_DECLARATION( InventoryItem, ReactiveShields, "powerup_shield" )

ResponseDef ReactiveShields::Responses[] =
	{
      { &EV_InventoryItem_Use,				( Response )ReactiveShields::Use },
      { &EV_Item_ReactiveShields_PowerDown,( Response )ReactiveShields::PowerDown },
		{ NULL, NULL }
	};

ReactiveShields::ReactiveShields
	(
	)

	{
   setModel( "shield.def" );
   Set( 1 );
   setRespawnTime( 180 + G_Random( 60 ) );
	}

void ReactiveShields::Use
   (
   Event *ev
   )

   {
   Event *event;
   str realname;

   if ( !owner )
      {
      CancelPendingEvents();
      PostEvent( EV_Remove, 0 );
      return;
      }

   if ( owner->PowerupActive() )
      {
      return;
      }

   // Make sure there is a reactive shield available
   assert( amount );

   amount--;
   if (amount <= 0)
      {
      owner->RemoveItem( this );
      }

   owner->flags |= FL_SHIELDS;
   PostEvent( EV_Item_ReactiveShields_PowerDown, 30 );

	realname = GetRandomAlias( "snd_activate" );
   if ( realname.length() )
      owner->sound( realname, 1, CHAN_ITEM, ATTN_NORM );
   owner->edict->s.renderfx |= RF_DLIGHT;
	owner->edict->s.color_r	= 0;
	owner->edict->s.color_g	= 0;
	owner->edict->s.color_b	= 1;
	owner->edict->s.radius	= 120;

   event = new Event( "poweruptimer" );
   event->AddInteger( 30 );
   event->AddInteger( P_SHIELDS );
   owner->ProcessEvent ( event );
   }

void ReactiveShields::PowerDown
   (
   Event *ev
   )

   {
   if ( !owner )
      {
      CancelPendingEvents();
      PostEvent( EV_Remove, 0 );
      return;
      }

   if ( owner->flags & FL_SHIELDS )
      {
      str realname;

      owner->flags &= ~FL_SHIELDS;
	   realname = GetRandomAlias( "snd_deactivate" );
      if ( realname.length() )
         owner->sound( realname, 1, CHAN_ITEM, ATTN_NORM );
      owner->edict->s.renderfx &= ~RF_DLIGHT;
	   owner->edict->s.color_r	= 0;
	   owner->edict->s.color_g	= 0;
	   owner->edict->s.color_b	= 0;
	   owner->edict->s.radius	= 0;
      }
   CancelPendingEvents();
   PostEvent( EV_Remove, 0 );
   }

