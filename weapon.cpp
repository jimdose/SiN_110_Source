//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/weapon.cpp                       $
// $Revision:: 147                                                            $
//   $Author:: Markd                                                          $
//     $Date:: 7/24/99 5:45p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/weapon.cpp                            $
// 
// 147   7/24/99 5:45p Markd
// Added No Weapon Change Deathmatch bug
// 
// 146   4/16/99 5:01p Aldie
// Added takeallammo
// 
// 145   3/12/99 7:49p Jimdose
// made weapons fire 1/10th of a second sooner on clients
// 
// 144   3/02/99 9:16p Aldie
// Added CTF game code
// 
// 2     2/16/99 4:09p Aldie
// 
// 1     2/11/99 1:40p Aldie
// 
// 143   12/16/98 5:43p Jimdose
// infiniterockets no longer gives infinite mines
// 
// 142   12/14/98 7:00p Jimdose
// added sv_infinitesniper
// 
// 141   12/09/98 8:06p Jimdose
// added infinite ammo vars
// 
// 140   11/19/98 9:29p Jimdose
// fixed dropping weapons when on different gravaxis
// 
// 139   11/18/98 12:21a Jimdose
// Fixed gravaxis stuff.
// 
// 138   11/15/98 11:19p Jimdose
// Fixed bug where reloading only worked if you had less ammo in your clip than
// in your inventory
// 
// 137   11/13/98 1:47a Markd
// Put in FL_ROTATEDBOUNDS modification when picked up and then dropped
// 
// 136   11/07/98 10:46p Markd
// don't reload weapons while in cinematic
// 
// 135   10/22/98 7:57p Markd
// put in proper pre-caching in all the classes
// 
// 134   10/22/98 12:19a Jimdose
// Added aimanim and aimframe
// Added SetAimAnim
// 
// 133   10/21/98 5:29p Aldie
// Moved around mutant checks for picking up weapons
// 
// 132   10/21/98 1:30a Jimdose
// DoneReloading now sends a weapon ready event to sentient
// 
// 131   10/20/98 8:23p Jimdose
// no longer pickup weapons when you already have that weapon and enough ammo
// no longer switch to weapon when picking up if you already have it
// 
// 130   10/19/98 12:07a Jimdose
// made all code use fast checks for inheritance (no text lookups when
// possible)
// isSubclassOf no longer requires ::_classinfo()
// moved Magnum-specific Drop code to magnum.cpp
// 
// 129   10/18/98 6:42p Markd
// Added notdroppable event to weapons
// 
// 128   10/16/98 9:50p Aldie
// Added SecondaryAmmo command
// 
// 127   10/16/98 12:59a Aldie
// Fixed ammo types
// 
// 126   10/14/98 1:46a Markd
// Moved RandomGlobalSound to null out weaponidle before detach
// 
// 125   10/14/98 1:20a Jimdose
// Got cross-level persistant info working
// 
// 124   10/11/98 7:41p Aldie
// Mutate and restore commands for Richard
// 
// 123   10/10/98 5:58p Aldie
// More quantumdestab fixes
// 
// 122   10/09/98 2:07a Aldie
// Updated DMFLAGS
// 
// 121   10/08/98 5:47p Aldie
// Be able to pickup up dropped weapons in DF_WEAPONSSTAY mode
// 
// 120   10/08/98 12:36a Jimdose
// Added ForceIdle
// 
// 119   10/06/98 5:24p Markd
// put in bullet-proofing of owner variable
// 
// 118   10/05/98 10:43p Aldie
// Converted over to new silencer methods
// 
// 117   10/04/98 10:25p Markd
// Took out annoying warning, made the trace for gun position to muzzle
// position more bullet proof
// 
// 116   10/03/98 7:14p Markd
// fixed muzzle position stuff
// 
// 115   10/01/98 8:00p Aldie
// Don't pickup a weapon when mutant
// 
// 114   9/19/98 4:47p Markd
// fixed music stuff and added actionincrement to weapons
// 
// 113   9/12/98 11:10p Aldie
// Don't detach in putaway
// 
// 112   9/12/98 5:16p Jimdose
// Added call to DetachGun in PutAway
// 
// 111   9/09/98 6:24p Markd
// Added IsDroppable method
// 
// 110   9/07/98 7:49p Markd
// went back to previous attaching of weapons
// 
// 109   9/07/98 6:21p Markd
// don't attach if no worldmodel
// 
// 108   9/05/98 12:13p Aldie
// Fixed a bug that 2015 found.
// 
// 107   9/02/98 11:08a Markd
// Put in setModel into Sentient so that weapon could be properly detached and
// re-attached again.
// 
// 106   8/31/98 7:45p Aldie
// Updated surface data structure and removed surfinfo field
// 
// 105   8/31/98 4:19p Markd
// Made GetMuzzlePosition behave a bit more rationally.
// 
// 104   8/29/98 9:47p Jimdose
// Added call info to G_Trace
// 
// 103   8/29/98 5:27p Markd
// added specialfx, replaced misc with specialfx where appropriate
// 
// 102   8/19/98 4:56p Jimdose
// Added check for "gun" bone to MuzzleOffset
// 
// 101   8/18/98 8:12p Aldie
// Added dual mode weapons to base class
// 
// 100   8/18/98 7:39p Aldie
// Added dual weapon modes to base class
// 
// 99    8/14/98 5:48p Aldie
// Removed bloodsplat completely from weapon
// 
// 98    8/13/98 7:29p Aldie
// Fixed magnum dropping when it gets shot out of your hand.
// 
// 97    8/10/98 6:53p Aldie
// Added a better scaling for bloodsplats.
// 
// 96    8/06/98 10:53p Aldie
// Added weapon tweaks and kickback.  Also modified blast radius damage and
// rocket jumping.
// 
// 95    8/06/98 6:54p Jimdose
// Added min/max range, and projkectile speed
// 
// 94    7/26/98 2:13p Aldie
// Don't put bulletholes on hidden objects
// 
// 93    7/26/98 9:22a Jimdose
// Bulletholes are now bound to entities
// 
// 92    7/25/98 6:35p Aldie
// Bulletholes only in single player
// 
// 91    7/24/98 3:50p Aldie
// Fix for deathmatch flag weapons staying around
// 
// 90    7/22/98 9:58p Markd
// Added Raising, PuttingAway and Reloading functions
// 
// 89    7/22/98 8:18p Aldie
// Made sure reloading only happens when weapon is ready.
// 
// 88    7/22/98 7:03p Aldie
// Fixed reloading while reloading :-)
// 
// 87    7/22/98 5:16p Aldie
// Fixed NextAttack time
// 
// 86    7/20/98 6:43p Markd
// Put in new muzzle offset stuff
// 
// 85    7/20/98 3:54p Aldie
// Made weapons post the init commands in the future.
// 
// 84    7/19/98 5:41p Markd
// Added DetachFromOwner method
// 
// 83    7/17/98 4:04p Markd
// Added HasAnim support to putaway and ready
// 
// 82    7/17/98 11:32a Aldie
// Added clipammo and forcereload stuff
// 
// 81    7/15/98 9:59p Markd
// Made muzzle flashes into TEMP_DLIGHT's
// 
// 80    7/14/98 6:58p Aldie
// Made dropped weapons fade out
// 
// 79    7/14/98 5:52p Aldie
// Don't drop magnums in deathmatch.  Made the delay to pick up dropped weapons
// a little longer for the owner.
// 
// 78    7/14/98 3:54p Markd
// made weapons cycle through their models when spawning
// 
// 77    7/12/98 7:27p Jimdose
// Removed code setting scale and frame
// 
// 76    7/11/98 8:20p Jimdose
// Drop now returns true or false depending upon whether the item can be
// dropped or not
// 
// 75    7/10/98 5:39p Aldie
// Fixed printf of a warning
// 
// 74    7/10/98 12:06a Aldie
// Autochange override when you pickup a new weapon.  Currently only the
// sniperrifle will not be putaway if you are using it.
// 
// 73    7/09/98 10:41p Aldie
// If no barrel in weapon, look for barrel bone in owner
// 
// 72    7/01/98 7:04p Aldie
// Fixed assert with weapon reloading after death
// 
// 71    6/26/98 12:24p Markd
// Changed SetAmmoAmount fixed picking upweapons
// 
// 70    6/26/98 11:30a Markd
// Fixed weapon pickup bug
// 
// 69    6/25/98 8:47p Markd
// Added keyed items for Triggers, Rewrote Item class, rewrote every pickup
// method
// 
// 68    6/25/98 12:43p Aldie
// Changed bloodsplat scale and made a triggerdelay for dropping weapons
// 
// 67    6/24/98 1:38p Aldie
// Implementation of inventory system and picking stuff up
// 
// 66    6/19/98 9:28p Jimdose
// Added general weapon muzzle code
// 
// 65    6/17/98 1:20a Jimdose
// Moved setOwner to Item.  
// Added EV_Item_Pickup
// 
// 64    6/16/98 4:08p Jimdose
// Gave dropping weapons velocity
// 
// 63    6/15/98 10:39a Aldie
// Created MuzzleOffset derived from MuzzlePosition
// 
// 62    6/11/98 12:40a Markd
// Added BasePosition and MuzzlePosition
// 
// 61    6/10/98 9:49p Markd
// Made Finish attack set attack_finished to level.time not 0
// 
// 60    6/10/98 7:45p Aldie
// Updated some reload functions.
// 
// 59    6/10/98 3:46p Markd
// replaced instance of AmmoAvailable with HasAmmor to make monsters work right
// 
// 58    6/10/98 2:10p Aldie
// Updated damage function.
// 
// 57    6/10/98 1:18p Markd
// Added SetAmmoClipSize event removed NextAttack(0) from AttackDone
// 
// 56    6/09/98 7:37p Markd
// Put in "0" ammo_clip_size support
// 
// 55    6/09/98 3:58p Markd
// Fixed bug with double pickup of ammos from dropped guns
// 
// 54    6/09/98 12:54p Aldie
// Updated ReadyToFire function
// 
// 53    6/08/98 8:39p Markd
// Fixed some reload issues
// 
// 52    6/08/98 8:19p Markd
// Added reloading support and ReadyToUse function
// 
// 51    6/08/98 5:43p Markd
// removed "shoot" command from Fire function
// 
// 50    6/05/98 6:21p Markd
// When picking up weapons, ammo is given if you already have that weapon
// 
// 49    6/05/98 6:26p Aldie
// Added location to apply multi damage
// 
// 48    6/04/98 7:36p Jimdose
// Drop now posts EV_Item_DropToFloor instead of processing it.
// 
// 47    6/03/98 4:39p Markd
// Removed dummy weapon, there is now just a single weapon that gets sent over
// 
// 46    5/27/98 5:03a Aldie
// Added queue for bulletsplats
// 
// 45    5/27/98 3:20a Markd
// zeroed out animations for dropped weapons
// 
// 44    5/27/98 2:33a Markd
// When dropping weapons, made sure to zero out the anim and frame for the
// weapon
// 
// 43    5/25/98 8:51a Aldie
// Fixed sprayblood with masked textures
// 
// 42    5/25/98 6:52a Aldie
// Added maxbulletholes to stop from overflowing.
// 
// 41    5/24/98 8:46p Jimdose
// Made a lot of functions more str-friendly.
// Got rid of a lot of char * based strings
// Cleaned up get spawn arg functions and sound functions
// sound functions now use consistant syntax
// 
// 40    5/24/98 1:05a Jimdose
// Changed worldmodel, viewmodel, and ammotype to str objects
// Added sound events for ai
// 
// 39    5/23/98 10:20p Aldie
// Made some changes to bulletholes to try to get them to work with ents, but
// no luck.
// 
// 38    5/23/98 4:48p Aldie
// Added bulletholes
// 
// 37    5/14/98 4:27p Markd
// Fixed NULL weapon model issue
// 
// 36    5/13/98 4:55p Jimdose
// now uses SafePtrs
// got rid of weapon_owner.  replaced with owner which is a SafePtr.
// 
// 35    5/11/98 11:25a Markd
// Changed some worldmodel stuff
// 
// 34    5/03/98 4:34p Jimdose
// Changed Vector class
// 
// 33    4/14/98 9:58p Jimdose
// Made SetModels set the dummy model if it exists
// 
// 32    4/10/98 12:36a Jimdose
// Fire now cancels EV_Weapon_DoneFiring
// 
// 31    4/09/98 3:30p Jimdose
// Added gettype and settype
// added sound so that anim sounds play from the owner
// 
// 30    4/08/98 4:55p Jimdose
// Made ShowDummyOnClient and HideDummyOnClient check if dummy is NULL
// Fixed the bug with weapons not being shown on monsters.  The dummy's origin
// was non 0,0,0
// 
// 29    4/08/98 4:46p Jimdose
// Added ShowDummyOnClient and HideDummyOnClient
// 
// 28    4/07/98 8:19p Jimdose
// Made assaultrifle fire at normal speed
// 
// 27    4/07/98 8:00p Markd
// removed defhandle, changed all SINMDL calls to modelindex calls, removed
// SINMDL prefix
// 
// 26    4/07/98 6:45p Jimdose
// Rewrote weapon code.
// Fixed weapon switching bugs
// fixed crash from freeing weapons at level changes
// Added order to rank
// 
// 25    4/06/98 7:10p Aldie
// Added zooming for SniperRifle
// 
// 24    4/05/98 11:17p Jimdose
// No longer see the gun lerping around
// 
// 23    4/05/98 5:29p Jimdose
// Weapon attaching is back in (previous bug was probably related to not
// freeing the ents after a map change...go figure).
// 
// 22    4/04/98 7:28p Jimdose
// Can't spray blood against sky anymore
// 
// 21    4/04/98 6:11p Jimdose
// Made response from EV_Trigger_ActivateTargets to EV_Trigger_Effect
// Added attachable guns (currently disabled)
// 
// 20    4/02/98 4:53p Jimdose
// Added AmmoAvailable
// Made SprayBlood work
// Added check for valid owner in AnimateFlash
// 
// 19    3/31/98 1:05a Jimdose
// Made monsters always have ammo
// 
// 18    3/30/98 2:35p Jimdose
// Added Ammo
// Added world models
// 
// 17    3/27/98 11:03p Jimdose
// Added muzzle flash
// 
// 16    3/26/98 8:17p Jimdose
// Temporarily disabled spray blood function
// 
// 15    3/23/98 1:31p Jimdose
// Revamped event and command system
// 
// 14    3/18/98 7:24p Jimdose
// Added code for handling readying and putting away weapons
// Made work with new animation system
// 
// 13    3/02/98 8:49p Jimdose
// Changed the classid parameter of CLASS_DECLARATION to a quoted string so
// that you could have a NULL classid.
// 
// 12    3/02/98 5:36p Jimdose
// Fixed setOwner so that it handles NULL being passed in when entites are
// freed or when the weapon is dropped.
// 
// 11    2/19/98 2:35p Jimdose
// Updated to work with Q2 based progs
// 
// 9     12/15/97 12:04p Aldie
// Fixed error message from coming up when checking for reload animations when
// there was none (I.e. Melee weapons).
// 
// 8     12/14/97 7:49p Jimdose
// Fixed bug where if a weapon didn't have a "reload" animation, every other
// time the player tried to fire would fail.
// 
// 7     12/12/97 2:10p Markd
// Changed NextAttacks in CheckReload and Fire to 1 second instead of 5
// 
// 6     12/11/97 3:31p Markd
// Added SprayBlood function
// 
// 5     12/09/97 7:46p Markd
// Added range variable.  Added different behavior when firing...if there is no
// model, then go ahead and shoot right away
// 
// 4     11/18/97 5:28p Markd
// Put in CheckTwitch, CheckIdle, put in clip support and other goodies
// 
// 3     10/27/97 3:30p Jimdose
// Removed dependency on quakedef.h
// 
// 2     9/26/97 4:46p Jimdose
// Added standard Ritual header
//
// DESCRIPTION:
// Source file for Weapon class.  The weapon class is the base class for
// all weapons in Sin.  Any entity created from a class derived from the weapon
// class will be usable by any Sentient (players and monsters) as a weapon.
// 

#include "g_local.h"
#include "entity.h"
#include "item.h"
#include "weapon.h"
#include "scriptmaster.h"
#include "sentient.h"
#include "misc.h"
#include "specialfx.h"
#include "chaingun.h"
#include "assaultrifle.h"

#ifdef SIN_ARCADE
static ScriptVariablePtr sv_infinitebullets;
static ScriptVariablePtr sv_infiniterockets;
static ScriptVariablePtr sv_infiniteplasma;
static ScriptVariablePtr sv_infinitespears;
static ScriptVariablePtr sv_infinitesniper;
#endif

CLASS_DECLARATION( Item, Weapon, NULL );

Event EV_Weapon_Shoot( "shoot" );
Event EV_Weapon_FinishAttack( "attack_finished" );
Event EV_Weapon_DoneLowering( "putaway" );
Event EV_Weapon_DoneRaising( "ready" );
Event EV_Weapon_DoneFiring( "donefiring" );
Event EV_Weapon_Idle( "idle" );
Event	EV_Weapon_MuzzleFlash( "muzzleflash" );
Event	EV_Weapon_SecondaryUse( "secondaryuse" );
Event	EV_Weapon_DoneReloading( "donereloading" );
Event EV_Weapon_SetAmmoClipSize( "ammoclipsize" );
Event EV_Weapon_ProcessModelCommands( "process_mdl_cmds" );
Event EV_Weapon_SetMaxRange( "maxrange" );
Event EV_Weapon_SetMinRange( "minrange" );
Event EV_Weapon_SetProjectileSpeed( "projectilespeed" );
Event EV_Weapon_SetKick( "kick" );
Event EV_Weapon_PrimaryMode( "primarymode" );
Event EV_Weapon_SecondaryMode( "secondarymode" );
Event EV_Weapon_ActionIncrement( "actionincrement" );
Event EV_Weapon_PutAwayAndRaise( "putawaythenraise" );
Event EV_Weapon_Raise( "raise" );
Event EV_Weapon_NotDroppable( "notdroppable" );
Event EV_Weapon_SetAimAnim( "setaimanim" );

ResponseDef Weapon::Responses[] =
	{
	   { &EV_Item_Pickup,			         ( Response )Weapon::PickupWeapon },
	   { &EV_Weapon_FinishAttack,	         ( Response )Weapon::FinishAttack },
	   { &EV_Weapon_DoneLowering,	         ( Response )Weapon::DoneLowering },
	   { &EV_Weapon_DoneRaising,	         ( Response )Weapon::DoneRaising },
		{ &EV_Weapon_DoneFiring,	         ( Response )Weapon::DoneFiring },
	   { &EV_Weapon_Idle,			         ( Response )Weapon::Idle },
		{ &EV_Weapon_MuzzleFlash,           ( Response )Weapon::EventMuzzleFlash },
		{ &EV_WeaponSound,		         	( Response )Weapon::WeaponSound },
	   { &EV_Weapon_DoneReloading,         ( Response )Weapon::DoneReloading },
      { &EV_Weapon_SetAmmoClipSize,       ( Response )Weapon::SetAmmoClipSize },
      { &EV_Weapon_ProcessModelCommands,  ( Response )Weapon::ProcessWeaponCommandsEvent },
		{ &EV_Weapon_SetMaxRange,				( Response )Weapon::SetMaxRangeEvent },
		{ &EV_Weapon_SetMinRange,				( Response )Weapon::SetMinRangeEvent },
		{ &EV_Weapon_SetProjectileSpeed,		( Response )Weapon::SetProjectileSpeedEvent },
      { &EV_Weapon_SetKick,         		( Response )Weapon::SetKick },
      { &EV_Weapon_SecondaryUse,      		( Response )Weapon::SecondaryUse },
      { &EV_Weapon_PrimaryMode,      		( Response )Weapon::PrimaryMode },
      { &EV_Weapon_SecondaryMode,    		( Response )Weapon::SecondaryMode },
      { &EV_Weapon_ActionIncrement,    	( Response )Weapon::SetActionLevelIncrement },
      { &EV_Weapon_PutAwayAndRaise,    	( Response )Weapon::PutAwayAndRaise },
      { &EV_Weapon_Raise,    	            ( Response )Weapon::Raise },
      { &EV_Weapon_NotDroppable,    	   ( Response )Weapon::NotDroppableEvent },
      { &EV_Weapon_SetAimAnim,            ( Response )Weapon::SetAimAnim },

		{ NULL, NULL }
	};

static      int numBulletHoles = 0;
static      Queue queueBulletHoles;

void ResetBulletHoles(void)
   {
   numBulletHoles = 0;
   queueBulletHoles.Clear();
   }

Weapon::Weapon()
	{
	attack_finished	      = 0;
	owner					      = NULL;
	ammorequired		      = 0;
   secondary_ammorequired  = 0;
	startammo			      = 0;
	rank					      = 0;
   ammo_clip_size          = 0;
   ammo_in_clip            = G_GetIntArg( "ammo_in_clip", 0 );
   kick                    = 0;
   last_attack_time        = level.time-10;
	nextweaponsoundtime     = 0;
	weaponstate			      = WEAPON_HOLSTERED;
   weaponmode              = ( weaponmode_t )G_GetIntArg( "weaponmode", PRIMARY );
   dualmode                = false;
   silenced                = G_GetIntArg( "silenced", false );
   notdroppable            = false;

   aimanim = -1;
   aimframe = 0;

	// handles most cases
	weapontype			= WEAPON_2HANDED_HI;

   // start off unattached
   attached          = false;

	// maximum effective firing distance (for AI)
	maxrange = 8192 * 2; // FIXME grr... magic number...
	
	// minimum safe firing distance (for AI)
	minrange = 0;

	// speed of the projectile (0 == infinite speed)
	projectilespeed = 0;

   // default action_level_increment
   action_level_increment = 2;

	// default weapons don't have alt fire
   alternate_fire          = false;
   }

Weapon::~Weapon()
	{
   DetachGun();
	}

void Weapon::CreateSpawnArgs
   (
   void
   )

   {
   Item::CreateSpawnArgs();
   G_SetIntArg( "ammo_in_clip", ammo_in_clip );
   G_SetIntArg( "silenced", silenced );
   G_SetIntArg( "weaponmode", weaponmode );
   }

int Weapon::Rank
	(
	void
	)

	{
	return rank;
	}

int Weapon::Order
	(
	void
	)

	{
	return order;
	}

void Weapon::SetRank
	(
	int order,
	int rank
	)

	{
	this->order = order;
	this->rank = rank;
	}

void Weapon::SetType
	(
	weapontype_t type
	)

	{
	weapontype = type;
	}

weapontype_t Weapon::GetType
	(
	void
	)

	{
	return weapontype;
	}

void Weapon::SetAmmo
	(
	const char *type,
	int amount,
	int startamount
	)

	{
   if ( type )
		{
	   ammotype = type;
      primary_ammo_type = type;
		}
	else
		{
		ammotype = "";
      primary_ammo_type = "";
      }

	ammorequired = amount;
	startammo = startamount;
	}

void Weapon::SetSecondaryAmmo
   (
   const char *type,
	int amount,
	int startamount
	)

	{
   if ( type )
		{
	   secondary_ammo_type = type;
		}
	else
		{
      secondary_ammo_type = "";
      }

	secondary_ammorequired = amount;
	}

void Weapon::SetAmmoAmount
	(
	int amount
	)

	{
   if ( ammo_clip_size )
      ammo_in_clip = amount;
	}

void Weapon::UseAmmo
	(
	int amount
	)

	{
   if ( ammo_clip_size )
      {
      ammo_in_clip -= amount;
      if (ammo_in_clip < 0)
         {
         warning("UseAmmo","Used more ammo than in clip.\n");
         ammo_in_clip = 0;
         }
      }
   else
      {
      Ammo * ammo;
	   assert( owner );
	   if ( owner && owner->isClient() && !UnlimitedAmmo() )
		   {
         if ( ammotype.length() )
            {
		      ammo = ( Ammo * )owner->FindItem( ammotype.c_str() );
		      
            if ( weaponmode == PRIMARY )
               {
               if ( !ammo || !ammo->Use( ammorequired ) )
	   		      {
		   	      SetAmmoAmount( 0 );
			         return;
                  }
               }
            else
               {
               if ( !ammo || !ammo->Use( secondary_ammorequired ) )
	   		      {
		   	      SetAmmoAmount( 0 );
			         return;
                  }
               }
		      SetAmmoAmount( ammo->Amount() );
            }
		   }
      }
	}

Vector Weapon::MuzzleOffset
	(
   void
	)

   {
   vec3_t	trans[ 3 ];
   vec3_t   orient;
   int		groupindex;
   int		tri_num;
	Vector	offset = vec_zero;
   int      useanim;
   int      useframe;

   // get the bone information
   if ( ( !edict->s.gunmodelindex ) || ( owner && owner->isClient() ) )
      {
      if ( gi.GetBoneInfo( edict->s.modelindex, "barrel", &groupindex, &tri_num, orient ) )
		   {
         if ( aimanim == -1 )
            {
            useanim = edict->s.anim;
            useframe = edict->s.frame;
            }
         else
            {
            useanim = aimanim;
            useframe = aimframe;
            }
         if ( gi.GetBoneTransform( edict->s.modelindex, groupindex, tri_num, orient, useanim, useframe, 
			   edict->s.scale, trans, offset.vec3() ) )
		      {
            //
            // we scale the pos by 0.3 because of RF_DEPTHHACK 
            //
            offset *= 0.3f;
            if ( owner && owner->isClient() )
               {
               switch( owner->client->pers.hand )
                  {
                  case LEFT_HANDED:
                     offset[ 1 ] *= -1.0f;
                     break;
                  case CENTER_HANDED:
                     offset[ 1 ] = 0;
                     break;
                  }
               }
            }
         }
      }
   //
   // if it is a non-client, than get the information from the world model of the gun
   //
   else if ( gi.GetBoneInfo( edict->s.gunmodelindex, "barrel", &groupindex, &tri_num, orient ) )
      {
      gi.GetBoneTransform( edict->s.gunmodelindex, groupindex, tri_num, orient, 0, 0, 
			edict->s.scale, trans, offset.vec3() );
      }
   // Gun doesn't have a barrel, so search the owner for a barrel bone
   else if ( owner && gi.GetBoneInfo( owner->edict->s.modelindex,
                             "barrel",
                             &groupindex,
                             &tri_num,
                             orient ) )
		{
      gi.GetBoneTransform( owner->edict->s.modelindex, 
                           groupindex,
                           tri_num,
                           orient,
                           owner->edict->s.anim,
                           owner->edict->s.frame,
                           owner->edict->s.scale,
                           trans,
                           offset.vec3() );
		}

   return offset;
   }

void Weapon::GetMuzzlePosition
	(
   Vector *position,
	Vector *forward,
	Vector *right,
	Vector *up
	)

	{
   Vector	offset;
	Vector	f, r, u;
	Vector	pos;
	Vector	end;
   Vector   dir;
	Vector	gunpos;
	trace_t	trace;

	assert( owner );

	// technically, we should never not have an owner when firing.
	if ( !owner )
		{
		return;
		}

   //
   // get the position of the owners gun bone
   //
   gunpos = owner->GunPosition();
	pos = gunpos;

	owner->GetGunOrientation( pos, &f, &r, &u );

   // get the bone information
	offset = MuzzleOffset();

   pos += f * offset[ 0 ];
   pos -= r * offset[ 1 ];
	pos += u * offset[ 2 ];

	// prevent the creature from firing through walls
	trace = G_Trace( gunpos, vec_zero, vec_zero, pos, owner, MASK_PROJECTILE, "Weapon::GetMuzzlePosition" );
	if ( ( trace.fraction < 1 ) || ( trace.startsolid ) || ( trace.allsolid ) )
		{
      pos = gunpos;
      pos -= r * offset[ 1 ];
	   pos += u * offset[ 2 ];
		}

   //
   // calculate where this projectile is going to hit
   //
   end = gunpos + f*2048;
	trace = G_FullTrace( gunpos, vec_zero, vec_zero, end, 10, owner, MASK_SHOT, "Weapon::GetMuzzlePosition" );
   dir = trace.endpos - pos;
   dir.normalize();
   if ( dir*f < 0.707 )
      dir = f;

	if ( position )
		{
		*position = pos;
		}

	if ( forward )
		{
		*forward = dir;
		}

	if ( right )
		{
		*right = r;
		}

	if ( up )
		{
		*up = u;
		}
   }

void Weapon::SetAmmoClipSize
	(
   Event * ev
	)

	{
	ammo_clip_size = ev->GetInteger( 1 );
	}

void Weapon::SetModels
	(
	const char *world,
	const char *view
	)

	{
   Event *ev;
	assert( view );

	viewmodel = view;
   modelIndex( view );

   if ( world )
		{
	   worldmodel = world;
      modelIndex( world );
		}
   else
		{
      worldmodel = "";
		}

	if ( owner )
		{
   	setModel( viewmodel );
		}
	else if ( worldmodel.length() )
		{
		setModel( worldmodel );
		}
   else
      {
		setModel( viewmodel );
      }

   if ( worldmodel.length() )
      {
      ev = new Event( EV_Weapon_ProcessModelCommands );
      ev->AddInteger( modelIndex( worldmodel.c_str() ) );
      PostEvent( ev, 0 );
      }
   ev = new Event( EV_Weapon_ProcessModelCommands );
   ev->AddInteger( modelIndex( viewmodel.c_str() ) );
   PostEvent( ev, 0 );
	}

void Weapon::SetAimAnim
   (
   Event *ev
   )

   {
   str anim;

   anim = ev->GetString( 1 );
   aimanim = gi.Anim_NumForName( edict->s.modelindex, anim.c_str() );
   aimframe = ev->GetInteger( 2 );
   }

void Weapon::SetOwner
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

	Item::SetOwner( ent );

	setOrigin( vec_zero );
   setAngles( vec_zero );

	if ( !viewmodel.length() )
		{
		error( "setOwner", "Weapon without viewmodel set" );
		}

	setModel( viewmodel );

	if ( ent->isClient() && ammotype.length() && startammo && !G_GetSpawnArg( "savegame" ) )
		{
      ent->giveItem( ammotype.c_str(), startammo );
		}
	}

void Weapon::TakeAllAmmo
	(
	void
	)

	{
	Ammo *ammo;

	if ( owner )
		{
      if ( ammotype.length() )
         {
		   ammo = ( Ammo * )owner->FindItem( ammotype.c_str() );
		   if ( ammo )
			   {
			   owner->takeItem( ammotype.c_str(), ammo->Amount() );
			   }
         }
		}
	}

int Weapon::AmmoAvailable
	(
	void
	)

	{
	Ammo *ammo;

	if ( owner )
		{
      if ( ammotype.length() )
         {
		   ammo = ( Ammo * )owner->FindItem( ammotype.c_str() );
		   if ( ammo )
			   {
			   return ammo->Amount();
			   }
         }
		}

	return 0;
	}

qboolean Weapon::UnlimitedAmmo
   (
   void
   )

   {
	if ( !owner )
		{
		return false;
		}
		
   if ( !owner->isClient() || ( owner->flags & FL_GODMODE ) || DM_FLAG( DF_INFINITE_AMMO ) )
		{
		return true;
		}

#ifdef SIN_ARCADE
   if ( !sv_infinitebullets || !sv_infiniterockets || !sv_infiniteplasma || !sv_infinitespears || !sv_infinitesniper )
      {
      sv_infinitebullets = gameVars.CreateVariable( "infinitebullets", 0 );
      sv_infiniterockets = gameVars.CreateVariable( "infiniterockets", 0 );
      sv_infiniteplasma  = gameVars.CreateVariable( "infiniteplasma", 0 );
      sv_infinitespears  = gameVars.CreateVariable( "infinitespears", 0 );
      sv_infinitesniper  = gameVars.CreateVariable( "infinitesniper", 0 );
      }

   if ( sv_infinitebullets->intValue() && ( ( !Q_strncasecmp( ammotype.c_str(), "bullet", 6 ) && ( ammotype != "BulletPulse" ) &&
      ( ammotype != "BulletSniper" ) ) || ( ammotype == "ShotgunClip" ) ) )
      {
      return true;
      }

   if ( sv_infiniterockets->intValue() && ( ammotype == "Rockets" ) )
      {
      return true;
      }

   if ( sv_infiniteplasma->intValue() && ( ammotype == "BulletPulse" ) )
      {
      return true;
      }

   if ( sv_infinitesniper->intValue() && ( ammotype == "BulletSniper" ) )
      {
      return true;
      }

   if ( sv_infinitespears->intValue() && ( ammotype == "Spears" ) )
      {
      return true;
      }
#endif

   return false;
   }

qboolean Weapon::HasAmmo
	(
	void
	)

	{
	if ( !owner )
		{
		return false;
		}
		
   if ( UnlimitedAmmo() )
		{
		return true;
		}

   if ( weaponmode == PRIMARY )
      {
      if ( ( ammo_clip_size && ammo_in_clip >= ammorequired ) || AmmoAvailable() >= ammorequired )
		   {
		   return true;
		   }
      }
   else
      {
      if ( ( ammo_clip_size && ammo_in_clip >= secondary_ammorequired ) || AmmoAvailable() >= secondary_ammorequired )
		   {
		   return true;
		   }
      }

	return false;
	}

qboolean Weapon::HasAmmoInClip
	(
	void
	)

	{
   if ( ammo_clip_size )
      {
      if ( weaponmode == PRIMARY )
         {
         if ( ammo_in_clip >= ammorequired )
	   	   {
		      return true;
		      }
         }
      else
         {
         if ( ammo_in_clip >= secondary_ammorequired )
	   	   {
		      return true;
		      }
         }
      }
   else
      {
      return HasAmmo();
      }

	return false;
	}

void Weapon::ForceState
   (
   weaponstate_t state
   )

   {
   weaponstate = state;
   }

qboolean Weapon::AttackDone
	(
	void
	)

	{
	return ( attack_finished <= level.time );
	}

qboolean Weapon::ReadyToFire
	(
	void
	)

	{
	return ( weaponstate == WEAPON_READY ) && AttackDone();
	}

qboolean Weapon::ReadyToChange
	(
	void
	)

	{
	return ( weaponstate == WEAPON_READY );
	}

qboolean Weapon::ReadyToUse
	(
	void
	)

	{
   return true;
	}

qboolean Weapon::ChangingWeapons
	(
	void
	)

	{
	return ( weaponstate == WEAPON_LOWERING ) || ( weaponstate == WEAPON_RAISING );
	}

qboolean Weapon::WeaponRaising
	(
	void
	)

	{
	return ( weaponstate == WEAPON_RAISING );
	}

qboolean Weapon::WeaponPuttingAway
	(
	void
	)

	{
	return ( weaponstate == WEAPON_LOWERING );
	}

qboolean Weapon::Reloading
	(
	void
	)

	{
	return ( weaponstate == WEAPON_RELOADING );
	}

void Weapon::PutAway
	(
	void
	)
	
	{
	if ( weaponstate != WEAPON_READY )
		{
		return;
		}

	weaponstate = WEAPON_LOWERING;

   if ( !HasAnim( "putaway" ) || ( deathmatch->value && ( ( int )dmflags->value & DF_FAST_WEAPONS ) ) )
		{
		ProcessEvent( EV_Weapon_DoneLowering );
		return;
		}

   if ( dualmode )
      {
      if ( weaponmode == PRIMARY )
         RandomAnimate( "primaryputaway", EV_Weapon_DoneLowering );
      else
         RandomAnimate( "secondaryputaway", EV_Weapon_DoneLowering );
      }
   else
      if ( ( owner ) && ( owner->flags & FL_SILENCER ) && ( silenced ) )
      	RandomAnimate( "silputaway", EV_Weapon_DoneLowering );
      else
        	RandomAnimate( "putaway", EV_Weapon_DoneLowering );

   //weaponmode = PRIMARY;
	}

void Weapon::ReadyWeapon
	(
	void
	)
	
	{
   str   animname;

	if ( weaponstate != WEAPON_HOLSTERED )
		{
		return;
		}

	weaponstate = WEAPON_RAISING;

	AttachGun();

   if ( ( owner ) && ( owner->flags & FL_SILENCER ) && ( silenced ) )
      animname = "silready";
   else
      {
      if ( weaponmode == SECONDARY )
         animname = "secondaryready";      
      else
         animname = "ready";      

      }

   if ( !HasAnim( animname.c_str() ) || ( deathmatch->value && ( ( int )dmflags->value & DF_FAST_WEAPONS ) ) )
	   {
		ProcessEvent( EV_Weapon_DoneRaising );
		return;
		}

	RandomAnimate( animname.c_str(), EV_Weapon_DoneRaising );
	}

void Weapon::DetachFromOwner
	(
	void
	)
	
	{
   StopAnimating();
   DetachGun();
 	weaponstate = WEAPON_HOLSTERED;
	}

void Weapon::AttachToOwner
	(
	void
	)
	
	{
   AttachGun();
   ForceIdle();
	}

qboolean Weapon::Drop
	(
	void
	)

	{
   float radius;
   Vector temp;

	if ( !owner )
		{
		return false;
		}

	if ( !IsDroppable() )
		{
		return false;
		}

   DetachGun();

   const gravityaxis_t &grav = gravity_axis[ gravaxis ];

   temp[ grav.z ] = 40 * grav.sign;
   if ( owner )
      {
	   setOrigin( owner->worldorigin + temp );
      }
   else
      {
	   setOrigin( worldorigin + temp );
      }
	setModel( worldmodel );

   // hack to fix the bounds when the gun is dropped

   //
   // once dropped reset the rotated bounds
   //
   flags |= FL_ROTATEDBOUNDS;

   gi.CalculateBounds( edict->s.modelindex, edict->s.scale, mins.vec3(), maxs.vec3() );
   radius = ( mins - maxs ).length() * 0.25f;
   mins.x = mins.y = -radius;
   maxs.x = maxs.y = radius;
   setSize( mins, maxs );

	StopAnimating();
   edict->s.frame = 0;
   edict->s.anim = 0;

	// drop the weapon
	PlaceItem();
   if ( owner )
      {
      temp[ grav.x ] = G_CRandom( 50 );
      temp[ grav.y ] = G_CRandom( 50 );
      temp[ grav.z ] = 100 * grav.sign;
	   velocity = owner->velocity * 0.5 + temp;
	   setAngles( owner->angles );
      }

	avelocity = Vector( 0, G_CRandom( 360 ), 0 );

	if ( owner && owner->isClient() )
		{
		spawnflags |= DROPPED_PLAYER_ITEM;
      if ( ammo_clip_size )
         startammo = ammo_in_clip;
      else
         startammo = 0;
      
      // If owner is dead, put all his ammo of that type in the gun.
      if ( owner->deadflag )
         {
         startammo = AmmoAvailable();
         }
		}
	else
		{
		spawnflags |= DROPPED_ITEM;
      if ( ammo_clip_size && ammo_in_clip )
         startammo = ammo_in_clip;
      else
         startammo >>= 2;

      if ( startammo == 0 )
         {
         startammo = 1;
         }
		}

   // Wait some time before the last owner can pickup this weapon
   last_owner = owner;
   last_owner_trigger_time = level.time + 2.5f;

   // Cancel reloading events
   CancelEventsOfType( EV_Weapon_DoneReloading );

   // Remove this from the owner's item list
   if ( owner )
      {
      owner->RemoveItem( this );
      }
   
   owner = NULL;
   
   // Fade out dropped weapons, to keep down the clutter
   PostEvent( EV_FadeOut, 30 );
	return true;
	}

void Weapon::Fire
	(
	void
	)

	{
   qboolean skipframefix;

	if ( !ReadyToFire() )
		{
		return;
		}

	if ( !HasAmmoInClip() )
		{
      CheckReload();
		return;
		}

   if ( weaponmode == PRIMARY )
      UseAmmo( ammorequired );
   else
      UseAmmo( secondary_ammorequired );

	weaponstate = WEAPON_FIRING;

	CancelEventsOfType( EV_Weapon_DoneFiring );
   // this is just a precaution that we can re-trigger
	NextAttack( 5 );

   skipframefix = false;
   if ( owner && owner->isClient() && !isSubclassOf( ChainGun ) && !isSubclassOf( AssaultRifle ) )
      {
      skipframefix = true;
      StopAnimating();
      }

  	if ( dualmode )
      {
      if ( weaponmode == PRIMARY )
         {
         RandomAnimate( "primaryfire", EV_Weapon_DoneFiring );
         }
      else
         {
         RandomAnimate( "secondaryfire", EV_Weapon_DoneFiring );
         }
      }
   else
      {
      if ( ( owner ) && ( owner->flags & FL_SILENCER ) && ( silenced ) )
         RandomAnimate( "silfire", EV_Weapon_DoneFiring );
      else
         RandomAnimate( "fire", EV_Weapon_DoneFiring );
      }

   if ( skipframefix )
      {
      last_animation_time = ( level.framenum + 1 ) * FRAMETIME;
      }

   last_attack_time = level.time;
	}

//**********************************************************************************/
//
// Non-public Weapon functions
//
//**********************************************************************************/

void Weapon::DetachGun
	(
	void
	)

	{
	if ( attached )
		{
      RandomGlobalSound("null_sound", 1, CHAN_WEAPONIDLE );
      attached = false;
      detach();
		hideModel();
		edict->s.gunmodelindex	= 0;
      edict->s.gunanim        = 0;
		edict->s.gunframe		   = 0;
   	edict->s.effects &= ~EF_SMOOTHANGLES;
		}
	}

//
// attach and detach the gun from the owner
//

void Weapon::AttachGun
	(
	void
	)

	{
	int groupindex;
	int tri_num;
	Vector orient;

	if ( !owner )
		{
		return;
		}

   if (attached)
      DetachGun();

	if	( gi.GetBoneInfo( owner->edict->s.modelindex, "gun", &groupindex, &tri_num, orient.vec3() ) )
	   {
      attached = true;
		attach( owner->entnum, groupindex, tri_num, orient );
		showModel();
		setOrigin( vec_zero );
		edict->s.gunmodelindex	= modelIndex( worldmodel.c_str() );
      if ( edict->s.gunmodelindex )
         {
         edict->s.gunanim        = gi.Anim_Random( edict->s.gunmodelindex, "idle" );
         if ( edict->s.gunanim < 0 )
            edict->s.gunanim = 0;
		   edict->s.gunframe		   = 0;
         }
      else
         {
         edict->s.gunanim        = 0;
		   edict->s.gunframe		   = 0;
         }
   	edict->s.effects |= EF_SMOOTHANGLES;
		}
	else
		{
		gi.dprintf( "attach failed\n" );
		}
	}

void Weapon::PickupWeapon
	(
	Event *ev
	)
	
	{
	Sentient *sen;
	Entity   *other;
   Weapon   *weapon;
	Weapon   *current;
   qboolean hasweapon;
   qboolean giveammo;
   Ammo     *ammo;

	other = ev->GetEntity( 1 );
   
   assert( other );

	if ( !other->isSubclassOf( Sentient ) )
      {
		return;
      }

	sen = ( Sentient * )other;

   // If this is the last owner, check to see if he can pick it up
   if ( ( sen == last_owner ) && ( level.time < last_owner_trigger_time ) )
      {
      return;
      }

   hasweapon = sen->HasItem( getClassname() );
   giveammo = ( sen->isClient() && ammotype.length() && startammo );

   // if he already has the weapon, don't pick it up if he doesn't need the ammo
   if ( hasweapon )
      {
      if ( !giveammo )
         {
         return;
         }

      // check if he needs the ammo
      ammo = ( Ammo * )sen->FindItem( ammotype.c_str() );
      if ( ammo && ( ammo->Amount() >= ammo->MaxAmount() ) )
         {
         // doesn't need the ammo or the weapon, so return.
         return;
         }
      }

  	weapon = ( Weapon * )ItemPickup( other );
	if ( !weapon )
      {
      // Item Pickup failed, so don't give ammo either.
      return;
      }

   //
   // once picked up we don't want rotated bounds
   //
   flags &= ~FL_ROTATEDBOUNDS;

   //FIXME
   // Sentient should probably handle this when itempickup is called
   // Check if we should switch his weapon
   current = sen->CurrentWeapon();
   if ( !DM_FLAG( DF_NO_WEAPON_CHANGE ) )
      {
	   if ( !hasweapon && current && ( current != weapon ) && ( current->AutoChange() ) && 
		   ( ( current->Rank() < weapon->Rank() ) || ( !current->HasAmmo() && weapon->HasAmmo() ) ) )
		   {
		   sen->ChangeWeapon( weapon );
		   }
      }

   // check if we should give him ammo
	if ( giveammo )
		{
      sen->giveItem( ammotype.c_str(), startammo );
		}
	}

void Weapon::ForceIdle
   (
   void
   )

   {
	weaponstate = WEAPON_READY;
	   
   if ( dualmode )
      {
      if ( weaponmode == PRIMARY )
   	   RandomAnimate( "primaryidle", EV_Weapon_Idle );
      else
         RandomAnimate( "secondaryidle", EV_Weapon_Idle );
      }
   else
      {
      if ( owner && ( owner->flags & FL_SILENCER ) && ( silenced ) )
      	RandomAnimate( "silidle", EV_Weapon_Idle );
      else
         RandomAnimate( "idle", EV_Weapon_Idle );
      }
   }

void Weapon::DoneLowering
	(
	Event *ev
	)

	{
	weaponstate = WEAPON_HOLSTERED;

   DetachGun();

	if ( owner )
		{
		owner->ProcessEvent( EV_Sentient_WeaponPutAway );
		}
	StopAnimating();
	}

void Weapon::DoneRaising
	(
	Event *ev
	)

	{
	weaponstate = WEAPON_READY;

   if ( !ForceReload() )
      {
      ForceIdle();
      }

	if ( !owner )
		{
		PostEvent( EV_Remove, 0 );
		return;
		}

   // Set the ammo type
   if (weaponmode == PRIMARY)
      {
      ammotype = primary_ammo_type;
      }
   else if ( weaponmode == SECONDARY )
      {
      ammotype = secondary_ammo_type;
      }

   if ( owner )
	   owner->ProcessEvent( EV_Sentient_WeaponReady );
	}

void Weapon::DoneFiring
	(
	Event *ev
	)

	{
   if ( !CheckReload() )
      {
      ForceIdle();
      }

	if ( owner )
		{
		owner->ProcessEvent( EV_Sentient_WeaponDoneFiring );
		}
	}

void Weapon::DoneReloading
	(
	Event *ev
	)

	{
	Ammo *ammo;
   int amount;

   amount = ammo_clip_size - ammo_in_clip;
	assert( owner );
	if ( owner && owner->isClient() && !UnlimitedAmmo() )
		{
      if ( ammotype.length() )
         {
		   ammo = ( Ammo * )owner->FindItem( ammotype.c_str() );
         if ( ammo )
            {
            if ( ammo->Amount() < amount )
               amount = ammo->Amount();
            if ( !ammo->Use( amount ) )
               {
               amount = 0;
               }
            }
	      SetAmmoAmount( amount + ammo_in_clip );
         }
		}
   else
      {
      SetAmmoAmount( ammo_clip_size );
      }
   
   ForceIdle();

   if ( owner )
      {
	   owner->ProcessEvent( EV_Sentient_WeaponReady );
      }
   }

qboolean Weapon::ForceReload
   ( 
   void
   )

   {
   if ( weaponstate != WEAPON_READY )
      return false;

   if ( level.cinematic && owner && owner->isClient() )
      {
      return false;
      }

   // do a reload if the ammo in clip is not full, 
   // and there is some ammo available out of clip
   if ( 
      ( ammo_clip_size != ammo_in_clip ) && 
      ( AmmoAvailable() > 0 )
      )
      {
   	weaponstate = WEAPON_RELOADING;
      if ( ( owner ) && ( owner->flags & FL_SILENCER ) && ( silenced ) )
         RandomAnimate( "silreload", EV_Weapon_DoneReloading );
      else
         RandomAnimate( "reload", EV_Weapon_DoneReloading );
      return true;
      }
   return false;
   }

qboolean Weapon::CheckReload
	(
	void
	)

	{
   if ( weaponstate != WEAPON_READY )
      return false;

   if ( level.cinematic && owner && owner->isClient() )
      {
      return false;
      }

   if ( ammo_clip_size && !ammo_in_clip && HasAmmo() )
      {
   	weaponstate = WEAPON_RELOADING;
      if ( ( owner ) && ( owner->flags & FL_SILENCER ) && ( silenced ) )
         RandomAnimate( "silreload", EV_Weapon_DoneReloading );
      else
      	RandomAnimate( "reload", EV_Weapon_DoneReloading );
      return true;
      }
   return false;
	}

void Weapon::Idle
	(
	Event *ev
	)

	{
   if ( ammo_clip_size && ( !ammo_in_clip || level.time > last_attack_time + 2 ) )
      {
      if (CheckReload())
         return;
      }

   ForceIdle();
	}

void Weapon::FinishAttack
	(
	Event *ev
	)

	{
   attack_finished = level.time;
   }

void Weapon::NextAttack
	(
	double rate
	)

	{
	attack_finished = level.time + (float)rate;
	}

float	Weapon::GetMaxRange
	(
	void
	)

	{
	return maxrange;
	}

float	Weapon::GetMinRange
	(
	void
	)

	{
	return minrange;
	}

float	Weapon::GetProjectileSpeed
	(
	void
	)

	{
	return projectilespeed;
	}

void Weapon::SetMaxRangeEvent
	(
	Event *ev
	)
	
	{
	maxrange = ev->GetFloat( 1 );
	}

void Weapon::SetMinRangeEvent
	(
	Event *ev
	)

	{
	minrange = ev->GetFloat( 1 );
	}

void Weapon::SetProjectileSpeedEvent
	(
	Event *ev
	)

	{
	projectilespeed = ev->GetFloat( 1 );
	}

void Weapon::NotDroppableEvent
	(
	Event *ev
	)

	{
   notdroppable = true;
	}

void Weapon::SetMaxRange
	(
	float val
	)

	{
	maxrange = val;
	}

void Weapon::SetMinRange
	(
	float val
	)

	{
	minrange = val;
	}

void Weapon::SetProjectileSpeed
	(
	float val
	)

	{
	projectilespeed = val;
	}

void Weapon::EventMuzzleFlash
	(
	Event *ev
	)

	{
	if ( !owner )
		{
		return;
		}

   SpawnTempDlight
      (
      owner->worldorigin,
      ev->GetFloat( 1 ),
      ev->GetFloat( 2 ),
      ev->GetFloat( 3 ),
      ev->GetFloat( 4 ),
      ev->GetFloat( 5 ),
      ev->GetFloat( 6 )
      );
	}

void Weapon::MuzzleFlash
	(
   float r,
   float g,
   float b,
   float radius,
   float decay,
   float life
	)

	{
	if ( !owner )
		{
		return;
		}

   SpawnTempDlight
      (
      owner->worldorigin,
      r,
      g,
      b,
      radius,
      decay,
      life
      );
	}

void Weapon::BulletHole
   (
   trace_t *trace
   )
   {
   Entity *hole;
   Vector norm,norm2;
   Entity *hit;

   hit = trace->ent->entity;

   if ( !hit )
		{
      return;
		}

   if ( trace->surface &&
      ( trace->surface->flags & SURF_NODRAW ) )
      return;

   if ( hit->hidden() )
      return;

   // FIXME: Make Bullet holes client side.
   if ( deathmatch->value )
      return;

   hole = new Entity;
	hole->setMoveType( MOVETYPE_PUSH );
	hole->setSolidType( SOLID_NOT );
   hole->setModel( "sprites/bullethole.spr" );
	hole->setSize( "0 0 0", "0 0 0" );

   norm = trace->plane.normal;
   norm2.x = -norm.x;
   norm2.y = -norm.y;
   norm2.z = norm.z;

   hole->angles = norm2.toAngles();
   hole->setAngles( hole->angles );
   hole->setOrigin( Vector( trace->endpos ) + ( norm * 0.2 ) ) ;

	if ( ( trace->ent->solid == SOLID_BSP ) && ( hit != world ) )
		{
		hole->bind( hit );
		}

   queueBulletHoles.Enqueue(hole);
   numBulletHoles++;

   if (numBulletHoles > sv_maxbulletholes->value)
      {
      // Fade one out of the list.
      Entity *fadehole;
      fadehole = (Entity *) queueBulletHoles.Dequeue();
      fadehole->ProcessEvent(EV_Remove);
      numBulletHoles--;
      }
   }

EXPORT_FROM_DLL void Weapon::WeaponSound
	(
	Event *ev
	)

	{
	Event *e;

	// Broadcasting a sound can be time consuming.  Only do it once in a while on really fast guns.
	if ( nextweaponsoundtime > level.time )
		{
		if ( owner )
			{
			owner->BroadcastSound( ev, CHAN_WEAPON, NullEvent, 0 );
			}
		else
			{
			BroadcastSound( ev, CHAN_WEAPON, EV_HeardWeapon, 0 );
			}
		return;
		}

	if ( owner )
		{
		e = new Event( ev );
		owner->ProcessEvent( e );
		}
	else
		{
		Item::WeaponSound( ev );
		}

	// give us some breathing room
	nextweaponsoundtime = level.time + 0.4;
	}

qboolean Weapon::Removable
   (
   void
   )

   {
   if (
         ( ( int )( dmflags->value ) & DF_WEAPONS_STAY ) && 
         !( spawnflags & ( DROPPED_ITEM | DROPPED_PLAYER_ITEM ) ) 
      )
      return false;
   else
      return true;
   }

qboolean Weapon::Pickupable
   (
   Entity *other
   )

   {
   Sentient *sen;

   if ( !other->isSubclassOf( Sentient ) )
		{
		return false;
		}
   else if ( !other->isClient() )
      {
      return false;
      }

   sen = ( Sentient * )other;

   //FIXME
   // This should be in player

   // Mutants can't pickup weapons
   if ( other->flags & (FL_MUTANT|FL_SP_MUTANT) )
      {
      return false;
      }

   // If we have the weapon and weapons stay, then don't pick it up
   if ( ( ( int )( dmflags->value ) & DF_WEAPONS_STAY ) && !( spawnflags & ( DROPPED_ITEM | DROPPED_PLAYER_ITEM ) ) ) 
      {
      Weapon   *weapon;

      weapon = ( Weapon * )sen->FindItem( getClassname() );

      if ( weapon )
         return false;
      }

   return true;
   }

qboolean Weapon::AutoChange
   (
   void
   )

   {
   return true;
   }

int Weapon::ClipAmmo
   (
   void
   )

   {
   if (ammo_clip_size)
      return ammo_in_clip;
   else
      return -1;
   }

void Weapon::ProcessWeaponCommandsEvent
	(
	Event *ev
	)

	{
   int index;

   index = ev->GetInteger( 1 );
   ProcessInitCommands( index );
	}

void Weapon::SetKick
   (
   Event *ev
   )

   {
   kick = ev->GetInteger( 1 );
   }

void Weapon::SecondaryUse
   (
   Event *ev
   )

   {
   if ( !dualmode )
      return;

   // Switch to the secondary mode of the weapon

   if (weaponstate != WEAPON_READY)
      return;

   weaponstate = WEAPON_CHANGING;

   if (weaponmode == PRIMARY)
      {
      RandomAnimate( "primary2secondary", EV_Weapon_SecondaryMode );
      weaponmode = SECONDARY;
      }
   else
      {
      RandomAnimate( "secondary2primary", EV_Weapon_PrimaryMode );
      weaponmode = PRIMARY;
      }
   }

void Weapon::PrimaryMode
   (
   Event *ev
   )

   {
   RandomAnimate( "primaryidle", EV_Weapon_Idle );
   weaponstate = WEAPON_READY;
   ammotype = primary_ammo_type;
   }

void Weapon::SecondaryMode
   (
   Event *ev
   )
   
   {
   RandomAnimate( "secondaryidle", EV_Weapon_Idle );
   weaponstate = WEAPON_READY;
   ammotype = secondary_ammo_type;
   }

void Weapon::SetActionLevelIncrement
   (
   Event *ev
   )
   {
   action_level_increment = ev->GetInteger( 1 );
   }

int Weapon::ActionLevelIncrement
   (
   void
   )
   {
   return action_level_increment;
   }

qboolean Weapon::IsDroppable
	(
	void
	)
	{
	if ( notdroppable || !worldmodel.length() )
		{
		return false;
		}
   else
      {
      return true;
      }
   }

qboolean Weapon::IsSilenced
   (
   void
   )

   {
   return silenced;
   }

void Weapon::Raise
   (
   Event *ev 
   )

   {
   weaponstate = WEAPON_HOLSTERED;
   ReadyWeapon();
   }

void Weapon::PutAwayAndRaise
   (
   Event *ev
   )
   
   {
   weaponstate = WEAPON_LOWERING;

   if ( deathmatch->value && ( ( int )dmflags->value & DF_FAST_WEAPONS ) )
		{
		ProcessEvent( EV_Weapon_DoneRaising );
		return;
		}

	RandomAnimate( "putaway", EV_Weapon_Raise );
   }

void Weapon::SetPrimaryMode
   (
   void
   )

   {
   weaponmode = PRIMARY;
   ammotype = primary_ammo_type;
   }

void Weapon::SetSecondaryMode
   (
   void
   )

   {
   weaponmode = SECONDARY;
   ammotype = secondary_ammo_type;
   }

