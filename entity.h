//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/entity.h                         $
// $Revision:: 163                                                            $
//   $Author:: Aldie                                                          $
//     $Date:: 3/19/99 4:12p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/entity.h                              $
// 
// 163   3/19/99 4:12p Aldie
// Moved MOD to client
// 
// 162   3/17/99 3:55p Aldie
// Incremental CTF update
// 
// 161   3/12/99 8:12p Aldie
// Added deathquad
// 
// 160   3/11/99 3:48p Aldie
// Add more meansofdeath
// 
// 159   3/05/99 5:47p Aldie
// Added mod_thrallball
// 
// 158   3/02/99 9:16p Aldie
// Added CTF game code
// 
// 157   11/15/98 11:33p Markd
// added fat projectile flag
// 
// 156   11/13/98 2:35a Aldie
// Added mutant drain MOD
// 
// 155   11/08/98 10:50p Jimdose
// changed how archive wrote groundentity entity number
// 
// 154   10/27/98 3:51a Jimdose
// added FL_NOION
// 
// 153   10/26/98 4:30p Aldie
// Added Ghost command
// 
// 152   10/25/98 11:53p Jimdose
// added EXPORT_TEMPLATE
// 
// 151   10/25/98 4:37a Aldie
// Moved link()
// 
// 150   10/25/98 12:01a Markd
// put in censored support
// 
// 149   10/24/98 7:15p Jimdose
// archive wasn't saving orientation
// 
// 148   10/23/98 5:39a Jimdose
// Added SetMassEvent
// 
// 147   10/22/98 1:40a Markd
// Added stealth mode
// 
// 146   10/20/98 11:30p Markd
// Increased ranges on BroadcastSounds
// 
// 145   10/20/98 3:30a Jimdose
// Added isBoundTo
// 
// 144   10/20/98 12:44a Markd
// Made setSize virtual
// 
// 143   10/18/98 8:44p Jimdose
// Added GetEntName
// 
// 142   10/17/98 11:02p Markd
// Added ifskill
// 
// 141   10/17/98 8:11p Jimdose
// Changed Damage to DamgeEvent
// 
// 140   10/16/98 1:42a Jimdose
// Added FL_DONTSAVE
// 
// 139   10/15/98 3:39p Markd
// Added FL_FORCEFIELD
// 
// 138   10/13/98 11:14p Markd
// Added hurt and mutate events
// 
// 137   10/13/98 5:25p Markd
// Added UseBoundingBoxEvent
// 
// 136   10/11/98 8:50p Jimdose
// Added RandomGlobalEntitySound and RandomGlobalEntitySoundEvent
// 
// 135   10/11/98 7:41p Aldie
// Mutate and restore commands for Richard
// 
// 134   10/11/98 5:34p Aldie
// Added MOD_MUTANTHANDS
// 
// 133   10/10/98 9:13p Markd
// Took out SetAliasPrefix
// 
// 132   10/10/98 9:13p Aldie
// Added SPIDERSPLASH
// 
// 131   10/10/98 3:35a Jimdose
// changed team to moveteam
// 
// 130   10/10/98 1:32a Jimdose
// moved edict archiving out of entity archive functions
// no longer call SetOrigin during unarchiving since it needs parent and
// bindmaster pointers.  Instead, edicts are now fully unarchived.
// 
// 129   10/09/98 8:59p Aldie
// Moved air_finished to player
// 
// 128   10/09/98 4:33p Aldie
// Add MOD_FRIENDLY_FIRE
// 
// 127   10/08/98 7:39p Aldie
// Added lightoffset
// 
// 126   10/08/98 7:25p Aldie
// minlight, gravity, lightoffset
// 
// 125   10/07/98 11:45p Jimdose
// Added DistanceTo and WithinDistance for vectors
// Added SetDeltaAngles
// 
// 124   10/06/98 10:50p Aldie
// Created an oxygenator
// 
// 123   10/06/98 9:39p Markd
// removed last_origin
// 
// 122   10/05/98 11:23p Markd
// Moved all SOUND_RADIUSES to header 
// 
// 121   10/05/98 10:37p Aldie
// Added FL_SILENCER
// 
// 120   10/04/98 10:28p Aldie
// Added multiple weapon changes.  Damage, flashes, quantum stuff
// 
// 119   10/03/98 1:12p Aldie
// Added new pulse effects
// 
// 118   10/02/98 11:27p Jimdose
// Added SetEntNum
// 
// 117   9/28/98 9:12p Markd
// Put in archive and unarchive functions
// 
// 116   9/28/98 4:07p Aldie
// Added oxygen powerup
// 
// 115   9/26/98 4:46p Aldie
// Added mutant mode
// 
// 114   9/23/98 10:07p Aldie
// Added ION_DESTRUCT to MOD
// 
// 113   9/22/98 2:59p Aldie
// Added effects command
// 
// 112   9/15/98 6:37p Markd
// Added RotatedBounds flag support
// 
// 111   9/13/98 4:35p Aldie
// Changed MOD_LASERBEAM to MOD_LASER
// 
// 110   9/12/98 11:11p Aldie
// Added some more MOD
// 
// 109   9/11/98 4:24p Aldie
// Added a couple more means of death
// 
// 108   9/09/98 6:45p Markd
// put in world weapon model animations
// 
// 107   9/08/98 11:30p Jimdose
// Added AnimEvent
// 
// 106   9/02/98 11:08a Markd
// Put in setModel into Sentient so that weapon could be properly detached and
// re-attached again.
// 
// 105   8/31/98 7:45p Aldie
// Updated surface data structure and removed surfinfo field
// 
// 104   8/31/98 5:45p Aldie
// Added FL_CLOAK
// 
// 103   8/29/98 9:49p Jimdose
// moved #defines and enum defines from g_local.h
// 
// 102   8/28/98 3:46p Markd
// Added centroid to edict_s
// 
// 101   8/27/98 9:04p Jimdose
// Moved a lot of small functions to the header as inline
// Made Centroid a variable
// 
// 100   8/24/98 6:50p Jimdose
// Added SetGravityAxis
// 
// 99    8/22/98 8:55p Jimdose
// Added support for alternate gravity axis
// 
// 98    8/18/98 11:08p Markd
// Added new Alias System
// 
// 97    8/18/98 11:12a Markd
// Added "skin" event
// 
// 96    8/08/98 8:18p Markd
// Made max_health a float
// 
// 95    8/08/98 7:51p Jimdose
// Made definition of world into include of worldspawn.h
// 
// 94    7/31/98 8:10p Jimdose
// Script commands now include flags to indicate cheats and console commands
// 
// 93    7/29/98 2:32p Aldie
// Changed health to a float
// 
// 92    7/25/98 3:58p Markd
// Added EV_GotKill
// 
// 91    7/23/98 6:17p Aldie
// Updated damage system and fixed some damage related bugs.  Also put tracers
// back to the way they were, and added gib event to funcscriptmodels
// 
// 90    7/21/98 9:34p Jimdose
// Added AliasExists and PrefixAliasExists
// 
// 89    7/21/98 1:10p Aldie
// Added meansofdeath to obituaries
// 
// 88    7/20/98 5:08p Aldie
// Added explicit processinitcommands
// 
// 87    7/18/98 11:15p Markd
// Added takedamage and nodamage
// 
// 86    7/18/98 4:02p Markd
// Added attach, detach, attachmodel events
// 
// 85    7/17/98 4:04p Markd
// Added HasAnim to entity.cpp
// 
// 84    7/15/98 11:23p Markd
// Added processinitcommands stuff
// 
// 83    7/14/98 11:35p Markd
// Added PHSSound and RandomPHSSound
// 
// 82    7/14/98 3:54p Markd
// Added last_animation_time
// 
// 81    7/13/98 5:01p Aldie
// Added dead player bodies with gibbing
// 
// 80    7/11/98 2:49p Markd
// Added dialog event
// 
// 79    7/11/98 2:25p Markd
// removed dialog event
// 
// 78    7/10/98 11:11p Markd
// Added dialog event
// 
// 77    7/09/98 9:35p Jimdose
// Added getParentVector
// 
// 76    7/08/98 12:58p Jimdose
// Added classname event
// 
// 75    6/24/98 12:23p Markd
// Added shatter_percentage
// 
// 74    6/19/98 4:45p Jimdose
// Added Centroid, DistanceTo, and WithinDistance
// 
// 73    6/19/98 10:56a Markd
// re-ordered tesselation event
// 
// 72    6/18/98 2:00p Markd
// rewrote tesselation code
// 
// 71    6/10/98 5:10p Markd
// Added ExpandAlias
// 
// 70    6/10/98 2:10p Aldie
// Updated damage function.
// 
// 69    6/08/98 4:58p Markd
// Added GroupModelEvent
// 
// 68    6/05/98 6:27p Aldie
// Added location to Damage function.
// 
// 67    5/26/98 10:53p Markd
// made sounds be SOUND_SYNCH by default
// 
// 66    5/26/98 9:39p Markd
// removed damage regions
// 
// 65    5/26/98 9:25p Aldie
// Added kill event
// 
// 64    5/26/98 8:44p Markd
// Added damage_regions and DamageSkin Method
// 
// 63    5/25/98 12:22p Aldie
// Inited waterlevel and water type
// 
// 62    5/25/98 7:58p Markd
// Added RandomPositionedSound
// 
// 61    5/25/98 6:47p Jimdose
// Made animateframe, prethink and posthink into functions built into the base
// entity class
// 
// 60    5/25/98 4:43p Markd
// Added SpawnParticles
// 
// 59    5/24/98 9:01p Jimdose
// Changed classname to a const char *
// 
// 58    5/24/98 8:46p Jimdose
// Made a lot of functions more str-friendly.
// Got rid of a lot of char * based strings
// Cleaned up get spawn arg functions and sound functions
// sound functions now use consistant syntax
// 
// 57    5/24/98 1:05a Jimdose
// Added sound events for ai
// 
// 56    5/20/98 11:12a Markd
// removed char * dependency
// 
// 55    5/14/98 10:20p Jimdose
// world is now an EntityPtr
// 
// 54    5/13/98 4:54p Jimdose
// now uses SafePtrs
// 
// 53    5/11/98 8:07p Jimdose
// Added EntityPtr
// 
// 52    5/11/98 5:53p Markd
// Added aliascache command
// 
// 51    5/11/98 2:19p Markd
// Fixed randomsound stuff
// 
// 50    5/08/98 2:57p Markd
// Added another RandomSound method
// 
// 49    5/07/98 11:32p Markd
// Removed footstep command and event
// 
// 48    5/04/98 8:32p Markd
// Removed cachemodel and cachesound
// 
// 47    5/03/98 4:37p Jimdose
// removed oldorigin
// 
// 46    5/02/98 8:45p Markd
// Added CacheModel, CacheSound and entityflags events
// 
// 45    5/02/98 12:49a Jimdose
// added scale event
// 
// 44    5/01/98 7:32p Jimdose
// Added groundplane, groundsurface, groundcontents
// 
// 43    4/29/98 10:46p Markd
// added positioned_sound and random_sound
// 
// 42    4/16/98 1:56p Jimdose
// Added EndAnimEvent and PrevAnimEvent
// 
// 41    4/10/98 12:34a Jimdose
// got rid of damage_inflictor
// 
// 40    4/09/98 3:30p Jimdose
// sound and stopsound are now virtual
// 
// 39    4/07/98 8:00p Markd
// 
// 38    4/05/98 10:43p Markd
// Added Tesselate
// 
// 37    4/05/98 10:17p Jimdose
// added lastorigin
// 
// 36    4/05/98 7:20p Aldie
// Added dyamic lights
// 
// 35    4/05/98 1:59a Jimdose
// Added setmodelevent
// 
// 34    4/04/98 7:28p Jimdose
// added HitSky for generic trace
// 
// 33    4/04/98 6:14p Jimdose
// Added HitSky and RandomSound
// 
// 32    4/02/98 4:52p Jimdose
// Added parameter to droptofloor
// Added animation control events
// 
// 31    3/31/98 5:40p Markd
// Added StartAnimatingEvent
// 
// 30    3/30/98 11:39p Markd
// Added modelIndex function
// 
// 29    3/30/98 11:21p Markd
// Added setScale
// 
// 28    3/30/98 11:16p Markd
// Added sound and random sound support
// 
// 27    3/30/98 7:29p Markd
// Added Footstep method
// 
// 26    3/29/98 9:38p Jimdose
// Changed Killed and Pain to events
// Added damage event
// 
// 25    3/27/98 7:01p Markd
// Added vieworigin and viewangles
// 
// 24    3/26/98 8:10p Jimdose
// Changed groundentity to an edict_t *
// Added GetBone
// 
// 23    3/25/98 3:24p Markd
// Added model binding variables
// 
// 22    3/23/98 1:33p Jimdose
// Revamped event and command system
// 
// 21    3/18/98 7:19p Jimdose
// Added RandomAnimate
// Added animDoneEvent
// 
// 20    3/11/98 11:30a Markd
// Added movement variable totaldelta
// 
// 19    3/07/98 2:05p Markd
// Added stuff for Animation system
// 
// 18    3/02/98 8:49p Jimdose
// Changed CLASS_PROTOTYPE to only take the classname
// 
// 17    2/17/98 6:59p Jimdose
// no longer pass script into interpretCommand
// 
// 16    2/16/98 2:05p Jimdose
// Added hierarchial object binding.
// Added joinTeam and quitTeam for object teams
// Added getLocalVector to aid in translating into the object's local
// coordinate system.
// Added orientation rotation matrix that is calculated each time setAngles is
// called, allowing us to get rid of a lot of calls to AngleVectors.
// 
// 15    2/06/98 5:47p Jimdose
// Added link and unlink
// Removed touch and think functions
// Removed Spawn (all spawning done in constructor)
// Added client pointer
// No longer initialize mins and maxs to '0 0 0' since it screws up bmodels.
// 
// 14    2/03/98 10:57a Jimdose
// Updated to work with Quake 2 engine
// Moved initialization to constructor and removed Init function
// 
// 12    12/12/97 4:27p Markd
// Added "soundprefix"
// 
// 11    11/24/97 6:54p Markd
// Added Register Sound and Random Sound
// 
// 10    11/15/97 6:53p Markd
// added ProcessNoteCommands, added RandomAnimate, added animloop_count and
// animloop_anim variables for animation loop tracking
// 
// 9     11/15/97 2:48p Jimdose
// Added ProcessEvent member function
// 
// 8     11/14/97 4:44p Jimdose
// Added PostEvent
// 
// 7     11/12/97 5:13p Jimdose
// Created event definitions
// 
// 6     10/29/97 4:18p Jimdose
// Added FadeOut.
// 
// 5     10/28/97 4:13p Jimdose
// Added interpretCommand to make Entity be controllable by scripts via
// ScriptMaster.
// 
// 4     9/29/97 6:18p Markd
// working on animate
// 
// 3     9/26/97 6:14p Jimdose
// Added standard Ritual headers
//
// DESCRIPTION:
// Base class for all enities that are controlled by Sin.  If you have any
// object that should be called on a periodic basis and it is not an entity,
// then you have to have an dummy entity that calls it.
//
// An entity in Sin is any object that is not part of the world.  Any non-world
// object that is visible in Sin is an entity, although it is not required that
// all entities be visible to the player.  Some objects are basically just virtual
// constructs that act as an instigator of certain actions, for example, some 
// triggers are invisible and cannot be touched, but when activated by other
// objects can cause things to happen.
//
// All entities are capable of receiving messages from Sin or from other entities.
// Messages received by an entity may be ignored, passed on to their superclass,
// or acted upon by the entity itself.  The programmer must decide on the proper
// action for the entity to take to any message.  There will be many messages
// that are completely irrelevant to an entity and should be ignored.  Some messages
// may require certain states to exist and if they are received by an entity when
// it these states don't exist may indicate a logic error on the part of the 
// programmer or map designer and should be reported as warnings (if the problem is
// not severe enough for the game to be halted) or as errors (if the problem should 
// not be ignored at any cost).
// 

#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "g_local.h"
#include "class.h"
#include "vector.h"
#include "script.h"
#include "listener.h"

typedef enum
	{
	DAMAGE_NO,
	DAMAGE_YES,			// will take damage if hit
	DAMAGE_AIM			// auto targeting recognizes this
	} damage_t;

//deadflag
#define DEAD_NO						0
#define DEAD_DYING					1
#define DEAD_DEAD						2
#define DEAD_RESPAWNABLE			3

// flags
#define	FL_FLY					0x00000001
#define	FL_SWIM					0x00000002	// implied immunity to drowining
#define	FL_INWATER				0x00000004
#define	FL_GODMODE				0x00000008
#define	FL_NOTARGET				0x00000010
#define	FL_PARTIALGROUND		0x00000020	// not all corners are valid
#define	FL_FATPROJECTILE		0x00000040	// projectile should use fat trace
#define	FL_TEAMSLAVE			0x00000080	// not the first on the team
#define	FL_NO_KNOCKBACK		0x00000100
#define	FL_PRETHINK				0x00000200
#define	FL_POSTTHINK			0x00000400
#define  FL_BLOOD             0x00000800
#define  FL_SPARKS            0x00001000
#define  FL_TESSELATE         0x00002000
#define  FL_BLASTMARK         0x00004000
#define  FL_DIE_TESSELATE     0x00008000
#define  FL_DARKEN            0x00010000
#define  FL_DIE_GIBS          0x00020000
#define  FL_SHIELDS           0x00040000  // sentient has reactive shields
#define  FL_DIE_EXPLODE       0x00080000  // when it dies, it will explode
#define  FL_ADRENALINE        0x00100000  // sentient is under adrenaline effects
#define  FL_CLOAK             0x00200000  // sentient is cloaked
#define  FL_ROTATEDBOUNDS     0x00400000  // model uses rotated mins and maxs
#define  FL_MUTANT            0x00800000  // sentient is in mutant mode
#define  FL_OXYGEN            0x01000000  // sentient has oxygen powerup
#define  FL_SILENCER          0x02000000  // sentient has silencer
#define  FL_SP_MUTANT         0x04000000  // mutant mode single player
#define  FL_MUTATED           0x08000000  // keep track of mutation
#define  FL_FORCEFIELD        0x10000000  // sentient has force field ( invulnerable )
#define  FL_DONTSAVE          0x20000000  // don't add to the savegame
#define  FL_STEALTH           0x40000000  // character is in "stealth" mode
#define  FL_NOION             0x80000000  // don't allow Ion tesselation

// damage flags
#define DAMAGE_RADIUS			0x00000001	// damage was indirect
#define DAMAGE_NO_ARMOR			0x00000002	// armour does not protect from this damage
#define DAMAGE_ENERGY			0x00000004	// damage is from an energy based weapon
#define DAMAGE_NO_KNOCKBACK	0x00000008	// do not affect velocity, just view angles
#define DAMAGE_BULLET			0x00000010  // damage is from a bullet (used for ricochets)
#define DAMAGE_NO_PROTECTION	0x00000020  // armor, shields, invulnerability, and godmode have no effect
#define DAMAGE_NO_SKILL       0x00000040  // damage is not affected by skill level

//
// Sound travel distances
//

#define SOUND_BREAKING_RADIUS 500
#define SOUND_WEAPON_RADIUS   800
#define SOUND_MOVEMENT_RADIUS 256
#define SOUND_PAIN_RADIUS     320
#define SOUND_DEATH_RADIUS    800
#define SOUND_DOOR_RADIUS     240
#define SOUND_MUTANT_RADIUS   256
#define SOUND_VOICE_RADIUS    800
#define SOUND_MACHINE_RADIUS  512
#define SOUND_RADIO_RADIUS    8192

extern Event EV_ClientConnect;
extern Event EV_ClientDisconnect;
extern Event EV_ClientKill;
extern Event EV_ClientMove;
extern Event EV_ClientEndFrame;

// Generic entity events
extern Event EV_Classname;
extern Event EV_Activate;
extern Event EV_Use;
//extern Event EV_Footstep;
extern Event EV_FadeOut;
extern Event EV_Fade;
extern Event EV_Killed;
extern Event EV_GotKill;
extern Event EV_Pain;
extern Event EV_Damage;
extern Event EV_Gib;
extern Event EV_Mutate;

// Physics events
extern Event EV_MoveDone;
extern Event EV_Touch;
extern Event EV_Blocked;
extern Event EV_Attach;
extern Event EV_AttachModel;
extern Event EV_Detach;
extern Event EV_UseBoundingBox;

// Animation events
extern Event EV_NewAnim;
extern Event EV_LastFrame;
extern Event EV_TakeDamage;
extern Event EV_NoDamage;
extern Event EV_SetSkin;

// script stuff
extern Event EV_Hide;
extern Event EV_Show;
extern Event EV_BecomeSolid;
extern Event EV_BecomeNonSolid;
extern Event EV_PlaySound;
extern Event EV_StopSound;
extern Event EV_GravityAxis;
extern Event EV_Bind;
extern Event EV_Unbind;
extern Event EV_JoinTeam;
extern Event EV_QuitTeam;
extern Event EV_SetHealth;
extern Event EV_SetSize;
extern Event EV_SetAlpha;
extern Event EV_SetOrigin;
extern Event EV_SetTargetName;
extern Event EV_SetTarget;
extern Event EV_SetKillTarget;
extern Event EV_SetAngles;
extern Event EV_RegisterAlias;
extern Event EV_RandomSound;
extern Event EV_EntitySound;
extern Event EV_RandomEntitySound;
extern Event EV_RandomGlobalEntitySound;
extern Event EV_StopEntitySound;
extern Event EV_Anim;
extern Event EV_StartAnimating;
extern Event EV_GroupModelEvent;
extern Event EV_DialogEvent;
extern Event EV_RandomPHSSound;
extern Event EV_PHSSound;
extern Event EV_ProcessInitCommands;
// dir is 1
// power is 2
// minsize is 3
// maxsize is 4
// percentage is 5
// thickness 6
// entity is 7
// origin 8
extern Event EV_Tesselate;
extern Event EV_Shatter_MinSize;
extern Event EV_Shatter_MaxSize;
extern Event EV_Shatter_Thickness;
extern Event EV_Shatter_Percentage;

// AI sound events
extern Event EV_WeaponSound;
extern Event EV_MovementSound;
extern Event EV_PainSound;
extern Event EV_DeathSound;
extern Event EV_BreakingSound;
extern Event EV_DoorSound;
extern Event EV_MutantSound;
extern Event EV_VoiceSound;
extern Event EV_MachineSound;
extern Event EV_RadioSound;

extern Event EV_HeardWeapon;
extern Event EV_HeardMovement;
extern Event EV_HeardPain;
extern Event EV_HeardDeath;
extern Event EV_HeardBreaking;
extern Event EV_HeardDoor;
extern Event EV_HeardMutant;
extern Event EV_HeardVoice;
extern Event EV_HeardMachine;
extern Event EV_HeardRadio;
extern Event EV_Hurt;
extern Event EV_IfSkill;

// Define ScriptMaster
class ScriptMaster;

//
// Spawn args
//
// "spawnflags"
// "alpha" default 1.0
// "model"
// "origin"
// "targetname"
// "target"
//
#define MAX_MODEL_CHILDREN 8

class Entity;
#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL SafePtr<Entity>;
#endif
typedef SafePtr<Entity> EntityPtr;

class EXPORT_FROM_DLL Entity : public Listener
	{
	public:
		CLASS_PROTOTYPE( Entity );

		// spawning variables
		int					entnum;
		edict_t				*edict;
		gclient_t			*client;
		const char			*classname;
		int					spawnflags;

		// rendering variables
		float					translucence;
		int					viewheight;		// height above origin where eyesight is determined
		int					light_level;	// keeps track of light level at origin

		// Animation variables
		str					model;
      int               next_anim;     // index of next_anim, if an anim change is pending,
                                       // this value is non-negative
      int               next_frame;    // index of next_frame, if a frame change is pending,
                                       // this value is non-negative
      int               last_frame_in_anim;// last frame in the current animation
      Vector            frame_delta;   // current movement from this frame
      Vector            total_delta;   // total unprocessed movement 
      Vector            next_anim_delta; // total delta of next animation
      float             next_anim_time;  // total time of next animation
      qboolean          animating;     // whether the model is currently animating
		Event					*animDoneEvent;
      float             last_animation_time; // the last server frame this model was animated
      int               num_frames_in_gun_anim; // num frames in the gun animation, if there is one

		// physics variables
		Vector				mins;
		Vector				maxs;
		Vector				absmin;
		Vector				absmax;
		Vector				size;
		Vector				centroid;
		Vector				origin;
		Vector				velocity;
		Vector				avelocity;
		Vector				angles;
		Vector				worldorigin;
		Vector				worldangles;
		Vector				vieworigin;
		Vector				viewangles;
		int					contents;
		int					movetype;
		int					mass;
		float					gravity;			// per entity gravity multiplier (1.0 is normal)
		int					gravaxis;		// per entity gravity axis

		edict_t				*groundentity;
		csurface_t			*groundsurface;
		cplane_t				groundplane;
		int					groundcontents;

		int					groundentity_linkcount;

		// Binding variables
		Entity 				*bindmaster;
		str					moveteam;
		Entity				*teamchain;
		Entity 				*teammaster;
		float					orientation[3][3];

      // Model Binding variables
      int               numchildren;
      int               children[MAX_MODEL_CHILDREN];

		// targeting variables
		str					target;
		str					targetname;
		str			      killtarget;

		// Character state
		float					health;
		float             max_health;
		int					deadflag;
		int					flags;

		// underwater variables
		int					watertype;
		int					waterlevel;

		// Pain and damage variables
		damage_t				takedamage;
		EntityPtr			enemy;
		float					pain_finished;
		float					damage_debounce_time;

      // tesselation variables
      int               tess_min_size;
      int               tess_max_size;
      int               tess_thickness;
      float             tess_percentage;

								Entity::Entity();
		virtual				Entity::~Entity();

      void              SetEntNum( int num );
      void              GetEntName( Event *ev );

      qboolean				DistanceTo( Vector pos );
      qboolean				DistanceTo( Entity *ent );
		qboolean				WithinDistance( Vector pos, float dist );
		qboolean				WithinDistance( Entity *ent, float dist );

		const char			*Target( void );
		void					SetTarget( const char *target );
		qboolean				Targeted( void );
		const char			*TargetName( void );
		void					SetTargetName( const char *target );
      void              SetKillTarget( const char *killtarget );
      const char        *KillTarget( void );

      int               modelIndex( const char * mdl );
		virtual void		setModel( const char *model );
		virtual void		setModel( str &mdl );
		void					SetModelEvent( Event *ev );
		void					hideModel( void );
		void					EventHideModel( Event *ev );
		void					showModel( void );
		void					EventShowModel( Event *ev );
		qboolean				hidden( void );
      void              ProcessInitCommandsEvent( Event *ev );
      void              ProcessInitCommands( int index );

		void					setAlpha( float alpha );
		float					alpha( void );

		void					setMoveType( int type );
		int					getMoveType( void );

		void					setSolidType( solid_t type );
		int					getSolidType( void );

		Vector				getParentVector( Vector vec );
		Vector				getLocalVector( Vector vec );

		virtual void		setSize( Vector min, Vector max );
		void					setOrigin( Vector org );
		qboolean				GetBone( const char *name, Vector *pos, Vector *forward, Vector *right, Vector *up );
		void					setAngles( Vector ang );

		void					link( void );
		void					unlink( void );

		void					setContents( int type );
		int					getContents( void );
      void              setScale( float scale );

		qboolean				droptofloor( float maxfall );
		qboolean				isClient( void );

      virtual void		SetDeltaAngles( void );

		virtual void		DamageEvent( Event *event );
      virtual void      Damage( Entity *inflictor, 
                                Entity *attacker, 
                                int damage, 
                                Vector position,
                                Vector direction,
                                Vector normal,
                                int knockback,
                                int flags,
                                int meansofdeath,
                                int groupnum,
                                int trinum,
                                float damage_multiplier );

		virtual qboolean	CanDamage( Entity *target );

		qboolean				IsTouching( Entity *e1 );
      void              NextAnim( int animnum );
      void              NextFrame( int framenum );
      void              AnimateFrame( void );
      void              StopAnimating( void );
      void              StartAnimating( void );
		void					RandomAnimate( const char *animname, Event *endevent );
		void					RandomAnimate( const char *animname, Event &endevent );
      qboolean          HasAnim( const char *animname );

		void					joinTeam( Entity *teammember );
		void					quitTeam( void );
		void					EventQuitTeam( Event *ev );
      qboolean          isBoundTo( Entity *master );
		void					bind( Entity *master );
		void					unbind( void );
		void					EventUnbind( Event *ev );

		void					FadeOut( Event *ev );
		void					Fade( Event *ev );

		virtual void		CheckGround( void );
		virtual qboolean	HitSky( trace_t *trace );
		virtual qboolean	HitSky( void );

		void					BecomeSolid( Event *ev );
		void					BecomeNonSolid( Event *ev );
		void					PlaySound( Event *ev );
		void					StopSound( Event *ev );
		void					SetGravityAxis( int axis );
		void					GravityAxisEvent( Event *ev );
		void					BindEvent( Event *ev );
		void					JoinTeam( Event *ev );
		void					SetHealth( Event *ev );
		void					SetSize( Event *ev );
		void					SetScale( Event *ev );
		void					SetAlpha( Event *ev );
		void					SetOrigin( Event *ev );
		void					SetTargetName( Event *ev );
		void					SetTarget( Event *ev );
		void		         SetKillTarget( Event *ev );
		void					SetAngles( Event *ev );

		void					CourseAnglesEvent( Event *ev );
		void					SmoothAnglesEvent( Event *ev );

      str               GetRandomAlias( str name );
      void              SetWaterType( void );
      
      // model binding functions
      qboolean          attach( int parent_entity_num, int group_num, int tri_num, Vector orient );
      void              detach( void );

      void              RegisterAlias( Event *ev );
      void              RegisterAliasAndCache( Event *ev );

		qboolean				GlobalAliasExists( const char *name );
		qboolean				AliasExists( const char *name );

		virtual void		positioned_sound( Vector origin, str soundname, float volume = 1.0f, 
									int channel = CHAN_BODY, int attenuation = ATTN_NORM, float pitch = 1.0f, 
									float timeofs = 0, float fadetime = 0, int flags = SOUND_SYNCH );
		
		virtual void		sound( str soundname, float volume = 1.0f, int channel = CHAN_BODY, 
									int attenuation = ATTN_NORM, float pitch = 1.0f, float timeofs = 0, 
									float fadetime = 0, int flags = SOUND_SYNCH );
		
		virtual void		stopsound( int	channel );
		
		virtual void		RandomPositionedSound( Vector origin, str soundname, float volume = 1.0f, 
									int channel = CHAN_BODY, int attenuation = ATTN_NORM, float pitch = 1.0f, 
									float timeofs = 0, float fadetime = 0, int flags = SOUND_SYNCH );

		void					RandomSound( str soundname, float volume = 1.0f, int channel = CHAN_BODY, 
									int attenuation = ATTN_NORM, float pitch = 1.0f, float timeofs = 0, 
									float fadetime = 0, int flags = SOUND_SYNCH );
		
		void					RandomGlobalSound( str soundname, float volume = 1.0f, int channel = CHAN_BODY, 
									int attenuation = ATTN_NORM, float pitch = 1.0f, float timeofs = 0, 
									float fadetime = 0, int flags = SOUND_SYNCH );

      void              RandomGlobalEntitySound( str soundname, int attenuation = ATTN_IDLE );
      void              RandomGlobalEntitySoundEvent( Event *ev );

		void              RandomSound( Event *ev );
      void              EntitySound( Event *ev );
      void              StopEntitySound( Event *ev );
      void              RandomEntitySound( Event *ev );
      void              AnimEvent( Event *ev );
      void              StartAnimatingEvent( Event *ev );
		void					StopAnimatingEvent( Event *ev );
		void					EndAnimEvent( Event *ev );
		void					NextAnimEvent( Event *ev );
		void					NextFrameEvent( Event *ev );
		void					PrevFrameEvent( Event *ev );
		void					SetFrameEvent( Event *ev );
      void              SetLight(Event *ev);
      void              LightOn(Event *ev);
      void              LightOff(Event *ev);
      void              LightRed(Event *ev);
      void              LightGreen(Event *ev);
      void              LightBlue(Event *ev);
      void              LightRadius(Event *ev);
      void              Tesselate(Event *ev);
      void              SetShatterMinSize(Event *ev);
      void              SetShatterMaxSize(Event *ev);
      void              SetShatterThickness(Event *ev);
      void              SetShatterPercentage(Event *ev);
      void              Flags( Event *ev );
      void              Effects( Event *ev );
      void              RenderEffects( Event *ev );

		void					BroadcastSound( Event *soundevent, int channel, Event &event, float radius );
		void					WeaponSound( Event *ev );
		void					MovementSound( Event *ev );
		void					PainSound( Event *ev );
		void 					DeathSound( Event *ev );
		void					BreakingSound( Event *ev );
		void					DoorSound( Event *ev );
		void					MutantSound( Event *ev );
		void					VoiceSound( Event *ev );
		void					MachineSound( Event *ev );
		void					RadioSound( Event *ev );
      void              SpawnParticles( Event *ev );
      void              Kill( Event *ev );
      void              GroupModelEvent( Event *ev );

		virtual void		Prethink( void );
		virtual void		Postthink( void );
      void              DamageSkin( trace_t * trace, float damage );
      virtual void      DialogEvent( Event *ev );
		void					PHSSound( Event *ev );
		void              RandomPHSSound( Event *ev );
		void					AttachEvent( Event *ev );
		void					AttachModelEvent( Event *ev );
		void					DetachEvent( Event *ev );
      void              TakeDamageEvent( Event *ev );
      void              NoDamageEvent( Event *ev );
      void              SetSkinEvent( Event *ev	);
      void              Lightoffset( Event *ev );
      void              Gravity( Event *ev );
      void              Minlight( Event *ev );
      void              GiveOxygen( float time );
      void              UseBoundingBoxEvent( Event *ev );
      void              HurtEvent( Event *ev );
      void              IfSkillEvent( Event *ev );
      void              SetMassEvent( Event *ev );
      void              Censor( Event *ev );
      void              Ghost( Event *ev );

      virtual void      Archive( Archiver &arc );
      virtual void      Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL qboolean Entity::DistanceTo
	(
	Vector pos
	)

	{
	Vector delta;

	delta = worldorigin - pos;
	return delta.length();
	}

inline EXPORT_FROM_DLL qboolean Entity::DistanceTo
	(
	Entity *ent
	)

	{
	Vector delta;

	assert( ent );

	if ( !ent )
		{
		// "Infinite" distance
		return 999999;
		}

	delta = worldorigin - ent->worldorigin;
	return delta.length();
	}

inline EXPORT_FROM_DLL qboolean Entity::WithinDistance
	(
	Vector pos,
	float dist
	)

	{
	Vector delta;

	delta = worldorigin - pos;

	// check squared distance
	return ( ( delta * delta ) < ( dist * dist ) );
	}

inline EXPORT_FROM_DLL qboolean Entity::WithinDistance
	(
	Entity *ent,
	float dist
	)

	{
	Vector delta;

	assert( ent );

	if ( !ent )
		{
		return false;
		}

	delta = worldorigin - ent->worldorigin;

	// check squared distance
	return ( ( delta * delta ) < ( dist * dist ) );
	}

inline EXPORT_FROM_DLL const char *Entity::Target
	(
	void
	)

	{
	return target.c_str();
	}

inline EXPORT_FROM_DLL qboolean Entity::Targeted
	(
	void
	)

	{
	if ( !targetname.length() )
		{
		return false;
		}
	return true;
	}

inline EXPORT_FROM_DLL const char *Entity::TargetName
	(
	void
	)

	{
	return targetname.c_str();
	}

inline EXPORT_FROM_DLL const char * Entity::KillTarget
	(
	void
	)

	{
	return killtarget.c_str();
	}

inline EXPORT_FROM_DLL qboolean Entity::hidden
	(
	void
	)

	{
	if ( edict->s.renderfx & RF_DONTDRAW )
		{
		return true;
		}
	return false;
	}

inline EXPORT_FROM_DLL void Entity::setModel
	(
	str &mdl
	)

	{
	setModel( mdl.c_str() );
	}

inline EXPORT_FROM_DLL void Entity::SetModelEvent
	(
	Event *ev
	)

	{
	setModel( ev->GetString( 1 ) );
	}

inline EXPORT_FROM_DLL void Entity::hideModel
	(
	void
	)

	{
	edict->s.renderfx |= RF_DONTDRAW;
	if ( getSolidType() <= SOLID_TRIGGER )
		{
		edict->svflags |= SVF_NOCLIENT;
		}
	}

inline EXPORT_FROM_DLL void Entity::showModel
	(
	void
	)

	{
	edict->s.renderfx &= ~RF_DONTDRAW;
	edict->svflags &= ~SVF_NOCLIENT;
	}

inline EXPORT_FROM_DLL float Entity::alpha
	(
	void
	)

	{
	return 1.0f - translucence;
	}

inline EXPORT_FROM_DLL void Entity::setMoveType
	(
	int type
	)

	{
	movetype = type;
	}

inline EXPORT_FROM_DLL int Entity::getMoveType
	(
	void
	)

	{
	return movetype;
	}

inline EXPORT_FROM_DLL int Entity::getSolidType
	(
	void
	)

	{
	return edict->solid;
	}

inline EXPORT_FROM_DLL void Entity::unlink
	(
	void
	)

	{
	gi.unlinkentity( edict );
	}

inline EXPORT_FROM_DLL void Entity::setContents
	(
	int type
	)

	{
	contents = type;
	}

inline EXPORT_FROM_DLL int Entity::getContents
	(
	void
	)

	{
	return contents;
	}

inline EXPORT_FROM_DLL qboolean Entity::isClient
	(
	void
	)

	{
	if ( client )
		{
		return true;
		}
	return false;
	}

inline EXPORT_FROM_DLL void Entity::SetDeltaAngles
   (
   void
   )

   {
   int i;

   if ( client )
      {
	   for( i = 0; i < 3; i++ )
         {
		   client->ps.pmove.delta_angles[ i ] = ANGLE2SHORT( client->ps.viewangles[ i ] );
         }
      }
   }

inline EXPORT_FROM_DLL void Entity::RandomAnimate
	(
   const char *animname,
	Event &endevent
   )

   {
	Event *ev;

	ev = new Event( endevent );
	RandomAnimate( animname, ev );
   }

inline EXPORT_FROM_DLL qboolean Entity::HasAnim
	(
   const char *animname
   )
   {
   int num;

	num = gi.Anim_Random( edict->s.modelindex, animname );
   return ( num >= 0 );
   }

inline EXPORT_FROM_DLL qboolean Entity::GlobalAliasExists
	(
	const char *name
	)

	{
	assert( name );

	return ( gi.GlobalAlias_FindRandom( name ) != NULL );
	}

inline EXPORT_FROM_DLL qboolean Entity::AliasExists
	(
	const char *name
	)

	{
	assert( name );

	return ( gi.Alias_FindRandom( edict->s.modelindex, name ) != NULL );
	}

inline EXPORT_FROM_DLL void Entity::stopsound
	(
	int channel
	)

	{
   RandomGlobalSound( "null_sound", 0.1, channel, 0 );
	}

inline EXPORT_FROM_DLL str Entity::GetRandomAlias
	(
   str name
	)

	{
	str realname;
   const char *s;

   s = gi.Alias_FindRandom( edict->s.modelindex, name.c_str() );   
   if ( s )
      {
      realname = s;
      }

   return realname;
	}

inline EXPORT_FROM_DLL qboolean Entity::HitSky
	(
	trace_t *trace
	)
	
	{
	assert( trace );
	if ( trace->surface && ( trace->surface->flags & SURF_SKY ) )
		{
		return true;
		}
	return false;
	}

inline EXPORT_FROM_DLL qboolean Entity::HitSky
	(
	void
	)
	
	{
	return HitSky( &level.impact_trace );
	}

inline EXPORT_FROM_DLL void Entity::Archive
	(
	Archiver &arc
	)

   {
   Listener::Archive( arc );

   G_ArchiveEdict( arc, edict );

   arc.WriteInteger( spawnflags );

   arc.WriteFloat( translucence );
   arc.WriteInteger( viewheight );
   arc.WriteInteger( light_level );

   arc.WriteString( model );
   arc.WriteInteger( next_anim );
   arc.WriteInteger( next_frame );
   arc.WriteInteger( last_frame_in_anim );
   arc.WriteVector( frame_delta );
   arc.WriteVector( total_delta );
   arc.WriteVector( next_anim_delta );
   arc.WriteFloat( next_anim_time );
   arc.WriteBoolean( animating );
   arc.WriteEvent( *animDoneEvent );
   arc.WriteFloat( last_animation_time );
   arc.WriteInteger( num_frames_in_gun_anim );

   arc.WriteVector( mins );
   arc.WriteVector( maxs );
   arc.WriteVector( absmin );
   arc.WriteVector( absmax );
   arc.WriteVector( size );
   arc.WriteVector( centroid );
   arc.WriteVector( origin );
   arc.WriteVector( velocity );
   arc.WriteVector( avelocity );
   arc.WriteVector( angles );
   arc.WriteVector( worldorigin );
   arc.WriteVector( worldangles );
   arc.WriteRaw( orientation, sizeof( orientation ) );
   arc.WriteVector( vieworigin );
   arc.WriteVector( viewangles );
   arc.WriteInteger( contents );
   arc.WriteInteger( movetype );
   arc.WriteInteger( mass );
   arc.WriteFloat( gravity );
   arc.WriteInteger( gravaxis );

   if ( groundentity )
      {
		arc.WriteInteger( groundentity - g_edicts );
      }
   else
      {
      arc.WriteInteger( -1 );
      }

   arc.WriteRaw( &groundplane, sizeof( groundplane ) );
   arc.WriteInteger( groundcontents );

   arc.WriteInteger( groundentity_linkcount );

   arc.WriteObjectPointer( bindmaster );
   arc.WriteString( moveteam );
   arc.WriteObjectPointer( teamchain );
   arc.WriteObjectPointer( teammaster );

   arc.WriteInteger( numchildren );
   arc.WriteRaw( children, sizeof( children ) );

   arc.WriteString( target );
   arc.WriteString( targetname );
   // add to target list to rebuild targetlists
   arc.WriteString( killtarget );

   arc.WriteFloat( health );
   arc.WriteFloat( max_health );
   arc.WriteInteger( deadflag );
   arc.WriteInteger( flags );

   arc.WriteInteger( watertype );
   arc.WriteInteger( waterlevel );

   arc.WriteInteger( ( int )takedamage );
   arc.WriteSafePointer( enemy );
   arc.WriteFloat( pain_finished );
   arc.WriteFloat( damage_debounce_time );

   arc.WriteInteger( tess_min_size );
   arc.WriteInteger( tess_max_size );
   arc.WriteInteger( tess_thickness );
   arc.WriteFloat( tess_percentage );
   }

inline EXPORT_FROM_DLL void Entity::Unarchive
	(
	Archiver &arc
	)

   {
   int temp;

   Listener::Unarchive( arc );

   G_UnarchiveEdict( arc, edict );

   arc.ReadInteger( &spawnflags );

   arc.ReadFloat( &translucence );
   arc.ReadInteger( &viewheight );
   arc.ReadInteger( &light_level );

   arc.ReadString( &model );
   setModel( model );

   arc.ReadInteger( &next_anim );
   arc.ReadInteger( &next_frame );
   arc.ReadInteger( &last_frame_in_anim );
   arc.ReadVector( &frame_delta );
   arc.ReadVector( &total_delta );
   arc.ReadVector( &next_anim_delta );
   arc.ReadFloat( &next_anim_time );
   arc.ReadBoolean( &animating );
   animDoneEvent = new Event( arc.ReadEvent() );
   arc.ReadFloat( &last_animation_time );
   arc.ReadInteger( &num_frames_in_gun_anim );

   arc.ReadVector( &mins );
   arc.ReadVector( &maxs );
   arc.ReadVector( &absmin );
   arc.ReadVector( &absmax );
   arc.ReadVector( &size );
   arc.ReadVector( &centroid );
   arc.ReadVector( &origin );
   arc.ReadVector( &velocity );
   arc.ReadVector( &avelocity );
   arc.ReadVector( &angles );
   arc.ReadVector( &worldorigin );
   arc.ReadVector( &worldangles );
   arc.ReadRaw( orientation, sizeof( orientation ) );
   arc.ReadVector( &vieworigin );
   arc.ReadVector( &viewangles );
   arc.ReadInteger( &contents );
   arc.ReadInteger( &movetype );
   arc.ReadInteger( &mass );
   arc.ReadFloat( &gravity );
   arc.ReadInteger( &gravaxis );

   temp = arc.ReadInteger();
   if ( temp == -1 )
      groundentity = NULL;
   else
      groundentity = &g_edicts[ temp ];

   groundsurface = NULL;

   arc.ReadRaw( &groundplane, sizeof( groundplane ) );
   arc.ReadInteger( &groundcontents );

   arc.ReadInteger( &groundentity_linkcount );

   arc.ReadObjectPointer( ( Class ** )&bindmaster );
   arc.ReadString( &moveteam );
   arc.ReadObjectPointer( ( Class ** )&teamchain );
   arc.ReadObjectPointer( ( Class ** )&teammaster );

   arc.ReadInteger( &numchildren );
   arc.ReadRaw( children, sizeof( children ) );

   arc.ReadString( &target );
   arc.ReadString( &targetname );
   arc.ReadString( &killtarget );

	// reset target stuff
	SetTargetName( targetname.c_str() );
	SetTarget( target.c_str() );

   arc.ReadFloat( &health );
   arc.ReadFloat( &max_health );
   arc.ReadInteger( &deadflag );
   arc.ReadInteger( &flags );

   arc.ReadInteger( &watertype );
   arc.ReadInteger( &waterlevel );

   temp = arc.ReadInteger();
   takedamage = ( damage_t )temp;
   arc.ReadSafePointer( &enemy );
   arc.ReadFloat( &pain_finished );
   arc.ReadFloat( &damage_debounce_time );

   arc.ReadInteger( &tess_min_size );
   arc.ReadInteger( &tess_max_size );
   arc.ReadInteger( &tess_thickness );
   arc.ReadFloat( &tess_percentage );
   }

#include "worldspawn.h"

#endif
