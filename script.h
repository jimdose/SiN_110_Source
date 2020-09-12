//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/script.h                         $
// $Revision:: 12                                                             $
//   $Author:: Jimdose                                                        $
//     $Date:: 10/07/98 11:59p                                                $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/script.h                              $
// 
// 12    10/07/98 11:59p Jimdose
// changed script_p to offset in script markers
// 
// 11    9/21/98 10:15p Markd
// Putting archiving and unarchiving functions in
// 
// 10    6/09/98 4:24p Jimdose
// filename is now an str
// added close and filename
// 
// 9     5/26/98 11:59p Markd
// moved buffer out of protected for e3 demo
// 
// 8     5/24/98 4:48p Jimdose
// Made char *'s const
// 
// 7     3/02/98 8:49p Jimdose
// Changed CLASS_PROTOTYPE to only take the classname
// 
// 6     2/17/98 7:14p Jimdose
// Added MarkPosition and RestorePosition
// Added atString for determining if the next token is a quoted string
// 
// 5     2/03/98 10:54a Jimdose
// Updated to work with Quake 2 engine
// 
// 3     11/24/97 4:30p Markd
// Added GetVector 
// 
// 2     9/26/97 6:14p Jimdose
// Added standard Ritual headers
//
// DESCRIPTION:
// C++ implementaion of tokenizing text interpretation.  Class accepts filename
// to load or pointer to preloaded text data.  Standard tokenizing operations
// such as skip white-space, get string, get integer, get float, get token,
// and skip line are implemented.  
//
// Note: all '//', '#', and ';' are treated as comments.  Probably should
// make this behaviour toggleable.
// 

#ifndef __SCRIPT_H__
#define __SCRIPT_H__

#include "class.h"
#include "vector.h"
#include "str.h"

#define	MAXTOKEN	256

typedef struct
	{
	qboolean		tokenready;
   int         offset;
	int			line;		
	char			token[ MAXTOKEN ];
	} scriptmarker_t;

class EXPORT_FROM_DLL Script : public Class
	{
	protected:
		qboolean		tokenready;
		
		str			filename;
		const char	*script_p;
		const char	*end_p;
		
		int			line;		
		char			token[ MAXTOKEN ];

		qboolean		releaseBuffer;

		qboolean		AtComment( void );
		void			CheckOverflow( void );

	public:
		const char	*buffer;
		int			length;

      CLASS_PROTOTYPE( Script );

		~Script();
		Script();
		void			Close( void );
		const char *Filename( void );
		int			GetLineNumber( void );
		void			Reset( void );	
		void			MarkPosition( scriptmarker_t *mark );
		void			RestorePosition( scriptmarker_t *mark );
		qboolean		SkipToEOL( void );
		void			SkipWhiteSpace( qboolean crossline );
		void			SkipNonToken( qboolean crossline );
		qboolean		TokenAvailable( qboolean crossline );
		qboolean		CommentAvailable( qboolean crossline );
		void			UnGetToken( void );
		qboolean		AtString( qboolean crossline );
		const char	*GetToken( qboolean crossline );
		const char	*GetLine( qboolean crossline );
		const char	*GetRaw( void );
		const char	*GetString( qboolean crossline );
		qboolean		GetSpecific( const char *string );
		int			GetInteger( qboolean crossline );
		double		GetDouble( qboolean crossline );
		float			GetFloat( qboolean crossline );
		Vector		GetVector( qboolean crossline );
		int			LinesInFile( void );
		void			Parse( const char *data, int length, const char *name );
		void			LoadFile( const char *name );
		const char	*Token( void );
      virtual void Archive( Archiver &arc );
      virtual void Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Script::Archive
	(
	Archiver &arc
	)
   {
   Class::Archive( arc );

   arc.WriteString( filename );
   arc.WriteBoolean( tokenready );
   //
   // save out current pointer as an offset
   //
   arc.WriteInteger( script_p - buffer );
   arc.WriteInteger( line );
   arc.WriteRaw( token, sizeof( token ) );
   }

inline EXPORT_FROM_DLL void Script::Unarchive
	(
	Archiver &arc
	)
   {
   int i;

   Class::Unarchive( arc );

   arc.ReadString( &filename );
   //
   // load the file in
   //
   LoadFile( filename.c_str() );

   arc.ReadBoolean( &tokenready );
   arc.ReadInteger( &i );
   //
   // restore the script pointer
   //
   script_p = buffer + i;
   arc.ReadInteger( &line );
   arc.ReadRaw( token, sizeof( token ) );
   }

#endif
