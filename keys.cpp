//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/keys.cpp                        $
// $Revision:: 24                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 11/15/98 4:30p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/keys.cpp                             $
// 
// 24    11/15/98 4:30p Markd
// don't play pulse part dialog if jc not present
// 
// 23    10/26/98 2:17p Aldie
// Updated evidence.def
// 
// 22    10/25/98 1:51a Aldie
// Added passcode2
// 
// 21    10/25/98 12:23a Markd
// Put in pulse parts
// 
// 20    10/23/98 10:15p Aldie
// Changed class name of identity card
// 
// 19    10/22/98 6:27p Aldie
// Fixed typo with identity card
// 
// 18    10/20/98 3:00a Aldie
// Set oldorigin of pulseparts
// 
// 17    10/19/98 12:05a Jimdose
// made all code use fast checks for inheritance (no text lookups when
// possible)
// isSubclassOf no longer requires ::_classinfo()
// moved ScubaGear to powerups.cpp
// 
// 16    10/17/98 6:58p Aldie
// Made pulseparts work
// 
// 15    10/16/98 11:01p Aldie
// Added Hand
// 
// 14    10/12/98 3:49p Aldie
// More items
// 
// 13    10/07/98 9:06p Aldie
// Added a bunch of inventory items
// 
// 12    9/07/98 6:20p Markd
// added inventory_dollar
// 
// 11    8/08/98 8:04p Markd
// Added money bag
// 
// 10    7/20/98 3:52p Aldie
// Fixed the icons
// 
// 9     7/19/98 5:40p Markd
// Added keyring
// 
// 8     7/19/98 5:32p Markd
// Added KeyRing
// 
// 7     7/19/98 3:43p Markd
// Added a setIcon for keys
// 
// 6     6/27/98 8:13p Markd
// Added additional inventory items
// 
// 5     6/25/98 8:47p Markd
// Added keyed items for Triggers, Rewrote Item class, rewrote every pickup
// method
// 
// DESCRIPTION:
// Access cards and keys

#include "inventoryitem.h" 
#include "player.h"

class EXPORT_FROM_DLL BlueCard : public InventoryItem
	{
	public:
      CLASS_PROTOTYPE( BlueCard );
                  BlueCard();
   };

CLASS_DECLARATION( InventoryItem, BlueCard, "inventory_bluecard" )

ResponseDef BlueCard::Responses[] =
	{
		{ NULL, NULL }
	};

BlueCard::BlueCard
	(
	)
	{
   setModel( "card_blu.def" );
	}


class EXPORT_FROM_DLL OrangeCard : public InventoryItem
	{
	public:
      CLASS_PROTOTYPE( OrangeCard );
                  OrangeCard();
   };

CLASS_DECLARATION( InventoryItem, OrangeCard, "inventory_orangecard" )

ResponseDef OrangeCard::Responses[] =
	{
		{ NULL, NULL }
	};

OrangeCard::OrangeCard
	(
	)
	{
   setModel( "card_orng.def" );
	}

class EXPORT_FROM_DLL YellowCard : public InventoryItem
	{
	public:
      CLASS_PROTOTYPE( YellowCard );
                  YellowCard();
   };

CLASS_DECLARATION( InventoryItem, YellowCard, "inventory_yellowcard" )

ResponseDef YellowCard::Responses[] =
	{
		{ NULL, NULL }
	};

YellowCard::YellowCard
	(
	)
	{
   setModel( "card_yel.def" );
	}

class EXPORT_FROM_DLL GreenCard : public InventoryItem
	{
	public:
      CLASS_PROTOTYPE( GreenCard );
                  GreenCard();
   };

CLASS_DECLARATION( InventoryItem, GreenCard, "inventory_greencard" )

ResponseDef GreenCard::Responses[] =
	{
		{ NULL, NULL }
	};

GreenCard::GreenCard
	(
	)
	{
   setModel( "card_grn.def" );
	}

class EXPORT_FROM_DLL IdentCard : public InventoryItem
	{
	public:
      CLASS_PROTOTYPE( IdentCard );
                  IdentCard();
   };

CLASS_DECLARATION( InventoryItem, IdentCard, "inventory_identcard" )

ResponseDef IdentCard::Responses[] =
	{
		{ NULL, NULL }
	};

IdentCard::IdentCard
	(
	)
	{
   setModel( "identcard.def" );
	}

class EXPORT_FROM_DLL Cookies : public InventoryItem
	{
	public:
      CLASS_PROTOTYPE( Cookies );
                  Cookies();
   };

CLASS_DECLARATION( InventoryItem, Cookies, "inventory_cookies" )

ResponseDef Cookies::Responses[] =
	{
		{ NULL, NULL }
	};

Cookies::Cookies
	(
	)
	{
   setModel( "cookies.def" );
	}

class EXPORT_FROM_DLL ComLink : public InventoryItem
	{
	public:
      CLASS_PROTOTYPE( ComLink );
                  ComLink();
   };

CLASS_DECLARATION( InventoryItem, ComLink, "inventory_comlink" )

ResponseDef ComLink::Responses[] =
	{
		{ NULL, NULL }
	};

ComLink::ComLink
	(
	)
	{
   setModel( "comlink.def" );
	}

class EXPORT_FROM_DLL Coin : public InventoryItem
	{
	public:
      CLASS_PROTOTYPE( Coin );
                  Coin();
   };

CLASS_DECLARATION( InventoryItem, Coin, "inventory_coin" )

ResponseDef Coin::Responses[] =
	{
		{ NULL, NULL }
	};

Coin::Coin
	(
	)
	{
   setModel( "coin.def" );
	}

class EXPORT_FROM_DLL Code : public InventoryItem
	{
	public:
      CLASS_PROTOTYPE( Code );
                  Code();
   };

CLASS_DECLARATION( InventoryItem, Code, "inventory_code" )

ResponseDef Code::Responses[] =
	{
		{ NULL, NULL }
	};

Code::Code
	(
	)
	{
   setModel( "code.def" );
	}

class EXPORT_FROM_DLL KeyRing : public InventoryItem
	{
	public:
      CLASS_PROTOTYPE( KeyRing );
                  KeyRing();
   };

CLASS_DECLARATION( InventoryItem, KeyRing, "inventory_keyring" )

ResponseDef KeyRing::Responses[] =
	{
		{ NULL, NULL }
	};

KeyRing::KeyRing
	(
	)
	{
   setModel( "keys.def" );
	}

class EXPORT_FROM_DLL MoneyBag : public InventoryItem
	{
	public:
      CLASS_PROTOTYPE( MoneyBag );
                  MoneyBag();
   };

CLASS_DECLARATION( InventoryItem, MoneyBag, "inventory_moneybag" )

ResponseDef MoneyBag::Responses[] =
	{
		{ NULL, NULL }
	};

MoneyBag::MoneyBag
	(
	)
	{
   setModel( "moneybag_inv.def" );
	}

class EXPORT_FROM_DLL Dollar : public InventoryItem
	{
	public:
      CLASS_PROTOTYPE( Dollar );
                  Dollar();
   };

CLASS_DECLARATION( InventoryItem, Dollar, "inventory_dollar" )

ResponseDef Dollar::Responses[] =
	{
		{ NULL, NULL }
	};

Dollar::Dollar
	(
	)
	{
   setModel( "dollar.def" );
	}

class EXPORT_FROM_DLL Evidence : public InventoryItem
	{
	public:
      CLASS_PROTOTYPE( Evidence );
                  Evidence();
   };

CLASS_DECLARATION( InventoryItem, Evidence, "inventory_evidence" )

ResponseDef Evidence::Responses[] =
	{
		{ NULL, NULL }
	};

Evidence::Evidence
	(
	)
	{
   setModel( "evidence.def" );
	}

class EXPORT_FROM_DLL Decoder : public InventoryItem
	{
	public:
      CLASS_PROTOTYPE( Decoder );
                  Decoder();
   };

CLASS_DECLARATION( InventoryItem, Decoder, "inventory_decoder" )

ResponseDef Decoder::Responses[] =
	{
		{ NULL, NULL }
	};

Decoder::Decoder
	(
	)
	{
   setModel( "code.def" );
	}

class EXPORT_FROM_DLL PulsePart1 : public InventoryItem
	{
	public:
      CLASS_PROTOTYPE( PulsePart1 );
                     PulsePart1();
      virtual Item   *ItemPickup( Entity *other );
   };

CLASS_DECLARATION( InventoryItem, PulsePart1, "inventory_pulsepart1" )

ResponseDef PulsePart1::Responses[] =
	{
		{ NULL, NULL }
	};

PulsePart1::PulsePart1
	(
	)
	{
   ExecuteThread( "global/pulse_parts.scr::precache", true );
   setModel( "pulsepart1.def" );
	}

Item *PulsePart1::ItemPickup
   (
   Entity *other
   )

   {    
   if ( !level.no_jc )
      ExecuteThread( "global/pulse_parts.scr::blade_finds_piece1", true );
   gameVars.CreateVariable( "pulse1", 1 );
   if ( other->isClient() )
      {
      Player *player;
      ScriptVariable	*var1,*var2,*var3;

      var1 = gameVars.GetVariable( "pulse1" );
      var2 = gameVars.GetVariable( "pulse2" );
      var3 = gameVars.GetVariable( "pulse3" );

      if ( var1 && var2 && var3 )
         {
         player = ( Player * )other;
         player->giveWeapon( "PulseRifle" );
         player->FreeInventoryOfType( "PulsePart2" );
         player->FreeInventoryOfType( "PulsePart3" );
	      CancelEventsOfType( EV_Item_DropToFloor );
	      CancelEventsOfType( EV_Item_Respawn );
         CancelEventsOfType( EV_FadeOut );
         PostEvent( EV_Remove, 0 );
         return NULL;
         }
      }
   return Item::ItemPickup( other );
   }

class EXPORT_FROM_DLL PulsePart2 : public InventoryItem
	{
	public:
      CLASS_PROTOTYPE( PulsePart2 );
                     PulsePart2();
      virtual Item   *ItemPickup( Entity *other );
   };

CLASS_DECLARATION( InventoryItem, PulsePart2, "inventory_pulsepart2" )

ResponseDef PulsePart2::Responses[] =
	{
		{ NULL, NULL }
	};

PulsePart2::PulsePart2
	(
	)
	{
   ExecuteThread( "global/pulse_parts.scr::precache", true );
   setModel( "pulsepart2.def" );
	}

Item *PulsePart2::ItemPickup
   (
   Entity *other
   )

   {
   if ( !level.no_jc )
      ExecuteThread( "global/pulse_parts.scr::blade_finds_piece2", true );
   gameVars.CreateVariable( "pulse2", 1 );
   if ( other->isClient() )
      {
      Player *player;
      ScriptVariable	*var1,*var2,*var3;

      var1 = gameVars.GetVariable( "pulse1" );
      var2 = gameVars.GetVariable( "pulse2" );
      var3 = gameVars.GetVariable( "pulse3" );

      if ( var1 && var2 && var3 )
         {
         player = ( Player * )other;
         player->giveWeapon( "PulseRifle" );
         player->FreeInventoryOfType( "PulsePart1" );
         player->FreeInventoryOfType( "PulsePart3" );
	      CancelEventsOfType( EV_Item_DropToFloor );
	      CancelEventsOfType( EV_Item_Respawn );
         CancelEventsOfType( EV_FadeOut );
         PostEvent( EV_Remove, 0 );
         return NULL;
         }
      }
   return Item::ItemPickup( other );
   }

class EXPORT_FROM_DLL PulsePart3 : public InventoryItem
	{
	public:
      CLASS_PROTOTYPE( PulsePart3 );
                     PulsePart3();
      virtual Item   *ItemPickup( Entity *other );
   };

CLASS_DECLARATION( InventoryItem, PulsePart3, "inventory_pulsepart3" )

ResponseDef PulsePart3::Responses[] =
	{
		{ NULL, NULL }
	};

PulsePart3::PulsePart3
	(
	)
	{
   ExecuteThread( "global/pulse_parts.scr::precache", true );
   setModel( "pulsepart3.def" );
	}

Item *PulsePart3::ItemPickup
   (
   Entity *other
   )

   {
   if ( !level.no_jc )
      ExecuteThread( "global/pulse_parts.scr::blade_finds_piece3", true );
   gameVars.CreateVariable( "pulse3", 1 );
   if ( other->isClient() )
      {
      Player *player;
      ScriptVariable	*var1,*var2,*var3;

      var1 = gameVars.GetVariable( "pulse1" );
      var2 = gameVars.GetVariable( "pulse2" );
      var3 = gameVars.GetVariable( "pulse3" );

      if ( var1 && var2 && var3 )
         {
         player = ( Player * )other;
         player->giveWeapon( "PulseRifle" );
         player->FreeInventoryOfType( "PulsePart1" );
         player->FreeInventoryOfType( "PulsePart2" );
	      CancelEventsOfType( EV_Item_DropToFloor );
	      CancelEventsOfType( EV_Item_Respawn );
         CancelEventsOfType( EV_FadeOut );
         PostEvent( EV_Remove, 0 );
         return NULL;
         }
      }
   return Item::ItemPickup( other );
   }

class EXPORT_FROM_DLL Chemsuit : public InventoryItem
	{
	public:
      CLASS_PROTOTYPE( Chemsuit );
                  Chemsuit();
   };

CLASS_DECLARATION( InventoryItem, Chemsuit, "inventory_chembiosuit" )

ResponseDef Chemsuit::Responses[] =
	{
		{ NULL, NULL }
	};

Chemsuit::Chemsuit
	(
	)
	{
   setModel( "chemsuit.def" );
	}

class EXPORT_FROM_DLL Blueprints : public InventoryItem
	{
	public:
      CLASS_PROTOTYPE( Blueprints );
                  Blueprints();
   };

CLASS_DECLARATION( InventoryItem, Blueprints, "inventory_blueprints" )

ResponseDef Blueprints::Responses[] =
	{
		{ NULL, NULL }
	};

Blueprints::Blueprints
	(
	)
	{
   setModel( "blueprints.def" );
	}

class EXPORT_FROM_DLL U4Sample : public InventoryItem
	{
	public:
      CLASS_PROTOTYPE( U4Sample );
                  U4Sample();
   };

CLASS_DECLARATION( InventoryItem, U4Sample, "inventory_u4sample" )

ResponseDef U4Sample::Responses[] =
	{
		{ NULL, NULL }
	};

U4Sample::U4Sample
	(
	)
	{
   setModel( "u4_sample.def" );
	}

class EXPORT_FROM_DLL Envelope : public InventoryItem
	{
	public:
      CLASS_PROTOTYPE( Envelope );
                  Envelope();
   };

CLASS_DECLARATION( InventoryItem, Envelope, "inventory_envelope" )

ResponseDef Envelope::Responses[] =
	{
		{ NULL, NULL }
	};

Envelope::Envelope
	(
	)
	{
   setModel( "envelope.def" );
	}

class EXPORT_FROM_DLL CandyBar : public InventoryItem
	{
	public:
      CLASS_PROTOTYPE( CandyBar );
                  CandyBar();
   };

CLASS_DECLARATION( InventoryItem, CandyBar, "inventory_candybar" )

ResponseDef CandyBar::Responses[] =
	{
		{ NULL, NULL }
	};

CandyBar::CandyBar
	(
	)
	{
   setModel( "CandyBar.def" );
	}

class EXPORT_FROM_DLL PassCode : public InventoryItem
	{
	public:
      CLASS_PROTOTYPE( PassCode );
                  PassCode();
   };

CLASS_DECLARATION( InventoryItem, PassCode, "inventory_passcode" )

ResponseDef PassCode::Responses[] =
	{
		{ NULL, NULL }
	};

PassCode::PassCode
	(
	)
	{
   setModel( "password.def" );
	}

class EXPORT_FROM_DLL PassCode2 : public InventoryItem
	{
	public:
      CLASS_PROTOTYPE( PassCode2 );
                  PassCode2();
   };

CLASS_DECLARATION( InventoryItem, PassCode2, "inventory_passcode2" )

ResponseDef PassCode2::Responses[] =
	{
		{ NULL, NULL }
	};

PassCode2::PassCode2
	(
	)
	{
   setModel( "password2.def" );
	}

class EXPORT_FROM_DLL Hand : public InventoryItem
	{
	public:
      CLASS_PROTOTYPE( Hand );
                  Hand();
   };

CLASS_DECLARATION( InventoryItem, Hand, "inventory_hand" )

ResponseDef Hand::Responses[] =
	{
		{ NULL, NULL }
	};

Hand::Hand
	(
	)
	{
   setModel( "hand.def" );
	}



/*SINED inventory_genericpulsepart (.3 1 .3) (-8 -8 0) (8 8 16) NOT_SOLID NOT_DAMAGABLE
Pulse Weapon Part - Will always spawn as the next piece that the user needs
to complete the weapon.  When the user picks up 3 of these, they will get the PulseRifle
*/

class EXPORT_FROM_DLL GenericPulsePart : public InventoryItem
	{
   
   public:
      CLASS_PROTOTYPE( GenericPulsePart );
                  GenericPulsePart();
   };

CLASS_DECLARATION( InventoryItem, GenericPulsePart, "inventory_genericpulsepart" )

ResponseDef GenericPulsePart::Responses[] =
	{
		{ NULL, NULL }
	};

GenericPulsePart::GenericPulsePart
	(
	)
	{
   ScriptVariable	*var1,*var2,*var3;

   var1 = gameVars.GetVariable( "pulse1" );
   var2 = gameVars.GetVariable( "pulse2" );
   var3 = gameVars.GetVariable( "pulse3" );

   // Based on what pulserifle pieces that have already been found,
   // spawn the correct model in the game.

   if ( !var1 )
      {
      PulsePart1 *part1;

      part1 = new PulsePart1;
      part1->setModel( "pulsepart1.def" );
      part1->setOrigin( origin );
      part1->worldorigin.copyTo(part1->edict->s.old_origin);
      }
   else if ( !var2 )
      {
      PulsePart2 *part2;

      part2 = new PulsePart2;
      part2->setModel( "pulsepart2.def" );
      part2->setOrigin( origin );
      part2->worldorigin.copyTo(part2->edict->s.old_origin);
      }
   else if ( !var3 )
      {
      PulsePart3 *part3;

      part3 = new PulsePart3;
      part3->setModel( "pulsepart3.def" );
      part3->setOrigin( origin );
      part3->worldorigin.copyTo(part3->edict->s.old_origin);
      }

   PostEvent( EV_Remove, 0 );
   }
