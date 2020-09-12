//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/item.h                           $
// $Revision:: 24                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 3/02/99 9:16p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/item.h                                $
// 
// 24    3/02/99 9:16p Aldie
// Added CTF game code
// 
// 23    11/08/98 10:52p Jimdose
// amountoverride wasn't archived
// made icon_index and item_index be calculated in unarchive
// 
// 22    10/14/98 1:20a Jimdose
// Got cross-level persistant info working
// 
// 21    9/29/98 5:59p Markd
// Added dialog_needed stuff
// 
// 20    9/28/98 9:12p Markd
// Put in archive and unarchive functions
// 
// 19    9/01/98 7:47p Aldie
// Added itemname to inventory stuff
// 
// 18    8/29/98 7:23p Aldie
// Added itemname to get around targetname problem
// 
// 17    7/14/98 3:55p Markd
// Got rid of pickup_sound
// 
// 16    7/11/98 8:19p Jimdose
// Drop now returns true or false depending upon whether the item can be
// dropped or not
// 
// 15    6/26/98 11:29a Markd
// Changed what ItemPickup returns
// 
// 14    6/25/98 8:48p Markd
// Rewrote Item class, added keyed items to triggers, cleaned up item system
// 
// 13    6/24/98 1:38p Aldie
// Implementation of inventory system and picking stuff up
// 
// 12    6/19/98 6:38p Aldie
// Moved icon to inventory item
// 
// 11    6/18/98 9:26p Aldie
// Started inventory system
// 
// 10    6/17/98 1:16a Jimdose
// Moved setOwner to Item.  
// Added EV_Item_Pickup
// 
// 9     6/16/98 4:09p Jimdose
// Added DropToFloor 
// 
// 8     4/04/98 6:15p Jimdose
// Defined DROPPED_ITEM and DROPPED_PLAYER_ITEM
// 
// 7     3/23/98 1:33p Jimdose
// Revamped event and command system
// 
// 6     3/02/98 8:49p Jimdose
// Changed CLASS_PROTOTYPE to only take the classname
// 
// 5     2/19/98 2:35p Jimdose
// Updated to work with Q2 based progs
// 
// 3     10/27/97 2:59p Jimdose
// Removed dependency on quakedef.h
// 
// 2     9/26/97 5:30p Jimdose
// Added standard Ritual headers
//
// DESCRIPTION:
// Base class for respawnable, carryable objects.
// 

#ifndef __ITEM_H__
#define __ITEM_H__

#include "g_local.h"
#include "entity.h"
#include "trigger.h"
#include "sentient.h"

extern Event EV_Item_Pickup;
extern Event EV_Item_DropToFloor;
extern Event EV_Item_Respawn;
extern Event EV_Item_SetAmount;
extern Event EV_Item_SetMaxAmount;
extern Event EV_Item_SetIconName;
extern Event EV_Item_RespawnSound;
extern Event EV_Item_DialogNeeded;

#define DROPPED_ITEM					0x00008000
#define DROPPED_PLAYER_ITEM		0x00010000

class EXPORT_FROM_DLL Item : public Trigger
	{
	protected:
		SentientPtr			owner;
		qboolean				respawnable;
      qboolean          playrespawn;
		float					respawntime;
      str               icon_name;
      str               dialog_needed;
      str               item_name;
      int               icon_index;
      int               item_index;
      int               maximum_amount;
		int	            amount;
      qboolean          amount_override;


		void					ItemTouch( Event *ev );
   
	public:
      str               itemname;

      CLASS_PROTOTYPE( Item );

								Item::Item();
								Item::~Item();
		virtual void      CreateSpawnArgs( void );
		virtual void		PlaceItem( void );
		virtual void		SetOwner( Sentient *ent );
		virtual void		DropToFloor( Event *ev );
		virtual Item      *ItemPickup( Entity *other );
		virtual void		Respawn( Event *ev );
		virtual void		setRespawn( qboolean flag );
		virtual qboolean	Respawnable( void );
		virtual void		setRespawnTime( float time );
		virtual float		RespawnTime( void );
      virtual int       GetIconIndex( void ) { return icon_index; };
      virtual int       GetItemIndex( void ) { return item_index; };
      virtual int       Amount( void );
      virtual int       MaxAmount( void );
      virtual int       Icon( void );
      virtual qboolean  Pickupable( Entity *other );
      virtual void      setIcon( const char *i );
      virtual void      setName( const char *i );
      virtual void      SetAmount( Event *ev );
      virtual void      SetMaxAmount( Event *ev );
      virtual void      SetIconName( Event *ev );
      virtual void      SetItemName( Event *ev );
      virtual void      Set( int startamount	);
      virtual void      SetMax( int maxamount );
		virtual void		Add( int num );
      virtual void      Remove( int num );
		virtual qboolean	Use( int amount );
		virtual qboolean	Removable( void );
      virtual void      Pickup( Event *ev );
      virtual qboolean	Drop( void );
      virtual void      RespawnSound( Event *ev );
      virtual void      DialogNeeded( Event *ev );
      virtual str       GetDialogNeeded( void );
		virtual void      ClearOwner( void ){ owner = NULL; }
	   virtual void      Archive( Archiver &arc );
      virtual void      Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Item::Archive
	(
	Archiver &arc
	)
   {
   Trigger::Archive( arc );

   arc.WriteSafePointer( owner );
   arc.WriteBoolean( respawnable );
   arc.WriteBoolean( playrespawn );
   arc.WriteFloat( respawntime );
   arc.WriteString( icon_name );
   arc.WriteString( dialog_needed );
   arc.WriteString( item_name );
   arc.WriteInteger( maximum_amount );
   arc.WriteInteger( amount );
   arc.WriteBoolean( amount_override );
   arc.WriteString( itemname );
   }

inline EXPORT_FROM_DLL void Item::Unarchive
	(
	Archiver &arc
	)
   {
   Trigger::Unarchive( arc );

   arc.ReadSafePointer( &owner );
   arc.ReadBoolean( &respawnable );
   arc.ReadBoolean( &playrespawn );
   arc.ReadFloat( &respawntime );

   arc.ReadString( &icon_name );
   icon_index = gi.imageindex( icon_name.c_str() );

   arc.ReadString( &dialog_needed );

   arc.ReadString( &item_name );
   item_index = gi.itemindex( item_name.c_str() );

   arc.ReadInteger( &maximum_amount );
   arc.ReadInteger( &amount );
   arc.ReadBoolean( &amount_override );
   arc.ReadString( &itemname );
   }

#endif /* item.h */
