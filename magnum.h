//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/magnum.h                         $
// $Revision:: 13                                                             $
//   $Author:: Jimdose                                                        $
//     $Date:: 10/19/98 12:06a                                                $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/magnum.h                              $
// 
// 13    10/19/98 12:06a Jimdose
// made all code use fast checks for inheritance (no text lookups when
// possible)
// isSubclassOf no longer requires ::_classinfo()
// added Drop
// 
// 12    10/05/98 10:38p Aldie
// Converted over to new silencer methods
// 
// 11    6/17/98 10:56a Aldie
// Moved some functions to silenced bulletweapon.
// 
// 10    6/15/98 9:12p Aldie
// Updated to silenced bullet
// 
// 9     3/30/98 2:36p Jimdose
// Changed from subclass of Magnum to subclass of BulletWeapon
// 
// 8     3/23/98 1:33p Jimdose
// Revamped event and command system
// 
// 7     3/02/98 8:49p Jimdose
// Changed CLASS_PROTOTYPE to only take the classname
// 
// 6     2/19/98 2:35p Jimdose
// Updated to work with Q2 based progs
// 
// 4     11/18/97 5:30p Markd
// Changed Fire to Shoot
// got rid off a few thinking functions
// 
// 3     10/27/97 2:59p Jimdose
// Removed dependency on quakedef.h
// 
// 2     10/24/97 8:13p Jimdose
// Created file.
//
// DESCRIPTION:
// Magnum.
// 

#ifndef __MAGNUM_H__
#define __MAGNUM_H__

#include "g_local.h"
#include "item.h"
#include "weapon.h"
#include "bullet.h"

class EXPORT_FROM_DLL Magnum : public BulletWeapon
	{
	public:
		CLASS_PROTOTYPE( Magnum );
		
								Magnum::Magnum();
		virtual void		Shoot( Event *ev );
      virtual qboolean  Drop( void );
	};

#endif /* magnum.h */
