//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/weapon.h                         $
// $Revision:: 69                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 4/16/99 5:03p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/weapon.h                              $
// 
// 69    4/16/99 5:03p Aldie
// Added TakeAllAmmo
// 
// 68    3/02/99 9:16p Aldie
// Added CTF game code
// 
// 2     2/16/99 4:09p Aldie
// 
// 1     2/11/99 1:40p Aldie
// 
// 67    12/10/98 1:46p Jimdose
// Added UnlimitedAmmo
// 
// 66    11/08/98 10:57p Jimdose
// secondary_ammorequired wasn't being archived
// 
// 65    10/25/98 11:53p Jimdose
// added EXPORT_TEMPLATE
// 
// 64    10/22/98 12:19a Jimdose
// Added aimanim and aimframe
// Added SetAimAnim
// 
// 63    10/18/98 6:42p Markd
// Added notdroppable event to weapons
// 
// 62    10/16/98 9:51p Aldie
// Added SecondaryAmmo command
// 
// 61    10/14/98 1:34a Jimdose
// Got cross-level persitant data working
// 
// 60    10/10/98 5:58p Aldie
// More quantumdestab fixes
// 
// 59    10/08/98 12:35a Jimdose
// Added ForceIdle
// 
// 58    10/05/98 10:43p Aldie
// Converted over to new silencer methods
// 
// 57    9/21/98 4:21p Markd
// Put in archive functions and rewrote all archive routines
// 
// 56    9/19/98 4:59p Markd
// added ActionIncrement event
// 
// 55    9/16/98 8:58p Aldie
// Added ability to do a hold down weapon charge
// 
// 54    9/11/98 2:53p Aldie
// Added ReleaseFire functionality
// 
// 53    9/09/98 6:23p Markd
// Added IsDroppable
// 
// 52    9/02/98 11:08a Markd
// Put in setModel into Sentient so that weapon could be properly detached and
// re-attached again.
// 
// 51    8/29/98 9:54p Jimdose
// Moved prototype of ResetBulletHoles from g_local.h
// 
// 50    8/18/98 7:39p Aldie
// Added dual weapon modes to base class
// 
// 49    8/14/98 5:48p Aldie
// Moved bloodsplats to sentient
// 
// 48    8/10/98 6:54p Aldie
// Added scale to bloodsplats
// 
// 47    8/06/98 10:53p Aldie
// Added weapon tweaks and kickback.  Also modified blast radius damage and
// rocket jumping.
// 
// 46    8/06/98 6:54p Jimdose
// Added min/max range, and projkectile speed
// 
// 45    7/22/98 10:21p Markd
// Added WeaponReloading, PuttingAway, and RaisingWeapon
// 
// 44    7/20/98 5:41p Aldie
// Added command processing for weapons.
// 
// 43    7/19/98 5:21p Markd
// Added DetachFromOwner command
// 
// 42    7/17/98 4:41p Aldie
// Made NextAttack a public function.
// 
// 41    7/17/98 11:32a Aldie
// Added ClipAmmo and ForceReload
// 
// 40    7/15/98 9:59p Markd
// Removed some muzzle flash stuff
// 
// 39    7/11/98 8:20p Jimdose
// Drop now returns true or false depending upon whether the weapon can be
// dropped or not
// 
// 38    7/10/98 12:07a Aldie
// Autochange support
// 
// 37    7/02/98 2:35p Aldie
// Added last owner for weapon
// 
// 36    6/26/98 12:23p Markd
// Added Pickupable function
// 
// 35    6/25/98 8:48p Markd
// Rewrote Item class, added keyed items to triggers, cleaned up item system
// 
// 34    6/19/98 9:28p Jimdose
// Added general weapon muzzle code
// 
// 33    6/17/98 1:16a Jimdose
// 
// 32    6/15/98 10:40a Aldie
// Added a new weapon state
// 
// 31    6/11/98 12:38a Markd
// Added BasePosition and MuzzlePosition methods
// 
// 30    6/10/98 2:10p Aldie
// Updated damage function.
// 
// 29    6/10/98 1:18p Markd
// Changed SetAmmoClipSize
// 
// 28    6/08/98 8:18p Markd
// added reloading support and ReadyToUse
// 
// 27    6/05/98 6:28p Aldie
// Added location to damage
// 
// 26    6/03/98 4:40p Markd
// Removed Dummy and its methods, added AttachGun and DetachGun
// 
// 25    5/25/98 6:53a Aldie
// Added max bulletholes
// 
// 24    5/24/98 8:46p Jimdose
// Made a lot of functions more str-friendly.
// Got rid of a lot of char * based strings
// Cleaned up get spawn arg functions and sound functions
// sound functions now use consistant syntax
// 
// 23    5/24/98 1:07a Jimdose
// Added sound events for ai
// viewmodel, worldmodel, and ammotype are now str objects
// 
// 22    5/23/98 4:53p Aldie
// Added bullethole
// 
// 21    5/13/98 4:51p Jimdose
// Now uses SafePtrs
// 
// 20    4/09/98 3:30p Jimdose
// Added gettype and settype
// added sound so that anim sounds play from the owner
// 
// 19    4/08/98 4:46p Jimdose
// Added ShowDummyOnClient and HideDummyOnClient
// 
// 18    4/07/98 6:47p Jimdose
// Rewrote weapon code
// 
// 17    4/06/98 7:10p Aldie
// Added zooming for SniperRifle
// 
// 16    4/04/98 6:12p Jimdose
// Added attachable weapons
// 
// 15    4/02/98 4:46p Jimdose
// Added AmmoAvailable
// 
// 14    3/30/98 2:37p Jimdose
// Added ammo, rank, and dropping of weapons
// 
// 13    3/27/98 11:05p Jimdose
// added muzzle flash
// 
// 12    3/23/98 1:33p Jimdose
// Revamped event and command system
// 
// 11    3/18/98 7:24p Jimdose
// Added code for handling readying and putting away weapons
// Made work with new animation system
// 
// 10    3/02/98 8:49p Jimdose
// Changed CLASS_PROTOTYPE to only take the classname
// 
// 9     2/19/98 2:35p Jimdose
// Updated to work with Q2 based progs
// 
// 7     12/11/97 3:32p Markd
// Added SpawnBlood call
// 
// 6     12/09/97 7:42p Markd
// Added range variable
// 
// 5     11/18/97 5:27p Markd
// Put in clip_size and clip_ammo as well as time variables to keep track of
// last twitch time and last fire time
// 
// 4     10/31/97 4:28p Jimdose
// Removed redefinition of owner as Sentient * since it hid the original
// definition in Entity.
// 
// 3     10/27/97 2:59p Jimdose
// Removed dependency on quakedef.h
// 
// 2     9/26/97 4:46p Jimdose
// Added standard Ritual header
//
// DESCRIPTION:
// Header file for Weapon class.  The weapon class is the base class for
// all weapons in Sin.  Any entity created from a class derived from the weapon
// class will be usable by any Sentient (players and monsters) as a weapon.
// 

#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "g_local.h"
#include "item.h"
#include "sentient.h"
#include "ammo.h"
#include "queue.h"

extern Event EV_Weapon_Shoot;
extern Event EV_Weapon_FinishAttack;
extern Event EV_Weapon_DoneLowering;
extern Event EV_Weapon_DoneRaising;
extern Event EV_Weapon_DoneFiring;
extern Event EV_Weapon_Idle;
extern Event EV_Weapon_MuzzleFlash;
extern Event EV_Weapon_SecondaryUse;
extern Event EV_Weapon_DoneReloading;
extern Event EV_Weapon_SetMaxRange;
extern Event EV_Weapon_SetMinRange;
extern Event EV_Weapon_SetProjectileSpeed;
extern Event EV_Weapon_ActionIncrement;
extern Event EV_Weapon_PutAwayAndRaise;
extern Event EV_Weapon_NotDroppable;

typedef enum
	{
	WEAPON_READY,
	WEAPON_FIRING,
	WEAPON_LOWERING,
	WEAPON_RAISING,
	WEAPON_HOLSTERED,
	WEAPON_RELOADING,
   WEAPON_CHANGING
	} weaponstate_t;

typedef enum
	{
	WEAPON_MELEE,  				// For hands only weapons
	WEAPON_1HANDED,				// For short, lightweight weapons fired high (Magnum, pistols, etc.)
	WEAPON_2HANDED_HI,			// For long, aimed weapons fired high (sniper rifle, shotgun, etc.)
	WEAPON_2HANDED_LO				// For long, heavy weapons fired low (rocket launcher)
	} weapontype_t;

typedef enum
   {
   PRIMARY,
   SECONDARY
   } weaponmode_t;

class EXPORT_FROM_DLL Weapon : public Item
	{
	private:
      qboolean					attached;
		float						nextweaponsoundtime;

   protected:
		float						maxrange;				// maximum effective firing distance (for AI)
		float						minrange;				// minimum safe firing distance (for AI)
		float						projectilespeed;		// speed of the projectile (0 == infinite speed)

		float						attack_finished;
		float						flashtime;
		float						flashdecay;
		weaponstate_t			weaponstate;
      weaponmode_t         weaponmode;
      qboolean             dualmode;
      str                  primary_ammo_type;
      str                  secondary_ammo_type;
      str						viewmodel;
		str						worldmodel;
		str                  ammotype;
      int						ammorequired;
      int                  secondary_ammorequired;
		int						startammo;
		int						rank;
		int						order;
      int						ammo_clip_size;
      int						ammo_in_clip;
      float						last_attack_time;
		weapontype_t			weapontype;
		SentientPtr				last_owner;
      float						last_owner_trigger_time;
      int                  kick;
      int                  action_level_increment;
      qboolean             silenced;
      qboolean             notdroppable;
      int                  aimanim;
      int                  aimframe;

      // CTF
      qboolean             alternate_fire;

		void						SetMaxRangeEvent( Event *ev );
		void						SetMinRangeEvent( Event *ev );
		void						SetProjectileSpeedEvent( Event *ev );
      void                 SetSecondaryAmmo( const char *type, int amount, int startamount );

      virtual void			DetachGun( void );
		virtual void			AttachGun( void );

		virtual void			PickupWeapon( Event *ev );
		virtual void			DoneLowering( Event *ev );
		virtual void			DoneRaising( Event *ev );
		virtual void			DoneFiring( Event *ev );
		virtual void			Idle( Event *ev );
      virtual qboolean		CheckReload( void );
		virtual void			DoneReloading( Event *ev );
		virtual void			FinishAttack( Event *ev );
		virtual void			EventMuzzleFlash( Event *ev );
      virtual void			MuzzleFlash( float r, float g, float b, float radius, float decay, float life );
      virtual void			BulletHole( trace_t *trace );
      virtual void         SetAimAnim( Event *ev );

	public:

      CLASS_PROTOTYPE( Weapon );

									Weapon();
		virtual					~Weapon();

		virtual void         CreateSpawnArgs( void );

		virtual int				Rank( void );
		virtual int				Order( void );
		virtual void			SetRank( int order, int rank );

		virtual void			SetType( weapontype_t type );
		virtual weapontype_t GetType( void );

		float						GetMaxRange( void );
		float						GetMinRange( void );
		float						GetProjectileSpeed( void );

		void						SetMaxRange( float val );
		void						SetMinRange( float val );
		void						SetProjectileSpeed( float val );

      virtual void         ForceIdle( void );
      virtual void         NextAttack( double rate );

		virtual void			SetAmmo( const char *type, int amount, int startamount );
		virtual void			SetAmmoAmount( int amount );
      virtual void         UseAmmo( int amount );
      virtual void			SetAmmoClipSize( Event * ev );
		virtual void			SetModels( const char *world, const char *view );

		virtual void			SetOwner( Sentient *ent );

		virtual int				AmmoAvailable( void );
      virtual qboolean     UnlimitedAmmo( void );
		virtual qboolean		HasAmmo( void );
      virtual qboolean     HasAmmoInClip( void );
		virtual qboolean		AttackDone( void );
		virtual qboolean		ReadyToFire( void );
		virtual qboolean		ReadyToChange( void );
      virtual qboolean     ReadyToUse( void );
		virtual qboolean		ChangingWeapons( void );
		virtual qboolean		Reloading( void );
      virtual qboolean     WeaponRaising(	void );
      virtual qboolean     WeaponPuttingAway(	void );

		virtual void			PutAway( void );
		virtual void			ReadyWeapon( void );
		virtual qboolean		Drop( void );
		virtual void			Fire( void );
      virtual void			ReleaseFire( float holdfiretime ) { /* No action for base class */ };

		virtual qboolean	   Removable( void );
      virtual qboolean     Pickupable( Entity *other );
      virtual void         DetachFromOwner( void );
      virtual void         AttachToOwner( void );

		virtual void			WeaponSound( Event *ev );

		virtual Vector			MuzzleOffset( void );
		virtual void			GetMuzzlePosition( Vector *position, Vector *forward = NULL, Vector *right = NULL, Vector *up = NULL );

      virtual qboolean     AutoChange( void );
      virtual int          ClipAmmo( void );
      virtual qboolean     ForceReload( void );

      virtual void         ProcessWeaponCommandsEvent(Event *ev);
      virtual void         SetKick( Event *ev );
      virtual void         SecondaryUse( Event *ev );
      virtual void         PrimaryMode( Event *ev );
      virtual void         SecondaryMode( Event *ev );

      virtual qboolean     IsDroppable( void );
      virtual int          ActionLevelIncrement( void );
      virtual void         SetActionLevelIncrement( Event *ev );
      virtual void         PutAwayAndRaise( Event *ev );
      virtual void         Raise( Event *ev );
      virtual qboolean     IsSilenced( void );
      virtual void         ForceState( weaponstate_t state );
      virtual void         NotDroppableEvent( Event *ev );
      
      virtual void         Archive(	Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
      
      // CTF
      void                 SetPrimaryMode( void );
      void                 SetSecondaryMode( void );
      virtual void         TakeAllAmmo( void );
      qboolean             AlternateFire( void ) { return alternate_fire; }
   };


inline EXPORT_FROM_DLL void Weapon::Archive
	(
	Archiver &arc
	)
   {
   Item::Archive( arc );
   arc.WriteBoolean( attached );
   arc.WriteFloat( nextweaponsoundtime );
   arc.WriteFloat( maxrange );
   arc.WriteFloat( minrange );
   arc.WriteFloat( projectilespeed );
   arc.WriteFloat( attack_finished );
   arc.WriteFloat( flashtime );
   arc.WriteFloat( flashdecay );
   arc.WriteInteger( weaponstate );
   arc.WriteInteger( weaponmode );
   arc.WriteBoolean( dualmode );
   arc.WriteString( primary_ammo_type );
   arc.WriteString( secondary_ammo_type );
   arc.WriteString( viewmodel );
   arc.WriteString( worldmodel );
   arc.WriteString( ammotype );
   arc.WriteInteger( ammorequired );
   arc.WriteInteger( secondary_ammorequired );
   arc.WriteInteger( startammo );
   arc.WriteInteger( rank );
   arc.WriteInteger( order );
   arc.WriteInteger( ammo_clip_size );
   arc.WriteInteger( ammo_in_clip );
   arc.WriteFloat( last_attack_time );
   arc.WriteInteger( weapontype );
	arc.WriteSafePointer( last_owner );
   arc.WriteFloat( last_owner_trigger_time );
   arc.WriteInteger( kick );
   arc.WriteInteger( action_level_increment );
   arc.WriteBoolean( silenced );
   arc.WriteBoolean( notdroppable );
   arc.WriteInteger( aimanim );
   arc.WriteInteger( aimframe );
   }

inline EXPORT_FROM_DLL void Weapon::Unarchive
	(
	Archiver &arc
	)
   {
   int temp;

   Item::Unarchive( arc );
   arc.ReadBoolean( &attached );
   arc.ReadFloat( &nextweaponsoundtime );
   arc.ReadFloat( &maxrange );
   arc.ReadFloat( &minrange );
   arc.ReadFloat( &projectilespeed );
   arc.ReadFloat( &attack_finished );
   arc.ReadFloat( &flashtime );
   arc.ReadFloat( &flashdecay );

   arc.ReadInteger( &temp );
   weaponstate = ( weaponstate_t )temp;
   arc.ReadInteger( &temp );
   weaponmode = ( weaponmode_t )temp;

   arc.ReadBoolean( &dualmode );
   arc.ReadString( &primary_ammo_type );
   arc.ReadString( &secondary_ammo_type );
   arc.ReadString( &viewmodel );
   arc.ReadString( &worldmodel );
   arc.ReadString( &ammotype );
   arc.ReadInteger( &ammorequired );
   arc.ReadInteger( &secondary_ammorequired );
   arc.ReadInteger( &startammo );
   arc.ReadInteger( &rank );
   arc.ReadInteger( &order );
   arc.ReadInteger( &ammo_clip_size );
   arc.ReadInteger( &ammo_in_clip );
   arc.ReadFloat( &last_attack_time );

   arc.ReadInteger( &temp );
   weapontype = ( weapontype_t )temp;

	arc.ReadSafePointer( &last_owner );
   arc.ReadFloat( &last_owner_trigger_time );
   arc.ReadInteger( &kick );
   arc.ReadInteger( &action_level_increment );
   arc.ReadBoolean( &silenced );
   arc.ReadBoolean( &notdroppable );
   arc.ReadInteger( &aimanim );
   arc.ReadInteger( &aimframe );
   }

#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL SafePtr<Weapon>;
#endif
typedef SafePtr<Weapon> WeaponPtr;

EXPORT_FROM_DLL void ResetBulletHoles( void );

#endif /* weapon.h */
