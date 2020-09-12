//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/securityturret.h                 $
// $Revision:: 11                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 7/07/98 4:12p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/securityturret.h                      $
// 
// 11    7/07/98 4:12p Aldie
// Updated to new class hierarchy
// 
// 10    4/10/98 12:35a Jimdose
// made turret "New and Improved!"
// 
// 9     4/09/98 7:37p Markd
// 
// 8     4/08/98 4:22p Jimdose
// Getting ready to conver to Q2
// 
// 6     12/15/97 12:01a Jimdose
// Made wake up and firing distances farther.
// 
// 5     12/14/97 4:24p Jimdose
// Changed from monster_turret to trap_securityturret
// 
// 4     12/13/97 6:00p Jimdose
// Changed the base from a Sentient to an Entity
// 
// 3     12/13/97 3:47p Jimdose
// Finished implementing behaviour
// 
// 2     12/09/97 3:00p Jimdose
// Created file
//
// DESCRIPTION:
// 

#ifndef __SECURITY_TURRET_H__
#define __SECURITY_TURRET_H__

#include "turret.h"

class EXPORT_FROM_DLL TurretTop : public Turret
	{
   private:
      void        SetupBase( void );
	public:
      CLASS_PROTOTYPE( TurretTop );

						     TurretTop();
	};

class EXPORT_FROM_DLL TurretBase : public Entity
	{
	public:
      CLASS_PROTOTYPE( TurretBase );

							TurretBase();
		void				GoUp( Event *ev );
		void				GoDown( Event *ev );
	};

#endif /* Turret.h */
