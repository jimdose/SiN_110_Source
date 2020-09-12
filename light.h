//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/light.h                          $
// $Revision:: 12                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 10/09/98 9:01p                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/light.h                               $
// 
// 12    10/09/98 9:01p Aldie
// Lightstyle on lensflare from Lights
// 
// 11    9/28/98 9:12p Markd
// Put in archive and unarchive functions
// 
// 10    6/17/98 7:18p Markd
// added off_style and on_style
// 
// 9     4/30/98 9:24p Jimdose
// Changed use of string to str class
// 
// 8     3/23/98 1:33p Jimdose
// Revamped event and command system
// 
// 7     3/02/98 8:49p Jimdose
// Changed CLASS_PROTOTYPE to only take the classname
// 
// 6     3/02/98 5:41p Jimdose
// Created file
// 
// DESCRIPTION:
// Classes for creating and controlling lights.
// 

#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "g_local.h"
#include "entity.h"
#include "trigger.h"

extern Event EV_Light_TurnOn;
extern Event EV_Light_TurnOff;
extern Event EV_Light_SetLightStyle;

class EXPORT_FROM_DLL BaseLight : public Trigger
	{
	protected:
		int		style;
		str		lightstyle;
      str      on_style;
      str      off_style;

	public:
      CLASS_PROTOTYPE( BaseLight );
		
								BaseLight();
		void					SetLightStyle( const char *stylestring );
		void					EventSetLightStyle( Event *ev );
      int               GetStyle( void );
		void					TurnOn( Event *ev );
		void					TurnOff( Event *ev );
	   virtual void      Archive( Archiver &arc );
      virtual void      Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void BaseLight::Archive
	(
	Archiver &arc
	)
   {
   Trigger::Archive( arc );

   arc.WriteInteger( style );
   arc.WriteString( lightstyle );
   arc.WriteString( on_style );
   arc.WriteString( off_style );
   }

inline EXPORT_FROM_DLL void BaseLight::Unarchive
	(
	Archiver &arc
	)
   {
   Trigger::Unarchive( arc );

   arc.ReadInteger( &style );
   arc.ReadString( &lightstyle );
   arc.ReadString( &on_style );
   arc.ReadString( &off_style );
   }

class EXPORT_FROM_DLL LightRamp : public BaseLight
	{
	protected:
		float		minlevel;
		float		maxlevel;
		float		currentlevel;
		float		rate;

	public:
      CLASS_PROTOTYPE( LightRamp );
		
				         LightRamp();
		void	         RampLight( Event *ev );
		void	         StartRamp( Event *ev );
	   virtual void   Archive( Archiver &arc );
      virtual void   Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void LightRamp::Archive
	(
	Archiver &arc
	)
   {
   BaseLight::Archive( arc );

   arc.WriteFloat( minlevel );
   arc.WriteFloat( maxlevel );
   arc.WriteFloat( currentlevel );
   arc.WriteFloat( rate );
   }

inline EXPORT_FROM_DLL void LightRamp::Unarchive
	(
	Archiver &arc
	)
   {
   BaseLight::Unarchive( arc );

   arc.ReadFloat( &minlevel );
   arc.ReadFloat( &maxlevel );
   arc.ReadFloat( &currentlevel );
   arc.ReadFloat( &rate );
   }


class EXPORT_FROM_DLL TriggerLightRamp : public LightRamp
	{
	public:
      CLASS_PROTOTYPE( TriggerLightRamp );
	};

class EXPORT_FROM_DLL Light : public BaseLight
	{
	public:
      CLASS_PROTOTYPE( Light );
		
		void					ToggleLight( Event *ev );
								Light();
	};

class EXPORT_FROM_DLL TriggerLightStyle : public Light
	{
	public:
      CLASS_PROTOTYPE( TriggerLightStyle );
	};

#endif /* light.h */
