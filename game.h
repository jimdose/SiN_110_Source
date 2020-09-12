//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/game.h                           $
// $Revision:: 52                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 1/27/99 10:02p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/game.h                                $
// 
// 52    1/27/99 10:02p Markd
// Merged 2015 source into main code base
// 
// 51    12/18/98 11:05p Jimdose
// added definitions of server side stuff to get rid of qcommon.h includes
// 
// 50    11/11/98 10:04p Jimdose
// Removed comment
// 
// 49    11/11/98 10:02p Jimdose
// added SVF_MONSTERCLIP and SVF_PLAYERCLIP
// 
// 48    10/20/98 9:46p Jimdose
// made CalcCRC take a const char *
// 
// 47    10/20/98 9:39p Jimdose
// Added CalcCRC
// Upped GAME_API_VERSION
// 
// 46    10/16/98 1:56a Jimdose
// Added autosave to WriteLevel function
// Increased GAME_API_VERSION
// 
// 45    10/10/98 5:58p Aldie
// More quantumdestab fixes
// 
// 44    10/08/98 7:42p Jimdose
// Added ServerCommand
// 
// 43    9/08/98 7:09p Jimdose
// added printf to game_import_t
// 
// 42    9/07/98 8:29p Markd
// Added fullmins fullmaxs and fullradius
// 
// 41    9/05/98 11:55a Markd
// Upped game api version
// 
// 40    9/01/98 7:47p Aldie
// Added itemname to inventory stuff
// 
// 39    8/31/98 7:45p Aldie
// Updated surface data structure and removed surfinfo field
// 
// 38    8/29/98 9:51p Jimdose
// made netconsole_s, netconbuffer_s, and netsurface_s visible to game dll to
// get rid of it in g_local.h
// 
// 37    8/29/98 2:53p Aldie
// Added status meter for loading levels.
// 
// 36    8/28/98 3:46p Markd
// Added centroid to edict_s
// 
// 35    8/25/98 7:55p Markd
// Added SVF_ONLYPARENT flag
// 
// 34    8/18/98 11:08p Markd
// Added new Alias System
// 
// 33    8/02/98 9:00p Markd
// Merged code 3.17
// 
// 32    7/17/98 7:58p Markd
// Added radius to fulltrace, also added SVF_USEBBOX
// 
// 31    6/27/98 6:40p Markd
// Added SoundLength
// 
// 30    6/20/98 7:50p Markd
// Added BoneGroupName function
// 
// 29    6/15/98 10:06p Jimdose
// added gi.fulltrace
// 
// 28    6/15/98 7:57p Markd
// Put in Group_Flags
// 
// 27    6/08/98 7:23p Aldie
// Added some surface in the game import
// 
// 26    5/26/98 8:42p Markd
// Added NumGroups to interface
// 
// 25    5/24/98 4:48p Jimdose
// Made char *'s const
// 
// 24    5/24/98 2:46p Markd
// Made char *'s into const char *'s
// 
// 23    5/23/98 12:53p Aldie
// Updated surfaces networking.
// 
// 22    5/20/98 11:12a Markd
// removed char * dependency
// 
// 21    5/13/98 4:47p Aldie
// Update damage surfaces
// 
// 20    5/09/98 8:01p Jimdose
// added GameDir, PlayerDir, and CreatePath to the import list for the dll
// 
// 19    5/05/98 2:44p Aldie
// Added server side surface states
// 
// 18    4/30/98 4:48p Aldie
// Server side console states
// 
// 17    4/28/98 7:00p Aldie
// Added sever side console buffer
// 
// 16    4/27/98 3:20p Jimdose
// Added DebugLines
// 
// 15    4/27/98 1:51p Aldie
// Added server side console states.
// 
// 14    4/09/98 1:40p Markd
// Added SVF_SHOOTABLE
// 
// 13    4/07/98 8:01p Markd
// Changed all SINMDL commands to non-SINMDL prefix
// 
// 12    3/30/98 6:12p Markd
// Added Alias commands
// 
// 11    3/29/98 8:33p Markd
// Changed nature of InitCmds and FrameCommands
// 
// 10    3/27/98 7:00p Markd
// Changed Bone functions a bit
// 
// 9     3/25/98 1:22p Markd
// 
// 8     3/24/98 9:59a Markd
// Added new bone, and group stuff for models
// 
// 7     3/18/98 8:01p Markd
// Accidentally made fadetime an int instead of a float
// 
// 6     3/18/98 7:15p Markd
// Changed sound code stuff
// 
// 5     3/05/98 6:44p Markd
// Added SINMDL stuff
// 
// 4     2/03/98 11:08a Jimdose
// Converted to work with Sin progs
// Could use a little clean up.
// 
// 3     12/30/97 6:04p Jimdose
// Added header text
//
// DESCRIPTION:
// game dll information visible to server
//

#ifndef __GAME_H__
#define __GAME_H__

#ifdef __cplusplus
extern "C" {
#endif

#define	GAME_API_VERSION			13

// edict->svflags
#define	FRAMETIME					0.1

#define	SVF_NOCLIENT				0x00000001	// don't send entity to clients, even if it has effects
#define	SVF_DEADMONSTER			0x00000002	// treat as CONTENTS_DEADMONSTER for collision
#define	SVF_MONSTER					0x00000004	// treat as CONTENTS_MONSTER for collision
#define	SVF_SHOOTABLE				0x00000008	// treat as CONTENTS_SHOOTABLE for collision
#define	SVF_USEBBOX 				0x00000010	// do not perform perfect collision use the bbox instead
#define	SVF_ONLYPARENT				0x00000020	// only send this entity to its parent
#define	SVF_HIDEOWNER				0x00000040	// hide the owner of the client
#define	SVF_MONSTERCLIP         0x00000080	// treat as CONTENTS_MONSTERCLIP for collision
#define	SVF_PLAYERCLIP          0x00000100	// treat as CONTENTS_PLAYERCLIP for collision
// 2015 code    
#define  SVF_NOTOWNER            0x00000200  // don't draw for owner

// edict->solid values

typedef enum
	{
	SOLID_NOT,			// no interaction with other objects
	SOLID_TRIGGER,		// only touch when inside, after moving
	SOLID_BBOX,			// touch on edge
	SOLID_BSP			// bsp clip, touch on edge
	} solid_t;

//===============================================================

// link_t is only used for entity area links now
typedef struct link_s
{
	struct link_s	*prev, *next;
} link_t;

#define	MAX_ENT_CLUSTERS	16

typedef struct edict_s edict_t;
typedef struct gclient_s gclient_t;
typedef struct netconsole_s netconsole_t;
typedef struct netconbuffer_s netconbuffer_t;
typedef struct netsurface_s netsurface_t;

#ifndef QCOMMON

// If this is modified in qcommon.h, it must be reflected here.
#define	MAX_MSGLEN		1400		// max length of a message

// If this is modified in qcommon.h, it must be reflected here.
enum svc_ops_e
{
	svc_bad,
	svc_muzzleflash,
	svc_muzzleflash2,
	svc_temp_entity,
	svc_layout,
	svc_inventory,
   svc_console_command
};

#endif

#ifndef GAME_INCLUDE

typedef struct gclient_s
{
	player_state_t	ps;		// communicated by server to clients
	int				ping;
	// the game dll can add anything it wants after
	// this point in the structure
} gclient_t;

struct edict_s
{
	entity_state_t		s;
	struct gclient_s	*client;
	qboolean				inuse;
	int					linkcount;

	// FIXME: move these fields to a server private sv_entity_t
	link_t				area;					// linked to a division node or leaf
	
	int					num_clusters;		// if -1, use headnode instead
	int					clusternums[MAX_ENT_CLUSTERS];
	int					headnode;			// unused if num_clusters != -1
	int					areanum, areanum2;

	//================================

	int					svflags;				// SVF_NOCLIENT, SVF_DEADMONSTER, SVF_MONSTER, etc
	vec3_t				mins, maxs;
	vec3_t				absmin, absmax, size;
   vec3_t            fullmins, fullmaxs;
   float             fullradius;
   vec3_t            centroid;
	solid_t				solid;
	int					clipmask;
	edict_t				*owner;

	// the game dll can add anything it wants after
	// this point in the structure
};

#endif		// GAME_INCLUDE

struct netconsole_s
   {
   console_state_t   s;
   qboolean          inuse;
   };

struct netconbuffer_s
   {
   console_buffer_state_t s;
   };

struct netsurface_s
   {
	surface_state_t   s;
   qboolean          inuse;
   };

//===============================================================

//
// functions provided by the main engine
//
typedef struct
{
	// special messages
	void		(*bprintf) (int printlevel, const char *fmt, ...);
	void		(*dprintf) (const char *fmt, ...);
	void		(*printf) (const char *fmt, ...);
	void		(*cprintf) (edict_t *ent, int printlevel, const char *fmt, ...);
	void		(*centerprintf) (edict_t *ent, const char *fmt, ...);
	void		(*sound) (edict_t *ent, int channel, int soundindex, float volume, float attenuation, float timeofs, float pitch, float fadetime, int flags);
	void		(*positioned_sound) (vec3_t origin, edict_t *ent, int channel, int soundinedex, float volume, float attenuation, float timeofs, float pitch, float fadetime, int flags);

	// config strings hold all the index strings, the lightstyles,
	// and misc data like the sky definition and cdtrack.
	// All of the current configstrings are sent to clients when
	// they connect, and changes are sent to all connected clients.
	void		(*configstring) (int num, const char *string);

	void		(*error) (const char *fmt, ...);

	// new names can only be added during spawning
	// existing names can be looked up at any time
	int		(*modelindex) (const char *name);
	int		(*soundindex) (const char *name);
	int		(*imageindex) (const char *name);
	int		(*itemindex)  (const char *name);

	void		(*setmodel) (edict_t *ent, const char *name);

	// collision detection against world and bboxes of a-models
	trace_t	(*trace) (vec3_t start, vec3_t mins, vec3_t maxs, vec3_t end, edict_t *passent, int contentmask);

	// for full ray intersection tests against a-model polys and world
	trace_t	(*fulltrace) (vec3_t start, vec3_t mins, vec3_t maxs, vec3_t end, float radius, edict_t *passent, int contentmask);

	int		(*pointcontents) (vec3_t point);
	qboolean	(*inPVS) (vec3_t p1, vec3_t p2);
	qboolean	(*inPHS) (vec3_t p1, vec3_t p2);
	void		(*SetAreaPortalState) (int portalnum, qboolean open);
	qboolean	(*AreasConnected) (int area1, int area2);

	// an entity will never be sent to a client or used for collision
	// if it is not passed to linkentity.  If the size, position, or
	// solidity changes, it must be relinked.
	void		(*linkentity) (edict_t *ent);
	void		(*unlinkentity) (edict_t *ent);		// call before removing an interactive edict
	int		(*BoxEdicts) (vec3_t mins, vec3_t maxs, edict_t **list,	int maxcount, int areatype);
	void		(*Pmove) (pmove_t *pmove);				// player movement code common with client prediction

	// network messaging
	void		(*multicast) (vec3_t origin, multicast_t to);
	void		(*unicast) (edict_t *ent, qboolean reliable);
	void		(*WriteChar) (int c);
	void		(*WriteByte) (int c);
	void		(*WriteShort) (int c);
	void		(*WriteLong) (int c);
	void		(*WriteFloat) (float f);
	void		(*WriteString) (const char *s);
	void		(*WritePosition) (vec3_t pos);	// some fractional bits
	void		(*WriteDir) (vec3_t pos);		// single byte encoded, very coarse
	void		(*WriteAngle) (float f);

	// managed memory allocation
	void		*(*TagMalloc) (int size, int tag);
	void		(*TagFree) (void *block);
	void		(*FreeTags) (int tag);

	// console variable interaction
	cvar_t	*(*cvar) (const char *var_name, const char *value, int flags);
	cvar_t	*(*cvar_set) (const char *var_name, const char *value);
	cvar_t	*(*cvar_forceset) (const char *var_name, const char *value);

	// ClientCommand and coneole command parameter checking
	int			(*argc) (void);
	const char	*(*argv) (int n);
	const char	*(*args) (void);

	// add commands to the server console as if they were typed in
	// for map changing, etc
	void			(*AddCommandString) (const char *text);

	void			(*DebugGraph) (float value, int color);

	int			(*LoadFile) ( const char *path, void **buffer, int tag);
	const char	*(*GameDir)( void );
	const char	*(*PlayerDir)( void );
	void			(*CreatePath)(const char *path);
	float 		(*SoundLength) ( const char *path );


   // 
   // Model support
   //
   qboolean (*IsModel) ( int index );

   //
   // MODEL UTILITY FUNCTIONS
   //

   // DEF SPECIFIC STUFF
   int				(*NumAnims) ( int modelindex );
   int				(*NumSkins) ( int modelindex );
   int				(*NumGroups) ( int modelindex );
   sinmdl_cmd_t * (*InitCommands) ( int modelindex );
   void				(*CalculateBounds) ( int modelindex, float scale, vec3_t mins, vec3_t maxs );

   // ANIM SPECIFIC STUFF
   const char *   (*Anim_NameForNum) ( int modelindex, int animnum );
   int				(*Anim_NumForName) ( int modelindex, const char * name );
   int				(*Anim_Random) ( int modelindex, const char * name );
   int				(*Anim_NumFrames) ( int modelindex, int animnum );
   float				(*Anim_Time) ( int modelindex, int animnum );
   void				(*Anim_Delta) ( int modelindex, int animnum, vec3_t delta );

   // FRAME SPECIFIC STUFF
   sinmdl_cmd_t * (*Frame_Commands) ( int modelindex, int animnum, int framenum );
   void				(*Frame_Delta) ( int modelindex, int animnum, int framenum, vec3_t delta );
   float				(*Frame_Time) ( int modelindex, int animnum, int framenum );

   // SKIN SPECIFIC STUFF
   const char *   (*Skin_NameForNum) ( int modelindex, int skinnum );
   int				(*Skin_NumForName) ( int modelindex, const char * name );

   // GROUP SPECIFIC STUFF
   int				(*Group_NameToNum) ( int modelindex, const char * name );
   const char *   (*Group_NumToName) ( int modelindex, int num );
   float				(*Group_DamageMultiplier) ( int modelindex, int num );
   int				(*Group_Flags) ( int modelindex, int num );

   // BONE SPECIFIC STUFF
   qboolean (*GetBoneInfo)
      (
      int modelindex,
      const char * bonename,
      int * groupindex,
      int * tri_num,
      vec3_t orientation
      );

   const char * (*GetBoneGroupName)
      (
      int modelindex,
      const char * bonename
      );

   qboolean (*GetBoneTransform)
      (
      int modelindex,
      int groupindex,
      int tri_num,
      vec3_t orientation,
      int anim,
      int frame,
      float scale,
      vec3_t trans[3], 
      vec3_t pos
      );

   //
   // ALIAS SYSTEM
   //
   qboolean			(*Alias_Add)( int modelindex, const char * alias, const char * name, float weight );
   const char *   (*Alias_FindRandom)( int modelindex, const char * alias );
   void				(*Alias_Dump)( int modelindex );
   void				(*Alias_Clear)( int modelindex );

   //
   // GLOBAL ALIAS SYSTEM
   //
   qboolean			(*GlobalAlias_Add)( const char * alias, const char * name, float weight );
   const char *   (*GlobalAlias_FindRandom)( const char * alias );
   void				(*GlobalAlias_Dump)( void );
   void				(*GlobalAlias_Clear)( void );

   unsigned short ( *CalcCRC )( const char *start, int count );

   //
   // SURFACES
   //
   int            (*Surf_NumSurfaces)( void );
   csurface_t *   (*Surf_Surfaces)( void );

   void           (*IncrementStatusCount)( int i );
   debugline_t		**DebugLines;
	int				*numDebugLines;
} game_import_t;

//
// functions exported by the game subsystem
//
typedef struct
{
	int			apiversion;

	// the init function will only be called when a game starts,
	// not each time a level is loaded.  Persistant data for clients
	// and the server can be allocated in init
	void		(*Init) (void);
	void		(*Shutdown) (void);

	// each new level entered will cause a call to SpawnEntities
	void		(*SpawnEntities) (const char *mapname, const char *entstring, const char *spawnpoint);

	// Read/Write Game is for storing persistant cross level information
	// about the world state and the clients.
	// WriteGame is called every time a level is exited.
	// ReadGame is called on a loadgame.
	void		(*WriteGame) (const char *filename, qboolean autosave);
	void		(*ReadGame) (const char *filename);

	// ReadLevel is called after the default map information has been
	// loaded with SpawnEntities, so any stored client spawn spots will
	// be used when the clients reconnect.
	void		(*WriteLevel) (const char *filename, qboolean autosave );
	void		(*ReadLevel) (const char *filename);

	qboolean	(*ClientConnect) (edict_t *ent, const char *userinfo );
	void		(*ClientBegin) (edict_t *ent, qboolean loadgame);
	void		(*ClientUserinfoChanged) (edict_t *ent, const char *userinfo);
	void		(*ClientDisconnect) (edict_t *ent);
	void		(*ClientCommand) (edict_t *ent);
	void		(*ClientThink) (edict_t *ent, usercmd_t *cmd);

	void		(*RunFrame) (void);

	// ServerCommand will be called when an "sv <command>" command is issued on the
	// server console.
	// The game can issue gi.argc() / gi.argv() commands to get the rest
	// of the parameters
	void		(*ServerCommand) (void);

   void     (*CreateSurfaces) (csurface_t *surfaces, int count);

	//
	// global variables shared between game and server
	//

	// The edict array is allocated in the game dll so it
	// can vary in size from one game to another.
	// 
	// The size will be fixed when ge->Init() is called
	struct edict_s	*edicts;
	int			edict_size;
	int			num_edicts;		// current number, <= max_edicts
	int			max_edicts;
   struct netconsole_s *consoles;
   int         console_size;
   int         num_consoles;
   int         max_consoles;
   struct netconbuffer_s *conbuffers;
   int         conbuffer_size;
   struct netsurface_s *surfaces;
   int         surface_size;
   int         max_surfaces;
   int         num_surfaces;
} game_export_t;

game_export_t *GetGameApi (game_import_t *import);

#ifdef __cplusplus
	}
#endif

#endif
