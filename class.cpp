//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/class.cpp                        $
// $Revision:: 20                                                             $
//   $Author:: Jimdose                                                        $
//     $Date:: 10/19/98 12:07a                                                $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/class.cpp                             $
// 
// 20    10/19/98 12:07a Jimdose
// made all code use fast checks for inheritance (no text lookups when
// possible)
// isSubclassOf no longer requires ::_classinfo()
// 
// 19    10/07/98 11:42p Jimdose
// Got savegames working
// 
// 18    9/24/98 1:49a Jimdose
// Added DisplayMemoryUsage
// 
// 17    9/21/98 2:15a Jimdose
// Moved non-type specific code in SafePtr to SafePtrBase to help with save
// games
// 
// 16    8/27/98 9:04p Jimdose
// NumEventCommands is now a member of Event
// 
// 15    6/27/98 9:18p Jimdose
// Made lookup for event responses for faster processing
// 
// 14    6/15/98 9:09p Aldie
// Fixed checkInheritance printfs
// 
// 13    5/24/98 4:48p Jimdose
// Made char *'s const
// 
// 12    5/11/98 8:06p Jimdose
// Added SafePtr
// 
// 11    5/08/98 2:51p Jimdose
// Added archiving functions
// 
// 10    3/27/98 6:35p Jimdose
// made checking of classnames case independant
// 
// 9     3/23/98 1:31p Jimdose
// Revamped event and command system
// 
// 8     3/04/98 1:49p Jimdose
// Changed overloaded delete so that it used delete[] instead of delete, since
// we allocate with new[];
// 
// 7     3/02/98 8:49p Jimdose
// Changed the classid parameter of CLASS_DECLARATION to a quoted string so
// that you could have a NULL classid.
// 
// 6     2/03/98 10:53a Jimdose
// Updated to work with Quake 2 engine
// Made class registration automatic
// 
// 5     1/22/98 6:50p Jimdose
// Made Q2 compatible
// 
// 3     10/27/97 3:40p Jimdose
// Included stdarg.h
// 
// 2     9/26/97 6:13p Jimdose
// Added standard Ritual headers
//
// DESCRIPTION:
// Base class that all classes that are used in conjunction with Sin should
// be based off of.  Class gives run-time type information about any class
// derived from it.  This is really handy when you have a pointer to an object 
// that you need to know if it supports certain behaviour.
// 

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "g_local.h"
#include "class.h"
#include "linklist.h"

int totalmemallocated = 0;
int numclassesallocated = 0;

static ClassDef *classlist = NULL;

ClassDef::ClassDef()
	{
	this->classname		= NULL;
	this->classID			= NULL;
	this->superclass		= NULL;
	this->responses		= NULL, 
	this->numEvents		= 0;
	this->responseLookup = NULL;
	this->newInstance		= NULL;
	this->classSize		= 0;
	this->super				= NULL;
	this->prev				= this;
	this->next				= this;
	}

ClassDef::ClassDef
	(
	const char *classname,
	const char *classID,
	const char *superclass,
	ResponseDef *responses, 
	void *( *newInstance )( void ),
	int classSize
	)

	{
	ClassDef *node;

	if ( classlist == NULL )
		{
		classlist = new ClassDef;
		}

	this->classname			= classname;
	this->classID				= classID;
	this->superclass			= superclass;
	this->responses			= responses;
	this->numEvents			= 0;
	this->responseLookup		= NULL;
	this->newInstance			= newInstance;
	this->classSize			= classSize;
	this->super					= getClass( superclass );

	// It's not uncommon for classes to not have a class id, so just set it 
	// to an empty string so that we're not checking for it all the time.
	if ( !classID )
		{
		this->classID = "";
		}

	// Check if any subclasses were initialized before their superclass
	for( node = classlist->next; node != classlist; node = node->next )
		{
		if ( ( node->super == NULL ) && ( !Q_stricmp( node->superclass, this->classname ) ) &&
			( Q_stricmp( node->classname, "Class" ) ) )
			{
			node->super	= this;
			}
		}

	// Add to front of list
	LL_Add( classlist, this, prev, next );
	}

ClassDef::~ClassDef()
	{
	ClassDef *node;

	if ( classlist != this )
		{
		LL_Remove( this, prev, next );

		// Check if any subclasses were initialized before their superclass
		for( node = classlist->next; node != classlist; node = node->next )
			{
			if ( node->super == this )
				{
				node->super	= NULL;
				}
			}
		}
	else
		{
		// If the head of the list is deleted before the list is cleared, then we may have problems
		assert( this->next == this->prev );
		}

	if ( responseLookup )
		{
		delete[] responseLookup;
		responseLookup = NULL;
		}
	}

EXPORT_FROM_DLL void ClassDef::BuildResponseList
	(
	void
	)

	{
	ClassDef		*c;
	ResponseDef *r;
	int			ev;
	int			i;
	qboolean		*set;
	int			num;

	if ( responseLookup )
		{
		delete[] responseLookup;
		responseLookup = NULL;
		}

	num = Event::NumEventCommands();
	responseLookup = ( Response ** )new char[ sizeof( Response * ) * num ];
	memset( responseLookup, 0, sizeof( Response * ) * num );

	set = new qboolean[ num ];
	memset( set, 0, sizeof( qboolean ) * num );

	this->numEvents = num;

	for( c = this; c != NULL; c = c->super )
		{
		r = c->responses;
		if ( r )
			{
			for( i = 0; r[ i ].event != NULL; i++ )
				{
				ev = ( int )*r[ i ].event;
				if ( !set[ ev ] )
					{
					set[ ev ] = true;
					if ( r[ i ].response )
						{
						responseLookup[ ev ] = &r[ i ].response;
						}
					else
						{
						responseLookup[ ev ] = NULL;
						}
					}
				}
			}
		}

	delete[] set;
	}

EXPORT_FROM_DLL void BuildEventResponses
	(
	void
	)

	{
	ClassDef *c;
	int amount;
	int numclasses;

	amount = 0;
	numclasses = 0;
	for( c = classlist->next; c != classlist; c = c->next )
		{
		c->BuildResponseList();

		amount += c->numEvents * sizeof( Response * );
		numclasses++;
		}

	gi.dprintf( "\n------------------\nEvent system initialized:\n"
		"%d classes\n%d events\n%d total memory in response list\n\n", 
		numclasses, Event::NumEventCommands(), amount );
	}

EXPORT_FROM_DLL ClassDef *getClassForID
	(
	const char *name
	)

	{
	ClassDef *c;

	for( c = classlist->next; c != classlist; c = c->next )
		{
		if ( c->classID && !Q_stricmp( c->classID, name ) )
			{
			return c;
			}
		}

	return NULL;
	}

EXPORT_FROM_DLL ClassDef *getClass
	(
	const char *name
	)

	{
	ClassDef *c;

	for( c = classlist->next; c != classlist; c = c->next )
		{
		if ( !Q_stricmp( c->classname, name ) )
			{
			return c;
			}
		}

	return NULL;
	}

EXPORT_FROM_DLL ClassDef *getClassList
	(
	void
	)

	{
	return classlist;
	}

EXPORT_FROM_DLL void listAllClasses
	(
	void
	)

	{
	ClassDef *c;

	for( c = classlist->next; c != classlist; c = c->next )
		{
		gi.dprintf( "%s\n", c->classname );
		}
	}

EXPORT_FROM_DLL void listInheritanceOrder
	(
	const char *classname
	)

	{
	ClassDef *cls;
	ClassDef *c;

	cls = getClass( classname );
	if ( !cls )
		{
		gi.dprintf( "Unknown class: %s\n", classname );
		return;
		}
	for( c = cls; c != NULL; c = c->super )
		{
		gi.dprintf( "%s\n", c->classname );
		}
	}

EXPORT_FROM_DLL qboolean checkInheritance
	(
	ClassDef *superclass,
	ClassDef *subclass
	)

	{
	ClassDef *c;

	for( c = subclass; c != NULL; c = c->super )
		{
		if ( c == superclass )
			{
			return true;
			}
		}
	return false;
	}

EXPORT_FROM_DLL qboolean checkInheritance
	(
	ClassDef *superclass,
	const char *subclass
	)

	{
	ClassDef *c;

	c = getClass( subclass );
	if ( c == NULL )
		{
		gi.dprintf( "Unknown class: %s\n", subclass );
		return false;
		}
	return checkInheritance( superclass, c );
	}

EXPORT_FROM_DLL qboolean checkInheritance
	(
	const char *superclass,
	const char *subclass
	)

	{
	ClassDef *c1;
	ClassDef *c2;

	c1 = getClass( superclass );
	c2 = getClass( subclass );
	if ( c1 == NULL )
		{
		gi.dprintf( "Unknown class: %s\n", superclass );
		return false;
		}
	if ( c2 == NULL )
		{
		gi.dprintf( "Unknown class: %s\n", subclass );
		return false;
		}
	return checkInheritance( c1, c2 );
	}
	
CLASS_DECLARATION( NULL, Class, NULL );

ResponseDef Class::Responses[] =
	{
		{ NULL, NULL }
	};

#ifdef NDEBUG

EXPORT_FROM_DLL void * Class::operator new( size_t s )
	{
	int *p;

	s += sizeof( int );
	p = ( int * )::new char[ s ];
	*p = s;
	totalmemallocated += s;
	numclassesallocated++;
	return p + 1;
	}

EXPORT_FROM_DLL void Class::operator delete( void *ptr )
	{
	int *p;

	p = ( ( int * )ptr ) - 1;
	totalmemallocated -= *p;
	numclassesallocated--;
	::delete[]( p );
	}

#else

EXPORT_FROM_DLL void * Class::operator new( size_t s )
	{
	int *p;

	s += sizeof( int ) * 3;
	p = ( int * )::new char[ s ];
	p[ 0 ] = 0x12348765;
	*( int * )( ((byte *)p) + s - sizeof( int ) ) = 0x56784321;
	p[ 1 ] = s;
	totalmemallocated += s;
	numclassesallocated++;
	return p + 2;
	}

EXPORT_FROM_DLL void Class::operator delete( void *ptr )
	{
	int *p;

	p = ( ( int * )ptr ) - 2;

	assert( p[ 0 ] == 0x12348765 );
	assert( *( int * )( ((byte *)p) + p[ 1 ] - sizeof( int ) ) == 0x56784321 );

	totalmemallocated -= p[ 1 ];
	numclassesallocated--;
	::delete[]( p );
	}

#endif

EXPORT_FROM_DLL void DisplayMemoryUsage
	(
   void
	)

	{
	gi.printf( "Classes %-5d Class memory used: %d\n", numclassesallocated, totalmemallocated );
   }
	Class::Class()
	{
	SafePtrList = NULL;
	}

Class::~Class()
	{
	while( SafePtrList != NULL )
		{
		SafePtrList->Clear();
		}
	}

EXPORT_FROM_DLL void Class::Archive
	(
	Archiver &arc
	)

	{
	}

EXPORT_FROM_DLL void Class::Unarchive
	(
	Archiver &arc
	)

	{
	}

EXPORT_FROM_DLL void Class::warning
	(
	const char *function,
	const char *fmt,
	...
	)

	{
	va_list	argptr;
	char		text[ 1024 ];

	va_start( argptr, fmt );
	vsprintf( text, fmt, argptr );
	va_end( argptr );

	if ( getClassID() )
		{
		gi.dprintf( "%s::%s : %s\n", getClassID(), function, text );
		}
	else
		{
		gi.dprintf( "%s::%s : %s\n", getClassname(), function, text );
		}
	}

EXPORT_FROM_DLL void Class::error
	(
	const char *function,
	const char *fmt,
	...
	)

	{
	va_list	argptr;
	char		text[ 1024 ];

	va_start( argptr, fmt );
	vsprintf( text, fmt, argptr );
	va_end( argptr );

	if ( getClassID() )
		{
		gi.error( "%s::%s : %s\n", getClassID(), function, text );
		}
	else
		{
		gi.error( "%s::%s : %s\n", getClassname(), function, text );
		}
	}

EXPORT_FROM_DLL qboolean Class::inheritsFrom
	(
	const char *name 
	)

	{
	ClassDef *c;

	c = getClass( name );
	if ( c == NULL )
		{
		gi.dprintf( "Unknown class: %s\n", name );
		return false;
		}
	return checkInheritance( c, classinfo() );
	}

EXPORT_FROM_DLL qboolean Class::isInheritedBy
	(
	const char *name 
	)

	{
	ClassDef *c;

	c = getClass( name );
	if ( c == NULL )
		{
		gi.dprintf( "Unknown class: %s\n", name );
		return false;
		}
	return checkInheritance( classinfo(), c );
	}

EXPORT_FROM_DLL const char *Class::getClassname
	( 
	void 
	)

	{
	ClassDef *cls;

	cls = classinfo();
	return cls->classname;
	}

EXPORT_FROM_DLL const char *Class::getClassID
	(
	void 
	)

	{
	ClassDef *cls;

	cls = classinfo();
	return cls->classID;
	}

EXPORT_FROM_DLL const char *Class::getSuperclass
	( 
	void 
	)

	{
	ClassDef *cls;

	cls = classinfo();
	return cls->superclass;
	}

EXPORT_FROM_DLL void *Class::newInstance
	( 
	void 
	)

	{
	ClassDef *cls;

	cls = classinfo();
	return cls->newInstance();
	}
