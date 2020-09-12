//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/path.cpp                         $
// $Revision:: 33                                                             $
//   $Author:: Jimdose                                                        $
//     $Date:: 10/16/98 8:25p                                                 $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/path.cpp                              $
// 
// 33    10/16/98 8:25p Jimdose
// Added distanceToNextNode and dirToNextNode;
// Optimized ClosestPointOnPath, DistanceAlongPath, PointAtDistance
// 
// 32    10/16/98 1:53a Jimdose
// Added another NextNode function for finding the next node after the
// specified node
// 
// 31    10/14/98 10:18p Jimdose
// Made GetNode check for NULL nodes and error out
// 
// 30    10/14/98 10:16p Jimdose
// Added assert to GetNode to help find any NULL pointers in the list
// 
// 29    8/29/98 9:45p Jimdose
// Made SV_ commands begin with G_
// 
// 28    8/18/98 10:02p Jimdose
// Added NextNode
// 
// 27    6/04/98 10:48p Jimdose
// Fixed a bunch of things that got broken just in time for E3.  Paths and
// scripting actually work now.
// 
// 26    5/25/98 5:30p Jimdose
// Pathnodes are no longer a subclass of Entity.  This was done to save on
// edicts
// 
// 25    5/22/98 9:38p Jimdose
// working on ai
// 
// 24    5/20/98 6:37p Jimdose
// ClosestPointOnPath does a trace to see if the point is accessible
// 
// 23    5/18/98 8:14p Jimdose
// Renamed Navigator back to PathManager
// 
// 22    5/16/98 3:38p Jimdose
// Added ClosestPointOnPath, DistanceAlongPath, and PointAtDistance
// 
// 21    5/13/98 4:48p Jimdose
// PathList now uses SafePtr
// 
// 20    5/05/98 6:12p Jimdose
// removed spline test stuff
// 
// 19    5/05/98 2:38p Jimdose
// testing splines
// 
// 18    4/27/98 6:09p Jimdose
// Changed alpha on debug lines
// 
// 17    4/27/98 4:12p Jimdose
// Now use debug lines for drawing path instead of beams to cut down on net
// traffic
// 
// 16    4/16/98 2:08p Jimdose
// Rewrote to use new PathNode
// 
// 15    4/07/98 11:55p Jimdose
// Changed beams to specify color
// 
// 14    3/23/98 1:31p Jimdose
// Revamped event and command system
// 
// 13    3/05/98 3:49p Jimdose
// Made the pathinfo_t == operator EXPORT_FROM_DLL
// 
// 12    3/04/98 1:42p Jimdose
// Added pathinfo_t comparison function
// 
// 11    3/02/98 8:49p Jimdose
// Changed the classid parameter of CLASS_DECLARATION to a quoted string so
// that you could have a NULL classid.
// 
// 10    3/02/98 5:43p Jimdose
// Continued development on paths.  Now uses Path class to represent a path.
// 
// DESCRIPTION:
// 

#include "g_local.h"
#include "entity.h"
#include "path.h"
#include "container.h"
#include "navigate.h"
#include "misc.h"

CLASS_DECLARATION( Class, Path, NULL );

ResponseDef Path::Responses[] =
	{
		{ NULL, NULL }
	};

Path::Path()
	{
	pathlength = 0;
	from = NULL;
	to = NULL;
	nextnode = 1;
	}

Path::Path
	(
	int numnodes
	)

	{
	pathlength = 0;
	from = NULL;
	to = NULL;
	nextnode = 1;
	pathlist.Resize( numnodes );
   dirToNextNode.Resize( numnodes );
   distanceToNextNode.Resize( numnodes );
	}

void Path::Clear
	(
	void
	)

	{
	nextnode = 1;
	pathlength = 0;
	from = NULL;
	to = NULL;
	pathlist.FreeObjectList();
   dirToNextNode.FreeObjectList();
   distanceToNextNode.FreeObjectList();
	}

void Path::Reset
	(
	void
	)

	{
	nextnode = 1;
	}

PathNode *Path::Start
	(
	void
	)

	{
	return from;
	}

PathNode *Path::End
	(
	void
	)

	{
	return to;
	}

void Path::AddNode
	(
	PathNode *node
	)

	{
   Vector dir;
   float len;
	int num;

	if ( !from )
		{
		from = node;
		}

	to = node;
	pathlist.AddObject( PathNodePtr( node ) );

   len = 0;
   distanceToNextNode.AddObject( len );
   dirToNextNode.AddObject( vec_zero );

	num = NumNodes();
	if ( num > 1 )
		{
      dir = node->worldorigin - GetNode( num - 1 )->worldorigin;
      len = dir.length();
      dir *= 1 / len;

      distanceToNextNode.SetObjectAt( num - 1, len );
      dirToNextNode.SetObjectAt( num - 1, dir );

		pathlength += len;
		}
	}

PathNode *Path::GetNode
	(
	int num
	)

	{
   PathNode *node;

   node = pathlist.ObjectAt( num );
   assert( node != NULL );
   if ( node == NULL )
      {
      error( "GetNode", "Null pointer in node list\n" );
      }

	return node;
	}

PathNode	*Path::NextNode
	(
	void
	)

	{
	if ( nextnode <= NumNodes() )
		{
		return pathlist.ObjectAt( nextnode++ );
		}
	return NULL;
	}

PathNode	*Path::NextNode
	(
	PathNode	*node
	)

	{
   int i;
   int num;
   PathNode *n;

   num = NumNodes();

   // NOTE: We specifically DON'T check the last object (hence the i < num instead
   // of the usual i <= num, so don't go doing something stupid like trying to fix
   // this without keeping this in mind!! :)
   for( i = 1; i < num; i++ )
      {
		n = pathlist.ObjectAt( i );
      if ( n == node )
         {
         // Since we only check up to num - 1, it's ok to do this.
         // We do this since the last node in the list has no next node (duh!).
         return pathlist.ObjectAt( i + 1 );
         }
		}

	return NULL;
	}

Vector Path::ClosestPointOnPath
	(
	Vector pos
	)

	{
	PathNode	*s;
	PathNode	*e;
	int		num;
	int		i;
	float		bestdist;
	Vector	bestpoint;
	float		dist;
	float		segmentlength;
	Vector	delta;
	Vector	p1;
	Vector	p2;
	Vector	p3;
	float		t;

	num = NumNodes();
	s = GetNode( 1 );
	
	bestpoint = s->worldorigin;
	delta = bestpoint - pos;
	bestdist = delta * delta;

   for( i = 2; i <= num; i++ )
		{
		e = GetNode( i );

		// check if we're closest to the endpoint
		delta = e->worldorigin - pos;
		dist = delta * delta;

		if ( dist < bestdist )
			{
			bestdist = dist;
			bestpoint = e->worldorigin;
			}

		// check if we're closest to the segment
      segmentlength = distanceToNextNode.ObjectAt( i - 1 );
      p1 = dirToNextNode.ObjectAt( i - 1 );
		p2 = pos - s->worldorigin;

		t = p1 * p2;
		if ( ( t > 0 ) && ( t < segmentlength ) )
			{
			p3 = ( p1 * t ) + s->worldorigin;

			delta = p3 - pos;
			dist = delta * delta;
			if ( dist < bestdist )
				{
				bestdist = dist;
				bestpoint = p3;
				}
			}

		s = e;
		}

	return bestpoint;
	}

float Path::DistanceAlongPath
	(
	Vector pos
	)

	{
	PathNode	*s;
	PathNode	*e;
	int		num;
	int		i;
	float		bestdist;
	float		dist;
	float		segmentlength;
	Vector	delta;
	Vector	p1;
	Vector	p2;
	Vector	p3;
	float		t;
	float		pathdist;
	float		bestdistalongpath;

	pathdist = 0;

	num = NumNodes();
	s = GetNode( 1 );
	delta = s->worldorigin - pos;
	bestdist = delta * delta;
	bestdistalongpath = 0;

	for( i = 2; i <= num; i++ )
		{
		e = GetNode( i );

		segmentlength = distanceToNextNode.ObjectAt( i - 1 );

      // check if we're closest to the endpoint
		delta = e->worldorigin - pos;
		dist = delta * delta;

		if ( dist < bestdist )
			{
			bestdist = dist;
			bestdistalongpath = pathdist + segmentlength;
			}

		// check if we're closest to the segment
      p1 = dirToNextNode.ObjectAt( i - 1 );
		p2 = pos - s->worldorigin;

		t = p1 * p2;
		if ( ( t > 0 ) && ( t < segmentlength ) )
			{
			p3 = ( p1 * t ) + s->worldorigin;

			delta = p3 - pos;
			dist = delta * delta;
			if ( dist < bestdist )
				{
				bestdist = dist;
				bestdistalongpath = pathdist + t;
				}
			}

		s = e;

		pathdist += segmentlength;
		}

	return bestdistalongpath;
	}

Vector Path::PointAtDistance
	(
	float dist
	)

	{
	PathNode	*s;
	PathNode	*e;
	int		num;
	int		i;
	float		t;
	float		pathdist;
	float		segmentlength;

	num = NumNodes();
	s = GetNode( 1 );
	pathdist = 0;

	for( i = 2; i <= num; i++ )
		{
		e = GetNode( i );

      segmentlength = distanceToNextNode.ObjectAt( i - 1 );
		if ( ( pathdist + segmentlength ) > dist )
			{
			t = dist - pathdist;
			return s->worldorigin + dirToNextNode.ObjectAt( i - 1 ) * t;
			}

		s = e;
		pathdist += segmentlength;
		}

	// cap it off at start or end of path
	return s->worldorigin;
	}

PathNode *Path::NextNode
	(
	float dist
	)

	{
	PathNode	*s;
	PathNode	*e;
	int		num;
	int		i;
	float		pathdist;
	float		segmentlength;

	num = NumNodes();
	s = GetNode( 1 );
	pathdist = 0;

	for( i = 2; i <= num; i++ )
		{
		e = GetNode( i );

      segmentlength = distanceToNextNode.ObjectAt( i - 1 );
		if ( ( pathdist + segmentlength ) > dist )
			{
			return e;
			}

		s = e;
		pathdist += segmentlength;
		}

	// cap it off at start or end of path
	return s;
	}

void Path::DrawPath
	(
	float r,
	float g,
	float b,
	float time
	)

	{
	Vector	s;
	Vector	e;
	Vector	offset;
	PathNode	*node;
	int		num;
	int		i;

	num = NumNodes();

	if ( ai_debugpath->value )
		{
		gi.dprintf( "numnodes %d, len %d, nodes %d :", PathManager.NumNodes(), ( int )Length(), num );
		for( i = 1; i <= num; i++ )
			{
			node = GetNode( i );
			gi.dprintf( " %d", node->nodenum );
			}

		gi.dprintf( "\n" );
		}

	node = GetNode( 1 );
	s = node->worldorigin;

	offset = Vector( r, g, b ) * 4 + Vector( 0, 0, 20 );
	for( i = 2; i <= num; i++ )
		{
		node = GetNode( i );
		e = node->worldorigin;

		G_DebugLine( s + offset, e + offset, r, g, b, 1 );
		s = e;
		}
	}

int Path::NumNodes
	(
	void
	)

	{
	return pathlist.NumObjects();
	}

float Path::Length
	(
	void
	)

	{
	return pathlength;
	}
