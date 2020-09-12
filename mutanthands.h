//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/mutanthands.h                       $
// $Revision:: 5                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 9/22/98 12:49p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/mutanthands.h                            $
// 
// 5     9/22/98 12:49p Markd
// Put in archive and unarchive functions
// 
// 4     6/10/98 10:02p Markd
// made mutant hands subclass of fists
// 
// 3     5/16/98 5:00p Markd
// Added flip variable
// 
// 2     5/11/98 11:25a Markd
// First time
// 
// 1     5/11/98 10:18a Markd
// 
// 1     5/11/98 9:55a Markd
// 
// DESCRIPTION:
// Mutant Hands
// 

#ifndef __MUTANTHANDS_H__
#define __MUTANTHANDS_H__

#include "g_local.h"
#include "item.h"
#include "weapon.h"
#include "fists.h"

class EXPORT_FROM_DLL MutantHands : public Fists
	{
	public:
		CLASS_PROTOTYPE( MutantHands );
		
							MutantHands::MutantHands();
	};

#endif /* MutantHands.h */
