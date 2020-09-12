//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/animals.cpp                      $
// $Revision:: 8                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 11/16/98 11:15p                                                $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/animals.cpp                           $
// 
// 8     11/16/98 11:15p Markd
// Added fish
// 
// 7     10/25/98 9:10p Markd
// made bats be more like rats but with wings
// 
// 6     10/19/98 12:04a Jimdose
// made all code use fast checks for inheritance (no text lookups when
// possible)
// isSubclassOf no longer requires ::_classinfo()
// 
// 5     10/13/98 11:13p Markd
// Redid mouse, allowed mutation
// 
// 4     9/22/98 5:19p Markd
// Put in new consolidated gib function
// 
// 3     9/22/98 3:21p Markd
// put in parentmode lockout for blood and gibs
// 
// 2     8/10/98 6:51p Aldie
// First version of rat
//
// DESCRIPTION:
// Animals behavior

#include "actor.h"
#include "gibs.h"

class EXPORT_FROM_DLL Rat : public Actor
	{

	public:
		CLASS_PROTOTYPE( Rat );

      void                       Killed( Event *ev );
      void                       Touched( Event *ev );
      void                       Mutate( Event *ev );
	};

CLASS_DECLARATION( Actor, Rat, "animals_rat" );

ResponseDef Rat::Responses[] =
	{
      { &EV_Killed,      ( Response )Rat::Killed },
      { &EV_Touch,       ( Response )Rat::Touched },
      { &EV_Mutate,       ( Response )Rat::Mutate },
      { NULL, NULL }
   };


void Rat::Touched
   (
   Event *ev
   )

   {
   Event *event;
	Entity *other;

	other = ev->GetEntity( 1 );

	assert( other != this );

   if ( other->isSubclassOf( Sentient ) )
      {
      event = new Event( EV_Actor_Attack );
      event->AddEntity( other );
      ProcessEvent( event );
      }
   }

void Rat::Mutate
   (
   Event *ev
   )

   {
   Vector tempmins;
   Vector tempmaxs;
   Event *event;

   assert( !( flags & FL_MUTATED ) );

   flags |= FL_MUTATED;

   edict->s.scale = 3;
   health *= edict->s.scale;
   max_health *= edict->s.scale;
   tempmins = mins * edict->s.scale;
   tempmaxs = maxs * edict->s.scale;
   setSize( tempmins, tempmaxs );

   unlink();
   KillBox( this );
   link();

   event = new Event( EV_Actor_MeleeDamage );
   event->AddFloat( melee_damage * edict->s.scale );
   ProcessEvent( event );
   event = new Event( EV_Actor_MeleeRange );
   event->AddFloat( melee_range * edict->s.scale );
   ProcessEvent( event );
   }

void Rat::Killed
   (
   Event *ev
   )

   {
   takedamage = DAMAGE_NO;
   setSolidType( SOLID_NOT );
   hideModel();

   if ( sv_gibs->value && !parentmode->value )
      {
      int numgibs;
      float gibsize;

      gibsize = size.length() / 175;
      numgibs = gibsize * 6;
      if ( numgibs > 4 )
         numgibs = 4;
      CreateGibs( this, health, gibsize, numgibs );
      }

   PostEvent( EV_Remove, 0 );
   }

class EXPORT_FROM_DLL Bat : public Actor
	{

	public:
		CLASS_PROTOTYPE( Bat );

      void                       Killed( Event *ev );
      void                       Touched( Event *ev );
      void                       Mutate( Event *ev );
	};

CLASS_DECLARATION( Actor, Bat, "animals_bat" );

ResponseDef Bat::Responses[] =
	{
      { &EV_Killed,      ( Response )Bat::Killed },
      { &EV_Touch,       ( Response )Bat::Touched },
      { &EV_Mutate,       ( Response )Bat::Mutate },
      { NULL, NULL }
   };


void Bat::Touched
   (
   Event *ev
   )

   {
   Event *event;
	Entity *other;

	other = ev->GetEntity( 1 );

	assert( other != this );

   if ( other->isSubclassOf( Sentient ) )
      {
      event = new Event( EV_Actor_Attack );
      event->AddEntity( other );
      ProcessEvent( event );
      }
   }

void Bat::Mutate
   (
   Event *ev
   )

   {
   Vector tempmins;
   Vector tempmaxs;
   Event *event;

   assert( !( flags & FL_MUTATED ) );

   flags |= FL_MUTATED;

   edict->s.scale = 5;
   health *= edict->s.scale;
   max_health *= edict->s.scale;
   tempmins = mins * edict->s.scale;
   tempmaxs = maxs * edict->s.scale;
   setSize( tempmins, tempmaxs );

   unlink();
   KillBox( this );
   link();

   event = new Event( EV_Actor_MeleeDamage );
   event->AddFloat( melee_damage * edict->s.scale );
   ProcessEvent( event );
   event = new Event( EV_Actor_MeleeRange );
   event->AddFloat( melee_range * edict->s.scale );
   ProcessEvent( event );
   }

void Bat::Killed
   (
   Event *ev
   )

   {
   takedamage = DAMAGE_NO;
   setSolidType( SOLID_NOT );
   hideModel();

   if ( sv_gibs->value && !parentmode->value )
      {
      int numgibs;
      float gibsize;

      gibsize = size.length() / 175;
      numgibs = gibsize * 6;
      if ( numgibs > 4 )
         numgibs = 4;
      CreateGibs( this, health, gibsize, numgibs );
      }

   PostEvent( EV_Remove, 0 );
   }


class EXPORT_FROM_DLL Fish : public Actor
	{

	public:
		CLASS_PROTOTYPE( Fish );

      void                       Killed( Event *ev );
	};

CLASS_DECLARATION( Actor, Fish, "animals_fish" );

ResponseDef Fish::Responses[] =
	{
      { &EV_Killed,      ( Response )Fish::Killed },
      { NULL, NULL }
   };


void Fish::Killed
   (
   Event *ev
   )

   {
   takedamage = DAMAGE_NO;
   setSolidType( SOLID_NOT );
   hideModel();

   if ( sv_gibs->value && !parentmode->value )
      {
      int numgibs;
      float gibsize;

      gibsize = size.length() / 175;
      numgibs = gibsize * 6;
      if ( numgibs > 4 )
         numgibs = 4;
      CreateGibs( this, health, gibsize, numgibs );
      }

   PostEvent( EV_Remove, 0 );
   }
