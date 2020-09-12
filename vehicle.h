//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/vehicle.h                        $
// $Revision:: 31                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 3/05/99 5:51p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/vehicle.h                             $
// 
// 31    3/05/99 5:51p Markd
// made vehicles respawn in CTF, fixed up turrets a bit more
// 
// 30    2/26/99 5:54p Markd
// Fixed some stuff for turrets
// 
// 29    2/19/99 7:49p Markd
// implemented turret for CTF
// 
// 28    11/16/98 8:26p Jimdose
// made vehicles check for water and lava
// 
// 27    11/08/98 10:55p Jimdose
// seatoffset was archived twice
// 
// 26    10/25/98 11:53p Jimdose
// added EXPORT_TEMPLATE
// 
// 25    10/20/98 7:52p Markd
// Fixed drivable vehicles
// 
// 24    10/18/98 9:01p Markd
// Added ShowWeapon method and showweapon variable
// 
// 23    10/15/98 11:53p Markd
// added jumping ability to vehicles
// 
// 22    10/08/98 7:17p Markd
// added steerinplace and stuff
// 
// 21    10/06/98 9:45p Markd
// Added last_origin to the class
// 
// 20    9/21/98 4:21p Markd
// Put in archive functions and rewrote all archive routines
// 
// 19    9/16/98 10:07p Markd
// working on vehicles
// 
// 18    9/15/98 4:30p Markd
// Updated vehicle code
// 
// 17    9/14/98 6:13p Markd
// Added some more functionality to vehicles
// 
// 16    9/09/98 3:04p Markd
// Added IsDrivable method
// 
// 15    7/25/98 4:39p Jimdose
// Added Driver
// 
// 14    7/20/98 12:09p Markd
// Added driveranim and seatoffset stuff
// 
// 13    7/19/98 4:28p Markd
// Got rid of Damage support
// 
// 12    7/18/98 11:14p Markd
// Added damage support
// 
// 11    7/17/98 4:05p Markd
// Added more functionality to the vehicles
// 
// 10    6/23/98 2:59p Jimdose
// Better (but still bad) driving code
// 
// 9     6/22/98 2:05p Jimdose
// Reintegrated into Sin
// 
// 7     11/01/97 2:02p Jimdose
// Worked on vehicles
// 
// 6     10/31/97 9:03p Jimdose
// Worked on vehicles
// 
// 5     10/30/97 11:48p Jimdose
// Worked on vehicle code
// 
// 4     10/27/97 2:59p Jimdose
// Removed dependency on quakedef.h
// 
// 3     10/08/97 9:30p Jimdose
// Refined Vehicle movement.
// 
// 2     10/08/97 6:03p Jimdose
// Began vehicle support.
// 
// DESCRIPTION:
// Script controlled vehicles.
// 

#ifndef __VEHICLE_H__
#define __VEHICLE_H__

#include "g_local.h"
#include "entity.h"
#include "sentient.h"
#include "scriptslave.h"

extern Event EV_Vehicle_Enter;
extern Event EV_Vehicle_Exit;
extern Event EV_Vehicle_Drivable;
extern Event EV_Vehicle_UnDrivable;
extern Event EV_Vehicle_Lock;
extern Event EV_Vehicle_UnLock;
extern Event EV_Vehicle_SeatAnglesOffset;
extern Event EV_Vehicle_SeatOffset;
extern Event EV_Vehicle_DriverAnimation;
extern Event EV_Vehicle_SetWeapon;
extern Event EV_Vehicle_ShowWeapon;
extern Event EV_Vehicle_SetSpeed;
extern Event EV_Vehicle_SetTurnRate;

class EXPORT_FROM_DLL VehicleBase : public ScriptModel
	{
	public:
		VehicleBase *vlink;
		Vector		 offset;

      CLASS_PROTOTYPE( VehicleBase );

		VehicleBase();
      virtual void Archive(	Archiver &arc );
      virtual void Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void VehicleBase::Archive
	(
	Archiver &arc
	)
   {
   ScriptModel::Archive( arc );
   arc.WriteObjectPointer( vlink );
   arc.WriteVector( offset );
   }

inline EXPORT_FROM_DLL void VehicleBase::Unarchive
	(
	Archiver &arc
	)
   {
   ScriptModel::Unarchive( arc );
   arc.ReadObjectPointer( ( Class ** )&vlink );
   arc.ReadVector( &offset );
   }


/*QUAKED script_wheelsback (0 .5 .8) ?
*/
class EXPORT_FROM_DLL BackWheels : public VehicleBase
	{
	public:
      CLASS_PROTOTYPE( BackWheels );
	};

/*QUAKED script_wheelsfront (0 .5 .8) ?
*/
class EXPORT_FROM_DLL FrontWheels : public VehicleBase
	{
	public:
      CLASS_PROTOTYPE( FrontWheels )
	};


class EXPORT_FROM_DLL Vehicle : public VehicleBase
	{
	protected:
		SentientPtr			driver;
		SentientPtr			lastdriver;
		float					maxturnrate;
		float					currentspeed;
		float					turnangle;
		float					turnimpulse;
		float					moveimpulse;
		float					jumpimpulse;
		float					speed;
      float             conesize;
      float             maxtracedist;
      int               buttons;
      Vector            cmd_angles;
      str               weaponName;
      str               driveranim;
      Vector            last_origin;
      Vector            seatangles;
      Vector            seatoffset;
      Vector            driveroffset;
      Vector            Corners[4];

      qboolean          drivable;
      qboolean          locked;
      qboolean          hasweapon;
      qboolean          showweapon;
      qboolean          steerinplace;
      qboolean          jumpable;

      // CTF only stuff
      Vector            startorigin;

      virtual void      WorldEffects( void );
      virtual void      CheckWater( void );
		virtual void		DriverUse( Event *ev );
		virtual void		VehicleStart( Event *ev );
		virtual void		VehicleTouched( Event *ev );
		virtual void		VehicleBlocked( Event *ev );
		virtual void		Postthink( void );
		virtual void		Drivable( Event *ev );
		virtual void		UnDrivable( Event *ev );
		virtual void		Jumpable( Event *ev );
		virtual void		SeatAnglesOffset( Event *ev );
		virtual void		SeatOffset( Event *ev );
      virtual void      SetDriverAngles( Vector angles );
		virtual void		Lock( Event *ev );
		virtual void		UnLock( Event *ev );
		virtual void		SetWeapon( Event *ev );
		virtual void		ShowWeaponEvent( Event *ev );
		virtual void		DriverAnimation( Event *ev );
		virtual void		SetSpeed( Event *ev );
		virtual void		SetTurnRate( Event *ev );
		virtual void		SteerInPlace( Event *ev );

	public:

      CLASS_PROTOTYPE( Vehicle );

								Vehicle();

		virtual qboolean	Drive( usercmd_t *ucmd );
		virtual qboolean	HasWeapon( void );
		virtual qboolean	ShowWeapon( void );
      Sentient				*Driver( void );
		virtual qboolean	IsDrivable( void );
      virtual void      Archive(	Archiver &arc );
      virtual void      Unarchive( Archiver &arc );
		virtual float		SetDriverPitch( float pitch );
	};

inline EXPORT_FROM_DLL void Vehicle::Archive
	(
	Archiver &arc
	)
   {
   VehicleBase::Archive( arc );

   arc.WriteSafePointer( driver );
   arc.WriteSafePointer( lastdriver );
   arc.WriteFloat( maxturnrate );
   arc.WriteFloat( currentspeed );
   arc.WriteFloat( turnangle );
   arc.WriteFloat( turnimpulse );
   arc.WriteFloat( moveimpulse );
   arc.WriteFloat( jumpimpulse );
   arc.WriteFloat( speed );
   arc.WriteFloat( conesize );
   arc.WriteFloat( maxtracedist );
   arc.WriteString( weaponName );
   arc.WriteString( driveranim );
   arc.WriteVector( last_origin );
   arc.WriteVector( seatangles );
   arc.WriteVector( seatoffset );
   arc.WriteVector( driveroffset );

   arc.WriteVector( Corners[ 0 ] );
   arc.WriteVector( Corners[ 1 ] );
   arc.WriteVector( Corners[ 2 ] );
   arc.WriteVector( Corners[ 3 ] );

   arc.WriteBoolean( drivable );
   arc.WriteBoolean( locked );
   arc.WriteBoolean( hasweapon );
   arc.WriteBoolean( showweapon );
   arc.WriteBoolean( steerinplace );
   arc.WriteBoolean( jumpable );
   }

inline EXPORT_FROM_DLL void Vehicle::Unarchive
	(
	Archiver &arc
	)
   {
   VehicleBase::Unarchive( arc );
   arc.ReadSafePointer( &driver );
   arc.ReadSafePointer( &lastdriver );
   arc.ReadFloat( &maxturnrate );
   arc.ReadFloat( &currentspeed );
   arc.ReadFloat( &turnangle );
   arc.ReadFloat( &turnimpulse );
   arc.ReadFloat( &moveimpulse );
   arc.ReadFloat( &jumpimpulse );
   arc.ReadFloat( &speed );
   arc.ReadFloat( &conesize );
   arc.ReadFloat( &maxtracedist );
   arc.ReadString( &weaponName );
   arc.ReadString( &driveranim );
   arc.ReadVector( &last_origin );
   arc.ReadVector( &seatangles );
   arc.ReadVector( &seatoffset );
   arc.ReadVector( &driveroffset );

   arc.ReadVector( &Corners[ 0 ] );
   arc.ReadVector( &Corners[ 1 ] );
   arc.ReadVector( &Corners[ 2 ] );
   arc.ReadVector( &Corners[ 3 ] );

   arc.ReadBoolean( &drivable );
   arc.ReadBoolean( &locked );
   arc.ReadBoolean( &hasweapon );
   arc.ReadBoolean( &showweapon );
   arc.ReadBoolean( &steerinplace );
   arc.ReadBoolean( &jumpable );
   }

class EXPORT_FROM_DLL DrivableVehicle : public Vehicle
	{
	public:
      float             respawntime;

      CLASS_PROTOTYPE( DrivableVehicle );

								DrivableVehicle();

		virtual void		Killed( Event *ev );
		virtual void		Respawn( Event *ev );
	};

#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL	SafePtr<Vehicle>;
#endif
typedef SafePtr<Vehicle>			VehiclePtr;

#endif /* vehicle.h */
