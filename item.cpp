//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/item.cpp                         $
// $Revision:: 51                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 11/12/98 9:20p                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/item.cpp                              $
// 
// 51    11/12/98 9:20p Markd
// fixed null sounds for snd_pickup
// 
// 50    10/24/98 2:07p Aldie
// Mutants can only pickup health
// 
// 49    10/22/98 10:22p Markd
// Put in support for game and level item script variables
// 
// 48    10/19/98 12:05a Jimdose
// made all code use fast checks for inheritance (no text lookups when
// possible)
// isSubclassOf no longer requires ::_classinfo()
// got rid of warning in Set
// 
// 47    10/14/98 1:18a Jimdose
// Got cross-level persistant info working
// Added amount_override
// 
// 46    10/11/98 8:57p Aldie
// Don't print out error message unecessarily
// 
// 45    10/10/98 1:28a Jimdose
// items no longer drop to the floor when loading savegames
// 
// 44    10/09/98 2:06a Aldie
// Updated DMFLAGS
// 
// 43    10/07/98 5:51p Markd
// Fixed small sized enemies getting resized and causing fall out of level
// errors
// 
// 42    10/04/98 6:15p Markd
// fixed pickup sounds
// 
// 41    9/29/98 5:59p Markd
// Added dialog_needed stuff
// 
// 40    9/29/98 11:05a Markd
// Added respawnsound support
// 
// 39    9/15/98 6:37p Markd
// Added RotatedBounds flag support
// 
// 38    9/08/98 9:29p Markd
// fixed picking things up by using them
// 
// 37    9/02/98 11:53a Markd
// Put in pickup by pressing the use key
// 
// 36    9/01/98 7:45p Aldie
// Added itemname
// 
// 35    8/29/98 7:23p Aldie
// Added itemname to get around targetname problem.
// 
// 34    8/18/98 11:08p Markd
// Added new Alias System
// 
// 33    8/15/98 1:48p Aldie
// Don't turn off glow when objects are picked up
// 
// 32    8/12/98 4:19p Aldie
// Fixed icons not showing up correctly
// 
// 31    7/26/98 1:17a Markd
// Put in respawn sounds for items
// 
// 30    7/14/98 6:57p Aldie
// Made dropped weapons fade out
// 
// 29    7/14/98 3:53p Markd
// made pickup sounds work properly
// 
// 28    7/12/98 4:34p Markd
// Fixed bounding boxes on items
// 
// 27    7/11/98 8:19p Jimdose
// Drop now returns true or false depending upon whether the item can be
// dropped or not
// 
// 26    7/10/98 2:48p Aldie
// Cleared targetname for all items to circumvent an error when removing an
// actor carrying a weapon of the same targetname as him.
// 
// 25    6/26/98 11:30a Markd
// Changed ItemPickup
// 
// 24    6/25/98 8:47p Markd
// Added keyed items for Triggers, Rewrote Item class, rewrote every pickup
// method
// 
// 23    6/24/98 1:36p Aldie
// Implementation of inventory system and picking stuff up
// 
// 22    6/17/98 1:20a Jimdose
// Moved setOwner to Item.  
// Added EV_Item_Pickup
// 
// 21    6/16/98 9:37p Markd
// made items capable of being orientated
// 
// 20    6/16/98 4:08p Jimdose
// Gave dropping weapons velocity
// 
// 19    6/04/98 7:36p Jimdose
// PlaceItem now posts the EV_Remove instead of processing it
// 
// 18    6/03/98 4:37p Markd
// When picking an item up, stop glowing, when dropping it start glowing
// 
// 17    5/13/98 4:45p Jimdose
// droptofloor event is now posted with 0 delay
// 
// 16    5/03/98 4:50p Jimdose
// Fixed bug where items fell through ground
// 
// 15    5/03/98 4:44p Jimdose
// changed Vector class
// 
// 14    5/02/98 12:39a Jimdose
// Changed PlaceItem so that items only test if they can drop to the floor.  If
// they can, they're left where they were spawned so that they fall, otherwise
// they're removed
// 
// 13    4/05/98 9:41p Markd
// Put in RF_GLOW
// 
// 12    4/04/98 6:05p Jimdose
// ItemPickup no longer activates targets, since the item should alread have
// triggered its targets when it was touched
// 
// 11    4/02/98 4:49p Jimdose
// changed droptofloor
// 
// 10    3/30/98 2:32p Jimdose
// now shows model on placement
// 
// 9     3/28/98 8:57p Jimdose
// changed bounding box
// 
// 8     3/23/98 1:31p Jimdose
// Revamped event and command system
// 
// 7     3/02/98 8:49p Jimdose
// Changed the classid parameter of CLASS_DECLARATION to a quoted string so
// that you could have a NULL classid.
// 
// 6     2/19/98 2:35p Jimdose
// Updated to work with Q2 based progs
// 
// 4     11/07/97 5:59p Markd
// Removed QUAKE specific sound effects
// 
// 3     10/27/97 3:29p Jimdose
// Removed dependency on quakedef.h
// 
// 2     9/26/97 5:30p Jimdose
// Added standard Ritual headers
//
// DESCRIPTION:
// Base class for respawnable, carryable objects.
// 

#include "g_local.h"
#include "entity.h"
#include "trigger.h"
#include "item.h"
#include "inventoryitem.h"
#include "scriptmaster.h"
#include "health.h"

Event EV_Item_Pickup( "item_pickup" );
Event EV_Item_DropToFloor( "droptofloor" );
Event EV_Item_Respawn( "respawn" );
Event EV_Item_SetAmount( "amount" );
Event EV_Item_SetMaxAmount( "maxamount" );
Event EV_Item_SetIconName( "iconname" );
Event EV_Item_SetItemName( "itemname" );
Event EV_Item_RespawnSound( "respawnsound" );
Event EV_Item_DialogNeeded( "dialogneeded" );

CLASS_DECLARATION( Trigger, Item, NULL );

ResponseDef Item::Responses[] =
	{
		{ &EV_Trigger_Effect,	   ( Response )Item::ItemTouch },
	   { &EV_Item_DropToFloor,	   ( Response )Item::DropToFloor },
	   { &EV_Item_Respawn,		   ( Response )Item::Respawn },
	   { &EV_Item_SetAmount,      ( Response )Item::SetAmount },
	   { &EV_Item_SetMaxAmount,   ( Response )Item::SetMaxAmount },
	   { &EV_Item_SetIconName,    ( Response )Item::SetIconName },
      { &EV_Item_SetItemName,    ( Response )Item::SetItemName },
	   { &EV_Item_Pickup,			( Response )Item::Pickup },
      { &EV_Use,		            ( Response )Item::TriggerStuff },
      { &EV_Item_RespawnSound,   ( Response )Item::RespawnSound },
      { &EV_Item_DialogNeeded,   ( Response )Item::DialogNeeded },
		{ NULL, NULL }
	};

Item::Item()
	{
   str fullname;
   Vector defangles;

	setRespawnTime( 20 );
	setRespawn( false );

	setSolidType( SOLID_NOT );

	// Set default respawn behavior
	// Derived classes should use setRespawn
	// if they want to override the default behavior
	if ( deathmatch->value )
		{
		setRespawn( true );
		}
	else
		{
		setRespawn( false );
		}

   edict->s.renderfx |= RF_GLOW;

   // angles
   defangles = Vector( 0, G_GetFloatArg( "angle", 0 ), 0 );
   if (defangles.y == -1)
      {
      defangles = Vector( -90, 0, 0 );
      }
   else if (defangles.y == -2)
      {
      defangles = Vector( 90, 0, 0 );
      }
   angles = G_GetVectorArg( "angles", defangles );
	setAngles( angles );

   //
   // we want the bounds of this model auto-rotated
   //
   flags |= FL_ROTATEDBOUNDS;

   //
   // rotate the mins and maxs for the model
   //
   if ( size.length() < 10 )
	   setSize( "-10 -10 0", "10 10 20" );

   //
   // reset the mins and maxs to pickup the FL_ROTATEDBOUNDS flag
   //
   setSize( mins, maxs );

   if ( !LoadingSavegame )
      {
	   // Items can't be immediately dropped to floor, because they might
	   // be on an entity that hasn't spawned yet.
	   PostEvent( EV_Item_DropToFloor, 0 );
      }

	respondto = TRIGGER_PLAYERS;

   icon_name = str("");
   icon_index = 0;
   item_index = 0;
   maximum_amount = 1;
   playrespawn = false;

   amount_override = false;
   amount = 1;

   // FIXME
   // If the targetname is set by the spawn args, then this item
   // will have a targetname.  If we try to remove the owner of this
   // item, then we will remove the owner, then try to remove the item
   // which will already have been removed by the previous event.
   // This doesn't allow any items to have a targetname.
   SetTargetName( "" );

   // Using itemname as a temporary fix to this problem
   itemname = G_GetSpawnArg( "itemname", "");

   if ( G_GetSpawnArg( "amount" ) )
      {
      amount = G_GetIntArg( "amount" );
      if ( amount >= MaxAmount() )
         {
         SetMax( amount );
         }
      amount_override = true;
      }
	}

Item::~Item()
	{
	if ( owner )
		{
		owner->RemoveItem( this );
		owner = NULL;
		}
	}

void Item::CreateSpawnArgs
   (
   void
   )

   {
   G_SetIntArg( "amount", amount );
   G_SetSpawnArg( "model", model.c_str() );
   }

/*
============
PlaceItem

Puts an item back in the world
============
*/
void Item::PlaceItem
	(
	void
	)

	{
	setSolidType( SOLID_TRIGGER );
	setMoveType( MOVETYPE_TOSS );
	showModel();

   edict->s.renderfx |= RF_GLOW;
	groundentity = NULL;
	}

/*
============
DropToFloor

plants the object on the floor
============
*/
void Item::DropToFloor
	(
	Event *ev
	)

	{
   str fullname;
	Vector save;

	PlaceItem();

	setOrigin( origin + "0 0 1" );
	save = origin;
	if ( !droptofloor( 8192 ) )
		{
		gi.dprintf( "%s fell out of level at '%5.1f %5.1f %5.1f'\n", 
			getClassID(), origin.x, origin.y, origin.z );
		PostEvent( EV_Remove, 0 );
		return;
		}
   //
   // if the our global variable doesn't exist, lets zero it out
   //
   fullname = str( "playeritem_" ) + getClassname();
   if ( !gameVars.VariableExists( fullname.c_str() ) )
      {
      gameVars.SetVariable( fullname.c_str(), 0 );
      }

   if ( !levelVars.VariableExists( fullname.c_str() ) )
      {
      levelVars.SetVariable( fullname.c_str(), 0 );
      }

	setOrigin( save );
	groundentity = NULL;
	}

qboolean Item::Drop
	(
	void
	)

	{
	if ( !owner )
		{
		return false;
		}

	setOrigin( owner->worldorigin + "0 0 40" );

	// drop the item
	PlaceItem();
	velocity = owner->velocity * 0.5 + Vector( G_CRandom( 50 ), G_CRandom( 50 ), 100 );
	setAngles( owner->angles );
	avelocity = Vector( 0, G_CRandom( 360 ), 0 );

   trigger_time = level.time + 1;

	if ( owner->isClient() )
		{
		spawnflags |= DROPPED_PLAYER_ITEM;
		}
	else
		{
		spawnflags |= DROPPED_ITEM;
		}

   // Remove this from the owner's item list
   owner->RemoveItem( this );
	owner = NULL;

	return true;
	}


void Item::ItemTouch
	(
	Event *ev
	)

	{
	Entity	*other;
	Event		*e;

	if ( owner )
		{
		// Don't respond to trigger events after item is picked up.
		gi.dprintf( "%s with targetname of %s was triggered unexpectedly.\n", getClassID(), TargetName() );
		return;
		}

	other = ev->GetEntity( 1 );

	e = new Event( EV_Item_Pickup );
	e->AddEntity( other );
	ProcessEvent( e );
	}

void Item::SetOwner
	(
	Sentient *ent
	)

	{
	assert( ent );
	if ( !ent )
		{
		// return to avoid any buggy behaviour
		return;
		}

   owner = ent;
	setRespawn( false );

   edict->s.renderfx &= ~RF_GLOW;
	setSolidType( SOLID_NOT );
	hideModel();
	CancelEventsOfType( EV_Item_DropToFloor );
	CancelEventsOfType( EV_Remove );
//	ItemPickup( ent );
	}

Item * Item::ItemPickup
	(
	Entity *other
	)

	{
   Sentient * sent;
   Item * item;
	str realname;

   if ( !Pickupable( other ) )
		{
		return NULL;
		}

   sent = ( Sentient * )other;

   item = sent->giveItem( getClassname(), Amount(), icon_index );

   if ( !item )
      return NULL;

	realname = GetRandomAlias( "snd_pickup" );
   if ( realname.length() > 1 )
      sent->sound( realname, 1, CHAN_ITEM, ATTN_NORM );

	if ( !Removable() )
		{
		// leave the item for others to pickup
		return item;
		}

	CancelEventsOfType( EV_Item_DropToFloor );
	CancelEventsOfType( EV_Item_Respawn );
   CancelEventsOfType( EV_FadeOut );

	setSolidType( SOLID_NOT );
	hideModel();


	if ( Respawnable() )
		{
		PostEvent( EV_Item_Respawn, RespawnTime() );
		}
	else
		{
		PostEvent( EV_Remove, 0.1 );
		}

   if ( DM_FLAG( DF_INSTANT_ITEMS ) )
		{
      Event *ev;

      ev = new Event( EV_InventoryItem_Use );
      ev->AddEntity( other );

      item->ProcessEvent( ev );
		}

   return item;
	}

void Item::Respawn
	(
	Event *ev
	)

	{
	showModel();

	// allow it to be touched again
	setSolidType( SOLID_TRIGGER );

	// play respawn sound
   if ( playrespawn )
      {
   	RandomGlobalSound( "snd_itemspawn" );
      }

	setOrigin( origin );
	};

void Item::setRespawn
	( 
	qboolean flag 
	)

	{
	respawnable = flag;
	}

qboolean Item::Respawnable
	( 
	void 
	)

	{
	return respawnable;
	}

void Item::setRespawnTime
	( 
	float time 
	)

	{
	respawntime = time;
	}

float Item::RespawnTime
	( 
	void 
	)

	{
	return respawntime;
	}

int Item::Amount
   (
   void
   )

   {
   return amount;
   }

int Item::MaxAmount
   (
   void
   )

   {
   return maximum_amount;
   }

qboolean Item::Pickupable
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
      item = sent->FindItem( getClassname() );

      if ( item && ( item->Amount() >= item->MaxAmount() ) )
         {
         return false;
         }

      // Mutants can't pick up anything but health
      if ( other->flags & (FL_MUTANT|FL_SP_MUTANT) && !( this->isSubclassOf( Health ) ) )
         {
         return false;
         }

      // If deathmatch and already in a powerup, don't pickup anymore when DF_INSTANT_ITEMS is on
      if ( DM_FLAG( DF_INSTANT_ITEMS ) &&
           this->isSubclassOf( InventoryItem ) &&
           sent->PowerupActive()
         )
         {
         return false;
         }
      }
   return true;
   }

void Item::Pickup
	(
   Event * ev
	)

	{
	ItemPickup( ev->GetEntity( 1 ) );
   }

void Item::setIcon
   (
   const char *i
   )

   {
   icon_name = i;
   icon_index = gi.imageindex( i );
   }

void Item::setName
   (
   const char *i
   )

   {
   item_name = i;
   item_index = gi.itemindex( i );
   }

int Item::Icon
   (
   void
   )

   {
   if ( icon_name.length() )
      return icon_index;
   else
      return -1;
   }

void Item::Set
	(
	int startamount
	)

	{
   if ( !amount_override )
      {
      amount = startamount;
      if ( amount >= MaxAmount() )
         SetMax( amount );
      }
   }

void Item::SetMax
	(
	int maxamount
	)

	{
   maximum_amount = maxamount;
   }

void Item::SetAmount
	(
	Event *ev
	)

	{
	Set( ev->GetInteger( 1 ) );
   }

void Item::SetMaxAmount
	(
	Event *ev
	)

	{
	SetMax( ev->GetInteger( 1 ) );
   }

void Item::SetIconName
	(
	Event *ev
	)

	{
   setIcon( ev->GetString( 1 ) );
	}

void Item::SetItemName
	(
	Event *ev
	)

	{
   setName( ev->GetString( 1 ) );
	}

void Item::Add
	(
	int num
	)

	{
	amount += num;
   if ( amount >= MaxAmount() )
      amount = MaxAmount();
	}

void Item::Remove
   (
   int num
   )
   {
   amount -= num;
   if (amount < 0)
      amount = 0;
   }


qboolean Item::Use
	(
	int num
	)

	{
	if ( num > amount )
		{
		return false;
		}

	amount -= num;
	return true;
	}

qboolean Item::Removable
	( 
	void 
	)

	{
   return true;
	}

void Item::RespawnSound
	(
	Event *ev
	)

	{
   playrespawn = true;
   }

void Item::DialogNeeded
	(
	Event *ev
	)

	{
   //
   // if this item is needed for a trigger, play this dialog
   //
   dialog_needed = ev->GetString( 1 );
   }

str Item::GetDialogNeeded
	(
   void
	)

	{
   return dialog_needed;
   }
