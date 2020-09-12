//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/gamescript.cpp                   $
// $Revision:: 15                                                             $
//   $Author:: Jimdose                                                        $
//     $Date:: 10/20/98 10:30p                                                $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/gamescript.cpp                        $
// 
// 15    10/20/98 10:30p Jimdose
// added crc checking to unarchive
// 
// 14    10/10/98 1:28a Jimdose
// CloseScripts clears the game and dialog scripts
// 
// 13    10/07/98 11:49p Jimdose
// Rewrote archiving functions for savegames
// got rid of type
// 
// 12    9/22/98 4:00a Jimdose
// SetSourceScript now copies the sourcescript from the script that is passed
// in.  This guarantees that it works if we pass in a copy of a script.
// 
// 11    9/22/98 1:49a Jimdose
// Fixed bug where GetScript made a copy of the script that it found.  All
// functions that call GetScript were then making copies of the copy, so when
// those scripts checked for labels, they checked their sourcescript's labels
// which were NULL since the sourcescript was itself a copy.  whew!
// 
// 10    9/21/98 10:15p Markd
// Putting archiving and unarchiving functions in
// 
// 9     7/21/98 5:24p Jimdose
// GameScript now initializes type
// 
// 8     7/13/98 5:56p Markd
// Added GetGameScript and SetGameScript
// 
// 7     7/11/98 8:43p Markd
// Added SetDialogScript command
// 
// 6     7/10/98 9:41p Jimdose
// Fixed SetSourceScript so that model scripts don't change types
// 
// 5     7/07/98 11:36p Jimdose
// Added GameScriptMarker
// 
// 4     6/27/98 5:45p Jimdose
// Removed call to FindLabels in Parse.  This caused the script to search for
// labels anytime a new thread started
// 
// 3     6/09/98 4:20p Jimdose
// Multi-file scripting implemented
// 
// 2     6/05/98 2:37p Jimdose
// Created file
// 
// DESCRIPTION:
// Subclass of script that preprocesses labels
//

#include "g_local.h"
#include "script.h"
#include "gamescript.h"

ScriptLibrarian ScriptLib;

CLASS_DECLARATION( Class, GameScriptMarker, NULL );

ResponseDef GameScriptMarker::Responses[] =
	{
		{ NULL, NULL }
	};

CLASS_DECLARATION( Class, ScriptLibrarian, NULL );

ResponseDef ScriptLibrarian::Responses[] =
	{
		{ NULL, NULL }
	};

ScriptLibrarian::~ScriptLibrarian()
	{
	int i;
	int num;

   num = scripts.NumObjects();
   for( i = 1; i <= num; i++ )
      {
      delete scripts.ObjectAt( i );
      }
	}

void ScriptLibrarian::CloseScripts
	(
	void
	)

	{
	int i;
	int num;
	GameScript *scr;

   // Clear out the game and dialog scripts
   SetGameScript( "" );
   SetDialogScript( "" );

   num = scripts.NumObjects();
   for( i = num; i > 0; i-- )
      {
		scr = scripts.ObjectAt( i );
		scripts.RemoveObjectAt( i );
      delete scr;
      }
	}

void ScriptLibrarian::SetDialogScript
	(
   str scriptname
	)
   {
   dialog_script = scriptname;
   }

void ScriptLibrarian::SetGameScript
	(
   str scriptname
	)
   {
   game_script = scriptname;
   }

const char *ScriptLibrarian::GetGameScript
	(
   void
	)
   {
   return game_script.c_str();
   }

GameScript *ScriptLibrarian::FindScript
	(
	const char *name
	)

	{
	int i;
	int num;
	GameScript *scr;
	str n;

	// Convert all forward slashes to back slashes
   n = G_FixSlashes( name );

   num = scripts.NumObjects();
   for( i = 1; i <= num; i++ )
      {
		scr = scripts.ObjectAt( i );

		if ( scr->Filename() == n )
			{
			return scr;
			}
      }

   return NULL;
	}

GameScript *ScriptLibrarian::GetScript
	(
	const char *name
	)

	{
	GameScript *scr;
   str n;

   n = G_FixSlashes( name );
   scr = FindScript( n.c_str() );
   if ( !scr && ( gi.LoadFile( name, NULL, 0 ) != -1 ) )
		{
		scr = new GameScript();
		scr->LoadFile( n.c_str() );
		scripts.AddObject( scr );
		}
	
	return scr;
	}

qboolean	ScriptLibrarian::Goto
	(
	GameScript *scr,
	const char *name
	)

	{
	const char *p;
	GameScript *s;
	str n;

	p = strstr( name, "::" );
	if ( !p )
		{
		return scr->Goto( name );
		}
	else
		{
		n = str( name, 0, p - name );
      if ( n == str( "dialog" ) )
         {
         n = dialog_script;
         }
		s = GetScript( n.c_str() );
		if ( !s )
			{
			return false;
			}

		p += 2;
		if ( s->labelExists( p ) )
			{
			scr->SetSourceScript( s );
			return scr->Goto( p );
			}
		}

	return false;
	}

qboolean	ScriptLibrarian::labelExists
	(
	GameScript *scr,
	const char *name
	)

	{
	const char *p;
	GameScript *s;
	str n;

	p = strstr( name, "::" );
	if ( !p )
		{
		return scr->labelExists( name );
		}
	else
		{
		n = str( name, 0, p - name );
      if ( n == str( "dialog" ) )
         {
         n = dialog_script;
         }
		s = GetScript( n.c_str() );
		if ( !s )
			{
			return false;
			}

		p += 2;
		return s->labelExists( p );
		}

	return false;
	}

CLASS_DECLARATION( Script, GameScript, NULL );

ResponseDef GameScript::Responses[] =
	{
		{ NULL, NULL }
	};

GameScript::GameScript()
	{
	sourcescript = this;
	labelList = NULL;
   crc = 0;
	}

GameScript::GameScript
	(
	GameScript *scr
	)

	{
   crc = 0;
	labelList = NULL;
	SetSourceScript( scr );
	}

GameScript::~GameScript()
	{
	Close();
	}

void GameScript::Close
	(
	void
	)

	{
	FreeLabels();
	Script::Close();
	sourcescript = this;
   crc = 0;
	}

void GameScript::SetSourceScript
	(
	GameScript *scr 
	)

	{
	if ( scr != this )
		{
		Close();

		sourcescript = scr->sourcescript;
      crc = sourcescript->crc;
		Parse( scr->buffer, scr->length, scr->Filename() );
		}
	}

void GameScript::FreeLabels
	(
	void
	)

	{
   int i;
	int num;

	if ( labelList )
		{
		num = labelList->NumObjects();
		for( i = 1; i <= num; i++ )
			{
			delete labelList->ObjectAt( i );
			}

		delete labelList;
		}

	labelList = NULL;
	}

void GameScript::LoadFile
	( 
	const char *name
	)

	{
	str n;

   // Convert all forward slashes to back slashes
   n = G_FixSlashes( name );

   sourcescript = this;
	Script::LoadFile( n.c_str() );
	FindLabels();

   crc = gi.CalcCRC( buffer, length );
	}

void GameScript::FindLabels
	(
   void
   )

   {
   scriptmarker_t mark;
   const char		*tok;
   script_label_t *label;
	int				len;

	FreeLabels();

	labelList = new Container<script_label_t *>;

	MarkPosition( &mark );
   
   Reset();

	while( TokenAvailable( true ) )
		{
      tok = GetToken( true );
      // see if it is a label
      if ( tok )
			{
			len = strlen( tok );
			if ( len && tok[ len - 1 ] == ':' )
				{
				if ( !labelExists( tok ) )
					{
					label = new script_label_t;
         		MarkPosition( &label->pos );
					label->labelname = tok;
					labelList->AddObject( label );
					}
				else
					{
					warning( "FindLabels", "Duplicate labels %s\n", tok );
					}
				}
         }
		}

   RestorePosition( &mark );
   }

EXPORT_FROM_DLL qboolean GameScript::labelExists
	(
	const char *name
	)

	{
   str				labelname;
   script_label_t *label;
   int				i;
	int				num;

	if ( !sourcescript->labelList )
		{
		return false;
		}

   labelname = name;
	if ( !labelname.length() )
		{
		return false;
		}

   if ( labelname[ labelname.length() - 1 ] != ':' )
		{
      labelname += ":";
		}

   num = sourcescript->labelList->NumObjects();
   for( i = 1; i <= num; i++ )
      {
      label = sourcescript->labelList->ObjectAt( i );
      if ( labelname == label->labelname )
			{
         return true;
			}
      }

   return false;
	}

EXPORT_FROM_DLL qboolean GameScript::Goto
	(
	const char *name
	)

	{
   str				labelname;
   script_label_t *label;
   int				i;
	int				num;

	if ( !sourcescript->labelList )
		{
		return false;
		}

   labelname = name;
	if ( !labelname.length() )
		{
		return false;
		}

   if ( labelname[ labelname.length() - 1 ] != ':' )
		{
      labelname += ":";
		}

   num = sourcescript->labelList->NumObjects();
   for( i = 1; i <= num; i++ )
      {
      label = sourcescript->labelList->ObjectAt( i );
      if ( labelname == label->labelname )
         {
         RestorePosition( &label->pos );
         return true;
         }
      }

	return false;
	}

EXPORT_FROM_DLL void GameScript::Mark
	( 
	GameScriptMarker *mark 
	)

	{
	assert( mark );
   assert( sourcescript );

	mark->filename = sourcescript->Filename();
	MarkPosition( &mark->scriptmarker );
	}

EXPORT_FROM_DLL void GameScript::Restore
	(
	GameScriptMarker *mark
	)

	{
   // If we change this function, we must update the unarchive function as well
   GameScript *scr;

	assert( mark );

   scr = ScriptLib.FindScript( mark->filename.c_str() );
   if ( scr )
      {
      SetSourceScript( scr );
      }
   else
      {
      LoadFile( mark->filename.c_str() );
      }

	RestorePosition( &mark->scriptmarker );
	}
