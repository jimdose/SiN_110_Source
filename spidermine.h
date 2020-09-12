//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/spidermine.h                        $
// $Revision:: 15                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 11/11/98 5:46p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/spidermine.h                             $
// 
// 15    11/11/98 5:46p Aldie
// Don't drop spidermines
// 
// 14    11/09/98 12:13a Aldie
// Made it so you can reclaim your mines when you die in deathmatch
// 
// 13    10/25/98 11:53p Jimdose
// added EXPORT_TEMPLATE
// 
// 12    10/22/98 5:01p Aldie
// Fixed some spidermine bugs
// 
// 11    10/08/98 12:03a Jimdose
// Got rid of unused variables speed and direction from Mine
// Added archive functions for Detonator
// 
// 10    9/21/98 4:50p Markd
// Fixed projectile owner
// 
// 9     9/21/98 4:21p Markd
// Put in archive functions and rewrote all archive routines
// 
// 8     9/13/98 8:36p Aldie
// Don't autoswitch to detonator
// 
// 7     8/29/98 5:27p Markd
// added specialfx, replaced misc with specialfx where appropriate
// 
// 6     8/25/98 5:30p Aldie
// New version of the spidermine which uses cameras
// 
// 5     6/08/98 9:04p Aldie
// Added ReadyToUse support
// 
// 4     6/08/98 8:21p Aldie
// Updated mines with new anim and logic
// 
// 3     6/08/98 11:49a Aldie
// New version of spidermine.
// 
// 2     5/11/98 11:25a Markd
// First time
// 
// 1     5/11/98 11:10a Markd
// 
// 1     5/11/98 10:24a Markd
// 
// 1     5/11/98 10:20a Markd
// 
// 1     5/11/98 10:18a Markd
// 
// 1     5/11/98 9:55a Markd
// 
// DESCRIPTION:
// Spider Mines
// 

#ifndef __SPIDERMINE_H__
#define __SPIDERMINE_H__

#include "g_local.h"
#include "item.h"
#include "weapon.h"
#include "specialfx.h"

class Detonator;

typedef SafePtr<Detonator> DetonatorPtr;
#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL SafePtr<Detonator>;
#endif

class EXPORT_FROM_DLL Mine : public Projectile
	{
   private:
      DetonatorPtr      detonator;
      qboolean          detonate;
      qboolean          sticky;

	public:
		CLASS_PROTOTYPE( Mine );

		void					Explode( Event *ev );
		void					Setup( Entity *owner, Vector pos, Vector dir );
      void              SlideOrStick( Event *ev );
      void              CheckForTargets( Event *ev );
      void              Run( Event *ev );
      void              SetDetonator( Detonator *det );
      qboolean          IsOwner( Sentient *sent );
      virtual void Archive( Archiver &arc );
      virtual void Unarchive( Archiver &arc );
	};

#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL SafePtr<Mine>;
#endif

typedef SafePtr<Mine> MinePtr;

#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL Container<MinePtr>;
#endif

class EXPORT_FROM_DLL Detonator : public Weapon
	{
   private: 
   public:
      Container<MinePtr>	 mineList;
      int                   currentMine;

      CLASS_PROTOTYPE( Detonator );
		
                            Detonator::Detonator();
      virtual void		    Shoot( Event *ev );
      virtual void		    DoneFiring( Event *ev );
              void          AddMine( Mine *mine );
              void          RemoveMine( Mine *mine );
              void          CycleCamera( Event *ev );
      virtual qboolean      AutoChange( void );
              qboolean      IsDroppable( void );
      virtual void          Archive( Archiver &arc );
      virtual void          Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Mine::Archive
	(
	Archiver &arc
	)
   {
   Projectile::Archive( arc );
   arc.WriteSafePointer( detonator );
   arc.WriteBoolean( detonate );
   arc.WriteBoolean( sticky );
   }

inline EXPORT_FROM_DLL void Mine::Unarchive
	(
	Archiver &arc
	)
   {
   Projectile::Unarchive( arc );
   arc.ReadSafePointer( &detonator );
   arc.ReadBoolean( &detonate );
   arc.ReadBoolean( &sticky );
   }

inline EXPORT_FROM_DLL void Detonator::Archive
	(
	Archiver &arc
	)

   {
   int i;
   int num;

   Weapon::Archive( arc );
   
   arc.WriteInteger( currentMine );

   num = mineList.NumObjects();
   arc.WriteInteger( num );
   for( i = 1; i <= num; i++ )
      {
      arc.WriteSafePointer( mineList.ObjectAt( i ) );
      }
   }

inline EXPORT_FROM_DLL void Detonator::Unarchive
	(
	Archiver &arc
	)

   {
   int i;
   int num;

   mineList.FreeObjectList();

   Weapon::Unarchive( arc );

   arc.ReadInteger( &currentMine );

   arc.ReadInteger( &num );
   mineList.Resize( num );
   for( i = 1; i <= num; i++ )
      {
      arc.ReadSafePointer( mineList.AddressOfObjectAt( i ) );
      }
   }

class EXPORT_FROM_DLL SpiderMine : public Weapon
	{
   private:
      MinePtr           currentMine;
      DetonatorPtr      detonator;
	public:
		CLASS_PROTOTYPE( SpiderMine );
		
								SpiderMine::SpiderMine();
		virtual void		Shoot( Event *ev );
      virtual void		DoneFiring( Event *ev );
      virtual qboolean  ReadyToUse( void );
              void      ChangeToDetonator( Event *ev ); 
              void      SetDetonator( Detonator *det );
      virtual void      SetOwner( Sentient *sent );
              qboolean  IsDroppable( void );
      virtual void Archive( Archiver &arc );
      virtual void Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void SpiderMine::Archive
	(
	Archiver &arc
	)
   {
   Weapon::Archive( arc );
   arc.WriteSafePointer( currentMine );
   arc.WriteSafePointer( detonator );
   }

inline EXPORT_FROM_DLL void SpiderMine::Unarchive
	(
	Archiver &arc
	)
   {
   Weapon::Unarchive( arc );
   arc.ReadSafePointer( &currentMine );
   arc.ReadSafePointer( &detonator );
   }


#endif /* SpiderMine.h */
