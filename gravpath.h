//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/gravpath.h                       $
// $Revision:: 11                                                             $
//   $Author:: Jimdose                                                        $
//     $Date:: 10/25/98 11:53p                                                $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/gravpath.h                            $
// 
// 11    10/25/98 11:53p Jimdose
// added EXPORT_TEMPLATE
// 
// 10    10/21/98 2:18a Jimdose
// Added Reset to Unarchive
// 
// 9     10/07/98 11:51p Jimdose
// Added destructor for GravPathManager
// added Reset to GravPath::Unarchive 
// 
// 8     9/30/98 4:36p Aldie
// Added reset
// 
// 7     9/29/98 11:46p Aldie
// Added force spawnflag
// 
// 6     9/28/98 9:12p Markd
// Put in archive and unarchive functions
// 
// 5     8/27/98 2:54p Aldie
// Added a headnode flag
// 
// 4     8/27/98 2:31p Aldie
// Update active flag as a public var
// 
// 3     8/26/98 9:45p Aldie
// Added activate and deactivate
// 
// 2     5/22/98 12:19p Aldie
// First version of gravpath
//
// DESCRIPTION:
// Gravity path - Used for underwater currents and wells.

#ifndef __GRAVPATH_H__
#define __GRAVPATH_H__

#include "g_local.h"
#include "class.h"
#include "container.h"


class EXPORT_FROM_DLL GravPathNode : public Entity
   {
   private:
      float    speed;
      float    radius;
      qboolean headnode;
   
   public:
      qboolean       active; 

      CLASS_PROTOTYPE(GravPathNode);
                     GravPathNode();
      void           CreatePath(Event *ev); 
      void           Activate(Event *ev); 
      void           Deactivate(Event *ev); 
      float          Speed(void);
      float          Radius(void) {return radius;};
	   virtual void   Archive( Archiver &arc );
      virtual void   Unarchive( Archiver &arc );
   };

inline EXPORT_FROM_DLL void GravPathNode::Archive
	(
	Archiver &arc
	)
   {
   Entity::Archive( arc );

   arc.WriteFloat( speed );
   arc.WriteFloat( radius );
   arc.WriteBoolean( headnode );
   arc.WriteBoolean( active );
   }

inline EXPORT_FROM_DLL void GravPathNode::Unarchive
	(
	Archiver &arc
	)
   {
   Entity::Unarchive( arc );

   arc.ReadFloat( &speed );
   arc.ReadFloat( &radius );
   arc.ReadBoolean( &headnode );
   arc.ReadBoolean( &active );
   }

typedef SafePtr<GravPathNode> GravPathNodePtr;

//
// Exported templated classes must be explicitly instantiated
//
#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL SafePtr<GravPathNode>;
template class EXPORT_FROM_DLL Container<GravPathNodePtr>;
#endif

class EXPORT_FROM_DLL GravPath : public Listener
	{
	private:
		Container<GravPathNodePtr>	pathlist;
		float							   pathlength;
      
		GravPathNodePtr    	      from;
		GravPathNodePtr   		   to;
		int							   nextnode;
		
	public:
      CLASS_PROTOTYPE( GravPath );

						      GravPath();
                        ~GravPath();
		void			      Clear(void);
		void			      Reset(void);
		void			      AddNode(GravPathNode *node);
		GravPathNode      *GetNode(int num);
		GravPathNode      *NextNode(void);
		Vector		      ClosestPointOnPath(Vector pos, Entity &ent,float *bestdist,float *speed,float *radius);
		float			      DistanceAlongPath(Vector pos, float *speed);
		Vector		      PointAtDistance(float dist);
		void			      DrawPath(Event *ev);
		int			      NumNodes(void);
		float			      Length(void);
		GravPathNode		*Start(void);
		GravPathNode		*End(void);
	   virtual void      Archive( Archiver &arc );
      virtual void      Unarchive( Archiver &arc );

      Vector                     mins;
      Vector                     maxs;
      Vector                     origin;
      qboolean                   force;
	};

inline EXPORT_FROM_DLL void GravPath::Archive
	(
	Archiver &arc
	)

   {
   int i, num;

   Listener::Archive( arc );

   num = pathlist.NumObjects();
   arc.WriteInteger( num );
   for ( i = 1; i <= num; i++ )
      {
      arc.WriteSafePointer( pathlist.ObjectAt( i ) );
      }

   arc.WriteFloat( pathlength );
   arc.WriteSafePointer( from );
   arc.WriteSafePointer( to );
   arc.WriteInteger( nextnode );
   arc.WriteVector( mins );
   arc.WriteVector( maxs );
   arc.WriteVector( origin );
   arc.WriteBoolean( force );
   }

inline EXPORT_FROM_DLL void GravPath::Unarchive
	(
	Archiver &arc
	)

   {
   int i, num;

   Reset();

   Listener::Unarchive( arc );

   arc.ReadInteger( &num );
   pathlist.Resize( num );
   for ( i = 1; i <= num; i++ )
      {
      arc.ReadSafePointer( pathlist.AddressOfObjectAt( i ) );
      }

   arc.ReadFloat( &pathlength );
   arc.ReadSafePointer( &from );
   arc.ReadSafePointer( &to );
   arc.ReadInteger( &nextnode );
   arc.ReadVector( &mins );
   arc.ReadVector( &maxs );
   arc.ReadVector( &origin );
   arc.ReadBoolean( &force );
   }

#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL Container<GravPath *>;
#endif

class EXPORT_FROM_DLL GravPathManager : public Class
   {
	private:
	   Container<GravPath *>	pathList;

	public:
      CLASS_PROTOTYPE( GravPathManager );
               ~GravPathManager();
      void     Reset( void );
      void     AddPath(GravPath *p);
      void     RemovePath(GravPath *p);
      Vector   CalculateGravityPull(Entity &ent, Vector position, qboolean *force);
	   virtual void Archive( Archiver &arc );
      virtual void Unarchive( Archiver &arc );
   };

inline EXPORT_FROM_DLL void GravPathManager::Archive
	(
	Archiver &arc
	)
   {
   int i, num;

   Class::Archive( arc );

   num = pathList.NumObjects();
   arc.WriteInteger( num );
   for ( i = 1; i <= num; i++ )
      {
      arc.WriteObject( pathList.ObjectAt( i ) );
      }
   }

inline EXPORT_FROM_DLL void GravPathManager::Unarchive
	(
	Archiver &arc
	)
   {
   int i, num;

   Reset();

   Class::Unarchive( arc );

   arc.ReadInteger( &num );
   for ( i = 1; i <= num; i++ )
      {
      GravPath * ptr;

      ptr = new GravPath;
      arc.ReadObject( ptr );
      pathList.AddObject( ptr );
      }
   }

extern GravPathManager gravPathManager;

extern Event EV_DrawGravPath;

#endif /* gravpath.h */
