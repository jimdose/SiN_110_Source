//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/object.h                         $
// $Revision:: 7                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 9/22/98 12:49p                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/object.h                              $
// 
// 7     9/22/98 12:49p Markd
// Put in archive and unarchive functions
// 
// 6     8/29/98 7:16p Markd
// Added FireBarrel
// 
// 5     8/09/98 5:50p Markd
// Rewrote ThrowObjects pickup and throw
// 
// 4     8/08/98 8:24p Markd
// Added ThrowObject
// 
// 3     4/10/98 1:24a Markd
// Got rid of damage func
// 
// 2     4/05/98 10:53p Markd
// first time
// 
// 1     4/05/98 10:51p Markd
// 
// DESCRIPTION:
// Object class
// 

#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "g_local.h"
#include "entity.h"
#include "specialfx.h"

class EXPORT_FROM_DLL Object : public Entity
	{
   private:
	public:
      CLASS_PROTOTYPE( Object );
							   Object::Object();
      void              Killed(Event *ev);
	};

extern Event EV_ThrowObject_Pickup;
extern Event EV_ThrowObject_Throw;

class EXPORT_FROM_DLL ThrowObject : public Object
	{
   private:
      int               owner;
      Vector            pickup_offset;
      str               throw_sound;
	public:
      CLASS_PROTOTYPE( ThrowObject );
							   ThrowObject::ThrowObject();
      void              Touch(Event *ev);
      void              Throw( Event * ev );
      void              Pickup( Event * ev );
      void              PickupOffset( Event * ev );
      void              ThrowSound( Event * ev );
	   virtual void      Archive( Archiver &arc );
      virtual void      Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void ThrowObject::Archive
	(
	Archiver &arc
	)
   {
   Object::Archive( arc );

   arc.WriteInteger( owner );
   arc.WriteVector( pickup_offset );
   arc.WriteString( throw_sound );
   }

inline EXPORT_FROM_DLL void ThrowObject::Unarchive
	(
	Archiver &arc
	)
   {
   Object::Unarchive( arc );

   arc.ReadInteger( &owner );
   arc.ReadVector( &pickup_offset );
   arc.ReadString( &throw_sound );
   }


class EXPORT_FROM_DLL FireBarrel : public Object
	{
   private:
      FireSprite        *fire;
	public:
      CLASS_PROTOTYPE( FireBarrel );
							   FireBarrel::FireBarrel();
							   FireBarrel::~FireBarrel();
	   virtual void      Archive( Archiver &arc );
      virtual void      Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void FireBarrel::Archive
	(
	Archiver &arc
	)
   {
   Object::Archive( arc );

   arc.WriteObjectPointer( fire );
   }

inline EXPORT_FROM_DLL void FireBarrel::Unarchive
	(
	Archiver &arc
	)
   {
   Object::Unarchive( arc );

   arc.ReadObjectPointer( ( Class ** )&fire );
   }

#endif /* object.h */
