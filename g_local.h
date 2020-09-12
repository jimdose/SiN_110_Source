//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/g_local.h                        $
// $Revision:: 100                                                            $
//   $Author:: Aldie                                                          $
//     $Date:: 3/12/99 8:12p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/g_local.h                             $
// 
// 100   3/12/99 8:12p Aldie
// added idtime
// 
// 99    3/02/99 9:16p Aldie
// Added CTF game code
// 
// 98    11/10/98 5:51p Jimdose
// disabled exporting symbols from the dll
// 
// 97    11/10/98 4:34p Jimdose
// added clearsavegames to level
// 
// 96    11/08/98 10:47p Jimdose
// moved earthquake to level struct
// 
// 95    11/06/98 5:18p Jimdose
// added missionfailed and missionfailedtime to level vars
// when a mission has failed or the player is dead in single player, the game
// code immediately shows the loadmenu, preventing them from letting the game
// continue running if they exit the menu
// 
// 94    10/27/98 9:46p Aldie
// Changed training cvar to level.training
// 
// 93    10/26/98 2:16p Aldie
// Added AirClamp
// 
// 92    10/25/98 11:49p Jimdose
// added EXPORT_TEMPLATE
// moved playerfrozen to level
// 
// 91    10/25/98 6:26p Markd
// Added in no_jc abililty
// 
// 90    10/24/98 2:18p Markd
// Added stufftext service
// 
// 89    10/19/98 9:52p Jimdose
// changed slime variables to lightvolume
// 
// 88    10/10/98 1:33a Jimdose
// moved include of g_utils.h to be before g_spawn.h
// 
// 87    10/08/98 12:38a Jimdose
// Made savegames work
// 
// 86    9/30/98 5:39p Aldie
// Added showinfo command
// 
// 85    9/27/98 6:28p Aldie
// Added water, slime, and lava colors to worldspawn
// 
// 84    9/19/98 5:01p Markd
// took out current_music and fallback_music
// 
// 83    9/10/98 8:34p Markd
// Removed hidestats and drawoverlay from level variables
// 
// 82    9/07/98 8:29p Markd
// Added fullmins fullmaxs and fullradius
// 
// 81    9/02/98 7:48p Aldie
// Added ValidPlayerModels list
// 
// 80    8/29/98 9:52p Jimdose
// General cleanup of g_local.h
// got rid of unused variables and macros
// moved prototypes to their appropriate headers
// 
// 79    8/28/98 3:46p Markd
// Added centroid to edict_s
// 
// 78    8/27/98 9:06p Jimdose
// Moved some prototypes that didn't belong here to g_utils.h
// Made STEPSIZE global
// 
// 77    8/27/98 2:31p Aldie
// Added adrenaline flags
// 
// 76    8/25/98 7:47p Jimdose
// Added gravaxis to SelectSpawnPoint
// 
// 75    8/21/98 5:26p Markd
// Added sv_precache and cl_precache 
// 
// 74    8/19/98 8:50p Aldie
// Changed MOD to enumerated type
// 
// 73    8/17/98 7:43p Markd
// Added MOD_LAVA and MOD_SLIME
// 
// 72    8/17/98 4:35p Markd
// Added cinematic variable
// 
// 71    8/14/98 8:14p Aldie
// Added generic overlay system
// 
// 70    8/08/98 8:24p Markd
// Added MOD_THROWOBJECT
// 
// 69    8/07/98 6:01p Aldie
// Added frag credits for falling damage
// 
// 68    8/04/98 6:06p Aldie
// Relocated SPAWNFLAG_DETAIL
// 
// 67    8/03/98 7:53p Jimdose
// Added G_DrawDebugNumber
// 
// 66    8/03/98 7:36p Markd
// Added MOD_DEBRIS
// 
// 65    8/02/98 9:00p Markd
// Merged code 3.17
// 
// 64    7/24/98 6:19p Aldie
// enable and disable huds and dialog checking
// 
// 63    7/23/98 2:32p Aldie
// Made speed of rocket a tweak cvar
// 
// 62    7/21/98 10:05p Markd
// Added FL_DIE_EXPLODE
// 
// 61    7/21/98 9:06p Markd
// Added current_mood and fallback_mood
// 
// 60    7/21/98 1:10p Aldie
// Added meansofdeath to obituaries
// 
// 59    7/18/98 5:08p Aldie
// Added showdamage
// 
// 58    7/17/98 7:58p Markd
// Added radius to G_FullTrace
// 
// 57    7/15/98 9:59p Markd
// Added FL_SHIELDS
// 
// 56    7/13/98 5:01p Aldie
// Added dead player bodies with gibbing
// 
// 55    7/09/98 10:38p Aldie
// Moved body parts to game
// 
// 54    7/08/98 12:58p Jimdose
// made developer cvar global
// 
// 53    7/03/98 12:02p Aldie
// Updated client persistent data
// 
// 52    7/02/98 2:34p Aldie
// Mission computer
// 
// 51    6/23/98 9:55p Jimdose
// Fixed infinite loop bug in G_RunFrame
// 
// 50    6/15/98 10:07p Jimdose
// Added G_FullTrace
// 
// 49    6/08/98 11:42a Aldie
// Added MOVETYPE_SLIDE
// 
// 48    5/27/98 5:28a Aldie
// Added sv_gibs
// 
// 47    5/27/98 5:04a Aldie
// Added queue for bloodsplats
// 
// 46    5/25/98 6:52a Aldie
// Added maxbulletholes
// 
// 45    5/24/98 4:48p Jimdose
// Made char *'s const
// 
// 44    5/23/98 12:53p Aldie
// Updated surfaces networking.
// 
// 43    5/20/98 7:17p Markd
// Added G_DebugBBox
// 
// 42    5/20/98 11:12a Markd
// removed char * dependency
// 
// 41    5/14/98 10:21p Jimdose
// Added G_NextEntity
// Made G_MoveStep return extended failure information
// 
// 40    5/13/98 4:47p Aldie
// Update damage surfaces
// 
// 39    5/12/98 7:07p Markd
// Put in development spawnflag
// 
// 38    5/11/98 5:53p Markd
// Added FL_DIE_GIBS
// 
// 37    5/08/98 7:01p Markd
// Added FL_DARKEN flag
// 
// 36    5/05/98 2:49p Jimdose
// removed kick_angles, kick_origin, v_dmg_roll, v_dmg_pitch, v_dmg_time,
// fall_time, fall_value, damage_alpha, bonus_alpha, damage_blend, v_angle,
// bobtime, oldviewangles, and oldvelocity from gclient_t.  Most are moved into
// Player class.
// 
// 35    5/05/98 2:41p Aldie
// added server side surface states
// 
// 34    5/03/98 4:44p Jimdose
// added line drawing utility functions similar to opengl
// 
// 33    5/02/98 8:46p Markd
// Changed gamedir from Basesin1 to BASE
// 
// 32    5/01/98 5:08p Jimdose
// added prototype for world as an Entity *.  This points to the entity created
// by WorldSpawn
// 
// 31    4/30/98 9:24p Jimdose
// Changed use of string to str class
// 
// 30    4/30/98 4:48p Aldie
// Server side console states
// 
// 29    4/28/98 7:00p Aldie
// Added sever side console buffer
// 
// 28    4/27/98 3:21p Jimdose
// Added DebugLines
// 
// 27    4/27/98 1:51p Aldie
// Added server side console states.
// 
// 26    4/16/98 2:09p Jimdose
// Removed navigation_numbeacons
// 
// 25    4/10/98 4:57p Jimdose
// added spawntime to edict
// 
// 24    4/10/98 1:24a Markd
// Added new FL_ flags for sparks, blood, tesselation, blastmarks and
// die_tesselation
// 
// 23    4/07/98 3:49p Aldie
// Added zooming crosshair
// 
// 22    4/04/98 6:14p Jimdose
// Added G_GetNameForSurface
// 
// 21    4/02/98 4:51p Jimdose
// Added stats and deathmatch scoreboard
// 
// 20    3/30/98 10:43p Jimdose
// Added G_Movestep
// 
// 19    3/28/98 4:36p Jimdose
// Added deathmatch starts
// 
// 18    3/27/98 5:39p Jimdose
// Made BeginIntermission accept a string instead of an edict
// 
// 17    3/26/98 8:15p Jimdose
// Added coop variable
// Removed unused structures and prototypes
// Added prototypes of game interface functions
// 
// 16    3/24/98 5:03p Jimdose
// Included listener.h in place of g_event.h
// 
// 15    3/24/98 4:30p Aldie
// New svc commands for consoles.
// 
// 14    3/23/98 1:33p Jimdose
// Revamped event and command system
// 
// 13    3/11/98 7:38p Markd
// Added current_viewthing
// 
// 12    3/04/98 8:00p Aldie
// More support for damage surfaces.
// 
// 11    3/02/98 5:49p Jimdose
// Added num_navbeacons to level_locals_t
// Added entname to edict_s
// Added findradius
// Removed unused Q2 functions
// Added include of string.h from standard C++ library
// 
// 10    2/21/98 1:16p Jimdose
// Added G_TestMove and G_TestStepMove for use in pathfinding code
// Removed buttons, oldbuttons, and latched_buttons from gclient_t structure
// 
// 9     2/18/98 8:08p Jimdose
// Prototyped IsNumeric
// 
// 8     2/16/98 2:23p Jimdose
// Added active_edicts and free_edicts for faster entity processing and for
// operations that depend on the order that physics is processed on entities
// (such as binding).
// Added next and prev fields to edict_t
// Included linklist.h
// 
// 7     2/09/98 2:35p Aldie
// Removed const of vec_origin and vec_zero
// 
// 6     2/09/98 11:55a Jimdose
// Made vec_zero and vec_origin const
// Prototyped G_PushMove
// 
// 5     2/06/98 5:50p Jimdose
// Update prototypes
// 
// 4     2/03/98 11:06a Jimdose
// In process of converting to work with Sin progs
// 
// 3     12/30/97 6:04p Jimdose
// Added header text
//
// DESCRIPTION:
// local definitions for game module
//

#ifndef __G_LOCAL_H__
#define __G_LOCAL_H__

#if 0

#define EXPORT_FROM_DLL __declspec( dllexport )
#define EXPORT_TEMPLATE

#else

#define EXPORT_FROM_DLL

#endif

#include "q_shared.h"

// define GAME_INCLUDE so that game.h does not define the
// short, server-visible gclient_t and edict_t structures,
// because we define the full size ones in this file
#define	GAME_INCLUDE
#include "game.h"
#include "container.h"
#include "str.h"

// the "gameversion" client command will print this plus compile date
#define	GAMEVERSION	"base"

// memory tags to allow dynamic memory to be cleaned up
#define	TAG_GAME					765			// clear when unloading the dll
#define	TAG_LEVEL				766			// clear when loading a new level

// protocol bytes that can be directly added to messages
#define	svc_muzzleflash		1
#define	svc_muzzleflash2		2
#define	svc_temp_entity		3
#define	svc_layout				4
#define	svc_inventory			5
#define  svc_console_command  6
#define  svc_stufftext        12

// handedness values
#define	RIGHT_HANDED			0
#define	LEFT_HANDED				1
#define	CENTER_HANDED			2

#define	random()					((rand () & 0x7fff) / ((float)0x7fff))
#define	crandom()				(2.0 * (random() - 0.5))

// predefine Entity so that we can add it to edict_t without any errors
class Entity;

//
// Exported templated classes must be explicitly instantiated
//
#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL Container<str>;
#endif

// client data that stays across multiple level loads
typedef struct
	{
	char			userinfo[MAX_INFO_STRING];
	char			netname[16];
	char			model[MAX_QPATH];	
   char        skin[MAX_QPATH];
	int			hand;

	// values saved and restored from edicts when changing levels
	int			health;
	int			max_health;

	} client_persistant_t;

// client data that stays across deathmatch respawns
typedef struct
	{
	int			enterframe;			// level.framenum the client entered the game
	int			score;				// frags, etc
	vec3_t		cmd_angles;			// angles sent over in the last command
	int		   ctf_team;         // CTF team number
	int         ctf_state;        // CTF player state
	float       ctf_lasttechmsg;  // CTF Last time a tech message was sent
	float       ctf_lastfraggedcarrier; // Last time a carrier was fragged
	float       ctf_lasthurtcarrier; // List time carrier was hurt
	float       ctf_lastreturnedflag; // Last time flag was returned
   float       ctf_idtime;       // Last time a player id was made
	} client_respawn_t;

// this structure is cleared on each PutClientInServer(),
// except for 'client->pers'
typedef struct gclient_s
	{
	// known to server
	player_state_t			ps;				// communicated by server to clients
	int						ping;

	// private to game
	client_persistant_t	pers;
	client_respawn_t		resp;
   qboolean             showinfo; 
   } gclient_t;

struct edict_s
	{
	entity_state_t	s;
	gclient_t	   *client;	// NULL if not a player
									// the server expects the first part
									// of gclient_t to be a player_state_t
									// but the rest of it is opaque

	qboolean			inuse;
	int				linkcount;

	// FIXME: move these fields to a server private sv_entity_t
	link_t			area;					// linked to a division node or leaf
	
	int				num_clusters;		// if -1, use headnode instead
	int				clusternums[MAX_ENT_CLUSTERS];
	int				headnode;			// unused if num_clusters != -1
	int				areanum, areanum2;

	//================================

	int				svflags;
	vec3_t			mins, maxs;
	vec3_t			absmin, absmax, size;
   vec3_t         fullmins, fullmaxs;
   float          fullradius;
   vec3_t         centroid;
	solid_t			solid;
	int				clipmask;
	edict_t			*owner;


	// DO NOT MODIFY ANYTHING ABOVE THIS, THE SERVER
	// EXPECTS THE FIELDS IN THAT ORDER!

	//================================
	Entity			*entity;
	float				freetime;			// sv.time when the object was freed
	float				spawntime;			// sv.time when the object was spawned

	char				entname[ 64 ];

	edict_t			*next;
	edict_t			*prev;
	};

#include "vector.h"
#include "linklist.h"
#include "class.h"

//
// this structure is left intact through an entire game
// it should be initialized at dll load time, and read/written to
// the server.ssv file for savegames
//

class EXPORT_FROM_DLL game_locals_t : public Class
	{
	public:
		CLASS_PROTOTYPE( game_locals_t );

      gclient_t	      *clients;				// [maxclients]
	   qboolean	         autosaved;

	   // can't store spawnpoint in level, because
	   // it would get overwritten by the savegame restore
	   str               spawnpoint;          // needed for coop respawns

	   // store latched cvars here that we want to get at often
	   int			      maxclients;
	   int			      maxentities;
      int               maxconsoles;
      int               maxsurfaces;

	   qboolean		      force_entnum;
	   int			      spawn_entnum;

      // List of valid player models loaded from players global scriptfile
      Container<str>    ValidPlayerModels;

                        game_locals_t();
	   virtual void      Archive( Archiver &arc );
      virtual void      Unarchive( Archiver &arc );
	};

//
// this structure is cleared as each map is entered
// it is read/written to the level.sav file for savegames
//
class EXPORT_FROM_DLL level_locals_t : public Class
	{
	public:
		CLASS_PROTOTYPE( level_locals_t );

      int			framenum;
	   float			time;

	   str         level_name;	            // the descriptive name (Outer Base, etc)
	   str         mapname;		            // the server name (base1, etc)
	   str         nextmap;		            // go here when fraglimit is hit

      // used for cinematics
      qboolean    playerfrozen;

      // used to prevent players from continuing failed games
      qboolean    missionfailed;
      float       missionfailedtime;

	   // intermission state
	   float			intermissiontime;			// time the intermission was started
	   int			exitintermission;

	   edict_t		*next_edict;				// Used to keep track of the next edict to process in G_RunFrame

	   int			total_secrets;
	   int			found_secrets;

	   Entity		*current_entity;	// entity running from G_RunFrame
   
	   // FIXME - remove this later when it is passed in the event.
      trace_t     impact_trace;

      int         body_queue;

      float       earthquake;
      
      qboolean    clearsavegames;
      qboolean    cinematic;

      qboolean    no_jc;

      // Blending color for water, light volumes,lava
      Vector      water_color;
      Vector      lightvolume_color;
      Vector      lava_color;
      float       water_alpha;
      float       lightvolume_alpha;
      float       lava_alpha;
      qboolean    airclamp;
      qboolean    training;

                     level_locals_t();
	   virtual void   Archive( Archiver &arc );
      virtual void   Unarchive( Archiver &arc );
	};

#include "g_main.h"
#include "listener.h"
#include "g_utils.h"
#include "g_spawn.h"
#include "g_phys.h"

#endif
