//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/class.h                          $
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
// $Log:: /Quake 2 Engine/Sin/code/game/class.h                               $
// 
// 17    10/25/98 11:53p Jimdose
// added EXPORT_TEMPLATE
// 
// 16    10/19/98 12:07a Jimdose
// made all code use fast checks for inheritance (no text lookups when
// possible)
// isSubclassOf no longer requires ::_classinfo()
// 
// 15    10/07/98 11:42p Jimdose
// Got savegames working
// 
// 14    9/24/98 1:49a Jimdose
// Added DisplayMemoryUsage
// 
// 13    9/21/98 2:15a Jimdose
// Moved non-type specific code in SafePtr to SafePtrBase to help with save
// games
// 
// 12    9/03/98 9:08p Jimdose
// Overrided == and != for SafePtr
// 
// 11    6/27/98 9:18p Jimdose
// Made lookup for event responses for faster processing
// 
// 10    5/24/98 4:48p Jimdose
// Made char *'s const
// 
// 9     5/11/98 8:06p Jimdose
// Added SafePtr
// 
// 8     5/08/98 2:51p Jimdose
// Added archiving functions
// 
// 7     3/23/98 1:33p Jimdose
// Revamped event and command system
// 
// 6     3/02/98 8:49p Jimdose
// Changed CLASS_PROTOTYPE to only take the classname
// 
// 5     2/03/98 10:53a Jimdose
// Updated to work with Quake 2 engine
// Made class registration automatic
// 
// 4     1/22/98 6:50p Jimdose
// Made Q2 compatible
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

#ifndef __CLASS_H__
#define __CLASS_H__

#include "g_local.h"

class Class;
class Event;
class Archiver;

typedef void ( Class::*Response )( Event *event );
typedef struct 
	{
	Event		*event;
	Response	response;
	} ResponseDef;

/***********************************************************************

  ClassDef

***********************************************************************/

class EXPORT_FROM_DLL ClassDef
	{
	public:
		const char	*classname;
		const char	*classID;
		const char	*superclass;
		void			*( *newInstance )( void );
		int			classSize;
		ResponseDef *responses;
		int			numEvents;
		Response		**responseLookup;
		ClassDef		*super;
		ClassDef		*next;
		ClassDef		*prev;

		ClassDef();
		~ClassDef();
		ClassDef( const char *classname, const char *classID, const char *superclass, 
			ResponseDef *responses, void *( *newInstance )( void ), int classSize );
		void	BuildResponseList( void );
	};

/***********************************************************************

  SafePtr

***********************************************************************/

class SafePtrBase;

class Class;

class EXPORT_FROM_DLL SafePtrBase
	{
   private:
		void	AddReference( Class *ptr );
		void	RemoveReference( Class *ptr );

	protected:
		SafePtrBase *prevSafePtr;
		SafePtrBase *nextSafePtr;
		Class       *ptr;

	public:
                  SafePtrBase();
		virtual     ~SafePtrBase();
		void	      InitSafePtr( Class *newptr );
      void	      Clear( void );
	};

/***********************************************************************

  Class

***********************************************************************/

#define CLASS_DECLARATION( nameofsuperclass, nameofclass, classid )	\
	ClassDef nameofclass::ClassInfo												\
		(																					\
		#nameofclass, classid, #nameofsuperclass,								\
		nameofclass::Responses, nameofclass::_newInstance,					\
		sizeof( nameofclass )														\
		);																					\
	EXPORT_FROM_DLL void *nameofclass::_newInstance( void )				\
		{																					\
		return new nameofclass;														\
		}																					\
	ClassDef *nameofclass::classinfo( void )								   \
		{																					\
		return &( nameofclass::ClassInfo );										\
		}

#define CLASS_PROTOTYPE( nameofclass )											\
	public:																				\
	static	ClassDef			ClassInfo;											\
	static	void				*nameofclass::_newInstance( void );			\
	virtual	ClassDef			*nameofclass::classinfo( void );			   \
	static	ResponseDef		nameofclass::Responses[];

class EXPORT_FROM_DLL Class
	{
   private:
		SafePtrBase	 *SafePtrList;
		friend class SafePtrBase;

	public:
		CLASS_PROTOTYPE( Class );
		void * operator	new( size_t );
		void operator		delete( void * );

								Class();
		virtual				~Class();
		virtual void		Archive( Archiver &arc );
		virtual void		Unarchive( Archiver &arc );
		void					warning( const char *function, const char *fmt, ... );
		void					error( const char *function, const char *fmt, ... );
		qboolean				inheritsFrom( ClassDef *c );
		qboolean				inheritsFrom( const char *name );
		qboolean				isInheritedBy( const char *name );
		qboolean				isInheritedBy( ClassDef *c );
		const char			*getClassname( void );
		const char			*getClassID( void );
		const char			*getSuperclass( void );
		void					*newInstance( void );
	};

EXPORT_FROM_DLL void			BuildEventResponses( void );
EXPORT_FROM_DLL ClassDef	*getClassForID( const char *name );
EXPORT_FROM_DLL ClassDef	*getClass( const char *name );
EXPORT_FROM_DLL ClassDef	*getClassList( void );
EXPORT_FROM_DLL void			listAllClasses( void );
EXPORT_FROM_DLL void			listInheritanceOrder( const char *classname );
EXPORT_FROM_DLL qboolean	checkInheritance( ClassDef *superclass, ClassDef *subclass );
EXPORT_FROM_DLL qboolean	checkInheritance( ClassDef *superclass, const char *subclass );
EXPORT_FROM_DLL qboolean	checkInheritance( const char *superclass, const char *subclass );
EXPORT_FROM_DLL void       DisplayMemoryUsage( void );

inline EXPORT_FROM_DLL qboolean Class::inheritsFrom
	( 
	ClassDef *c 
	)

	{
	return checkInheritance( c, classinfo() );
	}

inline EXPORT_FROM_DLL qboolean Class::isInheritedBy
	( 
	ClassDef *c 
	)

	{
	return checkInheritance( classinfo(), c );
	}

// The lack of a space between the ")" and "inheritsFrom" is intentional.
// It allows the macro to compile like a function call.  However, this
// may cause problems in some compilers (like gcc), so we may have to
// change this to work like a normal macro with the object passed in
// as a parameter to the macro.
#define isSubclassOf( classname )inheritsFrom( &classname::ClassInfo )
#define isSuperclassOf( classname )isInheritedBy( &classname::ClassInfo )

/***********************************************************************

  SafePtr

***********************************************************************/

inline EXPORT_FROM_DLL SafePtrBase::SafePtrBase()
	{
   prevSafePtr = NULL;
	nextSafePtr = NULL;
   ptr = NULL;
   }

inline EXPORT_FROM_DLL SafePtrBase::~SafePtrBase()
	{
   Clear();
   }

inline EXPORT_FROM_DLL void SafePtrBase::Clear
   (
   void
   )

	{
	if ( ptr )
		{
		RemoveReference( ptr );
		ptr = NULL;
		}
	}

inline EXPORT_FROM_DLL void SafePtrBase::InitSafePtr
   (
   Class *newptr
   )

	{
	if ( ptr != newptr )
		{
		if ( ptr )
			{
			RemoveReference( ptr );
			}

		ptr = newptr;
	   if ( ptr == NULL )
		   {
		   return;
   	   }

      AddReference( ptr );
      }
	}

inline EXPORT_FROM_DLL void SafePtrBase::AddReference
	(
	Class *ptr
	)

	{
	if ( !ptr->SafePtrList )
		{
		ptr->SafePtrList = this;
		LL_Reset( this, nextSafePtr, prevSafePtr );
		}
	else
		{
		LL_Add( ptr->SafePtrList, this, nextSafePtr, prevSafePtr );
		}
	}

inline EXPORT_FROM_DLL void SafePtrBase::RemoveReference
	(
	Class *ptr
	)

	{
	if ( ptr->SafePtrList == this )
		{
		if ( ptr->SafePtrList->nextSafePtr == this )
			{
			ptr->SafePtrList = NULL;
			}
		else
			{
			ptr->SafePtrList = nextSafePtr;
			LL_Remove( this, nextSafePtr, prevSafePtr );
			}
		}
	else
		{
		LL_Remove( this, nextSafePtr, prevSafePtr );
		}
	}

template<class T>
class EXPORT_FROM_DLL SafePtr : public SafePtrBase
	{
	public:
		SafePtr( T* objptr = 0 );
		SafePtr( const SafePtr& obj );

		SafePtr& operator=( const SafePtr& obj );
		SafePtr& operator=( T * const obj );

		friend EXPORT_FROM_DLL int operator==( SafePtr<T> a, T *b );
		friend EXPORT_FROM_DLL int operator!=( SafePtr<T> a, T *b );
		friend EXPORT_FROM_DLL int operator==( T *a, SafePtr<T> b );
		friend EXPORT_FROM_DLL int operator!=( T *a, SafePtr<T> b );

      operator	T*() const;
		T* operator->() const;
		T& operator*() const;
	};

template<class T>
inline EXPORT_FROM_DLL SafePtr<T>::SafePtr( T* objptr )
	{
   InitSafePtr( objptr );
	}

template<class T>
inline EXPORT_FROM_DLL SafePtr<T>::SafePtr( const SafePtr& obj )
	{
   InitSafePtr( obj.ptr );
	}

template<class T>
inline EXPORT_FROM_DLL SafePtr<T>& SafePtr<T>::operator=( const SafePtr& obj )
	{
   InitSafePtr( obj.ptr );
	return *this;
	}

template<class T>
inline EXPORT_FROM_DLL SafePtr<T>& SafePtr<T>::operator=( T * const obj )
	{
   InitSafePtr( obj );
	return *this;
	}

template<class T>
inline EXPORT_FROM_DLL int operator==
	(
	SafePtr<T> a,
	T* b
	)

	{
	return a.ptr == b;
	}

template<class T>
inline EXPORT_FROM_DLL int operator!=
	(
	SafePtr<T> a,
	T* b
	)

	{
	return a.ptr != b;
	}

template<class T>
inline EXPORT_FROM_DLL int operator==
	(
	T* a,
	SafePtr<T> b
	)

	{
	return a == b.ptr;
	}

template<class T>
inline EXPORT_FROM_DLL int operator!=
	(
	T* a,
	SafePtr<T> b
	)

	{
	return a != b.ptr;
	}

template<class T>
inline SafePtr<T>::operator T*() const
	{
	return ( T * )ptr;
	}

template<class T>
inline T* SafePtr<T>::operator->() const
	{
	return ( T * )ptr;
	}

template<class T>
inline T& SafePtr<T>::operator*() const
	{
	return *( T * )ptr;
	}

#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL SafePtr<Class>;
#endif
typedef SafePtr<Class> ClassPtr;

#include "archive.h"

#endif /* class.h */
