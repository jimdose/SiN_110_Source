//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/mutanthands.cpp                     $
// $Revision:: 11                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 10/11/98 5:32p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/mutanthands.cpp                          $
// 
// 11    10/11/98 5:32p Aldie
// Tweak damage
// 
// 10    10/10/98 11:44p Aldie
// Tweak damage and reach
// 
// 9     9/22/98 12:49p Markd
// Put in archive and unarchive functions
// 
// 8     8/06/98 6:58p Jimdose
// Added min/max range, and projectile speed
// 
// 7     7/25/98 7:10p Markd
// Put in EV_Removes for demo
// 
// 6     7/22/98 9:57p Markd
// Defined weapon type
// 
// 5     6/19/98 9:30p Jimdose
// Moved gun orientation code to Weapon
// 
// 4     6/10/98 10:02p Markd
// got em working with fists subclass
// 
// 3     5/16/98 5:00p Markd
// Added RF_XFLIP stuff
// 
// 2     5/11/98 11:24a Markd
// First time
// 
// 1     5/11/98 10:18a Markd
// 
// 1     5/11/98 9:55a Markd
// 
// DESCRIPTION:
// Mutant Hands
// 

#include "g_local.h"
#include "mutanthands.h"

CLASS_DECLARATION( Fists, MutantHands, NULL);

ResponseDef MutantHands::Responses[] =
	{
		{ NULL, NULL }
	};

MutantHands::MutantHands()
	{
#ifdef SIN_DEMO
   PostEvent( EV_Remove, 0 );
   return;
#endif
	SetModels( NULL, "view_mutanthands.def" );
	SetAmmo( NULL, 0, 0 );
	SetRank( 11, 11 );	
   strike_reach  = 75;
   strike_damage = 100;
	SetMaxRange( strike_reach );
   SetType( WEAPON_MELEE );
   kick = 25;
   meansofdeath = MOD_MUTANTHANDS;
	}

