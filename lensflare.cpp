//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/lensflare.cpp                    $
// $Revision:: 17                                                             $
//   $Author:: Jimdose                                                        $
//     $Date:: 10/19/98 12:07a                                                $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/lensflare.cpp                         $
// 
// 17    10/19/98 12:07a Jimdose
// made all code use fast checks for inheritance (no text lookups when
// possible)
// isSubclassOf no longer requires ::_classinfo()
// 
// 16    10/09/98 8:58p Aldie
// Lightstyle on lensflare from Lights
// 
// 15    10/09/98 5:23p Aldie
// Added some commands for lightstyle.
// 
// 14    9/25/98 2:59p Aldie
// More lensflare stuff. Added lightstyles
// 
// 13    5/03/98 4:34p Jimdose
// Changed Vector class
// 
// 12    3/30/98 11:39p Markd
// Added modelIndex stuff
// 
// 11    3/23/98 1:31p Jimdose
// Revamped event and command system
// 
// 10    3/18/98 2:05p Aldie
// Changed the filename of the sprite model extension to .spr
// 
// 9     3/14/98 4:40p Aldie
// Added scale to lensflare.
// 
// 8     3/13/98 7:25p Aldie
// Expanded lensflare to have color, dlights, and radius.
// 
// 7     3/12/98 5:37p Markd
// Changed model file for lensflare from sp3 file to def file
// 
// 6     3/12/98 3:02p Aldie
// Cleaned up lensflare.
// 
// 5     3/12/98 2:42p Aldie
// Random starting positions for lensflare rotation offset.
// 
// 4     3/10/98 7:45p Aldie
// 
// 3     3/07/98 5:16p Aldie
// Added new sprite.
// 
// 2     3/06/98 7:16p Aldie
// First try at lensflare.
//
// DESCRIPTION:LensFlare effect
// 
#include "g_local.h"
#include "entity.h"
#include "lensflare.h"
#include "light.h"

CLASS_DECLARATION( Trigger, LensFlare, "lensflare" );

/*****************************************************************************/
/*SINED lensflare (0 1 0) (-8 -8 -8) (8 8 8)
   
"color"      (r g b) 3 values between 0 and 1.0 (Default is 1.0 1.0 1.0)
"light"      If set,make the flare emit a dynamic light. (Default is not set)
"radius"     Radius of the dynamic light (Default is 200) 
"scale"      Factor to scale the lensflare (Default is 0.5)
"sprite"     Sprite model to use for the flare (Default is sprites/glow.spr")
"lightstyle" Lightstyle of the lensflare (Default is none)
/*****************************************************************************/

Event EV_LensFlare_Activate( "activate" );
Event EV_LensFlare_Deactivate( "deactivate" );
Event EV_LensFlare_Lightstyle( "lightstyle" );
Event EV_LensFlare_SetLightstyle( "setlightstyle" );

ResponseDef LensFlare::Responses[] =
	{
	   { &EV_LensFlare_Activate,        ( Response )LensFlare::Activate },
	   { &EV_LensFlare_Deactivate,      ( Response )LensFlare::Deactivate },
	   { &EV_LensFlare_Lightstyle,      ( Response )LensFlare::Lightstyle },
	   { &EV_LensFlare_SetLightstyle,   ( Response )LensFlare::SetLightstyle },
      { NULL, NULL }
	};

LensFlare::LensFlare( void )
	{
   Vector   color;
   Vector   def;
   int      dlight,radius;
   float    scale;
   int      lightstyle;

   color  = G_GetVectorArg("color",Vector(1,1,1));
   dlight = G_GetIntArg("light",0);
   radius = G_GetIntArg("radius",0);
   scale  = G_GetFloatArg("scale", 0.5f);
   model  = G_GetSpawnArg("sprite", "sprites/glow.spr" );
   lightstyle = G_GetIntArg("lightstyle", 255 );

   setModel( model );
	setMoveType( MOVETYPE_NONE );
	setSolidType( SOLID_NOT );

   edict->s.renderfx |= (RF_LENSFLARE);
   
   if (dlight)
      edict->s.renderfx |= (RF_DLIGHT);

   edict->s.angles[ROLL] = rand() % 360;
   edict->s.alpha        = 1.0f;
   edict->s.color_r      = color.x;
   edict->s.color_g      = color.y;
   edict->s.color_b      = color.z;
   edict->s.radius       = radius;
   edict->s.scale        = scale;
   edict->s.skinnum      = lightstyle;

   PostEvent( EV_LensFlare_SetLightstyle, 0 );
   }

void LensFlare::SetLightstyle
   (
   Event *ev
   )

   {
   int         num;
   const char  *name;
   Entity      *ent;

   name = Target();
	if ( name && strcmp( name, "" ) )
		{
		num = 0;
		do
			{
			num = G_FindTarget( num, name );
			if ( !num )
				{
				break;
				}
			
         ent = G_GetEntity( num );
         assert( ent );
         if ( ent->isSubclassOf( Light ) )
            {
            Light *light;

            light = ( Light * )ent;
            edict->s.skinnum = light->GetStyle();
            }
         } 
         while ( 1 );
      }
   }

void LensFlare::Activate
   (
   Event *ev
   )

   {
   setSolidType( SOLID_BSP );
   showModel();
   }

void LensFlare::Deactivate
   (
   Event *ev
   )

   {
   hideModel();
   }

void LensFlare::Lightstyle
   (
   Event *ev
   )

   {
   edict->s.skinnum = ev->GetInteger( 1 );
   }
