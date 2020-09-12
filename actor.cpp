//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/actor.cpp                        $
// $Revision:: 233                                                            $
//   $Author:: Markd                                                          $
//     $Date:: 2/08/99 5:12p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/actor.cpp                             $
// 
// 233   2/08/99 5:12p Markd
// fixed 2015 actor problem
// 
// 232   1/29/99 6:14p Jimdose
// added 2015 changes
// 
// 231   1/27/99 10:02p Markd
// Merged 2015 source into main code base
// 
// 230   11/16/98 8:50p Markd
// increased chat times
// 
// 229   11/16/98 7:28p Markd
// bullet proofed TargetEnemies so that dead bodies only spoke their secret
// once and then cleared who they were upset at, much like a soul being
// released from a dead body ;)
// 
// 228   11/15/98 7:58p Jimdose
// Actors now exclusively use flags for movement types
// Made eyeposition max out at maxs.z
// Swim monsters will no longer leave water
// Air monsters will no longer enter water
// 
// 227   11/15/98 2:58a Markd
// scale pain threshold by skill a bit less than what it is right now
// 
// 226   11/15/98 1:24a Jimdose
// monsters don't play snd_sightenemy now unless DoAction( "sightenemy" )
// succeeds.
// 
// 225   11/14/98 6:41p Jimdose
// guys no longer drown in moving water after the water has moved
// 
// 224   11/13/98 11:55p Markd
// bodyimpact sound to goryimpact sound
// 
// 223   11/13/98 11:00p Jimdose
// Took EV_CONSOLE off of fov
// 
// 222   11/13/98 10:02p Jimdose
// bodies no longer float when they die in water
// guys will allow themselves to fall when they are standing on other setients
// 
// 221   11/13/98 4:04p Markd
// increased min melee range
// 
// 220   11/12/98 11:30p Jimdose
// Increased melee kick
// 
// 219   11/10/98 5:47p Jimdose
// Made CanSee non-inline because it caused link problems
// 
// 218   11/09/98 6:23p Markd
// Added turnspeed event
// 
// 217   11/08/98 7:06p Markd
// Put in nochatter, made mutants not Like each other, added seenEnemy to
// actorinfo
// 
// 216   11/07/98 10:16p Jimdose
// actors no longer get mad at scriptobjects that hurt them
// 
// 215   11/07/98 3:34p Markd
// Added nodeathfade command
// 
// 214   11/06/98 8:25p Jimdose
// made visiondistance adjustable from script
// 
// 213   11/03/98 10:02p Aldie
// Drop inventory when being tesselated
// 
// 212   10/27/98 9:06p Markd
// tweaked enemy aiming
// 
// 211   10/27/98 7:52p Jimdose
// added IfEnemyWithinEvent
// made guys not lean if they're not moving very far
// 
// 210   10/27/98 3:46p Markd
// Changed skill level on actors
// 
// 209   10/27/98 3:51a Jimdose
// added kick to MeleeEvent
// 
// 208   10/27/98 1:50a Markd
// Made JumpTo take in account water level
// 
// 207   10/26/98 9:53p Markd
// Moved GotKill around, added gibfest sound
// 
// 206   10/26/98 9:04p Markd
// Changed jumpto behavior
// 
// 205   10/26/98 8:22p Markd
// Put CheckWater in Killed function
// 
// 204   10/26/98 5:51p Jimdose
// actor saves off spawn args before processing init commands
// 
// 203   10/26/98 2:19p Markd
// Added last_jump_time
// 
// 202   10/26/98 1:20p Markd
// made guys be BestTargetable after having an enemy already
// 
// 201   10/26/98 12:13p Markd
// fixed bug with blood preventing parent mode melee attacks
// 
// 200   10/26/98 3:59a Jimdose
// made Trymove not return STEPMOVE_STUCK when opening doors 
// 
// 199   10/26/98 1:53a Jimdose
// TryMove was still using origin insteard of worldorigin, so the M_CheckBottom
// call was always checking where the monster currently was, and not where he
// was going to.
// 
// 198   10/25/98 11:53p Aldie
// Another dead check to avoid bodies that are in the air not going dead
// 
// 197   10/25/98 4:43a Markd
// Added animal event
// 
// 196   10/25/98 4:28a Jimdose
// Made opendoor a forced action
// made CanShootFrom do extra tests to see if it should shoot damagable objects
// 
// 195   10/25/98 1:52a Aldie
// Changed gibanim functionality to be location based
// 
// 194   10/24/98 3:10p Markd
// Put in eyeoffset command
// 
// 193   10/24/98 3:26a Markd
// Put in more debug info for actors
// 
// 192   10/24/98 12:42a Markd
// changed origins to worldorigins where appropriate
// 
// 191   10/23/98 6:46p Aldie
// Turn off shadows for death and do deathgib anim on location
// 
// 190   10/22/98 9:28p Aldie
// Added ability for deathgib animation
// 
// 189   10/22/98 3:05p Markd
// fixed movespeed on actors
// 
// 188   10/22/98 1:40a Markd
// Added FL_STEALTH ability
// 
// 187   10/21/98 11:15p Markd
// Put in FL_CLOAK ability for targetting from enemies
// 
// 186   10/21/98 6:43p Markd
// made eyeposition the top of their bounding box
// 
// 185   10/21/98 3:37p Markd
// put in different enemy alignment and put in support for skins
// 
// 184   10/21/98 2:13a Markd
// Fixed jumping stuff
// 
// 183   10/20/98 11:29p Markd
// Made CanShootFrom aim at the chest rather than the centroid
// 
// 182   10/20/98 8:05p Aldie
// Added a DoGib function to ease readability
// 
// 181   10/20/98 2:37a Markd
// Added additional JumpTo methods
// 
// 180   10/20/98 12:43a Markd
// Put in scale for health, setsize, melee_range and melee_damage
// 
// 179   10/19/98 11:53p Aldie
// Moved the solid_trigger setting to the setup function of touchfields
// 
// 178   10/19/98 11:49p Aldie
// Fixed a bug where touch field was SOLID_BBOX.  Now it is forced to
// SOLID_TRIGGER.
// 
// 177   10/19/98 9:55p Markd
// Made it so "state" event does a ProcessScript
// 
// 176   10/19/98 8:58p Aldie
// Fix dead check for bodies in water
// 
// 175   10/19/98 2:58a Markd
// Fixed CanShootFrom and Jumping
// 
// 174   10/19/98 2:41a Markd
// made MakeEnemy not target the world
// 
// 173   10/19/98 2:41a Aldie
// Removed MOVETYPE_TOSS when actors die
// 
// 172   10/19/98 12:04a Jimdose
// made all code use fast checks for inheritance (no text lookups when
// possible)
// isSubclassOf no longer requires ::_classinfo()
// 
// 171   10/18/98 6:43p Markd
// If no melee attack, make weapon not droppable
// 
// 170   10/18/98 12:34a Markd
// Scaled shots_per_attack based on skill level
// 
// 169   10/18/98 12:01a Markd
// Fixed AttackEntity and IfCanShoot
// 
// 168   10/17/98 11:00p Markd
// Added IfCanShoot and not gettine mad at non-damageable things
// 
// 167   10/17/98 9:41p Markd
// Made InvestigateSound not set nextsoundtime unless the Action responds
// 
// 166   10/17/98 7:34p Jimdose
// deleted trig when actor deleted
// 
// 165   10/17/98 4:59p Markd
// Added attackmode event
// 
// 164   10/17/98 3:31p Markd
// Made firing more accurate over great distances
// 
// 163   10/17/98 12:34a Markd
// Initialized chattime to random( 20 )
// 
// 162   10/16/98 7:18p Markd
// Added a bunch of new commands, and added interfaces to the editor
// 
// 161   10/16/98 3:11a Aldie
// Double the armor when actors die
// 
// 160   10/16/98 1:41a Jimdose
// Added goto command for actors.  This helps the all too common mistake of
// typing "local.self goto label"
// 
// 159   10/15/98 9:32p Markd
// Made inanimate objects not move, not bleed, and not gib
// 
// 158   10/14/98 10:54p Jimdose
// Made Hates check for a null entity
// Added null check to investigate functions
// 
// 157   10/14/98 9:00p Markd
// Fixed JumpTo command, speed wise
// 
// 156   10/14/98 5:20p Markd
// Added jumpto event and jumpto function
// 
// 155   10/14/98 2:17a Markd
// Added in ifcanmeleeattack event
// 
// 154   10/14/98 1:27a Markd
// Added Has_weapon support
// 
// 153   10/14/98 12:11a Markd
// Put extra reach into melee event
// 
// 152   10/13/98 11:03p Markd
// Put scale in on all Anim_delta calls
// 
// 151   10/13/98 7:34p Markd
// made gib code scalable
// 
// 150   10/13/98 12:26a Markd
// Added support for flying creatures, also made it so that CanShootFrom fired
// from the centroid, and not from the gun position
// 
// 149   10/11/98 8:17p Markd
// Working on nautic fixes
// 
// 148   10/11/98 5:20p Markd
// Put in default pain_thresholds
// 
// 147   10/11/98 5:00p Markd
// Fixed water drowning, changed ProcessCommands so that it doesn't overwrite
// the the "thread" variable
// 
// 146   10/11/98 12:32a Markd
// Added Flight ability
// 
// 145   10/10/98 9:12p Markd
// Fixed Chatter using an alias for SoundTimeLength
// 
// 144   10/10/98 7:59p Markd
// Put in painthreshold and snd_pain_taunt
// 
// 143   10/10/98 5:01p Markd
// Changed trace masks to edict->clipmasks
// 
// 142   10/10/98 3:27p Markd
// Made EndBehavior always notify the actor script
// 
// 141   10/10/98 1:24a Jimdose
// Did some bulletproofing against possible NULL actorthread
// Prethink kills actors with NULL threads
// added SetVariable for setting thread variables safely
// 
// 140   10/09/98 5:24p Markd
// Fixed inanimate actor animations
// 
// 139   10/09/98 4:59p Jimdose
// Working on savegames
// 
// 138   10/07/98 11:32a Markd
// Made DamageThresholds targetable by actors
// 
// 137   10/06/98 5:25p Markd
// Made MakeEnemy and DoAction take the force parameter
// 
// 136   10/06/98 12:14p Markd
// Added ForceAction
// 
// 135   10/05/98 10:33p Markd
// Added canStrafe and noStrafe, also added MinimumAttackRange
// 
// 134   10/05/98 2:57p Markd
// Changed Chatter settings
// 
// 133   10/04/98 10:36p Markd
// Put in attack_finished
// 
// 132   10/04/98 8:45p Aldie
// Gib functions
// 
// 131   10/04/98 2:49p Markd
// Fixed swimming and forward speed stuff
// 
// 130   10/03/98 7:15p Markd
// got swimming characters working, in the process re-wrote a lot of the combat
// stuff
// 
// 129   10/01/98 8:00p Markd
// Added melee capabilities
// 
// 128   10/01/98 4:13p Jimdose
// Fixed some problems with CanShootFrom that prevented guys from being able to
// shoot the player when he's on ledges with railings
// 
// 127   9/24/98 7:26p Markd
// made inanimate objects not set off triggers
// 
// 126   9/24/98 7:10p Jimdose
// Added MyGunAngles
// 
// 125   9/24/98 12:42a Jimdose
// attempting to fix dead guys hanging in air
// 
// 124   9/22/98 10:19p Jimdose
// Initialized lastmove
// Fixed InFov
// Set fovdot in Fov event
// 
// 123   9/22/98 5:19p Markd
// Put in new consolidated gib function
// 
// 122   9/22/98 5:10p Jimdose
// Fixed inanimate objects
// 
// 121   9/22/98 3:21p Markd
// put in parentmode lockout for blood and gibs
// 
// 120   9/22/98 6:27a Jimdose
// Fixed bug when setting "attackmode"
// 
// 119   9/22/98 5:37a Jimdose
// Made attackmode only set once when thread is created
// 
// 118   9/22/98 5:31a Jimdose
// Added attackmode
// 
// 117   9/22/98 1:58a Jimdose
// Added lastmove and forwardspeed
// Regrouped functions by functionality
// Removed reaction table stuff
// 
// 116   9/19/98 7:49p Jimdose
// Fixed uninitialized pointer in ShowInfo and added more data
// 
// 115   9/19/98 6:16p Jimdose
// Added AttackPlayer
// AttackEntity and AttackPlayer makes the actor attack the entity immediately
// by forcing a call to SightEnemy
// 
// 114   9/19/98 4:34p Jimdose
// changed gi.dprintf's to gi.printf's in ShowInfo
// 
// 113   9/18/98 10:55p Jimdose
// Added inanimate actor type
// started work on swimming monsters
// 
// 112   9/16/98 8:38p Jimdose
// Made InFOV only test the fov in 2 dimensions
// 
// 111   9/14/98 5:26p Jimdose
// Made EndBehavior set script variables
// Added some checks for NULL when getting nearest nodes
// SeenEnemy is now cleared when currentEnemy is killed
// CanShootFrom no longer assumes ScriptSlaves are shootable, but does shoot
// ScriptModel.  Gotta find some solution that allows the level designers to
// specify whats shootable by the AI.
// 
// 110   9/08/98 9:48p Jimdose
// Enabled multi-size bounding box path code
// 
// 109   9/03/98 9:05p Jimdose
// Guys will now shoot through scriptslaves and objects with the assumption
// that he can destroy it
// 
// 108   8/31/98 7:46p Jimdose
// Spread out targeting a bit 
// 
// 107   8/31/98 5:42p Jimdose
// Added checks for NULL pointer in MakeEnemy and AttackEnemy
// 
// 106   8/29/98 9:39p Jimdose
// Added call info to G_Trace
// 
// 105   8/29/98 5:26p Markd
// added specialfx, replaced misc with specialfx where appropriate
// 
// 104   8/29/98 1:11p Markd
// Made it so M_CheckBottom only checks if groundentity is not world
// 
// 103   8/27/98 9:00p Jimdose
// Made centroid into a variable
// Made guys target enemies less often
// MakeEnemy checks if ent is the world (when a target is non-valid, the ent
// may be the world)
// 
// 102   8/27/98 6:00p Aldie
// Drop inventory items if the actors are gibbed.
// 
// 101   8/27/98 4:49p Jimdose
// Fixed bug with hidden actors being shown again on startup
// Made actors not target hidden enemies, or target while hidden (for
// cinematics)
// 
// 100   8/27/98 4:27p Markd
// detach children
// 
// 99    8/26/98 11:13p Jimdose
// Began strafe support
// 
// 98    8/26/98 6:45p Jimdose
// Made DefineStateEvent prepend the value in ai_actorscript
// 
// 97    8/24/98 6:55p Jimdose
// Added crouching pain and death animations
// Added path
// 
// 96    8/20/98 8:38p Jimdose
// Actors now share enemy info between each other on sight
// CanShoot checks the head as well as the centroid
// InFOV now uses an eliptical cone for testing vision (better vertical
// peripheral vision).
// 
// 95    8/19/98 4:57p Jimdose
// CanShootFrom now takes min and max weapon firing distances into account
// 
// 94    8/19/98 3:59p Jimdose
// Added IfNearEvent and CopyStateEvent
// 
// 93    8/19/98 2:30p Jimdose
// Can no longer alias "alert" to "idle" so I've added a hasalert variable
// 
// 92    8/18/98 11:57p Aldie
// Fixed init variable warning
// 
// 91    8/18/98 11:08p Markd
// Added new Alias System
// 
// 90    8/18/98 9:59p Jimdose
// Made actors only react to some sounds when they're caused by an enemy.
// Hmmm, would be nice if they checked their "memory" to see if they expect
// that kind of sound from there.
// 
// 89    8/15/98 5:29p Jimdose
// Fixed up the thread startup code.  No longer need to wait .1 in the script
// before sending commands.  Actor script is no longer run twice (because of
// the delayed model init commands.
// Got rid of !init label in scripts.  Now starts at beginning unless a label
// is given.
// CanShoot checks vision distance as an early exit.
// 
// 88    8/14/98 11:34p Jimdose
// Got rid of "runtoarea" state.  Attack now just lets MakeEnemy call
// sightenemy.  Hmmm...probably should change to make sure that actor
// immediatly attacks the specified entity.
// don't set currentEnemy until sightenemy is responded to.  Gets rid of a lot
// of brain dead situations.
// 
// 87    8/14/98 6:24p Jimdose
// Got rid of decelleration for steering
// 
// 86    8/13/98 7:30p Jimdose
// actorThread is now persistant.  Threads don't get killed unless actor dies
// or is removed.
// 
// 85    8/08/98 2:05p Markd
// Added entity who got the event to ForwardBehaviorEvent
// 
// 84    8/07/98 7:57p Markd
// Added ForwardToBehavior event
// 
// 83    8/07/98 6:01p Jimdose
// Rewrite AimAndShoot
// 
// 82    8/06/98 6:59p Jimdose
// Added IfEnemyVisible
// 
// 81    8/05/98 7:18p Jimdose
// Added definestate, ignoresounds, respondtosounds, respondtoall
// 
// 80    8/03/98 6:49p Jimdose
// fixed thread bug
// 
// 79    7/29/98 6:32p Jimdose
// Added MonsterStart
// 
// 78    7/29/98 6:27p Jimdose
// Removed monster.h
// 
// 77    7/29/98 2:30p Aldie
// Changed health to a float
// 
// 76    7/26/98 3:40p Jimdose
// Fixed guys in water
// guys no longer open locked doors
// 
// 75    7/26/98 11:43a Jimdose
// Added EnemyCanSeeMeFrom
// 
// 74    7/26/98 6:44a Jimdose
// Overrode the setsize event so that def files don't change the hardcoded size
// (need to fix these damn paths one day).
// 
// 73    7/26/98 3:48a Jimdose
// Modified aim based on skill
// 
// 72    7/25/98 4:39p Jimdose
// Guys shoot at vehicles and shoot out windows
// 
// 71    7/25/98 2:07a Jimdose
// Fixed bug with trig being delete without being NULLed out when gibbing
// Guys now attack any enemy
// 
// 70    7/24/98 9:59p Aldie
// Gib stuff
// 
// 69    7/24/98 6:16p Aldie
// Check for inventory items before removing dead guys
// 
// 68    7/24/98 4:14p Aldie
// Cancel useless checks
// 
// 67    7/24/98 3:46p Aldie
// Increased gibs
// 
// 66    7/23/98 10:16p Jimdose
// Removed ignoreenemies stuff
// Fixed a bunch of anim screwups when actor is killed
// fixed "big gib" bug
// 
// 65    7/23/98 6:55p Aldie
// Fun with gibs.
// 
// 64    7/23/98 6:19p Jimdose
// ignoreEnemies was being set when character was targeted
// 
// 63    7/22/98 7:02p Aldie
// Added ability to remove useless bodies.
// 
// 62    7/22/98 2:32p Jimdose
// fixed bug where guys wouldn't sight the enemy if the went into pain
// 
// 61    7/21/98 9:34p Jimdose
// Chatter now checks if the alias exists before playing the sound, thereby not
// generating warnings of missing sounds.
// 
// 60    7/19/98 9:20p Jimdose
// Improved support for overriding the default script
// 
// 59    7/16/98 6:21p Jimdose
// Fixed crash when actorthread was null
// 
// 58    7/14/98 11:50p Jimdose
// Made PopState return whether a new state was popped off the stack
// StateDoneEvent now kills the calling thread if no previous state exists on
// the stack
// DoAction creates a new thread if no actor thread exists
// 
// 57    7/14/98 6:57p Aldie
// Moved setsize before setmodel
// 
// 56    7/13/98 4:59p Aldie
// Added dead player bodies with gibbing
// 
// 55    7/09/98 10:40p Aldie
// Moved bodyparts to game
// 
// 54    7/08/98 8:59p Jimdose
// Moved opening door to script
// 
// 53    7/08/98 1:00p Jimdose
// added crouchsize and standsize
// 
// 52    7/07/98 11:37p Jimdose
// Replaced priority-based system with full script-based state system
// 
// 51    7/06/98 1:06p Jimdose
// working on ai
// 
// 50    6/30/98 6:47p Aldie
// Added Gib Event
// 
// 49    6/30/98 6:00p Jimdose
// Added more states and state detection code.
// Added range detection
// added health level detection
// 
// 48    6/25/98 8:46p Markd
// Removed rotating doors
// 
// 47    6/25/98 8:29p Aldie
// Updated killed and death
// 
// 46    6/25/98 8:10p Jimdose
// Disabled some prints
// 
// 45    6/25/98 8:10p Jimdose
// Using global actor script
// 
// 44    6/24/98 4:26p Jimdose
// Fixed bugs in TurnTo
// 
// 43    6/23/98 5:59p Aldie
// Fixed dropWeapon stuff.
// 
// 42    6/20/98 7:47p Markd
// Added location based pain and death support
// 
// 41    6/19/98 9:27p Jimdose
// Added GetGunOrientation
// 
// 40    6/19/98 4:44p Jimdose
// Added util functions InFOV, etc.
// 
// 39    6/18/98 8:45p Jimdose
// Removed string based SetBehavior and PushState functions
// Added source info to events
// 
// 38    6/18/98 2:00p Markd
// rewrote tesselation code
// 
// 37    6/17/98 10:00p Jimdose
// Improved door opening code
// Moved phyics move into class
// 
// 36    6/17/98 3:15p Markd
// fixed arg issue
// 
// 35    6/17/98 3:03p Markd
// Changed NumArgs back to previous behavior
// 
// 34    6/17/98 1:19a Jimdose
// Moved setOwner to Item.  
// Added EV_Item_Pickup
// 
// 33    6/15/98 10:46p Jimdose
// Made neutral allias become enemies with pain
// shurnk bounding box temporarily
// 
// 32    6/13/98 8:25p Jimdose
// Added leaning into turns (alright already Tom!)
// Added enemy visibility tests for FindCover
// 
// 31    6/11/98 12:44a Jimdose
// behaviors now get info from the script at startup
// 
// 30    6/10/98 10:24p Jimdose
// added priority based state system
// 
// 29    6/09/98 4:18p Jimdose
// worked on ai
// 
// 28    6/04/98 10:48p Jimdose
// Fixed a bunch of things that got broken just in time for E3.  Paths and
// scripting actually work now.
// 
// 27    6/03/98 5:43p Jimdose
// Fixed spelling of behavior. :)
// 
// 26    6/03/98 4:36p Markd
// Removed gun stuff from entity, it is now sent over as a separate object
// 
// 25    6/02/98 7:46p Markd
// Took out currentweapon assignments for client-side stuff
// 
// 24    5/28/98 6:01p Markd
// When actors die, they kill their dynamic light
// 
// 23    5/28/98 2:11p Markd
// Made enemies drop weapons and only fire if their weapons are ready
// 
// 22    5/28/98 1:50p Markd
// made actors drop weapons
// 
// 21    5/27/98 4:56p Markd
// Only gib when inflictor is rocket
// 
// 20    5/27/98 12:04p Jimdose
// fixed null pointer prob
// 
// 19    5/27/98 11:59a Jimdose
// Gibbing is harder
// 
// 18    5/27/98 11:50a Jimdose
// Added killtarget and target to killed
// 
// 17    5/27/98 7:15a Jimdose
// took out dprintf
// 
// 16    5/27/98 7:12a Jimdose
// ai ai ai
// 
// 15    5/27/98 6:39a Jimdose
// working on ai
// 
// 14    5/27/98 5:27a Aldie
// Added gibs
// 
// 13    5/27/98 5:11a Jimdose
// working on ai
// 
// 12    5/25/98 6:46p Jimdose
// Made animateframe, prethink and posthink into functions built into the base
// entity class
// 
// 11    5/25/98 5:32p Jimdose
// Pathnodes are no longer a subclass of Entity.  This was done to save on
// edicts
// 
// 10    5/25/98 1:06a Jimdose
// Added chatter
// 
// 9     5/24/98 8:46p Jimdose
// Made a lot of functions more str-friendly.
// Got rid of a lot of char * based strings
// Cleaned up get spawn arg functions and sound functions
// sound functions now use consistant syntax
// 
// 8     5/24/98 1:02a Jimdose
// Added monster hearing
// 
// 7     5/23/98 6:27p Jimdose
// Improved steering and opening doors
// 
// 6     5/22/98 9:44p Jimdose
// Disabled debug lines when checking to shoot
// 
// 5     5/22/98 9:38p Jimdose
// Commented out prints
// 
// 4     5/22/98 9:36p Jimdose
// AI Scripting works again (somewhat)
// 
// 3     5/20/98 6:36p Jimdose
// Rewrite
// 
// 2     5/18/98 8:15p Jimdose
// Created file
// 
// DESCRIPTION:
// Base class for character AI.
//

#include "g_local.h"
#include "actor.h"
#include "behavior.h"
#include "scriptmaster.h"
#include "doors.h"
#include "gibs.h"
#include "vehicle.h"
#include "misc.h"
#include "specialfx.h"
#include "object.h"
#include "scriptslave.h"
#include "explosion.h"
#include "misc.h"

//#define DEBUG_PRINT

CLASS_DECLARATION( Class, ActorState, NULL );

ResponseDef ActorState::Responses[] =
	{
		{ NULL, NULL }
	};

cvar_t *ai_actorscript;

// used below for a slight movement tweak
// added as a global here to prevent constant re-allocation
const Vector movetweak = "0 0 2";

#define TURN_SPEED		30

CLASS_DECLARATION( Sentient, Actor, "monster_generic" );

Event	EV_Actor_CrouchSize( "crouchsize" );
Event	EV_Actor_Fov( "fov" );
Event EV_Actor_VisionDistance( "visiondistance" );
Event EV_Actor_Start( "start" );
Event	EV_Actor_Dead( "dead" );

Event EV_Actor_ClearState( "clearstate" );
Event EV_Actor_SetState( "state" );
Event EV_Actor_SetBehavior( "behavior" );

Event EV_Actor_Friend( "friend" );				// Allied to player
Event EV_Actor_Civilian( "civilian" );			// Nuetral to all, runs from danger
Event EV_Actor_Enemy( "enemy" );					// Enemy to player
Event EV_Actor_Monster( "monster" );			// Enemy to player, civilians, and inanimate objects
Event EV_Actor_Animal( "animal" );		   	// neutral to all
Event EV_Actor_Inanimate( "inanimate" );		// Inanimate objects

Event EV_Actor_Swim( "swim" );					// specifies actor as being able to swim
Event EV_Actor_Fly( "fly" );					   // specifies actor as being able to swim
Event EV_Actor_NotLand( "noland" );				// specifies actor as not being able to walk on land

Event EV_Actor_TargetEnemies( "targetenemies" );

// Scripting
Event EV_Actor_Script( "script" );
Event EV_Actor_Thread( "thread" );

Event EV_Actor_IfEnemyVisible( "ifenemyvisible" );
Event EV_Actor_IfNear( "ifnear" );

Event EV_Actor_ForwardSpeed( "forwardspeed" );

Event EV_Actor_Idle( "idle" );
Event EV_Actor_LookAt( "lookat" );
Event EV_Actor_TurnTo( "turnto" );
Event EV_Actor_FinishedBehavior( "finishedbehavior" );
Event EV_Actor_NotifyBehavior( "notifybehavior" );
Event EV_Actor_WalkTo( "walkto" );
Event EV_Actor_JumpTo( "jumpto" );
Event EV_Actor_RunTo( "runto" );
Event EV_Actor_Anim( "anim" );
Event EV_Actor_Attack( "attack" );
Event EV_Actor_AttackPlayer( "attackplayer" );

Event EV_Actor_ReserveNode( "reservenode" );
Event EV_Actor_ReleaseNode( "releasenode" );
Event EV_Actor_IfCanHideAt( "ifcanhideat" );
Event EV_Actor_IfCanStrafeAttack( "ifcanstrafeattack" );
Event EV_Actor_IfCanMeleeAttack( "ifcanmeleeattack" );
Event EV_Actor_IfCanShoot( "ifcanshoot" );
Event EV_Actor_IfEnemyWithin( "ifenemywithin" );

Event EV_Actor_IgnoreSounds( "ignoresounds" );
Event EV_Actor_RespondToSounds( "respondtosounds" );
Event EV_Actor_IgnoreAll( "ignoreall" );
Event EV_Actor_RespondToAll( "respondtoall" );
Event EV_Actor_RespondTo( "respondto" );
Event EV_Actor_Ignore( "ignore" );
Event EV_Actor_DefineState( "definestate" );
Event EV_Actor_CopyState( "copystate" );

Event EV_Actor_Remove( "remove_useless" );

Event EV_Actor_ForwardToBehavior( "forwardcommand" );
Event EV_Actor_Aim( "aim" );
Event EV_Actor_MeleeRange( "meleerange" );
Event EV_Actor_MeleeDamage( "meleedamage" );
Event EV_Actor_Melee( "melee" );
Event EV_Actor_AttackFinished( "attack_finished" );

Event EV_Actor_CanStrafe( "canstrafe" );
Event EV_Actor_NoStrafe( "nostrafe" );

Event EV_Actor_PainThreshold( "painthreshold" );
Event EV_Actor_SetKillThread( "killthread" );
Event EV_Actor_AttackRange( "attackrange" );
Event EV_Actor_ShotsPerAttack( "shotsperattack" );
Event EV_Actor_ClearEnemy( "clearenemy" );
Event EV_Actor_AttackMode( "attackmode" );
Event EV_Actor_EyePositionOffset( "eyeoffset" );
Event EV_Actor_NoDeathFade( "nodeathfade" );
Event EV_Actor_NoChatter( "nochatter" );
Event EV_Actor_TurnSpeed( "turnspeed" );

ResponseDef StateInfo::Responses[] =
	{
		{ NULL, NULL }
	};

CLASS_DECLARATION( Class, StateInfo, NULL );

StateInfo::StateInfo()
	{
	ignore = true;
	}

ResponseDef Actor::Responses[] =
	{
		{ &EV_Activate,					( Response )Actor::ActivateEvent },
		{ &EV_Use,							( Response )Actor::UseEvent },

	   { &EV_Actor_Start,				( Response )Actor::Start },
	   { &EV_Pain,							( Response )Actor::Pain },
	   { &EV_Killed,						( Response )Actor::Killed },
		{ &EV_Actor_Dead,					( Response )Actor::Dead },

		{ &EV_Actor_TargetEnemies,		( Response )Actor::TargetEnemies },

		{ &EV_Actor_SetBehavior,		( Response )Actor::SetBehaviorEvent },
      { &EV_Actor_ForwardSpeed,     ( Response )Actor::ForwardSpeedEvent },

		{ &EV_Actor_CrouchSize,			( Response )Actor::CrouchSize },
      { &EV_Actor_Fov,              ( Response )Actor::SetFov },
      { &EV_Actor_VisionDistance,   ( Response )Actor::SetVisionDistance },
		{ &EV_Actor_Friend,				( Response )Actor::FriendEvent },
		{ &EV_Actor_Civilian,			( Response )Actor::CivilianEvent },
		{ &EV_Actor_Enemy,				( Response )Actor::EnemyEvent },
      { &EV_Actor_Monster,          ( Response )Actor::MonsterEvent },
      { &EV_Actor_Animal,           ( Response )Actor::AnimalEvent },
      { &EV_Actor_Inanimate,        ( Response )Actor::InanimateEvent },
      { &EV_Actor_Swim,             ( Response )Actor::SwimEvent },
      { &EV_Actor_Fly,              ( Response )Actor::FlyEvent },
      { &EV_Actor_NotLand,          ( Response )Actor::NotLandEvent },
      { &EV_Gib,                    ( Response )Actor::GibEvent },

		// Scripting
		{ &EV_Actor_DefineState,		( Response )Actor::DefineStateEvent },
		{ &EV_Actor_CopyState,			( Response )Actor::CopyStateEvent },
		{ &EV_Actor_IgnoreAll,			( Response )Actor::IgnoreAllEvent },
		{ &EV_Actor_RespondToAll,		( Response )Actor::RespondToAllEvent },
		{ &EV_Actor_RespondTo,			( Response )Actor::RespondToEvent },
		{ &EV_Actor_Ignore,				( Response )Actor::IgnoreEvent },
		{ &EV_Actor_IgnoreSounds,		( Response )Actor::IgnoreSoundsEvent },
		{ &EV_Actor_RespondToSounds,	( Response )Actor::RespondToSoundsEvent },

		{ &EV_Actor_ClearState,			( Response )Actor::ClearStateEvent },
		{ &EV_ScriptThread_End,			( Response )Actor::StateDoneEvent },
		{ &EV_Actor_SetState,			( Response )Actor::SetStateEvent },
		{ &EV_Actor_Script,				( Response )Actor::SetScript },
		{ &EV_Actor_Thread,				( Response )Actor::SetThread },
		{ &EV_Actor_IfEnemyVisible,	( Response )Actor::IfEnemyVisibleEvent },
		{ &EV_Actor_IfNear,				( Response )Actor::IfNearEvent },
		{ &EV_Actor_Idle,					( Response )Actor::IdleEvent },
		{ &EV_ProcessCommands,			( Response )Actor::StartMove },
		{ &EV_Actor_LookAt,				( Response )Actor::LookAt },
		{ &EV_Actor_TurnTo,				( Response )Actor::TurnToEvent },
		{ &EV_Actor_FinishedBehavior,	( Response )Actor::FinishedBehavior },
		{ &EV_Actor_NotifyBehavior,	( Response )Actor::NotifyBehavior },
		{ &EV_Actor_WalkTo,				( Response )Actor::WalkTo },
		{ &EV_Actor_JumpTo,				( Response )Actor::JumpToEvent },
		{ &EV_Actor_RunTo,				( Response )Actor::RunTo },
		{ &EV_Actor_Anim,					( Response )Actor::Anim },
		{ &EV_Actor_Attack,				( Response )Actor::AttackEntity },
      { &EV_Actor_AttackPlayer,     ( Response )Actor::AttackPlayer },
      { &EV_Actor_Remove,				( Response )Actor::RemoveUselessBody },
      { &EV_Actor_ForwardToBehavior,( Response )Actor::ForwardBehaviorEvent },

		{ &EV_Actor_ReserveNode,		( Response )Actor::ReserveNodeEvent },
		{ &EV_Actor_ReleaseNode,		( Response )Actor::ReleaseNodeEvent },
		{ &EV_Actor_IfCanHideAt,		( Response )Actor::IfCanHideAtEvent },
		{ &EV_Actor_IfCanStrafeAttack,( Response )Actor::IfCanStrafeAttackEvent },
		{ &EV_Actor_IfCanMeleeAttack, ( Response )Actor::IfCanMeleeAttackEvent },
		{ &EV_Actor_IfCanShoot,       ( Response )Actor::IfCanShootEvent },
      { &EV_Actor_IfEnemyWithin,    ( Response )Actor::IfEnemyWithinEvent },

		{ &EV_HeardWeapon,				( Response )Actor::InvestigateWeaponSound },
		{ &EV_HeardMovement,				( Response )Actor::InvestigateMovementSound },
		{ &EV_HeardPain,					( Response )Actor::InvestigatePainSound },
		{ &EV_HeardDeath,					( Response )Actor::InvestigateDeathSound },
		{ &EV_HeardBreaking,				( Response )Actor::InvestigateBreakingSound },
		{ &EV_HeardDoor,					( Response )Actor::InvestigateDoorSound },
		{ &EV_HeardMutant,				( Response )Actor::InvestigateMutantSound },
		{ &EV_HeardVoice,					( Response )Actor::InvestigateVoiceSound },
		{ &EV_HeardMachine,				( Response )Actor::InvestigateMachineSound },
		{ &EV_HeardRadio,					( Response )Actor::InvestigateRadioSound },

		{ &EV_Actor_Aim,					( Response )Actor::SetAim },
		{ &EV_Actor_MeleeRange,			( Response )Actor::SetMeleeRange },
		{ &EV_Actor_MeleeDamage,		( Response )Actor::SetMeleeDamage },
		{ &EV_Actor_Melee,		      ( Response )Actor::MeleeEvent },
		{ &EV_Actor_AttackFinished,	( Response )Actor::AttackFinishedEvent },

		{ &EV_Actor_CanStrafe,	      ( Response )Actor::CanStrafeEvent },
		{ &EV_Actor_NoStrafe,	      ( Response )Actor::NoStrafeEvent },

      { &EV_Actor_PainThreshold,    ( Response )Actor::SetPainThresholdEvent },
      { &EV_Actor_SetKillThread,    ( Response )Actor::SetKillThreadEvent },
      { &EV_Actor_AttackRange,      ( Response )Actor::AttackRangeEvent },
      { &EV_Actor_ShotsPerAttack,   ( Response )Actor::ShotsPerAttackEvent },
      { &EV_Actor_ClearEnemy,       ( Response )Actor::ClearEnemyEvent },
      { &EV_Actor_AttackMode,       ( Response )Actor::AttackModeEvent },
	   { &EV_SetHealth,			      ( Response )Actor::SetHealth },
	   { &EV_Actor_EyePositionOffset,( Response )Actor::EyeOffset },
	   { &EV_Actor_NoDeathFade,      ( Response )Actor::NoDeathFadeEvent },
	   { &EV_Actor_NoChatter,        ( Response )Actor::NoChatterEvent },
	   { &EV_Actor_TurnSpeed,        ( Response )Actor::TurnSpeedEvent },

      { &EV_ScriptThread_Goto,      ( Response )Actor::GotoEvent },

		{ NULL, NULL }
	};

//***********************************************************************************************
//
// Initialization functions
//
//***********************************************************************************************

Actor::Actor()
	{
	const char *text;
	str script;
   const char * skinname;
	Event *ev;
   SpawnArgs args;

	// don't spawn monsters in deathmatch
	if ( deathmatch->value || nomonsters->value )
		{
		PostEvent( EV_Remove, 0 );
		return;
		}

	actortype = IS_ENEMY;

	setSolidType( SOLID_BBOX );
	setMoveType( MOVETYPE_STEP );

	health				 = G_GetFloatArg( "health", 100 );
	max_health			 = health;
	takedamage			 = DAMAGE_AIM;
	mass					 = G_GetFloatArg( "mass", 200 );
	deadflag				 = DEAD_NO;
	edict->clipmask	 = MASK_MONSTERSOLID;
	edict->svflags		|= SVF_MONSTER;

   forwardspeed = 0;
   checkStrafe = true;

   // No longer used
   movement = AI_CANWALK;
   
   lastmove = STEPMOVE_OK;

	gunoffset = "0 0 44";

	numonstack = 0;
	behavior = NULL;
	path = NULL;

	newanimnum = -1;
	newanim = "";
	newanimevent = NULL;

	text = G_GetSpawnArg( "weapon" );
	if ( text )
		{
		giveWeapon( text );
		}

   spawngroup = G_GetStringArg( "spawngroup" );

   attackmode = G_GetIntArg( "attackmode", 0 );

   attack_range = G_GetFloatArg( "attackrange", 8192 );

	fov = 150;
	fovdot = cos( fov * 0.5 * M_PI / 180.0 );

	vision_distance = G_GetFloatArg( "visiondistance", 1024 );

   eyeoffset = "0 0 0";
	eyeposition = "0 0 64";

	hasalert = false;

	lastEnemy = NULL;
	enemyRange = RANGE_FAR;
	seenEnemy = false;
   nodeathfade = false;
   nochatter = false;

	turnspeed = 60;

   if ( !parentmode->value )
      {
      flags |= FL_BLOOD;
      flags |= FL_DIE_GIBS;
      }

   //
   // don't talk all at once initially
   //
	chattime = G_Random( 20 );
	nextsoundtime = 0;
   trig = NULL;
   deathgib = false;

	// set default crouchsize
	crouchsize_min = "-16 -16 0";
	crouchsize_max = "16 16 32";
	standsize_min = mins;
	standsize_max = maxs;

	// use a cvar to help with debugging
	ai_actorscript = gi.cvar( "ai_actorscript", "", 0 );
	actorscript = G_GetStringArg( "script", "global/enemy.scr" );
	actorstart = G_GetStringArg( "thread", "" );
	kill_thread = G_GetStringArg( "killthread", "" );

   // default melee characteristics
   melee_range = 100;
   melee_damage = 30;
   // default aim (normal)
   aim = G_GetFloatArg( "aim", 0 );
   // default pain_threshold is 10
   pain_threshold = G_GetFloatArg( "painthreshold", 10 * skill->value );
   // default shots per attack is 5 + ( 2 * skill->level )
   shots_per_attack = G_GetFloatArg( "shotsperattack", 3 + ( 2 * skill->value ) );

	startpos = worldorigin;

	next_drown_time = 0;
	air_finished = level.time + 5;
   last_jump_time = 0;

   CheckWater();

   setSize( "-16 -16 0", "16 16 76" );
   //setModel( G_GetSpawnArg( "model", "grunt.def" ) );
	showModel();

   if ( !LoadingSavegame )
      {
      // save off our spawn args
      args.SetArgs();
      G_InitSpawnArguments();

	   // force the init commands to be processed so that we start the right actor script immediately
	   CancelEventsOfType( EV_ProcessInitCommands );
	   ev = new Event( EV_ProcessInitCommands );
	   ev->AddInteger( edict->s.modelindex );
	   ProcessEvent( ev );

      SetupThread();

      if ( eyeposition.z > maxs.z )
         {
         eyeposition.z = maxs.z;
         }

      // restore our args
      G_InitSpawnArguments();
      args.RestoreArgs();
   
      // wait until the script starts before thinking
	   PostEvent( EV_Actor_Start, FRAMETIME );
      }

   //
   // I put this here, so that the initcommands would already be processed
   //
   skinname = G_GetSpawnArg( "skin" );
   if ( skinname && skinname[ 0 ] )
      {
      int skinnum;

      skinnum = gi.Skin_NumForName( edict->s.modelindex, skinname );
      if (skinnum >= 0)
         edict->s.skinnum = skinnum;
      }

	}

Actor::~Actor()
	{
	int n;
	int i;

	if ( actorthread )
		{
		actorthread->ProcessEvent( EV_ScriptThread_End );
		actorthread = NULL;
		}

	// delete the old action/response list
	n = actionList.NumObjects();
	for( i = n; i >= 1; i-- )
		{
		delete actionList.ObjectAt( i );
		}
	actionList.ClearObjectList();
	if ( behavior )
		{
		delete behavior;
		behavior = NULL;
		}

	if ( path )
		{
		delete path;
		path = NULL;
		}

   if ( trig )
      {
      delete trig;
      trig = NULL;
      }

	ClearStateStack();
	}

void Actor::Start
	(
	Event *ev 
	)

	{
	MonsterStart *start;
	
	// This is only used for choosing delay times for targeting enemies
	static int actornum = 0;

	hasalert = ( gi.Anim_Random( edict->s.modelindex, "alert" ) != -1 );

	start = MonsterStart::GetRandomSpot( spawngroup );
	if ( start )
		{
		setOrigin( start->worldorigin );
		worldorigin.copyTo( edict->s.old_origin );
		setAngles( start->worldangles );
		if ( start->animname != "" )
			{
			SetAnim( start->animname );
			}
		}

	droptofloor( 16 );

	flags |= FL_PRETHINK;

   // see if we have any melee attacks
   if ( HasAnim( "melee" ) )
      {
      has_melee = true;
      }
   else
      {
      // 
      // make sure we can't knock the weapon out of this characters hands
      //
      if ( currentWeapon )
         {
         Event * ev;

         ev = new Event( EV_Weapon_NotDroppable );
         currentWeapon->ProcessEvent( ev );
         }
      has_melee = false;
      }

	// spread their targeting about a bit
	PostEvent( EV_Actor_TargetEnemies, ( actornum++ % 10 ) * FRAMETIME );
	}

//***********************************************************************************************
//
// Vision functions
//
//***********************************************************************************************

range_t Actor::Range
	(
	Entity *targ
	)

   {
   float r;
   Vector delta;

   delta = centroid - targ->centroid;
	r = delta * delta;
	if ( r < 120 * 120 )
		{
		return RANGE_MELEE;
		}

	if ( r < 500 * 500 )
		{
		return RANGE_NEAR;
		}

	if ( r < 1000 * 1000 )
		{
		return RANGE_MID;
		}

	return RANGE_FAR;
   }

inline qboolean Actor::InFOV
	(
	Vector pos
	)

	{
	Vector delta;
	float	 dot;

	delta = pos - EyePosition();
   if ( !delta.x && !delta.y )
      {
      // special case for straight up and down
      return true;
      }

	// give better vertical vision
	delta.z = 0;

	delta.normalize();
	dot = DotProduct( orientation[ 0 ], delta.vec3() );

	return ( dot > fovdot );
	}

inline qboolean Actor::InFOV
	(
	Entity *ent
	)

	{
	return InFOV( ent->centroid );
	}

inline qboolean Actor::CanSeeFOV
	(
	Entity *ent
	)

	{
	return InFOV( ent ) && CanSeeFrom( worldorigin, ent );
	}

inline qboolean Actor::CanSeeFrom
  	(
	Vector pos,
	Entity *ent
	)

	{
	trace_t trace;
	Vector p;

	p = ent->centroid;

	// Check if he's visible
	trace = G_Trace( pos + eyeposition, vec_zero, vec_zero, p, this, MASK_OPAQUE, "Actor::CanSeeFrom 1" );
	if ( trace.fraction == 1.0 || trace.ent == ent->edict )
		{
		return true;
		}

	// Check if his head is visible
	p.z = ent->absmax.z;
	trace = G_Trace( pos + eyeposition, vec_zero, vec_zero, p, this, MASK_OPAQUE, "Actor::CanSeeFrom 2" );
	if ( trace.fraction == 1.0 || trace.ent == ent->edict )
		{
		return true;
		}

	return false;
	}

qboolean Actor::CanSee
	(
	Entity *ent
	)

	{
	return CanSeeFrom( worldorigin, ent );
	}

int Actor::EnemyCanSeeMeFrom
	(
	Vector pos
	)

	{
	Entity	*ent;
	int		i;
	int		n;
	float		rad;
	Vector	d;
	Vector	p1;
	Vector	p2;
	int		c;

	rad = max( size.x, size.y ) * 1.44 * 0.5;

	c = 0;
	n = enemyList.NumObjects();
	for( i = 1; i <= n; i++ )
		{
		ent = enemyList.ObjectAt( i );
		if ( !ent || ent->deadflag || ( ent->flags & FL_NOTARGET ) )
			{
			continue;
			}

		if ( WithinDistance( ent, vision_distance ) )
			{
			// To check if we're visible, I create a plane that intersects the actor
			// and is perpendicular to the delta vector between the actor and his enemy.
			// I place four points on this plane that "frame" the actor and check if 
			// the enemy can see any of those points.
			d = ent->centroid - pos;
			d.z = 0;
			d.normalize();
			p1.x = -d.y;
			p1.y = d.x;
			p1 *= rad;
			p2 = p1;
			p1.z = mins.z;
			p2.z = maxs.z;

			if ( CanSeeFrom( pos + p1, ent ) )
				{
				c++;
				}
			if ( CanSeeFrom( pos + p2, ent ) )
				{
				c++;
				}
			p1.z = -p1.z;
			p2.z = -p2.z;
			if ( CanSeeFrom( pos - p1, ent ) )
				{
				c++;
				}
			if ( CanSeeFrom( pos - p2, ent ) )
				{
				c++;
				}
			}
		}

	return c;
	}

qboolean Actor::CanSeeEnemyFrom
	(
	Vector pos
	)

	{
	Entity	*ent;
	int		i;
	int		n;

	n = enemyList.NumObjects();
	for( i = 1; i <= n; i++ )
		{
		ent = enemyList.ObjectAt( i );
		if ( !ent || ent->deadflag || ( ent->flags & FL_NOTARGET ) )
			{
			continue;
			}

		if ( WithinDistance( ent, vision_distance ) && CanSeeFrom( pos, ent ) )
			{
			return true;
			}
		}

	return false;
	}

//***********************************************************************************************
//
// Weapon functions
//
//***********************************************************************************************

qboolean Actor::WeaponReady
	(
	void
	)
	
	{
   if ( currentWeapon && currentWeapon->ReadyToFire() )
      {
      return true;
      }
   else if ( !currentWeapon && has_melee )
      {
      return true;
      }

	return false;
	}

void Actor::Attack
	(
	Event *ev
	)

	{
	Vector delta;
	Vector ang;
	Vector ang2;

	if ( ( currentWeapon ) && currentWeapon->ReadyToFire() && currentWeapon->HasAmmo() )
		{
		if ( currentEnemy )
			{
			ang = angles;
			delta = currentEnemy->centroid - GunPosition();
			ang2 = delta.toAngles();
			ang2[ 0 ] = -ang2[ 0 ];
			setAngles( ang2 );
			currentWeapon->Fire();
			setAngles( ang );
			}
		else
			{
			currentWeapon->Fire();
			}
		}
	}

Vector Actor::GunPosition
	(
	void
	)

	{
   vec3_t	trans[ 3 ];
   vec3_t   orient;
   int		groupindex;
   int		tri_num;
	Vector	offset = vec_zero;
	Vector	result;

	// get the gun position of the actor
	if ( !gi.GetBoneInfo( edict->s.modelindex, "gun", &groupindex, &tri_num, orient ) )
		{
		// Gun doesn't have a barrel, just return the default
		return worldorigin + gunoffset;
		}

	gi.GetBoneTransform( edict->s.modelindex, groupindex, tri_num, orient, edict->s.anim,
		edict->s.frame, edict->s.scale, trans, offset.vec3() );

	MatrixTransformVector( offset.vec3(), orientation, result.vec3() );
	result += worldorigin;

	return result;
	}

inline Vector Actor::MyGunAngles
	(
   Vector muzzlepos, 
   qboolean firing
	)
	
	{
	Vector ang;
	Vector dir;


	if ( currentEnemy && firing )
		{
		dir = currentEnemy->centroid - muzzlepos;
		dir.z += ( currentEnemy->absmax.z - currentEnemy->centroid.z ) * 0.75f;
		dir.normalize();

      ang = dir.toAngles();
      ang.x = -ang.x;
      }
   else
      {
	   ang.x = -worldangles.x;
	   ang.y = worldangles.y;
	   ang.z = worldangles.z;
      }

	return ang;
	}


#define MIN_AIM_DISTANCE 400
inline void Actor::GetGunOrientation
	(
   Vector muzzlepos,
	Vector *forward,
	Vector *right,
	Vector *up
	)
	
   {
   Vector ang;
   float  accuracy;
   float	 spread;
   float  invaim;
   float  skl;
   float  enemydistance;

   ang = MyGunAngles( muzzlepos, true );

   if ( currentEnemy )
      {
	   enemydistance = ( currentEnemy->centroid - muzzlepos ).length();
      if ( enemydistance < MIN_AIM_DISTANCE )
         enemydistance = MIN_AIM_DISTANCE;
      }
   else
      {
      enemydistance = MIN_AIM_DISTANCE;
      }

      // 0 is maximum accuracy
   invaim = 1.0f - aim;
   if ( invaim < 0 )
      invaim = 0;
	skl = min( skill->value, 3 );
   if ( skl < 1 )
      skl = 1;
	accuracy = 1 - ( min( skl, 3 ) * 0.18 );
   accuracy *= invaim;
	spread = ( 8 * MIN_AIM_DISTANCE * accuracy ) / enemydistance;
	ang.x += G_CRandom( spread );
	ang.y += G_CRandom( spread );

	ang.AngleVectors( forward, right, up );
	}

qboolean Actor::CanShootFrom
	(
	Vector pos,
	Entity *ent,
	qboolean usecurrentangles
	)

	{
   int      mask;
	Vector	delta;
	Vector	start;
	Vector	end;
	float		len;
	trace_t	trace;
	Vehicle	*v;
	Entity	*t;
   Vector   ang;

	if ( !currentWeapon || !WithinDistance( ent, vision_distance ) )
		{
      if (!currentWeapon && !has_melee )
		   return false;
		}

	if ( usecurrentangles )
		{
   	Vector	dir;

      start = pos + GunPosition() - worldorigin;
//      start = pos + centroid - worldorigin;
		end = ent->centroid;
		end.z += ( ent->absmax.z - ent->centroid.z ) * 0.75f;
		delta = end - start;
      ang = delta.toAngles();
      ang.x = -ang.x;
      ang.y = angles.y;
		len = delta.length();
   	ang.AngleVectors( &dir, NULL, NULL );
      dir *= len;
      end = start + dir;
		}
	else
		{
		start = pos + GunPosition() - worldorigin;
		end = ent->centroid;
		end.z += ( ent->absmax.z - ent->centroid.z ) * 0.75f;
      delta = end - start;
      len = delta.length();
		}

	// check if we're too far away, or too close
   if ( currentWeapon )
      {
	   if ( ( len > attack_range ) || ( len > currentWeapon->GetMaxRange() ) || ( len < currentWeapon->GetMinRange() ) )
		   {
		   return false;
		   }
      mask = MASK_SHOT;
      }
   else
      {
	   if ( ( len > attack_range ) || ( len > melee_range ) )
		   {
		   return false;
		   }
      mask = MASK_PROJECTILE;
      }

	// shoot past the guy we're shooting at
	end += delta * 4;

#if 0
   if ( usecurrentangles )
      {
      G_DebugLine( start, end, 1, 0, 0, 1 );
      }
   else
      {
	   G_DebugLine( start, end, 1, 1, 0, 1 );
      }
#endif

	// Check if he's visible
	trace = G_Trace( start, vec_zero, vec_zero, end, this, mask, "Actor::CanShootFrom" );
	if ( trace.startsolid )
		{
		return false;
		}

	// If we hit the guy we wanted, then shoot
	if ( trace.ent == ent->edict )
		{
		return true;
		}

	// if we hit a vehicle, check if the driver is someone we want to hit
	t = trace.ent->entity;
	if ( t && t->isSubclassOf( Vehicle ) )
		{
		v = ( Vehicle * )t;
		if ( ( v->Driver() == ent ) || IsEnemy( v->Driver() ) )
			{
			return true;
			}
		return false;
		}

	// If we hit someone else we don't like, then shoot
	if ( IsEnemy( t ) )
		{
		return true;
		}

	// if we hit something breakable, check if shooting it will
   // let us shoot someone.
	if ( t->isSubclassOf( Shatter ) || 
		t->isSubclassOf( Object ) ||
		t->isSubclassOf( DamageThreshold ) ||
		t->isSubclassOf( ScriptModel ) )
		{
      trace = G_Trace( Vector( trace.endpos ), vec_zero, vec_zero, end, t, mask, "Actor::CanShootFrom 2" );
	   if ( trace.startsolid )
		   {
		   return false;
		   }

	   // If we hit the guy we wanted, then shoot
	   if ( trace.ent == ent->edict )
		   {
		   return true;
		   }

	   // If we hit someone else we don't like, then shoot
	   if ( IsEnemy( trace.ent->entity ) )
		   {
		   return true;
		   }

      // Forget it then
      return false;
		}

	return false;
	}

qboolean Actor::CanShoot
	(
	Entity *ent,
	qboolean usecurrentangles
	)

	{
	return CanShootFrom( worldorigin, ent, usecurrentangles );
	}

float Actor::AttackRange
	(
   void
	)

	{
	if ( !currentWeapon && !has_melee )
		{
		return 0;
		}

   if ( currentWeapon )
      {
	   return ( currentWeapon->GetMaxRange() );
      }
   else
      {
      return ( melee_range );
      }
	}

float Actor::MinimumAttackRange
	(
   void
	)

	{
   float range;
   float maxrange;

	if ( !currentWeapon && !has_melee )
		{
		return 100;
		}

   range = melee_range * 0.75f;
   maxrange = melee_range;

   if ( currentWeapon )
      {
	   range = currentWeapon->GetMinRange();
      if ( !range && melee_range )
         range = melee_range * 0.75f;
	   maxrange = currentWeapon->GetMaxRange();
      }

   if ( range > maxrange )
      range = maxrange;

   return range;
	}

qboolean Actor::HasWeapon
	(
   void
	)
   {
   return ( currentWeapon != NULL );
   }

//***********************************************************************************************
//
// Actor type script commands
//
//***********************************************************************************************

void Actor::FriendEvent
	(
	Event *ev
	)

	{
	actortype = IS_FRIEND;
	}

void Actor::CivilianEvent
	(
	Event *ev
	)

	{
	actortype = IS_CIVILIAN;
	}

void Actor::EnemyEvent
	(
	Event *ev
	)

	{
	actortype = IS_ENEMY;
	}

void Actor::InanimateEvent
   (
   Event *ev
   )

   {
   actortype = IS_INANIMATE;
   //
   // clear the monster flag so triggers are not triggered
   //
	edict->svflags	&= ~SVF_MONSTER;
   //
   // don't make them move
   //
   setMoveType( MOVETYPE_NONE );
   // 
   // don't make it bleed
   //
   flags &= ~FL_BLOOD;
   // 
   // don't make it gib
   //
   flags &= ~FL_DIE_GIBS;
   }
   
void Actor::MonsterEvent
	(
	Event *ev
	)

	{
	actortype = IS_MONSTER;
	}

void Actor::AnimalEvent
	(
	Event *ev
	)

	{
	actortype = IS_ANIMAL;
	}

//***********************************************************************************************
//
// Enemy management
//
//***********************************************************************************************

qboolean Actor::HasEnemies
	(
	void
	)

	{
	return ( enemyList.NumObjects() > 0 );
	}

qboolean Actor::IsEnemy
	(
	Entity *ent
	)

	{
	return enemyList.ObjectInList( EntityPtr( ent ) ) && seenEnemy;
	}

void Actor::MakeEnemy
	(
	Entity *ent,
   qboolean force
	)

	{
   // don't get mad at things that can't be hurt or the world
	if ( 
         ent && 
         ( ent != world ) && 
         ( ent != this ) && 
         !( ent->flags & FL_NOTARGET ) &&
         ( ent->takedamage != DAMAGE_NO )
      )
		{
      if ( !enemyList.ObjectInList( EntityPtr( ent ) ) )
         {
		   enemyList.AddObject( EntityPtr( ent ) );
         }

		if ( !currentEnemy && !seenEnemy )
			{
			currentEnemy = ent;
			if ( DoAction( "sightenemy", force ) )
				{
				seenEnemy = true;
            Chatter( "snd_sightenemy", 5 );
				}
			else
				{
				currentEnemy = NULL;
				}
			}
		}
	}

void Actor::ClearEnemies
   (
   void
   )

   {
	currentEnemy = NULL;
   seenEnemy = false;
   enemyList.ClearObjectList();
   }


qboolean Actor::Likes
	(
	Entity *ent
	)

	{
	Actor *act;

	if ( ent->isClient() )
		{
		return ( actortype == IS_FRIEND );
		}
   else if ( actortype == IS_MONSTER )
      {
      // monsters don't like anyone, but they don't particular hate everyone
      return false;
      }
	else if ( ent->isSubclassOf( Actor ) )
		{
		act = ( Actor * )ent;
		return ( act->actortype == actortype );
		}

	return false;
	}

qboolean Actor::Hates
	(
	Entity *ent
	)

	{
	Actor *act;

   assert( ent );
   if ( !ent )
      {
      return false;
      }

	if ( ent->isClient() )
		{
      if ( ent->flags & FL_SP_MUTANT )
         {
         if ( actortype == IS_ENEMY )
            return false;
         else
            return true;
         }
      else
         {
		   return ( actortype != IS_CIVILIAN ) && ( actortype != IS_FRIEND );
         }
		}
	else if ( ent->isSubclassOf( Actor ) && ( actortype != IS_INANIMATE ) )
		{
		act = ( Actor * )ent;
//      if ( act->actortype == IS_INANIMATE )
//         {
//         // heh... Mutants hate inanimate objects. :)
//         return ( actortype == IS_MONSTER );
//         }
      if ( ( act->actortype <= IS_ENEMY ) && ( actortype <= IS_ENEMY ) )
			{
			return false;
			}
		if ( ( act->actortype == IS_FRIEND ) && ( actortype <= IS_ENEMY ) )
			{
			return true;
			}
		if ( ( act->actortype <= IS_ENEMY ) && ( actortype == IS_FRIEND ) )
			{
			return true;
			}
		}

	return false;
	}

//***********************************************************************************************
//
// Targeting functions
//
//***********************************************************************************************

qboolean Actor::GetVisibleTargets
	(
	void
	)

	{
	Sentient	*ent;
	Vector	delta;
	int		i;
	int		n;

	targetList.ClearObjectList();
	nearbyList.ClearObjectList();

	n = SentientList.NumObjects();
	for( i = 1; i <= n; i++ )
		{
		ent = SentientList.ObjectAt( i );

		//if ( ( ent == this ) || ent->deadflag || ( ent->flags & FL_NOTARGET ) || !Hates( ent ) )
		if ( ( ent == this ) || ( ent->flags & FL_NOTARGET ) || ent->hidden() )
			{
			continue;
			}

		if ( WithinDistance( ent, vision_distance ) && CanSeeFOV( ent ) )
			{
			targetList.AddObject( EntityPtr( ent ) );
			if ( WithinDistance( ent, 96 ) )
				{
				nearbyList.AddObject( EntityPtr( ent ) );
				}
			}
		}

	return ( targetList.NumObjects() > 0 );
	}

void Actor::TargetEnemies
	(
	Event *ev
	)

	{
	int i;
	int n;
	Entity *ent;
	Entity *newtarget;
	Actor *act;

   if ( actortype == IS_INANIMATE )
      {
      // inanimate objects don't need to worry about this kind of thing
      return;
      }

   if ( enemyList.NumObjects() >= 1 )
      {
      // don't target new enemies as much while we've already got an enemy
      PostEvent( EV_Actor_TargetEnemies, 5 );
      }
   else
      {
      PostEvent( EV_Actor_TargetEnemies, 1 );
      }

	if ( hidden() )
		{
		// don't target while hidden (for cinematic characters)
		//FIXME
		// probably should have a start/stop function
		return;
		}

	if ( GetVisibleTargets() )
		{
		n = targetList.NumObjects();
		for( i = 1; i <= n; i++ )
			{
			ent = targetList.ObjectAt( i );
			if ( ent )
				{
            if ( ent->flags & (FL_CLOAK|FL_STEALTH) )
               continue;

				if ( !ent->deadflag && Hates( ent ) && !IsEnemy( ent ) )
					{
					MakeEnemy( ent );
					}
				else if ( ent->isSubclassOf( Actor ) && Likes( ent ) )
					{
					act = ( Actor * )ent;
					if ( act->currentEnemy && Hates( act->currentEnemy ) && !IsEnemy( act->currentEnemy ) )
						{
						MakeEnemy( act->currentEnemy );
                  if ( act->deadflag )
                     {
                     //
                     // we have passed on the post mortem message of our death, so let's clear it
                     //
                     act->ClearEnemies();
                     }
						}
					}
				}
			}
		}

	newtarget = BestTarget();
	if ( newtarget && ( newtarget != currentEnemy ) )
		{
      seenEnemy = false;
		currentEnemy = newtarget;
		if ( DoAction( "sightenemy" ) )
			{
			seenEnemy = true;
   		Chatter( "snd_sightenemy", 5 );
			}
		else
			{
			currentEnemy = NULL;
			}
		}
	}

Entity *Actor::BestTarget
	(
	void
	)

   {
	int i;
	int n;
	Entity *ent;
	Entity *bestent;
	float bestscore;
	float score;

	bestscore = 8192 * 8192 * 20;
	n = enemyList.NumObjects();
   if ( n == 1 )
      {
      // don't waste our time when we only have one enemy
      return enemyList.ObjectAt( 1 );
      }

	bestent = NULL;
	for( i = 1; i <= n; i++ )
		{
		ent = enemyList.ObjectAt( i );
		if ( !ent || ent->deadflag )
			{
			enemyList.RemoveObjectAt( i );
			i--;
			n--;
			continue;
			}

      score = Range( ent ) + 1;
		if ( ent->health < WEAK_HEALTH )
			{
			// Try to kill off really weak enemies
			score *= WEAK_WEIGHT;
			}
		
		if ( ent->health > health )
			{
			score *= STRONGER_WEIGHT;
			}

		if ( CanSeeFOV( ent ) )
			{
			// We're more interested in guys we can see
			score *= VISIBLE_WEIGHT;
			}

		if ( i == n )
			{
			// Favor the latest enemy
			score *= NEWENEMY_WEIGHT;
			}

		if ( score < bestscore )
			{
			bestscore = score;
			bestent = ent;
			}
		}

	return bestent;
   }

Sentient *Actor::NearFriend
	(
	void
	)

	{
	int i;
	int num;
	Entity *ent;

	num = nearbyList.NumObjects();
	for( i = 1; i < num; i++ )
		{
		ent = nearbyList.ObjectAt( i );
		if ( Likes( ent ) )
			{
			return ( Sentient * )ent;
			}
		}

	return NULL;
	}

qboolean Actor::CloseToEnemy
	(
	Vector pos,
	float howclose
	)
	
	{
	Entity	*ent;
	int		i;
	int		n;

	n = enemyList.NumObjects();
	for( i = 1; i <= n; i++ )
		{
		ent = enemyList.ObjectAt( i );
		if ( !ent || ent->deadflag || ( ent->flags & FL_NOTARGET ) )
			{
			continue;
			}

		if ( WithinDistance( ent, howclose ) )
			{
			return true;
			}
		}

	return false;
	}

void Actor::EyeOffset
	(
	Event *ev
	)
	{
   eyeposition -= eyeoffset;
   eyeoffset = ev->GetVector( 1 );
   eyeposition += eyeoffset;
   }

//***********************************************************************************************
//
// State control functions
//
//***********************************************************************************************

void Actor::EnableState
	(
	str action
	)

	{
	StateInfo *ptr;

	ptr = GetState( action );
	if ( ptr )
		{
		ptr->ignore = false;
		}
	}

void Actor::DisableState
	(
	str action
	)

	{
	StateInfo *ptr;

	ptr = GetState( action );
	if ( ptr )
		{
		ptr->ignore = true;
		}
	}

StateInfo *Actor::SetResponse
	(
	str action,
	str response,
	qboolean ignore
	)

	{
	StateInfo *ptr;

	ptr = GetState( action );
	if ( !ptr )
		{
		ptr = new StateInfo;

		actionList.AddObject( ptr );
		ptr->action = action;
		}

	ptr->response = response;
	ptr->ignore = ignore;

	return ptr;
	}

const char *Actor::GetResponse
	(
	str action,
   qboolean force
	)

	{
	StateInfo *ptr;

	ptr = GetState( action );
	if ( ptr && ( force || !ptr->ignore ) )
		{
		return ptr->response.c_str();
		}

	return "";
	}

StateInfo *Actor::GetState
	(
	str action
	)

	{
	int i;
	int n;
	StateInfo *ptr;

	n = actionList.NumObjects();
	for( i = 1; i <= n; i++ )
		{
		ptr = actionList.ObjectAt( i );
		if ( ptr->action == action )
			{
			return ptr;
			}
		}

	return NULL;
	}

//***********************************************************************************************
//
// State stack management
//
//***********************************************************************************************

void Actor::ClearStateStack
	(
	void
	)

	{
	ActorState *state;
	int n;
	int i;

	while( !stateStack.Empty() )
		{
		state = stateStack.Pop();

		if ( state->animDoneEvent )
			{
			delete state->animDoneEvent;
			}

		// delete the old action/response list
		n = state->actionList.NumObjects();
		for( i = n; i >= 1; i-- )
			{
			delete state->actionList.ObjectAt( i );
			}
		state->actionList.ClearObjectList();

		if ( state->behavior )
			{
			delete state->behavior;
			}

		if ( state->path )
			{
			delete state->path;
			}
		
		delete state;
		}

	numonstack = 0;
	}

qboolean Actor::PopState
	(
	void
	)

	{
	ActorState *newstate;
	int n;
	int i;

#ifdef DEBUG_PRINT
	gi.dprintf( "%d Pop:", numonstack );
#endif
	if ( !stateStack.Empty() )
		{
		newstate = stateStack.Pop();
		numonstack--;

		state = newstate->name;

#ifdef DEBUG_PRINT
		gi.dprintf( "state '%s' anim '%s'", state.c_str(), newstate->anim.c_str() );
#endif
		if ( newstate->anim.length() )
			{
			SetAnim( newstate->anim, newstate->animDoneEvent );
			ChangeAnim();
			}

		SetPath( newstate->path );

#ifdef DEBUG_PRINT
		if ( newstate->behavior )
			{
			gi.dprintf( "%s", newstate->behavior->getClassname() );
			}
		else
			{
			gi.dprintf( "NULL behavior" );
			}
		gi.dprintf( "\n" );
#endif

		// NULL out our current thread so that EndBehavior doesn't
		// signal the thread that the behavior ended.
		thread = NULL;
		EndBehavior();

		assert( !behavior );

		// Set the thread after ending the old behavior, but before the new behavior
		if ( newstate->thread != -1 )
			{
			thread = Director.GetThread( newstate->thread );

			// Since PopState is called from the thread, we don't need to tell the thread to continue processing.
			// In fact, depending upon the state of the thread when we pushed it onto the stack, we may not want
			// the thread to continue processing (for example, if the last command was a waitFor).  Just restoring the
			// position here will tell the thread to continue executing or wait for an event to occur.
			// If we ever call PopState from outside of a thread, we MUST check to see if the thread should
			// continue execution.
			//FIXME
			// This is probably an actorthread that was removed
			// ADDENDUM: actorThread is now only removed once.  Thread should never be NULL.
			if ( thread )
				{
				thread->Restore( &newstate->marker );
				}
			}
		else
			{
			thread = NULL;
			}

		// delete the old action/response list
		n = actionList.NumObjects();
		for( i = n; i >= 1; i-- )
			{
			delete actionList.ObjectAt( i );
			}
		actionList.ClearObjectList();
		
		// Copy the new action/response list
		n = newstate->actionList.NumObjects();
		for( i = 1; i <= n; i++ )
			{
			actionList.AddObject( newstate->actionList.ObjectAt( i ) );
			}

		assert( !behavior );

		SetBehavior( newstate->behavior, NULL, thread );

		delete newstate;
		}
	else
		{
#ifdef DEBUG_PRINT
		gi.dprintf( "\n" );
#endif
		EndBehavior();

		return false;
		}

	return true;
	}

void Actor::PushState
	(
	const char *newstate,
	ScriptThread *newthread,
	ThreadMarker *marker
	)

	{
	ActorState *oldstate;
	int i;
	int n;

	oldstate = new ActorState;

	// push the old state
#ifdef DEBUG_PRINT
	gi.dprintf( "%d : Pushing old state %s\n", numonstack, state.c_str() );
	if ( behavior )
		{
		gi.dprintf( "old behavior %s\n", behavior->getClassname() );
		}
	else
		{
		gi.dprintf( "old behavior NULL\n" );
		}
	gi.dprintf( "new state %s\n", newstate );
#endif

	oldstate->name = state;
	oldstate->anim = animname;
	oldstate->animDoneEvent = animDoneEvent;
	animDoneEvent = NULL;

	oldstate->path = path;

	oldstate->behavior = behavior;

	// newthread must always be the old thread
	assert( newthread );
	oldstate->thread = newthread->ThreadNum();
	assert( marker );
	oldstate->marker = *marker;

	// Copy the action/response list
	n = actionList.NumObjects();
	for( i = 1; i <= n; i++ )
		{
		StateInfo *ptr;
		StateInfo *newobj;

		ptr = actionList.ObjectAt( i );
		newobj = new StateInfo;
		newobj->action		= ptr->action;
		newobj->response	= ptr->response;
		newobj->ignore		= ptr->ignore;
		oldstate->actionList.AddObject( newobj );
		}

	numonstack++;
	stateStack.Push( oldstate );

	// Any SetBehavior following this will delete this behavior, so null it out so that it doesn't happen
	if ( behavior )
		{
		behavior->End( *this );
		behavior = NULL;
		}

	state = newstate;
	thread = newthread;
	}

//***********************************************************************************************
//
// State control script commands
//
//***********************************************************************************************

void Actor::DefineStateEvent
	(
	Event *ev
	)

	{
	const char		*action;
	str				response;
	ScriptThread	*thread;
	str				script;
	int				len;

	action = ev->GetString( 1 );
	response = ev->GetString( 2 );

	// check if we have a filename in the label
	if ( !strstr( response.c_str(), "::" ) )
		{
		thread = ev->GetThread();
		if ( thread )
			{
			// add filename to the label so that if we jump to another script, our labels are still valid
			response = str( thread->Filename() ) + "::" + response;
			}
		}
	else
		{
		// prepend our debug directory name
		script = ai_actorscript->string;
		len = script.length();

		// if we have a directory, make sure that it ends with a '/' or a '\'
		if ( ( len > 0 ) && ( script[ len - 1 ] != '/' ) && ( script[ len - 1 ] != '\\' ) )
			{
			script += "/";
			}

		response = script + response;
		}

	SetResponse( action, response );
	}

void Actor::CopyStateEvent
	(
	Event *ev
	)

	{
	str			action1;
	str			action2;
	str			response;
	StateInfo	*ptr;

	action1 = ev->GetString( 1 );
	action2 = ev->GetString( 2 );

	ptr = GetState( action2 );
	if ( ptr )
		{
		response = ptr->response;
		}

	SetResponse( action1, response );
	}

void Actor::IgnoreAllEvent
	(
	Event *ev
	)

	{
	int i;
	int n;

	n = actionList.NumObjects();
	for( i = 1; i <= n; i++ )
		{
		actionList.ObjectAt( i )->ignore = true;
		}
	}

void Actor::IgnoreEvent
	(
	Event *ev 
	)

	{
	int i;
	int n;

	n = ev->NumArgs();
	for( i = 1; i <= n; i++ )
		{
		DisableState( ev->GetString( i ) );
		}
	}

void Actor::RespondToAllEvent
	(
	Event *ev
	)

	{
	int i;
	int n;

	n = actionList.NumObjects();
	for( i = 1; i <= n; i++ )
		{
		actionList.ObjectAt( i )->ignore = false;
		}
	}

void Actor::RespondToEvent
	(
	Event *ev
	)

	{
	int i;
	int n;

	n = ev->NumArgs();
	for( i = 1; i <= n; i++ )
		{
		EnableState( ev->GetString( i ) );
		}
	}

void Actor::ClearStateEvent
	(
	Event *ev
	)

	{
	ClearStateStack();
	}

void Actor::StateDoneEvent
	(
	Event *ev
	)

	{
	assert( actorthread == ev->GetThread() );

	if ( !deadflag || ( actortype == IS_INANIMATE ) )
		{
		// if we're not dead, pop off the previous state
		PopState();
		}
	else
		{
		// if we're dead, kill off all the previous states
		ClearStateStack();

		// kill off the thread
		actorthread->ProcessEvent( EV_ScriptThread_End );
		actorthread = NULL;
		}
	}

void Actor::SetStateEvent
	(
	Event *ev
	)

	{
	str response;
	str name;
	ThreadMarker marker;
	StateInfo *ptr;

	if ( ( deadflag == DEAD_DEAD ) && ( actortype != IS_INANIMATE ) )
		{
		return;
		}

	name = ev->GetString( 1 );

	// Don't check ignore flag
	ptr = GetState( name );
	if ( ptr )
		{
		response = ptr->response;
		}

#ifdef DEBUG_PRINT
	gi.dprintf( "%d : %d : Action: %s - %s\n", 
		actorthread->ThreadNum(), ev->GetThread()->ThreadNum(),
		name.c_str(), response.c_str() );
#endif

	// check the existance of the actor's thread to prevent a crash
	if ( !actorthread )
   	{
		return;
	   }

	actorthread->Mark( &marker );
	if ( response != "" && actorthread->Goto( response.c_str() ) )
		{
		PushState( name.c_str(), actorthread, &marker );
		SetAnim( "idle" );
		animname = "idle";
		SetVariable( "state", name.c_str() );
		ProcessScript( actorthread );
		}
	else
		{
		ev->Error( "Could not find label '%s'", response.c_str() );
      actorthread->Goto( response.c_str() );
		}
	}

void Actor::CanStrafeEvent
	(
	Event *ev
	)

	{
   checkStrafe = true;
   }

void Actor::NoStrafeEvent
	(
	Event *ev
	)

	{
   checkStrafe = false;
   }

//***********************************************************************************************
//
// Thread management
//
//***********************************************************************************************

void Actor::SetupThread
	(
	void
	)

	{
	str script;
	int len;
   Event *event;

	// we should never have a thread at this point
	assert( !actorthread );

	// prepend our debug director name
	script = ai_actorscript->string;
	len = script.length();

	// if we have a directory, make sure that it ends with a '/' or a '\'
	if ( ( len > 0 ) && ( script[ len - 1 ] != '/' ) && ( script[ len - 1 ] != '\\' ) )
		{
		script += "/";
		}
	script += actorscript;
	actorthread = Director.CreateThread( script.c_str(), MODEL_SCRIPT );

	if ( actorthread )
		{
      // setup thread variables
      SetVariable( "attackmode", attackmode );

		if ( actorstart.length() )
			{
			if ( !actorthread->Goto( actorstart.c_str() ) )
				{
				gi.dprintf( "Label '%s' not found in %s.", actorstart.c_str(), script.c_str() );
				}
			}

		ProcessScript( actorthread );
		}

   assert( actorthread );
   if ( !actorthread )
      {
      // not having a script is bad
      gi.dprintf( "Unable to start actor script '%s'.  Killing actor '%s'(%d).\n",
         script.c_str(), targetname.c_str(), entnum );

      // just kill him
		event = new Event( EV_Killed );
		event->AddEntity( this );
		event->AddInteger( 0 );
		event->AddEntity( this );
      event->AddString( "all" );
		ProcessEvent( event );

      return;
      }
	}

qboolean Actor::DoAction
	(
	str name,
   qboolean force
	)

	{
	str response;
	ThreadMarker marker;

   if ( !actorthread )
      {
      return false;
      }

	if ( ( deadflag == DEAD_DEAD ) && ( actortype != IS_INANIMATE ) )
		{
		return false;
		}

	response = GetResponse( name, force );

#ifdef DEBUG_PRINT
	gi.dprintf( "Action: %s - %s\n", name.c_str(), response.c_str() );
#endif

	actorthread->Mark( &marker );
	if ( response != "" && actorthread->Goto( response.c_str() ) )
		{
		PushState( name.c_str(), actorthread, &marker );
		SetAnim( "idle" );
		animname = "idle";
		SetVariable( "state", name.c_str() );
		ProcessScript( actorthread );
		return true;
		}

	return false;
	}

qboolean Actor::ForceAction
	(
	str name
	)

	{
   return DoAction( name, true );
	}

void Actor::ProcessScript
	(
	ScriptThread *thread,
   Event *ev
	)

	{
	thread->Vars()->SetVariable( "self", this );
	thread->Vars()->SetVariable( "origin", worldorigin );
	thread->Vars()->SetVariable( "yaw", worldangles.y );
	thread->Vars()->SetVariable( "health", health );
	thread->Vars()->SetVariable( "startpos", startpos );
	thread->Vars()->SetVariable( "shots_per_attack", shots_per_attack );
   //
   // see if the enemy lost his weapon 
   // i.e. it was shot out of his hands
   //
   if ( currentWeapon )
      {
      thread->Vars()->SetVariable( "has_weapon", 1 );
      }
   else
      {
      thread->Vars()->SetVariable( "has_weapon", 0 );
      }


	if ( currentEnemy )
		{
		thread->Vars()->SetVariable( "enemy", currentEnemy );
		}
	else
		{
		thread->Vars()->SetVariable( "enemy", "" );
		}

   if ( ev )
      {
	   thread->ProcessEvent( ev );
      }
   else
      {
      thread->ProcessEvent( EV_ScriptThread_Execute );
      }
	}

void Actor::StartMove
	(
	Event *ev
	)

	{
	if ( deadflag )
		{
		return;
		}

//	thread = ev->GetThread();
	}

inline ScriptVariable *Actor::SetVariable
   (
   const char *name,
   float value
   )

   {
   if ( actorthread )
      {
      return actorthread->Vars()->SetVariable( name, value );
      }

   return NULL;
   }

inline ScriptVariable *Actor::SetVariable
   (
   const char *name,
   int value
   )

   {
   if ( actorthread )
      {
      return actorthread->Vars()->SetVariable( name, value );
      }

   return NULL;
   }

inline ScriptVariable *Actor::SetVariable
   (
   const char *name,
   const char *text
   )

   {
   if ( actorthread )
      {
      return actorthread->Vars()->SetVariable( name, text );
      }

   return NULL;
   }

inline ScriptVariable *Actor::SetVariable
   (
   const char *name,
   str &text
   )

   {
   if ( actorthread )
      {
      return actorthread->Vars()->SetVariable( name, text.c_str() );
      }
   
   return NULL;
   }

inline ScriptVariable *Actor::SetVariable
   (
   const char *name,
   Entity *ent
   )

   {
   if ( actorthread )
      {
      return actorthread->Vars()->SetVariable( name, ent );
      }

   return NULL;
   }

inline ScriptVariable *Actor::SetVariable
   (
   const char *name,
   Vector &vec
   )

   {
   if ( actorthread )
      {
      return actorthread->Vars()->SetVariable( name, vec );
      }

   return NULL;
   }

//***********************************************************************************************
//
// Thread based script commands
//
//***********************************************************************************************

void Actor::SetScript
	(
	Event *ev
	)

	{
	str script;
	str label;
	int len;

	actorscript = ev->GetString( 1 );

	// gotta start the thread again!
	if ( actorthread )
		{
		// prepend our debug directory name
		script = ai_actorscript->string;
		len = script.length();

		// if we have a directory, make sure that it ends with a '/' or a '\'
		if ( ( len > 0 ) && ( script[ len - 1 ] != '/' ) && ( script[ len - 1 ] != '\\' ) )
			{
			script += "/";
			}

		script += actorscript;
		if ( !actorthread->SetScript( script.c_str() ) )
			{
			ev->Error( "Script '%s' not found", script.c_str() );
			}
		else
			{
         // setup thread variables
         SetVariable( "attackmode", attackmode );

			ProcessScript( actorthread );
			}
		}
	}

void Actor::SetThread
	(
	Event *ev
	)

	{
	ScriptThread *thread;

	if ( ( deadflag == DEAD_DEAD ) && ( actortype != IS_INANIMATE ) )
		{
		return;
		}

	thread = ev->GetThread();
	actorstart = ev->GetString( 1 );

	// get the name of the script
	if ( thread )
		{
		actorstart = str( thread->Filename() ) + "::" + actorstart;
		}

	// we may be getting this command from the .def file, so the thread may not have started yet
	if ( actorthread && actorstart.length() )
		{
      // setup thread variables
      SetVariable( "attackmode", attackmode );

		if ( actorthread->Goto( actorstart.c_str() ) )
			{
			ProcessScript( actorthread );
			}
		else
			{
			ev->Error( "Label '%s' not found.  Couldn't change thread.", actorstart.c_str() );
			}
		}
	}

//***********************************************************************************************
//
// Behavior management
//
//***********************************************************************************************

void Actor::EndBehavior
	(
	void
	)

	{
	ScriptThread *t;
	Event *event;

	if ( behavior )
		{
		behavior->End( *this );
		delete behavior;
		behavior = NULL;

		if ( thread )
			{
			t = thread;
			thread = NULL;
			event = new Event( EV_MoveDone );
			event->AddEntity( this );
#if 0
         if ( t == actorthread )
            {
            ProcessScript( actorthread, event );
            }
         else
            {
			   t->ProcessEvent( event );
            }
#else
         ProcessScript( actorthread, event );
         if ( t != actorthread )
            {
			   event = new Event( EV_MoveDone );
			   event->AddEntity( this );
			   t->ProcessEvent( event );
            }
#endif
         }
		}
	}

void Actor::SetBehaviorEvent
	(
	Event *ev
	)

	{
	ClassDef *cls;
	ScriptThread *thread;
	Event *e;
	str name;
	int i;
	int n;

	name = ev->GetString( 1 );
	if ( !checkInheritance( &Behavior::ClassInfo, name.c_str() ) )
		{
		ev->Error( "%s is not a valid behavior\n", name.c_str() );
		return;
		}

	thread = ev->GetThread();

	e = new Event( EV_Behavior_Args );
	e->SetSource( EV_FROM_SCRIPT );
	e->SetThread( thread );
	e->SetLineNumber( ev->GetLineNumber() );

	e->AddEntity( this );

	n = ev->NumArgs();
	for( i = 2; i <= n; i++ )
		{
		e->AddToken( ev->GetToken( i ) );
		}

	cls = getClass( name.c_str() );
	SetBehavior( ( Behavior * )cls->newInstance(), e, thread );
	}

void Actor::SetBehavior
	(
	Behavior *newbehavior,
	Event *startevent,
	ScriptThread *newthread
	)

	{
	if ( ( deadflag ) && ( actortype != IS_INANIMATE ) )
		{
		return;
		}

	// End any previous behavior, but don't call EV_MoveDone if we're using the same thread,
	// or we'll end THIS behavior
	if ( thread == newthread )
		{
		thread = NULL;
		}
	EndBehavior();

	behavior = newbehavior;
	if ( behavior )
		{
      if ( actortype == IS_INANIMATE )
		   {
         // think while we have a behavior
         flags |= FL_PRETHINK;
		   }

#ifdef DEBUG_PRINT
		gi.dprintf( "SetBehavior %s\n", behavior->getClassname() );
#endif
		if ( startevent )
			{
			behavior->ProcessEvent( startevent );
			}
		currentBehavior = behavior->getClassname();
		behavior->Begin( *this );
		thread = newthread;
		}
	}

void Actor::FinishedBehavior
	(
	Event *ev
	)

	{
	EndBehavior();
	}

void Actor::NotifyBehavior
	(
	Event *ev
	)

	{
	if ( behavior )
		{
		behavior->ProcessEvent( EV_Behavior_AnimDone );
		}
	}

void Actor::ForwardBehaviorEvent
	(
	Event *ev
	)

	{
	ScriptThread *thread;
	Event *e;
	str name;
	int i;
	int n;

	name = ev->GetString( 1 );

	thread = ev->GetThread();
	e = new Event( name );
	e->SetSource( EV_FROM_SCRIPT );
	e->SetThread( thread );
	e->SetLineNumber( ev->GetLineNumber() );

   // always add who got this event
   e->AddEntity( this );
	n = ev->NumArgs();
	for( i = 2; i <= n; i++ )
		{
		e->AddToken( ev->GetToken( i ) );
		}

	if ( behavior )
      behavior->ProcessEvent( e );
   else
      warning( "ForwardBehaviorEvent", "no behavior defined" );
	}

//***********************************************************************************************
//
// Path and node management
//
//***********************************************************************************************

void Actor::SetPath
	(
	Path *newpath
	)

	{
	if ( path && ( path != newpath ) )
		{
		delete path;
		}
	path = newpath;
	}

void Actor::ReserveNodeEvent
	(
	Event *ev
	)

	{
	PathNode *node;
	Vector pos;

	pos = ev->GetVector( 1 );
	node = PathManager.NearestNode( pos, this );

	if ( node && ( !node->entnum || ( node->entnum == entnum ) || ( node->occupiedTime < level.time ) ) )
		{
		// Mark node as occupied for a short time
		node->occupiedTime = level.time + ev->GetFloat( 2 );
		node->entnum = entnum;
		}
	}

void Actor::ReleaseNodeEvent
	(
	Event *ev
	)

	{
	PathNode *node;
	Vector pos;

	pos = ev->GetVector( 1 );
	node = PathManager.NearestNode( pos, this );

	if ( node && ( node->entnum == entnum ) )
		{
		node->occupiedTime = 0;
		node->entnum = 0;
		}
	}

//***********************************************************************************************
//
// Animation control functions
//
//***********************************************************************************************

void Actor::ChangeAnim
	(
	void
	)

	{
	float time;
	Vector totalmove;

	if ( newanimnum == -1 )
		{
		return;
		}

	// If we're changing to the same anim, don't restart the animation
	if ( animating && newanimnum == edict->s.anim )
		{
		if ( animDoneEvent )
			{
			delete animDoneEvent;
			}

		animDoneEvent = newanimevent;
		}
	else
		{
		StopAnimating();

		animname = newanim;

		time = gi.Anim_Time( edict->s.modelindex, newanimnum );
		gi.Anim_Delta( edict->s.modelindex, newanimnum, totalmove.vec3() );

		totalmove[ 1 ] = -totalmove[ 1 ];
      totalmove *= edict->s.scale;
		totallen = totalmove.length();

		// always have a valid move direction
		if ( totallen > 0.01 )
			{
			movespeed = totallen / time;
			animdir = totalmove * ( 1 / totallen );
			}
		else
			{
         if ( forwardspeed )
            {
	   	   movespeed = forwardspeed;
            }
         else
            {
			   movespeed = 1;
            }
			animdir = Vector( 1, 0, 0 );
			}

		MatrixTransformVector( animdir.vec3(), orientation, movedir.vec3() );
		movevelocity = movedir * movespeed;

		NextAnim( newanimnum );
		animDoneEvent = newanimevent;
		StartAnimating();
		}

	// clear the new anim variables
	newanimnum = -1;
	newanim = "";
	newanimevent = NULL;
	}

qboolean Actor::SetAnim
	(
	str anim,
	Event *ev
	)

   {
   int num;

	// FIXME
	// HACK to make actors use alert when fighting instead of idle
	if ( hasalert && currentEnemy && ( anim == "idle" ) )
		{
		anim = "alert";
		}

	num = gi.Anim_Random( edict->s.modelindex, anim.c_str() );
	if ( num != -1 )
		{
		newanim = anim;
		newanimnum = num;
		newanimevent = ev;

      if ( actortype == IS_INANIMATE )
         {
         // inanimate objects change anims immediately
         ChangeAnim();
         }

		return true;
		}

	// kill the event
	if ( ev )
		{
		delete ev;
		}

	return false;
	}

qboolean Actor::SetAnim
	(
	str anim,
	Event &ev
	)

	{
   Event * event;

   event = new Event( ev );
   return SetAnim( anim, event );
	}

void Actor::Anim
	(
	Event *ev
	)

	{
	Event *e;

	if ( ( deadflag ) && ( actortype != IS_INANIMATE ) )
		{
		return;
		}

	e = new Event( EV_Behavior_Args );
	e->SetSource( EV_FROM_SCRIPT );
	e->SetThread( ev->GetThread() );
	e->SetLineNumber( ev->GetLineNumber() );

	e->AddEntity( this );
	e->AddToken( ev->GetToken( 1 ) );

	SetBehavior( new PlayAnim, e, ev->GetThread() );
	}

//***********************************************************************************************
//
// Script commands
//
//***********************************************************************************************

void Actor::CrouchSize
	(
	Event *ev
	)

	{
	crouchsize_min = ev->GetVector( 1 );
	crouchsize_max = ev->GetVector( 2 );
	}

void Actor::SetFov
	(
	Event *ev
	)

	{
	fov = ev->GetFloat( 1 );
	fovdot = cos( fov * 0.5 * M_PI / 180.0 );
	}

void Actor::SetVisionDistance
   (
   Event *ev
   )
   
   {
   vision_distance = ev->GetFloat( 1 );
   }

void Actor::LookAt
	(
	Event *ev
	)

	{
	Entity *ent;
	TurnTo *turnTo;

	if ( ( deadflag ) && ( actortype != IS_INANIMATE ) )
		{
		return;
		}

	ent = ev->GetEntity( 1 );
	if ( ent && ent != world )
		{
		turnTo = new TurnTo;
		turnTo->SetTarget( ent );
		SetBehavior( turnTo, NULL, ev->GetThread() );
		}
	}

void Actor::TurnToEvent
	(
	Event *ev
	)
	
	{
	TurnTo *turnTo;

	if ( ( deadflag ) && ( actortype != IS_INANIMATE ) )
		{
		return;
		}

	turnTo = new TurnTo;
	turnTo->SetDirection( ev->GetFloat( 1 ) );

	SetBehavior( turnTo, NULL, ev->GetThread() );
	}

void Actor::IdleEvent
	(
	Event *ev
	)

	{
	Event *e;

	if ( ( deadflag ) && ( actortype != IS_INANIMATE ) )
		{
		return;
		}

	e = new Event( EV_Behavior_Args );
	e->SetSource( EV_FROM_SCRIPT );
	e->SetThread( ev->GetThread() );
	e->SetLineNumber( ev->GetLineNumber() );

	e->AddEntity( this );
	e->AddString( ev->GetToken( 1 ) );
	SetBehavior( new Idle, e, ev->GetThread() );
	}

void Actor::WalkTo
	(
	Event *ev
	)

	{
	Event *e;
	int i;
	int n;

	if ( ( deadflag ) && ( actortype != IS_INANIMATE ) )
		{
		return;
		}

	e = new Event( EV_Behavior_Args );
	e->SetSource( EV_FROM_SCRIPT );
	e->SetThread( ev->GetThread() );
	e->SetLineNumber( ev->GetLineNumber() );

	e->AddEntity( this );

	n = ev->NumArgs();

	e->AddString( "walk" );
	for( i = 1; i <= n; i++ )
		{
		e->AddToken( ev->GetToken( i ) );
		}

	SetBehavior( new GotoPathNode, e, ev->GetThread() );
	}

void Actor::RunTo
	(
	Event *ev
	)

	{
	Event *e;
	int i;
	int n;

	if ( ( deadflag ) && ( actortype != IS_INANIMATE ) )
		{
		return;
		}

	e = new Event( EV_Behavior_Args );
	e->SetSource( EV_FROM_SCRIPT );
	e->SetThread( ev->GetThread() );
	e->SetLineNumber( ev->GetLineNumber() );

	e->AddEntity( this );
	
	n = ev->NumArgs();

	e->AddString( "run" );
	for( i = 1; i <= n; i++ )
		{
		e->AddToken( ev->GetToken( i ) );
		}

	SetBehavior( new GotoPathNode, e, ev->GetThread() );
	}

void Actor::AttackEntity
	(
	Event *ev
	)
	
	{
	Entity *ent;

	if ( ( deadflag ) && ( actortype != IS_INANIMATE ) )
		{
		return;
		}

	ent = ev->GetEntity( 1 );
   // don't get mad at things that can't be hurt or the world
	if ( 
         ent && 
         ( ent != world ) && 
         ( ent->takedamage != DAMAGE_NO )
      )
		{
      ClearEnemies();
		MakeEnemy( ent, true );
		}
	}

void Actor::AttackPlayer
	(
	Event *ev
	)
	
	{
   int i;
	edict_t *ent;

	if ( ( deadflag ) && ( actortype != IS_INANIMATE ) )
		{
		return;
		}

   ClearEnemies();

   // make enemies of all the players
	for( i = 0; i < maxclients->value; i++ )
		{
		ent = &g_edicts[ i + 1 ];
		if ( !ent->inuse || !ent->client || !ent->entity )
			{
			continue;
			}

      MakeEnemy( ent->entity, true );
		}

   currentEnemy = BestTarget();
   if ( state != "sightenemy" )
      {
      if ( ForceAction( "sightenemy" ) )
         {
   		seenEnemy = true;
		   Chatter( "snd_sightenemy", 5 );
         }
      }
	}

void Actor::JumpToEvent
	(
	Event *ev
	)

	{
	Event *e;
	int i;
	int n;

	if ( ( deadflag ) && ( actortype != IS_INANIMATE ) )
		{
		return;
		}

	e = new Event( EV_Behavior_Args );
	e->SetSource( EV_FROM_SCRIPT );
	e->SetThread( ev->GetThread() );
	e->SetLineNumber( ev->GetLineNumber() );

	e->AddEntity( this );

	n = ev->NumArgs();

	e->AddString( "jump" );
	for( i = 1; i <= n; i++ )
		{
		e->AddToken( ev->GetToken( i ) );
		}

	SetBehavior( new Jump, e, ev->GetThread() );
	}

void Actor::GotoEvent
   (
   Event *ev
   )

   {
   // This command was added because it was a common mistake when writing actor scripts
   // to say "local.self goto label".  Since we're such nice guys, we'll print a warning
   // and send it on the the calling thread. :)
   ScriptThread *thread;

   thread = ev->GetThread();
   if ( thread )
      {
      gi.dprintf( "Actor recieved 'goto' command.  Passing to thread.\n" );
      thread->ProcessEvent( ev );
      }
   else
      {
      // should never happen, but say something anyways.
      gi.dprintf( "Actor recieved 'goto' command.  Thread is NULL.\n" );
      }
   }

//***********************************************************************************************
//
// Script conditionals
//
//***********************************************************************************************

void Actor::IfEnemyVisibleEvent
	(
	Event *ev
	)

	{
	ScriptThread *thread;

	thread = ev->GetThread();
	assert( thread );
	if ( !thread )
		{
		return;
		}

	if ( CanSeeEnemyFrom( worldorigin ) )
		{
		thread->ProcessCommandFromEvent( ev, 1 );
		}
	}

void Actor::IfNearEvent
	(
	Event *ev
	)

	{
	ScriptThread	*thread;
	Entity			*ent;
	Entity			*bestent;
	float				bestdist;
	float				dist;
	str				name;
   Vector         delta;
	float				distance;
	TargetList		*tlist;
	int				n;
	int				i;

	thread = ev->GetThread();
	assert( thread );
	if ( !thread )
		{
		return;
		}

	name = ev->GetString( 1 );
	distance = ev->GetFloat( 2 );

	if ( name[ 0 ] == '*' )
		{
		ent = ev->GetEntity( 1 );
		if ( WithinDistance( ent, distance ) )
			{
			SetVariable( "other", ent );
			thread->ProcessCommandFromEvent( ev, 3 );
			}
		}
	else if ( name[ 0 ] == '$' )
		{
		bestent = NULL;
		bestdist = distance * distance;

		tlist = world->GetTargetList( str( &name[ 1 ] ) );
		n = tlist->list.NumObjects();
		for( i = 1; i <= n; i++ )
			{
			ent = tlist->list.ObjectAt( i );
         delta = centroid - ent->centroid;
			dist = delta * delta;
			if ( dist <= bestdist )
				{
				bestent = ent;
				bestdist = dist;
				}
			}

		if ( bestent )
			{
			SetVariable( "other", bestent );
			thread->ProcessCommandFromEvent( ev, 3 );
			}
		}
	else
		{
		bestent = NULL;
		bestdist = distance * distance;

		ent = NULL;
		while( ent = findradius( ent, worldorigin.vec3(), distance ) )
			{
			if ( ent->inheritsFrom( name.c_str() ) )
				{
            delta = centroid - ent->centroid;
			   dist = delta * delta;
				if ( dist <= bestdist )
					{
					bestent = ent;
					bestdist = dist;
					}
				}
			}

		if ( bestent )
			{
			SetVariable( "other", bestent );
			thread->ProcessCommandFromEvent( ev, 3 );
			}
		}
	}

void Actor::IfCanHideAtEvent
	(
	Event *ev
	)

	{
	PathNode *node;
	Vector pos;
	ScriptThread *thread;

	thread = ev->GetThread();
	assert( thread );
	if ( !thread )
		{
		return;
		}

	pos = ev->GetVector( 1 );
	node = PathManager.NearestNode( pos, this );

	if ( node && ( node->nodeflags & ( AI_DUCK | AI_COVER ) ) && !CanSeeEnemyFrom( pos ) )
		{
		if ( !node->entnum || ( node->entnum == entnum ) || ( node->occupiedTime < level.time ) )
			{
			thread->ProcessCommandFromEvent( ev, 2 );
			}
		}
	}

void Actor::IfCanStrafeAttackEvent
	(
	Event *ev
	)

	{
	ScriptThread *thread;
	int num;
	Vector delta;
	Vector left;
	Vector pos;

   if ( !checkStrafe )
      return;
    
	if ( !currentEnemy )
		{
		return;
		}

	thread = ev->GetThread();
	assert( thread );
	if ( !thread )
		{
		return;
		}

	delta = currentEnemy->worldorigin - worldorigin;
	left.x = -delta.y;
	left.y = delta.x;
	left.normalize();

	num = gi.Anim_Random( edict->s.modelindex, "step_left" );
	if ( num != -1 )
		{
		gi.Anim_Delta( edict->s.modelindex, num, delta.vec3() );
      delta *= edict->s.scale;
		pos = worldorigin + left * delta.length();
		if ( CanMoveTo( pos ) && CanShootFrom( pos, currentEnemy, false ) )
			{
			thread->ProcessCommandFromEvent( ev, 1 );
			return;
			}
		}

	num = gi.Anim_Random( edict->s.modelindex, "step_right" );
	if ( num != -1 )
		{
		gi.Anim_Delta( edict->s.modelindex, num, delta.vec3() );
      delta *= edict->s.scale;
		pos = worldorigin - left * delta.length();
		if ( CanMoveTo( pos ) && CanShootFrom( pos, currentEnemy, false ) )
			{
			thread->ProcessCommandFromEvent( ev, 1 );
			return;
			}
		}
	}


void Actor::IfCanMeleeAttackEvent
	(
	Event *ev
	)

	{
	ScriptThread *thread;
	Vector      delta;
   float       r;

	if ( !currentEnemy || !has_melee )
		{
		return;
		}

	thread = ev->GetThread();
	assert( thread );
	if ( !thread )
		{
		return;
		}

   delta = centroid - currentEnemy->centroid;
	r = delta.length();
   if ( r <= melee_range )
      {
		thread->ProcessCommandFromEvent( ev, 1 );
      }
	}

void Actor::IfCanShootEvent
	(
	Event *ev
	)

	{
	ScriptThread *thread;

	if ( !currentEnemy )
		{
		return;
		}

	thread = ev->GetThread();
	assert( thread );
	if ( !thread )
		{
		return;
		}

   if ( CanShoot( currentEnemy, false ) )
      {
		thread->ProcessCommandFromEvent( ev, 1 );
      }
	}

void Actor::IfEnemyWithinEvent
	(
	Event *ev
	)

	{
	ScriptThread *thread;

	if ( !currentEnemy )
		{
		return;
		}

	thread = ev->GetThread();
	assert( thread );
	if ( !thread )
		{
		return;
		}

   if ( WithinDistance( currentEnemy, ev->GetFloat( 1 ) ) )
      {
		thread->ProcessCommandFromEvent( ev, 2 );
      }
	}

//***********************************************************************************************
//
// Sound reaction functions
//
//***********************************************************************************************

void Actor::IgnoreSoundsEvent
	(
	Event *ev
	)

	{
	DisableState( "weaponsound" );
	DisableState( "movementsound" );
	DisableState( "painsound" );
	DisableState( "deathsound" );
	DisableState( "breakingsound" );
	DisableState( "doorsound" );
	DisableState( "mutantsound" );
	DisableState( "voicesound" );
	DisableState( "machinesound" );
	DisableState( "radiosound" );
	}

void Actor::RespondToSoundsEvent
	(
	Event *ev
	)

	{
	EnableState( "weaponsound" );
	EnableState( "movementsound" );
	EnableState( "painsound" );
	EnableState( "deathsound" );
	EnableState( "breakingsound" );
	EnableState( "doorsound" );
	EnableState( "mutantsound" );
	EnableState( "voicesound" );
	EnableState( "machinesound" );
	EnableState( "radiosound" );
	}

void Actor::InvestigateWeaponSound
	(
	Event *ev
	)

	{
	Vector location;
	Entity *other;

	if ( !currentEnemy && !deadflag && ( nextsoundtime < level.time ) )
		{
		other = ev->GetEntity( 1 );
		location = ev->GetVector( 2 );
		SetVariable( "other", other );
		SetVariable( "location", location );
		if ( DoAction( "weaponsound" ) )
         {
   		nextsoundtime = level.time + 2;
         }
		}
	}

void Actor::InvestigateMovementSound
	(
	Event *ev
	)

	{
	Vector location;
	Entity *other;

	other = ev->GetEntity( 1 );
	if ( other && !currentEnemy && !deadflag && ( nextsoundtime < level.time ) && Hates( other ) )
		{
		location = ev->GetVector( 2 );
		SetVariable( "other", other );
		SetVariable( "location", location );
		if ( DoAction( "movementsound" ) )
   		nextsoundtime = level.time + 2;
		}
	}

void Actor::InvestigatePainSound
	(
	Event *ev
	)

	{
	Vector location;
	Entity *other;

	if ( !currentEnemy && !deadflag && ( nextsoundtime < level.time ) )
		{
		other = ev->GetEntity( 1 );
		location = ev->GetVector( 2 );
		SetVariable( "other", other );
		SetVariable( "location", location );
		if ( DoAction( "painsound" ) )
   		nextsoundtime = level.time + 2;
		}
	}

void Actor::InvestigateDeathSound
	(
	Event *ev
	)

	{
	Vector location;
	Entity *other;

	if ( !currentEnemy && !deadflag && ( nextsoundtime < level.time ) )
		{
		other = ev->GetEntity( 1 );
		location = ev->GetVector( 2 );
		SetVariable( "other", other );
		SetVariable( "location", location );
		if ( DoAction( "deathsound" ) )
   		nextsoundtime = level.time + 2;
		}
	}

void Actor::InvestigateBreakingSound
	(
	Event *ev
	)

	{
	Vector location;
	Entity *other;

	if ( !currentEnemy && !deadflag && ( nextsoundtime < level.time ) )
		{
		other = ev->GetEntity( 1 );
		location = ev->GetVector( 2 );
		SetVariable( "other", other );
		SetVariable( "location", location );
		if ( DoAction( "breakingsound" ) )
   		nextsoundtime = level.time + 2;
		}
	}

void Actor::InvestigateDoorSound
	(
	Event *ev
	)

	{
	Vector location;
	Entity *other;

	other = ev->GetEntity( 1 );
	if ( other && !currentEnemy && !deadflag && ( nextsoundtime < level.time ) && Hates( other ) )
		{
		location = ev->GetVector( 2 );
		SetVariable( "other", other );
		SetVariable( "location", location );
		if ( DoAction( "doorsound" ) )
   		nextsoundtime = level.time + 2;
		}
	}

void Actor::InvestigateMutantSound
	(
	Event *ev
	)

	{
	Vector location;
	Entity *other;

	other = ev->GetEntity( 1 );
	if ( other && !currentEnemy && !deadflag && ( nextsoundtime < level.time ) && Hates( other ) )
		{
		location = ev->GetVector( 2 );
		SetVariable( "other", other );
		SetVariable( "location", location );
		if ( DoAction( "mutantsound" ) )
   		nextsoundtime = level.time + 2;
		}
	}

void Actor::InvestigateVoiceSound
	(
	Event *ev
	)

	{
	Vector location;
	Entity *other;

	other = ev->GetEntity( 1 );
	if ( other && !currentEnemy && !deadflag && ( nextsoundtime < level.time ) && Hates( other ) )
		{
		location = ev->GetVector( 2 );
		SetVariable( "other", other );
		SetVariable( "location", location );
		if ( DoAction( "voicesound" ) )
	   	nextsoundtime = level.time + 2;
		}
	}

void Actor::InvestigateMachineSound
	(
	Event *ev
	)

	{
	Vector location;
	Entity *other;

	other = ev->GetEntity( 1 );
	if ( other && !currentEnemy && !deadflag && ( nextsoundtime < level.time ) && Hates( other ) )
		{
		location = ev->GetVector( 2 );
		SetVariable( "other", other );
		SetVariable( "location", location );
		if ( DoAction( "machinesound" ) )
   		nextsoundtime = level.time + 2;
		}
	}

void Actor::InvestigateRadioSound
	(
	Event *ev
	)

	{
	Vector location;
	Entity *other;

	other = ev->GetEntity( 1 );
	if ( other && !currentEnemy && !deadflag && ( nextsoundtime < level.time ) && Hates( other ) )
		{
		location = ev->GetVector( 2 );
		SetVariable( "other", other );
		SetVariable( "location", location );
		if ( DoAction( "radiosound" ) )
   		nextsoundtime = level.time + 2;
		}
	}

//***********************************************************************************************
//
// Pain and death related functions
//
//***********************************************************************************************

void Actor::Pain
	(
	Event *ev
	)

	{
	float		damage;
	Entity	*ent;
	float		oldhealth;
	float		newhealth;

#ifdef DEBUG_PRINT
	gi.dprintf( "Pain\n" );
#endif

	damage = ev->GetFloat( 1 );
	ent = ev->GetEntity( 2 );

   // if it's a Sentient and not liked, attack 'em.
	if ( ent && ent->isSubclassOf( Sentient ) && !Likes( ent ) )
      {
		MakeEnemy( ent );
      if ( ent != currentEnemy )
         {
         currentEnemy = BestTarget();
         }
      }

   if ( damage <= 0 )
      {
      return;
      }

	oldhealth = ( health + damage ) / max_health;
	newhealth = health / max_health;

   SetVariable( "other", ev->GetEntity( 2 ) );

   // If we pass more than one range,  
	if ( ( oldhealth > 0.75 ) && ( newhealth <= 0.75 ) )
		{
		DoAction( "health_ok" );
		}
	if ( ( oldhealth > 0.5 ) && ( newhealth <= 0.5 ) )
		{
		DoAction( "health_med" );
		}
	if ( ( oldhealth > 0.25 ) && ( newhealth <= 0.25 ) )
		{
		DoAction( "health_low" );
		}
	if ( ( oldhealth > 0.1 ) && ( newhealth <= 0.1 ) )
		{
		DoAction( "health_danger" );
		}

   if ( damage <= pain_threshold )
      {
		Chatter( "snd_pain_taunt", 5, true );
      return;
      }

	if ( strncmp( animname.c_str(), "pain", 4 ) && strncmp( animname.c_str(), "crouch_pain", 11 ) )
		{
      str aname;
      int index;

      //
      // determine pain animation
      //
		if ( !strncmp( animname.c_str(), "crouch", 6 ) )
			{
			aname = "crouch_";
			}
      aname += str("pain_") + str( ev->GetString( 3 ) );
   	index = gi.Anim_Random( edict->s.modelindex, aname.c_str() );
      if ( ( index == -1 ) && !strncmp( animname.c_str(), "crouch", 6 ) )
			{
			aname = "crouch_pain";
			index = gi.Anim_Random( edict->s.modelindex, aname.c_str() );
			}

		if ( index == -1 )
			{
			aname = "pain";
			}

		SetVariable( "painanim", aname.c_str() );
		DoAction( "pain" );
		}
	}

void Actor::Dead
	(
	Event *ev
	)

	{
   Vector   min, max;
   Event    *event;

	StopAnimating();
	if ( !groundentity && ( velocity != vec_zero ) )
		{
		// wait until we hit the ground
		PostEvent( ev, FRAMETIME );
		return;
		}

   //
   // drop anything that might be attached to us
   //
   if ( numchildren )
      {
      Entity * child;
      int i;
      //
      // detach all our children
      //
      for ( i = 0; i < MAX_MODEL_CHILDREN; i++ )
         {
         if ( children[ i ] )
            {
            child = ( Entity * )G_GetEntity( children[ i ] );
            child->ProcessEvent( EV_Detach );
            }
         }
      }
   
   deadflag = DEAD_DEAD;
   maxs[0] *= 2.0f;
   maxs[1] *= 2.0f;
   maxs[2] *= 0.3f;
   setSize(mins,maxs);
   edict->svflags |= SVF_DEADMONSTER;
   setMoveType( MOVETYPE_NONE );
   setOrigin( worldorigin );

   if ( deathgib )
      {
      // Put down a bloodsplat
      Vector      start, end, dir, norm, ang;
      float       scale;
      BloodSplat  *splat;
      trace_t     trace;

      dir   = Vector( 0, 0, -1 );
      start = centroid;
      end   = start + 100 * dir;

    	trace = G_Trace( start, vec_zero, vec_zero, end, this, MASK_SOLIDNONFENCE, "Actor::Dead" );

   	if ( !( HitSky( &trace ) || ( trace.ent->solid != SOLID_BSP ) || ( trace.ent->s.number != 0 ) ) )
	   	{
         scale = G_Random( 1.2 );
         if ( scale < 0.5 )
            scale = 0.5;
         norm = trace.plane.normal;
         norm.x = -norm.x;
         norm.y = -norm.y;
         ang = norm.toAngles();
         ang.z = G_Random( 360 );
         end = trace.endpos + Vector( trace.plane.normal ) * 0.2;
         splat = new BloodSplat( end, ang, scale );
         }
      }

   // If this body has nothing interesting, then remove it
   if ( !NumInventoryItems() )
      {
      if ( nodeathfade )
         return;

      PostEvent( EV_FadeOut, 10 );
      return;
      }

   // Spawn a touch field 
   min = worldorigin - "32 32 32";
	max = worldorigin + "32 32 32";
	trig = new TouchField;
	trig->Setup( this, EV_Touch, min, max, TRIGGER_PLAYERS );
   
   assert( trig->edict->solid == SOLID_TRIGGER );

   if ( !nodeathfade )
      {
      // Check in the future for uselessness
      event = new Event ( EV_Sentient_UselessCheck );
      PostEvent ( event, 1.0f + G_Random() );

      // If this guy has no InventoryItems, then fade him in 1 minute
      if ( !HasInventoryOfType( "InventoryItem" ) )
         {
         PostEvent( EV_Actor_Remove, 60.0f );
         }
      }
	}

void Actor::Killed
	(
	Event *ev
	)

	{
   const char	*name;
	Entity		*ent;
   int			num;
   Entity		*attacker;
   Entity		*inflictor;
   Vector		dir;
   Event			*event;
	int			i;
   str         dname;
   int         meansofdeath;

   CheckWater();
	StopAnimating();
	CancelPendingEvents();

   // don't allow them to fly, think, or swim anymore
   flags &= ~( FL_PRETHINK | FL_SWIM | FL_FLY );

	deadflag = DEAD_DYING;
	takedamage = DAMAGE_YES;
   groundentity = NULL;

   attacker	= ev->GetEntity( 1 );
	inflictor = ev->GetEntity( 3 );
	meansofdeath = ev->GetInteger( 5 );

   // Double all the armor
   DoubleArmor();

   SetVariable( "other", ev->GetEntity( 1 ) );
	if ( !DoAction( "killed" ) && actorthread )
		{
		actorthread->ProcessEvent( EV_ScriptThread_End );
		}


   // Turn off dlight and shadow
   edict->s.renderfx &= ~( RF_DLIGHT|RF_XFLIP );

   //
   // kill the killtargets
   //
	name = KillTarget();
	if ( name && strcmp( name, "" ) )
		{
		num = 0;
		do
			{
			num = G_FindTarget( num, name );
			if ( !num )
				{
				break;
				}

			ent = G_GetEntity( num );
			ent->PostEvent( EV_Remove, 0 );
			} 
		while ( 1 );
		}
		
   //
   // fire targets
   //
	name = Target();
	if ( name && strcmp( name, "" ) )
		{
		num = 0;
		do
			{
			num = G_FindTarget( num, name );
			if ( !num )
				{
				break;
				}

			ent = G_GetEntity( num );
		
			event = new Event( EV_Activate );
			event->AddEntity( attacker );
			ent->PostEvent( event, 0 );
			}
		while ( 1 );
		}
   //
   // see if we have a kill_thread
   //
   if ( kill_thread.length() > 1 )
      {
      ScriptThread * thread;

      //
      // create the thread, but don't start it yet
      //
      thread = ExecuteThread( kill_thread, false );
      if ( thread )
         {
         ProcessScript( thread, NULL );
         }
      else
         {
         warning( "Killed", "could not process kill_thread" );
         }
      }

   if (flags & FL_DIE_EXPLODE)
      {
	   CreateExplosion( worldorigin, 150*edict->s.scale, edict->s.scale * 2, true, this, this, this );
      }

   if ( flags & FL_DIE_TESSELATE )
      {
      float power;
      setSolidType( SOLID_NOT );
	   hideModel();

      dir = worldorigin - attacker->worldorigin;

	   if ( meansofdeath == MOD_ION )
         {
         power = 1000;
         }
      else
         {
         power = ev->GetFloat( 2 );
         }

      TesselateModel
         (
         this,
         tess_min_size,
         tess_max_size,
         dir,
         power,
         1.0f,
         tess_thickness,
         vec3_origin
         );

      DropInventoryItems();
		// Tesselated models require the model to be on the client for 1 more frame
		PostEvent( EV_Remove, FRAMETIME );
		return;
      }
	
   if ( DoGib( meansofdeath, inflictor ) )
		{
      deathgib = true;      
      }

   if ( currentWeapon )
      {
      DropWeapon( currentWeapon );
      }

	animOverride = false;
   
   //
   // determine death animation
   //
	if ( !strncmp( animname.c_str(), "crouch", 6 ) )
		{
		dname = "crouch_";
		}
   
   if ( deathgib )
      {
      str location;

      location = ev->GetString( 4 );

      // Check for location first otherwise randomize
      if ( location == "torso_upper" )
         dname += str( "gibdeath_upper" );
      else if ( location == "torso_lower" )
         dname += str( "gibdeath_lower" );
      else if ( strstr( location.c_str(), "leg" ) )
         dname += str( "gibdeath_lower" );
      else if ( strstr( location.c_str(), "arm" ) )
         dname += str( "gibdeath_upper" );
      else if ( strstr( location.c_str(), "head" ) )
         dname += str( "gibdeath_upper" );
      else if ( G_Random() > 0.5 )
         dname += str( "gibdeath_upper" );
      else
         dname += str( "gibdeath_lower" );
      }
   else
      {
      dname += str( "death_" ) + str( ev->GetString( 4 ) );
      }
   
   i = gi.Anim_Random( edict->s.modelindex, dname.c_str() );
   
   if ( ( i == -1 ) && !strncmp( animname.c_str(), "crouch", 6 ) )
		{
		dname = "crouch_death";
		i = gi.Anim_Random( edict->s.modelindex, dname.c_str() );
		}

	if ( i == -1 )
		{
		dname = "death";
		}

   if ( ( i != -1 ) &&  ( !strncmp( dname.c_str(), "gibdeath", 7 ) ) )
      {
      Event *ev1;
      
      ev1 = new Event( EV_Gib );
      ev1->AddInteger( 1 );
      ProcessEvent( ev1 );
      }
   if ( attacker )
      {
      str location;
      float damage;

      damage = ev->GetFloat( 2 );
      location = ev->GetString( 4 );

		event = new Event( EV_GotKill );
		event->AddEntity( this );
		event->AddInteger( damage );
		event->AddEntity( inflictor );
      event->AddString( location );
      event->AddInteger( meansofdeath );
      event->AddInteger( deathgib );
		attacker->ProcessEvent( event );
      }

	SetAnim( dname.c_str(), EV_Actor_Dead );

	// Call changeanim immediatly since we're no longer calling prethink
	ChangeAnim();

   //
   // moved this here so guys would not be solid right away
   //
   edict->svflags |= SVF_DEADMONSTER;
	edict->clipmask = MASK_DEADSOLID;

	if ( velocity.z < 10 )
		{
		velocity.z += G_Random( 300 );
		}

	angles.x = 0;
	angles.z = 0;
	setAngles( angles );
	}

void Actor::GibEvent
   (
   Event *ev
   )

   {
   qboolean hidemodel;

   hidemodel = !ev->GetInteger( 1 );

   if ( sv_gibs->value && !parentmode->value ) 
      {
      int numgibs;
      float gibsize;

      if ( hidemodel )
         {
         takedamage = DAMAGE_NO;
         setSolidType( SOLID_NOT );
	      hideModel();
       
         // If there is a touchfield, remove it.
         if ( trig )
			   {
            trig->PostEvent( EV_Remove, 0 );
			   trig = NULL;
			   }
         }

      gibsize = size.length() / 140;
      numgibs = gibsize * 6;
      if ( numgibs > 4 )
         numgibs = 4;
      CreateGibs( this, health, gibsize, numgibs );
      }

   DropInventoryItems();
   
   if ( hidemodel )
      PostEvent( EV_Remove, 0 );
   }

void Actor::RemoveUselessBody
   (
   Event *ev
   )

   {
   if ( trig )
   	{
      trig->PostEvent( EV_Remove, 0 );
		trig = NULL;
      }

   CancelEventsOfType( EV_Sentient_UselessCheck );
   PostEvent( EV_FadeOut, 5);
   }

void Actor::SetPainThresholdEvent
   (
   Event *ev
   )

   {
   pain_threshold = ( ev->GetFloat( 1 ) ) * skill->value * 0.66f;
   }

void Actor::SetKillThreadEvent
   (
   Event *ev
   )

   {
   kill_thread = ev->GetString( 1 );
   }

void Actor::AttackRangeEvent
   (
   Event *ev
   )

   {
   attack_range = ev->GetFloat( 1 );
   }

void Actor::AttackModeEvent
   (

   Event *ev
   )

   {
   attackmode = ev->GetInteger( 1 );
   SetVariable( "attackmode", attackmode );
   }

void Actor::ShotsPerAttackEvent
   (
   Event *ev
   )

   {
   float shots;

   shots = ev->GetFloat( 1 );
   //
   // scale the shots based on skill
   //
   if ( skill->value < 1 )
      shots_per_attack = shots * 0.4f;
   else if ( skill->value < 2 )
      shots_per_attack = shots * 0.7f;
   else if ( skill->value < 3 )
      shots_per_attack = shots;
   else
      shots_per_attack = shots * skill->value * 0.4f;
   }

void Actor::ClearEnemyEvent
   (
   Event *ev
   )

   {
   ClearEnemies();
   }

void Actor::NoDeathFadeEvent
	(
	Event *ev
	)

	{
   nodeathfade = true;
	}

void Actor::NoChatterEvent
	(
	Event *ev
	)

	{
   nochatter = true;
	}

void Actor::TurnSpeedEvent
	(
	Event *ev
	)

	{
   turnspeed = ev->GetFloat( 1 );
	}


//***********************************************************************************************
//
// Movement functions
//
//***********************************************************************************************

void Actor::ForwardSpeedEvent
   (
   Event *ev
   )

   {
   forwardspeed = ev->GetFloat( 1 );
   }

void Actor::SwimEvent
   (
   Event *ev
   )

   {
   // movement |= AI_CANSWIM;
   flags &= ~FL_FLY;
   flags |= FL_SWIM;
   }

void Actor::FlyEvent
   (
   Event *ev
   )

   {
   // movement |= AI_CANFLY;
   flags &= ~FL_SWIM;
   flags |= FL_FLY;
   }

void Actor::NotLandEvent
   (
   Event *ev
   )

   {
   //movement &= ~AI_CANWALK;
   flags &= FL_SWIM | FL_FLY;
   }

inline qboolean Actor::CanMoveTo
	(
	Vector pos
	)

	{
	Vector	min;
	trace_t	trace;
	Vector	start;
	Vector	end;
	Vector	s;

	s = Vector( 0, 0, STEPSIZE );
	start = worldorigin + s;
	end = pos + s;
	trace = G_Trace( start, mins, maxs, end, this, edict->clipmask, "Actor::CanMoveTo" );
	if ( trace.fraction == 1 )
		{
		return true;
		}
	return false;
	}

inline void Actor::CheckWater
	(
   void
	)
   {
   Vector sample[3];
   int cont;

   //
   // get waterlevel and type
   //
	waterlevel = 0;
	watertype = 0;

   sample[ 0 ] = worldorigin;
   sample[ 2 ] = EyePosition();
   sample[ 1 ] = ( sample[ 0 ] + sample[ 2 ] ) * 0.5f;

	cont = gi.pointcontents( sample[ 0 ].vec3() );

	if (cont & MASK_WATER)
	   {
		watertype = cont;
		waterlevel = 1;
   	cont = gi.pointcontents( sample[ 2 ].vec3() );
		if (cont & MASK_WATER)
		   {
			waterlevel = 3;
         }
      else
         {
   	   cont = gi.pointcontents( sample[ 1 ].vec3() );
		   if (cont & MASK_WATER)
		      {
			   waterlevel = 2;
            }
         }
		}
	}

#define MAX_PITCH 75
void Actor::Accelerate
	(
	Vector steering
	)

	{
   // activate this to limit turnrate
#if 0
   if ( steering.y > turnspeed )
      steering.y = turnspeed;
   else if ( steering.y < -turnspeed )
      steering.y = -turnspeed;
#endif

	angles.y += steering.y;

   if ( frame_delta.x > 4 )
      {
	   // make him lean into the turn a bit
	   angles.z = movespeed * ( 0.4f / 320.0f ) * steering.y;

      if ( ( flags & FL_FLY ) || ( ( flags & FL_SWIM ) && waterlevel > 0 ) )
         {
         angles.z = bound( angles.z, -2, 2 );
         }
      else
         {
         angles.z = bound( angles.z, -5, 5 );
         }
      }
   else
      {
      angles.z = 0;
      }

   if ( ( flags & FL_FLY ) || ( ( flags & FL_SWIM ) && waterlevel > 0 ) )
		{
		angles.x -= steering.x;
      //angles.x = bound( angles.x, -MAX_PITCH, MAX_PITCH );
		}

   setAngles( angles );
	}

void Actor::CalcMove
	(
	void
	)

	{
   if ( total_delta != vec_zero )
		{
		// movement deltas have inverted Y axis
		total_delta[ 1 ] = -total_delta[ 1 ];
		MatrixTransformVector( total_delta.vec3(), orientation, move.vec3() );
		total_delta = vec_zero;
		}
	else
		{
		move = vec_zero;
		}

   // force movement if forwardspeed is set
   if ( forwardspeed )
      {
      if ( move == vec_zero )
         {
         move = orientation[ 0 ];
         }
      else
         {
         move.normalize();
         }

		animdir = move;
      movedir = move;
		movespeed = forwardspeed;
      move *= movespeed * FRAMETIME;
		totallen = forwardspeed;
		movevelocity = movedir * movespeed;
      }
   }

void Actor::setAngles
	(
	Vector ang
	)

	{
	Sentient::setAngles( ang );
	MatrixTransformVector( animdir.vec3(), orientation, movedir.vec3() );
	movevelocity = movedir * movespeed;
	}

stepmoveresult_t Actor::WaterMove
   (
   void
   )

   {
	Vector	oldorg;
	Vector	neworg;
	trace_t	trace;
   int      oldwater;

	if ( ( totallen <= 0.01f ) || ( move == vec_zero ) )
		{
		return STEPMOVE_OK;
		}

	// try the move
	oldorg = worldorigin;
	neworg = worldorigin + move;

	trace = G_Trace( oldorg, mins, maxs, neworg, this, edict->clipmask, "Actor::WaterMove 1" );
	if ( trace.fraction == 0 )
		{
		return STEPMOVE_STUCK;
		}

   oldwater = waterlevel;

   setOrigin( trace.endpos );

   CheckWater();

	// swim monsters don't exit water voluntarily
	if ( ( oldwater > 1 ) && ( waterlevel < 2 ) )
	   {
      waterlevel = oldwater;
      setOrigin( oldorg );
      return STEPMOVE_STUCK;
   	}

	return STEPMOVE_OK;
   }

stepmoveresult_t Actor::AirMove
   (
   void
   )

   {
	Vector	oldorg;
	Vector	neworg;
	trace_t	trace;
   int      oldwater;

	if ( ( totallen <= 0.01f ) || ( move == vec_zero ) )
		{
		return STEPMOVE_OK;
		}

	// try the move
	oldorg = worldorigin;
	neworg = worldorigin + move;

	trace = G_Trace( oldorg, mins, maxs, neworg, this, edict->clipmask, "Actor::AirMove 1" );
	if ( trace.fraction == 0 )
		{
		return STEPMOVE_BLOCKED_BY_WATER;
		}

   oldwater = waterlevel;

   setOrigin( trace.endpos );

   CheckWater();

	// fly monsters don't enter water voluntarily
	if ( !oldwater && waterlevel )
	   {
      waterlevel = oldwater;
      setOrigin( oldorg );
		return STEPMOVE_STUCK;
	   }

	return STEPMOVE_OK;
   }

stepmoveresult_t Actor::TryMove
	(
	void
	)

	{
	Vector	oldorg;
	Vector	neworg;
	Vector	end;
	Entity	*ent;
	trace_t	trace;
   Door     *door;
#if 0
	vec3_t	test;
	int		contents;
#endif

	if ( ( totallen <= 0.01f ) || ( move == vec_zero ) )
		{
		return STEPMOVE_OK;
		}

	// try the move
	oldorg = worldorigin;
	neworg = worldorigin + move;

	// push down from a step height above the wished position
	neworg[ 2 ] += STEPSIZE;
	end = neworg;
	end[ 2 ] -= STEPSIZE * 4;//2;

	trace = G_Trace( neworg, mins, maxs, end, this, edict->clipmask, "Actor::TryMove 1" );
	if ( trace.allsolid )
		{
		ent = trace.ent->entity;
		if ( ent && ent->isSubclassOf( Door ) )
         {
         if ( state == "opendoor" )
            {
            return STEPMOVE_OK;
            }

         door = ( Door * )ent;
         if ( !door->locked && !door->isOpen() )
            {
   			SetVariable( "other", ent );
	   		SetVariable( "dir", end - worldorigin );
		   	ForceAction( "opendoor" );

            return STEPMOVE_OK;
            }
			}

		return STEPMOVE_STUCK;
		}

	if ( trace.startsolid )
		{
		neworg[ 2 ] -= STEPSIZE;
#if 0
		trace = G_Trace( neworg, mins, maxs, end, this, edict->clipmask, "Actor::TryMove 2" );
#else
      // 2015 - The following line altered to allow short actors to detect doors,
      // It doesn't seem to break anything else...
      if ( maxs[ 2 ] > ( STEPSIZE * 3 ) )
         {
   		trace = G_Trace( neworg, mins, maxs, end, this, edict->clipmask, "Actor::TryMove 2" );
         }
      else
         {
		   trace = G_Trace( neworg + movetweak, mins, maxs - movetweak, end, this, edict->clipmask, "Actor::TryMove 2" );
         }
#endif
		if ( trace.allsolid || trace.startsolid )
			{
			ent = trace.ent->entity;
		   if ( ent && ent->isSubclassOf( Door ) )
            {
            if ( state == "opendoor" )
               {
               return STEPMOVE_OK;
               }

            door = ( Door * )ent;
            if ( !door->locked && !door->isOpen() )
               {
   			   SetVariable( "other", ent );
	   		   SetVariable( "dir", end - worldorigin );
		   	   ForceAction( "opendoor" );

               return STEPMOVE_OK;
               }
			   }

		   return STEPMOVE_STUCK;
			}
		}

#if 0
	// don't go in to water
	if ( waterlevel == 0 )
		{
		test[ 0 ] = trace.endpos[ 0 ];
		test[ 1 ] = trace.endpos[ 1 ];
		test[ 2 ] = trace.endpos[ 2 ] + mins[ 2 ] + 1;	
		contents = gi.pointcontents( test );

		if ( contents & MASK_WATER )
			{
			return STEPMOVE_BLOCKED_BY_WATER;
			}
		}
#endif

	if ( trace.fraction == 1 )
		{
      // don't let guys get stuck standing on other guys
		// if monster had the ground pulled out, go ahead and fall
		if ( ( flags & FL_PARTIALGROUND ) || ( groundentity && groundentity->entity && 
         ( groundentity->entity->isSubclassOf( Sentient ) ) ) )
			{
			setOrigin( worldorigin + move );
			groundentity = NULL;
			return STEPMOVE_OK;
			}
	
		// walked off an edge
		return STEPMOVE_BLOCKED_BY_FALL;
		}

	// check point traces down for dangling corners
	worldorigin = trace.endpos;

	if ( !M_CheckBottom( this ) )
		{
      // don't let guys get stuck standing on other guys
		if ( ( flags & FL_PARTIALGROUND ) || ( groundentity && groundentity->entity && 
         ( groundentity->entity->isSubclassOf( Sentient ) ) ) )
			{
			// entity had floor mostly pulled out from underneath it
			// and is trying to correct
			setOrigin( worldorigin );

         CheckWater();

			return STEPMOVE_OK;
			}

		setOrigin( oldorg );
		return STEPMOVE_BLOCKED_BY_FALL;
		}

	if ( flags & FL_PARTIALGROUND )
		{
		flags &= ~FL_PARTIALGROUND;
		}

	groundentity = trace.ent;
	groundentity_linkcount = trace.ent->linkcount;
	groundplane = trace.plane;
	groundsurface = trace.surface;
	groundcontents = trace.contents;

	// the move is ok
	setOrigin( worldorigin );

   CheckWater();

	return STEPMOVE_OK;
	}

void Actor::SetAim
   (
   Event *ev
   )
   {
   aim = ev->GetFloat( 1 );
   }

void Actor::SetMeleeRange
   (
   Event *ev
   )
   {
   melee_range = ev->GetFloat( 1 );
   melee_range *= edict->s.scale;
   if ( melee_range < 70 )
      melee_range = 70;
   }

void Actor::SetMeleeDamage
   (
   Event *ev
   )
   {
   melee_damage = ev->GetFloat( 1 );
   melee_damage *= edict->s.scale;
   }

void Actor::MeleeEvent
   (
   Event *ev
   )
   {
	trace_t	trace;
	Vector	start;
	Vector	end;
   float    damage;
   float    extra_reach;
	Vector   org;
   Vector   ang;
	Vector   dir;
   float    kick;

   if ( !has_melee )
      {
      warning( "MeleeEvent","Melee being called without animation" );
      return;
      }

   damage = G_Random( melee_damage*0.5f )+ G_Random( melee_damage*0.5f );
   if ( ev->NumArgs() > 0 )
      extra_reach = ev->GetFloat( 1 );
   else
      extra_reach = 0;

   if ( ev->NumArgs() > 1 )
      {
      kick = ev->GetFloat( 2 );
      }
   else
      {
      kick = damage * 3;
      }

   // get the position of the attack 
	start = GunPosition();
   // get the attack_dir
   ang = MyGunAngles( start, true );
	ang.AngleVectors( &dir, NULL, NULL );

	end	= start + dir * ( melee_range + extra_reach );

   trace = G_FullTrace( start, vec_zero, vec_zero, end, 15, this, MASK_PROJECTILE, "Actor::Melee" );

	dir = Vector(trace.endpos) - start;
	dir.normalize();

	org = Vector(trace.endpos) - dir;

   if ( (trace.fraction < 1.0f) )
      {
      if ( trace.ent->entity && trace.ent->entity->takedamage )
		   {
         if ( trace.ent->entity->flags & FL_BLOOD )
   	      SpawnBlood( org, trace.plane.normal, damage );

         RandomGlobalSound("impact_goryimpact");
         if ( trace.intersect.valid )
            {
   			// We hit a valid group so send in location based damage
            trace.ent->entity->Damage( this,
                         this,
                         damage,
                         trace.endpos,
                         dir,
                         trace.plane.normal,
                         kick,
                         0,
                         MOD_FISTS,
                         trace.intersect.parentgroup,
                         -1,
                         trace.intersect.damage_multiplier );
            }
         else
            {
            // take the ground out so that the kick works
            trace.ent->entity->groundentity = NULL;

            // We didn't hit any groups, so send in generic damage
   			trace.ent->entity->Damage( this,
                         this,
                         damage,
                         trace.endpos,
                         dir,
                         trace.plane.normal,
                         kick,
                         0,
                         MOD_FISTS,
                         -1,
                         -1,
                         1 );
            }
		   }
      }
	}

void Actor::AttackFinishedEvent
   (
   Event *ev
   )
   {
   if ( currentWeapon )
      {
      currentWeapon->PostEvent( EV_Weapon_FinishAttack, 0 );
      }
   }

float Actor::JumpTo
   (
   Vector targ,
   float speed
   )
   {
   float		traveltime;
   float		vertical_speed;
   Vector	target;
	Vector	dir;
   Vector	xydir;

   CheckWater();
   //
   // if we got a jump, go into that mode
   //
   traveltime = 0;
   if ( speed <= 0 )
      {
      speed = movespeed * 1.5f;
      if ( speed < (400 * gravity) )
         speed = (400 * gravity);
      }

   target = targ;
   dir = target - worldorigin;
   xydir = dir;
   xydir.z = 0;
   setAngles( xydir.toAngles() );
   traveltime = xydir.length() / speed;
   //
   // we add 16 to allow for a little bit higher
   //
   if ( waterlevel > 2 )
      {
      vertical_speed = ( ( dir.z + 16 ) / traveltime ) + ( 0.5f * gravity * 60 * traveltime );
      }
   else
      {
      vertical_speed = ( ( dir.z + 16 ) / traveltime ) + ( 0.5f * gravity * sv_gravity->value * traveltime );
      }
   xydir.normalize();

   velocity = speed * xydir;
   velocity.z = vertical_speed;

   return traveltime;
   }

float Actor::JumpTo
   (
   PathNode *goal,
   float speed
   )
   {
   if ( goal )
      return JumpTo( goal->worldorigin, speed );
   else
      return 0;
   }

float Actor::JumpTo
   (
   Entity *goal,
   float speed
   )
   {
   if ( goal )
      return JumpTo( goal->worldorigin, speed );
   else
      return 0;
   }

EXPORT_FROM_DLL void Actor::setSize
	(
	Vector min,
	Vector max
	)
	{
   min *= edict->s.scale;
   max *= edict->s.scale;
   Sentient::setSize( min, max );
   }

EXPORT_FROM_DLL void Actor::SetHealth
	(
	Event *ev
	)

	{
	health = ev->GetFloat( 1 ) * edict->s.scale;
   max_health = health;
	}

//***********************************************************************************************
//
// Debug functions
//
//***********************************************************************************************

void Actor::ShowInfo
   (
   void
   )

   {
   Entity *ent;
	int i;
	int n;
	StateInfo *ptr;

   gi.printf( "\nEntity #   : %d\n", entnum );
   gi.printf( "Class ID   : %s\n", getClassID() );
   gi.printf( "Classname  : %s\n", getClassname() );
	gi.printf( "Targetname : %s\n", TargetName() );
	gi.printf( "Origin     : ( %f, %f, %f )\n", worldorigin.x, worldorigin.y, worldorigin.z );
	gi.printf( "Bounds     : Mins( %.2f, %.2f, %.2f ) Maxs( %.2f, %.2f, %.2f )\n", mins.x, mins.y, mins.z, maxs.x, maxs.y, maxs.z );
   gi.printf( "State      : %s\n", state.c_str() );

   if ( behavior )
      {
      gi.printf( "Behavior   : %s\n", behavior->getClassname() );
      }
   else
      {
      gi.printf( "Behavior   : NULL -- was '%s'\n", currentBehavior.c_str() );
      }

   if ( actorthread )
      {
      gi.printf( "Thread     : %s(%d)\n", actorthread->Filename(), actorthread->CurrentLine() );
      }
   else
      {
      gi.printf( "Thread     : NULL\n" );
      }
   gi.printf( "Actortype  : %d\n", actortype );
   gi.printf( "Attackmode : %d\n", attackmode );

   gi.printf( "Model      : %s\n", model.c_str() );
   gi.printf( "Anim       : %s\n", animname.c_str() );
	gi.printf( "Movespeed  : %.2f\n", movespeed );
   gi.printf( "Health     : %f\n", health );

   gi.printf( "\nResponses:\n" );
	n = actionList.NumObjects();
	for( i = 1; i <= n; i++ )
		{
		ptr = actionList.ObjectAt( i );
      gi.printf( "%s : ", ptr->action.c_str() );
      if ( ptr->ignore )
         {
         gi.printf( "ignored - " );
         }

      gi.printf( "%s\n", ptr->response.c_str() );
		}

	n = enemyList.NumObjects();
   if ( n )
      {
      gi.printf( "\nEnemies:\n" );

	   for( i = 1; i <= n; i++ )
		   {
		   ent = enemyList.ObjectAt( i );
         if ( ent )
            {
            if ( currentEnemy == ent )
               {
               gi.printf( "*" );
               }
            else
               {
               gi.printf( " " );
               }
            gi.printf( "%d : '%s'", ent->entnum, ent->targetname.c_str() );
            gi.printf( "\n" );
            }
         }
      }
   
   gi.printf( "seenEnemy: %d\n", seenEnemy );
   gi.printf( "actortype: %d\n", actortype );
   gi.printf( "deadflag: %d\n", deadflag );

   gi.printf( "\n" );
   if ( behavior )
      {
      gi.printf( "Behavior Info:\n" );
      gi.printf( "Game time: %f\n", level.time );
      behavior->ShowInfo( *this );
      gi.printf( "\n" );
      }
   }

//***********************************************************************************************
//
// General functions
//
//***********************************************************************************************

void Actor::Chatter
	(
	const char *snd,
	float chance,
	float volume,
	int channel
	)

	{
   str realname;

	if ( nochatter || chattime > level.time )
		{
		return;
		}

	if ( G_Random( 10 ) > chance )
		{
		chattime = level.time + 1 + G_Random( 2 );
		return;
		}

   realname = GetRandomAlias( snd );
	if ( realname.length() > 1 )
		{
      float delay;

      delay = gi.SoundLength( realname.c_str() );
		chattime = level.time + delay + 4 + G_Random( 5 );
		sound( realname, volume, channel );
		}
	else
		{
      // set it into the future, so we don't check it again right away
		chattime = level.time + 1;
		}
	}

void Actor::ActivateEvent
	(
	Event *ev
	)

	{
	Entity *ent;

	if ( ( deadflag ) && ( actortype != IS_INANIMATE ) )
		{
		return;
		}

	ent = ev->GetEntity( 1 );
	SetVariable( "other", ent );

	DoAction( "activate" );
	}

void Actor::UseEvent
	(
	Event *ev
	)

	{
	Entity *ent;

	if ( ( deadflag ) && ( actortype != IS_INANIMATE ) )
		{
		return;
		}

	ent = ev->GetEntity( 1 );
	SetVariable( "other", ent );

	DoAction( "use" );
	}

void Actor::Prethink
	(
	void
	)

	{
	range_t range;
   Event *event;

	assert( actorthread );
   if ( !actorthread )
      {
      // not having a script is bad
      gi.dprintf( "Null actorthread.  Killing actor '%s'(%d).\n", targetname.c_str(), entnum );

      // just kill him
		event = new Event( EV_Killed );
		event->AddEntity( this );
		event->AddInteger( 0 );
		event->AddEntity( this );
      event->AddString( "all" );
		ProcessEvent( event );

      return;
      }

	if ( hidden() )
		{
		// Don't think while hidden, you're just a cinematic.
		return;
		}

   if ( actortype == IS_INANIMATE )
      {
	   if ( behavior && !behavior->Evaluate( *this ) )
		   {
         // stop thinking
         flags &= ~FL_PRETHINK;
		   EndBehavior();
		   }
      return;
      }

	if ( currentEnemy )
		{
		if ( currentEnemy->deadflag )
			{
			DoAction( "enemydead" );
			currentEnemy = NULL;
         seenEnemy = false;
			}
		else
			{
			range = Range( currentEnemy );
			if ( ( lastEnemy != currentEnemy ) || ( range != enemyRange ) )
				{
				lastEnemy = currentEnemy;
				enemyRange = range;

				SetVariable( "other", currentEnemy );
				switch( range )
					{
					case RANGE_MELEE :
						DoAction( "range_melee" );
						break;

					case RANGE_NEAR :
						DoAction( "range_near" );
						break;

					case RANGE_MID :
						DoAction( "range_mid" );
						break;

					case RANGE_FAR :
						DoAction( "range_far" );
						break;
					}
				}
			}
		}
	else
		{
		lastEnemy = NULL;
		enemyRange = RANGE_FAR;
		}

   eyeposition[ 2 ] = maxs[ 2 ] + eyeoffset[ 2 ];
	angles.z = 0;

#ifdef DEBUG_PRINT
	gi.dprintf( "stack %d : %s : %s\n", numonstack, behavior ? behavior->getClassname() : "", animname.c_str() );
#endif
	if ( behavior && !behavior->Evaluate( *this ) )
		{
		EndBehavior();
		}

	if ( newanimnum != -1 )
		{
		ChangeAnim();
		}

	CalcMove();
   lastmove = STEPMOVE_STUCK;

   if ( flags & FL_SWIM )
      {
      lastmove = WaterMove();
      }
   else if ( flags & FL_FLY )
      {
      lastmove = AirMove();
      }
   else
      {
      lastmove = TryMove();
      }
   //
   // see if we should damage the actor because of waterlevel
   //
   if ( waterlevel == 3 && !( flags & FL_SWIM ) )
      {
		// if out of air, start drowning
		if ( air_finished < level.time )
			{
         // we may have been in a water brush when we spawned, so check our water level again to be sure
         CheckWater();
         if ( waterlevel < 3 )
            {
            // we're ok, so reset our air
            air_finished = level.time + 5;
            }
         else if ( next_drown_time < level.time && health > 0 )
				{
            // drown!
				next_drown_time = level.time + 1;

				RandomGlobalSound( "snd_uwchoke", 1, CHAN_VOICE, ATTN_NORM );
				ProcessEvent( EV_PainSound );

				Damage( world, world, 15, worldorigin, vec_zero, vec_zero, 0, DAMAGE_NO_ARMOR, MOD_DROWN, -1, -1, 1.0f );
				}
			}
      }
   else
		{
		air_finished = level.time + 5;
      }

	G_TouchTriggers( this );
	if ( groundentity && ( groundentity->entity != world ) && !M_CheckBottom( this ) )
		{
		// G_FixCheckBottom( this );
		flags |= FL_PARTIALGROUND;
		}
	}

/*****************************************************************************/
/*SINED info_monster_spawnspot (1 0 0) (-16 -16 0) (16 16 64)

Potential spawn location for a monster.

"spawngroup" - the name of the group of spawn spots that this one belongs to.
Monsters use spawngroup to choose which spawn spots to spawn at.

"angle"  - the orientation for the monster to spawn in.
"angles" - the full ( x, y, z ) orientation for the monster to spawn in.
"anim"  - the animation that the monster should use when spawning here.

/*****************************************************************************/

CLASS_DECLARATION( PathNode, MonsterStart, "info_monster_spawnspot" );

ResponseDef MonsterStart::Responses[] =
	{
		{ NULL, NULL }
	};

MonsterStart::MonsterStart()
	{
   spawngroup = G_GetSpawnArg( "spawngroup", "" );

	leader = NULL;
	leader = GetGroupLeader( spawngroup );
	if ( !leader )
		{
		leader = this;
		groupchain = NULL;
		}
	else
		{
		groupchain = leader->groupchain;
		leader->groupchain = this;
		}
	}

MonsterStart *MonsterStart::GetGroupLeader
	(
	str& groupname
	)

	{
	Entity *ent;
	MonsterStart *m;

	for( ent = world; ent; ent = G_NextEntity( ent ) )
		{
		if ( ent->isSubclassOf( MonsterStart ) )
			{
			m = ( MonsterStart * )ent;
			if ( ( m->spawngroup == groupname ) && m->leader )
				{
				return m->leader;
				}
			}
		}

	return NULL;
	}

MonsterStart *MonsterStart::GetRandomSpot
	(
	str& groupname
	)

	{
	MonsterStart *leader;
	MonsterStart *m;
	int num;
	int i;
	int j;

	leader = GetGroupLeader( groupname );
	if ( !leader )
		{
		return NULL;
		}
	
	num = 0;
	for( m = leader; m != NULL; m = m->groupchain )
		{
		num++;
		}

	j = ( int )G_Random( num );

	for( m = leader, i = 0; m != NULL; m = m->groupchain, i++ )
		{
		if ( i == j )
			{
			break;
			}
		}

	return m;
	}
