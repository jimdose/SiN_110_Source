//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/hammer.cpp                          $
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
// $Log:: /Quake 2 Engine/Sin/code/game/hammer.cpp                               $
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
// Hammer Melee weapon
// 

#include "g_local.h"
#include "item.h"
#include "weapon.h"
#include "fists.h"

class EXPORT_FROM_DLL Hammer : public Fists
	{
	public:
		CLASS_PROTOTYPE( Hammer );
		
							Hammer::Hammer();
      virtual qboolean       IsDroppable( void );
	};

CLASS_DECLARATION( Fists, Hammer, NULL);

ResponseDef Hammer::Responses[] =
	{
		{ NULL, NULL }
	};

Hammer::Hammer()
	{
#ifdef SIN_DEMO
   PostEvent( EV_Remove, 0 );
   return;
#endif
	SetModels( "sledgeham.def", "view_sledge.def" );
	SetAmmo( NULL, 0, 0 );
	SetRank( 11, 11 );	
   strike_reach = 48;
   strike_damage = 55;
	SetMaxRange( strike_reach );
   SetType( WEAPON_MELEE );
   kick = 25;
	}

qboolean Hammer::IsDroppable
	(
	void
	)
	{
	return false;
   }
