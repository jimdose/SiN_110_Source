//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/trigger.h                        $
// $Revision:: 47                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 3/02/99 9:16p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/trigger.h                             $
// 
// 47    3/02/99 9:16p Aldie
// Added CTF game code
// 
// 46    12/10/98 1:45p Jimdose
// added TriggerBox
// 
// 45    10/25/98 11:53p Jimdose
// added EXPORT_TEMPLATE
// 
// 44    10/24/98 6:04p Jimdose
// added changethread to TriggerChangeLevel
// 
// 43    10/23/98 3:44a Markd
// restart trigger_speakers after loading in a save game
// 
// 42    10/17/98 8:13p Jimdose
// Changed Damage to DamgeEvent in DamageThreshold
// Changed ownernum to EntityPtr owner in TouchField
// 
// 41    10/15/98 10:08p Markd
// Made all sounds synched by default
// 
// 40    10/14/98 7:54p Markd
// Added trigger_exit
// 
// 39    10/13/98 11:14p Markd
// Added Trigger_mutate
// 
// 38    9/21/98 4:21p Markd
// Put in archive functions and rewrote all archive routines
// 
// 37    9/20/98 7:30p Aldie
// Added flags to particles
// 
// 36    9/15/98 7:01p Markd
// Added setdamage ability to trigger_hurt's
// 
// 35    9/09/98 3:56p Aldie
// New lightning effect
// 
// 34    8/29/98 9:54p Jimdose
// externed EV_Trigger_StartThread and EV_Trigger_SetKey
// 
// 33    8/24/98 4:55p Markd
// Added speed to TriggerPush
// 
// 32    8/19/98 2:29p Aldie
// Added trigger_pushany
// 
// 31    8/17/98 6:20p Markd
// Added trigger_camerause
// 
// 30    8/14/98 8:18p Markd
// Fixed silly str thing to get rid of weird messages.
// 
// 29    8/05/98 2:52p Markd
// Added thread string variable to all triggers
// 
// 28    7/25/98 2:11a Jimdose
// Added TouchFieldPtr
// 
// 27    7/18/98 4:03p Markd
// Added SetKey event
// 
// 26    7/16/98 5:46p Markd
// Added particlestyle support to trigger_randomparticles
// 
// 25    7/13/98 5:57p Markd
// Added trigger_damagetargetsfixed and trigger_thread
// 
// 24    6/25/98 8:48p Markd
// Rewrote Item class, added keyed items to triggers, cleaned up item system
// 
// 23    5/25/98 5:42p Markd
// Added TriggerParticles and TriggerRandomTriggers
// 
// 22    5/24/98 8:46p Jimdose
// Made a lot of functions more str-friendly.
// Got rid of a lot of char * based strings
// Cleaned up get spawn arg functions and sound functions
// sound functions now use consistant syntax
// 
// 21    5/24/98 4:48p Jimdose
// Made char *'s const
// 
// 20    5/20/98 1:32p Markd
// put more functionality into Trigger_damagetargets
// 
// 19    5/20/98 11:12a Markd
// removed char * dependency
// 
// 18    5/16/98 5:01p Markd
// Added TriggerDamageTargets
// 
// 17    5/13/98 4:52p Jimdose
// now uses SafePtrs
// 
// 16    4/29/98 10:47p Markd
// Added trigger_speaker, trigger_randomspeaker
// 
// 15    4/20/98 1:40p Jimdose
// Added respondto in TouchField::Setup
// 
// 14    4/18/98 2:33p Jimdose
// Added damage_taken to DamageThreshold
// 
// 13    4/04/98 6:17p Jimdose
// Added EV_Trigger_Effect for overriding the effect of a trigger in subclasses
// added respondto variable to determine whether a trigger responds to players,
// monsters, or projectiles
// defined TRIGGER_PLAYERS, TRIGGER_MONSTERS, and TRIGGER_PROJECTILES
// Added TriggerHurt
// 
// 12    3/29/98 9:39p Jimdose
// Changed killed and pain to events
// 
// 11    3/27/98 5:38p Jimdose
// Made TriggerChangeLevel work
// 
// 10    3/23/98 1:33p Jimdose
// Revamped event and command system
// 
// 9     3/02/98 8:49p Jimdose
// Changed CLASS_PROTOTYPE to only take the classname
// 
// 8     2/17/98 6:58p Jimdose
// no longer pass script into interpretCommand
// 
// 7     2/06/98 5:42p Jimdose
// Added event handler to damageThreshold
// 
// 6     2/03/98 10:49a Jimdose
// Updated to work with Quake 2 engine
// Changed from think functions to events
// 
// 4     12/06/97 4:51p Markd
// Added intepretCommand for Trigger and TriggerMonsterJump
// 
// 3     10/27/97 2:59p Jimdose
// Removed dependency on quakedef.h
// 
// 2     9/26/97 5:23p Jimdose
// Added standard Ritual headers
//
// DESCRIPTION:
// Environment based triggers.
// 

#ifndef __TRIGGER_H__
#define __TRIGGER_H__

#include "g_local.h"
#include "entity.h"

class ScriptMaster;

extern Event EV_Trigger_ActivateTargets;
extern Event EV_Trigger_SetWait;
extern Event EV_Trigger_SetDelay;
extern Event EV_Trigger_SetCount;
extern Event EV_Trigger_SetMessage;
extern Event EV_Trigger_SetNoise;
extern Event EV_Trigger_SetKey;
extern Event EV_Trigger_Effect;
extern Event EV_Trigger_StartThread;
extern Event EV_Trigger_SetKey;

#define TRIGGER_PLAYERS			4
#define TRIGGER_MONSTERS		8
#define TRIGGER_PROJECTILES	16

class EXPORT_FROM_DLL Trigger : public Entity
	{
	protected:
		float			wait;
		float			delay;
		float			trigger_time;
		qboolean		triggerActivated;
		int			count;
		str		   noise;
		str			message;
      str         key;
      str         thread;
		EntityPtr	activator;
		int			respondto;

	public:
      CLASS_PROTOTYPE( Trigger );

						Trigger();
		virtual		~Trigger();

		void			Touch( Event *ev );
		void			EventSetWait( Event *ev );
		void			EventSetDelay( Event *ev );
		void			EventSetCount( Event *ev );
		void			EventSetKey( Event *ev );

		void			EventSetMessage( Event *ev );
		void        SetTriggerTime( float t ){ trigger_time = t; }
		void			SetMessage( const char *message );
		str         &Message( void );

		void			EventSetNoise( Event *ev );
		void			SetNoise( const char *text );
		str         &Noise( void );

      void        StartThread( Event *ev );
		void			TriggerStuff( Event *ev );
		void			ActivateTargets( Event *ev );
      virtual void Archive( Archiver &arc );
      virtual void Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Trigger::Archive
	(
	Archiver &arc
	)
   {
   Entity::Archive( arc );
   arc.WriteFloat( wait );
   arc.WriteFloat( delay );
   arc.WriteFloat( trigger_time );
   arc.WriteBoolean( triggerActivated );
   arc.WriteInteger( count );
   arc.WriteString( noise );
   arc.WriteString( message );
   arc.WriteString( key );
   arc.WriteString( thread );
   arc.WriteSafePointer( activator );
   arc.WriteInteger( respondto );
   }

inline EXPORT_FROM_DLL void Trigger::Unarchive
	(
	Archiver &arc
	)
   {
   Entity::Unarchive( arc );
   arc.ReadFloat( &wait );
   arc.ReadFloat( &delay );
   arc.ReadFloat( &trigger_time );
   arc.ReadBoolean( &triggerActivated );
   arc.ReadInteger( &count );
   arc.ReadString( &noise );
   arc.ReadString( &message );
   arc.ReadString( &key );
   arc.ReadString( &thread );
   arc.ReadSafePointer( &activator );
   arc.ReadInteger( &respondto );
   }

class EXPORT_FROM_DLL TouchField : public Trigger
	{
	private:
		Event				ontouch;
		EntityPtr      owner;

	public:
      CLASS_PROTOTYPE( TouchField );

		virtual void	Setup( Entity *ownerentity, Event ontouch, Vector min, Vector max, int respondto );
		void				SendEvent( Event *ev );
      virtual void   Archive(	Archiver &arc );
      virtual void   Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void TouchField::Archive
	(
	Archiver &arc
	)
   {
   Trigger::Archive( arc );
   arc.WriteEvent( ontouch );
   arc.WriteSafePointer( owner );
   }

inline EXPORT_FROM_DLL void TouchField::Unarchive
	(
	Archiver &arc
	)
   {
   Trigger::Unarchive( arc );
   arc.ReadEvent( &ontouch );
   arc.ReadSafePointer( &owner );
   }

#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL SafePtr<TouchField>;
#endif
typedef SafePtr<TouchField> TouchFieldPtr;

class EXPORT_FROM_DLL TriggerOnce : public Trigger
	{
	public:
      CLASS_PROTOTYPE( TriggerOnce );
		TriggerOnce();
	};

class EXPORT_FROM_DLL TriggerRelay : public Trigger
	{
	public:
      CLASS_PROTOTYPE( TriggerRelay );
		
		TriggerRelay();
	};

class EXPORT_FROM_DLL DamageThreshold : public Trigger
	{
	protected:
		int				damage_taken;

	public:
      CLASS_PROTOTYPE( DamageThreshold );

		virtual void	DamageEvent( Event *ev );
		void				Setup( Event *ev );
							DamageThreshold();
      virtual void   Archive(	Archiver &arc );
      virtual void   Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void DamageThreshold::Archive
	(
	Archiver &arc
	)
   {
   Trigger::Archive( arc );
   arc.WriteInteger( damage_taken );
   }

inline EXPORT_FROM_DLL void DamageThreshold::Unarchive
	(
	Archiver &arc
	)
   {
   Trigger::Unarchive( arc );
   arc.ReadInteger( &damage_taken );
   }

class EXPORT_FROM_DLL TriggerSecret : public TriggerOnce
	{
	public:
      CLASS_PROTOTYPE( TriggerSecret );
								
				TriggerSecret();
		void	FoundSecret( Event *ev );
		void	Activate( Event *ev );
	};

class EXPORT_FROM_DLL TriggerPush : public Trigger
	{
	protected:
      float    speed;
		Vector	pushvelocity;

	public:
      CLASS_PROTOTYPE( TriggerPush );

					TriggerPush();
		void		Push( Event *ev );
      virtual void Archive(	Archiver &arc );
      virtual void Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void TriggerPush::Archive
	(
	Archiver &arc
	)
   {
   Trigger::Archive( arc );
   arc.WriteFloat( speed );
   arc.WriteVector( pushvelocity );
   }

inline EXPORT_FROM_DLL void TriggerPush::Unarchive
	(
	Archiver &arc
	)
   {
   Trigger::Unarchive( arc );
   arc.ReadFloat( &speed );
   arc.ReadVector( &pushvelocity );
   }

class EXPORT_FROM_DLL TriggerPushAny : public Trigger
	{
	protected:
      float    speed;
		Vector	pushvelocity;

	public:
      CLASS_PROTOTYPE( TriggerPushAny );

					TriggerPushAny();
		void		Push( Event *ev );
      virtual void Archive(	Archiver &arc );
      virtual void Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void TriggerPushAny::Archive
	(
	Archiver &arc
	)
   {
   Trigger::Archive( arc );
   arc.WriteFloat( speed );
   arc.WriteVector( pushvelocity );
   }

inline EXPORT_FROM_DLL void TriggerPushAny::Unarchive
	(
	Archiver &arc
	)
   {
   Trigger::Unarchive( arc );
   arc.ReadFloat( &speed );
   arc.ReadVector( &pushvelocity );
   }

class EXPORT_FROM_DLL TriggerPlaySound : public Trigger
	{
	protected:
		int	state;
		float	attenuation;
		float	volume;
      int	channel;
      qboolean ambient;
		float fadetime;
      float timeofs;
      float pitch;

	public:
      CLASS_PROTOTYPE( TriggerPlaySound );

				TriggerPlaySound();
		void	ToggleSound( Event *ev );
		void	SetVolume( Event *ev );
		void	SetAttenuation( Event *ev );
		void	SetChannel( Event *ev );
      virtual void Archive(	Archiver &arc );
      virtual void Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void TriggerPlaySound::Archive
	(
	Archiver &arc
	)
   {
   Trigger::Archive( arc );
   arc.WriteInteger( state );
   arc.WriteFloat( attenuation );
   arc.WriteFloat( volume );
   arc.WriteInteger( channel );
   arc.WriteBoolean( ambient );
   arc.WriteFloat( fadetime );
   arc.WriteFloat( timeofs );
   arc.WriteFloat( pitch );
   }

inline EXPORT_FROM_DLL void TriggerPlaySound::Unarchive
	(
	Archiver &arc
	)
   {
   Trigger::Unarchive( arc );
   arc.ReadInteger( &state );
   arc.ReadFloat( &attenuation );
   arc.ReadFloat( &volume );
   arc.ReadInteger( &channel );
   arc.ReadBoolean( &ambient );
   arc.ReadFloat( &fadetime );
   arc.ReadFloat( &timeofs );
   arc.ReadFloat( &pitch );

   //
   // see if its a toggle sound, if it is, lets start its sound again
   //
   if ( spawnflags & 128 )
      {
      //
      // invert state so that final state will be right
      //
      state = !state;
      ToggleSound( NULL );
      }
   }


class EXPORT_FROM_DLL TriggerSpeaker : public TriggerPlaySound
	{
	public:
      CLASS_PROTOTYPE( TriggerSpeaker );

				TriggerSpeaker();
	};

class EXPORT_FROM_DLL RandomSpeaker : public TriggerSpeaker
	{
	protected:
      float mindelay;
      float maxdelay;

	public:
      CLASS_PROTOTYPE( RandomSpeaker );

				RandomSpeaker();
      void  TriggerSound( Event *ev	);
      void  ScheduleSound( void );
      virtual void Archive(	Archiver &arc );
      virtual void Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void RandomSpeaker::Archive
	(
	Archiver &arc
	)
   {
   TriggerSpeaker::Archive( arc );
   arc.WriteFloat( mindelay );
   arc.WriteFloat( maxdelay );
   }

inline EXPORT_FROM_DLL void RandomSpeaker::Unarchive
	(
	Archiver &arc
	)
   {
   TriggerSpeaker::Unarchive( arc );
   arc.ReadFloat( &mindelay );
   arc.ReadFloat( &maxdelay );
   }

class EXPORT_FROM_DLL TriggerChangeLevel : public Trigger
	{
	protected:
		str			map;
		str			spawnspot;
      str         changethread;

	public:
      CLASS_PROTOTYPE( TriggerChangeLevel );

						TriggerChangeLevel();
		void			ChangeLevel( Event *ev );
		const char	*Map( void );
		const char	*SpawnSpot( void );
      virtual void Archive(	Archiver &arc );
      virtual void Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void TriggerChangeLevel::Archive
	(
	Archiver &arc
	)
   {
   Trigger::Archive( arc );

   arc.WriteString( map );
   arc.WriteString( spawnspot );
   arc.WriteString( changethread );
   }

inline EXPORT_FROM_DLL void TriggerChangeLevel::Unarchive
	(
	Archiver &arc
	)
   {
   Trigger::Unarchive( arc );

   arc.ReadString( &map );
   arc.ReadString( &spawnspot );
   arc.ReadString( &changethread );
   }

class EXPORT_FROM_DLL TriggerExit : public Trigger
	{
	public:
      CLASS_PROTOTYPE( TriggerExit );

			  TriggerExit();
		void DisplayExitSign( Event *ev );
	};


class EXPORT_FROM_DLL TriggerUse : public Trigger
	{
	public:
      CLASS_PROTOTYPE( TriggerUse );
		
		TriggerUse();
	};

class EXPORT_FROM_DLL TriggerUseOnce : public TriggerUse
	{
	public:
      CLASS_PROTOTYPE( TriggerUseOnce );

		TriggerUseOnce();
	};

class EXPORT_FROM_DLL TriggerHurt : public TriggerUse
	{
	protected:
		float		damage;

		void		Hurt( Event *ev );
      void		SetDamage( Event *ev );

	public:
      CLASS_PROTOTYPE( TriggerHurt );

		             TriggerHurt();
      virtual void Archive(	Archiver &arc );
      virtual void Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void TriggerHurt::Archive
	(
	Archiver &arc
	)
   {
   Trigger::Archive( arc );

   arc.WriteFloat( damage );
   }

inline EXPORT_FROM_DLL void TriggerHurt::Unarchive
	(
	Archiver &arc
	)
   {
   Trigger::Unarchive( arc );

   arc.ReadFloat( &damage );
   }

class EXPORT_FROM_DLL TriggerDamageTargets : public Trigger
	{
	protected:
		float		    damage;

		void		    DamageTargets( Event *ev );

	public:
      CLASS_PROTOTYPE( TriggerDamageTargets );

		             TriggerDamageTargets();
		void	       PassDamage( Event *ev );
      virtual void Archive(	Archiver &arc );
      virtual void Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void TriggerDamageTargets::Archive
	(
	Archiver &arc
	)
   {
   Trigger::Archive( arc );

   arc.WriteFloat( damage );
   }

inline EXPORT_FROM_DLL void TriggerDamageTargets::Unarchive
	(
	Archiver &arc
	)
   {
   Trigger::Unarchive( arc );

   arc.ReadFloat( &damage );
   }

class EXPORT_FROM_DLL TriggerFixedDamageTargets : public TriggerDamageTargets
	{
	public:
      CLASS_PROTOTYPE( TriggerFixedDamageTargets );
	};

class EXPORT_FROM_DLL TriggerParticles : public Trigger
	{
	protected:
      Vector   dir;
      int      particlestyle;
      int      count;

	public:
      CLASS_PROTOTYPE( TriggerParticles );

                   TriggerParticles();
      void         SpawnParticles( Event *ev	);
      void         SetDirection( Event *ev );
      virtual void Archive(	Archiver &arc );
      virtual void Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void TriggerParticles::Archive
	(
	Archiver &arc
	)
   {
   Trigger::Archive( arc );
   
   arc.WriteVector( dir );
   arc.WriteInteger( particlestyle );
   arc.WriteInteger( count );
   }

inline EXPORT_FROM_DLL void TriggerParticles::Unarchive
	(
	Archiver &arc
	)
   {
   Trigger::Unarchive( arc );
   
   arc.ReadVector( &dir );
   arc.ReadInteger( &particlestyle );
   arc.ReadInteger( &count );
   }

class EXPORT_FROM_DLL RandomTriggerParticles : public TriggerParticles
	{
	protected:
      int   state;
      float mindelay;
      float maxdelay;

      void  ScheduleParticles( void );
      void  RandomParticles( Event * ev );
      void  ToggleParticles( Event * ev );

	public:
      CLASS_PROTOTYPE( RandomTriggerParticles );

      RandomTriggerParticles();
      virtual void Archive(	Archiver &arc );
      virtual void Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void RandomTriggerParticles::Archive
	(
	Archiver &arc
	)
   {
   TriggerParticles::Archive( arc );

   arc.WriteInteger( state );
   arc.WriteFloat( mindelay );
   arc.WriteFloat( maxdelay );
   }

inline EXPORT_FROM_DLL void RandomTriggerParticles::Unarchive
	(
	Archiver &arc
	)
   {
   TriggerParticles::Unarchive( arc );

   arc.ReadInteger( &state );
   arc.ReadFloat( &mindelay );
   arc.ReadFloat( &maxdelay );
   }

class EXPORT_FROM_DLL TriggerThread : public Trigger
	{
	public:
      CLASS_PROTOTYPE( TriggerThread );

		TriggerThread();
	};

class EXPORT_FROM_DLL TriggerCameraUse : public TriggerUse
	{
	public:
      CLASS_PROTOTYPE( TriggerCameraUse );

		void TriggerCamera( Event * ev );
	};

class EXPORT_FROM_DLL TriggerMutate : public TriggerUse
	{
	protected:
		void		Mutate( Event *ev );

	public:
      CLASS_PROTOTYPE( TriggerMutate );

		TriggerMutate();
	};

class EXPORT_FROM_DLL TriggerBox : public Trigger
	{
	public:
      CLASS_PROTOTYPE( TriggerBox );

		TriggerBox();
	};

#endif /* trigger.h */
