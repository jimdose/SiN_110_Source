//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/trigger.cpp                      $
// $Revision:: 126                                                            $
//   $Author:: Jimdose                                                        $
//     $Date:: 12/09/98 8:06p                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/trigger.cpp                           $
// 
// 126   12/09/98 8:06p Jimdose
// added triggerbox
// 
// 125   11/18/98 3:37a Jimdose
// added hack to get rid of tirggers marked with "secret" message
// 
// 124   11/17/98 2:51a Markd
// put in special case for oilrig trigger_once we don't want
// 
// 123   11/16/98 4:37a Markd
// put in better ToggleSound code
// 
// 122   11/15/98 3:50a Jimdose
// changed TriggerStuff so that if the activator is the world, it only runs the
// thread if the command came from script.  Grrrr...
// 
// 121   11/13/98 6:02p Jimdose
// TriggerStuff was only calling the thread if other was Sentient.  Changed it
// so that it calls it for all entities except when the world touches
// something.
// 
// 120   11/12/98 9:01p Markd
// pre-cached all "NOISE"'s
// 
// 119   11/07/98 10:15p Markd
// put in forcemusic support
// 
// 118   10/27/98 6:20a Aldie
// Bulletproof cameras
// 
// 117   10/26/98 3:51a Aldie
// Made trigger_hurt ignore armor and skill
// 
// 116   10/25/98 9:11p Markd
// put in null other protection for activate targets
// 
// 115   10/25/98 5:49p Markd
// Fixed random speakers, multi-triggering
// 
// 114   10/24/98 6:05p Jimdose
// added changethread to TriggerChangeLevel
// made waitForPlayer work in change level threads
// 
// 113   10/24/98 2:17p Markd
// Put in success music when hit trigger_exit
// 
// 112   10/24/98 12:42a Markd
// changed origins to worldorigins where appropriate
// 
// 111   10/22/98 5:04p Jimdose
// TriggerStuff now checks trigger_time at the begining of the function
// 
// 110   10/19/98 11:52p Aldie
// Force set the touchfield to SOLID_TRIGGER
// 
// 109   10/19/98 12:07a Jimdose
// made all code use fast checks for inheritance (no text lookups when
// possible)
// isSubclassOf no longer requires ::_classinfo()
// 
// 108   10/17/98 8:13p Jimdose
// Changed Damage to DamgeEvent in DamageThreshold
// Changed ownernum to EntityPtr owner in TouchField
// 
// 107   10/16/98 7:19p Markd
// made trigger_changelevel default to LevelComplete as its default thread name
// 
// 106   10/15/98 10:08p Markd
// Made all sounds synched by default
// 
// 105   10/15/98 3:37p Markd
// Moved STartThread code after triggers again, made sure trigger_changelevel
// executes script before changing levels
// 
// 104   10/14/98 7:53p Markd
// Added trigger_exit
// 
// 103   10/14/98 12:33p Markd
// Made TriggerOnce be able to turn off the touch ability
// 
// 102   10/13/98 11:13p Markd
// Put in trigger_mutate
// 
// 101   10/13/98 9:44p Jimdose
// TriggerChangeLevel no longer errors out when the map hasn't been set and
// loading savegames
// 
// 100   10/12/98 12:20p Markd
// Replaced StartThreads with ExecuteThreads
// 
// 99    10/10/98 1:29a Jimdose
// TriggerSecret no longer increments the secret count during savegames
// 
// 98    10/08/98 7:40p Jimdose
// changed noexit to a dmflag
// 
// 97    10/05/98 6:42p Markd
// Made Trigger Speakers get sent over at least once
// 
// 96    10/01/98 11:47a Markd
// Added Toggle flag to trigger_speakers
// 
// 95    9/30/98 4:55p Markd
// bullet-proofed camera choosing code so that non-camera would be properly
// detected
// 
// 94    9/30/98 3:42p Markd
// put in bulletproofing for start thread functions
// 
// 93    9/29/98 5:59p Markd
// Added dialog_needed stuff for keys on triggers
// 
// 92    9/21/98 4:21p Markd
// Put in archive functions and rewrote all archive routines
// 
// 91    9/20/98 7:11p Aldie
// Added flags to particles
// 
// 90    9/20/98 3:13p Markd
// made channel voice the default for trigger_speakers
// 
// 89    9/17/98 5:52p Jimdose
// Made total_secrets and found_secrets available to script
// Made trigger_secret's thread default to specific script.
// 
// 88    9/15/98 7:01p Markd
// Added setdamage ability to trigger_hurt's
// 
// 87    9/15/98 6:45p Aldie
// Removed some sound references
// 
// 86    9/14/98 6:16p Markd
// Added documentation to trigger_once
// 
// 85    9/14/98 3:10p Markd
// fixed trigger_speaker toggling
// 
// 84    9/11/98 5:45p Aldie
// Updated some flags for beam
// 
// 83    9/09/98 3:56p Aldie
// New lightning effect
// 
// 82    8/30/98 7:01p Markd
// Fixed touchable triggers for trigger_particle and trigger_randomparticle
// 
// 81    8/29/98 9:46p Jimdose
// Changed BeginIntermission to G_BeginIntermission
// 
// 80    8/29/98 5:27p Markd
// added specialfx, replaced misc with specialfx where appropriate
// 
// 79    8/27/98 6:47p Markd
// Added NOSOUND capability to trigger_particles
// 
// 78    8/24/98 4:55p Markd
// Added G_CalculateImpulse to TriggerPush
// 
// 77    8/24/98 11:32a Markd
// Added Start method to threads, repladed all ProcessEvent(
// EV_ScriptThread_execute) with thread->Start( -1 )
// 
// 76    8/19/98 2:28p Aldie
// Added trigger_pushany which is basically a trigger_push with angles support
// 
// 75    8/18/98 11:53p Jimdose
// Changed TriggerStuff so that it only accepts world triggers on EV_Activate
// 
// 74    8/18/98 11:08p Markd
// Added new Alias System
// 
// 73    8/17/98 6:19p Markd
// Added trigger_camerause
// 
// 72    8/15/98 10:12p Jimdose
// Made trigger_use solid only when visible
// 
// 71    8/15/98 5:36p Jimdose
// Trigger thread was starting the thread in TriggerStuff and in Trigger
// Effect, effectively, calling it twice
// 
// 70    8/14/98 8:18p Markd
// Fixed silly str thing to get rid of weird messages.
// 
// 69    8/10/98 7:26p Markd
// fixed a thread issue with triggers being triggered by world
// 
// 68    8/05/98 2:52p Markd
// Added thread support to triggers
// 
// 67    7/23/98 6:17p Aldie
// Updated damage system and fixed some damage related bugs.  Also put tracers
// back to the way they were, and added gib event to funcscriptmodels
// 
// 66    7/21/98 4:23p Aldie
// Make icons work for locks
// 
// 65    7/21/98 1:10p Aldie
// Added meansofdeath to obituaries
// 
// 64    7/18/98 3:56p Markd
// Added SetKey command
// 
// 63    7/18/98 1:57p Aldie
// Changed functionality of trigger_push.
// 
// 62    7/16/98 5:45p Markd
// Added particlestyle to Trigger_randomparticles
// 
// 61    7/15/98 9:58p Markd
// changed syntax of TempDLight
// 
// 60    7/13/98 5:56p Markd
// Added TriggerDamageTargetsFixed and TriggerThread
// 
// 59    7/10/98 4:17p Markd
// Made trigger_damagetargets not walkthroughable
// 
// 58    7/10/98 4:10p Markd
// made damage_threshold have accumulative flag
// 
// 57    7/09/98 12:07a Jimdose
// killtargeting posts a remove instead of processing it.
// 
// 56    6/27/98 2:16p Aldie
// Updated to new centerprintf method
// 
// 55    6/25/98 8:47p Markd
// Added keyed items for Triggers, Rewrote Item class, rewrote every pickup
// method
// 
// 54    6/18/98 8:48p Jimdose
// Added better event error handling
// Added source info to events
// 
// 53    6/17/98 7:24p Markd
// Updated documentation on Trigger_speakers
// 
// 52    6/10/98 2:38p Aldie
// Updated the trigger_push.
// 
// 51    6/10/98 2:10p Aldie
// Updated damage function.
// 
// 50    6/09/98 6:42p Markd
// made ambients default to ATTN_IDLE instead of ATTN_STATIC
// 
// 49    6/08/98 2:36p Markd
// re-did some trigger_speaker stuff to support attenuation on ambients
// 
// 48    5/25/98 5:40p Markd
// Added TriggerParticles and TriggerRandomParticles
// 
// 47    5/24/98 8:46p Jimdose
// Made a lot of functions more str-friendly.
// Got rid of a lot of char * based strings
// Cleaned up get spawn arg functions and sound functions
// sound functions now use consistant syntax
// 
// 46    5/24/98 5:25p Jimdose
// Changed char *'s to const char *'s
// 
// 45    5/22/98 9:39p Jimdose
// Changed check for "Monster" to "Actor"
// 
// 44    5/20/98 1:51p Markd
// Forgot to get rid of showmodel for TriggerDamageTargets-SOLID
// 
// 43    5/20/98 1:33p Markd
// Changed Trigger_damagetargets a bit
// 
// 42    5/20/98 11:11a Markd
// removed char * dependency
// 
// 41    5/18/98 6:13p Jimdose
// Added health to trigger
// 
// 40    5/16/98 5:00p Markd
// Added Trigger_DamageTargets
// 
// 39    5/08/98 7:54p Markd
// Fixed default trigger sound
// 
// 38    5/06/98 11:01a Markd
// Added warning on play_sound_triggered
// 
// 37    5/02/98 12:01a Jimdose
// Trigger Hurt now defaults to hurt monsters
// 
// 36    5/01/98 6:23p Jimdose
// Trigger hurt no longer hurts dead people
// 
// 35    5/01/98 5:07p Jimdose
// TriggerStuff now responds to messages from world regardless of its
// spawnflags
// 
// 34    4/30/98 12:18p Markd
// capitalized some trigger_speaker stuff
// 
// 33    4/30/98 12:14p Markd
// Added SINED clarifications
// 
// 32    4/30/98 12:00p Markd
// Fixed trigger_speaker, it now spawns properly
// 
// 31    4/29/98 10:45p Markd
// Added TriggerSpeaker and TriggerRandomSpeaker and TriggerPlaySound was
// modified
// 
// 30    4/20/98 1:40p Jimdose
// Added respondto in TouchField::Setup
// 
// 29    4/18/98 2:36p Jimdose
// Removed tesselating from DamageThreshold
// Changed DamageThreshold to behave more like a Trigger (using
// EV_Trigger_Effect)
// 
// 28    4/14/98 7:29p Markd
// Increased size of tesselation for damage_threshold
// 
// 27    4/14/98 6:56p Markd
// Added thickness to tesselation
// 
// 26    4/10/98 1:24a Markd
// Made DamageThreshold behave with new FL_TESSELATE flags
// 
// 25    4/05/98 10:43p Markd
// Moved Tesselate to Entity
// 
// 24    4/05/98 6:16p Markd
// Changed TE_TESSELATE a bit
// 
// 23    4/04/98 6:10p Jimdose
// Added TriggerHurt
// Added EV_Trigger_Effect so that subclasses of Trigger can easily change the
// effect of the trigger without loses its default behaviour
// Added respondto variable that determines wether a trigger responds to
// players, monsters, or projectiles
// 
// 22    3/29/98 9:40p Jimdose
// Changed killed and pain to events
// 
// 21    3/27/98 5:38p Jimdose
// Made TriggerChangeLevel work
// 
// 20    3/24/98 4:55p Jimdose
// Changed usage of GetToken to GetString so that script variables can be used
// 
// 19    3/23/98 1:31p Jimdose
// Revamped event and command system
// 
// 18    3/11/98 2:22p Jimdose
// Added support for area portals in damage threshold.
// 
// 17    3/02/98 8:49p Jimdose
// Changed the classid parameter of CLASS_DECLARATION to a quoted string so
// that you could have a NULL classid.
// 
// 16    2/17/98 6:59p Jimdose
// no longer pass script into interpretCommand
// 
// 15    2/16/98 2:11p Jimdose
// Fixed bug in ActivateTargets where entnum was being overwritten
// 
// 14    2/06/98 5:41p Jimdose
// Fixed Sined header for trigger_multiple.
// Removed use of touch function in DamageThreshold.
// 
// 13    2/03/98 10:49a Jimdose
// Updated to work with Quake 2 engine
// Changed from think functions to events
// 
// 11    12/06/97 4:51p Markd
// Added intepretCommand for Trigger and TriggerMonsterJump
// 
// 10    11/10/97 8:36p Jimdose
// Removed getMapTitle from World, so had to change trigger_changelevel
// 
// 9     10/27/97 3:30p Jimdose
// Removed dependency on quakedef.h
// 
// 8     10/08/97 6:03p Jimdose
// Began vehicle support.
// 
// 7     10/06/97 6:31p Markd
// changed triangulate size
// 
// 6     10/06/97 4:01p Markd
// added multiple parameters to the triangulate function.  Added lightmap
// lookups at each vert.  Added subtri filter that would cull some the created
// triangles
// 
// 5     10/05/97 6:09p Markd
// Changed tesselation factor back
// 
// 4     10/05/97 5:53p Markd
// Changed tesselation factor for triangulate
// 
// 3     10/04/97 5:22p Markd
// Added Triangulate calls
// 
// 2     9/26/97 5:23p Jimdose
// Added standard Ritual headers
//
// DESCRIPTION:
// Environment based triggers.
// 

#include "g_local.h"
#include "entity.h"
#include "trigger.h"
#include "scriptmaster.h"
#include "areaportal.h"
#include "worldspawn.h"
#include "misc.h"
#include "specialfx.h"
#include "sentient.h"
#include "item.h"
#include "player.h"
#include "camera.h"
#include "actor.h"
#include "g_utils.h"

Event EV_Trigger_ActivateTargets( "activatetrigger" );
Event EV_Trigger_SetWait( "wait" );
Event EV_Trigger_SetDelay( "delay" );
Event EV_Trigger_SetCount( "cnt" );
Event EV_Trigger_SetMessage( "message" );
Event EV_Trigger_SetNoise( "noise" );
Event EV_Trigger_Effect( "triggereffect" );
Event EV_Trigger_StartThread( "triggerthread" );
Event EV_Trigger_SetKey( "key" );

#define MULTI_ACTIVATE	1
#define INVISIBLE			2

#define VISIBLE			1

#define TRIGGER_PLAYERS			4
#define TRIGGER_MONSTERS		8
#define TRIGGER_PROJECTILES	16

/*****************************************************************************/
/*SINED trigger_multiple (.5 .5 .5) ? x x NOT_PLAYERS MONSTERS PROJECTILES

Variable sized repeatable trigger.  Must be targeted at one or more entities.

If "health" is set, the trigger must be killed to activate each time.
If "delay" is set, the trigger waits some time after activating before firing.

"thread" name of thread to trigger.  This can be in a different script file as well\
by using the '::' notation.

"wait" : Seconds between triggerings. (.2 default)
"cnt" how many times it can be triggered (infinite default)

If NOT_PLAYERS is set, the trigger does not respond to players
If MONSTERS is set, the trigger will respond to monsters
If PROJECTILES is set, the trigger will respond to projectiles (rockets, grenades, etc.)

set "message" to text string

/*****************************************************************************/

CLASS_DECLARATION( Entity, Trigger, "trigger_multiple" );

ResponseDef Trigger::Responses[] =
	{
	   { &EV_Trigger_SetWait,				( Response )Trigger::EventSetWait },
	   { &EV_Trigger_SetDelay,				( Response )Trigger::EventSetDelay },
	   { &EV_Trigger_SetCount,				( Response )Trigger::EventSetCount },
	   { &EV_Trigger_SetMessage,			( Response )Trigger::EventSetMessage },
	   { &EV_Trigger_SetNoise,				( Response )Trigger::EventSetNoise },
	   { &EV_Touch,							( Response )Trigger::TriggerStuff },
	   { &EV_Killed,							( Response )Trigger::TriggerStuff },
	   { &EV_Activate,						( Response )Trigger::TriggerStuff },
	   { &EV_Trigger_ActivateTargets,	( Response )Trigger::ActivateTargets },
	   { &EV_Trigger_SetKey,				( Response )Trigger::EventSetKey },
	   { &EV_Trigger_StartThread,			( Response )Trigger::StartThread },
		{ NULL, NULL }
	};

Trigger::Trigger()
	{
	triggerActivated	= false;
	activator			= NULL;
	trigger_time		= (float)0;

	setMoveType( MOVETYPE_NONE );
	setSolidType( SOLID_TRIGGER );

	delay = G_GetFloatArg( "delay" );
	wait  = G_GetFloatArg( "wait", 0.2 );
	health = G_GetFloatArg( "health", 0 );
	max_health = health;
	if ( health )
		{
		takedamage = DAMAGE_YES;
		setSolidType( SOLID_BBOX );
		}

	trigger_time = (float)0;

	count = G_GetFloatArg( "cnt", -1 );

	SetNoise( G_GetSpawnArg( "noise", "environment/switch/switch2.wav" ) );
	SetMessage( G_GetSpawnArg( "message" ) );
	SetKillTarget( G_GetSpawnArg( "killtarget" ) );

	hideModel();

	respondto = spawnflags ^ TRIGGER_PLAYERS;

	key = G_GetStringArg( "key" );
   thread = G_GetStringArg( "thread" );

   //
   // gross HACK for non-standard secret triggers
   //
   if ( message == "secret" )
      {
      TriggerSecret *trig;

      // don't ever trigger
      trigger_time = -1;

      // clear out the message
      G_SetSpawnArg( "message", "" );

      // spawn the replacement trigger
      trig = new TriggerSecret;

      // delete ourself on the way out.
      PostEvent( EV_Remove, 0 );
      }
	}

Trigger::~Trigger()
	{
	}

void Trigger::StartThread
	(
	Event *ev
	)

	{
   if ( thread.length() )
      {
      if ( !ExecuteThread( thread ) )
         {
         warning( "StartThread", "Null game script" );
         }
      }
   }

void Trigger::TriggerStuff
	(
	Event *ev
	)

	{
	Entity *other;
	Event *event;
	qboolean respond;

   // Don't bother with testing anything if we can't trigger yet
   if ( ( level.time < trigger_time ) || ( trigger_time == -1 ) )
		{
		return;
		}
	
	health = max_health;
	if ( health && ( ( int )*ev != ( int )EV_Killed ) && ( ( int )*ev != ( int )EV_Activate ) )
		{
		// if health is set, we only respond to killed and activate messages
		return;
		}

	other = ev->GetEntity( 1 );

	assert( other != this );

	respond = ( ( ( respondto & TRIGGER_PLAYERS ) && other->isClient() ) ||
		( ( respondto & TRIGGER_MONSTERS ) && other->isSubclassOf( Actor ) ) ||
		( ( respondto & TRIGGER_PROJECTILES ) && other->isSubclassOf( Projectile ) ) );

	// Always respond to activate messages from the world since they're probably from 
	// the "trigger" command
	if ( !respond && !( ( other == world ) && ( ( int )*ev == ( int )EV_Activate ) ) )
		{
		return;
		}

   if ( key.length() )
      {
      if ( !other->isSubclassOf( Sentient ) || !( ( (Sentient *)other )->HasItem( key.c_str() ) ) ) 
         {
         Item        *item;
         ClassDef		*cls;  
         str         dialog;

         cls = getClass( key.c_str() );
		   if ( !cls )
			   {
			   gi.dprintf( "No item named '%s'\n", key.c_str() );
			   return;
			   }
		   item = ( Item * )cls->newInstance();
         item->CancelEventsOfType( EV_Item_DropToFloor );
	      item->CancelEventsOfType( EV_Remove );
         item->ProcessPendingEvents();
         dialog = item->GetDialogNeeded();
         if ( dialog.length() > 1 )
            {
            if ( !ExecuteThread( dialog ) )
               {
               warning( "TriggerStuff", "Null game script" );
               }
            }
         else
            {
            gi.centerprintf ( other->edict, "jcx yv 20 string \"You need this item:\" jcx yv -20 icon %d", item->GetIconIndex() );
            }
         delete item;
         return;
         }
      }

	trigger_time = level.time + wait;

	event = new Event( EV_Trigger_Effect );
	event->AddEntity( other );
	PostEvent( event, delay );

	event = new Event( EV_Trigger_ActivateTargets );
	event->AddEntity( other );
	PostEvent( event, delay );

   if ( thread.length() )
      {
      // don't trigger the thread if we were triggered by the world touching us
      if ( ( other != world ) || ( ev->GetSource() != EV_FROM_CODE ) )
         {
	      event = new Event( EV_Trigger_StartThread );
   	   PostEvent( event, delay );
         }
      }

	if ( count > -1 )
		{
		count--;
		if ( count < 1 )
			{
			//
			// Don't allow it to trigger anymore
			//
			trigger_time = -1;

			//
			// Make sure we wait until we're done triggering things before removing
			//
			PostEvent( EV_Remove, delay + 0.1 );
			}
		}
	}

//
//==============================
// ActivateTargets
//
// "other" should be set to the entity that initiated the firing.
//
// Centerprints any message to the activator.
//
// Removes all entities with a targetname that match killtarget,
// so some events can remove other triggers.
//
// Search in targetname of all entities that match target 
// and send EVENT_ACTIVATE to there event handler
//==============================
//
void Trigger::ActivateTargets
	(
	Event *ev
	)

	{
	Entity	*other;
	Entity	*ent;
	Event		*event;
	const char *name;
	int		num;

	other = ev->GetEntity( 1 );

   if ( !other )
      other = world;

	if ( triggerActivated )
		{
		//
		// Entity triggered itself.  Prevent an infinite loop
		//
		ev->Error( "Entity targeting itself--Targetname '%s'", TargetName() );
		return;
		}

	triggerActivated = true;
	activator = other;
	
//
// print the message
//
	if ( message.length() && other && other->isClient() )
		{
		gi.centerprintf( other->edict, "jcx jcy string \"%s\"", message.c_str() );
		if ( Noise().length() )
			{
			other->sound( noise, 1, CHAN_VOICE, ATTN_NORM );
			}
		}
		
//
// kill the killtargets
//
	name = KillTarget();
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
			ent->PostEvent( EV_Remove, 0 );
			} 
		while ( 1 );
		}
		
//
// fire targets
//
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
		
			event = new Event( EV_Activate );
			event->AddEntity( other );
			ent->ProcessEvent( event );
			}
		while ( 1 );
		}

	triggerActivated = false;
	}
	
void Trigger::EventSetWait
	(
	Event *ev
	)

	{
	wait = ev->GetFloat( 1 );
   }

void Trigger::EventSetDelay
	(
	Event *ev
	)

	{
	delay = ev->GetFloat( 1 );
	}

void Trigger::EventSetKey
	(
	Event *ev
	)

	{
	key = ev->GetString( 1 );
	}

void Trigger::EventSetCount
	(
	Event *ev
	)

	{
	count = ev->GetInteger( 1 );
   }

void Trigger::EventSetMessage
	(
	Event *ev
	)

	{
  	SetMessage( ev->GetString( 1 ) );
	}

void Trigger::SetMessage
	( 
	const char *text
	)

	{
   if ( text )
      message = str( text );
	}

str &Trigger::Message
	(
	void
	)

	{
   return message;
	}

void Trigger::EventSetNoise
	(
	Event *ev
	)
	
	{
   SetNoise( ev->GetString( 1 ) );
	}

void Trigger::SetNoise
	( 
	const char *text
	)

	{
   if ( text )
      {
      noise = str( text );
      //
      // cache in the sound
      //
      gi.soundindex( text );
      }
	}

str &Trigger::Noise
	(
	void
	)

	{
	return noise;
	}

CLASS_DECLARATION( Trigger, TouchField, NULL );

ResponseDef TouchField::Responses[] =
	{
	   { &EV_Trigger_Effect,				( Response )TouchField::SendEvent },
		{ NULL, NULL }
	};

void TouchField::Setup
	(
	Entity *ownerentity,
	Event touchevent,
	Vector min,
	Vector max,
	int respondto
	)

	{
	assert( ownerentity );
	if ( !ownerentity )
		{
		error( "Setup", "Null owner" );
		}

	owner = ownerentity;
	ontouch	= touchevent;
	setSize( min, max );

   setSolidType( SOLID_TRIGGER );

	this->respondto = respondto;
	}

void TouchField::SendEvent
	(
	Event *ev
	)

	{
	Event *event;

   // Check if our owner is still around
   if ( owner )
      {
	   event = new Event( ontouch );
	   event->AddEntity( ev->GetEntity( 1 ) );
	   owner->PostEvent( event, delay );
      }
   else
      {
      // Our owner is gone!  The bastard didn't delete us!
      // Guess we're no longer needed, so remove ourself.
      PostEvent( EV_Remove, 0 );
      }
	}

/*****************************************************************************/
/*SINED trigger_once (.5 .5 .5) ? notouch x NOT_PLAYERS MONSTERS PROJECTILES

Variable sized trigger. Triggers once, then removes itself.  
You must set the key "target" to the name of another object in the 
level that has a matching 

If "health" is set, the trigger must be killed to activate it.
If "delay" is set, the trigger waits some time after activating before firing.

"targetname".  If "health" is set, the trigger must be killed to activate.

"thread" name of thread to trigger.  This can be in a different script file as well\
by using the '::' notation.

if "killtarget" is set, any objects that have a matching "target" will be
removed when the trigger is fired.

if "angle" is set, the trigger will only fire when someone is facing the 
direction of the angle.  Use "360" for an angle of 0.

"key" The item needed to activate this. (default nothing)

If NOT_PLAYERS is set, the trigger does not respond to players
If MONSTERS is set, the trigger will respond to monsters
If PROJECTILES is set, the trigger will respond to projectiles (rockets, grenades, etc.)

set "message" to text string

/*****************************************************************************/

CLASS_DECLARATION( Trigger, TriggerOnce, "trigger_once" );

ResponseDef TriggerOnce::Responses[] =
	{
		{ NULL, NULL }
	};

TriggerOnce::TriggerOnce()
	{
   //
   // gross HACK for oilrig.bsp
   //
   if ( message == "Foreman jumps over the edge of the rig" )
      {
      PostEvent( EV_Remove, 0 );
      }

	//
	// no matter what, we only trigger once
	//
	count = 1;
	respondto = spawnflags ^ TRIGGER_PLAYERS;

   // 
   // if it's not supposed to be touchable, clear the trigger
   //
   if ( spawnflags & 1 )
	   setSolidType( SOLID_NOT );
	}

/*****************************************************************************/
/*SINED trigger_relay (.5 .5 .5) (-8 -8 -8) (8 8 8) x x NOT_PLAYERS MONSTERS PROJECTILES

This fixed size trigger cannot be touched, it can only be fired by other events.
It can contain killtargets, targets, delays, and messages.

If NOT_PLAYERS is set, the trigger does not respond to events triggered by players
If MONSTERS is set, the trigger will respond to events triggered by monsters
If PROJECTILES is set, the trigger will respond to events triggered by projectiles (rockets, grenades, etc.)

/*****************************************************************************/

CLASS_DECLARATION( Trigger, TriggerRelay, "trigger_relay" );

ResponseDef TriggerRelay::Responses[] =
	{
		{ &EV_Touch, NULL },
		{ NULL, NULL }
	};

TriggerRelay::TriggerRelay()
	{
	setSolidType( SOLID_NOT );
	}

/*****************************************************************************/
/*SINED trigger_damagethreshold (0 .5 .8) ? x INVISIBLE NOT_PLAYERS MONSTERS ACCUMULATIVE

Triggers only when a threshold of damage is exceeded.
When used in conjunction with func_breakawaywall, allows
walls that may be destroyed with a rocket blast.  Will also trigger
any targeted func_areaportals when not invisible.

INVISIBLE tells the trigger to not be visible.

"health" specifies how much damage must occur before trigger fires.
Default is 60.

"cnt" specifies how many times the trigger can fire before it will remove itself.
-1 sepecies infinite firing.  Default is 1.

"key" The item needed to activate this. (default nothing)

If NOT_PLAYERS is set, the trigger does not respond to damage caused by players
If MONSTERS is set, the trigger will respond to damage caused by monsters

/*****************************************************************************/
#define DAMAGETHRESHOLD_ACCUMULATIVE   ( 1 << 4 )

CLASS_DECLARATION( Trigger, DamageThreshold, "trigger_damagethreshold" );

// Only used internally
static Event EV_DamageThreshold_Setup( "setup" );

ResponseDef DamageThreshold::Responses[] =
	{
	   { &EV_Damage,						( Response )DamageThreshold::DamageEvent },
	   { &EV_DamageThreshold_Setup,	( Response )DamageThreshold::Setup },
		{ &EV_Touch,						NULL },
		{ NULL, NULL }
	};

void DamageThreshold::DamageEvent
	(
	Event *ev
	)

	{
	Event			*event;
	Entity		*inflictor;
	Entity		*attacker;
	int			damage;

	if ( takedamage == DAMAGE_NO )
		{
		return;
		}

	damage		= ev->GetInteger( 1 );
	inflictor	= ev->GetEntity( 2 );
	attacker		= ev->GetEntity( 3 );

   if ( spawnflags & DAMAGETHRESHOLD_ACCUMULATIVE )
      {
      health -= damage;
   	damage_taken += damage;
      if ( health > 0 )
         return;
      }
   else
      {
	   if ( damage < health )
		   {
		   return;
		   }
   	damage_taken = damage;
      }

	event = new Event( EV_Activate );
	event->AddEntity( attacker );
	ProcessEvent( event );
	}

void DamageThreshold::Setup
	(
	Event *ev
	)

	{
	SetAreaPortals( Target(), false );
	}

DamageThreshold::DamageThreshold()
	{
	//
	// Default behavior is one use
	//
	count = G_GetIntArg( "cnt", 1 );

	damage_taken = 0;

	setSolidType( SOLID_BSP );
	setMoveType( MOVETYPE_PUSH );

	if ( !( spawnflags & INVISIBLE ) )
		{
		showModel();
		PostEvent( EV_DamageThreshold_Setup, 0 );
		}

	health = G_GetFloatArg( "health", 60 );
	max_health = health;
	takedamage = DAMAGE_YES;

	respondto = ( spawnflags ^ TRIGGER_PLAYERS ) & ~TRIGGER_PROJECTILES;
	}

/*****************************************************************************/
/*SINED trigger_secret (.5 .5 .5) ? notouch x NOT_PLAYERS MONSTERS PROJECTILES
Secret counter trigger.  Automatically sets and increments script variables \
level.total_secrets and level.found_secrets.

set "message" to text string

"key" The item needed to activate this. (default nothing)

"thread" name of thread to trigger.  This can be in a different script file as well \
by using the '::' notation.  (defaults to "global/universal_script.scr::secret")

If NOT_PLAYERS is set, the trigger does not respond to players
If MONSTERS is set, the trigger will respond to monsters
If PROJECTILES is set, the trigger will respond to projectiles (rockets, grenades, etc.)

/*****************************************************************************/

CLASS_DECLARATION( TriggerOnce, TriggerSecret, "trigger_secret" );

ResponseDef TriggerSecret::Responses[] =
	{
		{ &EV_Trigger_Effect,		( Response )TriggerSecret::FoundSecret },
		{ NULL, NULL }
	};

TriggerSecret::TriggerSecret()
	{
   if ( !LoadingSavegame )
      {
	   level.total_secrets++;
      levelVars.SetVariable( "total_secrets", level.total_secrets );
      }
	respondto = spawnflags ^ TRIGGER_PLAYERS;

   // set the thread to trigger when secrets are found
   thread = G_GetStringArg( "thread", "global/universal_script.scr::secret" );
	}

void TriggerSecret::FoundSecret
	(
	Event *ev
	)

	{
	//
	// anything that causes the trigger to fire increments the number
   // of secrets found.  This way, if the level designer triggers the
   // secret from the script, the player still gets credit for finding
   // it.  This is to prevent a secret from becoming undiscoverable.
	//
	level.found_secrets++;
   levelVars.SetVariable( "found_secrets", level.found_secrets );
   }

/*****************************************************************************/
/*SINED trigger_push (.5 .5 .5) ? x x NOT_PLAYERS NOT_MONSTERS NOT_PROJECTILES

Pushes entities as if they were caught in a heavy wind.

"speed" indicates the rate that entities are pushed (default 1000).

"angle" indicates the direction the wind is blowing (-1 is up, -2 is down)

"key" The item needed to activate this. (default nothing)

"target" if target is set, then a velocity will be calculated based on speed

If NOT_PLAYERS is set, the trigger does not push players
If NOT_MONSTERS is set, the trigger will not push monsters
If NOT_PROJECTILES is set, the trigger will not push projectiles (rockets, grenades, etc.)

/*****************************************************************************/

CLASS_DECLARATION( Trigger, TriggerPush, "trigger_push" );

ResponseDef TriggerPush::Responses[] =
	{
	   { &EV_Trigger_Effect,			( Response )TriggerPush::Push },
		{ NULL, NULL }
	};

void TriggerPush::Push
	(
	Event *ev
	)

	{
	Entity *other;

	other = ev->GetEntity( 1 );
	if ( other )
		{
      const char * targ;
	   Entity *ent;
	   int num;

      targ = Target ();
      if ( targ[ 0 ] )
         {
		   num = G_FindTarget( 0, Target() );
		   ent = G_GetEntity( num );
		   if ( num && ent )
            {
            other->velocity = G_CalculateImpulse
               (
               other->worldorigin,
               ent->worldorigin,
               speed,
               other->gravity
               );
            }
         }
      else
		   other->velocity = pushvelocity;
		}
	}

TriggerPush::TriggerPush()
	{
   speed = G_GetFloatArg( "speed", 1000 );
	pushvelocity = G_GetMovedir() * speed;
	respondto = spawnflags ^ ( TRIGGER_PLAYERS | TRIGGER_MONSTERS | TRIGGER_PROJECTILES );
	}

/*****************************************************************************/
/*SINED trigger_pushany (.5 .5 .5) ? x x NOT_PLAYERS NOT_MONSTERS NOT_PROJECTILES

Pushes entities as if they were caught in a heavy wind.

"speed" indicates the rate that entities are pushed (default 1000).
"angles" indicates the direction of the push
"key" The item needed to activate this. (default nothing)
"target" if target is set, then a velocity will be calculated based on speed

If NOT_PLAYERS is set, the trigger does not push players
If NOT_MONSTERS is set, the trigger will not push monsters
If NOT_PROJECTILES is set, the trigger will not push projectiles (rockets, grenades, etc.)

/*****************************************************************************/

CLASS_DECLARATION( Trigger, TriggerPushAny, "trigger_pushany" );

ResponseDef TriggerPushAny::Responses[] =
	{
	   { &EV_Trigger_Effect,			( Response )TriggerPushAny::Push },
		{ NULL, NULL }
	};

void TriggerPushAny::Push
	(
	Event *ev
	)

	{
	Entity *other;

	other = ev->GetEntity( 1 );
	if ( other )
		{
      const char * targ;
	   Entity *ent;
	   int num;

      targ = Target ();
      if ( targ[ 0 ] )
         {
		   num = G_FindTarget( 0, Target() );
		   ent = G_GetEntity( num );
		   if ( num && ent )
            {
            other->velocity = G_CalculateImpulse
               (
               other->worldorigin,
               ent->worldorigin,
               speed,
               other->gravity
               );
            }
         }
      else
		   other->velocity = pushvelocity;
		}
	}

TriggerPushAny::TriggerPushAny()
	{
   float mat[3][3];

   setAngles( G_GetVectorArg( "angles", Vector( 0, 0, 0 ) ) );
   AnglesToMat( angles.vec3(), mat );
   speed = G_GetFloatArg( "speed", 1000 );
	pushvelocity = Vector( mat[0][0],mat[0][1], mat[0][2] ) * speed;
	respondto = spawnflags ^ ( TRIGGER_PLAYERS | TRIGGER_MONSTERS | TRIGGER_PROJECTILES );
	}

/*****************************************************************************/
/*SINED play_sound_triggered (0.3 0.1 0.6) (-8 -8 -8) (8 8 8) AMBIENT-ON RELIABLE NOT_PLAYERS MONSTERS PROJECTILES AMBIENT-OFF x TOGGLE

DO NOT USE, USE TRIGGER_SPEAKER INSTEAD

play a sound when it is used

AMBIENT-ON specifies an ambient sound that starts on
RELIABLE should only be set for crucial voice-overs or sounds
AMBIENT-OFF specifies an ambient sound that starts off

if (AMBIENT-?) is not set, then the sound is sent over explicitly this creates more net traffic

"volume" how loud 0-4 (1 default full volume, ambients do not respond to volume)
"noise" sound to play
"channel" channel on which to play sound (0-7) (2 (voice) is default)
"attenuation" attenuation factor (0 becomes 1 for non-ambients, 2 for ambients)
   -1 - none, send to whole level
    0 - default (normal or ambient)
    1 - normal fighting sounds
    2 - idle monster sounds
    3 - ambient sounds
"key"          The item needed to activate this. (default nothing)

Normal sounds play each time the target is used.

Ambient Looped sounds have an attenuation of 2 by default, volume 1, and the use function toggles it on/off.
Multiple identical ambient looping sounds will just increase volume without any speed cost.
The attenuation factor can be over-ridden by specifying an attenuation factor.

If NOT_PLAYERS is set, the trigger does not respond to players
If MONSTERS is set, the trigger will respond to monsters
If PROJECTILES is set, the trigger will respond to projectiles (rockets, grenades, etc.)

/*****************************************************************************/

CLASS_DECLARATION( Trigger, TriggerPlaySound, "play_sound_triggered" );

Event EV_TriggerPlaySound_SetVolume( "volume" );
Event EV_TriggerPlaySound_SetAttenuation( "attenuation" );
Event EV_TriggerPlaySound_SetChannel( "channel" );

ResponseDef TriggerPlaySound::Responses[] =
	{
	   { &EV_Trigger_Effect,						( Response )TriggerPlaySound::ToggleSound },
	   { &EV_TriggerPlaySound_SetVolume,		( Response )TriggerPlaySound::SetVolume },
	   { &EV_TriggerPlaySound_SetAttenuation,	( Response )TriggerPlaySound::SetAttenuation },
	   { &EV_TriggerPlaySound_SetChannel,		( Response )TriggerPlaySound::SetChannel },
		{ &EV_Touch,                           NULL },
		{ NULL, NULL }
	};

void TriggerPlaySound::ToggleSound
	(
	Event *ev
	)

	{
	if ( !state )
		{
		// noise should already be initialized
		assert( Noise().length() );
      if ( ambient || spawnflags & 128 )
 		   state = 1;

      if (ambient)
         {
         int attn;

         attn = attenuation;
         if (attn > 3) attn = 3;
         if (attn < 0) attn = 0;
         edict->s.sound = ( gi.soundindex( Noise().c_str() ) ) + (attn<<14);
         }
      else
         {
		   sound( Noise().c_str(), volume, channel, attenuation, pitch, timeofs, fadetime );
         }
		}
	else
		{
		state = 0;
      if (ambient)
         edict->s.sound = 0;
      else
		   RandomGlobalSound( "null_sound", volume, channel | CHAN_NO_PHS_ADD, -1 );
		}
	}

void TriggerPlaySound::SetVolume
	(
	Event *ev
	)

	{
	//FIXME
	// update sound volume on client
   // this cannot be done
	volume = ev->GetFloat( 1 );
	}

void TriggerPlaySound::SetAttenuation
	(
	Event *ev
	)

	{
	attenuation = ev->GetFloat( 1 );
	}

void TriggerPlaySound::SetChannel
	(
	Event *ev
	)

	{
	channel = ev->GetInteger( 1 );
	}

TriggerPlaySound::TriggerPlaySound()
	{
   //
   // this is here so that a baseline is created for this
   //      
   edict->s.effects = EF_FORCEBASELINE;
   //
   // this is here so that it gets sent over at least once
   //
	showModel();
   ambient = false;
   pitch = 1.0f;
   timeofs = 0;
   fadetime = 0;
	volume		= G_GetFloatArg( "volume", 1.0 );
	channel		= G_GetIntArg( "channel", CHAN_VOICE );
	state			= 0;
	respondto	= spawnflags ^ TRIGGER_PLAYERS;
   if (spawnflags & 2)
      channel |= CHAN_RELIABLE;
   if (spawnflags & 33)
      {
      ambient = true;
   	attenuation = G_GetFloatArg( "attenuation", ATTN_IDLE );
      if (spawnflags & 1)
         {
         ToggleSound( NULL );
         }
      }
   else
      {
   	attenuation = G_GetFloatArg( "attenuation", ATTN_NORM );
      }
	}

/*****************************************************************************/
/*SINED trigger_speaker (0.3 0.1 0.6) (-8 -8 -8) (8 8 8) AMBIENT-ON RELIABLE NOT_PLAYERS MONSTERS PROJECTILES AMBIENT-OFF x TOGGLE

play a sound when it is used

AMBIENT-ON specifies an ambient sound that starts on
RELIABLE should only be set for crucial voice-overs or sounds
AMBIENT-OFF specifies an ambient sound that starts off

if (AMBIENT-?) is not set, then the sound is sent over explicitly this creates more net traffic

"volume" how loud 0-4 (1 default full volume, ambients do not respond to volume)
"noise" sound to play
"channel" channel on which to play sound (0 auto, 1 weapon, 2 voice, 3 item, 4 body, 8 don't use PHS) (voice is default)
"pitch" the pitch of the sample ( default 1, no pitch-shift )
"fadetime" fade the sound in over a time period in seconds ( default 0, no fade )
"timeofs" start time offset in milli-seconds into this sound ( default 0, no timeofs )
"attenuation" attenuation factor (0 becomes 1 for non-ambients, 2 for ambients)
   -1 - none, send to whole level
    0 - default (normal or ambient)
    1 - normal fighting sounds
    2 - idle monster sounds
    3 - ambient sounds
"key"          The item needed to activate this. (default nothing)
"thread" name of thread to trigger.  This can be in a different script file as well\
by using the '::' notation.

Normal sounds play each time the target is used.

Ambient Looped sounds have an attenuation of 2 by default, volume 1, and the use function toggles it on/off.
Multiple identical ambient looping sounds will just increase volume without any speed cost.
The attenuation factor can be over-ridden by specifying an attenuation factor.

If NOT_PLAYERS is set, the trigger does not respond to players
If MONSTERS is set, the trigger will respond to monsters
If PROJECTILES is set, the trigger will respond to projectiles (rockets, grenades, etc.)

/*****************************************************************************/
CLASS_DECLARATION( TriggerPlaySound, TriggerSpeaker, "trigger_speaker" );

ResponseDef TriggerSpeaker::Responses[] =
	{
		{ &EV_Touch,	NULL },
		{ NULL, NULL }
	};

TriggerSpeaker::TriggerSpeaker()
	{
   if (attenuation == -1)
      attenuation = 0;
	pitch    	= G_GetFloatArg( "pitch", 1.0 );
	fadetime    = G_GetFloatArg( "fadetime", 0 );
   timeofs     = G_GetFloatArg( "timeofs", 0 );
	}

/*****************************************************************************/
/*SINED trigger_randomspeaker (0.3 0.1 0.6) (-8 -8 -8) (8 8 8) x RELIABLE NOT_PLAYERS MONSTERS PROJECTILES x x

play a sound at random times

RELIABLE should only be set for crucial voice-overs or sounds

"mindelay" minimum delay between sound triggers (default 3)
"maxdelay" maximum delay between sound triggers (default 10)
"volume" how loud 0-4 (1 default full volume)
"noise" sound to play
"channel" channel on which to play sound (0 auto, 1 weapon, 2 voice, 3 item, 4 body, 8 don't use PHS) (voice is default)
"pitch" the pitch of the sample ( default 1, no pitch-shift )
"fadetime" fade the sound in over a time period in seconds ( default 0, no fade )
"timeofs" start time offset in milli-seconds into this sound ( default 0, no timeofs )
"attenuation" attenuation factor
   -1 - none, send to whole level
    0 - default (normal)
    1 - normal fighting sounds
    2 - idle monster sounds
    3 - ambient sounds
"key"          The item needed to activate this. (default nothing)

Normal sounds play each time the target is used.

If NOT_PLAYERS is set, the trigger does not respond to players
If MONSTERS is set, the trigger will respond to monsters
If PROJECTILES is set, the trigger will respond to projectiles (rockets, grenades, etc.)

/*****************************************************************************/

CLASS_DECLARATION( TriggerSpeaker, RandomSpeaker, "trigger_randomspeaker" );

Event EV_TriggerRandomSpeaker_TriggerSound( "triggersound" );

ResponseDef RandomSpeaker::Responses[] =
	{
	   { &EV_Trigger_Effect,						( Response )RandomSpeaker::TriggerSound },
		{ &EV_Touch,	NULL },
		{ NULL, NULL }
	};

void RandomSpeaker::TriggerSound
	(
	Event *ev
	)

	{
   ScheduleSound();
   TriggerPlaySound::ToggleSound( ev );
	}

void RandomSpeaker::ScheduleSound
	(
   void
	)

	{
	CancelEventsOfType( EV_Trigger_Effect );
   PostEvent( EV_Trigger_Effect, mindelay + G_Random( maxdelay-mindelay ) );
	}

RandomSpeaker::RandomSpeaker()
	{
	mindelay  	= G_GetFloatArg( "mindelay", 3 );
	maxdelay    = G_GetFloatArg( "maxdelay", 10 );
   ScheduleSound();
	}

/*****************************************************************************/
/*SINED trigger_changelevel (0.5 0.5 0.5) ? NO_INTERMISSION x NOT_PLAYERS MONSTERS PROJECTILES

When the player touches this, he gets sent to the map listed in the "map" variable.
Unless the NO_INTERMISSION flag is set, the view will go to the info_intermission
spot and display stats.

"spawnspot"  name of the spawn location to start at in next map.
"key"          The item needed to activate this. (default nothing)
"thread" This defaults to "LevelComplete" and should point to a thread that is called just
before the level ends.

If NOT_PLAYERS is set, the trigger does not respond to players
If MONSTERS is set, the trigger will respond to monsters
If PROJECTILES is set, the trigger will respond to projectiles (rockets, grenades, etc.)

/*****************************************************************************/

CLASS_DECLARATION( Trigger, TriggerChangeLevel, "trigger_changelevel" );

ResponseDef TriggerChangeLevel::Responses[] =
	{
		{ &EV_Trigger_Effect,		( Response )TriggerChangeLevel::ChangeLevel },
		{ NULL, NULL }
	};

TriggerChangeLevel::TriggerChangeLevel()
	{
	map = G_GetStringArg( "map" );
	if ( !map.length() && !LoadingSavegame )
		{
		error( "Init", "changelevel trigger doesn't have map" );
		}

   // We have to handle calling the thread ourselves, so clear out Trigger's tread variable
   thread = "";
   changethread = G_GetStringArg( "thread", "LevelComplete" );

	spawnspot = G_GetStringArg( "spawnspot" );
	respondto = spawnflags ^ TRIGGER_PLAYERS;
	}

void TriggerChangeLevel::ChangeLevel
	(
	Event *ev
	)

	{
	Entity *other;

	other = ev->GetEntity( 1 );

	if ( level.intermissiontime )
		{
		// already activated
		return;
		}

	// if noexit, do a ton of damage to other
	if ( deathmatch->value && DM_FLAG( DF_SAME_LEVEL ) && other != world )
		{
		other->Damage( this, other, 10 * other->max_health, other->worldorigin, vec_zero, vec_zero, 1000, 0, MOD_CRUSH, -1, -1, 1.0f );
		return;
		}

	// if multiplayer, let everyone know who hit the exit
	if ( deathmatch->value )
		{
		if ( other && other->edict->client )
			{
			gi.bprintf( PRINT_HIGH, "%s exited the level.\n", other->edict->client->pers.netname );
			}
		}

   // tell the script that the player's not ready so that if we return to this map,
   // we can do something about it.
   Director.PlayerNotReady();

   //
   // make sure we execute the thread before changing
   //
   if ( changethread.length() )
      {
      ExecuteThread( changethread );
      }

	G_BeginIntermission( map.c_str() );
	}

const char *TriggerChangeLevel::Map
	(
	void
	)

	{
	return map.c_str();
	}

const char *TriggerChangeLevel::SpawnSpot
	(
	void
	)

	{
	return spawnspot.c_str();
	}

/*****************************************************************************/
/*SINED trigger_use (0.5 0.5 0.5) ? VISIBLE x NOT_PLAYERS MONSTERS

Activates targets when 'used' by an entity
"key"          The item needed to activate this. (default nothing)
"thread" name of thread to trigger.  This can be in a different script file as well\
by using the '::' notation.

If NOT_PLAYERS is set, the trigger does not respond to players
If MONSTERS is set, the trigger will respond to monsters

/*****************************************************************************/

CLASS_DECLARATION( Trigger, TriggerUse, "trigger_use" );

ResponseDef TriggerUse::Responses[] =
	{
	   { &EV_Use,		( Response )TriggerUse::TriggerStuff },
		{ &EV_Touch,	NULL },
		{ NULL, NULL }
	};

TriggerUse::TriggerUse()
	{
	if ( spawnflags & VISIBLE )
		{
		showModel();
		setMoveType( MOVETYPE_PUSH );
		setSolidType( SOLID_BSP );
		}

	respondto = ( spawnflags ^ TRIGGER_PLAYERS ) & ~TRIGGER_PROJECTILES;
	}

/*****************************************************************************/
/*SINED trigger_useonce (0.5 0.5 0.5) ? VISIBLE x NOT_PLAYERS MONSTERS

Activates targets when 'used' by an entity, but only once
"key"          The item needed to activate this. (default nothing)
"thread" name of thread to trigger.  This can be in a different script file as well\
by using the '::' notation.

If NOT_PLAYERS is set, the trigger does not respond to players
If MONSTERS is set, the trigger will respond to monsters

/*****************************************************************************/

CLASS_DECLARATION( TriggerUse, TriggerUseOnce, "trigger_useonce" );

ResponseDef TriggerUseOnce::Responses[] =
	{
		{ &EV_Touch,	NULL },
		{ NULL, NULL }
	};

TriggerUseOnce::TriggerUseOnce()
	{
	// Only allow 1 use.
	count = 1;

	respondto = ( spawnflags ^ TRIGGER_PLAYERS ) & ~TRIGGER_PROJECTILES;
	}

/*****************************************************************************/
/*SINED trigger_hurt (0.5 0.5 0.5) ? x x NOT_PLAYERS NOT_MONSTERS PROJECTILES

"damage" amount of damage to cause. (default 10)
"key"          The item needed to activate this. (default nothing)

If NOT_PLAYERS is set, the trigger does not hurt players
If NOT_MONSTERS is set, the trigger does not hurt monsters
If PROJECTILES is set, the trigger will hurt projectiles (rockets, grenades, etc.)

/*****************************************************************************/

Event EV_TriggerHurt_SetDamage( "setdamage" );

CLASS_DECLARATION( TriggerUse, TriggerHurt, "trigger_hurt" );

ResponseDef TriggerHurt::Responses[] =
	{
		{ &EV_Trigger_Effect,		   ( Response )TriggerHurt::Hurt },
		{ &EV_TriggerHurt_SetDamage,  ( Response )TriggerHurt::SetDamage },
	   { &EV_Touch,						( Response )Trigger::TriggerStuff },
		{ NULL, NULL }
	};

TriggerHurt::TriggerHurt()
	{
	damage = G_GetFloatArg( "damage", 10 );
	respondto = spawnflags ^ ( TRIGGER_PLAYERS | TRIGGER_MONSTERS );
	}

void TriggerHurt::SetDamage
	(
	Event *ev
	)

	{
	damage = ev->GetInteger( 1 );
	}

void TriggerHurt::Hurt
	(
	Event *ev
	)

	{
	Entity *other;

	other = ev->GetEntity( 1 );

	if ( ( damage != 0 ) && !other->deadflag && !( other->flags & FL_GODMODE ) )
		{
		other->Damage( this, other, damage, other->worldorigin, vec_zero, vec_zero, 0, DAMAGE_NO_ARMOR|DAMAGE_NO_SKILL, MOD_CRUSH, -1, -1, 1.0f );
		}
	}

/*****************************************************************************/
/*SINED trigger_damagetargets (0.5 0.5 0.5) ? SOLID x NOT_PLAYERS NOT_MONSTERS PROJECTILES

"damage" amount of damage to cause. If no damage is specified, objects\
are damaged by the current health+1

"key"          The item needed to activate this. (default nothing)

if a trigger_damagetargets is shot at and the SOLID flag is set,\
the damage is passed on to the targets

If NOT_PLAYERS is set, the trigger does not hurt players
If NOT_MONSTERS is set, the trigger does not hurt monsters
If PROJECTILES is set, the trigger will hurt projectiles (rockets, grenades, etc.)

/*****************************************************************************/

CLASS_DECLARATION( Trigger, TriggerDamageTargets, "trigger_damagetargets" );

ResponseDef TriggerDamageTargets::Responses[] =
	{
      { &EV_Trigger_ActivateTargets,	( Response )TriggerDamageTargets::DamageTargets },
      { &EV_Damage,						   ( Response )TriggerDamageTargets::PassDamage },
		{ &EV_Touch,                     NULL },
		{ NULL, NULL }
	};

TriggerDamageTargets::TriggerDamageTargets()
	{
	damage = G_GetFloatArg( "damage", 0 );
	respondto = spawnflags ^ ( TRIGGER_PLAYERS | TRIGGER_MONSTERS );

   if (spawnflags & 1)
      {
	   health = 60;
	   max_health = health;
	   takedamage = DAMAGE_YES;
	   setSolidType( SOLID_BBOX );
      }
   else
      {
	   takedamage = DAMAGE_NO;
	   setSolidType( SOLID_NOT );
      }
	}

void TriggerDamageTargets::PassDamage
	(
	Event *ev
	)

	{
	Entity		*attacker;
	int			dmg;
	Entity	   *ent;
	const char	*name;
	int		   num;

	dmg		   = ev->GetInteger( 1 );
	attacker		= ev->GetEntity( 3 );

   //
   // damage the targets
   //
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
		
	      if ( !ent->deadflag && !( ent->flags & FL_GODMODE ) )
		      {
	         ent->Damage( this, attacker, dmg, ent->worldorigin, vec_zero, vec_zero, 0, 0, MOD_CRUSH, -1, -1, 1.0f );
		      }
			}
		while ( 1 );
		}
	}
//
//==============================
// DamageTargets
//==============================
//

void TriggerDamageTargets::DamageTargets
	(
	Event *ev
	)

	{
	Entity	*other;
	Entity	*ent;
	const char		*name;
	int		num;

	other = ev->GetEntity( 1 );

	if ( triggerActivated )
		{
		//
		// Entity triggered itself.  Prevent an infinite loop
		//
		ev->Error( "Entity targeting itself--Targetname '%s'", TargetName() );
		return;
		}

	triggerActivated = true;
	activator = other;
	
   //
   // print the message
   //
	if ( message.length() && other && other->isClient() )
		{
		gi.centerprintf( other->edict, "jcx jcy string \"%s\"", message.c_str() );
		if ( Noise().length() )
			{
			other->sound( Noise(), 1, CHAN_VOICE, ATTN_NORM );
			}
		}
		
   //
   // damage the targets
   //
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
		
	      if ( !ent->deadflag && !( ent->flags & FL_GODMODE ) )
		      {
            if (damage)
		         ent->Damage( this, other, damage, ent->worldorigin, vec_zero, vec_zero, 0, 0, MOD_CRUSH, -1, -1, 1.0f );
            else
               ent->Damage( this, other, ent->health+1, ent->worldorigin, vec_zero, vec_zero, 0, 0, MOD_CRUSH, -1, -1, 1.0f );
		      }
			}
		while ( 1 );
		}

	triggerActivated = false;
	}


/*****************************************************************************/
/*SINED trigger_damagetargetsfixed (0.5 0.5 0.5) (-8 -8 -8) (8 8 8) SOLID x NOT_PLAYERS NOT_MONSTERS PROJECTILES

"damage" amount of damage to cause. If no damage is specified, objects\
are damaged by the current health+1

"key"          The item needed to activate this. (default nothing)

if a trigger_damagetargetsfixed is shot at and the SOLID flag is set,\
the damage is passed on to the targets

If NOT_PLAYERS is set, the trigger does not hurt players
If NOT_MONSTERS is set, the trigger does not hurt monsters
If PROJECTILES is set, the trigger will hurt projectiles (rockets, grenades, etc.)

/*****************************************************************************/

CLASS_DECLARATION( TriggerDamageTargets, TriggerFixedDamageTargets, "trigger_damagetargetsfixed" );

ResponseDef TriggerFixedDamageTargets::Responses[] =
	{
		{ &EV_Touch,	NULL },
		{ NULL, NULL }
	};

/*****************************************************************************/
/*SINED trigger_particles (0.3 0.1 0.6) (-8 -8 -8) (8 8 8)  x NOSOUND NOT_PLAYERS MONSTERS PROJECTILES RANDSTYLE BRIGHT 

spawn some particles when triggered

"count" number of particles to spawn ( default 10 )
"noise" sound to play when triggered ( defaults to random spark sounds )
"angles" specifies direction to spawn particles
"key"   The item needed to activate this. (default nothing)
"particlestyle" style of particles ( default 122 (sparks) )
sample styles (121 blood, 120 gunsmoke, 123 orangeglow, 124 blueyellow, 125 debris trail, 128 oil, 129 waterspray)

If NOSOUND is set, no sound will be played
If NOT_PLAYERS is set, the trigger does not respond to players
If MONSTERS is set, the trigger will respond to monsters
If PROJECTILES is set, the trigger will respond to projectiles (rockets, grenades, etc.)
If RANDSTYLE is set, the particles will be set to random colors in the particlestyle
if BRIGHT is set, particles will be drawn extra bright
/*****************************************************************************/

CLASS_DECLARATION( Trigger, TriggerParticles, "trigger_particles" );

Event EV_TriggerParticles_SetDirection( "setdirection" );

ResponseDef TriggerParticles::Responses[] =
	{
	   { &EV_Trigger_Effect,						( Response )TriggerParticles::SpawnParticles },
	   { &EV_TriggerParticles_SetDirection,	( Response )TriggerParticles::SetDirection },
		{ &EV_Touch,	NULL },
		{ NULL, NULL }
	};

void TriggerParticles::SpawnParticles
	(
	Event *ev
	)

	{
   if ( !(spawnflags & 2) )
      {
      if (Noise().length())
         sound( Noise() );
      else
         RandomGlobalSound( str("sparks") );
      }

   if ( particlestyle == 122 )
      SpawnTempDlight( worldorigin, 1, 1, 0, 100, 0.9, 1 );

   Particles( worldorigin, dir, count, particlestyle, flags );
	}

void TriggerParticles::SetDirection
   (
   Event *ev
   )

   {
   const char  *target;
   int         num;
   Entity      *end;

   // Set the end position if there is a target set.
   target = Target();
   if ( target && strlen( target ) )
      {
      if ( num = G_FindTarget( 0, target ) )
         {
         end = G_GetEntity( num );
         assert( end );
         dir = end->worldorigin - worldorigin;
         dir.normalize();
         }
      }
   else 
      dir = Vector( 0, 0, 0 );
   }

TriggerParticles::TriggerParticles
   (
   )
	
   {
   const char *target;
   target = Target();

   if ( target && strlen( target ) )
      PostEvent( EV_TriggerParticles_SetDirection, 0 );
   else
      dir = G_GetMovedir();

	SetNoise( G_GetSpawnArg( "noise", "" ) );
	count     	= G_GetIntArg( "count", 10 );
	particlestyle	= G_GetIntArg( "particlestyle", 122 );
   
   if ( spawnflags & 32 )
      flags |= PARTICLE_RANDOM;
   if ( spawnflags & 64 )
      flags |= PARTICLE_OVERBRIGHT;
	}

/*****************************************************************************/
/*SINED trigger_randomparticles (0.3 0.1 0.6) (-8 -8 -8) (8 8 8) START_ON NOSOUND NOT_PLAYERS MONSTERS PROJECTILES RANDSTYLE BRIGHT 

START_ON start the effect on

spawn some particles randomly
triggering the object 

"count" number of particles to spawn ( default 10 )
"noise" sound to play when triggered ( default none )
"mindelay" minimum delay between particle triggers (default 3)
"maxdelay" maximum delay between particle triggers (default 10)
"key"      The item needed to activate this. (default nothing)
"particlestyle" style of particles ( default 122 (sparks) )
sample styles (121 blood, 120 gunsmoke, 123 orangeglow, 124 blueyellow, 125 debris trail )

If NOSOUND is set, no sound will be played
If NOT_PLAYERS is set, the trigger does not respond to players
If MONSTERS is set, the trigger will respond to monsters
If PROJECTILES is set, the trigger will respond to projectiles (rockets, grenades, etc.)
If RANDSTYLE is set, the particles will be set to random colors in the particlestyle
if BRIGHT is set, particles will be drawn extra bright
/*****************************************************************************/

Event EV_RandomTriggerParticles_SpawnParticles( "spawnparticles" );

CLASS_DECLARATION( TriggerParticles, RandomTriggerParticles, "trigger_randomparticles" );

ResponseDef RandomTriggerParticles::Responses[] =
	{
	   { &EV_RandomTriggerParticles_SpawnParticles, ( Response )RandomTriggerParticles::RandomParticles },
	   { &EV_Trigger_Effect,						      ( Response )RandomTriggerParticles::ToggleParticles },
		{ &EV_Touch,	NULL },
		{ NULL, NULL }
	};

void RandomTriggerParticles::RandomParticles
	(
	Event *ev
	)

	{
   SpawnParticles( NULL );
   if (state)
      ScheduleParticles();
	}

void RandomTriggerParticles::ToggleParticles
	(
	Event *ev
	)

	{
   state ^= 1;
   if (state)
      ScheduleParticles();
   else
     	CancelEventsOfType( EV_RandomTriggerParticles_SpawnParticles );
	}

void RandomTriggerParticles::ScheduleParticles
	(
   void
	)

	{
   if (state)
      PostEvent( EV_RandomTriggerParticles_SpawnParticles, mindelay + G_Random( maxdelay-mindelay ) );
	}


RandomTriggerParticles::RandomTriggerParticles()
	{
   state = 0;
   if (spawnflags & 1)
      state = 1;
   ScheduleParticles();
	mindelay  	= G_GetFloatArg( "mindelay", 3 );
	maxdelay    = G_GetFloatArg( "maxdelay", 10 );
   }


/*****************************************************************************/
/*SINED trigger_thread (.5 .5 .5) ? notouch x NOT_PLAYERS MONSTERS PROJECTILES

Variable sized trigger. After firing cnt times, removes itself.  

"thread" name of thread to trigger.  This can be in a different script file as well\
by using the '::' notation.

You must set the key "target" to the name of another object in the 
level that has a matching name

"cnt" how many times it can be triggered ( default 1 )
"targetname".  If "health" is set, the trigger must be killed to activate.

if "killtarget" is set, any objects that have a matching "target" will be
removed when the trigger is fired.

if "angle" is set, the trigger will only fire when someone is facing the 
direction of the angle.  Use "360" for an angle of 0.

"key" The item needed to activate this. (default nothing)

If NOT_PLAYERS is set, the trigger does not respond to players
If MONSTERS is set, the trigger will respond to monsters
If PROJECTILES is set, the trigger will respond to projectiles (rockets, grenades, etc.)

set "message" to text string

/*****************************************************************************/

CLASS_DECLARATION( Trigger, TriggerThread, "trigger_thread" );

ResponseDef TriggerThread::Responses[] =
	{
		{ NULL, NULL }
	};

TriggerThread::TriggerThread()
	{
   if ( count == -1 )
      count = 1;
   if ( !thread.length() )
      {
      warning( "TriggerThread", "thread string not defined.\n" );
      }
	}

/*****************************************************************************/
/*SINED trigger_camerause (0.5 0.5 0.5) ? VISIBLE x NOT_PLAYERS MONSTERS

Activates 'targeted' camera when 'used'
If activated, toggles through cameras
"key"          The item needed to activate this. (default nothing)
"thread" name of thread to trigger.  This can be in a different script file as well\
by using the '::' notation.

If NOT_PLAYERS is set, the trigger does not respond to players
If MONSTERS is set, the trigger will respond to monsters

/*****************************************************************************/

CLASS_DECLARATION( TriggerUse, TriggerCameraUse, "trigger_camerause" );

ResponseDef TriggerCameraUse::Responses[] =
	{
	   { &EV_Use,		( Response )TriggerCameraUse::TriggerCamera },
		{ &EV_Touch,	NULL },
		{ NULL, NULL }
	};

void TriggerCameraUse::TriggerCamera
	(
	Event *ev
	)
	{
   str    camthread;
	Entity *other;

	other = ev->GetEntity( 1 );
   if ( other->isClient() )
      {
      int num;
      Player * client;
      Entity * ent;
      Camera * cam;

      client = ( Player * )other;
      if ( client->ViewMode() == CAMERA_VIEW )
         {
         str nextcam;
         cam = client->CurrentCamera();

         // It's possible to get out of the camera
         if ( !cam )
            return;

         nextcam = cam->NextCamera();
         if ( nextcam.length() )
            {
            num = G_FindTarget( 0, nextcam.c_str() );

            if ( num )
               {
               ent = (Entity *) G_GetEntity( num );
               if ( ent && ent->isSubclassOf( Camera ) )
                  {
                  cam = (Camera *)ent;
                  camthread = cam->Thread();
                  client->SetCamera( cam );
                  }
               }
            }
         }
      else
         {
         num = G_FindTarget( 0, Target() );
         if ( num )
            {
            ent = (Entity *) G_GetEntity( num );
            if ( ent && ent->isSubclassOf( Camera ) )
               {
               cam = (Camera *)ent;
               camthread = cam->Thread();
               client->SetCamera( cam );
               }
            else
               {
               warning( "TriggerCamera", "%s is not a camera", Target() );
               }
            }

         }
      if ( camthread.length() > 1 )
         {
         if ( !ExecuteThread( camthread ) )
            {
            warning( "TriggerCamera", "Null game script" );
            }
         }
      }
	}

/*****************************************************************************/
/*SINED trigger_mutate (0.5 0.5 0.5) ? x x NOT_PLAYERS NOT_MONSTERS
mutates whatever triggers it.

"key"          The item needed to activate this. (default nothing)

If NOT_PLAYERS is set, the trigger does not activate on players
If NOT_MONSTERS is set, the trigger does not activate on monsters

/*****************************************************************************/

CLASS_DECLARATION( TriggerUse, TriggerMutate, "trigger_mutate" );

ResponseDef TriggerMutate::Responses[] =
	{
		{ &EV_Trigger_Effect,		   ( Response )TriggerMutate::Mutate },
	   { &EV_Touch,						( Response )Trigger::TriggerStuff },
		{ NULL, NULL }
	};

TriggerMutate::TriggerMutate()
	{
	respondto = spawnflags ^ ( TRIGGER_PLAYERS | TRIGGER_MONSTERS );
	}

void TriggerMutate::Mutate
	(
	Event *ev
	)

	{
   Event *event;
	Entity *other;

	other = ev->GetEntity( 1 );

   if ( other && ( !( other->flags & FL_MUTATED ) ) ) 
      {
      event = new Event( EV_Mutate );
      other->ProcessEvent( event );
      }
	}

/*****************************************************************************/
/*SINED trigger_exit (0.5 0.5 0.5) ?

When the player touches this, an exit icon will be displayed in his hud.
This is to inform him that he is near an exit.

/*****************************************************************************/

CLASS_DECLARATION( Trigger, TriggerExit, "trigger_exit" );

ResponseDef TriggerExit::Responses[] =
	{
		{ &EV_Trigger_Effect,		( Response )TriggerExit::DisplayExitSign },
		{ NULL, NULL }
	};

TriggerExit::TriggerExit()
	{
   wait = 1;
	respondto = TRIGGER_PLAYERS;
	}

void TriggerExit::DisplayExitSign
	(
	Event *ev
	)

	{
	Entity * other;
   Player * client;

	other = ev->GetEntity( 1 );

   if ( other && other->isClient() )
      {
      client = ( Player * )other;

      //
      // change music
      //
      client->ChangeMusic( "success", "normal", false );
      client->client->ps.stats[ STAT_EXITSIGN ] = 11;
      }
	}

/*****************************************************************************/
/*SINED trigger_box (.5 .5 .5) ? x x NOT_PLAYERS MONSTERS PROJECTILES

Variable sized repeatable trigger.  Must be targeted at one or more entities.  Made to
be spawned via script.

If "health" is set, the trigger must be killed to activate each time.
If "delay" is set, the trigger waits some time after activating before firing.

"thread" name of thread to trigger.  This can be in a different script file as well\
by using the '::' notation.

"wait" : Seconds between triggerings. (.2 default)
"cnt" how many times it can be triggered (infinite default)

If NOT_PLAYERS is set, the trigger does not respond to players
If MONSTERS is set, the trigger will respond to monsters
If PROJECTILES is set, the trigger will respond to projectiles (rockets, grenades, etc.)

set "message" to text string

/*****************************************************************************/

CLASS_DECLARATION( Trigger, TriggerBox, "trigger_box" );

ResponseDef TriggerBox::Responses[] =
	{
		{ NULL, NULL }
	};

TriggerBox::TriggerBox()
	{
   mins = G_GetVectorArg( "mins" );
   maxs = G_GetVectorArg( "maxs" );

   origin = ( mins + maxs ) * 0.5;

   setSize( mins - origin, maxs - origin );
	setOrigin( origin );
   }
