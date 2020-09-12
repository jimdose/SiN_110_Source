//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/listener.h                       $
// $Revision:: 31                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 5/19/99 11:30a                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/listener.h                            $
// 
// 31    5/19/99 11:30a Markd
// Added new camera support 
// 
// 30    10/26/98 4:27p Jimdose
// Sped up ValidEvent
// Added FindEvent( const char * )
// 
// 29    10/25/98 11:53p Jimdose
// added EXPORT_TEMPLATE
// 
// 28    10/18/98 8:45p Jimdose
// changed commandList to a str * container
// 
// 27    10/18/98 3:21a Jimdose
// made the assert in getName only fire if eventnum is non-zero
// 
// 26    10/17/98 11:33p Jimdose
// Added the event name to Event to help with debugging
// 
// 25    10/08/98 12:39a Jimdose
// Added event archiving functions
// 
// 24    9/25/98 4:41p Markd
// Changed Find functions to return an Event rather than a &Event, made the
// Exists function
// 
// 23    9/24/98 1:45a Jimdose
// Made Event a subclass of Class
// 
// 22    9/19/98 4:33p Jimdose
// Added ListCommands and EV_HIDE
// 
// 21    9/02/98 7:48p Aldie
// Moved template around
// 
// 20    8/27/98 9:04p Jimdose
// Moved a lot of small functions to the header as inline
// 
// 19    8/01/98 7:58p Jimdose
// Fixed bug with cheats in dm
// 
// 18    7/31/98 8:10p Jimdose
// Script commands now include flags to indicate cheats and console commands
// 
// 17    7/31/98 4:19p Jimdose
// Added DepthOfEvent
// 
// 16    7/20/98 5:08p Jimdose
// Added ProcessPendingEvents
// 
// 15    7/10/98 10:00p Jimdose
// Made remove script command post remove event so that it doesn't cause
// problems during event callbacks which trigger the script
// 
// 14    6/30/98 6:05p Jimdose
// Added IsVectorAt, IsEntityAt, and IsNumericAt for doing type checking on
// args
// Changed format for storing vectors to make it easy to identify
// 
// 13    6/27/98 9:18p Jimdose
// Made lookup for event responses for faster processing
// 
// 12    6/18/98 8:48p Jimdose
// Added better event error handling
// Added source info to events
// 
// 11    5/24/98 8:46p Jimdose
// Made a lot of functions more str-friendly.
// Got rid of a lot of char * based strings
// Cleaned up get spawn arg functions and sound functions
// sound functions now use consistant syntax
// 
// 10    5/24/98 4:48p Jimdose
// Made char *'s const
// 
// 9     5/24/98 1:06a Jimdose
// added const to various char *s
// 
// 8     5/08/98 2:51p Jimdose
// Moved archiving functions up to Class
// 
// 7     5/07/98 10:42p Jimdose
// Added archive and unarchive
// 
// 6     4/30/98 9:24p Jimdose
// Changed use of string to str class
// 
// 5     4/02/98 4:47p Jimdose
// Added initCommandList
// 
// 4     3/24/98 5:03p Jimdose
// Changed order of prototypes
// 
// 3     3/23/98 1:33p Jimdose
// Revamped event and command system
// 
// 2     3/04/98 1:01p Jimdose
// Created file
//
// DESCRIPTION:
// 

#include "g_local.h"
#include "class.h"
#include "container.h"

#ifndef __LISTENER_H__
#define __LISTENER_H__

class Entity;
class ScriptVariable;

typedef enum
	{
	EV_FROM_CODE,
	EV_FROM_CONSOLE,
	EV_FROM_SCRIPT
	} eventsource_t;

// Event flags
#define EV_CONSOLE	1								// Allow entry from console
#define EV_CHEAT		2								// Only allow entry from console if cheats are enabled
#define EV_HIDE		4								// Hide from eventlist

#define MAX_EVENT_USE	( ( 1 << 8 ) - 1 )

class ScriptThread;
class Archiver;

#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL Container<str *>;
#endif

class EXPORT_FROM_DLL Event : public Class
	{
	private:
		typedef struct EventInfo
			{
			unsigned			inuse			: 8;		// must change MAX_EVENT_USE to reflect maximum number stored here
			unsigned			source		: 2;
			unsigned			flags			: 2;
			unsigned			linenumber	: 20;		// linenumber does double duty in the case of the console commands
			};

		int					eventnum;
		EventInfo			info;
      const char        *name;
		Container<str>		*data;
		int					threadnum;

								Event( int num );
		static void			initCommandList( void );

		friend class		Listener;

		friend void	EXPORT_FROM_DLL G_ProcessPendingEvents( void );
		friend void EXPORT_FROM_DLL G_ClearEventList( void );
		friend void EXPORT_FROM_DLL G_InitEvents( void );
      friend void EXPORT_FROM_DLL G_ArchiveEvents( Archiver &arc );
      friend void EXPORT_FROM_DLL G_UnarchiveEvents( Archiver &arc );

		static Container<str *>	*Event::commandList;
		static Container<int>	*Event::flagList;
		static Container<int>	*Event::sortedList;
		static qboolean			Event::dirtylist;

		static int			compareEvents( const void *arg1, const void *arg2 );
		static void			SortEventList( void );
		static int			FindEvent( const char *name );
		static int			FindEvent( str &name );

	public:

		CLASS_PROTOTYPE( Event );

		static int			NumEventCommands( void );
		static void       ListCommands( const char *mask = NULL );

								Event();
								Event( Event &ev );
								Event( Event *ev );
								Event( const char *command, int flags = -1 );
								Event( str &command, int flags = -1 );
								~Event();

		str					getName( void );

		void					SetSource( eventsource_t source );
		void					SetLineNumber( int linenumber );
		void					SetConsoleEdict( edict_t *consoleedict );
		void					SetThread( ScriptThread *thread );

		eventsource_t		GetSource( void );
		ScriptThread		*GetThread( void );
		edict_t				*GetConsoleEdict( void );
		int					GetLineNumber( void );

		void					Error( const char *fmt, ... );

		static Event		Find( const char *command );
		static qboolean	Exists( const char *command );
		static Event		Find( str &command );
		
		Event&				printInfo(void);
		
		operator				int();
		operator				const char *();

		int					NumArgs( void );

		qboolean				IsVectorAt( int pos );
		qboolean				IsEntityAt( int pos );
		qboolean				IsNumericAt( int pos );

		const char			*GetToken( int pos );
		const char			*GetString( int pos );
		int					GetInteger( int pos );
		double				GetDouble( int pos );
		float					GetFloat( int pos );
		Vector				GetVector( int pos );
		Entity				*GetEntity( int pos );
		ScriptVariable		*GetVariable( int pos );

		void					AddToken( const char *text );
		void					AddTokens( int argc, const char **argv );
		void					AddString( const char *text );
		void					AddString( str &text );
		void					AddInteger( int val );
		void					AddDouble( double val );
		void					AddFloat( float val );
		void					AddVector( Vector &vec );
		void					AddEntity( Entity *ent );

      virtual void      Archive( Archiver &arc );
      virtual void      Unarchive( Archiver &arc );
	};

extern Event NullEvent;
extern Event EV_Remove;

#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL Container<Response>;
#endif

class Listener;

class EXPORT_FROM_DLL Listener : public Class
	{
	private:
		void							FloatVarEvent( Event *e );
		void							IntVarEvent( Event *e );
		void							StringVarEvent( Event *e );
		void							CharPtrVarEvent( Event *e );
		void							VectorVarEvent( Event *e );
		void							ScriptRemove( Event *e );

	protected:
		void							FloatVar( Event &e, float *var, float defaultvalue = 0 );
		void							IntVar( Event &e, int *var, float defaultvalue = 0 );
		void							StringVar( Event &e, str *var, const char *defaultvalue = "" );
		void							StringVar( Event &e, char **var, const char *defaultvalue = "" );
		void							VectorVar( Event &e, Vector *var, Vector defaultvalue = Vector( 0, 0, 0 ) );

		qboolean						CheckEventFlags( Event *event );

	public:
		CLASS_PROTOTYPE( Listener );

										~Listener();
		void							Remove( Event *e );
		qboolean						ValidEvent( Event &e );
		qboolean						ValidEvent( const char *name );
		qboolean						EventPending( Event &ev );
		qboolean						ProcessEvent( Event *event );
		qboolean						ProcessEvent( Event &event );
		void							PostEvent( Event *event, float time );
		void							PostEvent( Event &event, float time );
		qboolean						PostponeEvent( Event &event, float time );
		qboolean						PostponeEvent( Event *event, float time );
		void							CancelEventsOfType( Event *event );
		void							CancelEventsOfType( Event &event );
		void							CancelPendingEvents( void );
		qboolean						ProcessPendingEvents( void );
	};

inline EXPORT_FROM_DLL qboolean Event::Exists
	(
	const char *command
	)

	{
	int num;
	str c;

	if ( !commandList )
		{
		initCommandList();
		}

	c = command;
	num = FindEvent( c );
	if ( num )
		{
      return true;
		}

	return false;
	}


inline EXPORT_FROM_DLL Event Event::Find
	(
	const char *command
	)

	{
	int num;
	str c;

	if ( !commandList )
		{
		initCommandList();
		}

	c = command;
	num = FindEvent( c );
	if ( num )
		{
		return Event( num );
		}

	return NullEvent;
	}

inline EXPORT_FROM_DLL Event Event::Find
	(
	str &command
	)

	{
	int num;

	if ( !commandList )
		{
		initCommandList();
		}

	num = FindEvent( command );
	if ( num )
		{
		return Event( num );
		}

	return NullEvent;
	}

inline EXPORT_FROM_DLL void Event::SetSource
	(
	eventsource_t source
	)

	{
	info.source = ( unsigned )source;
	}

inline EXPORT_FROM_DLL void Event::SetLineNumber
	(
	int linenumber
	)

	{
	info.linenumber = linenumber;
	}

inline EXPORT_FROM_DLL void Event::SetConsoleEdict
	(
	edict_t *consoleedict
	)

	{
	// linenumber does double duty in the case of the console commands
	if ( consoleedict )
		{
		info.linenumber = consoleedict->s.number;
		}
	else
		{
		// default to player 1
		info.linenumber = 1;
		}
	}

inline EXPORT_FROM_DLL eventsource_t Event::GetSource
	(
	void
	)

	{
	return ( eventsource_t )info.source;
	}

inline EXPORT_FROM_DLL edict_t *Event::GetConsoleEdict
	(
	void
	)

	{
	// linenumber does double duty in the case of the console commands
	if ( ( info.source != EV_FROM_CONSOLE ) || ( info.linenumber < 1 ) || ( info.linenumber > game.maxclients ) )
		{
		assert( NULL );

		// default to player 1 for release
		return &g_edicts[ 1 ];
		}

	return &g_edicts[ info.linenumber ];
	}

inline EXPORT_FROM_DLL int Event::GetLineNumber
	(
	void
	)

	{
	// linenumber does double duty in the case of the console commands
	if ( info.source == EV_FROM_SCRIPT )
		{
		return info.linenumber;
		}

	return 0;
	}

inline EXPORT_FROM_DLL str Event::getName
	(
	void
	)

	{
   assert( name || !eventnum );

   if ( !name )
		{
		return "NULL";
		}

   return name;
	}

inline EXPORT_FROM_DLL Event& Event::printInfo
	(
	void
	)

	{
	gi.dprintf( "event '%s' is number %d\n", getName().c_str(), eventnum );

	return *this;
	}

inline EXPORT_FROM_DLL Event::operator int()
	{
	return eventnum;
	}

inline EXPORT_FROM_DLL Event::operator const char *()
	{
	return getName().c_str();
	}

inline EXPORT_FROM_DLL int Event::NumArgs
	(
	void
	)

	{
	if ( !data )
		{
		return 0;
		}
		
	return ( data->NumObjects() );
	}

inline EXPORT_FROM_DLL void Event::AddToken
	(
	const char *text
	)

	{
	AddString( text );
	}

inline EXPORT_FROM_DLL void Event::AddTokens
	(
	int argc,
	const char **argv
	)

	{
	int i;

	for( i = 0; i < argc; i++ )
		{
		assert( argv[ i ] );
		AddString( argv[ i ] );
		}
	}

inline EXPORT_FROM_DLL void Event::AddString
	(
	const char *text
	)

	{
	if ( !data )
		{
		data = new Container<str>;
		data->Resize( 1 );
		}

	data->AddObject( str( text ) );
	}

inline EXPORT_FROM_DLL void Event::AddString
	(
	str &text
	)

	{
	if ( !data )
		{
		data = new Container<str>;
		data->Resize( 1 );
		}

	data->AddObject( text );
	}

inline EXPORT_FROM_DLL void Event::AddInteger
	(
	int val
	)

	{
	char text[ 128 ];

	sprintf( text, "%d", val );
	AddString( text );
	}

inline EXPORT_FROM_DLL void Event::AddDouble
	(
	double val
	)

	{
	char text[ 128 ];

	sprintf( text, "%f", val );
	AddString( text );
	}

inline EXPORT_FROM_DLL void Event::AddFloat
	(
	float val
	)

	{
	char text[ 128 ];

	sprintf( text, "%f", val );
	AddString( text );
	}

inline EXPORT_FROM_DLL void Event::AddVector
	(
	Vector &vec
	)

	{
	char text[ 128 ];

	sprintf( text, "(%f %f %f)", vec[ 0 ], vec[ 1 ], vec[ 2 ] );
	AddString( text );
	}

inline EXPORT_FROM_DLL const char *Event::GetToken
	(
	int pos
	)

	{
	if ( !data || ( pos < 1 ) || ( data->NumObjects() < pos ) )
		{
		Error( "Index %d out of range.", pos );
		return "";
		}

	return data->ObjectAt( pos ).c_str();
	}

inline EXPORT_FROM_DLL qboolean Listener::ProcessEvent
	(
	Event &event
	)

	{
	Event *ev;

	ev = new Event( event );
	return ProcessEvent( ev );
	}

inline EXPORT_FROM_DLL void Listener::PostEvent
	(
	Event &event,
	float time
	)

	{
	Event *ev;

	ev = new Event( event );
	PostEvent( ev, time );
	}

inline EXPORT_FROM_DLL qboolean Listener::PostponeEvent
	(
	Event *event,
	float time
	)
	
	{
	return PostponeEvent( *event, time );
	}

inline EXPORT_FROM_DLL void Listener::CancelEventsOfType
	(
	Event &event
	)

	{
	CancelEventsOfType( &event );
	}

#endif
