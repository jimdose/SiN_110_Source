//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/str.h                            $
// $Revision:: 6                                                              $
//   $Author:: Jimdose                                                        $
//     $Date:: 10/25/98 11:58p                                                $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/str.h                                 $
// 
// 6     10/25/98 11:58p Jimdose
// working on getting rid of exports
// 
// 5     10/08/98 12:04a Jimdose
// made = keep the old string around until it was copied in case the source was
// inside the old string
// 
// 4     6/09/98 4:25p Jimdose
// added substring copy constructor
// 
// 3     5/13/98 4:53p Jimdose
// Moved defintion of functions to header to make them inline
// 
// 2     4/30/98 9:23p Jimdose
// Created file
// 
// DESCRIPTION:
// Simple, DLL portable string class
// 

#ifndef __STR_H__
#define __STR_H__

#include <assert.h>
#include <string.h>

#if 1
class __declspec( dllexport ) str
#else
class str
#endif
	{
	protected:
		int					len;
		char					*data;

	public:
								~str();
								str();
								str( const char *text );
								str( const str& string );
								str( const str string, int start, int end );

					int		length( void ) const;
		const		char *	c_str( void ) const;

					void		append( const char *text );
					void		append( const str& text );

					char		operator[]( int index ) const;
					char&		operator[]( int index );

					void		operator=( const str& text );
					void		operator=( const char *text );

		friend	str		operator+( const str& a, const str& b );
		friend	str		operator+( const str& a, const char *b );
		friend	str		operator+( const char *a, const str& b );

					str&		operator+=( const str& a );
					str&		operator+=( const char *a );

		friend	int		operator==(	const str& a, const str& b );
		friend	int		operator==(	const str& a, const char *b );
		friend	int		operator==(	const char *a, const str& b );

		friend	int		operator!=(	const str& a, const str& b );
		friend	int		operator!=(	const str& a, const char *b );
		friend	int		operator!=(	const char *a, const str& b );
	};

inline str::~str()
	{
	assert( data );
	if ( data )
		{
		delete [] data;
		data = NULL;
		}
	}

inline str::str()
	{
	data = new char[ 1 ];
	data[ 0 ] = 0;
	len = 0;
	}

inline str::str
	(
	const char *text
	)

	{
	assert( text );

	if ( text )
		{
		len = strlen( text );
		data = new char[ len + 1 ];
		strcpy( data, text );
		}
	else
		{
		data = new char[ 1 ];
		data[ 0 ] = 0;
		len = 0;
		}
	}

inline str::str
	(
	const str& text
	)

	{
	len = text.length();
	data = new char[ len + 1 ];
	strcpy( data, text.c_str() );
	}

inline str::str
	(
	const str text, 
	int start,
	int end
	)

	{
	int i;

	if ( end > text.length() )
		{
		end = text.length();
		}

	if ( start > text.length() )
		{
		start = text.length();
		}

	len = end - start;
	if ( len < 0 )
		{
		len = 0;
		}

	data = new char[ len + 1 ];
	for( i = 0; i < len; i++ )
		{
		data[ i ] = text[ start + i ];
		}

	data[ len ] = 0;
	}

inline int str::length( void ) const
	{
	return len;
	}

inline const char *str::c_str( void ) const
	{
	assert( data );

	return data;
	}

inline void str::append
	(
	const char *text
	)

	{
	char *olddata;

	assert( text );
	assert( data );

	if ( text )
		{
		olddata = data;

		len = strlen( data ) + strlen( text );
		data = new char[ len + 1 ];
		
		strcpy( data, olddata );
		strcat( data, text );

		if ( olddata )
			{
			delete [] olddata;
			olddata = NULL;
			}
		}
	}

inline void str::append
	(
	const str& text
	)

	{
	assert( data );
	append( text.c_str() );
	}

inline char str::operator[]( int index ) const
	{
	assert( data );

	// don't include the '/0' in the test, because technically, it's out of bounds
	assert( ( index >= 0 ) && ( index < len ) );

	// In release mode, give them a null character
	// don't include the '/0' in the test, because technically, it's out of bounds
	if ( ( index < 0 ) || ( index >= len ) )
		{
		return 0;
		}

	return data[ index ];
	}

inline char& str::operator[]
	(
	int index
	)

	{
	// Used for result for invalid indices
	static char dummy = 0;

	assert( data );

	// don't include the '/0' in the test, because technically, it's out of bounds
	assert( ( index >= 0 ) && ( index < len ) );

	// In release mode, let them change a safe variable
	// don't include the '/0' in the test, because technically, it's out of bounds
	if ( ( index < 0 ) || ( index >= len ) )
		{
		return dummy;
		}

	return data[ index ];
	}

inline void str::operator=
	(
	const str& text
	)

	{
   char *temp;

	assert( data );

   len = text.length();
	temp = new char[ len + 1 ];
	strcpy( temp, text.c_str() );

   // we don't destroy the old data until we've allocated the new one
   // in case we are assigning the string from data inside the old string.
	if ( data )
		{
		delete [] data;
		}

   data = temp;
	}

inline void str::operator=
	(
	const char *text
	)

	{
   char *temp;

	assert( data );
	assert( text );

	if ( !text )
		{
		// safe behaviour if NULL
		len = 0;
		temp = new char[ 1 ];
		temp[ 0 ] = 0;
		}
	else
		{
		len = strlen( text );
		temp = new char[ len + 1 ];
		strcpy( temp, text );
		}

   // we don't destroy the old data until we've allocated the new one
   // in case we are assigning the string from data inside the old string.
   if ( data )
		{
		delete [] data;
		}

   data = temp;
	}

inline str operator+
	(
	const str& a,
	const str& b
	)

	{
	str result( a );

	result.append( b );

	return result;
	}

inline str operator+
	(
	const str& a,
	const char *b
	)

	{
	str result( a );

	result.append( b );

	return result;
	}

inline str operator+
	(
	const char *a,
	const str& b
	)

	{
	str result( a );

	result.append( b );

	return result;
	}

inline str& str::operator+=
	(
	const str& a
	)

	{
	assert( data );
	append( a );
	return *this;
	}

inline str& str::operator+=
	(
	const char *a
	)

	{
	assert( data );
	append( a );
	return *this;
	}

inline int operator==
	(
	const str& a,
	const str& b
	)

	{
	return ( !strcmp( a.c_str(), b.c_str() ) );
	}

inline int operator==
	(
	const str& a,
	const char *b
	)

	{
	assert( b );
	if ( !b )
		{
		return false;
		}
	return ( !strcmp( a.c_str(), b ) );
	}

inline int operator==
	(
	const char *a,
	const str& b
	)

	{
	assert( a );
	if ( !a )
		{
		return false;
		}
	return ( !strcmp( a, b.c_str() ) );
	}

inline int operator!=
	(
	const str& a,
	const str& b
	)

	{
	return !( a == b );
	}

inline int operator!=
	(
	const str& a,
	const char *b
	)

	{
	return !( a == b );
	}

inline int operator!=
	(
	const char *a,
	const str& b
	)

	{
	return !( a == b );
	}

// Test function
void TestStringClass( void );

#endif
