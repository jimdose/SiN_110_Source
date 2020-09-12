//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/ammo.cpp                         $
// $Revision:: 28                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 10/24/98 2:07p                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/ammo.cpp                              $
// 
// 28    10/24/98 2:07p Aldie
// Moved pickupable function out.
// 
// 27    10/21/98 9:05p Aldie
// Added spear ammo
// 
// 26    10/21/98 5:24p Aldie
// Don't let mutants pickup ammo
// 
// 25    10/14/98 1:01a Jimdose
// change Ammo::Ammo so that it used Set to set amount so that spawnarg values
// are not cleared out
// 
// 24    10/05/98 11:59p Aldie
// Fix spidermines
// 
// 23    6/28/98 4:13p Markd
// simplified setup
// 
// 22    6/25/98 8:47p Markd
// Added keyed items for Triggers, Rewrote Item class, rewrote every pickup
// method
// 
// 21    6/24/98 1:35p Aldie
// Implementation of inventory system and picking stuff up
// 
// 20    6/17/98 1:19a Jimdose
// Moved setOwner to Item.  
// Added EV_Item_Pickup
// 
// 19    6/10/98 5:10p Markd
// Using ExpandAlias method
// 
// 18    6/10/98 1:19p Markd
// Added SetAmmoName and SetAmmoAmount, removed 357 ammo
// 
// 17    6/08/98 7:21p Aldie
// Added SpiderMine ammo
// 
// 16    5/26/98 4:44p Aldie
// Added remove ammo
// 
// 15    5/24/98 8:46p Jimdose
// Made a lot of functions more str-friendly.
// Got rid of a lot of char * based strings
// Cleaned up get spawn arg functions and sound functions
// sound functions now use consistant syntax
// 
// 14    5/24/98 4:48p Jimdose
// Made char *'s const
// 
// 13    5/08/98 2:55p Markd
// Put in Ammo pickup sounds
// 
// 12    4/28/98 5:28p Jimdose
// Changed rocket and sniper ammo from 20 to 10
// 
// 11    4/18/98 3:30p Markd
// Added new shotgun clip type
// 
// 10    4/07/98 9:18p Jimdose
// Added Rockets
// 
// 9     4/07/98 6:42p Jimdose
// Turned off respawn in singleplayer
// 
// 8     4/04/98 6:00p Jimdose
// Made response to EV_Touch be response to EV_Trigger_Effect
// 
// 7     3/31/98 4:21p Jimdose
// Changed model names
// 
// 6     3/30/98 9:54p Jimdose
// Changed location of .def files
// 
// 5     3/30/98 2:31p Jimdose
// Created file
// 
// DESCRIPTION:
// Base class for all ammunition for entities derived from the Weapon class.
// 

#include "g_local.h"
#include "item.h"
#include "ammo.h"

CLASS_DECLARATION( Item, Ammo, NULL );

ResponseDef Ammo::Responses[] =
	{
		{ NULL, NULL }
	};

Ammo::Ammo()
	{
   Set( 0 );
	}

void Ammo::Setup
	(
	const char *model
	)

	{
   const char * m;
	m = G_GetSpawnArg( "model" );
	if ( m )
      {
	   setModel( m );
      }
   else
      {
	   assert( model );
	   setModel( model );
      }
	}

CLASS_DECLARATION( Ammo, Bullet10mm, "ammo_10mm" );

ResponseDef Bullet10mm::Responses[] =
	{
		{ NULL, NULL }
	};

Bullet10mm::Bullet10mm()
	{
	Setup( "357.def" );
	}

CLASS_DECLARATION( Ammo, Bullet50mm, "ammo_50mm" );

ResponseDef Bullet50mm::Responses[] =
	{
		{ NULL, NULL }
	};

Bullet50mm::Bullet50mm()
	{
	Setup( "50mm.def" );
	}

CLASS_DECLARATION( Ammo, BulletPulse, "ammo_pulserifle" );

ResponseDef BulletPulse::Responses[] =
	{
		{ NULL, NULL }
	};

BulletPulse::BulletPulse()
	{
	Setup( "pulse_ammo.def" );
	}

CLASS_DECLARATION( Ammo, BulletSniper, "ammo_sniperrifle" );

ResponseDef BulletSniper::Responses[] =
	{
		{ NULL, NULL }
	};

BulletSniper::BulletSniper()
	{
	Setup( "sniper_ammo.def" );
	}

CLASS_DECLARATION( Ammo, Rockets, "ammo_rockets" );

ResponseDef Rockets::Responses[] =
	{
		{ NULL, NULL }
	};

Rockets::Rockets()
	{
	Setup( "rockets.def" );
	}

CLASS_DECLARATION( Ammo, Spears, "ammo_speargun" );

ResponseDef Spears::Responses[] =
	{
		{ NULL, NULL }
	};

Spears::Spears()
	{
	Setup( "spear_ammo.def" );
	}

CLASS_DECLARATION( Ammo, ShotgunClip, "ammo_shotgunclip" );

ResponseDef ShotgunClip::Responses[] =
	{
		{ NULL, NULL }
	};

ShotgunClip::ShotgunClip()
	{
	Setup( "shotgunclip.def" );
	}

CLASS_DECLARATION( Ammo, SpiderMines, "ammo_spidermines" );

ResponseDef SpiderMines::Responses[] =
	{
		{ NULL, NULL }
	};

SpiderMines::SpiderMines()
	{
	Setup( "mine.def" );
	}

