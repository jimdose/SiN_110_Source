//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/earthquake.cpp                   $
// $Revision:: 13                                                             $
//   $Author:: Jimdose                                                        $
//     $Date:: 11/08/98 10:47p                                                $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/earthquake.cpp                        $
// 
// 13    11/08/98 10:47p Jimdose
// moved earthquake to level struct
// 
// 12    10/22/98 5:56p Markd
// Made a bunch of global sounds local to that entity
// 
// 11    8/18/98 11:08p Markd
// Added new Alias System
// 
// 10    7/30/98 4:34p Aldie
// Don't respond to touch
// 
// 9     5/24/98 8:46p Jimdose
// Made a lot of functions more str-friendly.
// Got rid of a lot of char * based strings
// Cleaned up get spawn arg functions and sound functions
// sound functions now use consistant syntax
// 
// 8     5/22/98 12:35p Aldie
// Removed some unused functions
// 
// 7     5/22/98 12:19p Aldie
// Updated color of earthquake in SinEd
// 
// 6     5/21/98 10:58a Aldie
// Removed a printf
// 
// 5     5/20/98 10:21p Aldie
// Updated earthquake to new event system, may want to add radius later.
// 
// 3     12/06/97 4:50p Markd
// Added interpretCommands. 
// Added GetArgs as commands for future processing
// 
// 2     10/27/97 7:32p Jimdose
// Created file
//
// DESCRIPTION:
// Earthquake trigger causes a localized earthquake when triggered.
// The earthquake effect is visible to the user as the shaking of his screen.
// 
#include "earthquake.h"

/*****************************************************************************/
/*SINED func_earthquake (.5 .5 .8) (-8 -8 -8) (8 8 8)
 Causes an earthquake
"duration" is the duration of the earthquake.  Default is 0.8 seconds.
/*****************************************************************************/

CLASS_DECLARATION( Trigger, Earthquake, "func_earthquake" )

Event EV_Earthquake_Deactivate( "earthquake_deactivate" );

ResponseDef Earthquake::Responses[] =
	{
      { &EV_Touch,                     NULL },
      { &EV_Trigger_Effect,				( Response )Earthquake::Activate },
      { &EV_Earthquake_Deactivate,     ( Response )Earthquake::Deactivate },
      { NULL, NULL }
   };

Earthquake::Earthquake
   (
   void
   )

	{
   const char * name;

	duration = G_GetFloatArg( "duration", 0.8f );
   quakeactive = false;

   // cache in the quake sound
   name = gi.GlobalAlias_FindRandom( "earthquake" );
   gi.soundindex( name );
	}

EXPORT_FROM_DLL void Earthquake::Activate
   (
   Event *ev
   )

	{
	float newtime;
	Event *event;

	newtime = duration + level.time;
	if ( newtime > level.earthquake )
		{
		level.earthquake = newtime;
		}
   quakeactive = true;
   RandomGlobalSound( "earthquake", 1, CHAN_VOICE|CHAN_NO_PHS_ADD, ATTN_NONE );
   event = new Event(EV_Earthquake_Deactivate);
	PostEvent(event,duration);
   };

EXPORT_FROM_DLL void Earthquake::Deactivate
   (
   Event *ev
   )

   {
   quakeactive = false;
   level.earthquake = 0;
   RandomGlobalSound( "null_sound", 1, CHAN_VOICE|CHAN_NO_PHS_ADD, ATTN_NORM );
   }
