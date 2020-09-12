//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/path.h                           $
// $Revision:: 22                                                             $
//   $Author:: Jimdose                                                        $
//     $Date:: 10/25/98 11:53p                                                $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/path.h                                $
// 
// 22    10/25/98 11:53p Jimdose
// added EXPORT_TEMPLATE
// 
// 21    10/16/98 8:24p Jimdose
// Added distanceToNextNode and dirToNextNode;
// Optimized ClosestPointOnPath, DistanceAlongPath, PointAtDistance
// 
// 20    10/16/98 1:54a Jimdose
// Added another NextNode function for finding the next node after the
// specified node
// 
// 19    9/22/98 12:49p Markd
// Put in archive and unarchive functions
// 
// 18    8/18/98 10:02p Jimdose
// Added NextNode
// 
// 17    5/26/98 7:56p Jimdose
// added scripted cameras
// 
// 16    5/20/98 6:39p Jimdose
// Made ClosestPointOnPath accept an Entity to do a trace for
// 
// 15    5/16/98 3:38p Jimdose
// Added ClosestPointOnPath, DistanceAlongPath, and PointAtDistance
// 	
// 
// 14    5/13/98 4:50p Jimdose
// Added use of SafePtrs
// 
// 13    4/16/98 2:10p Jimdose
// Now uses PathNode as path point
// 
// 12    3/05/98 3:49p Jimdose
// Made the pathinfo_t == operator EXPORT_FROM_DLL
// 
// 11    3/04/98 1:42p Jimdose
// Added pathinfo_t comparison function
// 
// 10    3/02/98 8:49p Jimdose
// Changed CLASS_PROTOTYPE to only take the classname
// 
// 9     3/02/98 5:43p Jimdose
// Continued development on paths.  Now uses Path class to represent a path.
//
// DESCRIPTION:
// 

#ifndef __PATH_H__
#define __PATH_H__

#include "g_local.h"
#include "class.h"
#include "container.h"
#include "navigate.h"

//
// Exported templated classes must be explicitly instantiated
//
#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL Container<PathNodePtr>;
template class EXPORT_FROM_DLL Container<float>;
template class EXPORT_FROM_DLL Container<Vector>;
#endif

class EXPORT_FROM_DLL Path : public Class
	{
	private:
		Container<PathNodePtr>	pathlist;
      Container<float>	      distanceToNextNode;
      Container<Vector>	      dirToNextNode;
		float							pathlength;
		PathNodePtr					from;
		PathNodePtr					to;
		int							nextnode;
		
	public:
      CLASS_PROTOTYPE( Path );

						Path();
						Path( int numnodes );
		void			Clear( void );
		void			Reset( void );
		void			AddNode( PathNode *node );
		PathNode		*GetNode( int num );
		PathNode		*NextNode( void );
      PathNode		*NextNode( PathNode *node );
		Vector		ClosestPointOnPath( Vector pos );
		float			DistanceAlongPath( Vector pos );
		Vector		PointAtDistance( float dist );
		PathNode		*NextNode( float dist );
		void			DrawPath( float r, float g, float b, float time );
		int			NumNodes( void );
		float			Length( void );
		PathNode		*Start( void );
		PathNode		*End( void );
	   virtual void Archive( Archiver &arc );
      virtual void Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Path::Archive
	(
	Archiver &arc
	)
   {
   PathNodePtr ptr;
   int i, num;

   Class::Archive( arc );

   num = pathlist.NumObjects();
   arc.WriteInteger( num );
   for ( i = 1; i <= num; i++ )
      {
      ptr = pathlist.ObjectAt( i );
      arc.WriteSafePointer( ptr );
      }

   arc.WriteFloat( pathlength );
   arc.WriteSafePointer( from );
   arc.WriteSafePointer( to );
   arc.WriteInteger( nextnode );
   }

inline EXPORT_FROM_DLL void Path::Unarchive
	(
	Archiver &arc
	)
   {
   PathNodePtr *ptr;
   PathNodePtr node;
   float len;
   Vector dir;
   int i, num;

   Class::Unarchive( arc );

   pathlist.FreeObjectList();
   distanceToNextNode.FreeObjectList();
   dirToNextNode.FreeObjectList();

   arc.ReadInteger( &num );
   for( i = 1; i <= num; i++ )
      {
      pathlist.AddObject( node );
      ptr = pathlist.AddressOfObjectAt( i );
      arc.ReadSafePointer( ptr );
      }

   // Recalculate the path distances and directions
   // only go up to the node before the last node.
   for( i = 1; i < num; i++ )
      {
      dir = pathlist.ObjectAt( i + 1 )->worldorigin - pathlist.ObjectAt( i )->worldorigin;
      len = dir.length();
      dir *= 1 / len;

      distanceToNextNode.SetObjectAt( i, len );
      dirToNextNode.SetObjectAt( i, dir );
      }

   if ( num )
      {
      // special case for last node
      len = 0;
      distanceToNextNode.AddObject( len );
      dirToNextNode.AddObject( vec_zero );
      }

   arc.ReadFloat( &pathlength );
   arc.ReadSafePointer( &from );
   arc.ReadSafePointer( &to );
   arc.ReadInteger( &nextnode );
   }


#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL SafePtr<Path>;
#endif
typedef SafePtr<Path> PathPtr;

#endif /* path.h */
