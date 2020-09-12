//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/q_shared.h                       $
// $Revision:: 195                                                            $
//   $Author:: Jimdose                                                        $
//     $Date:: 8/03/99 7:09p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/q_shared.h                            $
// 
// 195   8/03/99 7:09p Jimdose
// changes for Sin Arcade
// 
// 194   7/24/99 6:47p Markd
// Added talk feature and added speech code
// 
// 193   7/24/99 5:45p Markd
// Added new NO_WEAPON_CHANGE DM Flag
// 
// 192   5/18/99 7:08p Aldie
// remove useless ctf flag
// 
// 191   3/19/99 4:14p Aldie
// Moved MOD to client
// 
// 190   3/02/99 9:16p Aldie
// Added CTF game code
// 
// 2     2/16/99 4:09p Aldie
// 
// 1     2/11/99 1:39p Aldie
// 
// 189   1/27/99 10:02p Markd
// Merged 2015 source into main code base
// 
// 188   1/26/99 5:46p Markd
// Added bone flags, new particle types and TransformFromTriangle for 2015
// 
// 187   11/14/98 8:07p Jimdose
// added DF_NO_DROP_WEAPONS
// 
// 186   11/09/98 12:56a Jimdose
// added EF_NOFOOTSTEPS
// 
// 185   11/08/98 8:24p Markd
// increased text length on keys and values
// 
// 184   11/06/98 5:47p Markd
// put in stuff for H2INC stuff
//
// 183   10/26/98 2:16p Aldie
// Added AirClamp
//
// 182   10/25/98 4:37a Aldie
// Upped MAX_SOUNDS
//
// 181   10/19/98 9:52p Jimdose
// changed slime variables to lightvolume
//
// 180   10/18/98 9:03p Markd
// Added PM_INVEHICLE_ZOOM
//
// 179   10/18/98 8:45p Jimdose
// ifdefed out event from entity_state_t
//
// 178   10/18/98 5:52p Aldie
// Added tempmodel flag
//
// 177   10/14/98 6:29p Markd
// Put in STAT_EXITSIGN
//
// 176   10/11/98 12:04a Aldie
// Added PMF_ADRENALINE
//
// 175   10/09/98 2:07a Aldie
// Updated DMFLAGS
//
// 174   10/08/98 8:23p Markd
// Increased MAX_SOUNDS
//
// 173   10/08/98 7:42p Jimdose
// Added DF_NOEXIT
//
// 172   10/08/98 4:34p Aldie
// Added RDF_NOENTITIES
//
// 171   10/06/98 9:16p Aldie
// Changed SURF_STRONG to SURF_ADD
//
// 170   10/05/98 12:27a Jimdose
// Added angledist
//
// 169   10/04/98 10:31p Markd
// Added MDL_GROUP stuff
//
// 168   10/04/98 10:28p Aldie
// Added multiple weapon changes.  Damage, flashes, quantum stuff
//
// 167   10/03/98 1:12p Aldie
// Added new pulse effects
//
// 166   9/28/98 5:51p Markd
// Changed Swamp to Duct
//
// 165   9/28/98 4:07p Aldie
// Added oxygen powerup
//
// 164   9/26/98 4:46p Aldie
// Added mutant mode
//
// 163   9/25/98 3:01p Aldie
// Tesselation defaults and flags
//
// 162   9/20/98 7:11p Aldie
// Added flags to particles
//
// 161   9/19/98 12:24p Markd
// eliminated unused fields in surfinfo_t
//
// 160   9/18/98 10:57p Jimdose
// added bound macro
//
// 159   9/11/98 12:22p Markd
// Changed SURF_DAMAGED to SURF_HARDWAREONLY
//
// 158   9/10/98 8:38p Aldie
// Electrical beam effects
//
// 157   9/09/98 3:56p Aldie
// New lightning effect
//
// 156   9/08/98 6:27p Markd
// rewrote commens for solid in entity_state
//
// 155   9/05/98 5:10p Aldie
//
// 154   9/03/98 2:11p Aldie
// Added checksums checks to .def files
//
// 153   9/01/98 7:47p Aldie
// Added itemname to inventory stuff
//
// 152   8/31/98 7:45p Aldie
// Updated surface data structure and removed surfinfo field
//
// 151   8/31/98 5:46p Aldie
// Powerup timer stuff
//
// 150   8/30/98 8:28p Markd
// Took out NOVIS flag, no longer needed
//
// 149   8/29/98 7:17p Markd
// added te_scaled_explosion
//
// 148   8/29/98 2:37p Markd
// Added EF_AUTO_ANIMATE
//
// 147   8/26/98 5:37p Aldie
// Removed damage_threshold field from surfinfo
//
// 146   8/25/98 7:55p Markd
// Removed THIRDPERSONVIEW
//
// 145   8/25/98 5:50p Markd
// Added PM_THIRDPERSONVIEW
//
// 144   8/24/98 6:50p Jimdose
// gravity axis is now encoded into effects
//
// 143   8/24/98 1:53p Markd
// renamed friction and restitution to magnitude and frequency
//
// 142   8/22/98 9:48p Markd
// Added TEMPMODEL_NOVIS flag
//
// 141   8/22/98 9:37p Jimdose
// GRAVITY_AXIS_MASK was defined wrong
//
// 140   8/22/98 8:48p Jimdose
// Added support for alternate gravity axis
//
// 139   8/22/98 12:06a Aldie
// New surface manager implemented
//
// 138   8/19/98 8:51p Aldie
// Added random particles
//
// 137   8/19/98 5:02p Markd
// Added new flags and fixed argument issue with sincmds
//
// 136   8/14/98 8:14p Aldie
// Added generic overlay system
//
// 135   8/12/98 6:04p Aldie
// Added a shield timer
//
// 134   8/06/98 7:05p Markd
// Added crouch flag to effects
//
// 133   8/05/98 7:48p Markd
// Added physics to tempmodels
//
// 132   8/04/98 6:06p Aldie
// Added RF_DETAIL
//
// 131   8/03/98 7:34p Markd
// Added SURFACE_DamageMultiplier func and debris field to client cmds
//
// 130   8/02/98 9:00p Markd
// Merged code 3.17
//
// 129   7/31/98 7:43p Aldie
// Client side bullet effects
//
// 128   7/24/98 10:50p Jimdose
// Increased MAX_MODELS to 640
//
// 127   7/24/98 6:21p Jimdose
// Added groundsurface, groundplane, and groundcontents to pmove_t
//
// 126   7/24/98 4:55p Jimdose
// Added CS_MAXCLIENTS for determining the number of clients the server allows
// from another client
//
// 125   7/24/98 2:10p Markd
// Added new audio channels
//
// 124   7/23/98 4:40p Markd
// Added EF_EVERYFRAME
//
// 123   7/23/98 12:31p Markd
// Added onladder to pmove_t
//
// 122   7/21/98 9:07p Markd
// Added new moods for music stuff
//
// 121   7/18/98 4:02p Markd
// Added PM_INVEHICLE movetype
//
// 120   7/17/98 11:31a Aldie
// Added STAT_CLIPAMMO
//
// 119   7/15/98 11:24p Markd
// Added normal to sinmdl_intersection_t
//
// 118   7/15/98 10:04p Aldie
// Added TE_BULLET_SPRAY
//
// 117   7/14/98 5:33a Jimdose
// Changed player eye and stand height
//
// 116   7/13/98 5:02p Aldie
// Added dead player bodies with gibbing
//
// 115   7/12/98 9:47p Markd
// added crosshair to statusbar layout
//
// 114   7/10/98 11:11p Markd
// Added local dialog flag
//
// 113   7/10/98 12:24a Aldie
// Undid RF_CUSTOMSKIN
//
// 112   7/10/98 12:21a Aldie
// Added customskin flag
//
// 111   7/09/98 9:35p Jimdose
// Removed RF_CONSOLE
// Added EF_SMOOTHANGLES
//
// 110   7/09/98 4:33p Markd
// Added console_owner to console_state_t
//
// 109   7/08/98 3:12p Aldie
// Reworked layout stuff
//
// 108   7/02/98 2:34p Aldie
// Mission computer
//
// 107   7/01/98 2:20p Markd
// Added RDF_NOCLEAR
//
// 106   6/30/98 4:40p Markd
// Changed default tesselation amount
//
// 105   6/27/98 4:25p Aldie
// Added STAT_WEAPONLIST
//
// 104   6/25/98 8:09p Aldie
// Added armor stats, and te_damage_wall
//
// 103   6/24/98 12:23p Markd
// Added more tesselation stuff, removed TE_SPARKS and TE_BLOOD
//
// 102   6/23/98 10:15p Markd
// Added position to sinmdl_intersection_t
//
// 101   6/20/98 6:22p Aldie
// Added flag for inventory model
//
// 100   6/20/98 2:20p Aldie
// Updated stats flags
//
// 99    6/19/98 6:39p Aldie
// Updated #defines for stats
//
// 98    6/18/98 6:19p Markd
// changed default tesselation sizes
//
// 97    6/18/98 2:15p Markd
// Added dir to trace_t
//
// 96    6/18/98 2:00p Markd
// rewrote tesselation code
//
// 95    6/15/98 7:57p Markd
// Reduced MAX_EDICTS, reduced MAX_MODELS, put in LittleUnsignedShort
//
// 94    6/15/98 10:40a Aldie
// Added defines for pulse beam
//
// 93    6/10/98 9:30p Markd
// fixed config string problem
//
// 92    6/10/98 4:37p Aldie
// Added comment to remind us that statusbars take up more than one
// configstring.
//
// 91    6/10/98 2:52p Markd
// typo with old configstring stuff
//
// 90    6/10/98 2:46p Markd
// Took out old configstrings
//
// 89    6/09/98 4:41p Markd
// Added additional environment mapped flag
//
// 88    6/08/98 5:18p Aldie
// Added spidermines and moved some defines here.
//
// 87    6/05/98 6:27p Aldie
// Added armor stats
//
// 86    6/03/98 4:40p Markd
// Removed variables from player_state_t and also added U_PREVFRAME, removed
// U_GUNFRAME, merged it with U_GUNANIMFRAME
//
// 85    5/28/98 1:26p Aldie
// Added rocket explosion particles
//
// 84    5/27/98 8:06p Aldie
// Added SIN_GetToken and SIN_Parse
//
// 83    5/27/98 4:54p Markd
// Put in TEMPMODEL_ALPHAFADE flag
//
// 82    5/27/98 5:04a Aldie
// Added EF_GIB
//
// 81    5/26/98 4:20p Markd
// Added sinmdl_intersection_t
//
// 80    5/25/98 8:51a Aldie
// Added new mask type (solid without fence)
//
// 79    5/25/98 7:15p Markd
// Added more TEMPMODEL commands
//
// 78    5/25/98 5:42p Markd
// Added TE_STRIKE and TE_DLIGHT
//
// 77    5/24/98 6:29p Markd
// Added CalculateRotatedBounds2
//
// 76    5/24/98 4:48p Jimdose
// Made char *'s const
//
// 75    5/24/98 2:56p Markd
// increased MAX_EDICTS to 1536
//
// 74    5/23/98 10:38p Markd
// Added TE_TEMPMODEL and TEMPMODEL flags
//
// 73    5/23/98 12:53p Aldie
// Updated surfaces networking.
//
// 72    5/20/98 11:12a Markd
// removed char * dependency
//
// 71    5/19/98 10:41p Markd
// Added surf_envmapped
//
// 70    5/18/98 6:18p Markd
// Added RF_ENVMAPPED
//
// 69    5/17/98 8:10p Aldie
// Moved mainconsole string here
//
// 68    5/16/98 11:02p Aldie
// Changed format of deathmatch flags
//
// 67    5/16/98 5:00p Markd
// Added RF_XFLIP
//
// 66    5/15/98 7:20p Markd
// Added SOUND_FLAGS
//
// 65    5/15/98 6:47p Markd
// added music_moods to playerstate and enumerated type
//
// 64    5/14/98 6:26p Markd
// Fixed up MASKS and added CONTENTS_FENCE and DUMMYFENCE
//
// 63    5/14/98 11:44a Markd
// Removed base_angle, added transvec
//
// 62    5/13/98 6:22p Markd
// Added TE_Burnwall and CalculateRotatedBounds
//
// 61    5/13/98 4:47p Aldie
// Update damage surfaces
//
// 60    5/08/98 7:54p Markd
// Set proper MAX_CMDS limit
//
// 59    5/08/98 7:02p Markd
// Added lightofs to entity_state also removed some render flags
//
// 58    5/07/98 11:24p Markd
// Added playerframe, playeranim and playerindex to playerstate, added
// gunframe, gunanim, and gunmodelindex to entity_state_t
//
// 57    5/06/98 7:49p Markd
// Added style and state to csurfinfo_s
//
// 56    5/05/98 7:38p Markd
// Added last_gunframe and last_gunanim to player_state_t for client side frame
// stuff
//
// 55    5/05/98 2:44p Aldie
// Added server side surface states
//
// 54    5/03/98 8:12p Markd
// Commented out MuzzleFlashes
//
// 53    5/02/98 8:46p Markd
// Added SURFACE flags and stuff
//
// 52    5/02/98 8:37p Aldie
// More console stuff for demos
//
// 51    4/30/98 4:49p Aldie
// Server side console states
//
// 50    4/28/98 7:00p Aldie
// Added sever side console buffer
//
// 49    4/27/98 3:21p Jimdose
// Added DebugLines
//
// 48    4/27/98 1:52p Aldie
// Added server side consoles.
//
// 47    4/18/98 6:12p Aldie
// Added ammo stats
//
// 46    4/18/98 4:24p Aldie
// Added ammo bar to stats
//
// 45    4/16/98 1:57p Jimdose
// Added prevframe to entity_state and gunprevframe to playerstate
//
// 44    4/14/98 6:30p Aldie
// Added laser temp ent.
//
// 43    4/09/98 1:41p Markd
// Added CONTENTS_SHOOTABLE and changed MASK_SHOT
//
// 42    4/07/98 8:01p Markd
// Added CS_SOUNDTRACK
//
// 41    4/06/98 7:10p Aldie
// Added zooming for SniperRifle
//
// 40    4/04/98 5:13p Markd
// Added TE_TESSELATE
//
// 39    4/03/98 3:35p Jimdose
// Added fast weapons
// Added draw flags for layouts
//
// 38    3/30/98 11:06p Aldie
// Added consoles as configstrings.
//
// 37    3/29/98 8:33p Markd
// Added sinmdl_cmd_t structure
//
// 36    3/28/98 3:10p Markd
// Increased MAX_MODEL_GROUPS
//
// 35    3/27/98 8:50p Jimdose
// Added support for third person view
//
// 34    3/27/98 7:00p Markd
// Increased MAX_MODELS, changed bone definition, added viewangles and
// vieworigin to entity_state_t and changed TransformFromTriangle and
// OriginFromTriangle
//
// 33    3/25/98 3:25p Markd
// Expanded bone_t definition
//
// 32    3/24/98 9:59a Markd
// Added TransformFromTriangle
//
// 31    3/18/98 7:47p Markd
// Added numgroups and groups to entity_state_t
//
// 30    3/18/98 7:16p Markd
// Added bone support to the entity state for entity linking in models
//
// 29    3/18/98 6:27p Aldie
// Added console to renderfx.
//
// 28    3/13/98 7:26p Aldie
// Added some new dlight renderfx
//
// 27    3/10/98 7:44p Aldie
// Added constants for player heights here.
//
// 26    3/09/98 2:51p Jimdose
// Working on euler-quat stuff
//
// 25    3/06/98 7:16p Aldie
// Arbitrary alpha for entities & lensflare
//
// 24    3/05/98 6:47p Markd
// added scale, to entity_state
//
// 23    3/05/98 3:49p Aldie
// More support for damaged surfaces.
//
// 22    3/05/98 11:36a Markd
// Added Anim suport
//
// 21    3/04/98 7:59p Aldie
// More support for damage textures.
//
// 20    3/04/98 5:14p Aldie
// Added support for damaged surfaces.
//
// 19    3/03/98 6:04p Aldie
// Added first pass for footsteps.
//
// 18    2/28/98 5:49p Markd
// Accidentally put the wrong file in their, I meant COM_FileExtension
//
// 17    2/28/98 5:46p Markd
// forgot a ;
//
// 16    2/28/98 5:46p Markd
// Added COM_StripExtension
//
// 15    2/28/98 4:43p Aldie
// Added Matrix4TransformVector
//
// 14    2/27/98 5:46p Jimdose
// Added min and max macros
//
// 13    2/25/98 4:38p Markd
// Added COM_GetToken
//
// 12    2/25/98 2:24p Aldie
// Added texture damage threshold constants
//
// 11    2/24/98 3:42p Aldie
// Added support for groupname and updated conveyor flag
//
// 10    2/22/98 10:15p Aldie
// Added support for texinfo commands over the net
//
// 9     2/22/98 2:19p Aldie
// Added support for trans_mag and trans_angle in the surface.
//
// 8     2/21/98 7:58p Aldie
// Removed dependency on TRANS33/66
//
// 7     2/21/98 7:18p Jimdose
// Added PMF_OLDNOCLIP and PMF_OLDLADDERS for client prediction
//
// 6     2/16/98 2:09p Jimdose
// Added quaternion field to entity_state_t for proper interpolation
// Added the following math utility functions: MatrixToEulerAngles,
// TransposeMatrix, MatrixTransformVector, OrthoNormalize, QuatToMat,
// MatToQuat, SlerpQuaternion, AnglesToMat, RotateAxis, MultQuat, EulerToQuat,
// VectorsToEulerAngles
//
// 5     2/04/98 4:04p Aldie
// Removed reference to value
//
// 4     1/21/98 6:53p Jimdose
// Made compatible with C++
// Added new render flag RF_DONTDRAW for invisible items
//
// 3     12/30/97 6:04p Jimdose
// Added header text
//
// DESCRIPTION:
// included first by ALL program modules
//

#ifndef __Q_SHARED_H__
#define __Q_SHARED_H__

#ifdef _WIN32
// unknown pragmas are SUPPOSED to be ignored, but....
#pragma warning(disable : 4244)     // MIPS
#pragma warning(disable : 4136)     // X86
#pragma warning(disable : 4051)     // ALPHA

#pragma warning(disable : 4018)     // signed/unsigned mismatch
#pragma warning(disable : 4305)		// truncation from const double to float

#endif

#ifndef _H2INC

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#endif

#ifndef min
#define min(a,b)  (((a) < (b)) ? (a) : (b))
#endif
#ifndef max
#define max(a,b)  (((a) > (b)) ? (a) : (b))
#endif

#ifndef _H2INC
#define bound(a,minval,maxval)  ( ((a) > (minval)) ? ( ((a) < (maxval)) ? (a) : (maxval) ) : (minval) )
#endif

#if (defined _M_IX86 || defined __i386__) && !defined C_ONLY && !defined __sun__
#define id386	1
#else
#define id386	0
#endif

#if defined _M_ALPHA && !defined C_ONLY
#define idaxp	1
#else
#define idaxp	0
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _H2INC
typedef unsigned char      byte;
#endif

#ifdef __cplusplus
typedef int qboolean;
#else
typedef enum {false, true}	qboolean;
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif


// angle indexes
#define	PITCH				0		// up / down
#define	YAW					1		// left / right
#define	ROLL				2		// fall over

#define	MAX_STRING_CHARS	1024	// max length of a string passed to Cmd_TokenizeString
#define	MAX_STRING_TOKENS	80		// max tokens resulting from Cmd_TokenizeString
#define	MAX_TOKEN_CHARS		128		// max length of an individual token

#define	MAX_QPATH			64		// max length of a quake game pathname
#define	MAX_OSPATH			128		// max length of a filesystem pathname

//
// per-level limits
//
#define	MAX_CLIENTS			256		// absolute limit
#ifdef SIN
#define	MAX_EDICTS			1024	// must change protocol to increase more
#else
#define	MAX_EDICTS			1024	// must change protocol to increase more
#endif
#define	MAX_LIGHTSTYLES		256
#ifdef SIN
#define	MAX_MODELS			640		// these are sent over the net as bytes
#define  MAX_CONSOLES      32
#define  MAX_SURFACES      1024
#define	MAX_SOUNDS			512		// so they cannot be blindly increased
#else
#define	MAX_MODELS			256		// these are sent over the net as bytes
#define	MAX_SOUNDS			256		// so they cannot be blindly increased
#endif
#define	MAX_IMAGES			256
#define	MAX_ITEMS			256


// game print flags
#define	PRINT_LOW			0		// pickup messages
#define	PRINT_MEDIUM		1		// death messages
#define	PRINT_HIGH			2		// critical messages
#define	PRINT_CHAT			3		// chat messages
#define	PRINT_TALK			4		// speech synthesis messages



#define	ERR_FATAL			0		// exit the entire game with a popup window
#define	ERR_DROP			1		// print to console and disconnect from game
#define	ERR_DISCONNECT		2		// don't kill server

#define	PRINT_ALL			0
#define PRINT_DEVELOPER		1		// only print when "developer 1"
#define PRINT_ALERT			2


// destination class for gi.multicast()
typedef enum
{
MULTICAST_ALL,
MULTICAST_PHS,
MULTICAST_PVS,
MULTICAST_ALL_R,
MULTICAST_PHS_R,
MULTICAST_PVS_R
} multicast_t;


/*
==============================================================

MATHLIB

==============================================================
*/

typedef float vec_t;
typedef vec_t vec3_t[3];
typedef vec_t vec5_t[5];

typedef	int	fixed4_t;
typedef	int	fixed8_t;
typedef	int	fixed16_t;

#ifndef M_PI
#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h
#endif

struct cplane_s;

extern vec3_t vec3_origin;

#define	nanmask (255<<23)

#define	IS_NAN(x) (((*(int *)&x)&nanmask)==nanmask)

// microsoft's fabs seems to be ungodly slow...
//float Q_fabs (float f);
//#define	fabs(f) Q_fabs(f)
#if !defined C_ONLY && !defined __linux__ && !defined __sgi
extern long Q_ftol( float f );
#else
#define Q_ftol( f ) ( long ) (f)
#endif

#define DotProduct(x,y)			(x[0]*y[0]+x[1]*y[1]+x[2]*y[2])
#define VectorSubtract(a,b,c)	(c[0]=a[0]-b[0],c[1]=a[1]-b[1],c[2]=a[2]-b[2])
#define VectorAdd(a,b,c)		(c[0]=a[0]+b[0],c[1]=a[1]+b[1],c[2]=a[2]+b[2])
#define VectorCopy(a,b)			(b[0]=a[0],b[1]=a[1],b[2]=a[2])
#define VectorClear(a)			(a[0]=a[1]=a[2]=0)
#define VectorNegate(a,b)		(b[0]=-a[0],b[1]=-a[1],b[2]=-a[2])
#define VectorSet(v, x, y, z)	(v[0]=(x), v[1]=(y), v[2]=(z))

void VectorMA (vec3_t veca, float scale, vec3_t vecb, vec3_t vecc);

// just in case you do't want to use the macros
vec_t _DotProduct (vec3_t v1, vec3_t v2);
void _VectorSubtract (vec3_t veca, vec3_t vecb, vec3_t out);
void _VectorAdd (vec3_t veca, vec3_t vecb, vec3_t out);
void _VectorCopy (vec3_t in, vec3_t out);

void ClearBounds (vec3_t mins, vec3_t maxs);
void AddPointToBounds (vec3_t v, vec3_t mins, vec3_t maxs);
int VectorCompare (vec3_t v1, vec3_t v2);
vec_t VectorLength (vec3_t v);
void CrossProduct (vec3_t v1, vec3_t v2, vec3_t cross);
vec_t VectorNormalize (vec3_t v);		// returns vector length
vec_t VectorNormalize2 (vec3_t v, vec3_t out);
void VectorInverse (vec3_t v);
void VectorScale (vec3_t in, vec_t scale, vec3_t out);
int Q_log2(int val);

void R_ConcatRotations (float in1[3][3], float in2[3][3], float out[3][3]);
void R_ConcatTransforms (float in1[3][4], float in2[3][4], float out[3][4]);

void AngleVectors (vec3_t angles, vec3_t forward, vec3_t right, vec3_t up);
int BoxOnPlaneSide (vec3_t emins, vec3_t emaxs, struct cplane_s *plane);
float	anglemod(float a);
float angledist( float ang );
float LerpAngle (float a1, float a2, float frac);

#define BOX_ON_PLANE_SIDE(emins, emaxs, p)	\
	(((p)->type < 3)?						\
	(										\
		((p)->dist <= (emins)[(p)->type])?	\
			1								\
		:									\
		(									\
			((p)->dist >= (emaxs)[(p)->type])?\
				2							\
			:								\
				3							\
		)									\
	)										\
	:										\
		BoxOnPlaneSide( (emins), (emaxs), (p)))

void ProjectPointOnPlane( vec3_t dst, const vec3_t p, const vec3_t normal );
void PerpendicularVector( vec3_t dst, const vec3_t src );
void RotatePointAroundVector( vec3_t dst, const vec3_t dir, const vec3_t point, float degrees );


//=============================================

#ifdef SIN
const char *COM_SkipPath (const char *pathname);
void COM_StripExtension (const char *in, char *out);
char *COM_FileExtension (const char *in);
void COM_FileBase (const char *in, char *out);
void COM_FilePath (const char *in, char *out);
void COM_DefaultExtension (char *path, const char *extension);
int  COM_ParseHex (const char *hex);
const char *COM_GetToken(const char **data_p, qboolean crossline);
const char *COM_Parse (const char **data_p);
#ifdef SIN
const char *SIN_GetToken(const char **data_p, qboolean crossline);
const char *SIN_Parse (const char **data_p);
#endif
// data is an in/out parm, returns a parsed out token

#ifndef _H2INC
void Com_sprintf (char *dest, int size, const char *fmt, ...);
#endif
#else
char *COM_SkipPath (char *pathname);
void COM_StripExtension (char *in, char *out);
void COM_FileBase (char *in, char *out);
void COM_FilePath (char *in, char *out);
void COM_DefaultExtension (char *path, char *extension);

char *COM_Parse (char **data_p);
// data is an in/out parm, returns a parsed out token

#ifndef _H2INC
void Com_sprintf (char *dest, int size, char *fmt, ...);
#endif
#endif

#ifdef _H2INC
void Com_PageInMemory (unsigned char *buffer, int size);
#else
void Com_PageInMemory (byte *buffer, int size);
#endif

//=============================================

// portable case insensitive compare
int Q_stricmp (const char *s1, const char *s2);
int Q_strcasecmp (const char *s1, const char *s2);
int Q_strncasecmp (const char *s1, const char *s2, int n);

//=============================================

#ifndef _H2INC

short	BigShort(short l);
short	LittleShort(short l);
int		BigLong (int l);
int		LittleLong (int l);
float	BigFloat (float l);
float	LittleFloat (float l);
#ifdef SIN
unsigned short	BigUnsignedShort(unsigned short l);
unsigned short	LittleUnsignedShort(unsigned short l);
#endif

#endif

void	Swap_Init (void);
#ifndef _H2INC

#ifdef SIN
const char	*va(const char *format, ...);
#else
char	*va(char *format, ...);
#endif

#endif

//=============================================

//
// key / value info strings
//
#ifdef SIN
#define	MAX_INFO_KEY		128
#define	MAX_INFO_VALUE		128
#else
#define	MAX_INFO_KEY		64
#define	MAX_INFO_VALUE		64
#endif
#define	MAX_INFO_STRING		512

#ifdef SIN
const char *Info_ValueForKey (const char *s, const char *key);
void Info_RemoveKey (char *s, const char *key);
void Info_SetValueForKey (char *s, const char *key, const char *value);
#else
char *Info_ValueForKey (char *s, char *key);
void Info_RemoveKey (char *s, char *key);
void Info_SetValueForKey (char *s, char *key, char *value);
#endif

/*
==============================================================

SYSTEM SPECIFIC

==============================================================
*/

extern	int	curtime;		// time returned by last Sys_Milliseconds

int		Sys_Milliseconds (void);
void	Sys_Mkdir (char *path);

// large block stack allocation routines
void	*Hunk_Begin (int maxsize);
void	*Hunk_Alloc (int size);
void	Hunk_Free (void *buf);
int		Hunk_End (void);

// directory searching
#define SFF_ARCH    0x01
#define SFF_HIDDEN  0x02
#define SFF_RDONLY  0x04
#define SFF_SUBDIR  0x08
#define SFF_SYSTEM  0x10

/*
** pass in an attribute mask of things you wish to REJECT
*/
#ifdef SIN
const char	*Sys_FindFirst (const char *path, unsigned musthave, unsigned canthave );
const char	*Sys_FindNext ( unsigned musthave, unsigned canthave );
#else
char	*Sys_FindFirst (char *path, unsigned musthave, unsigned canthave );
char	*Sys_FindNext ( unsigned musthave, unsigned canthave );
#endif
void	Sys_FindClose (void);


// this is only here so the functions in q_shared.c and q_shwin.c can link

#ifndef _H2INC

#ifdef SIN
void Sys_Error (const char *error, ...);
void Com_Printf (const char *msg, ...);
#else
void Sys_Error (char *error, ...);
void Com_Printf (char *msg, ...);
#endif

#endif


/*
==========================================================

CVARS (console variables)

==========================================================
*/

#ifndef CVAR
#define	CVAR

#define	CVAR_ARCHIVE	1	// set to cause it to be saved to vars.rc
#define	CVAR_USERINFO	2	// added to userinfo  when changed
#define	CVAR_SERVERINFO	4	// added to serverinfo when changed
#define	CVAR_NOSET		8	// don't allow change from console at all,
							// but can be set from the command line
#define	CVAR_LATCH		16	// save changes until server restart

// nothing outside the Cvar_*() functions should modify these fields!
typedef struct cvar_s
{
#ifdef _H2INC
   char     *AMD_name;
#else
	char		*name;
#endif
	char		*string;
	char		*latched_string;	// for CVAR_LATCH vars
	int			flags;
	qboolean	modified;	// set each time the cvar is changed
	float		value;
	struct cvar_s *next;
} cvar_t;

#endif		// CVAR

/*
==============================================================

COLLISION DETECTION

==============================================================
*/

// lower bits are stronger, and will eat weaker brushes completely
#define	CONTENTS_SOLID			1		// an eye is never valid in a solid
#define	CONTENTS_WINDOW			2		// translucent, but not watery
#ifdef SIN
#define	CONTENTS_FENCE			4
#else
#define	CONTENTS_AUX			4
#endif
#define	CONTENTS_LAVA			8
#ifdef SIN
#define	CONTENTS_LIGHTVOLUME 16
#else
#define	CONTENTS_SLIME			16
#endif
#define	CONTENTS_WATER			32
#define	CONTENTS_MIST			64
#define	LAST_VISIBLE_CONTENTS	64

// remaining contents are non-visible, and don't eat brushes
#ifdef SIN
#define	CONTENTS_DUMMYFENCE	0x1000
#endif

#define	CONTENTS_AREAPORTAL		0x8000

#define	CONTENTS_PLAYERCLIP		0x10000
#define	CONTENTS_MONSTERCLIP	0x20000

// currents can be added to any other contents, and may be mixed
#define	CONTENTS_CURRENT_0		0x40000
#define	CONTENTS_CURRENT_90		0x80000
#define	CONTENTS_CURRENT_180	0x100000
#define	CONTENTS_CURRENT_270	0x200000
#define	CONTENTS_CURRENT_UP		0x400000
#define	CONTENTS_CURRENT_DOWN	0x800000

#define	CONTENTS_ORIGIN			0x1000000	// removed before bsping an entity

#define	CONTENTS_MONSTER		0x2000000	// should never be on a brush, only in game
#define	CONTENTS_DEADMONSTER	0x4000000
#define	CONTENTS_DETAIL			0x8000000	// brushes to be added after vis leafs
#define	CONTENTS_TRANSLUCENT	0x10000000	// auto set if any surface has trans
#define	CONTENTS_LADDER			0x20000000
#define	CONTENTS_SHOOTABLE		0x40000000 // is shootable, but may not be blocking



#define	SURF_LIGHT		0x1		// value will hold the light strength

#define	SURF_SLICK		0x2		// effects game physics
#define	SURF_SKY		0x4		// don't draw, but add to skybox
#define	SURF_WARP		0x8		// turbulent water warp
#ifdef SIN
#define SURF_NONLIT     0x10    // surface is not lit
#define	SURF_NOFILTER  0x20	// surface is not filtered
#else
#define	SURF_TRANS33	0x10
#define	SURF_TRANS66	0x20
#endif
#ifdef SIN
#define	SURF_CONVEYOR	0x40
#else
#define	SURF_FLOWING	0x40	// scroll towards angle
#endif
#define	SURF_NODRAW		0x80	// don't bother referencing the texture

#ifdef SIN
#define	SURF_WAVY            0x400       // surface has waves
#define	SURF_RICOCHET		   0x800	      // projectiles bounce literally bounce off this surface
#define	SURF_PRELIT		      0x1000	   // surface has intensity information for pre-lighting
#define  SURF_CONSOLE         0x4000      // surface has a console on it
#define	SURF_HARDWAREONLY    0x10000     // surface should only do things in hardware
#define	SURF_DAMAGE          0x20000     // surface can be damaged
#define	SURF_WEAK            0x40000     // surface has weak hit points
#define	SURF_NORMAL          0x80000     // surface has normal hit points
#define	SURF_ADD             0x100000    // surface will be additive
#define	SURF_ENVMAPPED       0x200000    // surface is envmapped
#define	SURF_RANDOMANIMATE   0x400000    // surface start animating on a random frame
#define	SURF_ANIMATE         0x800000    // surface animates
#define	SURF_RNDTIME         0x1000000   // time between animations is random
#define	SURF_TRANSLATE       0x2000000   // surface translates
#define	SURF_NOMERGE         0x4000000   // surface is not merged in csg phase
#define  SURF_TYPE_BIT0       0x8000000   // 0 bit of surface type
#define  SURF_TYPE_BIT1       0x10000000  // 1 bit of surface type
#define  SURF_TYPE_BIT2       0x20000000  // 2 bit of surface type
#define  SURF_TYPE_BIT3       0x40000000  // 3 bit of surface type

#define MASK_SURF_TYPE        (SURF_TYPE_BIT0|SURF_TYPE_BIT1|SURF_TYPE_BIT2|SURF_TYPE_BIT3)

#define SURF_START_BIT        27
#define SURFACETYPE_FROM_FLAGS( x ) ( ( x >> (SURF_START_BIT) ) & 0xf )


#define  SURF_TYPE_SHIFT(x)   ( (x) << (SURF_START_BIT) ) // macro for getting proper bit mask
#define  SURF_TYPE_NONE       SURF_TYPE_SHIFT(0)
#define  SURF_TYPE_WOOD       SURF_TYPE_SHIFT(1)
#define  SURF_TYPE_METAL      SURF_TYPE_SHIFT(2)
#define  SURF_TYPE_STONE      SURF_TYPE_SHIFT(3)
#define  SURF_TYPE_CONCRETE   SURF_TYPE_SHIFT(4)
#define  SURF_TYPE_DIRT       SURF_TYPE_SHIFT(5)
#define  SURF_TYPE_FLESH      SURF_TYPE_SHIFT(6)
#define  SURF_TYPE_GRILL      SURF_TYPE_SHIFT(7)
#define  SURF_TYPE_GLASS      SURF_TYPE_SHIFT(8)
#define  SURF_TYPE_FABRIC     SURF_TYPE_SHIFT(9)
#define  SURF_TYPE_MONITOR    SURF_TYPE_SHIFT(10)
#define  SURF_TYPE_GRAVEL     SURF_TYPE_SHIFT(11)
#define  SURF_TYPE_VEGETATION SURF_TYPE_SHIFT(12)
#define  SURF_TYPE_PAPER      SURF_TYPE_SHIFT(13)
#define  SURF_TYPE_DUCT       SURF_TYPE_SHIFT(14)
#define  SURF_TYPE_WATER      SURF_TYPE_SHIFT(15)
#endif
#ifdef SIN
#define STRONG_DAMAGE_VALUE 200
#define NORMAL_DAMAGE_VALUE 90
#define WEAK_DAMAGE_VALUE 10
#endif


// content masks
#ifdef SIN

#define	MASK_ALL				(-1)
#define	MASK_SOLID				(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_FENCE)
#define	MASK_PLAYERSOLID		(CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_FENCE)
#define	MASK_DEADSOLID			(CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_FENCE)
#define	MASK_MONSTERSOLID		(CONTENTS_SOLID|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_FENCE)
#define	MASK_WATER				(CONTENTS_WATER|CONTENTS_LAVA)
#define	MASK_OPAQUE				(CONTENTS_SOLID|CONTENTS_LAVA)
#define	MASK_SHOT				(CONTENTS_SOLID|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEADMONSTER|CONTENTS_SHOOTABLE)
#define	MASK_PROJECTILE		(CONTENTS_SOLID|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEADMONSTER|CONTENTS_SHOOTABLE|CONTENTS_FENCE)
#define  MASK_CURRENT			(CONTENTS_CURRENT_0|CONTENTS_CURRENT_90|CONTENTS_CURRENT_180|CONTENTS_CURRENT_270|CONTENTS_CURRENT_UP|CONTENTS_CURRENT_DOWN)
#define  MASK_SOLIDNONFENCE   (CONTENTS_SOLID|CONTENTS_WINDOW)
#else

#define	MASK_ALL				(-1)
#define	MASK_SOLID				(CONTENTS_SOLID|CONTENTS_WINDOW)
#define	MASK_PLAYERSOLID		(CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER)
#define	MASK_DEADSOLID			(CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW)
#define	MASK_MONSTERSOLID		(CONTENTS_SOLID|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER)
#define	MASK_WATER				(CONTENTS_WATER|CONTENTS_LAVA|CONTENTS_SLIME)
#define	MASK_OPAQUE				(CONTENTS_SOLID|CONTENTS_SLIME|CONTENTS_LAVA)
#define	MASK_SHOT				(CONTENTS_SOLID|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEADMONSTER)
#define  MASK_CURRENT			(CONTENTS_CURRENT_0|CONTENTS_CURRENT_90|CONTENTS_CURRENT_180|CONTENTS_CURRENT_270|CONTENTS_CURRENT_UP|CONTENTS_CURRENT_DOWN)
#endif

// gi.BoxEdicts() can return a list of either solid or trigger entities
// FIXME: eliminate AREA_ distinction?
#define	AREA_SOLID		1
#define	AREA_TRIGGERS	2


// plane_t structure
// !!! if this is changed, it must be changed in asm code too !!!
typedef struct cplane_s
{
	vec3_t	normal;
	float	dist;
#ifdef _H2INC
   unsigned char  AMD_type;       // for fast side tests
   unsigned char  signbits;      // signx + (signy<<1) + (signz<<1)
   unsigned char  pad[2];
#else
	byte	type;			// for fast side tests
	byte	signbits;		// signx + (signy<<1) + (signz<<1)
	byte	pad[2];
#endif
} cplane_t;

// structure offset for asm code
#define CPLANE_NORMAL_X			0
#define CPLANE_NORMAL_Y			4
#define CPLANE_NORMAL_Z			8
#define CPLANE_DIST				12
#define CPLANE_TYPE				16
#define CPLANE_SIGNBITS			17
#define CPLANE_PAD0				18
#define CPLANE_PAD1				19

typedef struct cmodel_s
{
	vec3_t		mins, maxs;
	vec3_t		origin;		// for sounds or lights
	int			headnode;
} cmodel_t;

typedef struct csurface_s
{
#ifdef SIN
      char                groupname[64];     // Name of the surface
      int                 groupnumber;       // Number of the surface
      int                 flags;             // Surface flags
      int                 style;             // Style
      qboolean            trans_state;       // Translation on/off
      float               trans_mag;         // Translation magnitude
      float               trans_angle;       // Translation angle
      float               translucence;      // Translucence of the surface
      float               frequency;         // Frequency of the wavy surface / restitution of that surface
      float               magnitude;         // Magnitude of the wavy surface / friction of that surface
      float               upload_width;      // Power of 2 upload width
      float               upload_height;     // Power of 2 upload height
      vec3_t              transvec;		      // Translation vector
      float               nonlit;            // Nonlit vale
      int                 animation_frame;   // Animation frame to display
      int			        numframes;         // Number of frames of animation
      float               animtime;          // Animation time between frames
      int                 frameoffset;       // Offset for random start frame animation
      float               nextanimtime;      // Time in the future to change the animation
      float               delta_s;           // Delta s for the texture coordinates
      float               delta_t;           // Delta t for the texture coordinates
      float               last_update_time;  // Last time the surface was updated
      vec3_t              color;             // Color of the surface
      int                 leaf;              // Leaf number this surface resides in
      struct csurface_s   *next;             // Next surface in the chain
#else
      char		   name[16];
      int			flags;
      int			value;
#endif
} csurface_t;

#ifdef SIN
typedef struct
   {
   qboolean valid;
#ifdef _H2INC
   int AMD_group;
#else
   int group;
#endif
   int parentgroup;
   int tri_num;
   vec3_t position;
   vec3_t normal;
   float damage_multiplier;
   } sinmdl_intersection_t;
#endif

// a trace is returned when a box is swept through the world
typedef struct
{
	qboolean		allsolid;	// if true, plane is not valid
	qboolean		startsolid;	// if true, the initial point was in a solid area
	float			fraction;	// time completed, 1.0 = didn't hit anything
	vec3_t		endpos;		// final position
	cplane_t		plane;		// surface normal at impact
	csurface_t	*surface;	// surface hit
	int			contents;	// contents on other side of surface hit
	struct edict_s	*ent;		// not set by CM_*() functions
#ifdef SIN
   vec3_t      dir;        // the direction of the trace
   sinmdl_intersection_t intersect; // set if the trace hit a specific polygon
#endif
} trace_t;



// pmove_state_t is the information necessary for client side movement
// prediction
typedef enum
{
	// can accelerate and turn
	PM_NORMAL,
#ifdef SIN
   PM_ZOOM,
   PM_INVEHICLE_ZOOM,
#endif
	PM_SPECTATOR,
#ifdef SIN
   PM_INVEHICLE,
	PM_LOCKVIEW,
#endif
	// no acceleration or turning
	PM_DEAD,
	PM_GIB,		// different bounding box
#ifdef SIN
	PM_FREEZE,
   PM_MOVECAPTURED, // using a movement capturer
   PM_ONBIKE, // added for hoverbike
   PM_ATTACHVIEW, // added for guided missile
	PM_GRAPPLE_PULL,
#else
	PM_FREEZE
#endif
} pmtype_t;

// pmove->pm_flags
#define	PMF_DUCKED			   (1<<0)
#define	PMF_JUMP_HELD		   (1<<1)
#define	PMF_ON_GROUND		   (1<<2)
#define	PMF_TIME_WATERJUMP	(1<<3)	// pm_time is waterjump
#define	PMF_TIME_LAND		   (1<<4)	// pm_time is time before rejump
#define	PMF_TIME_TELEPORT	   (1<<5)	// pm_time is non-moving time
#define  PMF_NO_PREDICTION	   (1<<6)	// temporarily disables prediction (used for grappling hook)
#ifdef SIN
#define  PMF_MOREBITS         (1<<7)
#define	PMF_OLDNOCLIP	      (1<<8)
#define	PMF_MUTANT   	      (1<<9)
#define  PMF_ADRENALINE       (1<<10)
#define  PMF_NOAIRCLAMP       (1<<11)
#endif

#ifdef SIN
#define CROUCH_HEIGHT		36
#define CROUCH_EYE_HEIGHT	30
#define STAND_HEIGHT			72
#define STAND_EYE_HEIGHT	66
// 2015 code 
#define HOVERBIKE_HEIGHT      32
#define HOVERBIKE_EYE_HEIGHT  24
#endif

// this structure needs to be communicated bit-accurate
// from the server to the client to guarantee that
// prediction stays in sync, so no floats are used.
// if any part of the game code modifies this struct, it
// will result in a prediction error of some degree.
typedef struct
{
	pmtype_t	pm_type;

	short		origin[3];		// 12.3
	short		velocity[3];	// 12.3
	short		pm_flags;		// ducked, jump_held, etc
#ifdef _H2INC
   unsigned char pm_time;    // each unit = 8 ms
   short    AMD_gravity;
#else
	byte		pm_time;		// each unit = 8 ms

#ifdef SIN
	short		gravity : 13;
	unsigned gravity_axis : 3; // direction of gravity
#else
	short		gravity;
#endif

#endif

   short    delta_angles[3];  // add to command angles to get view direction
									// changed by spawns, rotating objects, and teleporters
} pmove_state_t;

#ifdef SIN
#define GRAVITY_AXIS_SHIFT 13
#define GRAVITY_AXIS_MASK	0xe000
#define GRAVITY_MASK			( ~GRAVITY_AXIS_MASK )
#define GRAVITY_NUM_AXIS	6

typedef struct
	{
	int x;
	int y;
	int z;
	int sign;
	} gravityaxis_t;

extern const gravityaxis_t gravity_axis[ GRAVITY_NUM_AXIS ];

#endif

//
// button bits
//
#define	BUTTON_ATTACK		1
#define	BUTTON_USE			2
#ifdef SIN
// 2015 code
#define BUTTON_JUMP        4 // for detecting when the player is jumping
#endif
#define	BUTTON_ANY			128			// any key whatsoever


// usercmd_t is sent to the server each client frame
#ifdef _H2INC
typedef struct usercmd_s
{
   unsigned char  msec;
   unsigned char  buttons;
	short	angles[3];
	short	forwardmove, sidemove, upmove;
   unsigned char  impulse;    // remove?
   unsigned char  lightlevel;    // light level the player is standing on
   unsigned char  debris;     // have we been hit by debris?
} usercmd_t;

#else

typedef struct usercmd_s
{
	byte	msec;
	byte	buttons;
	short	angles[3];
	short	forwardmove, sidemove, upmove;
	byte	impulse;		// remove?
	byte	lightlevel;		// light level the player is standing on
#ifdef SIN
   byte  debris;     // have we been hit by debris?
#endif
} usercmd_t;

#endif


#define	MAXTOUCH	32
typedef struct
{
	// state (in / out)
	pmove_state_t	s;

	// command (in)
	usercmd_t		cmd;
	qboolean		snapinitial;	// if s has been changed outside pmove

	// results (out)
	int			numtouch;
	struct edict_s	*touchents[MAXTOUCH];

	vec3_t		viewangles;			// clamped
	float		viewheight;

	vec3_t		mins, maxs;			// bounding box size

	struct edict_s	*groundentity;

#ifdef SIN
	csurface_t		*groundsurface;
	cplane_t			groundplane;
	int				groundcontents;
#endif

	int			watertype;
	int			waterlevel;

   qboolean    onladder;         // is he on a ladder

	// callbacks to test the world
	trace_t		(*trace) (vec3_t start, vec3_t mins, vec3_t maxs, vec3_t end);
	int			(*pointcontents) (vec3_t point);
} pmove_t;


// entity_state_t->effects
// Effects are things handled on the client side (lights, particles, frame animations)
// that happen constantly on the given entity.
// An entity that has effects will be sent to the client
// even if it has a zero index model.
#ifdef SIN
#define	EF_ROTATE			(1<<0)	   	// rotate (bonus items)
#define	EF_ROCKET			(1<<1)   		// redlight + trail
#define	EF_GIB				(1<<2)   		// leave a trail
#define  EF_PULSE          (1<<3)         // pulsecannon projectile effect
#define  EF_SMOOTHANGLES	(1<<4)			// 16-bit angles over net
#define  EF_EVERYFRAME  	(1<<5)			// def commands will be run every client frame
#define  EF_CROUCH         (1<<6)         // character is crouching
#define  EF_EFFECTS_16		(1<<7)			// reserved for net transmission
#define	EF_GRAVITY_AXIS_0	(1<<8)			// bit 0 of gravity axis
#define	EF_GRAVITY_AXIS_1	(1<<9)			// bit 1 of gravity axis
#define	EF_GRAVITY_AXIS_2	(1<<10)			// bit 2 of gravity axis
#define  EF_BEAMEFFECT     (1<<11)        // Beams effect
#define	EF_AUTO_ANIMATE	(1<<12)			// auto animate
#define	EF_NOFOOTSTEPS    (1<<13)			// don't play footsteps on model
#define  EF_EFFECTS_32		(1<<15)			// reserved for net transmission

#define EF_WARM            (1<<14)     // used to signify something that should be
                                       // light up by therm-optic goggles
#define EF_HOVER           (1<<16)     // hovering effect for the hoverbike
#define EF_HOVERTHRUST     (1<<17)     // engine thrust hoverbike effect
#define EF_HOVERTURBO      (1<<18)     // turbo thrust hoverbike effect
#define EF_VIEWMODEL       (1<<19)     // entity is a secondary view model
#define EF_ANIMEROCKET     (1<<20)     // added effect for anime rockets
#define EF_FLAMES          (1<<21)     // added flame trail effect
#define EF_DEATHFLAMES     (1<<22)     // added flame trail effect
#define EF_PLASMATRAIL1    (1<<23)     // trail effect for plasma bow
#define EF_PLASMATRAIL2    (1<<24)     // secondary trail effect for plasma bow
#define EF_NUKETRAIL       (1<<25)     // particle effect for a flying nuke ball

#define  EF_FORCEBASELINE  EF_CROUCH      // used to make sure we create a baseline for entities that wouldn't be processed
                                          // ordinarily.

#define EFFECTS_TO_GRAVITYAXIS( effect )   \
	( ( ( effect ) & ( EF_GRAVITY_AXIS_0 | EF_GRAVITY_AXIS_1 | EF_GRAVITY_AXIS_2 ) ) >> 8 )

#define GRAVITYAXIS_TO_EFFECTS( gravaxis )   \
	( ( ( gravaxis ) << 8 ) & ( EF_GRAVITY_AXIS_0 | EF_GRAVITY_AXIS_1 | EF_GRAVITY_AXIS_2 ) )

#else
#define	EF_ROTATE			0x00000001		// rotate (bonus items)
#define	EF_GIB				0x00000002		// leave a trail
#define	EF_BLASTER			0x00000008		// redlight + trail
#define	EF_ROCKET			0x00000010		// redlight + trail
#define	EF_GRENADE			0x00000020
#define	EF_HYPERBLASTER		0x00000040
#define	EF_BFG				0x00000080
#define EF_COLOR_SHELL		0x00000100
#define EF_POWERSCREEN		0x00000200
#define	EF_ANIM01			0x00000400		// automatically cycle between frames 0 and 1 at 2 hz
#define	EF_ANIM23			0x00000800		// automatically cycle between frames 2 and 3 at 2 hz
#define EF_ANIM_ALL			0x00001000		// automatically cycle through all frames at 2hz
#define EF_ANIM_ALLFAST		0x00002000		// automatically cycle through all frames at 10hz
#define	EF_FLIES			0x00004000
#define	EF_QUAD				0x00008000
#define	EF_PENT				0x00010000
#endif


#ifdef SIN

// model commands

#define  MDL_GROUP_SKINOFFSET_BIT0  0x0001
#define  MDL_GROUP_SKINOFFSET_BIT1  0x0002
#define  MDL_GROUP_FULLBRIGHT       0x0004
#define  MDL_GROUP_ENVMAPPED_GOLD   0x0008
#define  MDL_GROUP_ENVMAPPED_SILVER 0x0010
#define  MDL_GROUP_TRANSLUCENT_33   0x0020
#define  MDL_GROUP_TRANSLUCENT_66   0x0040
#define  MDL_GROUP_NODRAW           0x0080

//
// STATIC flags NEVER sent over the net
//
#define  MDL_GROUP_SURFACETYPE_BIT0 0x0100
#define  MDL_GROUP_SURFACETYPE_BIT1 0x0200
#define  MDL_GROUP_SURFACETYPE_BIT2 0x0400
#define  MDL_GROUP_SURFACETYPE_BIT3 0x0800
#define  MDL_GROUP_RICOCHET         0x1000
#define  MDL_GROUP_SKIN_NO_DAMAGE   0x2000
#define  MDL_GROUP_MASKED           0x4000
#define  MDL_GROUP_TWOSIDED         0x8000

// 2015 code
#define BONE_ORIGIN        0xfff
#define BONE_2015ATTACH    0x800

#endif

#ifdef SIN
// Particle flags
#define PARTICLE_RANDOM       (1<<0)
#define PARTICLE_OVERBRIGHT   (1<<1)
// 2015 code
#define PARTICLE_ADDITIVE     (1<<2) // draws the particle additively
#define PARTICLE_FIRE         (1<<3) // draws it as a fire particle
#define PARTICLE_HITSOLID     (1<<4) // collision detect solid objects
#define PARTICLE_HITENTS      (1<<5) // collision detect entities
#define PARTICLE_HITREMOVE    (1<<6) // remove the particle when it hits something
#endif

// entity_state_t->renderfx flags
#ifdef SIN

#define	RF_MINLIGHT			(1<<0)		// allways have some light (viewmodel)
#define	RF_VIEWERMODEL		(1<<1)   	// don't draw through eyes, only mirrors
#define	RF_WEAPONMODEL		(1<<2)		// only draw through eyes
#define	RF_FULLBRIGHT		(1<<3)		// allways draw full intensity
#define	RF_ENVMAPPED		(1<<4)		// model is environment mapped completely
#define	RF_TRANSLUCENT		(1<<5)
#define	RF_FRAMELERP		(1<<6)
#define	RF_BEAM				(1<<7)
#define	RF_CUSTOMSKIN		(1<<8)		// skin is an index in image_precache
#define	RF_GLOW				(1<<9)		// pulse lighting for bonus items
#define  RF_DONTDRAW			(1<<10)
#define  RF_LENSFLARE      (1<<11)
#define  RF_DLIGHT         (1<<12)
#define  RF_DETAIL         (1<<13)     // Culls a model based on the distance away from you
#define  RF_LIGHTOFFSET    (1<<14)
#define  RF_XFLIP          (1<<15)     // flip the model in x space (used for weapon models)

#else

#define	RF_MINLIGHT			1		// allways have some light (viewmodel)
#define	RF_VIEWERMODEL		2		// don't draw through eyes, only mirrors
#define	RF_WEAPONMODEL		4		// only draw through eyes
#define	RF_FULLBRIGHT		8		// allways draw full intensity
#define	RF_DEPTHHACK		16		// for view weapon Z crunching
#define	RF_TRANSLUCENT		32
#define	RF_FRAMELERP		64
#define	RF_BEAM				128
#define	RF_CUSTOMSKIN		256		// skin is an index in image_precache
#define	RF_GLOW				512		// pulse lighting for bonus items
#define	RF_SHELL_RED		1024
#define	RF_SHELL_GREEN		2048
#define	RF_SHELL_BLUE		4096

#endif

// player_state_t->refdef flags
#define	RDF_UNDERWATER		1		// warp the screen as apropriate
#define RDF_NOWORLDMODEL	2		// used for player configuration screen
#ifdef SIN
#define RDF_NOCLEAR	      4		// used for player configuration screen, don't clear behind the screen
#define RDF_NOENTITIES     8     // used for menu, so entites don't get drawn
#endif

#ifndef SIN
//
// muzzle flashes / player effects
//
#define	MZ_BLASTER			0
#define MZ_MACHINEGUN		1
#define	MZ_SHOTGUN			2
#define	MZ_CHAINGUN1		3
#define	MZ_CHAINGUN2		4
#define	MZ_CHAINGUN3		5
#define	MZ_RAILGUN			6
#define	MZ_ROCKET			7
#define	MZ_GRENADE			8
#define	MZ_LOGIN			9
#define	MZ_LOGOUT			10
#define	MZ_RESPAWN			11
#define	MZ_BFG				12
#define	MZ_SSHOTGUN			13
#define	MZ_HYPERBLASTER		14
#define	MZ_ITEMRESPAWN		15
#define MZ_SILENCED			128		// bit flag ORed with one of the above numbers

//
// monster muzzle flashes
//
#define MZ2_TANK_BLASTER_1				1
#define MZ2_TANK_BLASTER_2				2
#define MZ2_TANK_BLASTER_3				3
#define MZ2_TANK_MACHINEGUN_1			4
#define MZ2_TANK_MACHINEGUN_2			5
#define MZ2_TANK_MACHINEGUN_3			6
#define MZ2_TANK_MACHINEGUN_4			7
#define MZ2_TANK_MACHINEGUN_5			8
#define MZ2_TANK_MACHINEGUN_6			9
#define MZ2_TANK_MACHINEGUN_7			10
#define MZ2_TANK_MACHINEGUN_8			11
#define MZ2_TANK_MACHINEGUN_9			12
#define MZ2_TANK_MACHINEGUN_10			13
#define MZ2_TANK_MACHINEGUN_11			14
#define MZ2_TANK_MACHINEGUN_12			15
#define MZ2_TANK_MACHINEGUN_13			16
#define MZ2_TANK_MACHINEGUN_14			17
#define MZ2_TANK_MACHINEGUN_15			18
#define MZ2_TANK_MACHINEGUN_16			19
#define MZ2_TANK_MACHINEGUN_17			20
#define MZ2_TANK_MACHINEGUN_18			21
#define MZ2_TANK_MACHINEGUN_19			22
#define MZ2_TANK_ROCKET_1				23
#define MZ2_TANK_ROCKET_2				24
#define MZ2_TANK_ROCKET_3				25

#define MZ2_INFANTRY_MACHINEGUN_1		26
#define MZ2_INFANTRY_MACHINEGUN_2		27
#define MZ2_INFANTRY_MACHINEGUN_3		28
#define MZ2_INFANTRY_MACHINEGUN_4		29
#define MZ2_INFANTRY_MACHINEGUN_5		30
#define MZ2_INFANTRY_MACHINEGUN_6		31
#define MZ2_INFANTRY_MACHINEGUN_7		32
#define MZ2_INFANTRY_MACHINEGUN_8		33
#define MZ2_INFANTRY_MACHINEGUN_9		34
#define MZ2_INFANTRY_MACHINEGUN_10		35
#define MZ2_INFANTRY_MACHINEGUN_11		36
#define MZ2_INFANTRY_MACHINEGUN_12		37
#define MZ2_INFANTRY_MACHINEGUN_13		38

#define MZ2_SOLDIER_BLASTER_1			39
#define MZ2_SOLDIER_BLASTER_2			40
#define MZ2_SOLDIER_SHOTGUN_1			41
#define MZ2_SOLDIER_SHOTGUN_2			42
#define MZ2_SOLDIER_MACHINEGUN_1		43
#define MZ2_SOLDIER_MACHINEGUN_2		44

#define MZ2_GUNNER_MACHINEGUN_1			45
#define MZ2_GUNNER_MACHINEGUN_2			46
#define MZ2_GUNNER_MACHINEGUN_3			47
#define MZ2_GUNNER_MACHINEGUN_4			48
#define MZ2_GUNNER_MACHINEGUN_5			49
#define MZ2_GUNNER_MACHINEGUN_6			50
#define MZ2_GUNNER_MACHINEGUN_7			51
#define MZ2_GUNNER_MACHINEGUN_8			52
#define MZ2_GUNNER_GRENADE_1			53
#define MZ2_GUNNER_GRENADE_2			54
#define MZ2_GUNNER_GRENADE_3			55
#define MZ2_GUNNER_GRENADE_4			56

#define MZ2_CHICK_ROCKET_1				57

#define MZ2_FLYER_BLASTER_1				58
#define MZ2_FLYER_BLASTER_2				59

#define MZ2_MEDIC_BLASTER_1				60

#define MZ2_GLADIATOR_RAILGUN_1			61

#define MZ2_HOVER_BLASTER_1				62

#define MZ2_ACTOR_MACHINEGUN_1			63

#define MZ2_SUPERTANK_MACHINEGUN_1		64
#define MZ2_SUPERTANK_MACHINEGUN_2		65
#define MZ2_SUPERTANK_MACHINEGUN_3		66
#define MZ2_SUPERTANK_MACHINEGUN_4		67
#define MZ2_SUPERTANK_MACHINEGUN_5		68
#define MZ2_SUPERTANK_MACHINEGUN_6		69
#define MZ2_SUPERTANK_ROCKET_1			70
#define MZ2_SUPERTANK_ROCKET_2			71
#define MZ2_SUPERTANK_ROCKET_3			72

#define MZ2_BOSS2_MACHINEGUN_L1			73
#define MZ2_BOSS2_MACHINEGUN_L2			74
#define MZ2_BOSS2_MACHINEGUN_L3			75
#define MZ2_BOSS2_MACHINEGUN_L4			76
#define MZ2_BOSS2_MACHINEGUN_L5			77
#define MZ2_BOSS2_ROCKET_1				78
#define MZ2_BOSS2_ROCKET_2				79
#define MZ2_BOSS2_ROCKET_3				80
#define MZ2_BOSS2_ROCKET_4				81

#define MZ2_FLOAT_BLASTER_1				82

#define MZ2_SOLDIER_BLASTER_3			83
#define MZ2_SOLDIER_SHOTGUN_3			84
#define MZ2_SOLDIER_MACHINEGUN_3		85
#define MZ2_SOLDIER_BLASTER_4			86
#define MZ2_SOLDIER_SHOTGUN_4			87
#define MZ2_SOLDIER_MACHINEGUN_4		88
#define MZ2_SOLDIER_BLASTER_5			89
#define MZ2_SOLDIER_SHOTGUN_5			90
#define MZ2_SOLDIER_MACHINEGUN_5		91
#define MZ2_SOLDIER_BLASTER_6			92
#define MZ2_SOLDIER_SHOTGUN_6			93
#define MZ2_SOLDIER_MACHINEGUN_6		94
#define MZ2_SOLDIER_BLASTER_7			95
#define MZ2_SOLDIER_SHOTGUN_7			96
#define MZ2_SOLDIER_MACHINEGUN_7		97
#define MZ2_SOLDIER_BLASTER_8			98
#define MZ2_SOLDIER_SHOTGUN_8			99
#define MZ2_SOLDIER_MACHINEGUN_8		100

// --- Xian shit below ---
#define	MZ2_MAKRON_BFG					101
#define MZ2_MAKRON_BLASTER_1			102
#define MZ2_MAKRON_BLASTER_2			103
#define MZ2_MAKRON_BLASTER_3			104
#define MZ2_MAKRON_BLASTER_4			105
#define MZ2_MAKRON_BLASTER_5			106
#define MZ2_MAKRON_BLASTER_6			107
#define MZ2_MAKRON_BLASTER_7			108
#define MZ2_MAKRON_BLASTER_8			109
#define MZ2_MAKRON_BLASTER_9			110
#define MZ2_MAKRON_BLASTER_10			111
#define MZ2_MAKRON_BLASTER_11			112
#define MZ2_MAKRON_BLASTER_12			113
#define MZ2_MAKRON_BLASTER_13			114
#define MZ2_MAKRON_BLASTER_14			115
#define MZ2_MAKRON_BLASTER_15			116
#define MZ2_MAKRON_BLASTER_16			117
#define MZ2_MAKRON_BLASTER_17			118
#define MZ2_MAKRON_RAILGUN_1			119
#define	MZ2_JORG_MACHINEGUN_L1			120
#define	MZ2_JORG_MACHINEGUN_L2			121
#define	MZ2_JORG_MACHINEGUN_L3			122
#define	MZ2_JORG_MACHINEGUN_L4			123
#define	MZ2_JORG_MACHINEGUN_L5			124
#define	MZ2_JORG_MACHINEGUN_L6			125
#define	MZ2_JORG_MACHINEGUN_R1			126
#define	MZ2_JORG_MACHINEGUN_R2			127
#define	MZ2_JORG_MACHINEGUN_R3			128
#define	MZ2_JORG_MACHINEGUN_R4			129
#define MZ2_JORG_MACHINEGUN_R5			130
#define	MZ2_JORG_MACHINEGUN_R6			131
#define MZ2_JORG_BFG_1					132
#define MZ2_BOSS2_MACHINEGUN_R1			133
#define MZ2_BOSS2_MACHINEGUN_R2			134
#define MZ2_BOSS2_MACHINEGUN_R3			135
#define MZ2_BOSS2_MACHINEGUN_R4			136
#define MZ2_BOSS2_MACHINEGUN_R5			137

extern	vec3_t monster_flash_offset [];
#endif

// temp entity events
//
// Temp entity events are for things that happen
// at a location seperate from any existing entity.
// Temporary entity messages are explicitly constructed
// and broadcast.
typedef enum
{
	TE_GUNSHOT,
#ifndef SIN
	TE_BLOOD,
	TE_BLASTER,
	TE_RAILTRAIL,
	TE_SHOTGUN,
	TE_EXPLOSION1,
	TE_EXPLOSION2,
	TE_ROCKET_EXPLOSION,
	TE_GRENADE_EXPLOSION,
	TE_SPARKS,
	TE_SPLASH,
	TE_BUBBLETRAIL,
	TE_SCREEN_SPARKS,
	TE_SHIELD_SPARKS,
	TE_BULLET_SPARKS,
	TE_LASER_SPARKS,
	TE_PARASITE_ATTACK,
	TE_ROCKET_EXPLOSION_WATER,
	TE_GRENADE_EXPLOSION_WATER,
	TE_MEDIC_CABLE_ATTACK,
	TE_BFG_EXPLOSION,
	TE_BFG_BIGEXPLOSION,
	TE_BOSSTPORT,		// used as '22' in a map, so DON'T RENUMBER!!!
   TE_SPARKS,
#else
   TE_PARTICLES,
   TE_RANDOM_PARTICLES,
   TE_TESSELATE,
   TE_LASER,
   TE_BURNWALL,
   TE_TEMPMODEL,
   TE_STRIKE,
   TE_DLIGHT,
   TE_ROCKET_EXPLOSION,
   TE_BEAM,
   TE_DAMAGE_WALL,
   TE_TELEPORT_EFFECT,
   TE_BULLET_SPRAY,
   TE_SCALED_EXPLOSION,
   TE_PULSE_EXPLOSION,
   // 2015 code
   TE_FLAMETHROWER, // flames for the flamethrower
   TE_FLAMETHROWERROW, // row of flames for the flamethrower
   TE_FLAMETHROWERHIT, // hit flames for the flamethrower
   TE_FLAME, // a puff or row of flames (multipurpose)
   TE_NUKE_EXPLOSION, // fire explosion entity for the nuke
   TE_BOW_EXPLOSION, // explosion entity for the bow
   TE_HOVERBOOSTER, // vertical booster effect for the hoverbike
   TE_SIZED_PARTICLES,
   TE_RANDOM_SIZED_PARTICLES,
   TE_PARTICLES_FULL,
   TE_RANDOM_PARTICLES_FULL,
   TE_TRACER // bullet tracer
#endif
} temp_event_t;

#ifdef SIN
#define TM_ORIGIN 0x01
#define TM_ANGLES 0x02
#define TM_ANIM   0x04
#define TM_SCALE  0x08
#define TM_FLAGS  0x10
#define TM_OWNER  0x20
#define TM_LIFE   0x40
#define TM_ALPHA  0x80

#define TEMPMODEL_RANDOM_ROLL    0x0001
#define TEMPMODEL_AUTO_ANIMATE   0x0002
#define TEMPMODEL_ANIMATE_ONCE   0x0004
#define TEMPMODEL_ANIMATE_FAST   0x0008
#define TEMPMODEL_RANDOM_PITCH   0x0010
#define TEMPMODEL_RANDOM_YAW     0x0020
#define TEMPMODEL_ALPHAFADE      0x0040
#define TEMPMODEL_ANIMATE_SCALE  0x0080

//
// these flags are not sent over the net for now
//
#define TEMPMODEL_USE_PHYSICS          0x0100
#define TEMPMODEL_BOUNCE               0x0200
#define TEMPMODEL_TOUCH_DIE            0x0400
#define TEMPMODEL_LERP                 0x0800
#define TEMPMODEL_FRAMELERP            0x1000
#define TEMPMODEL_TOUCH_DIE_NO_FADE    0x2000

#define BM_ALPHA                    (1<<0)
#define BM_SCALE                    (1<<1)
#define BM_FLAGS                    (1<<2)
#define BM_LIFE                     (1<<3)

#define BEAM_AUTO_ANIMATE           (1<<0)
#define BEAM_ANIMATE_ONCE           (1<<1)
#define BEAM_ANIMATE_FAST           (1<<2)
#define BEAM_ROLL                   (1<<3)
#define BEAM_ANIMATE_RANDOM_START   (1<<4)
#define BEAM_LIGHTNING_EFFECT       (1<<5)
#define BEAM_RANDOM_ALPHA           (1<<6)

#define TESS_ORIGIN        0x01
#define TESS_MINSIZE       0x02
#define TESS_MAXSIZE       0x04
#define TESS_DIR           0x08
#define TESS_POWER         0x10
#define TESS_PERCENT       0x20
#define TESS_THICK         0x40
#define TESS_ENTNUM        0x80
#define TESS_LIGHTSTYLE    0x100
#define TESS_TYPE          0x200

#define TESSELATE_FALL              1
#define TESSELATE_EXPANDANDSHRINK   2
#define TESSELATE_EXPLODE           3
#define TESSELATE_FALLANDTRAIL      4
#define TESSELATE_IMPLODE           5

#define TESS_DEFAULT_MIN_SIZE    10
#define TESS_DEFAULT_MAX_SIZE    25
#define TESS_DEFAULT_PERCENT     0.15f
#define TESS_DEFAULT_POWER       128
#define TESS_DEFAULT_LIGHTSTYLE  125
#define TESS_DEFAULT_TYPE        0

#endif

#define SPLASH_UNKNOWN		0
#define SPLASH_SPARKS		1
#define SPLASH_BLUE_WATER	2
#define SPLASH_BROWN_WATER	3
#define SPLASH_SLIME		4
#define	SPLASH_LAVA			5
#define SPLASH_BLOOD		6


// sound channels
// channel 0 never willingly overrides
// other channels (1-7) allways override a playing sound on that channel
#define	CHAN_AUTO               0
#define	CHAN_WEAPON             1
#define	CHAN_VOICE              2
#define	CHAN_ITEM               3
#define	CHAN_BODY               4
#define  CHAN_DIALOG             5
#define  CHAN_DIALOG_SECONDARY   6
#define  CHAN_WEAPONIDLE         7
// modifier flags
#define	CHAN_NO_PHS_ADD			8	// send to all clients, not just ones in PHS (ATTN 0 will also do this)
#define	CHAN_RELIABLE			16	// send by reliable message, not datagram


// sound attenuation values
#define	ATTN_NONE               0	// full volume the entire level
#define	ATTN_NORM               1
#define	ATTN_IDLE               2
#define	ATTN_STATIC             3	// diminish very rapidly with distance



#ifdef SIN
#define STAT_HEALTH				    0
#define STAT_WEAPONLIST			    1
#define STAT_AMMO					    2
#define STAT_SELECTED_ICON		    3  // Icon of currently selected inventory item
#define STAT_SELECTED_AMOUNT      4  // Amount of this item
#define STAT_PREVIOUS_ICON        5  // Icon of previous inventory item
#define STAT_NEXT_ICON            6  // Icon of next inventory item
#define STAT_PICKUP_ICON		    7
#define STAT_PICKUP_STRING		    8
#define STAT_LAYOUTS			 	    9
#define STAT_FRAGS				   10
#define STAT_FLASHES 			   11
#define STAT_AMMO_BULLET357      12
#define STAT_AMMO_SHOTGUN        13
#define STAT_AMMO_BULLET10MM     14
#define STAT_AMMO_BULLET50MM     15
#define STAT_AMMO_BULLETPULSE    16
#define STAT_AMMO_BULLETSNIPER   17
#define STAT_AMMO_ROCKETS        18
#define STAT_AMMO_SPIDERMINES    19
#define STAT_ARMOR_HEAD          20
#define STAT_ARMOR_BODY          21
#define STAT_ARMOR_LEGS          22
#define STAT_ARMOR               23
#define STAT_SELECTED_MODELINDEX 24
#define STAT_CURRENT_WEAPON      25
#define STAT_CROSSHAIR           26
#define STAT_CLIPAMMO            27
#define STAT_POWERUPTIMER        28
#define STAT_POWERUPTYPE         29
#define STAT_SELECTED_NAME       30
#define STAT_EXITSIGN			   31		// cleared each frame

// 2015 code 
#define STAT_LASTLAP    12 // this is set to the client's last lap time * 10
#define STAT_CURRENTLAP    13 // this is set to the client's current lap time * 10
#define STAT_CPCOUNT    14 // number of checkpoints left to touch this lap
#define STAT_NIGHTVISION   15 // set when player is in night vision mode

#ifdef SIN_ARCADE
#define STAT_FIRSTPLACE       16  // set if the player is in first place
#define STAT_DRAWFIRSTPLACE   17  // set if the player is in first place and we should show the icon
#endif

#define P_SHIELDS                 1
#define P_ADRENALINE              2
#define P_CLOAK                   3
#define P_MUTAGEN                 4
#define P_OXYGEN                  5

#else

// player_state->stats[] indexes
#define STAT_HEALTH_ICON		0
#define STAT_HEALTH				1
#define STAT_AMMO_ICON			2
#define STAT_AMMO					3
#define STAT_ARMOR_ICON			4
#define STAT_ARMOR				5
#define STAT_SELECTED_ICON		6
#define STAT_PICKUP_ICON		7
#define STAT_PICKUP_STRING		8
#define STAT_TIMER_ICON			9
#define STAT_TIMER				10
#define STAT_HELPICON			11
#define STAT_SELECTED_ITEM		12
#define STAT_LAYOUTS				13
#define STAT_FRAGS				14
#define STAT_FLASHES				15		// cleared each frame, 1 = health, 2 = armor
#endif


#define MAX_STATS					32

#ifdef SIN
#define NUM_AMMO_TYPES        8
// 2015 code
// added new ammo types
#define NUM_2015_AMMO_TYPES   4 // number of additional 2015 ammo types
#define STAT_AMMO_BASE        (STAT_AMMO_BULLET357)
#define NUM_ARMOR_TYPES       3
#define STAT_ARMOR_BASE       (STAT_ARMOR_HEAD)
#endif

#ifdef SIN
#define DRAW_STATS				(1<<0)
#define DRAW_SPECTATOR   		(1<<1)
#define DRAW_MISSIONCPU       (1<<2)
#define DRAW_SCORES           (1<<3)
#define DRAW_OVERLAY          (1<<4)
#else
#define DRAW_STATS				(1<<0)
#define DRAW_LAYOUT				(1<<1)
#define DRAW_INVENTORY			(1<<2)
#endif

#ifdef SIN
// dmflags->value flags
#define DF_NO_HEALTH				(1<<0)
#define DF_NO_POWERUPS   		(1<<1)
#define DF_WEAPONS_STAY			(1<<2)
#define DF_NO_FALLING			(1<<3)
#define DF_INSTANT_ITEMS		(1<<4)
#define DF_SAME_LEVEL			(1<<5)
#define DF_SKINTEAMS				(1<<6)
#define DF_MODELTEAMS			(1<<7)
#define DF_FRIENDLY_FIRE		(1<<8)
#define DF_SPAWN_FARTHEST		(1<<9)
#define DF_FORCE_RESPAWN		(1<<10)
#define DF_NO_ARMOR				(1<<11)
#define DF_FAST_WEAPONS			(1<<12)
#define DF_NOEXIT             (1<<13)
#define DF_INFINITE_AMMO      (1<<14)
#define DF_FIXED_FOV          (1<<15)
#define DF_NO_DROP_WEAPONS    (1<<16)
#define DF_NO_WEAPON_CHANGE   (1<<17)

// 2015 code
#define DF_BBOX_BULLETS    (1<<17)
#define DF_AUTO_INFORMER   (1<<18)
#define DF_INFORMER_LOCK   (1<<19)
#define DF_MIDNIGHT        (1<<20) // wasn't able to get implimented
#define DF_FLASHLIGHT      (1<<21)
#define DF_FLASHLIGHTON    (1<<22)
#define DF_GOGGLES         (1<<23)
#define DF_GOGGLESON       (1<<24)

#else

// dmflags->value flags
#define DF_NO_HEALTH				1
#define DF_NO_ITEMS				2
#define DF_WEAPONS_STAY			4
#define DF_NO_FALLING			8
#define DF_INSTANT_ITEMS		16
#define DF_SAME_LEVEL			32
#define DF_SKINTEAMS				64
#define DF_MODELTEAMS			128
#define DF_FRIENDLY_FIRE		256
#define DF_SPAWN_FARTHEST		512
#define DF_FORCE_RESPAWN		1024
#define DF_NO_ARMOR				2048

#endif


/*
==========================================================

  ELEMENTS COMMUNICATED ACROSS THE NET

==========================================================
*/

#define	ANGLE2SHORT(x)	((int)((x)*65536/360) & 65535)
#define	SHORT2ANGLE(x)	((x)*(360.0/65536))


#ifdef SIN
//
// config strings are a general means of communication from
// the server to all connected clients.
// Each config string can be at most MAX_QPATH characters.
//
#define	CS_NAME				0
#define	CS_CDTRACK			1
#define	CS_SKY				2
#define	CS_SKYAXIS			3		// %f %f %f format
#define	CS_SKYROTATE		4
#define	CS_MAXCLIENTS		5
#define	CS_STATUSBAR		6		// display program string
                                 // STATUSBAR reserves configstrings from 6-30
#define	CS_MAPCHECKSUM		31		// for catching cheater maps
#define	CS_MODELS			32
#define	CS_SOUNDS			(CS_MODELS+MAX_MODELS)
#define	CS_IMAGES			(CS_SOUNDS+MAX_SOUNDS)
#define	CS_LIGHTS			(CS_IMAGES+MAX_IMAGES)
#define	CS_ITEMS			(CS_LIGHTS+MAX_LIGHTSTYLES)
#define	CS_PLAYERSKINS		(CS_ITEMS+MAX_ITEMS)
#define  CS_SOUNDTRACK     (CS_PLAYERSKINS+MAX_CLIENTS)

// 2015 code
#define  CS_CHECKPOINTS    (CS_SOUNDTRACK + 1)
#define  CS_BIKESKINS      (CS_CHECKPOINTS + 1)
#define  MAX_CONFIGSTRINGS (CS_BIKESKINS + MAX_CLIENTS) // # of config strings with 2015 stuff
#define  MAX_NORMCONFIGSTRINGS   (CS_SOUNDTRACK + 1) // # of config strings in original Sin

#else

//
// config strings are a general means of communication from
// the server to all connected clients.
// Each config string can be at most MAX_QPATH characters.
//
#define	CS_NAME				0
#define	CS_CDTRACK			1
#define	CS_SKY				2
#define	CS_SKYAXIS			3		// %f %f %f format
#define	CS_SKYROTATE		4
#define	CS_STATUSBAR		5		// display program string
                                 // STATUSBAR reserves configstrings from 5-30
#define	CS_MAPCHECKSUM		31		// for catching cheater maps
#define	CS_MODELS			32
#define	CS_SOUNDS			(CS_MODELS+MAX_MODELS)
#define	CS_IMAGES			(CS_SOUNDS+MAX_SOUNDS)
#define	CS_LIGHTS			(CS_IMAGES+MAX_IMAGES)
#define	CS_ITEMS			(CS_LIGHTS+MAX_LIGHTSTYLES)
#define	CS_PLAYERSKINS		(CS_ITEMS+MAX_ITEMS)
#define	MAX_CONFIGSTRINGS	(CS_PLAYERSKINS+MAX_CLIENTS)

#endif


//==============================================


// entity_state_t->event values
// ertity events are for effects that take place reletive
// to an existing entities origin.  Very network efficient.
// All muzzle flashes really should be converted to events...
typedef enum
{
	EV_NONE,
	EV_ITEM_RESPAWN,
	EV_FOOTSTEP,
	EV_FALLSHORT,
	EV_MALE_FALL,
	EV_MALE_FALLFAR,
	EV_FEMALE_FALL,
	EV_FEMALE_FALLFAR,
	EV_PLAYER_TELEPORT
} entity_event_t;

#ifdef SIN
#define MAX_MODEL_GROUPS   24
typedef struct
   {
   int              group_num; // the group which the triangle belongs to
   int              tri_num; // the actual triangle at which the bone is
   vec3_t           orientation; // orientation of bone
   } bone_t;
#endif
// entity_state_t is the information conveyed from the server
// in an update message about entities that the client will
// need to render in some way
typedef struct entity_state_s
{
	int		number;			// edict index

	vec3_t	origin;
	vec3_t	angles;

#ifdef SIN
	float		quat[ 4 ];
	float		mat[ 3 ][ 3 ];
#endif

	vec3_t	old_origin;		// for lerping
	int		modelindex;
#ifndef SIN
	int		modelindex2, modelindex3, modelindex4;	// weapons, CTF flags, etc
#endif
	int		frame;
#ifdef SIN
	int		prevframe;
   vec3_t   vieworigin;
   vec3_t   viewangles;
   int      anim;
   float    scale;
   float    alpha;
   float    color_r;
   float    color_g;
   float    color_b;
   int      radius;
   bone_t   bone;
   int      parent;
   int      numgroups;
#ifdef _H2INC
   unsigned char groups[MAX_MODEL_GROUPS];
#else
   byte     groups[MAX_MODEL_GROUPS];
#endif
   int      gunanim;
   int      gunframe;
   int      gunmodelindex;
   int      lightofs;
#endif
	int		skinnum;
	int		effects;
	int		renderfx;
#ifdef SIN
	int		solid;	// for client side prediction
                     // (bits 0-7) is x radius
                     // (bits 8-15) is y radius
                     // (bits 16-21) is z down distance
                     // (bits 22-30) is z up distance
							// gi.linkentity sets this properly
#else
	int		solid;			// for client side prediction, 8*(bits 0-4) is x/y radius
							// 8*(bits 5-9) is z down distance, 8(bits10-15) is z up
							// gi.linkentity sets this properly
#endif
	int		sound;			// for looping sounds, to guarantee shutoff
	int		event;			// impulse events -- muzzle flashes, footsteps, etc
							// events only go out for a single frame, they
							// are automatically cleared each frame
} entity_state_t;


#ifdef SIN
// means of death flags

typedef enum {
   MOD_FISTS,
   MOD_MAGNUM,
   MOD_SHOTGUN,
   MOD_ASSRIFLE,
   MOD_CHAINGUN,
   MOD_GRENADE,
   MOD_ROCKET,
   MOD_ROCKETSPLASH,
   MOD_PULSE,
   MOD_PULSELASER,
   MOD_SPEARGUN,
   MOD_SNIPER,
   MOD_VEHICLE,
   MOD_CRUSH,
   MOD_SHOTROCKET,
   MOD_FALLING,
   MOD_DROWN,
   MOD_SUICIDE,
   MOD_EXPLODEWALL,
   MOD_ELECTRIC,
   MOD_TELEFRAG,
   MOD_GENBULLET,
   MOD_LASER,
   MOD_BETTYSPIKE,
   MOD_HELIGUN,
   MOD_DEBRIS,
   MOD_THROWNOBJECT,
   MOD_LAVA,
   MOD_SLIME,
   MOD_ADRENALINE,
   MOD_ION,
   MOD_ION_DESTRUCT,
   MOD_QUANTUM,
   MOD_BEAM, 
   MOD_IMPACT,
   MOD_FRIENDLY_FIRE,
   MOD_SPIDERSPLASH,
   MOD_MUTANTHANDS,
   MOD_MUTANT_DRAIN,
	MOD_GRAPPLE,
	MOD_EMPATHY,
	MOD_THRALLBALL,
	MOD_THRALLSPLASH,
   MOD_DEATHQUAD,
   MOD_CTFTURRET
   } mod_type_t;

// CONSOLE3D State
#define MAIN_CONSOLE "maincon"
#define GENERIC_CONSOLE "gencon"
#define MISSION_CONSOLE "missioncon"
#define MAX_LAYOUT_LENGTH        1024
#define MAX_CONSOLE_NAME         32
#define MAX_BUFFER_LENGTH        1024
#define MAX_CON_LINES            16
#define MAX_STATUSBARS           32
#define MAXCMDLINE	            256

typedef enum {MENU3D, CONSOLE3D} consolefocus_t;

typedef struct surface_state_s
   {
   qboolean    changed;
#ifdef _H2INC
   char        *AMD_name;
#else
   char        *name;
#endif
   int         number;
   int         groupnumber;
   qboolean    trans_state;
   float       trans_mag;
   float       trans_angle;
   float       translucence;
   float       magnitude;
   float       frequency;
   int         damage_frame;
   } surface_state_t;

typedef struct statusbar_s
   {
#ifdef _H2INC
   float AMD_width,height;
#else
   float width,height;
#endif
   float min,max;
   float value;
   float red,green,blue,alpha;
   float update_time;
   } statusbar_t;

typedef struct console_state_s
   {
   int            number;                          // Console number
   char           console_name[MAX_CONSOLE_NAME];  // Console name
   int            spawnflags;                      // Console type (flag 2 = Scroll, flag 4 = Menu, flag 8 = IgnorePVS)
   float          create_time;                     // Console has been initially created.
   float          layout_update_time;              // Layout updated
   float          menufile_update_time;            // Menufile updated
   float          layoutfile_update_time;          // Layoutfile updated
   float          cleared_console_time;            // Cleared the console
   float          name_update_time;                // Changed the console name
   float          console_return_time;             // Hit return on the console
   float          red,green,blue,alpha;            // Foreground colors
   char           layout[MAX_LAYOUT_LENGTH];       // Current layout
   char           menu_file[MAX_OSPATH];           // menufile filename
   char           layout_file[MAX_OSPATH];         // layoutfile filename
   float          virtual_width;                   // User defined virtual width
   float          virtual_height;                  // User defined virtual height
   float          fraction;                        // Fraction of the scrolling console to draw
   int            rows;                            // Number of rows
   int            cols;                            // Number of cols
   int            linepos;                         // Cursor position
   char           cmdline[MAXCMDLINE];             // Input line text;
   int            menu_level;                      // Current menu level
   int            sel_menu_item;                   // Currently selected item
   consolefocus_t focus;                           // Current focus (Menu or scrolling)
   qboolean       consoleactive;                   // Console is active
   qboolean       menuactive;                      // Menu is active
   statusbar_t    sbar[MAX_STATUSBARS];            // Status bar states
   int            console_owner;                   // entity number of owner
   } console_state_t;

typedef struct console_buffer_state_s
   {
   int  start_index;               // Absolute index of the first character in the buffer
   int  end_index;                 // Absolute index of the last character in the buffer
   int  start;                     // Index of the first character in the circular buffer
#ifdef _H2INC
   int  AMD_end;                       // Index of the last character in the circular buffer
#else
   int  end;                       // Index of the last character in the circular buffer
#endif
   char buffer[MAX_BUFFER_LENGTH]; // State of the buffer for the console
   } console_buffer_state_t;

#endif

//==============================================
#ifdef SIN
typedef enum
   {
   mood_none,
   mood_normal,
   mood_action,
   mood_suspense,
   mood_mystery,
   mood_success,
   mood_failure,
   mood_surprise,
   mood_special,
   mood_aux1,
   mood_aux2,
   mood_aux3,
   mood_aux4,
   mood_aux5,
   mood_aux6,
   mood_aux7,
   mood_totalnumber
   } music_mood_t;
#endif

// player_state_t is the information needed in addition to pmove_state_t
// to rendered a view.  There will only be 10 player_state_t sent each second,
// but the number of pmove_state_t changes will be reletive to client
// frame rates
typedef struct
{
	pmove_state_t	pmove;		// for prediction

	// these fields do not need to be communicated bit-precise

	vec3_t		viewangles;		// for fixed views
	vec3_t		viewoffset;		// add to pmovestate->origin
	vec3_t		kick_angles;	// add to view direction to get render angles
								// set by weapon kicks, pain effects, etc

	vec3_t		gunangles;
	vec3_t		gunoffset;
#ifndef SIN
	int			gunindex;
	int			gunframe;
#else
   // for client side commands
   int         last_gunframe;
   int         last_gunanim;

   // client side music mood
#ifdef _H2INC
   unsigned char current_music_mood;
   unsigned char fallback_music_mood;
#else
   byte        current_music_mood;
   byte        fallback_music_mood;
#endif

#endif

	float		blend[4];		// rgba full screen effect

	float		fov;			// horizontal field of view

	int			rdflags;		// refdef flags

	short		stats[MAX_STATS];		// fast status bar updates
} player_state_t;

#ifdef SIN
#define SINMDL_CMD_MAX_CMDS 128
#define SINMDL_CMD_MAX_ARGS 32

typedef struct
   {
   int num_args;
   char *args[SINMDL_CMD_MAX_ARGS];
   } sinmdl_singlecmd_t;

typedef struct
   {
   int num_cmds;
   sinmdl_singlecmd_t cmds[ SINMDL_CMD_MAX_CMDS ];
   } sinmdl_cmd_t;


#define SOUND_SYNCH        0x1
#define SOUND_SYNCH_FADE   0x2
#define SOUND_RANDOM_PITCH_20 0x4
#define SOUND_RANDOM_PITCH_40 0x8
#define SOUND_LOCAL_DIALOG 0x10

typedef struct
	{
	vec3_t	start;
#ifdef _H2INC
   vec3_t   AMD_end;
#else
	vec3_t	end;
#endif
	vec3_t	color;
	float		alpha;
	} debugline_t;

#endif

void MatrixToEulerAngles( float mat[ 3 ][ 3 ], vec3_t ang );
void TransposeMatrix( float in[ 3 ][ 3 ], float out[ 3 ][ 3 ] );
void MatrixTransformVector( vec3_t in, float mat[ 3 ][ 3 ], vec3_t out );
void Matrix4TransformVector( vec3_t in, float mat[ 4 ][ 4 ], vec3_t out );
void OrthoNormalize( float mat[3][3] );
void QuatToMat( float q[ 4 ], float mat[ 3 ][ 3 ] );
void MatToQuat( float mat[ 3 ][ 3 ], float q[ 4 ] );
void SlerpQuaternion( float p[ 4 ], float q[ 4 ], float t, float qt[ 4 ] );
void AnglesToMat( float ang[ 3 ], float mat[ 3 ][ 3 ] );
void RotateAxis( float axis[ 3 ], float angle, float q[ 4 ] );
void MultQuat( float q1[ 4 ], float q2[ 4 ], float out[ 4 ] );
void EulerToQuat( float ang[ 3 ], float q[ 4 ] );
void VectorsToEulerAngles( vec3_t forward, vec3_t right, vec3_t up, vec3_t ang );
#ifdef SIN
/*
=================
TransformFromTriangle
=================
*/
void TransformFromTriangle( const float tri[3][3], float trans[3][3], vec3_t pos );
// 2015 code
/*
=================
TransformFromTriangle_2015
=================
*/
void TransformFromTriangle_2015(const float tri[3][3], float trans[3][3], vec3_t pos);
/*
=================
OriginFromTriangle
=================
*/
void OriginFromTriangle( const float tri[3][3], vec3_t pos );
void CalculateRotatedBounds( vec3_t angles, vec3_t mins, vec3_t maxs );
void CalculateRotatedBounds2( float trans[3][3], vec3_t mins, vec3_t maxs );
/*
=================
MusicMood_NameToNum
=================
*/
int MusicMood_NameToNum( const char * name );
/*
=================
MusicMood_NumToName
=================
*/
const char * MusicMood_NumToName( int num );
/*
===============
SURFACE_DamageMultiplier
===============
*/
float SURFACE_DamageMultiplier( int flags );

#endif

#ifdef __cplusplus
	}
#endif

#endif
