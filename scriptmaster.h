//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/scriptmaster.h                   $
// $Revision:: 89                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 5/19/99 11:30a                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/scriptmaster.h                        $
// 
// 89    5/19/99 11:30a Markd
// Added new camera support 
// 
// 88    12/16/98 12:42a Aldie
// Added endgame command for Sin Arcade
// 
// 87    12/14/98 7:00p Aldie
// Added mapname command
// 
// 86    11/11/98 10:55p Jimdose
// Added RemoveEnt, RemoveClass, KillEnt, KillClass
// 
// 85    11/10/98 4:34p Jimdose
// added ClearSaveGames
// 
// 84    11/07/98 10:15p Markd
// Added forcemusic support
// 
// 83    10/27/98 9:46p Aldie
// Changed training cvar to level.training
// 
// 82    10/27/98 8:07p Markd
// Added dialogsound command
// 
// 81    10/26/98 9:07p Aldie
// Added stuffcommand
// 
// 80    10/26/98 5:15p Jimdose
// 
// 79    10/26/98 4:42p Jimdose
// added recalcpaths
// 
// 78    10/26/98 2:16p Aldie
// Added AirClamp
// 
// 77    10/26/98 12:42a Markd
// Added new print commands and crucialdialog
// 
// 76    10/25/98 11:53p Jimdose
// added EXPORT_TEMPLATE
// 
// 75    10/25/98 6:26p Markd
// Added in no_jc abililty
// 
// 74    10/24/98 9:37p Jimdose
// Added GetUniqueThreadNumber
// 
// 73    10/22/98 5:02p Aldie
// Added a clearscreenprintfile command
// 
// 72    10/18/98 7:59p Aldie
// Added screenprintfile
// 
// 71    10/14/98 12:14a Aldie
// Added a bunch of intermission stuff
// 
// 70    10/08/98 12:00a Jimdose
// Made savegames work
// 
// 69    9/26/98 7:17p Markd
// Made WaitFor support more than one object with the same target name
// 
// 68    9/21/98 10:15p Markd
// Putting archiving and unarchiving functions in
// 
// 67    9/19/98 6:14p Aldie
// Added screenprint command
// 
// 66    9/02/98 7:48p Aldie
// Added cacheplayermodel
// 
// 65    8/24/98 11:32a Markd
// Added Start method to threads, repladed all ProcessEvent(
// EV_ScriptThread_execute) with thread->Start( -1 )
// 
// 64    8/22/98 6:34p Markd
// Added Terminate extened behavior
// 
// 63    8/22/98 1:22a Markd
// Added WaitForPlayer support
// 
// 62    8/21/98 1:43a Markd
// Changed parameters to CreateThread
// 
// 61    8/20/98 4:39p Markd
// Added PrintVector support
// 
// 60    8/19/98 6:38p Markd
// Added noncinematic event
// 
// 59    8/17/98 7:31p Jimdose
// Added WaitingFor to test if a thread is waiting for the specified entity
// 
// 58    8/17/98 4:36p Markd
// Added SetCinematic and SkipThread
// 
// 57    8/17/98 4:15p Jimdose
// Added ThreadName
// 
// 56    8/15/98 5:31p Jimdose
// Added SetScript to ScriptThread for changing script files without using a
// Goto
// 
// 55    8/14/98 9:09p Jimdose
// added waitUntil to keep track of wait times when marking and restoring (used
// when changing actor states)
// 
// 54    8/14/98 8:14p Aldie
// Added generic overlay system
// 
// 53    8/14/98 3:44p Jimdose
// WaitingFor variables are now all cleared after they're no longer valid
// 
// 52    8/13/98 7:29p Jimdose
// Added type to scriptthreads
// 
// 51    8/06/98 5:18p Jimdose
// Added ProcessCommandFromEvent
// 
// 50    7/25/98 4:38p Aldie
// Menu controls
// 
// 49    7/24/98 6:16p Aldie
// Added hud command
// 
// 48    7/24/98 4:52p Jimdose
// Added setcvar command to script
// 
// 47    7/21/98 9:07p Markd
// Added music event and soundtrack event
// 
// 46    7/20/98 5:48p Jimdose
// Added map command for changing levels
// 
// 45    7/18/98 7:38p Aldie
// Added support for fades
// 
// 44    7/11/98 8:45p Markd
// Added CreateThread optional label support
// 
// 43    7/11/98 2:50p Markd
// Added dialog event
// 
// 42    7/07/98 11:36p Jimdose
// Added error for unsupported global commands
// made end command signal self if model script
// added ThreadMarker
// 
// 41    7/03/98 4:11p Jimdose
// Added assert and break
// 
// 40    6/27/98 7:03p Markd
// Added WaitForSound
// 
// 39    6/18/98 8:49p Jimdose
// Removed ScriptError from ScriptMaster
// Made ScriptThread's ScriptError private
// Added Filename() to ScriptThread
// 
// 38    6/09/98 4:25p Jimdose
// Added multi-file scripting
// 
// 37    5/26/98 11:59p Markd
// moved goto and label to ScriptMaster
// 
// 36    5/26/98 9:26p Aldie
// Added spawn command
// 
// 35    5/26/98 7:56p Jimdose
// added scripted cameras
// 
// 34    5/26/98 4:20p Markd
// Added TargetList stuff to ScriptThread
// 
// 33    5/25/98 1:39p Aldie
// Added create console user
// 
// 32    5/24/98 8:46p Jimdose
// Made a lot of functions more str-friendly.
// Got rid of a lot of char * based strings
// Cleaned up get spawn arg functions and sound functions
// sound functions now use consistant syntax
// 
// 31    5/24/98 4:48p Jimdose
// Made char *'s const
// 
// 30    5/22/98 10:57a Markd
// put in label parsing into ScriptThread
// 
// 29    5/22/98 10:04a Jimdose
// added ThreadPtr as safe pointer
// 
// 28    5/20/98 5:28p Jimdose
// Added threadDying to prevent threads from executing after an "end" was
// reached
// 
// 27    5/19/98 4:24p Aldie
// Added DeathCallback and WaitForDeath
// 
// 26    5/11/98 5:53p Markd
// Added aliascache command
// 
// 25    5/08/98 2:57p Markd
// Added Register Alias method
// 
// 24    5/04/98 8:32p Markd
// Added cachemodel, cachesound and setlightstyle to ScriptThread
// 
// 23    5/02/98 8:47p Markd
// Added CreateThread behavior, and added private buffer stuff
// 
// 22    5/01/98 5:05p Jimdose
// Added TriggerEvent
// 
// 21    4/30/98 9:24p Jimdose
// Changed use of string to str class
// 
// 20    4/03/98 1:11p Aldie
// Added consolevar
// 
// 19    3/28/98 3:28p Aldie
// 
// 18    3/26/98 7:16p Aldie
// Added console type vars.
// 
// 17    3/26/98 2:53p Aldie
// Added interface between consoles and scripts.
// 
// 16    3/24/98 8:54p Jimdose
// Added thread management script commands
// 
// 15    3/24/98 5:04p Jimdose
// Removed ReadScript since it had become redundant
// 
// 14    3/23/98 1:33p Jimdose
// Revamped event and command system
// 
// 13    3/02/98 8:49p Jimdose
// Changed CLASS_PROTOTYPE to only take the classname
// 
// 12    3/02/98 5:39p Jimdose
// Changed Container to template
// 
// 11    2/24/98 3:42p Aldie
// Added support for texinfo commands.
// 
// 10    2/21/98 1:10p Jimdose
// Changed initThread so that it doesn't search for a label if a NULL pointer
// is passed in and added a parameter to determine if it should execute the
// code immediately.
// 
// 9     2/18/98 8:12p Jimdose
// Added new slave events.
// removed currentEntity
// Changed waitingFor to the targetname of the entity to wait for
// Added SendCommandToSlaves
// Replaced getScriptObject, getEntityFromScript, and FindEntity with GetObject
// 
// 8     2/17/98 7:07p Jimdose
// Rewrote script variable support.  New support KICKS ASS. :)
// 
// 7     2/03/98 10:48a Jimdose
// Updated to work with Quake 2 engine
// Got rid of preprocessing stage.
// 
// 5     11/07/97 6:41p Jimdose
// Changed DoMove to remove entities from the updateList more efficiently.
// Added support for variables.
// 
// 4     10/27/97 2:59p Jimdose
// Removed dependency on quakedef.h
// 
// 3     9/26/97 5:23p Jimdose
// Added standard Ritual headers
//
// DESCRIPTION:
// Script masters are invisible entities that are spawned at the begining of each
// map.  They simple parse the script and send commands to the specified objects
// at the apropriate time.  Using a combination of simple commands, very complex
// scripted events can occur.
// 

#ifndef __SCRIPTMASTER_H__
#define __SCRIPTMASTER_H__

#include "g_local.h"
#include "entity.h"
#include "trigger.h"
#include "gamescript.h"
#include "container.h"
#include "scriptvariable.h"
#include "worldspawn.h"

#define MAX_COMMANDS 20

typedef enum
	{
	LEVEL_SCRIPT,
	MODEL_SCRIPT
	} scripttype_t;

extern ScriptVariableList gameVars;
extern ScriptVariableList levelVars;
extern ScriptVariableList consoleVars;

extern Event EV_ProcessCommands;
extern Event EV_ScriptThread_Execute;
extern Event EV_ScriptThread_Callback;
extern Event EV_ScriptThread_CreateThread;
extern Event EV_ScriptThread_TerminateThread;
extern Event EV_ScriptThread_ControlObject;
extern Event EV_ScriptThread_Goto;
extern Event EV_ScriptThread_Pause;
extern Event EV_ScriptThread_Wait;
extern Event EV_ScriptThread_WaitFor;
extern Event EV_ScriptThread_WaitForThread;
extern Event EV_ScriptThread_WaitForSound;
extern Event EV_ScriptThread_End;
extern Event EV_ScriptThread_Print;
extern Event EV_ScriptThread_PrintInt;
extern Event EV_ScriptThread_PrintFloat;
extern Event EV_ScriptThread_PrintVector;
extern Event EV_ScriptThread_NewLine;
extern Event EV_ScriptThread_Clear;
extern Event EV_ScriptThread_Assert;
extern Event EV_ScriptThread_Break;
extern Event EV_ScriptThread_Clear;
extern Event EV_ScriptThread_Trigger;
extern Event EV_ScriptThread_Spawn;
extern Event EV_ScriptThread_Map;
extern Event EV_ScriptThread_SetCvar;
extern Event EV_ScriptThread_CueCamera;
extern Event EV_ScriptThread_CuePlayer;
extern Event EV_ScriptThread_FreezePlayer;
extern Event EV_ScriptThread_ReleasePlayer;
extern Event EV_ScriptThread_SetCinematic;
extern Event EV_ScriptThread_SetNonCinematic;
extern Event EV_ScriptThread_SetSkipThread;

class ScriptThread;
#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL SafePtr<ScriptThread>;
#endif
typedef SafePtr<ScriptThread> ThreadPtr;

class ThreadMarker;

class EXPORT_FROM_DLL ScriptThread : public Listener
	{
	protected:
		int						threadNum;
		str						threadName;

		scripttype_t			type;
		GameScript				script;
      Container<TargetList *> targets;

		int						linenumber;
		qboolean					doneProcessing;
		qboolean					threadDying;

		Container<int>			updateList;
		float						waitUntil;
		str						waitingFor;
		ScriptThread			*waitingForThread;
      str						waitingForConsole;
      str						waitingForVariable;
      str						waitingForDeath;
      qboolean             waitingForPlayer;
		int						waitingNumObjects;
		ScriptVariableList	localVars;

		void						ObjectMoveDone( Event *ev );
		void 						CreateThread( Event *ev );
		void 						TerminateThread( Event *ev );
		void 						ControlObject( Event *ev );
		void 						EventGoto( Event *ev );
		void 						EventPause( Event *ev );
		void 						EventWait( Event *ev );
		void 						EventWaitFor( Event *ev );
		void						EventWaitForThread( Event *ev );
      void						EventWaitForConsole( Event *ev );
      void						EventWaitForVariable( Event *ev );
      void						EventWaitForDeath( Event *ev );
      void						EventWaitForSound( Event *ev );
      void						EventWaitForPlayer( Event *ev );
		void 						EventEnd( Event *ev );
		void 						Print( Event *ev );
		void 						PrintInt( Event *ev );
		void 						PrintFloat( Event *ev );
		void 						PrintVector( Event *ev );
		void 						NewLine( Event *ev );
		void 						UserPrint( Event *ev );
		void 						UserPrintInt( Event *ev );
		void 						UserPrintFloat( Event *ev );
		void 						UserPrintVector( Event *ev );
		void 						UserNewLine( Event *ev );
		void 						Assert( Event *ev );
		void 						Break( Event *ev );
		void 						Clear( Event *ev );
		void 						ScriptCallback( Event *ev );
		void 						ThreadCallback( Event *ev );
      void 						ConsoleCallback( Event *ev );
      void 						VariableCallback( Event *ev );
      void 						DeathCallback( Event *ev );
		void 						DoMove( void );
		void 						Execute( Event *ev );
		void						TriggerEvent( Event *ev );
		void						ServerEvent( Event *ev );
		void						ClientEvent( Event *ev );
      void                 CacheModel( Event *ev );
      void                 CachePlayerModel( Event *ev );
      void                 CacheSound( Event *ev );
      void                 SetLightStyle( int stylenum, const char *stylestring );
      void                 EventSetLightStyle( Event *ev );
      void                 RegisterAlias( Event *ev );
      void                 RegisterAliasAndCache( Event *ev );
		void						MapEvent( Event *ev );
		void						SetCvarEvent( Event *ev );

      TargetList           *GetTargetList( str &targetname );

		void						CueCamera( Event *ev );
		void						CuePlayer( Event *ev );
		void						FreezePlayer( Event *ev );
		void						ReleasePlayer( Event *ev );
      void                 Spawn( Event *ev );
		void						DialogEvent( Event *ev );
		void						CrucialDialogEvent( Event *ev );
      void                 DialogSoundEvent( Event *ev );
      void                 SetDialogScript( Event *ev	);
      void                 FadeIn( Event *ev	);
      void                 FadeOut( Event *ev );
      void                 Hud( Event *ev );
      void						LoadOverlay( Event *ev );
      void						LoadIntermission( Event *ev );
      void						IntermissionLayout( Event *ev );
      void						Overlay( Event *ev );
      void						ScreenPrint( Event *ev );
      void						ScreenPrintFile( Event *ev );
      void						ClearScreenPrintFile( Event *ev );
      void                 MenuEvent( Event *ev );
      void                 MusicEvent( Event *ev	);
      void                 ForceMusicEvent( Event *ev	);
      void                 SoundtrackEvent( Event *ev );
		void						ScriptError( const char *fmt, ... );
		void						SetCinematic( Event *ev );
		void						SetNonCinematic( Event *ev );
		void						SetSkipThread( Event *ev );
      void                 JC_Hearable( Event *ev );
      void                 JC_Not_Hearable( Event *ev );
      void                 MissionFailed( Event *ev );
      void                 PassToPathmanager( Event *ev );
      void                 AirClamp( Event *ev );
      void                 StuffCommand( Event *ev );
      void                 Training( Event *ev );
      void                 ClearSaveGames( Event *ev );
		void		            KillEnt( Event *ev );
		void		            RemoveEnt( Event *ev );
		void		            KillClass( Event *ev );
		void		            RemoveClass( Event *ev );
      void                 MapName( Event *ev );
      void                 EndGame( Event *ev );
      void                 CameraCommand( Event *ev );

	public:
      CLASS_PROTOTYPE( ScriptThread );

									ScriptThread();
									~ScriptThread();
		void						ClearWaitFor( void );
		void						SetType( scripttype_t newtype );
		scripttype_t			GetType( void );
		int						ThreadNum( void );
		const char				*ThreadName( void );
		int						CurrentLine( void );
		const char				*Filename( void );
		qboolean					WaitingFor( Entity *obj );
		ScriptThread			*WaitingOnThread( void );
      const char				*WaitingOnConsole( void );
      const char				*WaitingOnVariable( void );
      const char				*WaitingOnDeath( void );
      qboolean             WaitingOnPlayer( void );
		ScriptVariableList	*Vars( void );
		qboolean					Setup( int num, GameScript *scr, const char *label );
		qboolean					SetScript( const char *name );
		qboolean					Goto( const char *name );
		qboolean					labelExists( const char *name );
		void                 Start( float delay );

		void						Mark( ThreadMarker *mark );
		void						Restore( ThreadMarker *mark );

		void						SendCommandToSlaves( const char *name, Event *ev );
		qboolean					FindEvent( const char *name );
		void						ProcessCommand( int argc, const char **argv );
		void						ProcessCommandFromEvent( Event *ev, int startarg );
      virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void ScriptThread::Archive
	(
	Archiver &arc
	)

   {
   Listener::Archive( arc );

   arc.WriteInteger( threadNum );
   arc.WriteString( threadName );
   arc.WriteInteger( type );

   arc.WriteObject( &script );

   // targets
   // don't need to save out targets

   arc.WriteInteger( linenumber );
   arc.WriteBoolean( doneProcessing );
   arc.WriteBoolean( threadDying );

   // updateList
   // don't need to save out updatelist

   arc.WriteFloat( waitUntil );
   arc.WriteString( waitingFor );
   arc.WriteObjectPointer( waitingForThread );
   arc.WriteString( waitingForConsole );
   arc.WriteString( waitingForVariable );
   arc.WriteString( waitingForDeath );
   arc.WriteBoolean( waitingForPlayer );
   arc.WriteInteger( waitingNumObjects );
   arc.WriteObject( &localVars );
   }

inline EXPORT_FROM_DLL void ScriptThread::Unarchive
	(
	Archiver &arc
	)

   {
   int i;

   Listener::Unarchive( arc );

   arc.ReadInteger( &threadNum );
   arc.ReadString( &threadName );
   arc.ReadInteger( &i );
   type = ( scripttype_t )i;

   arc.ReadObject( &script );

   // targets
   // don't need to load out targets
   targets.ClearObjectList();

   arc.ReadInteger( &linenumber );
   arc.ReadBoolean( &doneProcessing );
   arc.ReadBoolean( &threadDying );

   // updateList
   // don't need to save out updatelist
   updateList.ClearObjectList();

   arc.ReadFloat( &waitUntil );
   arc.ReadString( &waitingFor );
   arc.ReadObjectPointer( ( Class ** )&waitingForThread );
   arc.ReadString( &waitingForConsole );
   arc.ReadString( &waitingForVariable );
   arc.ReadString( &waitingForDeath );
   arc.ReadBoolean( &waitingForPlayer );
   arc.ReadInteger( &waitingNumObjects );
   arc.ReadObject( &localVars );
   }

//
// Exported templated classes must be explicitly instantiated
//
#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL Container<ScriptThread *>;
#endif

class EXPORT_FROM_DLL ThreadMarker : public Class
	{
	public:
      CLASS_PROTOTYPE( ThreadMarker );

		int						linenumber;
		qboolean					doneProcessing;
		float						waitUntil;
		str						waitingFor;
		ScriptThread			*waitingForThread;
      str						waitingForConsole;
      str						waitingForVariable;
      str						waitingForDeath;
      qboolean             waitingForPlayer;
		int						waitingNumObjects;
		GameScriptMarker		scriptmarker;
      virtual void         Archive( Archiver &arc );
      virtual void         Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void ThreadMarker::Archive
	(
	Archiver &arc
	)
   {
   Class::Archive( arc );

   arc.WriteInteger( linenumber );
   arc.WriteBoolean( doneProcessing );
   arc.WriteFloat( waitUntil );
   arc.WriteString( waitingFor );
   arc.WriteObjectPointer( waitingForThread );
   arc.WriteString( waitingForConsole );
   arc.WriteString( waitingForVariable );
   arc.WriteString( waitingForDeath );
   arc.WriteBoolean( waitingForPlayer );
   arc.WriteInteger( waitingNumObjects );
   arc.WriteObject( &scriptmarker );
   }

inline EXPORT_FROM_DLL void ThreadMarker::Unarchive
	(
	Archiver &arc
	)
   {
   Class::Unarchive( arc );

   arc.ReadInteger( &linenumber );
   arc.ReadBoolean( &doneProcessing );
   arc.ReadFloat( &waitUntil );
   arc.ReadString( &waitingFor );
   arc.ReadObjectPointer( ( Class ** )&waitingForThread );
   arc.ReadString( &waitingForConsole );
   arc.ReadString( &waitingForVariable );
   arc.ReadString( &waitingForDeath );
   arc.ReadBoolean( &waitingForPlayer );
   arc.ReadInteger( &waitingNumObjects );
   arc.ReadObject( &scriptmarker );
   }


class EXPORT_FROM_DLL ScriptMaster : public Listener
	{
	protected:
		ScriptThread					*currentThread;
		Container<ScriptThread *>	Threads;

		int								threadIndex;
      qboolean                   player_ready;

	public:
      CLASS_PROTOTYPE( ScriptMaster );

											ScriptMaster();
											~ScriptMaster();
		void								CloseScript( void );
		qboolean							NotifyOtherThreads( int num );
		void								KillThreads( void );
		qboolean							KillThread( int num );
		qboolean							RemoveThread( int num );
		ScriptThread					*CurrentThread( void );
		void								SetCurrentThread( ScriptThread *thread );
      ScriptThread               *CreateThread( GameScript *scr, const char *label, scripttype_t type = LEVEL_SCRIPT );
		ScriptThread					*CreateThread( const char *name, scripttype_t type, const char *label = NULL );
		ScriptThread					*GetThread( int num );
		ScriptVariableList			*GetVarGroup( const char *name );
		ScriptVariable					*GetExistingVariable( const char *name );
		ScriptVariable					*GetVariable( const char *name );
      void                       ConsoleInput( const char *name, const char *text );
      void                       ConsoleVariable( const char *name, const char *text );
      const char						*GetConsoleInput( const char *name );
      void                       DeathMessage( const char *name );
      void                       PlayerSpawned( void );
      qboolean                   PlayerReady( void );
      void                       PlayerNotReady( void );
      void                       CreateConsoleUser(const char *console_name, int user);
      qboolean                   Goto( GameScript * scr, const char *name );
      qboolean                   labelExists( GameScript * scr, const char *name );
      int                        GetUniqueThreadNumber( void );
      void                       FindLabels( void );
      virtual void               Archive( Archiver &arc );
      virtual void               Unarchive( Archiver &arc );
      
	};

inline EXPORT_FROM_DLL void ScriptMaster::Archive
	(
	Archiver &arc
	)
   {
   ScriptThread * ptr;
   int i, num;

   Listener::Archive( arc );

   arc.WriteObject( &levelVars );
   arc.WriteObject( &consoleVars );

   arc.WriteObjectPointer( currentThread );
   arc.WriteInteger( threadIndex );
   arc.WriteBoolean( player_ready );
   num = Threads.NumObjects();
   arc.WriteInteger( num );
   for ( i = 1; i <= num; i++ )
      {
      ptr = Threads.ObjectAt( i );
      arc.WriteObject( ptr );
      }
   }

inline EXPORT_FROM_DLL void ScriptMaster::Unarchive
	(
	Archiver &arc
	)
   {
   ScriptThread * ptr;
   int i, num;

   Listener::Unarchive( arc );

   arc.ReadObject( &levelVars );
   arc.ReadObject( &consoleVars );

   arc.ReadObjectPointer( ( Class ** )&currentThread );
   arc.ReadInteger( &threadIndex );
   arc.ReadBoolean( &player_ready );

   // make sure the list is cleared out
   Threads.FreeObjectList();
   // read in the the number of threads
   num = arc.ReadInteger();
   for ( i = 1; i <= num; i++ )
      {
      ptr = new ScriptThread;
      arc.ReadObject( ptr );
      Threads.AddObject( ptr );
      }
   }


extern ScriptMaster Director;

#endif /* scriptmaster.h */
