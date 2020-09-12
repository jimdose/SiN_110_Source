//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/spidermine.cpp                      $
// $Revision:: 50                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 6/07/99 2:29p                                                  $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/spidermine.cpp                           $
// 
// 50    6/07/99 2:29p Markd
// fixed null pointer bug
// 
// 49    11/18/98 1:27a Jimdose
// Fixed sliding and orientation issues with gravaxis
// 
// 48    11/16/98 9:44p Jimdose
// fixed sticking on alternate gravaxis
// 
// 47    11/16/98 3:12a Jimdose
// mine takes gravity of owner
// 
// 46    11/15/98 10:31p Jimdose
// view of spidermine is now towards direction it's moving
// 
// 45    11/13/98 8:00p Markd
// Fixed spider mine bug with owner being reset to world too soon
// 
// 44    11/13/98 3:30p Markd
// put in more precaching on weapons
// 
// 43    11/13/98 2:35a Aldie
// Lowered the rank of spidermines
// 
// 42    11/11/98 5:12p Aldie
// Spidermine fix when player dies - don't drop it
// 
// 41    11/09/98 2:52a Aldie
// increase health
// 
// 40    11/09/98 12:12a Aldie
// Made it so you can reclaim your mines when you die, and mines are now shootable
// 
// 39    10/26/98 2:50p Aldie
// Fixed a bug with checking of NULL owners
// 
// 38    10/24/98 12:42a Markd
// changed origins to worldorigins where appropriate
// 
// 37    10/22/98 7:57p Markd
// put in proper pre-caching in all the classes
// 
// 36    10/22/98 4:33p Aldie
// Fix for spidermine and detonators
// 
// 35    10/21/98 12:09a Aldie
// Removed friction
// 
// 34    10/20/98 8:26p Markd
// Added Attacker to DamageSurface stuff
// 
// 33    10/19/98 12:07a Jimdose
// made all code use fast checks for inheritance (no text lookups when possible)
// isSubclassOf no longer requires ::_classinfo()
// 
// 32    10/16/98 10:22p Aldie
// Updated single player damage settings
// 
// 31    10/16/98 2:30p Aldie
// Check for NULL detonator
// 
// 30    10/10/98 9:14p Aldie
// Damage tweak and detonator tweak
// 
// 29    10/10/98 7:14p Aldie
// Tweaked damage
// 
// 28    10/08/98 12:03a Jimdose
// Got rid of unused variables speed and direction from Mine
// 
// 27    10/05/98 10:20p Aldie
// Changed damage a bit
// 
// 26    10/02/98 5:47p Aldie
// Add MOD to RadiusDamage
// 
// 25    9/18/98 8:14p Markd
// rewrote surface system so that surfaces are now damaged by surface name instead
// of by surfinfo
// 
// 24    9/13/98 8:37p Aldie
// Don't autoswitch to detonator
// 
// 23    9/11/98 3:19p Aldie
// Make mines bounce of entities that take damage.
// 
// 22    9/05/98 12:13p Aldie
// Made explosion driven by animation of the spidermine.
// 
// 21    9/01/98 7:53p Aldie
// Removed sound error
// 
// 20    9/01/98 7:46p Aldie
// Added area checking for spidermines
// 
// 19    9/01/98 3:05p Markd
// Rewrote explosion code
// 
// 18    8/29/98 9:46p Jimdose
// Added call info to G_Trace
// 
// 17    8/27/98 2:31p Aldie
// Fix for dead owner
// 
// 16    8/26/98 6:19p Aldie
// Update fov to 120 and remove the proximity stuff
// 
// 15    8/25/98 7:39p Aldie
// Made spidermine immediately switch to detonator.
// 
// 14    8/25/98 5:29p Aldie
// New version of the spidermine which uses cameras
// 
// 13    8/22/98 9:36p Jimdose
// Added support for alternate gravity axis
// 
// 12    8/18/98 11:08p Markd
// Added new Alias System
// 
// 11    7/25/98 7:10p Markd
// Put in EV_Removes for demo
// 
// 10    7/22/98 9:57p Markd
// Defined weapon type
// 
// 9     6/27/98 7:58p Aldie
// Minor adjustments to stuff
// 
// 8     6/19/98 9:30p Jimdose
// Moved gun orientation code to Weapon
// 
// 7     6/10/98 2:10p Aldie
// Updated damage function.
// 
// 6     6/08/98 9:04p Aldie
// Updated doneFiring event
// 
// 5     6/08/98 8:43p Aldie
// Added ReadyToUse support
// 
// 4     6/08/98 8:21p Aldie
// Updated spidermines with new anims and logic
// 
// 3     6/08/98 11:34a Aldie
// New version of spidermines.
// 
// 2     5/11/98 11:24a Markd
// First time
// 
// 1     5/11/98 11:10a Markd
// 
// 1     5/11/98 10:24a Markd
// 
// 1     5/11/98 10:20a Markd
// 
// 1     5/11/98 10:18a Markd
// 
// 1     5/11/98 9:55a Markd
// 
// DESCRIPTION:
// Spider Mine
// 

#include "g_local.h"
#include "spidermine.h"
#include "explosion.h"
#include "player.h"
#include "surface.h"

CLASS_DECLARATION( Projectile, Mine, "Mine" );

Event EV_Mine_Explode( "mine_explode" );
Event EV_Mine_CheckForTargets( "mine_targets" );
Event EV_Mine_Run( "mine_run" );

ResponseDef Mine::Responses[] =
	{
	   { &EV_Touch,				         ( Response )Mine::SlideOrStick },
      { &EV_Killed,				         ( Response )Mine::Explode },
	   { &EV_Mine_Explode,	            ( Response )Mine::Explode },
      { &EV_Trigger_Effect,				( Response )Mine::SlideOrStick },
      { &EV_Mine_CheckForTargets,   	( Response )Mine::CheckForTargets },
      { &EV_Mine_Run,                	( Response )Mine::Run },
		{ NULL, NULL }
	};


void Mine::Run
   (
   Event *ev
   )

   {
   RandomAnimate( "run", NULL );
   }

void Mine::CheckForTargets
   (
   Event *ev
   )
   
   {
   Entity      *ent;
   Event       *event;
   trace_t     trace;

   // Playtest
   return;

   if (detonate)
      return;

   ent = findradius( NULL, worldorigin, 150 );
	while( ent )
		{
		if ( ( ent != this ) && 
           ( !ent->deadflag ) && 
           ( ent->entnum != owner ) &&
           ( ent->takedamage ) && 
           ( !(ent->flags & FL_NOTARGET) ) && 
           ( strcmp(ent->getClassname(),"Mine") ) )
			{
 			detonate = true;
         trace = G_Trace( worldorigin, vec_zero, vec_zero, ent->worldorigin, ent, MASK_PROJECTILE, "Mine::CheckForTargets" );
         if (trace.fraction != 1.0f)
            detonate = false;
         else
            break;
			}
		ent = findradius( ent, worldorigin, 150 );
		}

   if (detonate)
      {
      RandomGlobalSound("spider_arm",1);
      event = new Event(EV_Mine_Explode);
      PostEvent(event,0.5f);
      }
   else
      {
      event = new Event(EV_Mine_CheckForTargets);
      PostEvent(event,0.5f);
      }
   }


void Mine::SlideOrStick
   (
   Event *ev
   )

   {
   Entity   *other;
   Event    *event;
   Vector   norm;
   Vector   addSpeed;

   if (detonate)
      return;

	other = ev->GetEntity( 1 );
	assert( other );

   if ( other->takedamage )
		{
      setMoveType(MOVETYPE_BOUNCE);
      return;
		}
    
   // Check to see if we hit the ground, if so then slide along,
   // otherwise stick to the wall.
   if (( (level.impact_trace.plane.normal[ gravity_axis[ gravaxis ].z ] * gravity_axis[ gravaxis ].sign ) > 0.7 ) && 
     !sticky)
      {
      setMoveType(MOVETYPE_SLIDE);
      event = new Event(EV_Mine_CheckForTargets);
      PostEvent(event,2.5);
      }
   else
      {
      // So that we can shoot our own mines
	   edict->owner = world->edict;

      CancelEventsOfType(EV_Mine_Run);
      setMoveType(MOVETYPE_NONE);
      RandomAnimate( "stick", NULL );
      norm = level.impact_trace.plane.normal;
      angles = norm.toAngles();
      angles.x = -angles.x;
      setAngles(angles);
      velocity = "0 0 0";

      // Check to see if we are on the floor and adjust origin
      if (!sticky)
         {
         CheckGround();
         if (groundentity)
            setOrigin(origin + "0 0 12" );
         }

      setOrigin(origin);
      event = new Event(EV_Mine_CheckForTargets);
      PostEvent(event,0.7f);
      }
   }


void Mine::Explode
   (
   Event *ev
   )
   {
	int			damg;
	Vector		v;
   Vector		norm;
   Player      *client;
   Camera      *cam;
   Entity      *owner;


   detonate = true;
   takedamage = DAMAGE_NO;

   stopsound( CHAN_VOICE );
	setSolidType( SOLID_NOT );

   if ( HitSky() )
		{
		PostEvent( EV_Remove, 0 );
		return;
		}

   owner = G_GetEntity( this->owner );

   if ( !owner )
      owner = world;

   damg = 100;

   if ( !deathmatch->value && owner->isClient() )
      damg *= 1.5;

   surfaceManager.DamageSurface (&level.impact_trace, damg, owner );

   v = velocity;
	v.normalize();
   v = worldorigin - v * 24;

   RadiusDamage( this, owner, damg, this, MOD_SPIDERSPLASH );

   if ( owner->isSubclassOf( Player ) )
      {
      client = ( Player * )owner;
      cam = client->CurrentCamera();
   
      // If we are in the camera, get out of it
      if ( cam == ( Camera * )this )
         client->SetCamera( NULL );
      }

   // Remove the mine from the detonator
   if ( detonator )
      detonator->RemoveMine( this );

   RandomAnimate( "explode", NULL );
   PostEvent( EV_Remove, 0.2 );
   }

void Mine::SetDetonator
   (
   Detonator *det
   )

   {
   detonator = det;
   }

qboolean Mine::IsOwner
   (
   Sentient *sent
   )

   {
   return ( sent == G_GetEntity( this->owner ) );
   }

void Mine::Setup
   (
   Entity *owner,
   Vector pos,
	Vector dir
   )

   {
   Event *ev;
	Vector t[ 3 ];
	Vector forward;
	Vector right;
	Vector up;

   this->owner  = owner->entnum;

	edict->owner = owner->edict;

   setModel( "spidermine.def" );
   
   showModel();
   setMoveType( MOVETYPE_SLIDE );
   setSolidType( SOLID_BBOX );
   edict->clipmask = MASK_PROJECTILE;
   RandomAnimate( "open", EV_Mine_Run );

   SetGravityAxis( owner->gravaxis );
   velocity = dir * 600;
   sticky = false;

   const gravityaxis_t &grav = gravity_axis[ gravaxis ];

   setAngles( Vector( 0, dir.toYaw(), 0 ) );

   angles.AngleVectors( &t[0], &t[1], &t[2] );
	forward[ grav.x ] = t[ 0 ][ 0 ];
	forward[ grav.y ] = t[ 0 ][ 1 ] * grav.sign;
	forward[ grav.z ] = t[ 0 ][ 2 ] * grav.sign;
	right[ grav.x ] = t[ 1 ][ 0 ];
	right[ grav.y ] = t[ 1 ][ 1 ] * grav.sign;
	right[ grav.z ] = t[ 1 ][ 2 ] * grav.sign;
	up[ grav.x ] = t[ 2 ][ 0 ];
	up[ grav.y ] = t[ 2 ][ 1 ] * grav.sign;
	up[ grav.z ] = t[ 2 ][ 2 ] * grav.sign;
	VectorsToEulerAngles( forward.vec3(), right.vec3(), up.vec3(), angles.vec3() );
   setAngles( angles );
   
 	ev = new Event( EV_Mine_Explode );
	ev->AddEntity( world );
	PostEvent( ev, 180 );

 	takedamage = DAMAGE_YES;
	health = 150;
   edict->svflags |= ( SVF_SHOOTABLE );
   setSize("-4 -4 -4", "4 4 4");
   
   setOrigin( pos );
   worldorigin.copyTo(edict->s.old_origin);
   detonate = false;

   fov = 120;

	if ( owner->isClient() && owner->client->ps.pmove.pm_flags & PMF_DUCKED )
      {
      setMoveType( MOVETYPE_TOSS );
      sticky = true;
      }
   }

CLASS_DECLARATION( Weapon, SpiderMine, NULL);

ResponseDef SpiderMine::Responses[] =
	{
	   { &EV_Weapon_Shoot,              ( Response )SpiderMine::Shoot },
      { &EV_Weapon_DoneFiring,         ( Response )SpiderMine::DoneFiring },
      { &EV_Weapon_SecondaryUse,       ( Response )SpiderMine::ChangeToDetonator },
      { NULL, NULL }
	};

SpiderMine::SpiderMine
   (
   )

	{
#ifdef SIN_DEMO
   PostEvent( EV_Remove, 0 );
   return;
#endif
	SetModels( "mines.def", "view_mines.def" );
	SetAmmo( "SpiderMines", 1, 0 );
	SetRank( 60, 5 );
   SetType( WEAPON_1HANDED );
   modelIndex( "spidermine.def" );
   modelIndex( "mine.def" );

   currentMine = 0;
	}

qboolean SpiderMine::IsDroppable
	(
	void
	)
	{
	return false;
   }

void SpiderMine::SetOwner
	(
	Sentient *sent
	)

	{
   Detonator   *detonator;
   int         num;

   assert( sent );
	if ( !sent )
		{
		// return to avoid any buggy behaviour
		return;
		}

	Item::SetOwner( sent );

	setOrigin( vec_zero );
   setAngles( vec_zero );

	if ( !viewmodel.length() )
		{
		error( "setOwner", "Weapon without viewmodel set" );
		}

	setModel( viewmodel );

   // Give the owner a detonator and setup the link

   detonator = ( Detonator * )sent->FindItem( "Detonator" );
   
   if ( !detonator )
      {
      detonator = ( Detonator * )sent->giveWeapon( "Detonator" );
      }

   SetDetonator( detonator );


   // Check the world for any spidermines in existence and 
   // if the player owns them, add them to the minelist.
   num = 0;
	while( ( num = G_FindClass( num, "Mine" ) ) != NULL )
		{
		Mine *mine = ( Mine * )G_GetEntity( num );

      if ( mine->IsOwner( sent ) )
         {
         detonator->AddMine( mine );
         mine->SetDetonator( detonator );
         }
      }
	}

void SpiderMine::DoneFiring
   (
   Event *ev
   )

   {
   assert( owner );
	
   weaponstate = WEAPON_HOLSTERED;
   DetachGun();
	StopAnimating();

	if ( owner )
		{
		owner->SetCurrentWeapon( detonator );
		}
   }

void SpiderMine::ChangeToDetonator
   (
   Event *ev
   )

   {   
   if ( owner && detonator->mineList.NumObjects() )
      owner->ChangeWeapon( detonator );
   }

qboolean SpiderMine::ReadyToUse
	(
	void
	)

	{
   Event *ev;

   if ( HasAmmo() )
      {
      return true;
      }
   else
      {
      if ( owner->isClient() )
         {    
         // Check to see if detonator has mines active
         if ( detonator && detonator->mineList.NumObjects() )
            {
            ev = new Event( "use" );
            ev->AddString( "Detonator" );
            owner->PostEvent( ev, 0 );
            }
         }
      return false;
      }
	}

void SpiderMine::SetDetonator
   ( 
   Detonator *det
   )

   {
   detonator = det;
   }

void SpiderMine::Shoot
	(
	Event *ev
	)

	{
 	Vector	pos;
	Vector	dir;
   Mine     *mine;
   Event    *event;

	assert( owner );
	if ( !owner )
		{
		return;
		}

	GetMuzzlePosition( &pos, &dir );


   if ( currentMine )
      {
      event = new Event(EV_Mine_Explode);
      currentMine->ProcessEvent( event );
      }
   else
      {
     	mine = new Mine;
   	mine->Setup( owner, pos, dir );
      mine->SetDetonator( detonator );
      detonator->AddMine( mine );   
      }

	NextAttack( 1.8f );
   }

CLASS_DECLARATION( Weapon, Detonator, NULL);

ResponseDef Detonator::Responses[] =
	{
	   { &EV_Weapon_Shoot,              ( Response )Detonator::Shoot },
      { &EV_Weapon_DoneFiring,         ( Response )Detonator::DoneFiring },
      { &EV_Weapon_SecondaryUse,       ( Response )Detonator::CycleCamera },
      { NULL, NULL }
	};

Detonator::Detonator
   (
   )

   {
#ifdef SIN_DEMO
   PostEvent( EV_Remove, 0 );
   return;
#endif
   SetModels( NULL, "view_detonator.def" );
   SetType( WEAPON_1HANDED );
   currentMine = 0;
   }

void Detonator::RemoveMine
   (
   Mine *mine
   )

   {
   mineList.RemoveObject( MinePtr( mine ) );
   }

void Detonator::AddMine
   (
   Mine *mine
   )

   {
   mineList.AddObject( MinePtr( mine ) );
   }

void Detonator::CycleCamera
   ( 
   Event *ev 
   )

   {
   Player      *client;
   int         numMines;
   Mine        *mine;
   
   assert( owner );
	if ( !owner )
		{
		return;
		}

   numMines = mineList.NumObjects();

   if ( !numMines )
      return;

   currentMine++;
   
   mine = mineList.ObjectAt( ( currentMine % numMines ) + 1 );
   if ( !mine )
      {
      mineList.RemoveObjectAt( ( currentMine % numMines ) + 1 );
      return;
      }
   
   client = ( Player * )( Entity * ) owner;
   if ( client->edict->areanum == mine->edict->areanum )
      client->SetCamera( mine );
   else
      {
      gi.cprintf(client->edict, PRINT_HIGH, "Spidermine %d out of range\n", ( currentMine % numMines ) + 1 );
      }
   }

void Detonator::DoneFiring
   (
   Event *ev
   )

   {
   Weapon *weapon;

	weaponstate = WEAPON_READY;

	if ( owner )
		{
		owner->ProcessEvent( EV_Sentient_WeaponDoneFiring );
		}

   // Change back to spidermines if there is ammo, otherwise change weapons.

   weapon = ( Weapon * )owner->FindItem( "SpiderMine" );
   
   if ( !weapon || !weapon->HasAmmo() )
      {
      weapon = owner->BestWeapon();
      }

   owner->ChangeWeapon( weapon );
   }

void Detonator::Shoot
   (
   Event *ev
   )

   {
   int      num,i;
   Player   *player;
   Entity   *cameraMine;
   Event    *event;
   
   // If the owner is in a camera, the only detonate that mine, 
   // otherwise detonate them all

 	NextAttack( 0.1 );

   if ( owner->isClient() )
      {
      player = ( Player * )( Entity * )owner;

      cameraMine = player->CurrentCamera();
      
      if ( cameraMine && cameraMine->isSubclassOf( Mine ) )
         {
         event = new Event(EV_Mine_Explode);
         cameraMine->PostEvent( event, 0 );
         return;
         }
      }
   
   // Go through all the mines and detonate them 

   num = mineList.NumObjects();

	for( i = num; i >= 1; i-- )
      {
      Event *explodeEvent;
      Mine  *mine;

      mine = mineList.ObjectAt( i );
      explodeEvent = new Event(EV_Mine_Explode);
      mine->PostEvent( explodeEvent, 0 );
      }
   }

qboolean Detonator::IsDroppable
	(
	void
	)
	{
	return false;
   }

qboolean Detonator::AutoChange
   (
   void
   )

   {
   return false;
   }
