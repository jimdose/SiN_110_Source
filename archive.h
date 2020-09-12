//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/archive.h                        $
// $Revision:: 9                                                              $
//   $Author:: Jimdose                                                        $
//     $Date:: 11/12/98 2:31a                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/archive.h                             $
// 
// 9     11/12/98 2:31a Jimdose
// Added ReadFile.  Archives now read from pak files
// 
// 8     10/25/98 11:52p Jimdose
// added EXPORT_TEMPLATE
// 
// 7     10/07/98 11:41p Jimdose
// Got savegames working!!!
// Rewrote event archiving
// 
// 6     9/21/98 10:15p Markd
// Putting archiving and unarchiving functions in
// 
// 5     9/21/98 4:21p Markd
// Put in archive functions and rewrote all archive routines
// 
// 4     5/24/98 4:48p Jimdose
// Made char *'s const
// 
// 3     5/08/98 2:50p Jimdose
// Base archivable class is now Class instead of Listener
// 
// 2     5/07/98 10:39p Jimdose
// created file
// 
// 1     5/06/98 8:19p Jimdose
// 
// DESCRIPTION:
// Class for archiving objects
// 

#ifndef __ARCHIVE_H__
#define __ARCHIVE_H__

#include "g_local.h"
#include "str.h"

#define ARCHIVE_NULL_POINTER ( -654321 )
#define ARCHIVE_POINTER_VALID ( 0 )
#define ARCHIVE_POINTER_NULL ( ARCHIVE_NULL_POINTER )
#define ARCHIVE_POINTER_SELF_REFERENTIAL ( -123456 )

enum
	{
   pointer_fixup_normal,
   pointer_fixup_safe
	};

typedef struct
   {
   void **ptr;
   int  index;
   int  type;
   } pointer_fixup_t;

#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL Container<Class *>;
template class EXPORT_FROM_DLL Container<pointer_fixup_t *>;
#endif

class EXPORT_FROM_DLL ReadFile : public Class
	{
	protected:
		str				filename;
      size_t         length;
      byte           *buffer;
      byte           *pos;

	public:
      CLASS_PROTOTYPE( ReadFile );

							ReadFile();
							~ReadFile();
		void				Close( void );
      const char     *Filename( void );
      size_t         Length( void );
      size_t         Pos( void );
      qboolean       Seek( size_t newpos );
      qboolean       Open( const char *name );
      qboolean       Read( void *dest, size_t size );
	};

class EXPORT_FROM_DLL Archiver : public Class
	{
   private:
      Container<Class *>         classpointerList;
      Container<pointer_fixup_t *> fixupList;

	protected:
		str				filename;
		qboolean			fileerror;
		FILE				*file;
      ReadFile       readfile;
		int				archivemode;
      int            numclassespos;

		void				CheckRead( void );
		void				CheckType( int type );
		int            ReadType( void );
		size_t			ReadSize( void );
		void				CheckSize( int type, size_t size );
		void				ReadData( int type, void *data, size_t size );

		void				CheckWrite( void );
		void				WriteType( int type );
		void				WriteSize( size_t size );
		void				WriteData( int type, const void *data, size_t size );

	public:
      CLASS_PROTOTYPE( Archiver );

							Archiver();
							~Archiver();
		void				FileError( const char *fmt, ... );
		void				Close( void );

		void				Read( str &name );
		void				Read( const char *name );

      //
      // return methods
      //
		Vector			ReadVector( void );
		Quat			   ReadQuat( void );
		int				ReadInteger( void );
		unsigned			ReadUnsigned( void );
		byte				ReadByte( void );
		char				ReadChar( void );
		short				ReadShort( void );
		unsigned short	ReadUnsignedShort( void );
		float				ReadFloat( void );
		double			ReadDouble( void );
		qboolean			ReadBoolean( void );
		str				ReadString( void );
		Event 			ReadEvent( void );
      //
      // ptr methods
      //
		void  			ReadVector( Vector * vec );
		void  			ReadQuat( Quat * quat );
		void				ReadInteger( int * num );
		void  			ReadUnsigned( unsigned * unum);
		void				ReadByte( byte * num );
		void				ReadChar( char * ch );
		void				ReadShort( short * num );
		void           ReadUnsignedShort( unsigned short * num );
		void           ReadFloat( float * num );
		void			   ReadDouble( double * num );
		void  			ReadBoolean( qboolean * bool );
		void  			ReadString( str * string );
		void           ReadObjectPointer( Class ** ptr );
		void           ReadSafePointer( SafePtrBase * ptr );
		void           ReadEvent( Event * ev );

		void				ReadRaw( void *data, size_t size );
		Class				*ReadObject( void );
		Class				*ReadObject( Class *obj );

		void				Create( str &name );
		void				Create( const char *name );
		void				WriteVector( Vector &v );
		void  			WriteQuat( Quat &quat );
		void				WriteInteger( int v );
		void				WriteUnsigned( unsigned v );
		void				WriteByte( byte v );
		void				WriteChar( char v );
		void				WriteShort( short v );
		void				WriteUnsignedShort( unsigned short v );
		void				WriteFloat( float v );
		void				WriteDouble( double v );
		void				WriteBoolean( qboolean v );
		void				WriteRaw( const void *data, size_t size );
		void				WriteString( str &string );
		void				WriteObject( Class *obj );
		void           WriteObjectPointer( Class * ptr );
		void           WriteSafePointer( Class * ptr );
		void           WriteEvent( Event &ev );
	};

inline EXPORT_FROM_DLL void Archiver::Read
   (
   str &name
   )

   {
   Read( name.c_str() );
   }

inline EXPORT_FROM_DLL void Archiver::Create
   (
   str &name
   )

   {
   Create( name.c_str() );
   }

#endif /* archive.h */
