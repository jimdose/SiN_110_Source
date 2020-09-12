//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/skeet.h                          $
// $Revision:: 5                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 9/21/98 4:57p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/skeet.h                               $
// 
// 5     9/21/98 4:57p Markd
// Added archive and unarchive functions
// 
// 4     5/24/98 4:48p Jimdose
// Made char *'s const
// 
// 3     5/19/98 4:25p Aldie
// Fixed skeet death
// 
// 2     5/15/98 1:04p Aldie
//
// DESCRIPTION: Skeey and Pigeons
// 

class EXPORT_FROM_DLL Pigeon : public Entity
	{
   private:
      float maxspeed;
      float acceleration;
      float speed;
      int   owner;
      str   name;
	public:
      CLASS_PROTOTYPE( Pigeon );
      void Setup( Entity *owner,	Vector pos,	Vector dir, float pspeed, float pgrav,	float pduration, const char *name );
      void RemovePigeon( Event *ev);
      void Killed(Event *ev);
      virtual void Archive( Archiver &arc );
      virtual void Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Pigeon::Archive
	(
	Archiver &arc
	)
   {
   Entity::Archive( arc );
   arc.WriteFloat( maxspeed );
   arc.WriteFloat( acceleration );
   arc.WriteFloat( speed );
   arc.WriteInteger( owner );
   arc.WriteString( name );
   }

inline EXPORT_FROM_DLL void Pigeon::Unarchive
	(
	Archiver &arc
	)
   {
   Entity::Unarchive( arc );
   arc.ReadFloat( &maxspeed );
   arc.ReadFloat( &acceleration );
   arc.ReadFloat( &speed );
   arc.ReadInteger( &owner );
   arc.ReadString( &name );
   }


class EXPORT_FROM_DLL SkeetLauncher : public Entity
	{
   private:
      Vector launchAngle;
      float pspeed;
      float pgravity;
      float pduration;
      float speed_var;
      float x_var;
      float y_var;
      float z_var;
   public:
      CLASS_PROTOTYPE( SkeetLauncher );
      SkeetLauncher( );
      void Launch(Event *ev);
      void SetXdir(Event *ev);
      void SetYdir(Event *ev);
      void SetZdir(Event *ev);
      void SetXvar(Event *ev);
      void SetYvar(Event *ev);
      void SetZvar(Event *ev);
      void SetSpeed(Event *ev);
      void SetGravity(Event *ev);
      void SetDuration(Event *ev);
      void SetSpeedVar(Event *ev);
      virtual void Archive( Archiver &arc );
      virtual void Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void SkeetLauncher::Archive
	(
	Archiver &arc
	)
   {
   Entity::Archive( arc );
   arc.WriteVector( launchAngle );
   arc.WriteFloat( pspeed );
   arc.WriteFloat( pgravity );
   arc.WriteFloat( pduration );
   arc.WriteFloat( speed_var );
   arc.WriteFloat( x_var );
   arc.WriteFloat( y_var );
   arc.WriteFloat( z_var );
   }

inline EXPORT_FROM_DLL void SkeetLauncher::Unarchive
	(
	Archiver &arc
	)
   {
   Entity::Unarchive( arc );
   arc.ReadVector( &launchAngle );
   arc.ReadFloat( &pspeed );
   arc.ReadFloat( &pgravity );
   arc.ReadFloat( &pduration );
   arc.ReadFloat( &speed_var );
   arc.ReadFloat( &x_var );
   arc.ReadFloat( &y_var );
   arc.ReadFloat( &z_var );
   }
