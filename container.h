//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/container.h                      $
// $Revision:: 17                                                             $
//   $Author:: Jimdose                                                        $
//     $Date:: 10/25/98 11:53p                                                $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/container.h                           $
// 
// 17    10/25/98 11:53p Jimdose
// added EXPORT_TEMPLATE
// 
// 16    10/07/98 11:45p Jimdose
// Added \n to dprintf's
// Made resize assert only when size was negative
// 
// 15    9/21/98 6:01p Markd
// tried putting archiving back in, but took it out again, when I realized it
// wouldn't work because the class hierarchy hasn't been created yet.
// 
// 14    9/21/98 4:21p Markd
// Put in archive functions and rewrote all archive routines
// 
// 13    8/20/98 4:42p Jimdose
// Added Sort function.
// 
// 12    7/09/98 1:40a Jimdose
// ClearObjectList now only reallocates the list if there are any objects in
// the list
// 
// 11    5/25/98 2:29p Aldie
// Fixed issues with not loading game dll
// 
// 10    3/23/98 1:33p Jimdose
// Revamped event and command system
// 
// 9     3/04/98 1:43p Jimdose
// Changed IndexOfObject so that it did a comparison instead of a memcmp
// 
// 8     3/02/98 5:27p Jimdose
// Changed Container to a template to make it more flexible
// 
// 7     2/03/98 10:51a Jimdose
// Updated to work with Quake 2 engine
// 
// 5     11/20/97 9:03p Jimdose
// Changed Container class to use entity # (int) instead of void *
// 
// 4     11/07/97 6:37p Jimdose
// Added FreeObjectList to empty the list and free up the memory.
// Changed ClearObjectList to only empty the list, but keep the memory
// allocated.
// Changed all functions from being virtual to being exported by the DLL.
// 
// 3     10/27/97 2:49p Jimdose
// Removed dependency on quakedef.h
// 
// 2     9/26/97 6:13p Jimdose
// Added standard Ritual headers
//
// DESCRIPTION:
// Base class for a dynamic array.  Allows adding, removing, index of,
// and finding of entries with specified value.  Originally created for 
// cataloging entities, but pointers to objects that may be removed at
// any time are bad to keep around, so only entity numbers should be
// used in the future.
// 

#ifndef __CONTAINER_H__
#define __CONTAINER_H__

#include "g_local.h"
#include <stdlib.h>

template< class Type >
class EXPORT_FROM_DLL Container
	{
	private:
		Type	*objlist;
		int	numobjects;
		int	maxobjects;

	public:
					Container();
					~Container<Type>();
		void		FreeObjectList( void );
		void		ClearObjectList( void );
		int		NumObjects( void );
		void		Resize( int maxelements );
		void		SetObjectAt( int index, Type& obj );
		int		AddObject( Type& obj );
		int		AddUniqueObject( Type& obj );
		void  	AddObjectAt( int index, Type& obj );
		int		IndexOfObject( Type& obj );
		qboolean	ObjectInList( Type& obj );
		Type&		ObjectAt( int index );
		Type		*AddressOfObjectAt( int index );
		void		RemoveObjectAt( int index );
		void		RemoveObject( Type& obj );
		void		Sort( int ( __cdecl *compare )( const void *elem1, const void *elem2 ) );
//      virtual void Archive(	Archiver &arc );
//      virtual void Unarchive( Archiver &arc );
	};
/*
template< class Type >
EXPORT_FROM_DLL void Container<Type>::Archive
	(
	Archiver &arc
	)
	{
   int i;

   arc.WriteInteger( maxobjects );
   arc.WriteInteger( numobjects );

   for ( i = 0; i < numobjects; i++ )
      {
		arc.WriteRaw( objlist[ i ], sizeof( Type ) );
      }
	}

template< class Type >
EXPORT_FROM_DLL void Container<Type>::Unarchive
	(
	Archiver &arc
	)

	{
   int i;

	FreeObjectList();

   maxobjects = arc.ReadInteger();
   numobjects = arc.ReadInteger();

	objlist = new Type[ maxobjects ];
   for ( i = 0; i < numobjects; i++ )
      {
		arc.ReadRaw( &objlist[ i ], sizeof( Type ) );
      }
	}
*/

template< class Type >
Container<Type>::Container()
	{
	objlist = NULL;
	FreeObjectList();
	}

template< class Type >
Container<Type>::~Container<Type>()
	{
	FreeObjectList();
	}

template< class Type >
EXPORT_FROM_DLL void Container<Type>::FreeObjectList
	(
	void
	)

	{
	if ( objlist )
		{
		delete[] objlist;
		}
	objlist = NULL;
	numobjects = 0;
	maxobjects = 0;
	}

template< class Type >
EXPORT_FROM_DLL void Container<Type>::ClearObjectList
	(
	void
	)

	{
	// only delete the list if we have objects in it 
	if ( objlist && numobjects )
		{
		delete[] objlist;
		objlist = new Type[ maxobjects ];
		numobjects = 0;
		}
	}

template< class Type >
EXPORT_FROM_DLL int Container<Type>::NumObjects
	(
	void
	)

	{
	return numobjects;
	}

template< class Type >
EXPORT_FROM_DLL void Container<Type>::Resize
	(
	int maxelements
	)

	{
	Type *temp;
	int i;

   assert( maxelements >= 0 );
   
   if ( maxelements <= 0 )
      {
      FreeObjectList();
      return;
      }

	if ( !objlist )
		{
		maxobjects = maxelements;
		objlist = new Type[ maxobjects ];
		}
	else
		{
		temp = objlist;
		maxobjects = maxelements;
		if ( maxobjects < numobjects )
			{
			maxobjects = numobjects;
			}

		objlist = new Type[ maxobjects ];
		for( i = 0; i < numobjects; i++ )
			{
			objlist[ i ] = temp[ i ];
			}
		delete[] temp;
		}
	}

template< class Type >
EXPORT_FROM_DLL void Container<Type>::SetObjectAt
	(
	int index,
	Type& obj
	)

	{
	if ( ( index <= 0 ) || ( index > numobjects ) )
		{
		gi.error( "Container::SetObjectAt : index out of range" );
		}

	objlist[ index - 1 ] = obj;
	}

template< class Type >
EXPORT_FROM_DLL int Container<Type>::AddObject
	(
	Type& obj
	)

	{
	if ( !objlist )
		{
		Resize( 10 );
		}

	if ( numobjects == maxobjects )
		{
		Resize( maxobjects * 2 );
		}

	objlist[ numobjects ] = obj;
	numobjects++;

	return numobjects;
	}

template< class Type >
EXPORT_FROM_DLL int Container<Type>::AddUniqueObject
	(
	Type& obj
	)

	{
   int index;

   index = IndexOfObject( obj );
   if ( !index )
      index = AddObject( obj );
   return index;
	}

template< class Type >
EXPORT_FROM_DLL void Container<Type>::AddObjectAt
	(
	int index,
	Type& obj
	)

	{
   //
   // this should only be used when reconstructing a list that has to be identical to the original
   //
   if ( index > maxobjects )
      {
      Resize( index );
      }
   if ( index > numobjects )
      {
      numobjects = index;
      }
   SetObjectAt( index, obj );
	}

template< class Type >
EXPORT_FROM_DLL int Container<Type>::IndexOfObject
	(
	Type& obj
	)

	{
	int i;

	for( i = 0; i < numobjects; i++ )
		{
		if ( objlist[ i ] == obj )
			{
			return i + 1;
			}
		}

	return 0;
	}

template< class Type >
EXPORT_FROM_DLL qboolean Container<Type>::ObjectInList
	(
	Type& obj
	)

	{
	if ( !IndexOfObject( obj ) )
		{
		return false;
		}

	return true;
	}

template< class Type >
EXPORT_FROM_DLL Type& Container<Type>::ObjectAt
	(
	int index
	)

	{
	if ( ( index <= 0 ) || ( index > numobjects ) )
		{
		gi.error( "Container::ObjectAt : index out of range" );
		}

	return objlist[ index - 1 ];
	}

template< class Type >
EXPORT_FROM_DLL Type * Container<Type>::AddressOfObjectAt
	(
	int index
	)

	{
   //
   // this should only be used when reconstructing a list that has to be identical to the original
   //
   if ( index > maxobjects )
      {
      gi.error( "Container::AddressOfObjectAt : index is greater than maxobjects" );
      }
   if ( index > numobjects )
      {
      numobjects = index;
      }
	return &objlist[ index - 1 ];
	}

template< class Type >
EXPORT_FROM_DLL void Container<Type>::RemoveObjectAt
	(
	int index
	)

	{
	int i;

	if ( !objlist )
		{
		gi.dprintf( "Container::RemoveObjectAt : Empty list\n" );
		return;
		}

	if ( ( index <= 0 ) || ( index > numobjects ) )
		{
		gi.error( "Container::RemoveObjectAt : index out of range" );
		return;
		}

	i = index - 1;
	numobjects--;
	for( i = index - 1; i < numobjects; i++ )
		{
		objlist[ i ] = objlist[ i + 1 ];
		}
	}

template< class Type >
EXPORT_FROM_DLL void Container<Type>::RemoveObject
	(
	Type& obj
	)

	{
	int index;

	index = IndexOfObject( obj );
	if ( !index )
		{
		gi.dprintf( "Container::RemoveObject : Object not in list\n" );
		return;
		}

	RemoveObjectAt( index );
	}

template< class Type >
EXPORT_FROM_DLL void Container<Type>::Sort
	(
	int ( __cdecl *compare )( const void *elem1, const void *elem2 )
	)

	{
	if ( !objlist )
		{
		gi.dprintf( "Container::RemoveObjectAt : Empty list\n" );
		return;
		}

	qsort( ( void * )objlist, ( size_t )numobjects, sizeof( Type ), compare );
	}

//
// Exported templated classes must be explicitly instantiated
//
#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL Container<int>;
#endif

#endif /* container.h */
