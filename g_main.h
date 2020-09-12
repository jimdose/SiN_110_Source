//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/g_main.h                         $
// $Revision:: 16                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 4/01/99 3:20p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/g_main.h                              $
// 
// 16    4/01/99 3:20p Markd
// Added dedicated support to Means of Death.
// 
// 15    3/02/99 9:16p Aldie
// Added CTF game code
// 
// 14    11/13/98 2:35a Aldie
// Declared fixbodiesforplayer
// 
// 13    11/09/98 12:55a Jimdose
// added sv_footsteps cvar so that server admins can turn footsteps off
// completely
// 
// 12    10/27/98 9:46p Aldie
// Changed training cvar to level.training
// 
// 11    10/25/98 10:16p Aldie
// Added training cvar
// 
// 10    10/22/98 5:02p Aldie
// Removed blastscale_z
// 
// 9     10/21/98 6:42p Markd
// Added sv_drawtrace
// 
// 8     10/16/98 1:56a Jimdose
// Added autosave variable to G_WriteLevel
// 
// 7     10/11/98 8:50p Jimdose
// Added LoadingServer
// 
// 6     10/09/98 2:07a Aldie
// Updated DMFLAGS
// 
// 5     10/08/98 7:41p Jimdose
// changed noexit to a dmflag
// added server commands
// Added ip filtering
// 
// 4     10/08/98 12:38a Jimdose
// Made savegames work
// 
// 3     9/22/98 3:21p Markd
// put in parentmode lockout for blood and gibs
// 
// 2     8/29/98 9:49p Jimdose
// created file
// 
// 1     8/29/98 6:44p Jimdose
//
// DESCRIPTION:
// Global header file for g_main.cpp
// 

#ifndef __G_MAIN_H__
#define __G_MAIN_H__

#include "g_local.h"

extern	Vector			vec_origin;
extern	Vector			vec_zero;

extern   qboolean       LoadingSavegame;
extern   qboolean       LoadingServer;

extern	game_locals_t	game;
extern	level_locals_t	level;
extern	game_import_t	gi;
extern	game_export_t	globals;

extern	edict_t			*g_edicts;
extern	edict_t			active_edicts;
extern	edict_t			free_edicts;

extern   netconsole_t	*g_consoles;
extern   netconbuffer_t	*g_conbuffers;
extern   netsurface_t	*g_surfaces;

extern	cvar_t	*developer;
extern	cvar_t	*precache;

extern	cvar_t	*maxentities;
extern   cvar_t   *maxconsoles;
extern	cvar_t	*deathmatch;
extern	cvar_t	*coop;
extern	cvar_t	*dmflags;
extern	cvar_t	*skill;
extern	cvar_t	*fraglimit;
extern	cvar_t	*timelimit;
extern   cvar_t   *ctf;
extern   cvar_t   *capturelimit;
extern	cvar_t	*filterban;

extern	cvar_t	*flood_msgs;
extern	cvar_t	*flood_persecond;
extern	cvar_t	*flood_waitdelay;

extern	cvar_t	*g_select_empty;
extern	cvar_t	*g_unlimited_ammo;
extern	cvar_t	*nomonsters;
extern   cvar_t   *dialog;

extern	cvar_t	*sv_gravity;
extern	cvar_t	*sv_maxvelocity;
extern   cvar_t   *sv_maxbulletholes;
extern   cvar_t   *sv_maxbloodsplats;
extern   cvar_t   *sv_gore;
extern   cvar_t   *sv_gibs;
extern   cvar_t   *sv_showdamage;
extern   cvar_t   *sv_showdamagelocation;

extern	cvar_t	*gun_x, *gun_y, *gun_z;
extern	cvar_t	*sv_rollspeed;
extern	cvar_t	*sv_rollangle;

extern	cvar_t	*run_pitch;
extern	cvar_t	*run_roll;
extern	cvar_t	*bob_up;
extern	cvar_t	*bob_pitch;
extern	cvar_t	*bob_roll;

extern	cvar_t	*sv_cheats;
extern	cvar_t	*maxclients;

extern   cvar_t   *sv_rocketspeed;
extern   cvar_t   *sv_rocketrate;

extern   cvar_t	*sv_stopspeed;
extern   cvar_t	*sv_friction;
extern   cvar_t	*sv_waterfriction;
extern   cvar_t	*sv_waterspeed;
extern   cvar_t   *sv_footsteps;

extern	cvar_t	*sv_traceinfo;
extern	cvar_t	*sv_drawtrace;
extern	int		sv_numtraces;

extern   cvar_t	*parentmode;
extern	cvar_t	*dedicated;

extern   usercmd_t *current_ucmd;

#define DM_FLAG( flag ) ( deathmatch->value && ( ( int )dmflags->value & ( flag ) ) )

void		G_BeginIntermission( const char *map );
void		G_PutClientInServer( edict_t *ent );
void		G_SaveClientData( void );
void		G_MoveClientToIntermission( Entity *client );
void		G_DeathmatchScoreboard( Entity *ent );
void		G_DeathmatchScoreboardMessage( Entity *client, Entity *killer );
void     G_WriteClient( Archiver &arc, gclient_t *client );
void     G_AllocGameData( void );

extern "C" {
	void		G_ClientEndServerFrames( void );
	void		G_ClientThink( edict_t *ent, usercmd_t *cmd );
	qboolean G_ClientConnect( edict_t *ent, const char *userinfo );
	void		G_ClientUserinfoChanged( edict_t *ent, const char *userinfo );
	void		G_ClientDisconnect( edict_t *ent );
	void		G_ClientBegin( edict_t *ent, qboolean loadgame );
	void		G_ClientCommand( edict_t *ent );
	void		G_WriteGame( const char *filename, qboolean autosave );
	void		G_ReadGame( const char *filename );
	void		G_WriteLevel( const char *filename, qboolean autosave );
	void		G_ReadLevel( const char *filename );
	void		G_InitGame( void );
	void		G_ShutdownGame( void );
	void		G_RunFrame( void );
   void     G_ServerCommand( void );
	void		G_ClientThink( edict_t *ent, usercmd_t *ucmd );
   void     FixDeadBodiesForPlayer( edict_t *ent );
	};

qboolean    SV_FilterPacket( const char *from );
void        SVCmd_AddIP_f( void );
void        SVCmd_RemoveIP_f( void );
void        SVCmd_ListIP_f( void );
void        SVCmd_WriteIP_f( void );

#endif /* g_main.h */
