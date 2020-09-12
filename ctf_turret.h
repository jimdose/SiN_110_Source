//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/ctf_turret.h                     $
// $Revision:: 6                                                              $
//   $Author:: Aldie                                                          $
//     $Date:: 3/19/99 5:13p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/ctf_turret.h                          $
// 
// 6     3/19/99 5:13p Aldie
// Made turret non-droppable
// 
// 5     3/05/99 5:51p Markd
// made vehicles respawn in CTF, fixed up turrets a bit more
// 
// 4     2/26/99 7:42p Markd
// Fixed turrets some more
// 
// 3     2/26/99 5:53p Markd
// Fixed up turrets a lot more
// 
// 2     2/19/99 7:49p Markd
// implemented turret for CTF
// 
// 1     2/19/99 6:03p Markd
// 
// 8     10/06/98 10:52p Aldie
// Moved bubble trail to client
// 
// 7     9/21/98 4:50p Markd
// Fixed projectile owner
// 
// 6     8/29/98 5:27p Markd
// added specialfx, replaced misc with specialfx where appropriate
// 
// 5     4/04/98 6:12p Jimdose
// Created file
// 
// DESCRIPTION:
// Fires a spear.  Used by Seabonites.
// 

#ifndef __CTF_TURRET_H__
#define __CTF_TURRET_H__

#include "g_local.h"
#include "vehicle.h"
#include "heligun.h"
#include "bullet.h"
#include "sentient.h"


class EXPORT_FROM_DLL CTFTurret : public DrivableVehicle
	{
	public:
		CLASS_PROTOTYPE( CTFTurret );
		
								CTFTurret ();
		virtual void		DriverUse( Event *ev );
		virtual float		SetDriverPitch( float pitch );
	};


class EXPORT_FROM_DLL CTFTurretGun : public HeliGun
	{
	public:
		CLASS_PROTOTYPE( CTFTurretGun );
		
								CTFTurretGun();
		virtual void		Shoot( Event *ev );
      qboolean          IsDroppable( void );

	};

class EXPORT_FROM_DLL CTFDrivableTurret : public DrivableVehicle
	{
   private:
      Vector            baseangles;
      float             maxpitch;
      float             maxyaw;
      float             entertime;
      float             exittime;
      int               lastbutton;
      float             shotdamage;
      Sentient          *gunholder;
      BulletWeapon      *gun;

	public:
		CLASS_PROTOTYPE( CTFDrivableTurret );
		
								CTFDrivableTurret ();
		virtual qboolean	Drive( usercmd_t *ucmd );
		virtual void		Postthink( void );
      virtual void      Fire( void );
		virtual float		SetDriverPitch( float pitch );
		virtual void		DriverUse( Event *ev );
	};

#endif /* ctfturret.h */
