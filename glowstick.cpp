//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/glowstick.cpp                    $
// $Revision:: 12                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 10/24/98 3:14p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/glowstick.cpp                         $
// 
// 12    10/24/98 3:14p Aldie
// Upped the life of sticks
// 
// 11    10/24/98 12:42a Markd
// changed origins to worldorigins where appropriate
// 
// 10    10/07/98 1:17a Aldie
// New model
// 
// 9     7/25/98 7:10p Markd
// Put in EV_Removes for demo
// 
// 8     7/21/98 7:33p Aldie
// Changed def file
// 
// 7     7/20/98 3:52p Aldie
// Fixed the icon
// 
// 6     6/25/98 8:47p Markd
// Added keyed items for Triggers, Rewrote Item class, rewrote every pickup
// method
// 
// 5     6/24/98 1:36p Aldie
// Implementation of inventory system and picking stuff up
// 
// 4     6/20/98 7:03p Aldie
// Changed the avel
// 
// 3     6/20/98 6:53p Aldie
// Changed the model back to hvshell.def
// 
// 2     6/19/98 6:37p Aldie
// First version of glowstick
//
// DESCRIPTION:
// Glowstick for a lightsource

#include "inventoryitem.h" 

class EXPORT_FROM_DLL GlowStick : public InventoryItem
	{
	public:
      CLASS_PROTOTYPE( GlowStick );
                  GlowStick();
      void        Use( Event *ev );
   };

CLASS_DECLARATION( InventoryItem, GlowStick, "powerups_glowstick" )

ResponseDef GlowStick::Responses[] =
	{
      { &EV_InventoryItem_Use,				( Response )GlowStick::Use },
		{ NULL, NULL }
	};

GlowStick::GlowStick
	(
	)

	{
#ifdef SIN_DEMO
   PostEvent( EV_Remove, 0 );
   return;
#endif
   setModel( "glowstick.def" );
   Set( 1 );
	}

void GlowStick::Use
   (
   Event *ev
   )

   {
   Entity   *glowstick;
   Vector   dir;
   
   assert( owner );

   // Make sure there is a glowstick to 
   assert( amount );

   amount--;

   if (amount <= 0)
      {
      owner->RemoveItem( this );
      }

   dir = owner->orientation[ 0 ];

   glowstick = new Entity;

   glowstick->angles = dir.toAngles();
   glowstick->setAngles( glowstick->angles );
 	glowstick->setMoveType( MOVETYPE_BOUNCE );
	glowstick->setSolidType( SOLID_NOT );
   glowstick->setModel( "glowstick.def" );
   glowstick->edict->s.renderfx |= RF_DLIGHT;
	glowstick->avelocity = "500 0 0";
   glowstick->velocity = dir * 500;
   glowstick->edict->s.color_r = 0.4;
   glowstick->edict->s.color_g = 1.0;
   glowstick->edict->s.color_b = 0.1;
   glowstick->edict->s.radius  = 200;
   glowstick->setOrigin( owner->worldorigin + Vector(0,0,owner->viewheight) );
   glowstick->PostEvent(EV_Remove, 60);
   }

