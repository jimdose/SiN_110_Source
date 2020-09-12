//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/secgun.h                            $
// $Revision:: 2                                                              $
//   $Author:: Markd                                                          $
//     $Date:: 10/21/98 12:05a                                                $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/secgun.h                                 $
// 
// 2     10/21/98 12:05a Markd
// First time
// 
// 1     10/20/98 11:35p Markd
// 
// DESCRIPTION:
// Securton Gun
// 

#ifndef __SECGUN_H__
#define __SECGUN_H__

#include "g_local.h"
#include "item.h"
#include "weapon.h"
#include "genericbullet.h"

class EXPORT_FROM_DLL Secgun : public GenericBullet
{
	public:
		CLASS_PROTOTYPE( Secgun );
		
								Secgun::Secgun();
		virtual void		Shoot( Event *ev );
	};

#endif /* ChainGun.h */
