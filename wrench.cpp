//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/wrench.cpp                          $
// $Revision:: 4                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 10/04/98 10:25p                                                $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/wrench.cpp                               $
// 
// 4     10/04/98 10:25p Markd
// Added IsDroppable
// 
// 3     9/29/98 7:07p Markd
// changed models for these weapons
// 
// 2     9/24/98 12:03p Markd
// new melee weapons
// 
// 1     9/24/98 11:59a Markd
// 
// DESCRIPTION:
// Wrench Melee weapon
// 

#include "g_local.h"
#include "item.h"
#include "weapon.h"
#include "fists.h"

class EXPORT_FROM_DLL Wrench : public Fists
	{
	public:
		CLASS_PROTOTYPE( Wrench );
		
							Wrench::Wrench();
      virtual qboolean       IsDroppable( void );
	};

CLASS_DECLARATION( Fists, Wrench, NULL);

ResponseDef Wrench::Responses[] =
	{
		{ NULL, NULL }
	};

Wrench::Wrench()
	{
#ifdef SIN_DEMO
   PostEvent( EV_Remove, 0 );
   return;
#endif
	SetModels( "wrench.def", "view_wrench.def" );
	SetAmmo( NULL, 0, 0 );
	SetRank( 11, 11 );	
   strike_reach = 48;
   strike_damage = 55;
	SetMaxRange( strike_reach );
   SetType( WEAPON_MELEE );
   kick = 25;
	}

qboolean Wrench::IsDroppable
	(
	void
	)
	{
	return false;
   }
