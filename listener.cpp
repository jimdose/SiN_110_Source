//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/listener.cpp                     $
// $Revision:: 48                                                             $
//   $Author:: Aldie                                                          $
//     $Date:: 3/26/99 6:26p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/listener.cpp                          $
// 
// 48    3/26/99 6:26p Aldie
// Fixed more CTF bugs, probably the last ones
// 
// 47    3/18/99 6:44p Aldie
// CancelPendingEvents when destructing
// 
// 46    3/17/99 4:00p Aldie
// CTF Update
// 
// 45    11/10/98 5:48p Jimdose
// Made SortEventList sort the list manually when TEMPLATE_EXPORT is not
// defined
// 
// 44    10/26/98 4:27p Jimdose
// Sped up ValidEvent
// Added FindEvent( const char * )
// 
// 43    10/24/98 3:25a Jimdose
// added g_watch for only displaying events from a specific object
// 
// 42    10/19/98 6:30p Jimdose
// increased g_eventlimit to 1500
// 
// 41    10/19/98 12:07a Jimdose
// made all code use fast checks for inheritance (no text lookups when
// possible)
// isSubclassOf no longer requires ::_classinfo()
// 
// 40    10/18/98 8:44p Jimdose
// Made commandList a Container of str * instead of str.  Fixes problem of name
// pointer in event being invalidated when commandList is resized
// 
// 39    10/18/98 3:22a Jimdose
// Added code for timing events
// 
// 38    10/17/98 11:33p Jimdose
// Added the event name to Event to help with debugging
// 
// 37    10/17/98 12:22a Jimdose
// upped g_eventlimit to 500
// 
// 36    10/16/98 7:19p Jimdose
// Added g_eventlimit
// G_ProcessPendingEvents now breaks out if the number of events executed
// during the call exceeds g_eventlimit.
// Removed g_response and old code from ProcessEvent
// 
// 35    10/16/98 1:53a Jimdose
// Added FL_DONTSAVE to entities, so events that belong to entities with this
// flag aren't archived
// 
// 34    10/10/98 1:28a Jimdose
// PostEvent kills any events posted during a loadgame
// 
// 33    10/07/98 11:52p Jimdose
// Wrote Event archiving functions
// 
// 32    9/24/98 1:46a Jimdose
// Made Event a subclass of Class
// 
// 31    9/19/98 4:32p Jimdose
// Added ListCommands
// 
// 30    8/27/98 9:03p Jimdose
// Moved a lot of small functions to the header as inline
// 
// 29    8/26/98 6:42p Jimdose
// Added more info when g_showevents is set
// 
// 28    8/20/98 4:42p Jimdose
// (Finally) added binary search for resolving event names
// 
// 27    8/17/98 4:29p Jimdose
// added event reporting with g_showevents cvar
// 
// 26    8/06/98 5:18p Jimdose
// Fixed check for default flags in Event constructor for str objects
// 
// 25    8/01/98 7:58p Jimdose
// Fixed bug with cheats in dm
// 
// 24    7/31/98 8:09p Jimdose
// Script commands now include flags to indicate cheats and console commands
// 
// 23    7/31/98 4:19p Jimdose
// Added DepthOfEvent
// 
// 22    7/20/98 5:09p Jimdose
// Added ProcessPendingEvents
// 
// 21    7/10/98 10:00p Jimdose
// Made remove script command post remove event so that it doesn't cause
// problems during event callbacks which trigger the script
// 
// 20    7/08/98 12:54p Jimdose
// Made error for vectors not including '(' ')' a developer 2 warning
// 
// 19    6/30/98 6:05p Jimdose
// Added IsVectorAt, IsEntityAt, and IsNumericAt for doing type checking on
// args
// Changed format for storing vectors to make it easy to identify
// 
// 18    6/27/98 9:18p Jimdose
// Made lookup for event responses for faster processing
// 
// 17    6/24/98 6:48p Jimdose
// Made entity number based commands use "*" prefix consistantly
// 
// 16    6/20/98 7:41p Jimdose
// Made GetEntity return NULL if the index is out of range
// 
// 15    6/18/98 8:47p Jimdose
// Added better event error handling
// Added source info to events
// Added checks for event still in use when processing events (prevents
// deleting events twice)
// 
// 14    6/17/98 3:03p Markd
// Changed NumArgs back to previous behavior
// 
// 13    6/10/98 7:53p Markd
// Made NumArgs behave correctly like argc
// 
// 12    5/24/98 8:46p Jimdose
// Made a lot of functions more str-friendly.
// Got rid of a lot of char * based strings
// Cleaned up get spawn arg functions and sound functions
// sound functions now use consistant syntax
// 
// 11    5/24/98 4:48p Jimdose
// Made char *'s const
// 
// 10    5/24/98 1:06a Jimdose
// added const to various char *s
// 
// 9     5/08/98 2:51p Jimdose
// Moved archiving functions up to Class
// 
// 8     5/07/98 10:42p Jimdose
// Added archive and unarchive
// 
// 7     4/30/98 9:24p Jimdose
// Changed use of string to str class
// 
// 6     4/06/98 5:44p Jimdose
// Added assertion for null entities in AddEntity.  In the release version, it
// "safely" treats null ents as entnum 0
// 
// 5     4/02/98 4:48p Jimdose
// Added initCommandList to ensure that NullEvent is always initialized first
// 
// 4     3/24/98 5:02p Jimdose
// Made GetToken return the exact string instead of resolving the value of
// variables
// PostponeEvent was not updating the position of the event in the list, which
// would cause a logjam of events that were following the event.
// 
// 3     3/23/98 1:31p Jimdose
// Revamped event and command system
// 
// 2     3/04/98 1:01p Jimdose
// Created file
//
// DESCRIPTION:
// 

#include "listener.h"
#include "scriptvariable.h"
#include "worldspawn.h"
#include "scriptmaster.h"

Event EV_Remove( "immediateremove" );
Event EV_ScriptRemove( "remove" );

typedef struct eventcache_s 
	{
	Listener *obj;
	Event		*event;
	float		time;

	struct eventcache_s *next;
	struct eventcache_s *prev;
	} eventcache_t;

#define MAX_EVENTS 2000

extern "C" 
	{
	eventcache_t	Events[ MAX_EVENTS ];
	int				numEvents = 0;
	cvar_t			*g_numevents;
	};

cvar_t *g_showevents;
cvar_t *g_eventlimit;
cvar_t *g_timeevents;
cvar_t *g_watch;

eventcache_t FreeEventHead;
eventcache_t *FreeEvents = &FreeEventHead;
eventcache_t EventQueueHead;
eventcache_t *EventQueue = &EventQueueHead;

Container<str *> *Event::commandList = NULL;
Container<int> *Event::flagList = NULL;
Container<int> *Event::sortedList = NULL;
qboolean Event::dirtylist = false;

Event NullEvent;

CLASS_DECLARATION( Class, Event, NULL );

ResponseDef Event::Responses[] =
	{
		{ NULL, NULL }
	};

EXPORT_FROM_DLL int Event::NumEventCommands
	(
	void
	)

	{
	if ( commandList )
		{
		// Add 1 since container gives the inclusive number of objects
		return commandList->NumObjects() + 1;
		}

	return 0;
	}

EXPORT_FROM_DLL int Event::compareEvents
	( 
	const void *arg1, 
	const void *arg2 
	)

	{
	int ev1;
	int ev2;

	ev1 = *( int * )arg1;
	ev2 = *( int * )arg2;

	return stricmp( commandList->ObjectAt( ev1 )->c_str(), commandList->ObjectAt( ev2 )->c_str() );
	}

EXPORT_FROM_DLL void Event::SortEventList
	(
	void
	)

	{
	dirtylist = false;

	if ( sortedList && commandList )
		{
#ifndef EXPORT_TEMPLATE
      qsort( ( void * )sortedList->AddressOfObjectAt( 1 ), 
         ( size_t )sortedList->NumObjects(), 
         sizeof( int ), compareEvents );
#else
		sortedList->Sort( compareEvents );
#endif
		}
	}

inline EXPORT_FROM_DLL int Event::FindEvent
	(
	const char *name
	)

	{
	int eventnum;
   int index;
	int l;
	int r;
	int diff;

   assert( name );
   if ( !name )
      {
      return 0;
      }

	if ( !commandList )
		{
		return 0;
		}

	if ( dirtylist )
		{
		SortEventList();
		}

   l = 1;
   r = sortedList->NumObjects();
   while( r >= l )
      {
      index = ( l + r ) >> 1;
		eventnum = sortedList->ObjectAt( index );
      diff = stricmp( name, commandList->ObjectAt( eventnum )->c_str() );
      if ( diff < 0 )
         {
         r = index - 1;
         }
      else if ( diff > 0 )
         {
         l = index + 1;
         }
      else
         {
         return eventnum;
         }
      }

   return 0;
	}

EXPORT_FROM_DLL int Event::FindEvent
	(
	str &name
	)

	{
   return FindEvent( name.c_str() );
	}

EXPORT_FROM_DLL void Event::ListCommands
	(
   const char *mask
	)

	{
   str name;
   int flags;
	int eventnum;
   int num;
	int i;
	int n;
   int l;
   int p;
   int hidden;
   str text;

	if ( !commandList )
		{
      gi.printf( "No events.\n" );
		return;
		}

	if ( dirtylist )
		{
		SortEventList();
		}

   l = 0;
   if ( mask )
      {
      l = strlen( mask );
      }

   hidden = 0;
   num = 0;
   n = sortedList->NumObjects();
   for( i = 1; i <= n; i++ )
      {
		eventnum = sortedList->ObjectAt( i );
      name = commandList->ObjectAt( eventnum )->c_str();
      flags = flagList->ObjectAt( eventnum );

      if ( flags & EV_HIDE )
         {
         hidden++;
         continue;
         }

      if ( mask && Q_strncasecmp( name.c_str(), mask, l ) )
         {
         continue;
         }

      num++;

      text = "   ";
      p = 0;
      if ( flags & EV_CONSOLE )
         {
         text[ p++ ] = '*';
         }
      if ( flags & EV_CHEAT )
         {
         text[ p++ ] = 'C';
         }

      gi.printf( "%4d : %s%s\n", eventnum, text.c_str(), name.c_str() );
      }

   gi.printf( "\n* = console command.\nC = cheat command.\n\n"
      "Printed %d of %d total commands.\n", num, n - hidden );

   if ( developer->value && hidden )
      {
      gi.printf( "Suppressed %d commands.\n", hidden );
      }
	}

EXPORT_FROM_DLL void Event::initCommandList
	(
	void
	)

	{
	int flags;
   str *n;

	flags = 0;
	commandList = new Container<str *>;

   n = new str( "NULL" );
	NullEvent.eventnum = commandList->AddObject( n );
	
	flagList = new Container<int>;
	flagList->AddObject( flags );

	sortedList = new Container<int>;
	sortedList->AddObject( NullEvent.eventnum );

	dirtylist = false;

	NullEvent.data = NULL;
	NullEvent.info.inuse = 0;
	NullEvent.info.source = EV_FROM_CODE;
	NullEvent.info.flags = 0;
	NullEvent.info.linenumber = 0;
	}

Event::Event()
	{
	info.inuse = 0;
	info.source = EV_FROM_CODE;
	info.flags = 0;
	info.linenumber = 0;
	threadnum = -1;
	eventnum = 0;
	data = NULL;
   name = NULL;
	}

Event::Event
	(
	int num
	)

	{
	if ( !commandList )
		{
		initCommandList();
		}

	assert( ( num > 0 ) && num <= commandList->NumObjects() );

   if ( ( num <= 0 ) || ( num > commandList->NumObjects() ) )
      {
      num = 0;
      name = NULL;
   	info.flags = 0;
      }
   else
      {
      name = commandList->ObjectAt( num )->c_str();
	   info.flags = flagList->ObjectAt( num );
      }
	
	eventnum = num;
	data = NULL;
	info.inuse = 0;
	info.source = EV_FROM_CODE;
	info.linenumber = 0;
	threadnum = -1;
	}

Event::Event
	(
	Event &ev
	)

	{
	int num;
	int i;

	eventnum = ( int )ev;
	assert( ( eventnum > 0 ) && eventnum <= commandList->NumObjects() );
	data = NULL;
	
   name = commandList->ObjectAt( eventnum )->c_str();
	info.inuse = 0;
	info.source = ev.info.source;
	info.flags = ev.info.flags;
	info.linenumber = ev.info.linenumber;
	threadnum = ev.threadnum;

	if ( ev.data )
		{
		num = ev.data->NumObjects();

		data = new Container<str>;
		data->Resize( num );

		for( i = 1; i <= num; i++ )
			{
			data->AddObject( ev.data->ObjectAt( i ) );
			}
		}
	}

Event::Event
	(
	Event *ev
	)

	{
	int num;
	int i;

   assert( ev );
   if ( !ev )
      {
      Class::error( "Event", "NULL Event\n" );
      }

	eventnum = ( int )*ev;
	assert( ( eventnum > 0 ) && eventnum <= commandList->NumObjects() );
	data = NULL;
   name = commandList->ObjectAt( eventnum )->c_str();
	info.inuse = 0;
	info.source = ev->info.source;
	info.flags = ev->info.flags;
	info.linenumber = ev->info.linenumber;
	threadnum = ev->threadnum;
	if ( ev->data )
		{
		num = ev->data->NumObjects();

		data = new Container<str>;
		data->Resize( num );

		for( i = 1; i <= num; i++ )
			{
			data->AddObject( ev->data->ObjectAt( i ) );
			}
		}
	}

Event::Event
	(
	const char *command,
	int flags
	)

	{
	str c;
   str *t;

	if ( !commandList )
		{
		initCommandList();
		}

	c = command;
	eventnum = FindEvent( c );
	if ( !eventnum )
		{
      t = new str( c );
		eventnum = commandList->AddObject( t );
		// check for default flags
		if ( flags == -1 )
			{
			flags = 0;
			}
		flagList->AddObject( ( int )flags );
		sortedList->AddObject( eventnum );
		dirtylist = true;
		}
   
   // Use the name stored in the command list in case the string passed in 
   // is not in static memory.
   name = commandList->ObjectAt( eventnum )->c_str();

	data = NULL;
	info.inuse = 0;
	info.source = EV_FROM_CODE;
	info.linenumber = 0;
	threadnum = -1;

	// If flags have changed, let the user know.  It's probably a development bug.
	int &flagobj = flagList->ObjectAt( eventnum );

	// check for default flags
	if ( flags == -1 )
		{
		flags = flagobj;
		}

	assert( flags == flagobj );
	if ( flags != flagobj )
		{
		// Flags not equal.  Use combined value.
		flagobj |= flags;
		}

	info.flags = flagobj;
	}

Event::Event
	(
	str &command,
	int flags
	)

	{
   str *t;

	if ( !commandList )
		{
		initCommandList();
		}

	eventnum = FindEvent( command );
	if ( !eventnum )
		{
      t = new str( command );
		eventnum = commandList->AddObject( t );
		// check for default flags
		if ( flags == -1 )
			{
			flags = 0;
			}
		flagList->AddObject( flags );
		sortedList->AddObject( eventnum );
		dirtylist = true;
		}

   // Use the name stored in the command list since the string passed in 
   // is not in static memory.
   name = commandList->ObjectAt( eventnum )->c_str();
   data = NULL;
	info.inuse = 0;
	info.source = EV_FROM_CODE;
	info.linenumber = 0;
	threadnum = -1;

	// If flags have changed, let the user know.  It's probably a development bug.
	int &flagobj = flagList->ObjectAt( eventnum );

	// check for default flags
	if ( flags == -1 )
		{
		flags = flagobj;
		}

	assert( flags == flagobj );
	if ( flags != flagobj )
		{
		// Flags not equal.  Use combined value.
		flagobj |= flags;
		}

	info.flags = flagobj;
	}

EXPORT_FROM_DLL Event::~Event()
	{
	if ( data )
		{
		delete data;
		data = NULL;
		}
	}

EXPORT_FROM_DLL void Event::SetThread
	(
	ScriptThread *thread
	)

	{
	if ( thread )
		{
		threadnum = thread->ThreadNum();
		}
	else
		{
		threadnum = -1;
		}
	}

EXPORT_FROM_DLL ScriptThread *Event::GetThread
	(
	void
	)

	{
	if ( threadnum != -1 )
		{
		return Director.GetThread( threadnum );
		}

	return NULL;
	}

EXPORT_FROM_DLL void Event::Error
	(
	const char *fmt,
	...
	)

	{
	va_list			argptr;
	char				text[ 1024 ];
	ScriptThread	*thread;
	const char		*filename;

	va_start( argptr, fmt );
	vsprintf( text, fmt, argptr );
	va_end( argptr );

	switch( GetSource() )
		{
		default :
		case EV_FROM_CODE :
			gi.dprintf( "Game: '%s' : %s\n", getName().c_str(), text );
			break;

		case EV_FROM_SCRIPT :
			thread = GetThread();
			filename = "Dead script";
			if ( thread )
				{
				filename = thread->Filename();
				}
			gi.dprintf( "%s(%d): '%s' :\n%s\n", filename, info.linenumber, getName().c_str(), text );
			break;

		case EV_FROM_CONSOLE :
			gi.cprintf( GetConsoleEdict(), PRINT_HIGH, "Console: '%s' : %s\n", getName().c_str(), text );
			break;
		}
	}

EXPORT_FROM_DLL void Event::AddEntity
	(
	Entity *ent
	)

	{
	char text[ 128 ];

	//assert( ent );
	if ( !ent )
		{
		sprintf( text, "*0" );
		}
	else
		{
		sprintf( text, "*%d", ent->entnum );
		}
	AddString( text );
	}

EXPORT_FROM_DLL qboolean Event::IsVectorAt
	(
	int pos
	)

	{
	const char *text;
	ScriptVariable *var;

	if ( !data || ( pos < 1 ) || ( data->NumObjects() < pos ) )
		{
		Error( "Index %d out of range.", pos );
		return false;
		}

	text = data->ObjectAt( pos ).c_str();
	assert( text );

	var = Director.GetExistingVariable( text );
	if ( var )
		{
		text = var->stringValue();
		}

	if ( text[ 0 ] == '(' )
		{
		// probably a vector, so say that it is
		return true;
		}
	
	// not a vector
	return false;
	}

EXPORT_FROM_DLL qboolean Event::IsEntityAt
	(
	int pos
	)

	{
	const char		*name;
	int				t;
	ScriptVariable *var;

	if ( !data || ( pos < 1 ) || ( data->NumObjects() < pos ) )
		{
		Error( "Index %d out of range.", pos );
		return false;
		}

	name = data->ObjectAt( pos ).c_str();
	assert( name );

	var = Director.GetExistingVariable( name );
	if ( var )
		{
		name = var->stringValue();
		}

	if ( name[ 0 ] == '$' )
		{
		t = G_FindTarget( 0, &name[ 1 ] );
		if ( !t )
			{
			Error( "Entity with targetname of '%s' not found", &name[ 1 ] );

			return false;
			}
		}
	else
		{
		if ( name[ 0 ] != '*' )
			{
			Error( "Expecting a '*'-prefixed entity number but found '%s'.", name );

			return false;
			}
			
		if ( !IsNumeric( &name[ 1 ] ) )
			{
			Error( "Expecting a numeric value but found '%s'.", &name[ 1 ] );

			return false;
			}
		else
			{
			t = atoi( &name[ 1 ] );
			}
		}

	if ( ( t < 0 ) || ( t > game.maxentities ) )
		{
		Error( "%d out of valid range for entity.", t );
		return false;
		}

	// only return true if the entity exists
	return ( G_GetEntity( t ) != NULL );
	}

EXPORT_FROM_DLL qboolean Event::IsNumericAt
	(
	int pos
	)

	{
	const char *text;
	ScriptVariable *var;

	if ( !data || ( pos < 1 ) || ( data->NumObjects() < pos ) )
		{
		Error( "Index %d out of range.", pos );
		return false;
		}

	text = data->ObjectAt( pos ).c_str();
	assert( text );

	var = Director.GetExistingVariable( text );
	if ( var )
		{
		text = var->stringValue();
		}

	return IsNumeric( text );
	}

EXPORT_FROM_DLL const char *Event::GetString
	(
	int pos
	)

	{
	const char *text;
	ScriptVariable *var;

	if ( !data || ( pos < 1 ) || ( data->NumObjects() < pos ) )
		{
		Error( "Index %d out of range.", pos );
		return "";
		}

	text = data->ObjectAt( pos ).c_str();
	assert( text );

	var = Director.GetExistingVariable( text );
	if ( var )
		{
		return var->stringValue();
		}
	return text;
	}

EXPORT_FROM_DLL int Event::GetInteger
	(
	int pos
	)

	{
	const char *text;
	ScriptVariable *var;

	if ( !data || ( pos < 1 ) || ( data->NumObjects() < pos ) )
		{
		Error( "Index %d out of range.", pos );
		return 0;
		}

	text = data->ObjectAt( pos ).c_str();
	assert( text );

	var = Director.GetExistingVariable( text );
	if ( var )
		{
		if ( !IsNumeric( var->stringValue() ) )
			{
			Error( "Variable %s contains non-numeric value '%s'", text, var->stringValue() );
			}
		return var->intValue();
		}

	if ( !IsNumeric( text ) )
		{
		Error( "Expecting a numeric value but found '%s'.", text );
		return 0;
		}

	return atoi( text );
	}

EXPORT_FROM_DLL double Event::GetDouble
	(
	int pos
	)

	{
	const char *text;
	ScriptVariable *var;

	if ( !data || ( pos < 1 ) || ( data->NumObjects() < pos ) )
		{
		Error( "Index %d out of range.", pos );
		return 0;
		}

	text = data->ObjectAt( pos ).c_str();
	assert( text );

	var = Director.GetExistingVariable( text );
	if ( var )
		{
		if ( !IsNumeric( var->stringValue() ) )
			{
			Error( "Variable %s contains non-numeric value '%s'", text, var->stringValue() );
			}
		return ( double )var->floatValue();
		}
	
	if ( !IsNumeric( text ) )
		{
		Error( "Expecting a numeric value but found '%s'.", text );
		return 0;
		}

	return ( double )atof( text );
	}

EXPORT_FROM_DLL float Event::GetFloat
	(
	int pos
	)

	{
	const char *text;
	ScriptVariable *var;

	if ( !data || ( pos < 1 ) || ( data->NumObjects() < pos ) )
		{
		Error( "Index %d out of range.", pos );
		return 0;
		}

	text = data->ObjectAt( pos ).c_str();
	assert( text );

	var = Director.GetExistingVariable( text );
	if ( var )
		{
		if ( !IsNumeric( var->stringValue() ) )
			{
			Error( "Variable %s contains non-numeric value '%s'", text, var->stringValue() );
			}
		return var->floatValue();
		}
	
	if ( !IsNumeric( text ) )
		{
		Error( "Expecting a numeric value but found '%s'.", text );
		return 0;
		}

	return atof( text );
	}

EXPORT_FROM_DLL Vector Event::GetVector
	(
	int pos
	)

	{
	const char *text;
	ScriptVariable *var;

	if ( !data || ( pos < 1 ) || ( data->NumObjects() < pos ) )
		{
		Error( "Index %d out of range.", pos );
		return vec_zero;
		}

	text = data->ObjectAt( pos ).c_str();
	assert( text );

	var = Director.GetExistingVariable( text );
	if ( var )
		{
		text = var->stringValue();
		}

	// Check if this is a ()-based vector
	// we accept both, but using parenthesis we can determine if it is a vector or not
	if ( text[ 0 ] == '(' )
		{
		return Vector( &text[ 1 ] );
		}
	
	// give an error, but try converting it anyways
	if ( developer->value > 1 )
		{
		Error( "Vector '%s' does not include '(' ')'.", text );
		}
	return Vector( text );
	}

EXPORT_FROM_DLL Entity *Event::GetEntity
	(
	int pos
	)

	{
	const char		*name;
	int				t;
	ScriptVariable *var;

	if ( !data || ( pos < 1 ) || ( data->NumObjects() < pos ) )
		{
		Error( "Index %d out of range.", pos );
		return NULL;
		}

	name = data->ObjectAt( pos ).c_str();
	assert( name );

	var = Director.GetExistingVariable( name );
	if ( var )
		{
		name = var->stringValue();
		}

	if ( name[ 0 ] == '$' )
		{
		t = G_FindTarget( 0, &name[ 1 ] );
		if ( !t )
			{
			Error( "Entity with targetname of '%s' not found", &name[ 1 ] );

			return NULL;
			}
		}
	else
		{
		if ( name[ 0 ] != '*' )
			{
			Error( "Expecting a '*'-prefixed entity number but found '%s'.", name );

			return NULL;
			}
			
		if ( !IsNumeric( &name[ 1 ] ) )
			{
			Error( "Expecting a numeric value but found '%s'.", &name[ 1 ] );

			return NULL;
			}
		else
			{
			t = atoi( &name[ 1 ] );
			}
		}

	if ( ( t < 0 ) || ( t > game.maxentities ) )
		{
		Error( "%d out of valid range for entity.", t );
		return NULL;
		}

	return G_GetEntity( t );
	}

EXPORT_FROM_DLL ScriptVariable *Event::GetVariable
	(
	int pos
	)

	{
	if ( !data || ( pos < 1 ) || ( data->NumObjects() < pos ) )
		{
		Error( "Index %d out of range.", pos );
		return NULL;
		}

	return Director.GetVariable( data->ObjectAt( pos ).c_str() );
	}

EXPORT_FROM_DLL void Event::Archive
   (
   Archiver &arc
   )

   {
   str name;
   int num;
   int i;

   name = getName();
   arc.WriteString( name );

   arc.WriteRaw( &info, sizeof( info ) );
   arc.WriteInteger( threadnum );

   if ( !data )
      {
      arc.WriteInteger( 0 );
      }
   else
      {
      num = data->NumObjects();

      arc.WriteInteger( num );
      for( i = 1; i <= num; i++ )
         {
         arc.WriteString( data->ObjectAt( i ) );
         }
      }
	}

EXPORT_FROM_DLL void Event::Unarchive
   (
   Archiver &arc
   )

   {
   Event ev;
   str name;
   int i;
   int num;

	if ( data )
		{
      delete data;
      data = NULL;
      }

   arc.ReadString( &name );
   *this = Event( name );

   arc.ReadRaw( &info, sizeof( info ) );
   arc.ReadInteger( &threadnum );

   arc.ReadInteger( &num );
   if ( num )
      {
	   data = new Container<str>;
	   data->Resize( num );
      for( i = 1; i <= num; i++ )
         {
         arc.ReadString( &name );
   	   data->AddObject( name );
         }
      }
   }

CLASS_DECLARATION( Class, Listener, NULL );

ResponseDef Listener::Responses[] =
	{
	   { &EV_Remove,				( Response )Listener::Remove },
		{ &EV_ScriptRemove,		( Response )Listener::ScriptRemove },
		{ NULL, NULL }
	};

EXPORT_FROM_DLL void Listener::Remove
	(
	Event *e
	)

	{
   this->CancelPendingEvents();
	delete this;
	}

EXPORT_FROM_DLL void Listener::ScriptRemove
	(
	Event *e
	)

	{
	// Forces the remove to be done at a safe time
	PostEvent( EV_Remove, 0 );
	}

#if 0
EXPORT_FROM_DLL void Listener::FloatVar
	(
	Event &e,
	float *var,
	float defaultvalue
	)

	{
	}

EXPORT_FROM_DLL void Listener::IntVar
	(
	Event &e,
	int *var,
	float defaultvalue
	)

	{
	}

EXPORT_FROM_DLL void Listener::StringVar
	(
	Event &e,
	str *var,
	const char *defaultvalue
	)

	{
	}

EXPORT_FROM_DLL void Listener::StringVar
	(
	Event &e,
	char **var,
	const char *defaultvalue
	)

	{
	}

EXPORT_FROM_DLL void Listener::VectorVar
	(
	Event &e,
	Vector *var,
	Vector defaultvalue
	)

	{
	}
#endif

EXPORT_FROM_DLL qboolean Listener::ValidEvent
	(
	Event &e
	)

	{
	ClassDef	*c;
	int		ev;

	ev = ( int )e;

	c = this->classinfo();
   assert( ( ev >= 0 ) && ( ev < c->numEvents ) );
	if ( ( ev < 0 ) || ( ev >= c->numEvents ) )
		{
      warning( "ValidEvent", "Event '%s' out of response range for class '%s'.  "
         "Event probably invalid or allocated late.\n", e.getName().c_str(), getClassname() );
		return false;
		}

	return ( c->responseLookup[ ev ] != NULL );
   }

EXPORT_FROM_DLL qboolean Listener::ValidEvent
	(
	const char *name
	)

	{
	ClassDef	*c;
	int		ev;

   ev = Event::FindEvent( name );

	c = this->classinfo();
   assert( ( ev >= 0 ) && ( ev < c->numEvents ) );
	if ( ( ev < 0 ) || ( ev >= c->numEvents ) )
		{
      warning( "ValidEvent", "Event '%s' out of response range for class '%s'.  "
         "Event probably invalid or allocated late.\n", name, getClassname() );
		return false;
		}

	return ( c->responseLookup[ ev ] != NULL );
	}

EXPORT_FROM_DLL qboolean Listener::EventPending
	( 
	Event &ev
	)

	{
	eventcache_t *event;
	int eventnum;

	assert( EventQueue );
	assert( EventQueue->next );

	event = EventQueue->next;

	eventnum = ( int )ev;
	while( event != EventQueue )
		{
		if ( ( event->obj == this ) && ( (int)*event->event == eventnum ) )
			{
			return true;
			}
		event = event->next;
		}

	return false;
   }

EXPORT_FROM_DLL inline qboolean Listener::CheckEventFlags
	(
	Event *event
	)

	{
	// Special handling of console events
	if ( event->GetSource() == EV_FROM_CONSOLE )
		{
		if ( !( event->info.flags & (EV_CONSOLE|EV_CHEAT) ) )
			{
			if ( isSubclassOf( Entity ) )
				{
				Entity *ent;

				ent = ( Entity * )this;
				gi.cprintf( ent->edict, PRINT_HIGH, "Command not available from console.\n" );
				}

			// don't process
			return false;
			}

		// don't allow console cheats during deathmatch unless the server says it's ok.
		if ( ( event->info.flags & EV_CHEAT ) && deathmatch->value && !sv_cheats->value )
			{
			if ( isSubclassOf( Entity ) )
				{
				Entity *ent;

				ent = ( Entity * )this;
				gi.cprintf( ent->edict, PRINT_HIGH, "You must run the server with '+set cheats 1' to enable this command.\n" );
				}

			// don't process
			return false;
			}
		}

	// ok to process
	return true;
	}

EXPORT_FROM_DLL qboolean Listener::ProcessEvent
	(
	Event *event
	)

	{
	ClassDef *c;
	int		ev;
	int		i;

	// Prevent overflow of the inuse count
	if ( event->info.inuse >= MAX_EVENT_USE )
		{
		gi.error( "ProcessEvent : Event usage overflow on '%s' event.  Possible infinite loop.\n", event->getName().c_str() );
		}

	if ( g_showevents->value )
		{
		int n;
		str text;

		text = va( "%.1f: %s", level.time, this->getClassname() );
		if ( isSubclassOf( Entity ) )
			{
			text += va( " (*%d) ", ( ( Entity * )this )->entnum );
			if ( ( ( Entity * )this )->Targeted() )
				{
				text += va( "'%s'", ( ( Entity * )this )->TargetName() );
				}
			}
		else if ( isSubclassOf( ScriptThread ) )
			{
			text += va( " #%d:'%s'", ( ( ScriptThread * )this )->ThreadNum(), ( ( ScriptThread * )this )->ThreadName() );
			}
		else if ( isSubclassOf( ScriptVariable ) )
			{
			text += va( " '%s'", ( ( ScriptVariable * )this )->getName() );
			}

		switch( event->GetSource() )
			{
			default :
			case EV_FROM_CODE :
				text += " : Code :";
				break;

			case EV_FROM_SCRIPT :
				assert( event->GetThread() );
				text += va( " : %s(%d) :", event->GetThread()->Filename(), event->info.linenumber );
				break;

			case EV_FROM_CONSOLE :
				text += " : Console :";
				break;
			}

		text += event->getName().c_str();
		n = event->NumArgs();
		for( i = 1; i <= n; i++ )
			{
			text += va( " %s", event->GetToken( i ) );
			}

		text += "\n";

      if ( !g_watch->value || ( isSubclassOf( Entity ) && ( g_watch->value == ( ( Entity * )this )->entnum ) ) )
         {
         if ( g_showevents->value == 2 )
			   {
			   G_DebugPrintf( text.c_str() );
			   }
		   else
			   {
			   gi.dprintf( "%s", text.c_str() );
			   }
         }
		}

	ev = ( int )*event;
	c = this->classinfo();
	if ( ev >= c->numEvents	)
		{
      event->Error( "Event out of response range for class '%s'.  Event probably invalid or allocated late.\n", getClassname() );
		return false;
		}

	if ( c->responseLookup[ ev ] )
		{
      int start;
      int end;

		event->info.inuse++;

      if ( !g_timeevents->value )
         {
         // only process the event if we allow it
		   if ( CheckEventFlags( event ) )
			   {
			   ( this->**c->responseLookup[ ev ] )( event );
			   }
         }
      else
         {
         start = G_Milliseconds();

		   // only process the event if we allow it
		   if ( CheckEventFlags( event ) )
			   {
			   ( this->**c->responseLookup[ ev ] )( event );
			   }

         end = G_Milliseconds();
         if ( g_timeevents->value == 1 )
            {
            gi.printf( "'%s' : %d\n", event->getName().c_str(), end - start );
            }
         else
            {
            G_DebugPrintf( "'%s' : %d\n", event->getName().c_str(), end - start );
            }
         }

		// Prevent an event from being freed twice, in case it's been re-used 
		event->info.inuse--;
		if ( !event->info.inuse )
			{
			delete event;
			}

      return true;
		}

   if ( !event->info.inuse )
		{
		delete event;
		}

	return false;
	}

EXPORT_FROM_DLL void Listener::PostEvent
	(
	Event *ev,
	float time
	)

	{
	eventcache_t *newevent;
	eventcache_t *event;

   if ( LoadingSavegame )
      {
		if ( !ev->info.inuse )
			{
			delete ev;
			}

      return;
      }

	if ( LL_Empty( FreeEvents, next, prev ) )
		{
		gi.error( "PostEvent : No more free events on '%s' event.\n", ev->getName().c_str() );
		return;
		}

	newevent = FreeEvents->next;
	LL_Remove( newevent, next, prev );

	// Probably don't have this many events, but it's a good safety precaution
	if ( ev->info.inuse >= MAX_EVENT_USE )
		{
		gi.error( "PostEvent : Event usage overflow on '%s' event.  Possible infinite loop.\n", ev->getName().c_str() );
		return;
		}

	ev->info.inuse++;

	newevent->obj		= this;
	newevent->event	= ev;
	newevent->time		= level.time + time;

	event = EventQueue->next;
	while( ( event != EventQueue ) && ( newevent->time >= event->time ) )
		{
		event = event->next;
		}

	LL_Add( event, newevent, next, prev );
	numEvents++;
	}

EXPORT_FROM_DLL qboolean Listener::PostponeEvent
	(
	Event &ev,
	float time
	)
	
	{
	eventcache_t *event;
	eventcache_t *node;
	int eventnum;

	assert( EventQueue );
	assert( EventQueue->next );

	eventnum = ( int )ev;

	event = EventQueue->next;
	while( event != EventQueue )
		{
		if ( ( event->obj == this ) && ( ( int )*event->event == eventnum ) )
			{
			event->time	+= time;

			node = event->next;
			while( ( node != EventQueue ) && ( event->time >= node->time ) )
				{
				node = node->next;
				}

			LL_Remove( event, next, prev );
			LL_Add( node, event, next, prev );
			
			return true;
			}
		event = event->next;
		}

	return false;
	}

EXPORT_FROM_DLL void Listener::CancelEventsOfType
	(
	Event *ev
	)

	{
	eventcache_t *event;
	eventcache_t *next;
	int eventnum;

	assert( EventQueue );
	assert( EventQueue->next );

	event = EventQueue->next;

	eventnum = (int)*ev;
	while( event != EventQueue )
		{
		next = event->next;
		if ( ( event->obj == this ) && ( (int)*event->event == eventnum ) )
			{
			delete event->event;
			event->event = NULL;
			LL_Remove( event, next, prev );
			LL_Add( FreeEvents, event, next, prev );
			numEvents--;
			}
		event = next;
		}
	}

EXPORT_FROM_DLL void Listener::CancelPendingEvents
	(
	void
	)

	{
	eventcache_t *event;
	eventcache_t *next;

	assert( EventQueue );
	assert( EventQueue->next );

	event = EventQueue->next;

	while( event != EventQueue )
		{
		next = event->next;
		if ( event->obj == this )
			{
			delete event->event;
			event->event = NULL;
			LL_Remove( event, next, prev );
			LL_Add( FreeEvents, event, next, prev );
			numEvents--;
			}
		event = next;
		}
	}

EXPORT_FROM_DLL qboolean Listener::ProcessPendingEvents
	( 
	void
	)

	{
	eventcache_t *event;
	qboolean processedEvents;
	float t;

	assert( EventQueue );
	assert( EventQueue->next );
	assert( EventQueue->prev );

	processedEvents = false;

	t = level.time + 0.001;

	event = EventQueue->next;
	while( event != EventQueue )
		{
		assert( event );
		assert( event->event );
		assert( event->obj );

		if ( event->time > t )
			{
			break;
			}

		if ( event->obj != this )
			{
			// traverse normally
			event = event->next;
			}
		else
			{
			LL_Remove( event, next, prev );
			numEvents--;

			assert( event->obj );

			// ProcessEvent increments the inuse count, so decrement it since we've already incremented it in PostEvent
			event->event->info.inuse--;

			event->obj->ProcessEvent( event->event );

			event->event = NULL;
			LL_Add( FreeEvents, event, next, prev );

			// start over, since can't guarantee that we didn't process any previous or following events
			event = EventQueue->next;

			processedEvents = true;
			}
		}

	return processedEvents;
   }

EXPORT_FROM_DLL Listener::~Listener()
	{
	CancelPendingEvents();
	}

EXPORT_FROM_DLL void G_ClearEventList
	(
	void
	)

	{
	int i;
	eventcache_t *e;

	LL_Reset( FreeEvents, next, prev );
	LL_Reset( EventQueue, next, prev );
	memset( Events, 0, sizeof( Events ) );

	for( e = &Events[ 0 ], i = 0; i < MAX_EVENTS; i++, e++ )
		{
		LL_Add( FreeEvents, e, next, prev );
		}

	numEvents = 0;
	}

EXPORT_FROM_DLL void G_ProcessPendingEvents
	(
	void
	)

	{
	eventcache_t *event;
	float t;
   int num;
   int maxevents;

	assert( EventQueue );
	assert( EventQueue->next );
	assert( EventQueue->prev );

   maxevents = ( int )g_eventlimit->value;

   num = 0;
	t = level.time + 0.001;
	while( !LL_Empty( EventQueue, next, prev ) )
		{
		event = EventQueue->next;

		assert( event );
		assert( event->event );
		assert( event->obj );

		if ( event->time > t )
			{
			break;
			}

		LL_Remove( event, next, prev );
		numEvents--;

		assert( event->obj );

		// ProcessEvent increments the inuse count, so decrement it since we've already incremented it in PostEvent
      assert( event->event->info.inuse > 0 );
		event->event->info.inuse--;

		event->obj->ProcessEvent( event->event );

		event->event = NULL;
		LL_Add( FreeEvents, event, next, prev );

      // Don't allow ourselves to stay in here too long.  An abnormally high number
      // of events being processed is evidence of an infinite loop of events.
      num++;
      if ( num > maxevents )
         {
         gi.printf( "Event overflow.  Possible infinite loop in script.  "
            "Enable g_showevents to trace.  Aborting frame.\n" );
         break;
         }
		}
	}

EXPORT_FROM_DLL void G_ArchiveEvents
	(
	Archiver &arc
	)

	{
	eventcache_t *event;
   int num;

	assert( EventQueue );
	assert( EventQueue->next );
	assert( EventQueue->prev );

   num = 0;
	for( event = EventQueue->next; event != EventQueue; event = event->next )
		{
		assert( event );
		assert( event->event );
		assert( event->obj );

      if ( event->obj->isSubclassOf( Entity ) &&
         ( ( ( Entity * )event->obj )->flags & FL_DONTSAVE ) )
         {
         continue;
         }

      num++;
		}

   arc.WriteInteger( num );
	for( event = EventQueue->next; event != EventQueue; event = event->next )
		{
		assert( event );
		assert( event->event );
		assert( event->obj );

      if ( event->obj->isSubclassOf( Entity ) &&
         ( ( ( Entity * )event->obj )->flags & FL_DONTSAVE ) )
         {
         continue;
         }

      arc.WriteObjectPointer( event->obj );
      arc.WriteEvent( *event->event );
      arc.WriteFloat( event->time );
		}
	}

EXPORT_FROM_DLL void G_UnarchiveEvents
	(
	Archiver &arc
	)

	{
	eventcache_t *e;
   int i;

   LL_Reset( FreeEvents, next, prev );
	LL_Reset( EventQueue, next, prev );
	memset( Events, 0, sizeof( Events ) );

   arc.ReadInteger( &numEvents );
	for( e = &Events[ 0 ], i = 0; i < numEvents; i++, e++ )
		{
      arc.ReadObjectPointer( ( Class ** )&e->obj );
      e->event = new Event();
      arc.ReadEvent( e->event );
      arc.ReadFloat( &e->time );

      LL_Add( EventQueue, e, next, prev );
		}

   for( ; i < MAX_EVENTS; i++, e++ )
		{
		LL_Add( FreeEvents, e, next, prev );
		}
	}

EXPORT_FROM_DLL void G_InitEvents
	( 
	void 
	)

	{
	g_numevents = gi.cvar ( "g_numevents", "0", 0 );
	g_showevents = gi.cvar ( "g_showevents", "0", 0 );
   g_eventlimit = gi.cvar ( "g_eventlimit", "1500", 0 );
   g_timeevents = gi.cvar ( "g_timeevents", "0", 0 );
   g_watch = gi.cvar ( "g_watch", "0", 0 );

	BuildEventResponses();	
	G_ClearEventList();

	// Sort the list before we go on since we won't be adding any more events
	Event::SortEventList();
	}
