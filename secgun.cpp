//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/secgun.cpp                          $
// $Revision:: 2                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 10/21/98 12:05a                                                $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/secgun.cpp                               $
// 
// 2     10/21/98 12:05a Markd
// First time
// 
// 1     10/20/98 11:32p Markd
// 
// DESCRIPTION:
// Securton mounted gun
// 

#include "g_local.h"
#include "item.h"
#include "weapon.h"
#include "genericbullet.h"
#include "secgun.h"


CLASS_DECLARATION( GenericBullet, Secgun, "weapon_secgun" );

ResponseDef Secgun::Responses[] =
	{
	   { &EV_Weapon_Shoot,           ( Response )Secgun::Shoot },
		{ NULL, NULL }
	};

Secgun::Secgun
   (
   )
	
   {
	SetModels( "secgun.def", "view_secgun.def" );
	SetAmmo( NULL, 0, 0 );
   SetType( WEAPON_2HANDED_LO );
   notdroppable = true;
	}


void Secgun::Shoot
	(
	Event *ev
	)

	{
   FireBullets( 1, "300 300 300", 28, 36, DAMAGE_BULLET, MOD_CHAINGUN, false );
	NextAttack( 0 );
	}

