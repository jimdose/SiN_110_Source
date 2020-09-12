//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/gamescript.h                     $
// $Revision:: 11                                                             $
//   $Author:: Jimdose                                                        $
//     $Date:: 10/25/98 11:53p                                                $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/gamescript.h                          $
// 
// 11    10/25/98 11:53p Jimdose
// added EXPORT_TEMPLATE
// 
// 10    10/20/98 10:30p Jimdose
// added crc checking to unarchive
// 
// 9     10/07/98 11:50p Jimdose
// Rewrote archiving functions for savegames
// got rid of type
// 
// 8     9/22/98 1:49a Jimdose
// removed freelabels
// 
// 7     9/21/98 10:15p Markd
// Putting archiving and unarchiving functions in
// 
// 6     7/13/98 5:57p Markd
// Added Setgamescript and Getgamescript methods
// 
// 5     7/11/98 8:43p Markd
// Added SetDialogScript
// 
// 4     7/07/98 11:36p Jimdose
// Added GameScriptMarker
// 
// 3     6/09/98 4:24p Jimdose
// finished implimentation
// 
// 2     6/05/98 2:37p Jimdose
// Created file
// 
// DESCRIPTION:
// Subclass of script that preprocesses labels
//

#ifndef __GAMESCRIPT_H__
#define __GAMESCRIPT_H__

#include "class.h"
#include "script.h"

typedef struct
	{
	scriptmarker_t pos;
	str labelname;
	} script_label_t;

class GameScript;

class EXPORT_FROM_DLL GameScriptMarker : public Class
	{
	public:
		CLASS_PROTOTYPE( GameScriptMarker );

      str               filename;
		scriptmarker_t		scriptmarker;
      virtual void      Archive( Archiver &arc );
      virtual void      Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void GameScriptMarker::Archive
	(
	Archiver &arc
	)

   {
   // Game scripts are unique in that we don't call our superclass to archive it's data.
   // Instead, we only read enough info to then initialize the script ourselves.
   arc.WriteString( filename );
   arc.WriteBoolean( scriptmarker.tokenready );
   arc.WriteInteger( scriptmarker.offset );
   arc.WriteInteger( scriptmarker.line );
   arc.WriteRaw( scriptmarker.token, sizeof( scriptmarker.token ) );
   }

inline EXPORT_FROM_DLL void GameScriptMarker::Unarchive
	(
	Archiver &arc
	)

   {
   // Game scripts are unique in that we don't call our superclass to archive it's data.
   // Instead, we only read enough info to then initialize the script ourselves.
   arc.ReadString( &filename );
   arc.ReadBoolean( &scriptmarker.tokenready );
   arc.ReadInteger( &scriptmarker.offset );
   arc.ReadInteger( &scriptmarker.line );
   arc.ReadRaw( scriptmarker.token, sizeof( scriptmarker.token ) );
   }

#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL Container<script_label_t *>;
#endif

class EXPORT_FROM_DLL GameScript : public Script
	{
	protected:
		Container<script_label_t *>	*labelList;
		GameScript							*sourcescript;
      unsigned                      crc;

	public:
      CLASS_PROTOTYPE( GameScript );

								GameScript();
								GameScript( GameScript *scr );
								~GameScript();
		void					Close( void );
		void					SetSourceScript( GameScript *scr );
		void					LoadFile( const char *filename );

		void					Mark( GameScriptMarker *mark );
		void					Restore( GameScriptMarker *mark );

		void					FreeLabels( void );
		void					FindLabels( void );
		qboolean				labelExists( const char *name );
		qboolean				Goto( const char *name );
      virtual void      Archive( Archiver &arc );
      virtual void      Unarchive( Archiver &arc );
	};

#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL Container<GameScript *>;
#endif

class EXPORT_FROM_DLL ScriptLibrarian : public Class
	{
	protected:
		Container<GameScript *>	scripts;
      str                     dialog_script;
      str                     game_script;

	public:
      CLASS_PROTOTYPE( ScriptLibrarian );

		~ScriptLibrarian();

		void			CloseScripts( void );
		void			SetDialogScript( str scriptname );
		void			SetGameScript( str scriptname );
		const char  *GetGameScript( void );
      GameScript  *FindScript( const char *name );
		GameScript	*GetScript( const char *name );
		qboolean		Goto( GameScript *scr, const char *name );
		qboolean		labelExists( GameScript *scr, const char *name );
      virtual void Archive( Archiver &arc );
      virtual void Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void ScriptLibrarian::Archive
	(
	Archiver &arc
	)
   {
   GameScript * scr;
   int i, num;

   Class::Archive( arc );

   num = scripts.NumObjects();
   arc.WriteInteger( num );
   for ( i = 1; i <= num; i++ )
      {
      scr = scripts.ObjectAt( i );
      arc.WriteObject( scr );
      }
   arc.WriteString( dialog_script );
   arc.WriteString( game_script );
   }

inline EXPORT_FROM_DLL void ScriptLibrarian::Unarchive
	(
	Archiver &arc
	)
   {
   GameScript * scr;
   int i, num;

   Class::Unarchive( arc );

   scripts.FreeObjectList();

   arc.ReadInteger( &num );
   for ( i = 1; i <= num; i++ )
      {
      scr = new GameScript;
      arc.ReadObject( scr );
      scripts.AddObject( scr );
      }

   arc.ReadString( &dialog_script );
   arc.ReadString( &game_script );
   }

extern ScriptLibrarian ScriptLib;

inline EXPORT_FROM_DLL void GameScript::Archive
	(
	Archiver &arc
	)

   {
   // Game scripts are unique in that we don't call our superclass to archive it's data.
   // Instead, we only read enough info to then initialize the script ourselves.
   GameScriptMarker mark;

   arc.WriteUnsigned( crc );

   Mark( &mark );
   arc.WriteObject( &mark );
   }

inline EXPORT_FROM_DLL void GameScript::Unarchive
	(
	Archiver &arc
	)

   {
   // This function is based in part on Restore, so it changes, we must update this function as well.
   // Game scripts are unique in that we don't call our superclass to archive it's data.
   // Instead, we only read enough info to then initialize the script ourselves.
   GameScriptMarker mark;
   unsigned filecrc;
   GameScript *scr;

   arc.ReadUnsigned( &filecrc );
   arc.ReadObject( &mark );

   scr = ScriptLib.FindScript( mark.filename.c_str() );
   if ( scr )
      {
      SetSourceScript( scr );
      }
   else
      {
      LoadFile( mark.filename.c_str() );
      }

   // Error out if CRCs have changed
   if ( filecrc != crc )
      {
      gi.error( "File '%s' has changed from when this savegame was written.  Load cancelled.\n", filename.c_str() );
      }

	RestorePosition( &mark.scriptmarker );
   }

#endif
