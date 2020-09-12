//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/genericrocket.cpp                $
// $Revision:: 3                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 10/04/98 10:23p                                                $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/genericrocket.cpp                     $
// 
// 3     10/04/98 10:23p Markd
// Took out NextAttack stuff
// 
// 2     9/15/98 6:46p Aldie
// Generic rocket for pinphat
//
// DESCRIPTION:
// Generic Rocket Launcher - to be used on monsters that have rocket launchers
// shown in their models

#include "g_local.h"
#include "genericrocket.h"
#include "rocketlauncher.h"

CLASS_DECLARATION( RocketLauncher, GenericRocket, "weapon_genericrocket" );

ResponseDef GenericRocket::Responses[] =
	{
	   { &EV_Weapon_Shoot,  ( Response )GenericRocket::Shoot },
		{ NULL, NULL }
	};

GenericRocket::GenericRocket()
	{
   SetModels( NULL, "view_genrocket.def" );
	SetAmmo( "Rockets", 1, 5 );
	}

void GenericRocket::Shoot
	(
	Event *ev
	)

	{
 	Rocket	*rocket;
	Vector	pos;
	Vector	dir;

	assert( owner );
	if ( !owner )
		{
		return;
		}

	GetMuzzlePosition( &pos, &dir );

	rocket = new Rocket;
	rocket->Setup( owner, pos, dir );
	}

