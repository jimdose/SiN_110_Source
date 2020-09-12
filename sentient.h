//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/sentient.h                       $
// $Revision:: 71                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 3/02/99 9:16p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/sentient.h                            $
// 
// 71    3/02/99 9:16p Aldie
// Added CTF game code
// 
// 2     2/16/99 4:09p Aldie
// 
// 1     2/11/99 1:39p Aldie
// 
// 70    11/16/98 8:59p Markd
// Added TakeItem event to header
// 
// 69    11/13/98 10:21p Aldie
// Added event take item
// 
// 68    11/09/98 6:22p Markd
// Added dropweaponnow event
// 
// 67    10/26/98 8:48p Jimdose
// exported EV_Sentient_WeaponUse and EV_Sentient_SetDropWeapon
// 
// 66    10/25/98 11:53p Jimdose
// added EXPORT_TEMPLATE
// 
// 65    10/22/98 2:38a Aldie
// Added setdropweapon command for sentients
// 
// 64    10/20/98 11:23p Jimdose
// added ignore to BestWeapon
// 
// 63    10/20/98 8:06p Aldie
// Added a DoGib function to ease readability
// 
// 62    10/18/98 6:42p Markd
// Added WeaponKnockedFromHands method
// 
// 61    10/16/98 3:10a Aldie
// Added armordouble
// 
// 60    10/14/98 1:33a Jimdose
// Got cross-level persitant data working
// 
// 59    10/11/98 8:58p Aldie
// Moved fields to sentient
// 
// 58    10/10/98 5:58p Aldie
// More quantumdestab fixes
// 
// 57    10/04/98 10:28p Aldie
// Added multiple weapon changes.  Damage, flashes, quantum stuff
// 
// 56    10/03/98 7:27p Markd
// working on swimming character and redid some weapon aiming stuff
// 
// 55    9/22/98 12:15p Aldie
// Added sentientFrozen
// 
// 54    9/21/98 6:05p Markd
// added archive and unarchive functions
// 
// 53    9/21/98 1:55a Aldie
// Moved some vars to sentient
// 
// 52    9/18/98 9:55p Markd
// Added noshadow event
// 
// 51    9/11/98 2:50p Aldie
// Added releasefiring functionality
// 
// 50    9/02/98 11:08a Markd
// Put in setModel into Sentient so that weapon could be properly detached and
// re-attached again.
// 
// 49    8/31/98 5:46p Aldie
// Powerup timer stuff
// 
// 48    8/31/98 1:55p Markd
// weapons no longer double trigger animations
// 
// 47    8/29/98 7:24p Aldie
// Added a givetargetname function
// 
// 46    8/29/98 5:55p Jimdose
// Moved prototype of ResetBloodSplats into sentient.h
// 
// 45    8/29/98 2:53p Aldie
// Updated printing of location based damage
// 
// 44    8/27/98 6:00p Aldie
// Drop inventory items if the actors are gibbed.
// 
// 43    8/14/98 5:48p Aldie
// Moved bloodsplats to sentient
// 
// 42    8/12/98 4:20p Aldie
// Fixed icons not showing up correctly
// 
// 41    7/31/98 4:20p Jimdose
// Externed a few events
// 
// 40    7/25/98 2:11a Jimdose
// Added SentientList
// 
// 39    7/24/98 6:16p Aldie
// Added check for inventory items
// 
// 38    7/24/98 4:13p Aldie
// Externed an event
// 
// 37    7/24/98 3:50p Aldie
// added uselesscheck
// 
// 36    7/19/98 5:42p Markd
// Added TakeItem support
// 
// 35    7/19/98 5:21p Markd
// Added ForceChangeWeapon
// 
// 34    7/17/98 4:04p Markd
// Added CanChangeWeapons
// 
// 33    7/14/98 6:59p Aldie
// Updated health
// 
// 32    6/25/98 8:48p Markd
// Rewrote Item class, added keyed items to triggers, cleaned up item system
// 
// 31    6/25/98 12:43p Aldie
// Added a method to get the number of inventory items
// 
// 30    6/24/98 1:39p Aldie
// Implementation of inventory system and picking stuff up
// 
// 29    6/20/98 7:50p Markd
// Added gun_bone_group_name variable
// 
// 28    6/19/98 9:28p Jimdose
// Added GetGunOrientation
// 
// 27    6/19/98 6:39p Aldie
// Updated item stuff
// 
// 26    6/18/98 9:29p Aldie
// Started inventory system
// 
// 25    6/17/98 1:18a Jimdose
// Changed attack to FireWeapon
// Removed include of item.h
// 
// 24    6/15/98 9:12p Aldie
// Made a give generic and an function that updates silenced weapons
// 
// 23    6/10/98 2:10p Aldie
// Updated damage function.
// 
// 22    6/05/98 6:27p Aldie
// Added armor stuff
// 
// 21    5/26/98 4:46p Aldie
// added take functions
// 
// 20    5/20/98 6:38p Jimdose
// Made anim functions use const char *
// 
// 19    5/13/98 4:53p Jimdose
// now uses SafePtrs
// 
// 18    4/07/98 6:47p Jimdose
// Rewrote weapon code
// 
// 17    3/30/98 2:38p Jimdose
// Added Ammo
// Added weapon dropping
// 
// 16    3/29/98 10:01p Jimdose
// Added animation control functions
// 
// 15    3/27/98 5:38p Jimdose
// Added FreeInventory
// 
// 14    3/23/98 1:33p Jimdose
// Revamped event and command system
// 
// 13    3/18/98 7:23p Jimdose
// Added code for handling readying and putting away weapons
// 
// 12    3/02/98 8:49p Jimdose
// Changed CLASS_PROTOTYPE to only take the classname
// 
// 11    3/02/98 5:38p Jimdose
// Added destructor.
// Changed Container to a template
// 
// 10    2/19/98 2:36p Jimdose
// Added weapons back in
// 
// 9     2/17/98 6:58p Jimdose
// no longer pass script into interpretCommand
// 
// 8     2/03/98 10:51a Jimdose
// Updated to work with Quake 2 engine
// Moved initialization to constructor and removed Init function
// 
// 6     12/09/97 7:41p Markd
// Added NumWeapons and WeaponNumber functions
// 
// 5     11/15/97 6:54p Markd
// Added InterpretCommand
// 
// 4     11/12/97 5:12p Jimdose
// Added event definitions
// 
// 3     10/27/97 2:59p Jimdose
// Removed dependency on quakedef.h
// 
// 2     9/26/97 6:47p Jimdose
// Added standard Ritual headers
//
// DESCRIPTION:
// Base class of entity that can carry other entities, and use weapons.
//

#ifndef __SENTIENT_H__
#define __SENTIENT_H__

#include "g_local.h"
#include "entity.h"
#include "container.h"

extern Event EV_Sentient_Attack;
extern Event EV_Sentient_ReleaseAttack;
extern Event EV_Sentient_GiveWeapon;
extern Event EV_Sentient_GiveAmmo;
extern Event EV_Sentient_TakeAmmo;
extern Event EV_Sentient_GiveArmor;
extern Event EV_Sentient_TakeArmor;
extern Event EV_Sentient_TakeItem;
extern Event EV_Sentient_GiveItem;
extern Event EV_Sentient_GiveInventoryItem;
extern Event EV_Sentient_GiveHealth;
extern Event EV_Sentient_WeaponPutAway;
extern Event EV_Sentient_WeaponReady;
extern Event EV_Sentient_WeaponDoneFiring;
extern Event EV_Sentient_AnimLoop;
extern Event EV_Sentient_UselessCheck;
extern Event EV_Sentient_TurnOffShadow;
extern Event EV_Sentient_Freeze;
extern Event EV_Sentient_UnFreeze;
extern Event EV_Sentient_ImpactDamage;
extern Event EV_Sentient_WeaponUse;
extern Event EV_Sentient_SetDropWeapon;

// Shutup compiler
class Weapon;
class Item;
class InventoryItem;

class EXPORT_FROM_DLL Sentient : public Entity
	{
	private:
		Container<int>		inventory;

	protected:
		Weapon				*currentWeapon;
      InventoryItem     *currentItem;
		Weapon				*newWeapon;
		str               currentAnim;
		qboolean				animOverride;
		Event					*tempAnimEvent;
      str               gun_bone_group_name;
      qboolean          stopanimating_tillchange;
      int               poweruptype;      
      int               poweruptimer;
      qboolean          sentientFrozen;
      qboolean          dropweapon;

		virtual void		EventGiveWeapon( Event *ev );
      virtual void		EventTakeWeapon( Event *ev );
		virtual void		EventGiveAmmo( Event *ev );
      virtual void		EventTakeAmmo( Event *ev );
      virtual void		EventGiveArmor( Event *ev );
      virtual void		EventTakeArmor( Event *ev );
      virtual void		EventGiveItem( Event *ev );
      virtual void		EventGiveHealth( Event *ev );
      virtual void		EventGiveInventoryItem( Event *ev );
      virtual void		EventGiveTargetname( Event *ev );
      virtual void		EventTakeItem( Event *ev );
		virtual void		WeaponPutAway( Event *ev );
		virtual void		WeaponReady( Event *ev );
		virtual void		WeaponDoneFiring( Event *ev );
		virtual void		AnimLoop( Event *ev );
      virtual void      ArmorDamage( Event *ev );
      virtual void      TurnOffShadow( Event *ev );
      virtual void      Freeze( Event *ev );
      virtual void      UnFreeze( Event *ev );
		virtual void      WeaponKnockedFromHands( void );

	public:
		Vector				gunoffset;
		Vector				eyeposition;

      // Weapon charging stuff
      float             firedowntime;
      qboolean          firedown;
      qboolean          usedown;

      str               saveskin;
      str               savemodel;

      CLASS_PROTOTYPE( Sentient );

								Sentient();
		virtual				~Sentient();
      virtual void      RestorePersistantData( SpawnArgGroup &group );
      virtual void      WritePersistantData( SpawnArgGroup &group );
		Vector				EyePosition( void );
		virtual Vector		GunPosition( void );
		virtual void		GetGunOrientation( Vector pos, Vector *forward, Vector *right, Vector *up );
      virtual Item      *giveItem( const char * itemname, int amount, int icon_index = -1 );
		virtual void		FireWeapon( Event *ev );
      virtual void		ReleaseFireWeapon( Event *ev );
		virtual void		AddItem( Item *object );
		virtual void		RemoveItem( Item *object );
		virtual Item		*FindItem( const char *itemname );
		virtual void		FreeInventory( void );
      virtual void		FreeInventoryOfType( const char *weaptype );
		virtual qboolean	HasItem( const char *itemname );
		virtual void		ForceChangeWeapon( Weapon *weapon );
		virtual void		ChangeWeapon( Weapon *weapon );
		virtual void		SetCurrentWeapon( Weapon *weapon );
		virtual Weapon		*CurrentWeapon( void );
		virtual Weapon		*BestWeapon( Weapon *ignore = NULL );
		virtual Weapon		*NextWeapon( Weapon *weapon );
		virtual Weapon		*PreviousWeapon( Weapon *weapon );
		virtual qboolean	WeaponReady( void );
		virtual void		DropWeapon( Weapon *weapon );
		virtual void		DropCurrentWeapon( void );
		virtual Weapon		*giveWeapon( const char *weaponname );
      virtual void		takeWeapon( const char *weaponname );
      virtual void		takeItem( const char *weaponname, int amount );
		virtual Weapon		*useWeapon( const char *weaponname );
      virtual int       NumWeapons( void );
      virtual Weapon    *WeaponNumber( int weaponnum );
		virtual void		SetAnim( const char *anim );
		virtual void		TempAnim( const char *anim, Event *event );
		virtual void		TempAnim( const char *anim, Event &event );
      virtual void      UpdateSilencedWeapons( void );
      virtual int       NumInventoryItems( void );
      virtual Item      *NextItem( Item *item );
      virtual Item      *PrevItem( Item *item );
      virtual void      SearchBody( Event *ev );
      virtual qboolean  CanChangeWeapons( void );
      virtual void      UselessCheck( Event *ev );
      virtual qboolean  HasInventoryOfType( const char * );
      virtual void      DropInventoryItems( void );
              void      SprayBlood( Vector src, Vector dir, float damage );
              void      PrintDamageLocationToAttacker( edict_s *attacker, const char *victim_name, const char *location );
              void      PrintDamageLocationToVictim( edict_s *victim, const char *location );
              qboolean  PowerupActive( void );
		virtual void		setModel( const char *model );
		virtual void		setModel( str &mdl );
      virtual void      Archive( Archiver &arc );
      virtual void      Unarchive( Archiver &arc );
      virtual void      ImpactDamage( Event *ev );
      virtual void      WeaponUse( Event *ev );
              void      GetMuzzlePositionAndDirection( Vector *pos, Vector *dir);
              void      DoubleArmor( void );
      virtual qboolean  DoGib( int meansofdeath, Entity *inflictor );
      virtual void      SetDropWeapon( Event *ev );
      virtual void      DropWeaponNowEvent( Event *ev );

      // CTF
      virtual Item      *HasItemOfSuperclass( const char *superclassname );
   };

inline EXPORT_FROM_DLL void Sentient::setModel
	(
	str &mdl
	)

	{
	setModel( mdl.c_str() );
	}


#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL SafePtr<Sentient>;
template class EXPORT_FROM_DLL Container<Sentient *>;
#endif

typedef SafePtr<Sentient> SentientPtr;

extern Container<Sentient *> SentientList;

void EXPORT_FROM_DLL ResetBloodSplats( void );

#endif /* sentient.h */
