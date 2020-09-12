//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/g_main.cpp                       $
// $Revision:: 178                                                            $
//   $Author:: Jimdose                                                        $
//     $Date:: 8/03/99 7:09p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/g_main.cpp                            $
// 
// 178   8/03/99 7:09p Jimdose
// changes for Sin Arcade
// 
// 177   7/27/99 2:35p Markd
// fixed potential text concatenation bug
// 
// 176   7/26/99 7:05p Markd
// Fixed the say_talk stuff
// 
// 175   7/24/99 6:47p Markd
// Added talk feature and added speech code
// 
// 174   5/19/99 4:57p Markd
// fixed some errors
// 
// 173   5/19/99 11:30a Markd
// Added new camera support 
// 
// 172   3/12/99 4:54p Aldie
// Added CTF_CalcScores
// 
// 171   3/02/99 9:08p Aldie
// Added CTF game code
// 
// 2     2/16/99 4:08p Aldie
// 
// 1     2/11/99 1:38p Aldie
// 
// 169   1/22/99 8:00p Jimdose
// added "showvar" command for inspecting script variables
// 
// 168   12/08/98 7:04p Aldie
// Added setup and shutdown calls to comm for arcade
// 
// 167   11/17/98 6:21p Aldie
// Put a check for DM in the fixbodies
// 
// 166   11/17/98 4:07a Markd
// put in stopsound when changing levels 
// 
// 165   11/15/98 11:31p Markd
// changed default fat rocket setting
// 
// 164   11/15/98 9:02p Jimdose
// added sv_fatrockets
// 
// 163   11/14/98 2:55a Aldie
// Don't update skin in single player in the clientuserinfo.  The player Init
// function will take care of it.
// 
// 162   11/13/98 11:02p Jimdose
// made fov persistant across levels and after zooming in and out
// 
// 161   11/13/98 10:05p Jimdose
// G_SaveClientData is now called when exiting the level, instead of when the
// level is saved.  This should fix the problem of the player keeping objects
// from the previous level when he crosses an episode (when savegames are
// cleared out).
// 
// 160   11/13/98 2:38a Aldie
// Fixed userinfo changed so manumit is preserved in loadgames
// 
// 159   11/11/98 2:56p Aldie
// Fix for deadbody code
// 
// 158   11/10/98 8:05p Aldie
// Fix dead bodies for players changing models
// 
// 157   11/10/98 4:34p Jimdose
// added clearsavegames to level
// 
// 156   11/09/98 1:04a Markd
// made parentmode not LATCHED
// 
// 155   11/09/98 12:55a Jimdose
// added sv_footsteps cvar so that server admins can turn footsteps off
// completely
// added CVAR_USERINFO to parentmode
// 
// 154   11/08/98 10:48p Jimdose
// moved earthquake to level struct
// upped savegame version
// 
// 153   11/08/98 8:09p Aldie
// Upped the savegame version
// 
// 152   11/06/98 10:04p Jimdose
// Added G_AllocDebugLines
// 
// 151   11/06/98 5:32p Jimdose
// added missionfailed and missionfailedtime to level vars
// when a mission has failed or the player is dead in single player, the game
// code immediately shows the loadmenu, preventing them from letting the game
// continue running if they exit the menu
// 
// 150   10/27/98 9:46p Aldie
// Changed training cvar to level.training
// 
// 149   10/27/98 6:52p Jimdose
// changed savegame version
// 
// 148   10/27/98 5:41a Jimdose
// upped the savegame version
// 
// 147   10/27/98 3:43a Aldie
// Removed the "loading" command string
// 
// 146   10/26/98 5:14p Jimdose
// change recalcpaths to ai_recalcpaths
// 
// 145   10/26/98 4:42p Jimdose
// added recalcpaths
// 
// 144   10/26/98 2:17p Aldie
// Added AirClamp
// 
// 143   10/25/98 11:56p Jimdose
// moved playerfrozen from game to level
// 
// 142   10/25/98 10:11p Markd
// made default dialog be mode 2 instead of mode 3
// 
// 141   10/25/98 9:10p Markd
// made dialog variable archived
// 
// 140   10/25/98 6:26p Markd
// Added in no_jc abililty
// 
// 139   10/25/98 6:09p Aldie
// Added training cvar
// 
// 138   10/25/98 4:53a Jimdose
// Increased the savegame version
// 
// 137   10/25/98 12:48a Markd
// changed manumit.def to manumit_pl.def
// 
// 136   10/24/98 6:05p Jimdose
// made waitForPlayer work in change level threads
// upped the savegame version number
// 
// 135   10/24/98 3:34p Markd
// Added loading command, fixed typo
// 
// 134   10/24/98 2:17p Markd
// Put in a loading in exit level
// 
// 133   10/24/98 12:42a Markd
// changed origins to worldorigins where appropriate
// 
// 132   10/23/98 6:46p Aldie
// Archive maxclients
// 
// 131   10/22/98 4:57p Aldie
// Removed blastscale_z value
// 
// 130   10/22/98 3:27a Jimdose
// changed the savegame version
// 
// 129   10/21/98 6:42p Markd
// Added sv_drawtrace
// 
// 128   10/20/98 10:30p Jimdose
// added savegame version
// 
// 127   10/20/98 2:21a Aldie
// Added sv_maplist for map rotation
// 
// 126   10/19/98 9:54p Jimdose
// changed slime variables to lightvolume
// 
// 125   10/19/98 12:07a Jimdose
// made all code use fast checks for inheritance (no text lookups when
// possible)
// isSubclassOf no longer requires ::_classinfo()
// 
// 124   10/18/98 8:42p Jimdose
// Cleaned unnecessary or slow stuff from G_RunFrame 
// 
// 123   10/18/98 3:23a Jimdose
// Added code for timing entities
// 
// 122   10/17/98 12:20a Jimdose
// Save games now archive paths
// Fixed bug due to ReadLevel not freeing the spawned entities
// G_SaveClientData doesn't save data during deathmatch
// 
// 121   10/16/98 1:50a Jimdose
// Added FL_DONTSAVE flag to mark entities that shouldn't be saved to savegames
// Send end level event to clients on level exit
// Added autosave variable to WriteLevel
// 
// 120   10/14/98 11:55p Markd
// put in assert( 0 ) in G_Error
// 
// 119   10/14/98 10:55p Jimdose
// More work on persitant data
// 
// 118   10/14/98 1:17a Jimdose
// Got cross-level persistant info working
// 
// 117   10/11/98 8:51p Jimdose
// Added LoadingServer variable
// 
// 116   10/10/98 1:26a Jimdose
// added G_Precache
// 
// 115   10/08/98 7:18p Jimdose
// Added IP filtering
// Removed noexit and samelevel cvars since they are dmflags
// fixed bug with restarting level
// 
// 114   10/08/98 12:38a Jimdose
// Made savegames work
// 
// 113   9/30/98 5:39p Aldie
// Added showinfo command
// 
// 112   9/26/98 4:44p Aldie
// Added mutant mode
// 
// 111   9/25/98 4:36p Markd
// replaced Event::Find with Event::Exists
// 
// 110   9/24/98 1:49a Jimdose
// Added g_showmem
// 
// 109   9/22/98 3:21p Markd
// put in parentmode lockout for blood and gibs
// 
// 108   9/19/98 5:01p Markd
// took out current_music and fallback_music
// 
// 107   9/19/98 4:33p Jimdose
// added eventlist client command
// 
// 106   9/18/98 5:37p Aldie
// Removed dead code
// 
// 105   9/11/98 2:49p Aldie
// Cleaned up intermission stuff
// 
// 104   9/10/98 8:38p Aldie
// Electrical beam effects
// 
// 103   9/09/98 3:03p Markd
// Fixed deathmatch camera
// 
// 102   9/07/98 8:29p Markd
// Added fulltrace bboxes
// 
// 101   9/03/98 2:49p Aldie
// Changed default of sv_showdamagelocation to 0
// 
// 100   9/02/98 7:46p Aldie
// Added ValidPlayerModels list
// 
// 99    8/31/98 4:44p Markd
// fixed setting on non-blade in demo and non-deathmatch
// 
// 98    8/29/98 9:41p Jimdose
// Made all function names consistantly begin with G_
// Added call info to G_Trace
// 
// 97    8/21/98 5:26p Markd
// Added sv_precache and cl_precache 
// 
// 96    8/19/98 8:49p Aldie
// Added sv_showdamagelocation for kicks
// 
// 95    8/13/98 8:10p Aldie
// Deathmatch score bug
// 
// 94    8/13/98 7:30p Aldie
// New deathmatch scoreboard
// 
// 93    8/08/98 7:29p Aldie
// Added intermissions for deathmatch
// 
// 92    8/07/98 4:20p Aldie
// Fixed say command when command is not known
// 
// 91    8/07/98 2:28p Aldie
// Fixed a bug where dead person could go into idle animation
// 
// 90    8/03/98 7:54p Jimdose
// Added sv_showentnums to show the entity number above any entity
// 
// 89    8/02/98 9:00p Markd
// Merged code 3.17
// 
// 88    7/31/98 8:08p Jimdose
// Script commands now include flags to indicate cheats and console commands
// 
// 87    7/31/98 4:19p Jimdose
// Fixed deathmatch cheats
// 
// 86    7/26/98 9:29a Aldie
// Fixed parameter error on skin checking
// 
// 85    7/26/98 9:12a Aldie
// Fix multiplayer skin lookups for invalid models
// 
// 84    7/26/98 5:32a Markd
// put in rudimentary savegame
// 
// 83    7/25/98 3:12p Aldie
// Initialize showdamage to 0
// 
// 82    7/24/98 10:03p Aldie
// Changed the gibs layout
// 
// 81    7/24/98 6:17p Aldie
// Dialog checking
// 
// 80    7/24/98 4:51p Jimdose
// Bounding boxes no longer show up in deathmatch
// 
// 79    7/24/98 3:47p Aldie
// Don't allow invalid models, skins, etc...
// 
// 78    7/23/98 6:17p Aldie
// Updated damage system and fixed some damage related bugs.  Also put tracers
// back to the way they were, and added gib event to funcscriptmodels
// 
// 77    7/23/98 2:32p Aldie
// Made speed of rocket a tweak cvar
// 
// 76    7/21/98 9:04p Markd
// Added current_mood and fallback mood for music
// 
// 75    7/18/98 5:04p Aldie
// Added showdamage
// 
// 74    7/13/98 4:59p Aldie
// Added dead player bodies with gibbing
// 
// 73    7/11/98 8:58p Markd
// Removed testthread command
// 
// 72    7/11/98 8:42p Markd
// Added testthread command
// 
// 71    7/10/98 6:20a Jimdose
// Added "add" command to add a value to a cvar
// Added G_DrawCSystem for use in debugging orientations
// 
// 70    7/09/98 10:38p Aldie
// Put bodyparts into game init
// 
// 69    7/08/98 12:54p Jimdose
// Made developer c_var global
// 
// 68    7/08/98 12:23p Aldie
// Updated deathmatch scoreboard
// 
// 67    7/03/98 12:01p Aldie
// New userinfo stuff
// 
// 66    7/01/98 7:02p Aldie
// Removed zoom crosshair stuff
// 
// 65    6/23/98 9:54p Jimdose
// Fixed infinite loop bug in G_RunFrame
// 
// 64    6/21/98 6:11p Jimdose
// set level.current_entity in G_ClientThink
// 
// 63    6/19/98 6:37p Aldie
// Removed one of the stat #defines
// 
// 62    6/18/98 8:46p Jimdose
// Added better event error handling
// Added source info to events
// 
// 61    6/15/98 8:04p Markd
// changed max_entities
// 
// 60    6/10/98 9:31p Markd
// Put in infiite loop checking into main loop
// 
// 59    6/09/98 4:19p Jimdose
// Fixed infinite loop bug in G_RunFrame
// 
// 58    5/27/98 5:27a Aldie
// added sv_gibs flag
// 
// 57    5/27/98 5:02a Aldie
// Added gibs and gore
// 
// 56    5/25/98 6:51a Aldie
// Added sv_maxbulletholes
// 
// 55    5/24/98 9:10p Markd
// added another mode to sv_showbboxes
// 
// 54    5/24/98 8:34p Markd
// changed max_entities
// 
// 53    5/24/98 4:48p Jimdose
// Made char *'s const
// 
// 52    5/20/98 7:16p Markd
// Added ClientDrawBoundingBoxes
// 
// 51    5/18/98 8:13p Jimdose
// Renamed Navigator back to PathManager
// 
// 50    5/14/98 10:11p Jimdose
// g_edicts is now initialized to NULL
// 
// 49    5/09/98 8:02p Jimdose
// Added ai commands to Clientcommand.
// Disables Cmd_Say_f
// Added path saving
// 
// 48    5/08/98 2:54p Jimdose
// working on Cmd_Say_f
// 
// 47    5/07/98 10:57p Jimdose
// Fixed gi.error crashing in ClientCommand
// 
// 46    5/05/98 2:43p Aldie
// Added server side surface states
// 
// 45    5/03/98 4:31p Jimdose
// Increased MAX_DEBUG_LINES
// 
// 44    5/02/98 8:37p Aldie
// More console stuff for demos
// 
// 43    4/29/98 5:04p Jimdose
// Fixed gi.error so that it doesn't crash when called from C++
// 
// 42    4/28/98 8:16p Jimdose
// Added checks to ensure that SOLID_BSP objects have models
// 
// 41    4/28/98 6:59p Aldie
// Added server side console buffer
// 
// 40    4/27/98 6:09p Jimdose
// Added debug lines
// 
// 39    4/27/98 5:28p Aldie
// Added server side console states.
// 
// 38    4/23/98 5:00p Jimdose
// Added ai_debugpath
// 
// 37    4/20/98 2:45p Jimdose
// working on ai
// 
// 36    4/18/98 3:01p Jimdose
// Added ai_createnodes and ai_showpath	
// 
// 35    4/16/98 2:03p Jimdose
// edict->s.prevframe is set to -1 (cleared) at the beginning of each frame
// Removed pathmanager
// 
// 34    4/08/98 12:20a Jimdose
// Made viewcommands unavailble without cheats enabled.
// 
// 33    4/07/98 3:48p Aldie
// Added zooming crosshair
// 
// 32    4/06/98 7:10p Aldie
// Added zooming for SniperRifle
// 
// 31    4/06/98 5:42p Jimdose
// G_RunFrame now clears RF_FRAMELERP in renderfx and sets the oldorigin on
// entities
// 
// 30    4/05/98 11:02p Jimdose
// Took out that lastorigin bullshit
// 
// 29    4/05/98 10:34p Jimdose
// Added lastorigin to entity so that we can properly track oldorigin since
// worldorigin may be changed prior to setting oldorigin
// 
// 28    4/05/98 2:56a Jimdose
// fixed bug where deathmatch scores never went away
// 
// 27    4/05/98 1:56a Jimdose
// Fixed bug where oldorigin was being updated with origin instead of
// worldorigin
// 
// 26    4/04/98 6:03p Jimdose
// Got rid of unreferenced variable
// 
// 25    4/03/98 3:36p Jimdose
// Defined draw flags for STAT_LAYOUTS
// 
// 24    4/03/98 1:10p Aldie
// Added consolevar
// 
// 23    4/02/98 4:49p Jimdose
// Added stats and scoreboard
// 
// 22    3/30/98 2:43p Jimdose
// Started on status bar and dm scores
// 
// 21    3/27/98 5:36p Jimdose
// Enabled level changing
// 
// 20    3/27/98 12:05p Aldie
// Added consolecmd
// 
// 19    3/26/98 8:23p Jimdose
// Added coop variable
// made deathmatch work
// changed groundentity to an edict_t *
// Changed assertions when traversing active entities so that it doesn't crash
// out
// 
// 18    3/24/98 4:54p Jimdose
// G_RunFrame now does pre and post physics checks for pending events
// 
// 17    3/23/98 1:31p Jimdose
// Revamped event and command system
// 
// 16    3/15/98 5:06p Aldie
// fixed bug with viewspan and appending models
// 
// 15    3/13/98 10:52a Markd
// fixed bug
// 
// 14    3/13/98 10:48a Markd
// Prepended "models/" to the beginning of viewmodel and viewspawn
// 
// 13    3/12/98 9:49a Markd
// Re-worked viewthing commands
// 
// 12    3/11/98 11:31a Markd
// Re-worked viewthing commands a bunch
// 
// 11    3/07/98 2:04p Markd
// Fixed View* commands
// 
// 10    3/05/98 6:43p Markd
// Added viewthing support
// 
// 9     3/02/98 5:47p Jimdose
// ShutdownGame now frees all entities and paths before exiting
// 
// 8     2/21/98 7:32p Jimdose
// Added checks for cl_oldladders and cl_oldnoclip in ClientUserinfoChanged
// 
// 7     2/21/98 1:14p Jimdose
// Temporarily bumped up maxentities
// Made player commands act as script commands
// Fixed physics loop so that old_origin is only set when RF_BEAM is not set.
// 
// 6     2/17/98 7:01p Jimdose
// gameVars are cleared upon game startup
// 
// 5     2/16/98 2:22p Jimdose
// Added active_edicts and free_edicts for faster entity processing and for
// operations that depend on the order that physics is processed on entities
// (such as binding).
// 
// 4     2/09/98 2:35p Aldie
// Removed const of vec_origin and vec_zero
// 
// 3     2/09/98 11:54a Jimdose
// Made vec_zero and vec_origin const
// 
// 2     2/03/98 11:05a Jimdose
// In process of converting to work with Sin progs
// 
// 1     1/23/98 5:53p Jimdose
// 
// 3     12/30/97 6:04p Jimdose
// Added header text
//
// DESCRIPTION:
// 

#define SAVEGAME_VERSION 13

#include <setjmp.h>
#include "limits.h"
#include "g_local.h"
#include "g_utils.h"
#include "Entity.h"
#include "vector.h"
#include "scriptmaster.h"
#include "navigate.h"
#include "viewthing.h"
#include "console.h"
#include "player.h"
#include "surface.h"
#include "gravpath.h"
#include "deadbody.h"
#include "ctf.h"

Vector vec_origin = "0 0 0";
Vector vec_zero = "0 0 0";

qboolean          LoadingSavegame = false;
qboolean          LoadingServer = false;
game_locals_t		game;
level_locals_t		level;
game_import_t		gi;
game_export_t		globals;

edict_t				*g_edicts = NULL;
edict_t				active_edicts;
edict_t				free_edicts;

netconsole_t      *g_consoles;
netconbuffer_t    *g_conbuffers;
netsurface_t      *g_surfaces;

cvar_t	*developer;
cvar_t	*deathmatch;
cvar_t	*coop;
cvar_t	*dmflags;
cvar_t	*skill;
cvar_t	*fraglimit;
cvar_t	*timelimit;
cvar_t	*password;

cvar_t	*filterban;

cvar_t	*flood_msgs;
cvar_t	*flood_persecond;
cvar_t	*flood_waitdelay;

cvar_t	*maxclients;
cvar_t	*maxentities;
cvar_t   *maxconsoles;
cvar_t   *maxsurfaces;
cvar_t	*g_select_empty;
cvar_t	*g_unlimited_ammo;
cvar_t	*nomonsters;
cvar_t	*dm_respawn;
cvar_t   *dialog;
cvar_t	*precache;
cvar_t   *g_showmem;
cvar_t   *g_timeents;

cvar_t	*sv_maxvelocity;
cvar_t	*sv_gravity;

cvar_t	*dedicated;

cvar_t	*sv_rollspeed;
cvar_t	*sv_rollangle;
cvar_t	*gun_x;
cvar_t	*gun_y;
cvar_t	*gun_z;

cvar_t	*run_pitch;
cvar_t	*run_roll;
cvar_t	*bob_up;
cvar_t	*bob_pitch;
cvar_t	*bob_roll;

cvar_t	*sv_cheats;
cvar_t	*sv_showbboxes;
cvar_t	*sv_showentnums;
cvar_t   *sv_rocketspeed;
cvar_t   *sv_rocketrate;

cvar_t	*sv_stopspeed;
cvar_t	*sv_friction;
cvar_t	*sv_waterfriction;
cvar_t	*sv_waterspeed;

cvar_t   *sv_maxbulletholes;
cvar_t   *sv_maxbloodsplats;
cvar_t   *sv_gore;
cvar_t   *sv_gibs;
cvar_t   *sv_showdamage;
cvar_t   *sv_showdamagelocation;
cvar_t	*sv_traceinfo;
cvar_t	*sv_drawtrace;
cvar_t   *sv_maplist;
cvar_t   *sv_footsteps;
cvar_t   *sv_fatrockets;

cvar_t	*csys_posx;
cvar_t	*csys_posy;
cvar_t	*csys_posz;
cvar_t	*csys_x;
cvar_t	*csys_y;
cvar_t	*csys_z;
cvar_t	*csys_draw;

cvar_t   *parentmode;

int		sv_numtraces;

usercmd_t *current_ucmd;

void     G_AllocDebugLines( void );
void		G_ClientDrawBoundingBoxes( void );
void		( *ServerError )( const char *fmt, ... );
char		G_ErrorMessage[ 1024 ];
jmp_buf	G_AbortGame;

#ifdef SIN_ARCADE
void G_CheckFirstPlace( void );
void G_DrawFirstPlace( void );
#endif

/*
===============
G_Error

Abort the server with a game error
===============
*/
void G_Error
	(
	const char *fmt,
	...
	)

	{
	va_list	argptr;
	
	va_start( argptr, fmt );
	vsprintf( G_ErrorMessage, fmt, argptr );
	va_end( argptr );

   assert( 0 );

	longjmp( G_AbortGame, -1 );
	}

/*
===============
G_ExitWithError

Calls the server's error function with the last error that occurred.
Should only be called after a setjmp( G_AbortGame ) call
===============
*/
void G_ExitWithError
	(
	void
	)
	
	{
	ServerError( G_ErrorMessage );
	}

/*
=================
G_ShutdownGame

Frees up any resources
=================
*/
void G_ShutdownGame
	(
	void
	)

	{
	gi.dprintf ("==== ShutdownGame ====\n");

	// If we get an error, call the server's error function
	if ( setjmp( G_AbortGame ) )
		{
		G_ExitWithError();
		}

   G_LevelShutdown();

   gi.FreeTags (TAG_GAME);
	}

/*
============
G_InitGame

This will be called when the dll is first loaded, which
only happens when a new game is begun
============
*/
void G_InitGame
   (
   void
   )

	{
	gi.dprintf ("==== InitGame ====\n");

	// Install our own error handler, since we can't
	// call the EXE's handler from within a C++ class
	ServerError = gi.error;
	gi.error = G_Error;

	// If we get an error, call the server's error function
	if ( setjmp( G_AbortGame ) )
		{
		G_ExitWithError();
		}

	// initialize the game variables
	gameVars.ClearList();

	gun_x = gi.cvar ("gun_x", "0", 0);
	gun_y = gi.cvar ("gun_y", "0", 0);
	gun_z = gi.cvar ("gun_z", "0", 0);

	developer			= gi.cvar( "developer", "0", 0 );
	precache 			= gi.cvar( "sv_precache", "1", 0 );

	//FIXME: sv_ prefix is wrong for these
	sv_rollspeed		    = gi.cvar ("sv_rollspeed", "200", 0);
	sv_rollangle		    = gi.cvar ("sv_rollangle", "2", 0);
	sv_maxvelocity		    = gi.cvar ("sv_maxvelocity", "2000", 0);
	sv_gravity			    = gi.cvar ("sv_gravity", "800", 0);
   sv_maxbulletholes     = gi.cvar ("sv_maxbulletholes", "32", 0);
   sv_maxbloodsplats     = gi.cvar ("sv_maxbloodspats", "5", 0);
   sv_gore               = gi.cvar ("sv_gore", "1", 0);
   sv_gibs               = gi.cvar ("sv_gibs", "1", 0);
   sv_showdamage         = gi.cvar ("sv_showdetaildamage", "0", 0);
   sv_showdamagelocation = gi.cvar ("sv_showdamagelocation", "0", 0);

	// noset vars
	dedicated			= gi.cvar ("dedicated", "0", CVAR_NOSET);

	// latched vars
	sv_cheats			= gi.cvar ("cheats", "0", CVAR_SERVERINFO|CVAR_LATCH);
	deathmatch			= gi.cvar ("deathmatch", "0", CVAR_SERVERINFO|CVAR_LATCH);
   coop					= gi.cvar ("coop", "0", CVAR_SERVERINFO|CVAR_LATCH);
	skill					= gi.cvar ("skill", "1", CVAR_SERVERINFO|CVAR_LATCH);
	
	maxclients			= gi.cvar ("maxclients", "4", CVAR_SERVERINFO | CVAR_LATCH | CVAR_ARCHIVE );
	maxentities			= gi.cvar ("maxentities", "1024", CVAR_LATCH);
   maxconsoles       = gi.cvar ("maxconsoles", "32", CVAR_LATCH);
   maxsurfaces       = gi.cvar ("maxsurfaces", "1024", CVAR_LATCH);

	// flood control
	flood_msgs        = gi.cvar ("flood_msgs", "4", 0);
	flood_persecond   = gi.cvar ("flood_persecond", "4", 0);
	flood_waitdelay   = gi.cvar ("flood_waitdelay", "10", 0);

   // change anytime vars
	password          = gi.cvar ("password", "", CVAR_USERINFO);
	filterban         = gi.cvar ("filterban", "1", 0);
#ifdef SIN_ARCADE
	dmflags				= gi.cvar ("dmflags", "0", CVAR_SERVERINFO|CVAR_ARCHIVE);
	fraglimit			= gi.cvar ("fraglimit", "0", CVAR_SERVERINFO|CVAR_ARCHIVE);
	timelimit			= gi.cvar ("timelimit", "0", CVAR_SERVERINFO|CVAR_ARCHIVE);
#else
	dmflags				= gi.cvar ("dmflags", "0", CVAR_SERVERINFO);
	fraglimit			= gi.cvar ("fraglimit", "0", CVAR_SERVERINFO);
	timelimit			= gi.cvar ("timelimit", "0", CVAR_SERVERINFO);
#endif
   // CTF
   capturelimit      = gi.cvar ("capturelimit", "0", CVAR_SERVERINFO);
	g_select_empty		= gi.cvar ("g_select_empty", "0", CVAR_ARCHIVE);
	g_unlimited_ammo	= gi.cvar ("g_unlimited_ammo", "0", CVAR_SERVERINFO);
   g_showmem         = gi.cvar ("g_showmem", "0", 0 );
   g_timeents        = gi.cvar ("g_timeents", "0", 0 );
	dm_respawn			= gi.cvar ("dm_respawn", "2", CVAR_SERVERINFO);
	nomonsters			= gi.cvar ("nomonsters", "0", CVAR_SERVERINFO);
   dialog   			= gi.cvar ("dialog", "2", CVAR_SERVERINFO | CVAR_ARCHIVE );

	run_pitch			= gi.cvar ("run_pitch", "0.002", 0);
	run_roll				= gi.cvar ("run_roll", "0.005", 0);
	bob_up				= gi.cvar ("bob_up", "0.005", 0);
	bob_pitch			= gi.cvar ("bob_pitch", "0.002", 0);
	bob_roll				= gi.cvar ("bob_roll", "0.002", 0);

	bob_roll				= gi.cvar ("bob_roll", "0.002", 0);

	csys_posx			= gi.cvar ("csys_posx",	"0", 0);
	csys_posy			= gi.cvar ("csys_posy",	"0", 0);
	csys_posz			= gi.cvar ("csys_posz",	"0", 0);
	csys_x				= gi.cvar ("csys_x",		"0", 0);
	csys_y				= gi.cvar ("csys_y",		"0", 0);
	csys_z				= gi.cvar ("csys_z",		"0", 0);
	csys_draw			= gi.cvar ("csys_draw", "0", 0);

	sv_traceinfo		= gi.cvar ("sv_traceinfo", "0", 0);
	sv_drawtrace		= gi.cvar ("sv_drawtrace", "0", 0);
		
   // debug stuff
	sv_showbboxes		= gi.cvar ("sv_showbboxes", "0", 0);
	sv_showentnums		= gi.cvar ("sv_showentnums", "0", 0);
   sv_rocketspeed    = gi.cvar ("sv_rocketspeed", "300", 0);
   sv_rocketrate     = gi.cvar ("sv_rocketrate", "1.2", 0);

	sv_friction			= gi.cvar ("sv_friction", "4", CVAR_SERVERINFO);
	sv_stopspeed		= gi.cvar ("sv_stopspeed", "100", CVAR_SERVERINFO);
	sv_waterfriction	= gi.cvar ("sv_waterfriction", "1", CVAR_SERVERINFO);
	sv_waterspeed		= gi.cvar ("sv_waterspeed", "400", CVAR_SERVERINFO);
   sv_maplist        = gi.cvar ("sv_maplist", "", CVAR_SERVERINFO|CVAR_ARCHIVE);
   sv_footsteps      = gi.cvar ("sv_footsteps", "1", CVAR_SERVERINFO|CVAR_ARCHIVE);

   if ( deathmatch->value )
      {
      sv_fatrockets = gi.cvar ("sv_fatrockets", "1", CVAR_SERVERINFO);
      }
   else
      {
      sv_fatrockets = gi.cvar ("sv_fatrockets", "1", CVAR_SERVERINFO);
      }

   parentmode        = gi.cvar ("parentmode", "0", CVAR_USERINFO|CVAR_SERVERINFO|CVAR_ARCHIVE);

	CTF_Init();

	G_InitEvents();
	sv_numtraces = 0;

	game.maxentities = maxentities->value;
	if (maxclients->value * 8 > game.maxentities)
		{
		game.maxentities = maxclients->value * 8;
		}
	game.maxclients = maxclients->value;
   game.maxconsoles = maxconsoles->value;
   game.maxsurfaces = maxsurfaces->value;
   G_AllocGameData();
   }

void G_AllocGameData
   (
   void 
   )

   {
   int i;

	gi.FreeTags( TAG_GAME );

   // Initialize debug lines
	G_AllocDebugLines();

	// initialize all entities for this game
	g_edicts =  ( edict_t * )gi.TagMalloc (game.maxentities * sizeof(g_edicts[0]), TAG_GAME);
	globals.edicts = g_edicts;
	globals.max_edicts = game.maxentities;

	// Add all the edicts to the free list
	LL_Reset( &free_edicts, next, prev );
	LL_Reset( &active_edicts, next, prev );
	for( i = 0; i < game.maxentities; i++ )
		{
		LL_Add( &free_edicts, &g_edicts[ i ], next, prev );
		}

	// initialize all clients for this game
	game.clients = ( gclient_t * )gi.TagMalloc (game.maxclients * sizeof(game.clients[0]), TAG_GAME);
	memset( game.clients, 0, game.maxclients * sizeof( game.clients[ 0 ] ) );
	for (i=0 ; i<game.maxclients ; i++)
		{
     	// set client fields on player ents
		g_edicts[ i + 1 ].client = game.clients + i;

		G_InitClientPersistant (&game.clients[i]);
		G_InitClientResp (&game.clients[i]);
		}
	globals.num_edicts = game.maxclients+1;

   // initialize all the consoles
   g_consoles = (netconsole_t *)gi.TagMalloc (game.maxconsoles * sizeof(g_consoles[0]), TAG_GAME);
   globals.consoles = g_consoles;
   globals.max_consoles = game.maxconsoles;
   globals.num_consoles = 0;
   g_conbuffers = (netconbuffer_t *)gi.TagMalloc (game.maxconsoles * sizeof(g_conbuffers[0]), TAG_GAME);
   globals.conbuffers = g_conbuffers;

   // initialize the surfaces
   g_surfaces = (netsurface_t *)gi.TagMalloc (game.maxsurfaces * sizeof(g_surfaces[0]), TAG_GAME);
   globals.surfaces = g_surfaces;
   globals.max_surfaces = game.maxsurfaces;
   globals.num_surfaces = 0;
   }

void ReadGame
   (
   const char *name
   )

	{
   str mapname;
   str spawnpoint;
	Archiver arc;
   int version;
   int savegame_version;

   LoadingServer = true;

   // Get rid of anything left over from the last level
   G_LevelShutdown();

	arc.Read( name );

   arc.ReadInteger( &version );
   if ( version < GAME_API_VERSION )
      {
      gi.error( "Savegame from an older version (%d) of Sin.\n", version );
      }
   else if ( version > GAME_API_VERSION )
      {
      gi.error( "Savegame from version %d of Sin.\n", version );
      }

   arc.ReadInteger( &savegame_version );
   if ( savegame_version < SAVEGAME_VERSION )
      {
      gi.error( "Savegame from an older version (%d) of Sin.\n", version );
      }
   else if ( savegame_version > SAVEGAME_VERSION )
      {
      gi.error( "Savegame from version %d of Sin.\n", version );
      }

   // Read the map name (needed by G_MapInit)
   arc.ReadString( &mapname );

   // Set up for a new map
   G_MapInit( mapname.c_str() );

   arc.ReadObject( &PersistantData );
   arc.ReadObject( &game );
	arc.ReadObject( &gameVars );

   arc.Close();
   }

void G_ReadGame
   (
   const char *name
   )

	{
	// If we get an error, call the server's error function
	if ( setjmp( G_AbortGame ) )
		{
		G_ExitWithError();
		}

   ReadGame( name );
   }

/*
============
WriteGame

This will be called whenever the game goes to a new level,
and when the user explicitly saves the game.

Game information include cross level data, like multi level
triggers, help computer info, and all client states.

A single player death will automatically restore from the
last save position.
============
*/

void WriteGame
   (
   const char *name,
   qboolean autosave
   )

	{
   Archiver arc;

   game.autosaved = autosave;

   arc.Create( name );

   arc.WriteInteger( GAME_API_VERSION );
   arc.WriteInteger( SAVEGAME_VERSION );

   arc.WriteString( level.mapname );

   arc.WriteObject( &PersistantData );
   arc.WriteObject( &game );
   arc.WriteObject( &gameVars );

	arc.Close();

   game.autosaved = false;
   }

void G_WriteGame
   (
   const char *name,
   qboolean autosave
   )

	{
	// If we get an error, call the server's error function
	if ( setjmp( G_AbortGame ) )
		{
		G_ExitWithError();
		}

   WriteGame( name, autosave );
   }

/*
==============
G_WriteClient
==============
*/
void G_WriteClient
   (
   Archiver &arc,
   gclient_t *client
   )

   {
   arc.WriteRaw( client, sizeof( gclient_t ) );
   }

/*
==============
G_ReadClient
==============
*/
void G_ReadClient
   (
   Archiver &arc,
   gclient_t *client
   )

   {
   arc.ReadRaw( client, sizeof( gclient_t ) );
   }

/*
==================
G_SaveClientData

Some information that should be persistant, like health, 
is stored in the Entity structure, so it needs to be mirrored 
out to the client structure before all the edicts are wiped.
==================
*/
void G_SaveClientData
   (
   void
   )

   {
	int		i;
	edict_t	*ent;

   PersistantData.Reset();

   if ( deathmatch->value )
      {
      return;
      }

	for( i = 0; i < game.maxclients; i++ )
   	{
		ent = &g_edicts[ 1 + i ];
		if ( !ent->inuse || !ent->entity )
         {
			continue;
         }

      PersistantData.AddEnt( ent->entity );
	   }
   }

/*
=================
WriteLevel

=================
*/
void WriteLevel
   (
   const char *filename,
   qboolean autosave
   )

   {
	int		i;
   int      num;
	edict_t	*edict;
   Archiver arc;

   if ( autosave )
      {
	   for( i = 0; i < game.maxclients; i++ )
   	   {
		   edict = &g_edicts[ 1 + i ];
		   if ( !edict->inuse && !edict->entity )
            {
			   continue;
            }

         delete edict->entity;
	      }
      }

   arc.Create( filename );

   // write out the version number
   arc.WriteInteger( GAME_API_VERSION );
   arc.WriteInteger( SAVEGAME_VERSION );

   // Write out the pending events.  These are written first in case 
   // later objects need to post events when reading the archive.
   G_ArchiveEvents( arc );

	// write out level_locals_t
   arc.WriteObject( &level );

   // write out consoles
   arc.WriteObject( &consoleManager );

   // write out script librarian
   arc.WriteObject( &ScriptLib );

   // write out gravity paths
   arc.WriteObject( &gravPathManager );

   // write out paths
   arc.WriteObject( &PathManager );

   // write out script controller
   arc.WriteObject( &Director );

   // write out surface manager
   arc.WriteObject( &surfaceManager );

   // write out Viewmodel manager (for debugging only)
   arc.WriteObject( &Viewmodel );

	// count the entities
   num = 0;
	for( i = 0; i < globals.num_edicts; i++ )
	   {
		edict = &g_edicts[ i ];
		if ( edict->inuse && edict->entity && !( edict->entity->flags & FL_DONTSAVE ) )
         {
			num++;
         }
      }

	// write out all the entities
   arc.WriteInteger( globals.num_edicts );
   arc.WriteInteger( num );
	for( i = 0; i < globals.num_edicts; i++ )
	   {
		edict = &g_edicts[ i ];
		if ( !edict->inuse || !edict->entity || ( edict->entity->flags & FL_DONTSAVE ) )
         {
			continue;
         }

      arc.WriteObject( edict->entity );
	   }

   arc.Close();
   }

void G_WriteLevel
   (
   const char *filename,
   qboolean autosave
   )

	{
	// If we get an error, call the server's error function
	if ( setjmp( G_AbortGame ) )
		{
		G_ExitWithError();
		}

   WriteLevel( filename, autosave );
   }

/*
=================
ReadLevel

SpawnEntities will already have been called on the
level the same way it was when the level was saved.

That is necessary to get the baselines set up identically.

The server will have cleared all of the world links before
calling ReadLevel.

No clients are connected yet.
=================
*/
void ReadLevel
   (
   const char *filename
   )

   {
	int		i;
   int      num;
   Archiver arc;
   int      version;
   int      savegame_version;

   LoadingSavegame = true;

   // Get rid of anything left over from the last level
   G_LevelShutdown();
   G_ResetEdicts();

	arc.Read( filename );

   // read the version number
   arc.ReadInteger( &version );
   if ( version < GAME_API_VERSION )
      {
      gi.error( "Savegame from an older version (%d) of Sin.\n", version );
      }
   else if ( version > GAME_API_VERSION )
      {
      gi.error( "Savegame from version %d of Sin.\n", version );
      }

   arc.ReadInteger( &savegame_version );
   if ( savegame_version < SAVEGAME_VERSION )
      {
      gi.error( "Savegame from an older version (%d) of Sin.\n", version );
      }
   else if ( savegame_version > SAVEGAME_VERSION )
      {
      gi.error( "Savegame from version %d of Sin.\n", version );
      }

   // Read in the pending events.  These are read in first in case 
   // later objects need to post events.
   G_UnarchiveEvents( arc );

	// read level_locals_t
   arc.ReadObject( &level );

   // read consoles
   arc.ReadObject( &consoleManager );

   // read script librarian
   arc.ReadObject( &ScriptLib );

   // read gravity paths
   arc.ReadObject( &gravPathManager );

   // read paths
   arc.ReadObject( &PathManager );

   // read script controller
   arc.ReadObject( &Director );

   // read surface manager
   arc.ReadObject( &surfaceManager );

   // read Viewmodel manager (for debugging only)
   arc.ReadObject( &Viewmodel );

	// read all the entities
   arc.ReadInteger( &globals.num_edicts );
   arc.ReadInteger( &num );
	for( i = 0; i < num; i++ )
	   {
      arc.ReadObject();
	   }

   arc.Close();

   // call the precache scripts
   G_Precache();

   LoadingSavegame = false;
   }

void G_ReadLevel
   (
   const char *filename
   )

	{
	// If we get an error, call the server's error function
	if ( setjmp( G_AbortGame ) )
		{
		G_ExitWithError();
		}

   ReadLevel( filename );
   }

/*
=================
GetGameAPI

Returns a pointer to the structure with all entry points
and global variables
=================
*/
game_export_t *GetGameAPI
   (
   game_import_t *import
   )

	{
	gi = *import;

	globals.apiversion				= GAME_API_VERSION;
	globals.Init						= G_InitGame;
	globals.Shutdown					= G_ShutdownGame;
	globals.SpawnEntities			= G_SpawnEntities;
   globals.CreateSurfaces        = CreateSurfaces;

	globals.WriteGame					= G_WriteGame;
	globals.ReadGame					= G_ReadGame;
	globals.WriteLevel				= G_WriteLevel;
	globals.ReadLevel					= G_ReadLevel;

	globals.ClientThink				= G_ClientThink;
	globals.ClientConnect			= G_ClientConnect;
	globals.ClientUserinfoChanged = G_ClientUserinfoChanged;
	globals.ClientDisconnect		= G_ClientDisconnect;
	globals.ClientBegin				= G_ClientBegin;
	globals.ClientCommand			= G_ClientCommand;

	globals.RunFrame					= G_RunFrame;
	globals.ServerCommand         = G_ServerCommand;

	globals.edict_size		= sizeof(edict_t);
   globals.console_size		= sizeof(netconsole_t);
   globals.conbuffer_size	= sizeof(netconbuffer_t);
   globals.surface_size		= sizeof(netsurface_t);

	return &globals;
	}

#ifndef GAME_HARD_LINKED
// this is only here so the functions in q_shared.c and q_shwin.c can link
void Sys_Error
   (
   const char *error,
   ...
   )

	{
	va_list		argptr;
	char		text[1024];

	va_start (argptr, error);
	vsprintf (text, error, argptr);
	va_end (argptr);

	gi.error (ERR_FATAL, "%s", text);
	}

void Com_Printf
   (
   const char *msg,
   ...
   )

	{
	va_list		argptr;
	char		text[1024];

	va_start (argptr, msg);
	vsprintf (text, msg, argptr);
	va_end (argptr);

	gi.dprintf ("%s", text);
	}

#endif

//======================================================================


/*
=================
G_ClientEndServerFrames
=================
*/
void G_ClientEndServerFrames 
	(
	void
	)

	{
	int		i;
	edict_t	*ent;

	// calc the player views now that all pushing
	// and damage has been added
	for( i = 0; i < maxclients->value; i++ )
		{
		ent = g_edicts + 1 + i;
		if ( !ent->inuse || !ent->client || !ent->entity )
			{
			continue;
			}

		ent->entity->ProcessEvent( EV_ClientEndFrame );
		}
	}

/*
=================
G_EndDMLevel

The timelimit or fraglimit has been exceeded
=================
*/
void G_EndDMLevel 
	(
	void
	)

   {
	int                  num;
	TriggerChangeLevel   *ent;
   char                 *s, *t, *f;
	static const char    *seps = " ,\n\r";

#ifdef SIN_ARCADE
   G_DrawFirstPlace();
#endif

   // stay on same level flag
	if ( DM_FLAG( DF_SAME_LEVEL ) )
		{
		G_BeginIntermission( level.mapname.c_str() );
	   return;
      }
	
 	// see if it's in the map list
	if ( *sv_maplist->string )
      {
		s = strdup(sv_maplist->string);
		f = NULL;
		t = strtok( s, seps );
		while ( t != NULL )
         {
			if ( !stricmp( t, level.mapname.c_str() ) )
            {
				// it's in the list, go to the next one
				t = strtok( NULL, seps );
				if ( t == NULL ) 
               { // end of list, go to first one
					if ( f == NULL ) // there isn't a first one, same level
						G_BeginIntermission( level.mapname.c_str() );
					else
						G_BeginIntermission( f );
				   }
            else
               {
					G_BeginIntermission( t );
               }
				free(s);
				return;
			}
			if (!f)
            {
            f = t;
            }
			t = strtok(NULL, seps);
		}
		free(s);
	}

   if ( !level.nextmap.length() )
		{
		// search for a changelevel
		num = G_FindClass( 0, "target_changelevel" );
		if ( !num )
			{
			// the map designer didn't include a changelevel,
			// so go back to the same level
			G_BeginIntermission( level.mapname.c_str() );
			}
		else
			{
			ent = ( TriggerChangeLevel * )G_GetEntity( num );
			G_BeginIntermission( ent->Map() );
			}
		}	
   }

/*
=================
G_CheckDMRules
=================
*/
void G_CheckDMRules 
	(
	void
	)

	{
	int			i;
	gclient_t	*cl;

	if ( level.intermissiontime )
		{
		return;
		}

	if ( !deathmatch->value )
		{
		return;
		}

	if ( timelimit->value )
		{
		if ( level.time >= timelimit->value * 60 )
			{
			gi.bprintf( PRINT_HIGH, "Timelimit hit.\n" );
			G_EndDMLevel();
			return;
			}
		}

	      // CTF
	if ( ctf->value )
		{
		if ( CTF_CheckRules() ) 
			{
			gi.bprintf( PRINT_HIGH, "Capturelimit hit.\n" );
			G_EndDMLevel ();
         return;
			}
      }

	if ( fraglimit->value )
		{
      for( i = 0; i < maxclients->value; i++ )
			{
			cl = game.clients + i;
			if ( !g_edicts[ i + 1 ].inuse )
				{
				continue;
				}

			if ( cl->resp.score >= fraglimit->value )
				{
				gi.bprintf( PRINT_HIGH, "Fraglimit hit.\n" );
				G_EndDMLevel();
				return;
				}
			}
		}
	}

void G_MoveClientToIntermission
   (
   Entity *ent
   )

   {
   // Display the scores for the client
	if ( deathmatch->value || coop->value )
	   {
		ent->client->showinfo = true;
		G_DeathmatchScoreboardMessage( ent, NULL );
		gi.unicast( ent->edict, true );
	   }
   }

void G_BeginIntermission
	(
	const char *map
	)
	
	{
   edict_t	   *client;
   Entity      *ent;
   Entity      *path;
   int         i,num;
   Event       *event, event2;

	assert( map );
   if ( !map )
      {
      gi.dprintf( "G_BeginIntermission : Null map name\n" );
      return;
      }

   if ( level.missionfailed )
      {
      // don't allow map changes when a mission has failed
      return;
      }

	if ( level.intermissiontime )
		{
		// already activated
		return;
		}

	level.intermissiontime = level.time;

   if ( level.clearsavegames && ( map[ 0 ] != '*' ) )
      {
      level.nextmap = str( "*" ) + map;
      }
   else
      {
      level.nextmap = map;
      }

   level.clearsavegames = false;

   level.exitintermission = !( deathmatch->value || coop->value );
	
   // find an intermission spot
   num = G_FindClass( 0, "info_player_intermission" );

	if ( ctf->value )
		CTF_CalcScores();

   // Only do the camera stuff if the node exists.
   if ( num )
      {
      ent = G_GetEntity( num );
	   SetCamera( ent );
      event = new Event( EV_Camera_Orbit );

      // Find the end node
      num = G_FindTarget( 0, "endnode1" );      
      if ( num )
         {
         path = G_GetEntity( num );
         event->AddEntity( path );
         ent->ProcessEvent( event );
         event = new Event( EV_Camera_JumpCut );
         ent->ProcessEvent( event );
         }
      }

   // Display scores for all the clients
	for( i = 0; i < maxclients->value; i++ )
      {
      client = g_edicts + 1 + i;
		
      if (!client->inuse)
			continue;
		
      ent = G_GetEntity( client->s.number );
      G_MoveClientToIntermission( ent );
      }

   // tell the script that the player's not ready so that if we return to this map,
   // we can do something about it.
   Director.PlayerNotReady();
	}

/*
=============
G_ExitLevel
=============
*/
void G_ExitLevel
   (
   void
   )

	{
	char command[ 256 ];
   int j;
   edict_t *ent;

   // kill the sounds
	Com_sprintf( command, sizeof( command ), "stopsound\n" );
	gi.AddCommandString( command );

	Com_sprintf( command, sizeof( command ), "gamemap \"%s\"\n", level.nextmap.c_str() );
	gi.AddCommandString( command );

	level.nextmap = "";

	level.exitintermission = 0;
	level.intermissiontime = 0;

	CTF_Init();

   G_SaveClientData();

   // Tell all the client that the level is done
	for( j = 1; j <= game.maxclients; j++ )
		{
		ent = &g_edicts[ j ];
		if ( !ent->inuse || !ent->entity )
			{
			continue;
			}

      ent->entity->ProcessEvent( EV_Player_EndLevel );
      }

	G_ClientEndServerFrames();

   // tell the script that the player's not ready so that if we return to this map,
   // we can do something about it.
   Director.PlayerNotReady();
	}

void G_DrawCSystem
	(
	void
	)

	{
	Vector pos;
	Vector ang;
	Vector f;
	Vector r;
	Vector u;
	Vector v;

	pos.x = csys_posx->value;
	pos.y = csys_posy->value;
	pos.z = csys_posz->value;

	ang.x = csys_x->value;
	ang.y = csys_y->value;
	ang.z = csys_z->value;

	ang.AngleVectors( &f, &r, &u );

	G_DebugLine( pos, pos + f * 48, 1.0, 0, 0, 1 );
	G_DebugLine( pos, pos + r * 48, 0, 1.0, 0, 1 );
	G_DebugLine( pos, pos + u * 48, 0, 0, 1.0, 1 );
	}

/*
================
G_RunFrame

Advances the world by 0.1 seconds
================
*/
void G_RunFrame
   (
   void
   )

	{
	edict_t	*edict;
	Entity	*ent;
   int		num;
	qboolean showentnums;
   int      start;
   int      end;

	// If we get an error, call the server's error function
	if ( setjmp( G_AbortGame ) )
		{
		G_ExitWithError();
		}

	level.framenum++;
	level.time = level.framenum * FRAMETIME;

   if ( g_showmem->value )
      {
      DisplayMemoryUsage();
      }

	// exit intermissions
	if ( level.exitintermission )
		{
		G_ExitLevel();
		return;
		}

   // if the player in the server and the mission has failed, show the loadmenu
   if ( g_edicts[ 1 ].inuse && level.missionfailed && ( level.missionfailedtime < level.time ) )
      {
	   // restart the entire server
      gi.AddCommandString( "con_clearfade\n" );
	   gi.AddCommandString( "menu_loadgame\n" );
      return;
      }

	path_checksthisframe = 0;

	// Reset debug lines
	G_InitDebugLines();

	// testing coordinate system
	if ( csys_draw->value )
		{
		G_DrawCSystem();
		}

	PathManager.ShowNodes();

	// don't show entnums during deathmatch
	showentnums = ( sv_showentnums->value && ( !deathmatch->value || sv_cheats->value ) );

	// Process most of the events before the physics are run
	// so that we can affect the physics immediately
	G_ProcessPendingEvents();

	//
	// treat each object in turn
	//
	for( edict = active_edicts.next, num = 0; edict != &active_edicts; edict = level.next_edict, num++ )
		{
		assert( edict );
		assert( edict->inuse );
		assert( edict->entity );

		level.next_edict = edict->next;

		// Paranoia - It's a way of life
		assert( num <= MAX_EDICTS );
      if ( num > MAX_EDICTS )
         {
   		gi.dprintf( "Possible infinite loop in G_RunFrame.\n");
         break;
         }

		ent = edict->entity;
		level.current_entity = ent;

      if ( g_timeents->value )
         {
         start = G_Milliseconds();
		   G_RunEntity( ent );
         end = G_Milliseconds();

         if ( g_timeents->value <= ( end - start ) )
            {
            G_DebugPrintf( "%d: '%s'(%d) : %d\n", level.framenum, ent->targetname.c_str(), ent->entnum, end - start );
            }
         }
      else
         {
		   G_RunEntity( ent );
         }

		if ( showentnums )
			{
			G_DrawDebugNumber( ent->worldorigin + Vector( 0, 0, ent->maxs.z + 2 ), ent->entnum, 2, 1, 1, 0 );
			}
		}

	// Process any pending events that got posted during the physics code.
	G_ProcessPendingEvents();

	// see if it is time to end a deathmatch
	G_CheckDMRules();

	// build the playerstate_t structures for all players
	G_ClientEndServerFrames();

   // see if we should draw the bounding boxes
   G_ClientDrawBoundingBoxes();

	// show how many traces the game code is doing
	if ( sv_traceinfo->value )
		{
		if ( sv_traceinfo->value == 3 )
			{
			G_DebugPrintf( "%0.1f : Total traces %d\n", level.time, sv_numtraces );
			}
		else
			{
			gi.dprintf( "%0.1f : Total traces %d\n", level.time, sv_numtraces );
			}
		}

	// reset out count of the number of game traces
	sv_numtraces = 0;

#ifdef SIN_ARCADE
   G_CheckFirstPlace();
#endif
	}

void G_ClientThink
   (
   edict_t *ent,
   usercmd_t *ucmd
   )

	{
	// If we get an error, call the server's error function
	if ( setjmp( G_AbortGame ) )
		{
		G_ExitWithError();
		}

	if ( ent->entity )
		{
		current_ucmd = ucmd;
		level.current_entity = ent->entity;
		ent->entity->ProcessEvent( EV_ClientMove );
      current_ucmd = NULL;
		}
	}

/*
===========
G_PutClientInServer

Called when a player connects to a server
============
*/
void G_PutClientInServer 
	(
	edict_t *ent
	)

	{
	if ( !ent->entity )
		{
	   G_InitSpawnArguments();
	   G_SetSpawnArg( "classname", "player" );

	   game.force_entnum = true;
	   game.spawn_entnum = ent->s.number;
	   G_CallSpawn();
	   game.force_entnum = false;
      
      if ( ent->entity && ent->entity->isSubclassOf( Player ) )
         {
         ( ( Player * )ent->entity )->Init();
			
			// Initialize the player to CTF 
			if ( ctf->value )
				( ( Player * )ent->entity )->InitCTF();
         }
      }
	}

/*
===========
G_ClientBegin

called when a client has finished connecting, and is ready
to be placed into the game.  This will happen every level load.
============
*/
void G_ClientBegin
	(
	edict_t *ent, 
	qboolean loadgame
	)

	{
	// If we get an error, call the server's error function
	if ( setjmp( G_AbortGame ) )
		{
		G_ExitWithError();
		}

   if ( ent->inuse && ent->entity )
		{
		// the client has cleared the client side viewangles upon
		// connecting to the server, which is different than the
		// state when the game is saved, so we need to compensate
		// with deltaangles
      ent->entity->SetDeltaAngles();
      }
	else
		{
		// a spawn point will completely reinitialize the entity
		G_InitEdict( ent );
		G_InitClientResp( ent->client );
		G_PutClientInServer( ent );
		}

	if ( level.intermissiontime && ent->entity )
		{
		G_MoveClientToIntermission( ent->entity );
		}
	else
		{
		// send effect if in a multiplayer game
		if ( game.maxclients > 1 )
			{
			gi.bprintf (PRINT_HIGH, "%s entered the game\n", ent->client->pers.netname);
			}
		}

	// make sure all view stuff is valid
	if ( ent->entity )
		{
		ent->entity->ProcessEvent( EV_ClientEndFrame );
		}
	}

void FixDeadBodiesForPlayer
   (
   edict_t *ent
   )

   {
   int      i,playernum;
   edict_t  *body;


   if ( !deathmatch->value )
      return;

   playernum = ent-g_edicts-1;

   for ( i=0; i<BODY_QUEUE_SIZE; i++ )
      {            
      body = &g_edicts[ ( int )maxclients->value + 1 + i ];

      if ( ( body->s.skinnum == playernum ) && ( body->s.modelindex != ent->s.modelindex ) )
         {
         body->s.renderfx |= RF_DONTDRAW;
         body->s.skinnum = -1;
         }
      }
   }   

/*
===========
G_ClientUserInfoChanged

called whenever the player updates a userinfo variable.

The game can override any of the settings in place
(forcing skins or names, etc) before copying it off.
============
*/
void G_ClientUserinfoChanged
   (
   edict_t *ent,
   const char *userinfo
   )

   {
	const char	*s;
	int			playernum;
   Player      *player;
   str         model;
   float       fov;
   Event       *ev;

	// If we get an error, call the server's error function
	if ( setjmp( G_AbortGame ) )
		{
		G_ExitWithError();
		}

   player = ( Player * )ent->entity;

	ent->client->ps.pmove.pm_flags &= ~PMF_OLDNOCLIP;
	s = Info_ValueForKey( userinfo, "cl_oldnoclip" );
	if (strlen(s))
		{
		if ( atoi(s) )
			{
			ent->client->ps.pmove.pm_flags |= PMF_OLDNOCLIP;
			}
		}

	// set name
	s = Info_ValueForKey( userinfo, "name" );
	strncpy (ent->client->pers.netname, s, sizeof(ent->client->pers.netname)-1);

   // Don't allow zero length names
   if ( !strlen( ent->client->pers.netname ) )
      strcpy( ent->client->pers.netname, "Blade" );

   if ( deathmatch->value )
      {
   	// set skin
	   s = Info_ValueForKey( userinfo, "skin" );
      strncpy( ent->client->pers.skin, s, sizeof( ent->client->pers.skin ) - 1 );
      }
   
   // Don't allow zero length skins
   if ( !strlen( ent->client->pers.skin ) )
      {
      strcpy( ent->client->pers.skin, "blade_base" );
      }

   // set model only if player not a mutant
   if ( !( player && ( player->flags & (FL_MUTANT|FL_SP_MUTANT) ) ) )
      {
      s = Info_ValueForKey( userinfo, "model" );
      COM_StripExtension( s, ent->client->pers.model );
      strcat( ent->client->pers.model, ".def" );

      // Don't allow zero length models
      if ( !strlen( ent->client->pers.model ) )
         {
         strcpy( ent->client->pers.model, "pl_blade.def" );
         }

      // Only allow models that the server sets up in the players script file
      model = ent->client->pers.model;
      if ( !game.ValidPlayerModels.ObjectInList( model ) )
         {
         // Fall back to blade
         strcpy( ent->client->pers.model, "pl_blade.def" );
         }

#ifdef SIN_DEMO
      if ( 1 )
#else
      // Always be blade in single player
      if ( !deathmatch->value )
#endif
         {
         strcpy( ent->client->pers.model, "pl_blade.def" );
         }
      // Call the player's setModel function if he exists
      // Prepend 'models/' to make things easier
	   if ( !strchr( ent->client->pers.model, '*' ) && !strchr( ent->client->pers.model, '\\' ) && !strchr( ent->client->pers.model, '/' ) )
		   {
		   model = "models/";
         model += ent->client->pers.model;
		   }
      else
         {
         model = ent->client->pers.model;
         }

      if ( player && !player->deadflag && ( player->model != model ) )
         {
         player->setModel( model );
         player->RandomAnimate( "idle", NULL );
         }      
      }

   // Fov
   if ( player )
      {
	   fov = atof( Info_ValueForKey( userinfo, "fov" ) );
	   if ( fov < 1 )
         {
		   fov = 90;
         }
	   else if ( fov > 160 )
         {
		   fov = 160;
         }
      ev = new Event( EV_Player_Fov );
      ev->AddFloat( fov );
      player->ProcessEvent( ev );
      }

	// CTF
	if ( ctf->value )
		{
		switch ( ent->client->resp.ctf_team )
			{
			case CTF_TEAM_HARDCORPS:
				strcpy( ent->client->pers.skin, ctf_hardcorps_skin->string );
				break;
			case CTF_TEAM_SINTEK:
				strcpy( ent->client->pers.skin, ctf_sintek_skin->string );
				break;
			default:
				break;
			}
		}

   // Player number
	playernum = ent - g_edicts - 1;

	// combine name, skin and model into a configstring
	gi.configstring (CS_PLAYERSKINS+playernum, va("%s\\%s\\%s", 
                     ent->client->pers.netname,
                     ent->client->pers.model,
                     ent->client->pers.skin));

	// handedness
	s = Info_ValueForKey( userinfo, "hand" );
	if ( strlen( s ) )
	   {
		ent->client->pers.hand = atoi( s );
	   }

	// save off the userinfo in case we want to check something later
	strncpy( ent->client->pers.userinfo, userinfo, sizeof( ent->client->pers.userinfo )-1 );

   // Hide the bodies that are associated with this player so that
   // no weird animations show up on the client
   if ( ( !LoadingSavegame ) && ( deathmatch->value || coop->value ) )
      FixDeadBodiesForPlayer( ent );
   }

/*
===========
G_ClientConnect

Called when a player begins connecting to the server.
The game can refuse entrance to a client by returning false.
If the client is allowed, the connection process will continue
and eventually get to ClientBegin()
Changing levels will NOT cause this to be called again.
============
*/
qboolean G_ClientConnect
   (
   edict_t *ent,
   const char *userinfo
   )
   
   {
	const char *value;

	// If we get an error, call the server's error function
	if ( setjmp( G_AbortGame ) )
		{
		G_ExitWithError();
		}

	// check to see if they are on the banned IP list
	value = Info_ValueForKey( userinfo, "ip" );
	if ( SV_FilterPacket( value ) )
      {
		return false;
      }

	// check for a password
	value = Info_ValueForKey( userinfo, "password" );
	if ( strcmp( password->string, value ) != 0 )
      {
		return false;
      }

   // if there is already a body waiting for us (a loadgame), just
   // take it, otherwise spawn one from scratch
   if ( ent->inuse == false )
      {
      // clear the respawning variables
      G_InitClientResp( ent->client );
      if ( !game.autosaved )//|| !ent->client->pers.weapon)
         {
         G_InitClientPersistant( ent->client );
         }
      }

	G_ClientUserinfoChanged( ent, userinfo );

	if ( game.maxclients > 1 )
      {
		gi.printf( "%s connected\n", ent->client->pers.netname );
      }

   LoadingServer = false;

	return true;
   }

/*
===========
G_ClientDisconnect

called when a player drops from the server

============
*/
void G_ClientDisconnect
	(
	edict_t *ent
	)

	{
	// If we get an error, call the server's error function
	if ( setjmp( G_AbortGame ) )
		{
		G_ExitWithError();
		}

	if ( ( !ent->client ) || ( !ent->entity ) )
		{
		return;
		}

	delete ent->entity;
	ent->entity = NULL;
	}

/*
==================
Cmd_Say_f
==================
*/
void G_Say
	(
	edict_t *ent,
	qboolean team,
	qboolean arg0
	)

	{
	int			j;
	edict_t		*other;
	const char	*p;
	char			text[ 2048 ];

	if ( gi.argc() < 2 && !arg0 )
		{
		return;
		}

   if ( !DM_FLAG( DF_MODELTEAMS | DF_SKINTEAMS ) && !ctf->value )
		{
		team = false;
		}

	if ( team )
		{
		Com_sprintf( text, sizeof( text ), "(%s): ", ent->client->pers.netname );
		}
	else
		{
		Com_sprintf( text, sizeof( text ), "%s: ", ent->client->pers.netname );
		}

	if ( arg0 )
		{
		strcat( text, gi.argv( 0 ) );
		strcat( text, " " );
		strcat( text, gi.args() );
		}
	else
		{
		p = gi.args();

		if ( *p == '"' )
			{
			p++;
			strcat( text, p );
			text[ strlen( text ) - 1 ] = 0;
			}
		else
			{
			strcat( text, p );
			}
		}

	// don't let text be too long for malicious reasons
	if ( strlen( text ) > 150 )
		{
		text[ 150 ] = 0;
		}

	strcat( text, "\n" );

	if ( dedicated->value )
		{
		gi.cprintf( NULL, PRINT_CHAT, "%s", text );
		}

	for( j = 1; j <= game.maxclients; j++ )
		{
		other = &g_edicts[ j ];
		if ( !other->inuse || !other->client )
			{
			continue;
			}

		if ( team )
			{
			if ( !OnSameTeam( ent->entity, other->entity ) )
				{
				continue;
				}
			}

		gi.cprintf( other, PRINT_CHAT, "%s", text );
		}
	}

/*
==================
G_Talk
// send over a speech command
==================
*/
void G_Talk
	(
	edict_t *ent
	)

	{
	int			j;
	edict_t		*other;
	const char	*p;
	char			text[ 2048 ];

	if ( gi.argc() < 2 )
		{
		return;
		}

	p = gi.args();

	if ( *p == '"' )
		{
		p++;
		strcpy( text, p );
		text[ strlen( text ) - 1 ] = 0;
		}
	else
		{
		strcpy( text, p );
		}

	// don't let text be too long for malicious reasons
	if ( strlen( text ) > 150 )
		{
		text[ 150 ] = 0;
		}

	strcat( text, "\n" );

	if ( dedicated->value )
		{
		gi.cprintf( NULL, PRINT_TALK, "speech %s", text );
		}

	for( j = 1; j <= game.maxclients; j++ )
		{
      float len;
      vec3_t delta;

		other = &g_edicts[ j ];
		if ( !other->inuse || !other->client )
			{
			continue;
			}
      // cull the talking based off of distance
		VectorSubtract (other->s.origin, ent->s.origin, delta);
   	len = VectorLength (delta);
      if ( len > 2000 )
         {
         continue;
         }
		gi.cprintf( other, PRINT_TALK, "%d %s", ent->s.number, text );
		}
	}


void G_CameraCommand
   (
   void
   )

   {
   Event *ev;
	const char *cmd;
   int   i;
   int   n;

   n = gi.argc();
   if ( !n )
      {
      gi.printf( "Usage: cam [command] [arg 1]...[arg n]\n" );
      return;
      }

	cmd = gi.argv( 1 );
  	if ( Event::Exists( cmd ) )
		{
		ev = new Event( cmd );
      // this is a hack but necessary
		//ev->SetSource( EV_FROM_CONSOLE );
		ev->SetSource( EV_FROM_SCRIPT );
      ev->SetConsoleEdict( NULL );

		for( i = 2; i < n; i++ )
			{
			ev->AddToken( gi.argv( i ) );
			}

      CameraMan.ProcessEvent( ev );
      }
   else
      {
      gi.printf( "Unknown camera command '%s'.\n", cmd );
      }
   }

void ClientCommand
	(
	edict_t *ent
	)

	{
	const char	*cmd;
	int			i;
	int			n;
	Event			*ev;
	qboolean		found;
	cvar_t		*cvar;
	float			t;

	if ( !ent->client || !ent->entity )
		{
		// not fully in game yet
		return;
		}
	
	cmd = gi.argv( 0 );
	n = gi.argc();

   if ( !Q_strcasecmp( cmd, "say" ) )
		{
   	G_Say( ent, false, false );
      return;
		}
   else if ( !Q_strcasecmp( cmd, "say_team" ) )
		{
   	G_Say( ent, true, false );
      return;
		}
   else if ( !Q_strcasecmp( cmd, "say_talk" ) )
		{
   	G_Talk( ent );
      return;
		}
   else if ( game.maxclients == 1 )
      {
      // only allow these commands when we only have one client (most likely only a local game)
      if ( !Q_strcasecmp( cmd, "add" ) )
		   {
		   if ( n < 3 )
			   {
			   gi.cprintf( ent, PRINT_HIGH, "Syntax: add [var name] [amount].\n" );
			   return;
			   }

		   cvar = gi.cvar( gi.argv( 1 ), "0", 0 );
		   t = cvar->value + atof( gi.argv( 2 ) );
		   gi.cvar_set( gi.argv( 1 ), va( "%f", t ) );
		   gi.dprintf( "%s = %f\n", gi.argv( 1 ), cvar->value );
		   return;
		   }
      else if ( !Q_strcasecmp( cmd, "eventlist" ) )
		   {
         const char *mask;

         mask = NULL;
         if ( n > 1 )
            {
            mask = gi.argv( 1 );
            }
         Event::ListCommands( mask );
         return;
         }
      else if ( !Q_strcasecmp( cmd, "classlist" ) )
		   {
         listAllClasses();
         return;
         }
      else if ( !Q_strcasecmp( cmd, "classtree" ) )
		   {
         if ( n > 1 )
            {
            listInheritanceOrder( gi.argv( 1 ) );
            }
         else
            {
			   gi.cprintf( ent, PRINT_HIGH, "Syntax: classtree [classname].\n" );
            }
         return;
         }
      else if ( !Q_strcasecmp( cmd, "showvar" ) )
         {
         ScriptVariable *var;

         var = Director.GetExistingVariable( gi.argv( 1 ) );
         if ( var )
            {
            gi.cprintf( ent, PRINT_HIGH, "%s = '%s'\n", gi.argv( 1 ), var->stringValue() );
            }
         else
            {
            gi.cprintf( ent, PRINT_HIGH, "Variable '%s' does not exist.\n", gi.argv( 1 ) );
            }
         return;
         }
	   else if ( !Q_strcasecmp (cmd, "cam") )
         {
		   G_CameraCommand();
		   return;
	      }
      }

	found = false;

  	if ( Event::Exists( cmd ) )
		{
		ev = new Event( cmd );
		ev->SetSource( EV_FROM_CONSOLE );
		ev->SetConsoleEdict( ent );
		for( i = 1; i < n; i++ )
			{
			ev->AddToken( gi.argv( i ) );
			}

		if ( !Q_strncasecmp( cmd, "view", 4 ) )
			{
			found = Viewmodel.ProcessEvent( ev );
			}
		else if ( !Q_strncasecmp( cmd, "ai_", 2 ) )
			{
			found = PathManager.ProcessEvent( ev );
			}
 		else if ( !Q_strncasecmp( cmd, "console", 7 ) )
			{
			found = consoleManager.ProcessEvent( ev );
			}
		else
			{
			found = ent->entity->ProcessEvent( ev );
			}
		}

	if ( !found )
		{
		// anything that doesn't match a command will be a chat
		G_Say( ent, false, true );
		}
	}

void G_ClientCommand 
	(
	edict_t *ent
	)

	{
	// If we get an error, call the server's error function
	if ( setjmp( G_AbortGame ) )
		{
		G_ExitWithError();
		}

	//FIXME
	// setjmp doesn't seem to like to work inside the above function, so I've broken it out, 
	// which makes it happy.  Wierd.
	ClientCommand( ent );
   }

#ifdef SIN_ARCADE
void G_CheckFirstPlace
	(
   void
	)

	{
	int			i;
   int         maxscore;
   int         maxplayer;
   int         score;

	// sort the clients by score
   maxscore = INT_MIN;
   maxplayer = -1;
	for( i = 0; i < game.maxclients; i++ )
		{
      game.clients[ i ].ps.stats[ STAT_FIRSTPLACE ] = 0;

		if ( !g_edicts[ 1 + i ].inuse )
			{
			continue;
			}

		score = game.clients[ i ].resp.score;
      if ( score > maxscore )
         {
         maxplayer = i;
         maxscore = score;
         }
      else if ( score == maxscore )
         {
         // if a tie, clear out the maxplayer
         maxplayer = -1;
         }
		}

   if ( maxplayer != -1 )
      {
      game.clients[ maxplayer ].ps.stats[ STAT_FIRSTPLACE ] = 1;
      }
   }

void G_DrawFirstPlace
	(
   void
	)

	{
	int i;

	// sort the clients by score
	for( i = 0; i < game.maxclients; i++ )
		{
      game.clients[ i ].ps.stats[ STAT_DRAWFIRSTPLACE ] = 0;
      if ( game.clients[ i ].ps.stats[ STAT_FIRSTPLACE ] )
         {
         game.clients[ i ].ps.stats[ STAT_DRAWFIRSTPLACE ] = 1;
         }
      }
   }

#endif

/*
==================
G_DeathmatchScoreboardMessage

==================
*/
void G_DeathmatchScoreboardMessage
	(
	Entity *ent,
	Entity *killer
	)

	{
	char			entry[ 1024 ];
	char			string[ 1400 ];
	int			stringlength;
	int			i, j, k;
	int			sorted[ MAX_CLIENTS ];
	int			sortedscores[ MAX_CLIENTS ];
	int			score, total;
	int			x,y;
	gclient_t	*cl;
	edict_t		*cl_ent, *killeredict, *entedict;
   const char  *tag;
   
   // CTF
   if ( ctf->value )
      {
		CTF_ScoreboardMessage (ent, killer);
		return;
	   }

	killeredict = NULL;
	entedict = NULL;
	if ( killer )
		{
		killeredict = killer->edict;
		}
	if ( ent )
		{
		entedict = ent->edict;
		}

	// sort the clients by score
	total = 0;
	for( i = 0; i < game.maxclients; i++ )
		{
		cl_ent = g_edicts + 1 + i;
		if ( !cl_ent->inuse )
			{
			continue;
			}

		score = game.clients[ i ].resp.score;
		for( j = 0; j < total; j++ )
			{
			if ( score > sortedscores[ j ] )
				break;
			}
		for( k = total; k > j; k-- )
			{
			sorted[ k ] = sorted[ k - 1 ];
			sortedscores[ k ] = sortedscores[ k - 1 ];
			}
		sorted[ j ] = i;
		sortedscores[ j ] = score;
		total++;
		}

	// print level name and exit rules
	string[ 0 ] = 0;

	stringlength = strlen( string );

	// add the clients in sorted order
	if ( total > 12 )
		{
		total = 12;
		}

	for( i = 0; i < total; i++ )
		{
		cl = &game.clients[ sorted[ i ] ];
		cl_ent = g_edicts + 1 + sorted[ i ];

      x = (i>=6) ? 160 : 0;
		y = 32 + 32 * (i%6);

      // Add a tag to the player and the killer
      if (cl_ent == entedict)
			tag = "tag1";
		else if (cl_ent == killeredict)
			tag = "tag2";
		else
			tag = NULL;

		// send the layout
		Com_sprintf( entry, sizeof( entry ),
			"client %i %i %i %i %i %i ",
			 x, y, sorted[ i ], cl->resp.score, cl->ping, ( level.framenum - cl->resp.enterframe ) / 600 );
		
      // Put the tag on the end of the client command
      if ( tag )
         strcat( entry, va( "1 %s ",tag ) );
      else
         strcat( entry, va( "0 " ) );

      j = strlen( entry );
		if ( stringlength + j > 1024 )
			{
			break;
			}
		strcpy( string + stringlength, entry );
		stringlength += j;
		}

	gi.WriteByte( svc_layout );
	gi.WriteString( string );
	}

/*
==================
G_DeathmatchScoreboard

Draw instead of help message.
Note that it isn't that hard to overflow the 1400 byte message limit!
==================
*/
void G_DeathmatchScoreboard
	(
	Entity *ent
	)

	{
	G_DeathmatchScoreboardMessage( ent, ent->enemy );
	gi.unicast( ent->edict, true );
	}

/*
=================
G_ClientDrawBoundingBoxes
=================
*/
void G_ClientDrawBoundingBoxes
	(
	void
	)

	{
	edict_t	*edict;
	Entity	*ent;
	Vector	eye;

	// don't show bboxes during deathmatch
   if ( !sv_showbboxes->value || ( deathmatch->value && !sv_cheats->value ) )
		{
      return;
		}

   edict = g_edicts + 1 + 0;
   ent = edict->entity;
   if ( ent )
      {
	   eye = ent->worldorigin;
	   ent = findradius( NULL, eye, 1000 );
	   while( ent )
		   {
         switch ((int)sv_showbboxes->value)
            {
            case 1:
               if ( ent->edict != edict && ent->edict->s.solid)
                  {
                  if (ent->bindmaster)
                     G_DebugBBox( ent->worldorigin, ent->mins, ent->maxs, 0, 1, 0, 1 );
                  else
                     G_DebugBBox( ent->worldorigin, ent->mins, ent->maxs, 1, 1, 0, 1 );
                  }
               break;
            case 2:
               if ( ent->edict != edict && ent->edict->s.solid)
                  {
                  if (ent->bindmaster)
                     G_DebugBBox( "0 0 0", ent->edict->absmin, ent->edict->absmax, 0, 0, 1, 1 );
                  else
                     G_DebugBBox( "0 0 0", ent->edict->absmin, ent->edict->absmax, 1, 0, 1, 1 );
                  }
               break;
            case 3:
               if ( ent->edict->s.modelindex && !(ent->edict->s.renderfx & RF_DONTDRAW) )
                  G_DebugBBox( ent->worldorigin, ent->mins, ent->maxs, 1, 1, 0, 1 );
               break;
            case 4:
            default:
               G_DebugBBox( ent->worldorigin, ent->mins, ent->maxs, 1, 1, 0, 1 );
               break;
            case 5:
               if ( ent->edict->s.solid )
                  {
                  G_DebugBBox( ent->worldorigin, ent->edict->fullmins, ent->edict->fullmaxs, 1, 1, 1, 1 );
                  }
               break;
            }
	      ent = findradius( ent, eye, 1000 );
		   }
      }
	}

CLASS_DECLARATION( Class, game_locals_t, NULL );

ResponseDef game_locals_t::Responses[] =
	{
		{ NULL, NULL }
	};

game_locals_t::game_locals_t()
   {
   clients = NULL;

   autosaved = false;
   spawnpoint = "";

   maxentities = 0;
   maxclients = 0;
   maxconsoles = 0;
   maxsurfaces = 0;

   force_entnum = false;
   spawn_entnum = 0;

   ValidPlayerModels.FreeObjectList();
   }

EXPORT_FROM_DLL void game_locals_t::Archive
	(
	Archiver &arc
	)

   {
   int i;
   int num;

   Class::Archive( arc );

   arc.WriteBoolean( autosaved );
   arc.WriteString( spawnpoint );
   arc.WriteBoolean( force_entnum );
   arc.WriteInteger( spawn_entnum );

   // List of valid player models loaded from players global scriptfile
   num = ValidPlayerModels.NumObjects();
   arc.WriteInteger( num );
   for( i = 1; i <= num; i++ )
      {
      arc.WriteString( ValidPlayerModels.ObjectAt( i ) );
      }

   arc.WriteInteger( maxentities );
   arc.WriteInteger( maxclients );
   arc.WriteInteger( maxconsoles );
   arc.WriteInteger( maxsurfaces );

   for( i = 0; i < maxclients; i++ )
      {
		G_WriteClient( arc, &clients[ i ] );
      }
   }

EXPORT_FROM_DLL void game_locals_t::Unarchive
	(
	Archiver &arc
	)

   {
   int i;
   int num;
   str modelname;

   Class::Unarchive( arc );

   arc.ReadBoolean( &autosaved );
   arc.ReadString( &spawnpoint );
   arc.ReadBoolean( &force_entnum );
   arc.ReadInteger( &spawn_entnum );

   // Load list of valid player models
   arc.ReadInteger( &num );
   for( i = 1; i <= num; i++ )
      {
      arc.ReadString( &modelname );
      ValidPlayerModels.AddObject( modelname );
      }

   arc.ReadInteger( &maxentities );
   arc.ReadInteger( &maxclients );
   arc.ReadInteger( &maxconsoles );
   arc.ReadInteger( &maxsurfaces );
   G_AllocGameData();

   for( i = 0; i < maxclients; i++ )
      {
		G_ReadClient( arc, &clients[ i ] );
      }
   }

CLASS_DECLARATION( Class, level_locals_t, NULL );

ResponseDef level_locals_t::Responses[] =
	{
		{ NULL, NULL }
	};

level_locals_t::level_locals_t()
   {
   framenum = 0;
   time = 0;

   level_name = "";
   mapname = "";
   nextmap = "";

   playerfrozen = false;
   intermissiontime = 0;
	exitintermission = 0;

   next_edict = NULL;

   total_secrets = 0;
	found_secrets = 0;

	current_entity = NULL;
   memset( &impact_trace, 0, sizeof( impact_trace ) );

   body_queue = 0;

   earthquake = 0;

   clearsavegames = false;

   cinematic = false;
   no_jc = false;

   water_color = vec_zero;
   lightvolume_color = vec_zero;
   lava_color  = vec_zero;
   water_alpha = lightvolume_alpha = lava_alpha = 0;
   training    = false;
   airclamp    = true;

   missionfailed = false;
   missionfailedtime = 0;
   }

EXPORT_FROM_DLL void level_locals_t::Archive
	(
	Archiver &arc
	)

   {
   Class::Archive( arc );

   arc.WriteInteger( framenum );
   arc.WriteFloat( time );
   arc.WriteString( level_name );
   arc.WriteString( mapname );
   arc.WriteString( nextmap );

   arc.WriteBoolean( playerfrozen );
   arc.WriteFloat( intermissiontime );
	arc.WriteInteger( exitintermission );

   arc.WriteInteger( total_secrets );
   arc.WriteInteger( found_secrets );

   arc.WriteInteger( body_queue );

   arc.WriteFloat( earthquake );

   arc.WriteBoolean( clearsavegames );

   arc.WriteBoolean( cinematic );
   arc.WriteBoolean( no_jc );

   arc.WriteVector( water_color );
   arc.WriteVector( lightvolume_color );
   arc.WriteVector( lava_color );
   arc.WriteFloat( water_alpha );
   arc.WriteFloat( lightvolume_alpha );
   arc.WriteFloat( lava_alpha );
   arc.WriteBoolean( airclamp );
   arc.WriteBoolean( training );

   arc.WriteBoolean( missionfailed );
   arc.WriteFloat( missionfailedtime );
   }

EXPORT_FROM_DLL void level_locals_t::Unarchive
	(
	Archiver &arc
	)

   {
   Class::Unarchive( arc );

   arc.ReadInteger( &framenum );
   arc.ReadFloat( &time );
   arc.ReadString( &level_name );
   arc.ReadString( &mapname );
   arc.ReadString( &nextmap );

   arc.ReadBoolean( &playerfrozen );
   arc.ReadFloat( &intermissiontime );
	arc.ReadInteger( &exitintermission );

   // not archived since we can't save mid-frame
   next_edict = NULL;

   arc.ReadInteger( &total_secrets );
   arc.ReadInteger( &found_secrets );
	
   // not archived since we can't save mid-frame
   current_entity = NULL;
   memset( &impact_trace, 0, sizeof( impact_trace ) );

   arc.ReadInteger( &body_queue );

   arc.ReadFloat( &earthquake );

   arc.ReadBoolean( &clearsavegames );

   arc.ReadBoolean( &cinematic );
   arc.ReadBoolean( &no_jc );
   arc.ReadVector( &water_color );
   arc.ReadVector( &lightvolume_color );
   arc.ReadVector( &lava_color );
   arc.ReadFloat( &water_alpha );
   arc.ReadFloat( &lightvolume_alpha );
   arc.ReadFloat( &lava_alpha );
   arc.ReadBoolean( &airclamp );
   arc.ReadBoolean( &training );

   arc.ReadBoolean( &missionfailed );
   arc.ReadFloat( &missionfailedtime );
   }

/*
==============================================================================

PACKET FILTERING
 

You can add or remove addresses from the filter list with:

addip <ip>
removeip <ip>

The ip address is specified in dot format, and any unspecified digits will match any value, so you can specify an entire class C network with "addip 192.246.40".

Removeip will only remove an address specified exactly the same way.  You cannot addip a subnet, then removeip a single host.

listip
Prints the current list of filters.

writeip
Dumps "addip <ip>" commands to listip.cfg so it can be execed at a later date.  The filter lists are not saved and restored by default, because I beleive it would cause too much confusion.

filterban <0 or 1>

If 1 (the default), then ip addresses matching the current list will be prohibited from entering the game.  This is the default setting.

If 0, then only addresses matching the list will be allowed.  This lets you easily set up a private game, or a game that only allows players from your local network.


==============================================================================
*/

typedef struct
   {
	unsigned	mask;
	unsigned	compare;
   } ipfilter_t;

#define	MAX_IPFILTERS	1024

ipfilter_t	ipfilters[ MAX_IPFILTERS ];
int			numipfilters;

/*
=================
StringToFilter
=================
*/
static qboolean StringToFilter
   (
   const char *s,
   ipfilter_t *f
   )

   {
	char	num[ 128 ];
	int	i;
   int   j;
	byte	b[ 4 ];
	byte	m[ 4 ];
	
	for( i = 0; i < 4; i++ )
	   {
		b[ i ] = 0;
		m[ i ] = 0;
	   }
	
	for( i = 0; i < 4; i++ )
	   {
		if ( *s < '0' || *s > '9' )
		   {
			gi.cprintf( NULL, PRINT_HIGH, "Bad filter address: %s\n", s );
			return false;
		   }
		
		j = 0;
		while( *s >= '0' && *s <= '9' )
		   {
			num[ j++ ] = *s++;
		   }

		num[ j ] = 0;
		b[ i ] = atoi( num );
		if ( b[ i ] != 0 )
         {
			m[ i ] = 255;
         }

		if ( !*s )
         {
			break;
         }

		s++;
	   }
	
	f->mask = *( unsigned * )m;
	f->compare = *( unsigned * )b;
	
	return true;
   }

/*
=================
SV_FilterPacket
=================
*/
qboolean SV_FilterPacket
   (
   const char *from
   )

   {
	int i;
	unsigned	in;
	byte m[ 4 ];
	const char *p;

	i = 0;
	p = from;
	while( *p && i < 4 )
      {
		m[ i ] = 0;
		while( *p >= '0' && *p <= '9' )
         {
			m[ i ] = m[ i ] * 10 + ( *p - '0' );
			p++;
		   }

		if ( !*p || *p == ':' )
         {
			break;
         }

		i++;
      p++;
	   }
	
	in = *( unsigned * )m;
	for( i = 0; i < numipfilters; i++ )
      {
		if ( ( in & ipfilters[ i ].mask ) == ipfilters[ i ].compare )
         {
			return ( int )filterban->value;
         }
      }

	return !( int )filterban->value;
   }


/*
=================
SV_AddIP_f
=================
*/
void SVCmd_AddIP_f
   (
   void
   )

   {
	int i;
	
	if ( gi.argc() < 3 )
      {
		gi.cprintf( NULL, PRINT_HIGH, "Usage:  addip <ip-mask>\n" );
		return;
      }

	for( i = 0; i < numipfilters; i++ )
      {
		if ( ipfilters[ i ].compare == 0xffffffff )
         {
         // free spot
			break;
         }
      }

	if ( i == numipfilters )
	   {
		if ( numipfilters == MAX_IPFILTERS )
         {
			gi.cprintf( NULL, PRINT_HIGH, "IP filter list is full\n" );
			return;
		   }
		numipfilters++;
	   }
	
	if ( !StringToFilter( gi.argv( 2 ), &ipfilters[ i ] ) )
      {
		ipfilters[ i ].compare = 0xffffffff;
      }
   }

/*
=================
SV_RemoveIP_f
=================
*/
void SVCmd_RemoveIP_f
   (
   void
   )

   {
	ipfilter_t	f;
	int			i;
   int         j;

	if ( gi.argc() < 3 )
      {
		gi.cprintf( NULL, PRINT_HIGH, "Usage:  sv removeip <ip-mask>\n" );
		return;
	   }

	if ( !StringToFilter( gi.argv( 2 ), &f ) )
      {
		return;
      }

	for( i = 0; i < numipfilters; i++ )
      {
		if ( ( ipfilters[ i ].mask == f.mask ) && ( ipfilters[ i ].compare == f.compare ) )
		   {
			for ( j = i + 1; j < numipfilters; j++ )
            {
				ipfilters[ j - 1 ] = ipfilters[ j ];
            }

			numipfilters--;
			gi.cprintf( NULL, PRINT_HIGH, "Removed.\n" );

			return;
		   }
      }

	gi.cprintf( NULL, PRINT_HIGH, "Didn't find %s.\n", gi.argv( 2 ) );
   }

/*
=================
SV_ListIP_f
=================
*/
void SVCmd_ListIP_f
   (
   void
   )

   {
	int   i;
	byte	b[ 4 ];

	gi.cprintf( NULL, PRINT_HIGH, "Filter list:\n" );
	for( i = 0; i < numipfilters; i++ )
   	{
		*( unsigned * )b = ipfilters[ i ].compare;
		gi.cprintf( NULL, PRINT_HIGH, "%3i.%3i.%3i.%3i\n", b[ 0 ], b[ 1 ], b[ 2 ], b[ 3 ] );
	   }
   }

/*
=================
SV_WriteIP_f
=================
*/
void SVCmd_WriteIP_f
   (
   void
   )

   {
	FILE	 *f;
	char	 name[ MAX_OSPATH ]; 
	byte	 b[ 4 ];
	int	 i;
	cvar_t *game;

	game = gi.cvar( "game", "", 0 );

	if ( !*game->string )
      {
		sprintf( name, "%s/listip.cfg", GAMEVERSION );
      }
	else
      {
		sprintf( name, "%s/listip.cfg", game->string );
      }

	gi.cprintf( NULL, PRINT_HIGH, "Writing %s.\n", name );

	f = fopen( name, "wb" );
	if ( !f )
	   {
		gi.cprintf( NULL, PRINT_HIGH, "Couldn't open %s\n", name );
		return;
	   }
	
	fprintf( f, "set filterban %d\n", ( int )filterban->value );

	for( i = 0; i < numipfilters; i++ )
	   {
		*( unsigned * )b = ipfilters[ i ].compare;
		fprintf( f, "sv addip %i.%i.%i.%i\n", b[ 0 ], b[ 1 ], b[ 2 ], b[ 3 ] );
	   }
	
	fclose( f );
   }

/*
=================
G_ServerCommand

G_ServerCommand will be called when an "sv" command is issued.
The game can issue gi.argc() / gi.argv() commands to get the rest
of the parameters
=================
*/
void G_ServerCommand
   (
   void
   )

   {
	const char *cmd;

	cmd = gi.argv(1);
	if ( Q_stricmp( cmd, "addip" ) == 0 )
      {
		SVCmd_AddIP_f();
      }
	else if ( Q_stricmp( cmd, "removeip" ) == 0 )
      {
		SVCmd_RemoveIP_f();
      }
	else if ( Q_stricmp( cmd, "listip" ) == 0 )
      {
		SVCmd_ListIP_f();
      }
	else if ( Q_stricmp( cmd, "writeip" ) == 0 )
      {
		SVCmd_WriteIP_f();
      }
	else
      {
		gi.cprintf( NULL, PRINT_HIGH, "Unknown server command \"%s\"\n", cmd );
      }
   }