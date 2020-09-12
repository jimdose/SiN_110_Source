//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/deadbody.cpp                     $
// $Revision:: 13                                                             $
//   $Author:: Jimdose                                                        $
//     $Date:: 11/19/98 9:28p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/deadbody.cpp                          $
// 
// 13    11/19/98 9:28p Jimdose
// made deadbodies copy the gravaxis
// 
// 12    11/11/98 11:11p Aldie
// Make deadbodies do blood and gib properly
// 
// 11    11/10/98 7:20p Aldie
// Fix for deadbodies not displaying death properly
// 
// 10    10/17/98 9:40p Markd
// dead body queue won't initialize unless in deathmatch or coop
// 
// 9     10/10/98 1:26a Jimdose
// InitializeBodyQueue is disabled while loading savegames
// 
// 8     9/22/98 5:19p Markd
// Put in new consolidated gib function
// 
// 7     9/22/98 3:21p Markd
// put in parentmode lockout for blood and gibs
// 
// 6     9/19/98 6:09p Markd
// changed linkentity to link() call
// 
// 5     8/29/98 9:40p Jimdose
// Moved bodyque to deadbody
// 
// 4     7/29/98 2:31p Aldie
// Changed health to a float
// 
// 3     7/23/98 6:17p Aldie
// Updated damage system and fixed some damage related bugs.  Also put tracers
// back to the way they were, and added gib event to funcscriptmodels
// 
// 2     7/13/98 4:59p Aldie
// Added dead player bodies with gibbing
//
// DESCRIPTION:
// Dead body

#include "deadbody.h"
#include "gibs.h"

CLASS_DECLARATION( Sentient, Deadbody, "deadbody" );

ResponseDef Deadbody::Responses[] =
	{
      { &EV_Gib,      ( Response )Deadbody::GibEvent },
      { NULL, NULL }
   };

void Deadbody::GibEvent
   (
   Event *ev
   )

   {
   takedamage = DAMAGE_NO;

   if ( sv_gibs->value && !parentmode->value ) 
      {
      setSolidType( SOLID_NOT );
	   hideModel();

      CreateGibs( this, health, 1.0f, 3 );
      } 
   }

void CopyToBodyQueue
   (
   edict_t *ent
   )
   
   {
	edict_t *body;

	// grab a body from the queue and cycle to the next one
	body = &g_edicts[ ( int )maxclients->value + level.body_queue + 1 ];
	level.body_queue = ( level.body_queue + 1 ) % BODY_QUEUE_SIZE;

	gi.unlinkentity( ent );
	gi.unlinkentity( body );

   body->s                    = ent->s;
	body->s.number             = body - g_edicts;
	body->svflags              = ent->svflags;	
   body->solid                = ent->solid;
	body->clipmask             = ent->clipmask;
	body->owner                = ent->owner;
	body->entity->movetype     = ent->entity->movetype;
	body->entity->takedamage   = DAMAGE_YES;
   body->entity->deadflag     = DEAD_DEAD;
   body->s.renderfx           &= ~RF_DONTDRAW;
   body->entity->origin       = ent->entity->worldorigin;
   body->entity->setSize(ent->mins,ent->maxs);
   body->entity->link();
   body->entity->SetGravityAxis( ent->entity->gravaxis );
   }

void InitializeBodyQueue
	(
	void
	)

   {
	int	   	i;
	Deadbody    *body;

   if ( ( !LoadingSavegame ) && ( deathmatch->value || coop->value ) )
      {
	   level.body_queue = 0;
	   for ( i=0; i<BODY_QUEUE_SIZE ; i++ )
	      {
		   body = new Deadbody;
         body->edict->owner = NULL;
         body->edict->s.skinnum = -1;
         body->flags |= (FL_DIE_GIBS|FL_BLOOD);
	      }
      }
   }
