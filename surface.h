//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/surface.h                        $
// $Revision:: 19                                                             $
//   $Author:: Jimdose                                                        $
//     $Date:: 10/25/98 11:53p                                                $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/surface.h                             $
// 
// 19    10/25/98 11:53p Jimdose
// added EXPORT_TEMPLATE
// 
// 18    10/20/98 8:26p Markd
// Added Attacker to DamageSurface stuff
// 
// 17    10/10/98 9:59p Jimdose
// made savegames work with surfaces
// 
// 16    10/05/98 11:02p Jimdose
// Added destructor
// Made Reset free up all surfaces
// 
// 15    9/21/98 10:15p Markd
// Putting archiving and unarchiving functions in
// 
// 14    9/21/98 4:21p Markd
// Put in archive functions and rewrote all archive routines
// 
// 13    9/18/98 8:14p Markd
// rewrote surface system so that surfaces are now damaged by surface name
// instead of by surfinfo
// 
// 12    8/31/98 7:45p Aldie
// Updated surface data structure and removed surfinfo field
// 
// 11    8/29/98 9:53p Jimdose
// moved prototype of CreateSurfaces from g_local.h
// 
// 10    6/08/98 7:23p Aldie
// Added damage command back in
// 
// 9     5/25/98 2:29p Aldie
// Fixed issues with not loading game dll
// 
// 8     5/24/98 9:00p Jimdose
// made SetName us G_CopyString to allocate a string
// 
// 7     5/24/98 4:48p Jimdose
// Made char *'s const
// 
// 6     5/13/98 4:47p Aldie
// Update damage surfaces
// 
// 5     5/05/98 2:44p Aldie
// Added server side surface states
// 
// 3     5/04/98 8:12p Aldie
// Added texture states.
// 
// 2     3/23/98 1:33p Jimdose
// Revamped event and command system
//
// DESCRIPTION:
// Controls surfaces
// 

#ifndef __SURFACE_H__
#define __SURFACE_H__

#include "g_local.h"
#include "listener.h"

extern Event EV_Surface_TransOn;
extern Event EV_Surface_TransOff;
extern Event EV_Surface_TransToggle;
extern Event EV_Surface_TransMag;
extern Event EV_Surface_Translucence;
extern Event EV_Surface_Magnitude;
extern Event EV_Surface_Frequency;
extern Event EV_Surface_TransAngle;
extern Event EV_Surface_DamageFrame;

class EXPORT_FROM_DLL Surface : public Class
   {
	private:
		str	surface_name;
      int	surface_number;
      int   damage;
      int   state;
      int   threshold;
      int   numframes;
      int   style;

	public:
      CLASS_PROTOTYPE( Surface );
      const char  *SurfaceName() {return surface_name.c_str();}
      int         SurfaceNumber() {return surface_number;};
      int         Damage() {return damage;};
      int         State() {return state;};
      int         Threshold() {return threshold;};
      int         NumFrames() {return numframes;};
      int         LightStyle() {return style;};
      void        SetThreshold(int num) {threshold = num;};
      void        SetNumFrames(int num) {numframes = num;};
      void        SetLightStyle(int num) {style = num;};
      void        SetDamage(int num) {damage = num;};
      void        SetNumber(int num) {surface_number = num;};
      void        SetState(int num) {state = num;};
      void        SetName(const char *surf_name) 
         {
         surface_name = str( surf_name );
         };
      virtual void Archive( Archiver &arc );
      virtual void Unarchive( Archiver &arc );

	};

inline EXPORT_FROM_DLL void Surface::Archive
	(
	Archiver &arc
	)
   {
   arc.WriteInteger( damage );
   arc.WriteInteger( state );
   }

inline EXPORT_FROM_DLL void Surface::Unarchive
	(
	Archiver &arc
	)
   {
   arc.ReadInteger( &damage );
   arc.ReadInteger( &state );
   }

#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL Container<Surface *>;
#endif

class EXPORT_FROM_DLL SurfaceModifier : public Listener
	{
   private:
      Container<Surface *>	surfaceList;
      void     DoDamage ( trace_t * trace, const char * group_name, float damage, Entity * attacker = world );

	public:
      CLASS_PROTOTYPE( SurfaceModifier );

               ~SurfaceModifier();
      void     CreateSurface (const char *surf_name, csurface_t *surfinfo);
      int      AddSurface(Surface *surf);
      void     RemoveSurface(const char *surf_name);
      int      SurfaceExists(const char *surf_name);
      Surface  *GetSurface(const char *surf_name);
      void     DamageSurface( trace_t * trace, float damage, Entity * attacker );
      void     Reset();

      void TranslationOn(Event *ev);
      void TranslationOff(Event *ev);
      void TranslationToggle(Event *ev);
      void SetTranslationMagnitude(Event *ev);
      void SetTranslationAngle(Event *ev);
      void SetTranslucence(Event *ev);
      void SetMagnitude(Event *ev);
      void SetFrequency(Event *ev);
      void SetDamageFrame(Event *ev);
      void SetDamage(Event *ev);
      virtual void Archive( Archiver &arc );
      virtual void Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void SurfaceModifier::Archive
	(
	Archiver &arc
	)
   {
   int i;
   Surface * surf;
   netsurface_t *s;
   int num;

   Listener::Archive( arc );

   num = surfaceList.NumObjects();
   arc.WriteInteger( num );
   for( i = 1; i <= num; i++ )
      {
      //
      // we only save out the dynamic fields
      //
      surf = surfaceList.ObjectAt( i );
      arc.WriteObject( surf );
      }

   // write the surface states
   s = g_surfaces;
   for( i = 0; i < game.maxsurfaces; i++, s++ )
      {
      arc.WriteBoolean( s->inuse );
      if ( s->inuse )
         {
         arc.WriteRaw( &s->s, sizeof( s->s ) );
         }
      }
   }

inline EXPORT_FROM_DLL void SurfaceModifier::Unarchive
	(
	Archiver &arc
	)
   {
   int i;
   Surface *surf;
   netsurface_t *s;
   int num;
   char *name;

   Listener::Unarchive( arc );

   // get the number
   arc.ReadInteger( &num );
   for( i = 1; i <= num; i++ )
      {
      //
      // we only read in the dynamic fields
      //
      surf = surfaceList.ObjectAt( i );
      arc.ReadObject( surf );
      }

   // read the surface states
   s = g_surfaces;
   for( i = 0; i < game.maxsurfaces; i++, s++ )
      {
      arc.ReadBoolean( &s->inuse );
      if ( s->inuse )
         {
         name = s->s.name;
         arc.ReadRaw( &s->s, sizeof( s->s ) );
         s->s.name = name;
         }
      }
   }

extern SurfaceModifier surfaceManager;

extern "C" void CreateSurfaces( csurface_t *surfaces, int count );

#endif /* surface.h */
