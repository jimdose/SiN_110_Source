//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/navigate.h                       $
// $Revision:: 42                                                             $
//   $Author:: Markd                                                          $
//     $Date:: 11/18/98 7:47p                                                 $
//
// Copyright (C) 1998 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/navigate.h                            $
// 
// 42    11/18/98 7:47p Markd
// Allowed nearestnode to ignore entity bbox
// 
// 41    11/08/98 6:34p Jimdose
// added SetNodeFlagsEvent
// 
// 40    10/26/98 6:32p Jimdose
// added fulltest to CheckPath and ClearPathTo
// 
// 39    10/26/98 5:16p Jimdose
// Added CalcPath and DisconnectPath
// 
// 38    10/26/98 4:42p Jimdose
// added recalcpaths
// 
// 37    10/25/98 11:53p Jimdose
// added EXPORT_TEMPLATE
// 
// 36    10/18/98 3:22a Jimdose
// Added code for timing paths
// 
// 35    10/14/98 10:59p Jimdose
// map name is now passed into Init
// 
// 34    10/14/98 5:22p Markd
// Changed jumptarget to target
// 
// 33    9/22/98 12:49p Markd
// Put in archive and unarchive functions
// 
// 32    9/18/98 10:59p Jimdose
// Started on swimming actors
// 
// 31    9/14/98 5:40p Jimdose
// NearestNode now requires that you pass in the entity that is going to use
// the path.
// NearestNode no longer hard codes the size when testing moves
// Added ai_shownodenums
// Revamped tests for valid paths.  Actors get stuck much less often.
// Made DrawAllConnections more usefull.
// ClearPathTo now uses binary search for finding the max height of a path.
// Upped version number
// Added FindEntities to fixup door entity numbers when loading pathfiles
// Fixed definition of MAX_WIDTH (it was still multiplied by 2 from the way it
// used to work).
// 
// 30    9/08/98 9:51p Jimdose
// Changed NUM_PATHSPERNODE and NUM_WIDTH_VALUES
// Made CHECK_PATH use a granularity of 8 instead of 16
// 
// 29    9/03/98 9:12p Jimdose
// made paths aware of doors
// 
// 28    8/29/98 9:53p Jimdose
// moved prototype of SV_TestMovestep to g_phys.h
// 
// 27    8/24/98 6:58p Jimdose
// Added array of heights for each width that a path supports
// 
// 26    8/19/98 7:59p Jimdose
// Began adding support for ladder and jump nodes
// 
// 25    8/18/98 10:03p Jimdose
// Separated checks for connection from checks for near nodes so that non-door
// nodes will not connect to nodes through doors
// 
// 24    8/15/98 5:32p Jimdose
// Increased MAX_PATHNODES
// 
// 23    7/26/98 6:42a Jimdose
// Added entnum to pathnode
// 
// 22    7/26/98 5:37a Jimdose
// added occupiedTime
// 
// 21    7/26/98 2:41a Jimdose
// Path files moved to maps directory
// Path files now contain full connection information to improve load times
// 
// 20    7/25/98 2:10a Jimdose
// Preparing for door nodes
// 
// 19    7/17/98 8:34p Jimdose
// Fixed bug where CreatePath would overwrite the stack if the path was longer
// than MAX_PATH_LENGTH
// 
// 18    6/13/98 8:21p Jimdose
// Moved search algorithm to separate object - PathFinder
// Removed optimize path stuff
// Added maxwidth and maxheight to paths
// 
// 17    6/09/98 5:32p Jimdose
// added ai_maxnode
// 
// 16    5/27/98 5:11a Jimdose
// working on ai
// 
// 15    5/25/98 5:31p Jimdose
// Pathnodes are no longer a subclass of Entity.  This was done to save on
// edicts
// 
// 14    5/22/98 9:40p Jimdose
// Made paths check through Movers
// 
// 13    5/18/98 8:14p Jimdose
// Renamed Navigator back to PathManager
// 
// 12    5/14/98 10:26p Jimdose
// Added UpdateNode
// Made alot of info in PathNode private
// 
// 11    5/13/98 4:50p Jimdose
// Added use of SafePtrs
// 
// 10    5/09/98 8:04p Jimdose
// added path saving and loading
// PathSearch now a Listener instead of a Class object
// 
// 9     5/07/98 10:43p Jimdose
// added archiving
// 
// 8     4/29/98 5:39p Jimdose
// added ai_checkroutes
// 
// 7     4/27/98 5:27p Jimdose
// working on ai
// 
// 6     4/20/98 2:45p Jimdose
// working on ai
// 
// 5     4/18/98 3:02p Jimdose
// Added ai_createnodes and ai_showpath	
// working on ai
// 
// 4     4/16/98 2:10p Jimdose
// Major rewrite
// 
// 3     3/02/98 8:49p Jimdose
// Changed CLASS_PROTOTYPE to only take the classname
// 
// 2     3/02/98 5:44p Jimdose
// Continued development.  Now use Path class to represent finished paths.
// 
// 1     2/25/98 2:27p Jimdose
// 
// 8     2/21/98 1:07p Jimdose
// Updated for Q2 dlls
// 
// 6     12/06/97 6:32p Jimdose
// Further evolution on path code.
// 
// 5     11/12/97 2:11p Jimdose
// Simplified the interface to PathSearch
// 
// 4     11/07/97 6:39p Jimdose
// More work on integrating with Sin
// 
// 3     11/05/97 4:00p Jimdose
// More work converting to work with Sin.
// 
// 2     9/26/97 6:14p Jimdose
// Added standard Ritual headers
//
// DESCRIPTION:
// Potentially could be an C++ implementation of the A* search algorithm, but
// is currently unfinished.
// 

#ifndef __NAVIGATE_H__
#define __NAVIGATE_H__

#include "g_local.h"
#include "class.h"
#include "entity.h"
#include "stack.h"
#include "container.h"
#include "doors.h"

extern Event EV_AI_SavePaths;
extern Event EV_AI_SaveNodes;
extern Event EV_AI_LoadNodes;
extern Event EV_AI_ClearNodes;
extern Event EV_AI_RecalcPaths;
extern Event EV_AI_CalcPath;
extern Event EV_AI_DisconnectPath;

extern cvar_t	*ai_createnodes;
extern cvar_t	*ai_showpath;
extern cvar_t	*ai_shownodes;
extern cvar_t	*ai_debugpath;
extern cvar_t	*ai_debuginfo;
extern cvar_t	*ai_showroutes;
extern cvar_t  *ai_timepaths;

extern int		ai_maxnode;

#define MAX_PATHCHECKSPERFRAME 4

extern int path_checksthisframe;

#define MAX_PATH_LENGTH		128		// should be more than plenty
#define NUM_PATHSPERNODE	16

class Path;
class PathNode;

#define NUM_WIDTH_VALUES	16
#define WIDTH_STEP			8
#define MAX_WIDTH				( WIDTH_STEP * NUM_WIDTH_VALUES )
#define MAX_HEIGHT			128

#define CHECK_PATH( path, width, height ) \
	( ( ( ( width ) >= MAX_WIDTH ) || ( ( width ) < 0 ) ) ? false : \
	( ( int )( path )->maxheight[ ( ( width ) / WIDTH_STEP ) - 1 ] < ( int )( height ) ) )

typedef struct
	{
	short			node;
	short			moveCost;
	byte			maxheight[ NUM_WIDTH_VALUES ];
	int			door;
	} pathway_t;

typedef enum { NOT_IN_LIST, IN_OPEN, IN_CLOSED } pathlist_t;

#define AI_FLEE		1
#define AI_DUCK		2
#define AI_COVER		4
#define AI_DOOR		8
#define AI_JUMP		16
#define AI_LADDER		32
#define AI_ACTION    64

void EXPORT_FROM_DLL DrawAllConnections( void );

class EXPORT_FROM_DLL PathNode : public Listener
	{
	public:
		PathNode			*chain;
		pathway_t		Child[ NUM_PATHSPERNODE ];	// these are the real connections between nodex
		int				numChildren;

		// These variables are all used during the search
		int				f;
		int				h;
		int				g;

		int				gridX;
		int				gridY;

		float				drawtime;
		float				occupiedTime;
		int				entnum;

		pathlist_t		inlist;
	
		// reject is used to indicate that a node is unfit for ending on during a search
		qboolean			reject;

		PathNode			*Parent;

		// For the open and closed lists
		PathNode			*NextNode;

		int				nodeflags;

		friend class   PathSearch;
		friend void		DrawAllConnections( void );

	private :
      qboolean       TestMove( Entity *ent, Vector start, Vector end, Vector &min, Vector &max, qboolean allowdoors = false, qboolean fulltest = false );

		qboolean			ConnectedTo( PathNode *node );
		void				ConnectTo( PathNode *node, byte maxheight[ NUM_WIDTH_VALUES ], float cost, Door *door = NULL );
		void				ConnectTo( PathNode *node, byte maxheight[ NUM_WIDTH_VALUES ] );
		void				Disconnect( PathNode *node );

		void				FindChildren( Event *ev );
      void           FindEntities( Event *ev );

	public:
      CLASS_PROTOTYPE( PathNode );

      int            contents;
		Vector			worldorigin;
		Vector			worldangles;
		Vector			mins;
		Vector			maxs;
		str				targetname;
		str				target;

		int				nodenum;

		qboolean			setangles;
		str				animname;

							PathNode();
							~PathNode();
		
		void				Setup( Vector pos );
		void				setAngles( Vector ang );
		void				setOrigin( Vector org );
		void				setSize( Vector min, Vector max );
		str				&TargetName( void );
		virtual void	Archive( Archiver &arc );
		virtual void	Unarchive( Archiver &arc );
		
		qboolean			CheckPath( PathNode *node, Vector min, Vector max, qboolean fulltest = true );
		Door				*CheckDoor( Vector pos );

      qboolean       CheckMove( Entity *ent, Vector pos, Vector &min, Vector &max, qboolean allowdoors = false, qboolean fulltest = false );
		qboolean			CheckMove( Vector pos, Vector min, Vector max );
		qboolean			ClearPathTo( PathNode *node, byte maxheight[ NUM_WIDTH_VALUES ], qboolean fulltest = true );
		qboolean			LadderTo( PathNode *node, byte maxheight[ NUM_WIDTH_VALUES ] );
		void				DrawConnections( void );
	};

//
// Exported templated classes must be explicitly instantiated
//
#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL Stack<PathNode *>;
template class EXPORT_FROM_DLL SafePtr<PathNode>;
#endif
typedef SafePtr<PathNode> PathNodePtr;

#define PATHMAP_GRIDSIZE	32
#define PATHMAP_CELLSIZE	( 8192 / PATHMAP_GRIDSIZE )

#define PATHMAP_NODES		126			// 128 - sizeof( int ) / sizeof( short )

class EXPORT_FROM_DLL MapCell
	{
	private :
		int	numnodes;
		short	nodes[ PATHMAP_NODES ];

	public :
								MapCell();
								~MapCell();
		void					Init( void );
		qboolean				AddNode( PathNode *node );
		qboolean				RemoveNode( PathNode *node );
		PathNode				*GetNode( int index );
		int					NumNodes( void );
	};

class EXPORT_FROM_DLL PathSearch : public Listener
	{
	private:
		MapCell				PathMap[ PATHMAP_GRIDSIZE ][ PATHMAP_GRIDSIZE ];

		void					AddToGrid( PathNode *node, int x, int y );
		qboolean				RemoveFromGrid( PathNode *node, int x, int y );
		int					NodeCoordinate( float coord );
		int					GridCoordinate( float coord );
		void					ClearNodes( Event *ev );
		void					LoadNodes( Event *ev );
		void					SaveNodes( Event *ev );
		void					SavePathsEvent( Event *ev );
      void              SetNodeFlagsEvent( Event *ev );
		void					RecalcPathsEvent( Event *ev );
      void              CalcPathEvent( Event *ev );
      void              DisconnectPathEvent( Event *ev );

	public:
      CLASS_PROTOTYPE( PathSearch );

		void					Archive( Archiver &arc );
		void					Unarchive( Archiver &arc );
		void					AddNode( PathNode *node );
		void					RemoveNode( PathNode *node );
		void					UpdateNode( PathNode *node );
		MapCell				*GetNodesInCell( int x, int y );
		MapCell				*GetNodesInCell( Vector pos );
		PathNode				*NearestNode( Vector pos, Entity *ent = NULL, qboolean usebbox = true );
		void					Teleport( Entity *teleportee, Vector from, Vector to );
		void					ShowNodes( void );
		int					NumNodes( void );
		void					SavePaths( void );
		void					Init( const char *mapname );
	};

extern PathSearch PathManager;

#define MAX_PATHNODES 2048

PathNode *AI_FindNode( const char *name );
PathNode *AI_GetNode( int num );
void AI_AddNode( PathNode *node );
void AI_RemoveNode( PathNode *node );
void AI_ResetNodes( void );

#include "path.h"

template<class Heuristic>
class EXPORT_FROM_DLL PathFinder
	{
	private:
	   Stack<PathNode *>	stack;
	   PathNode				*OPEN;
	   PathNode				*CLOSED;
		PathNode				*endnode;

		void					ClearPath( void );
		void					ClearOPEN( void );
		void					ClearCLOSED( void );
		PathNode				*ReturnBestNode( void );
		void					GenerateSuccessors( PathNode *BestNode );
		void					Insert( PathNode *Successor );
		void					PropagateDown( PathNode *Old );
		Path					*CreatePath( PathNode *startnode );

	public:
		Heuristic			heuristic;

								PathFinder();
								~PathFinder<Heuristic>();
		Path					*FindPath( PathNode *from, PathNode *to );
		Path					*FindPath( Vector start, Vector end );
	};

template <class Heuristic>
PathFinder<Heuristic>::PathFinder()
	{
	OPEN   = NULL;
	CLOSED = NULL;
	}

template <class Heuristic>
PathFinder<Heuristic>::~PathFinder()
	{
	ClearPath();
	}

template <class Heuristic>
EXPORT_FROM_DLL void PathFinder<Heuristic>::ClearOPEN
	(
	void
	)

	{
	PathNode *node;

	while( OPEN )
		{
		node = OPEN;
		OPEN = node->NextNode;

		node->inlist = NOT_IN_LIST;
		node->NextNode = NULL;
		node->Parent = NULL;

		// reject is used to indicate that a node is unfit for ending on during a search
		node->reject = false;
		}
	}

template <class Heuristic>
EXPORT_FROM_DLL void PathFinder<Heuristic>::ClearCLOSED
	(
	void
	)

	{
	PathNode *node;

	while( CLOSED )
		{
		node = CLOSED;
		CLOSED = node->NextNode;

		node->inlist = NOT_IN_LIST;
		node->NextNode = NULL;
		node->Parent = NULL;

		// reject is used to indicate that a node is unfit for ending on during a search
		node->reject = false;
		}
	}

template <class Heuristic>
EXPORT_FROM_DLL void PathFinder<Heuristic>::ClearPath
	(
	void
	)

	{
	stack.Clear();
	ClearOPEN();
	ClearCLOSED();
	}

template <class Heuristic>
EXPORT_FROM_DLL Path *PathFinder<Heuristic>::FindPath
	(
	PathNode *from, 
	PathNode *to
	)

	{
	Path		*path;
	PathNode	*node;
   int start;
   int end;
   qboolean checktime;

   checktime = false;
   if ( ai_timepaths->value )
      {
      start = G_Milliseconds();
      checktime = true;
      }

	OPEN   = NULL;
	CLOSED = NULL;

	endnode = to;

	// Should always be NULL at this point
	assert( !from->NextNode );

	// make Open List point to first node 
	OPEN = from;
	from->g = 0;
	from->h = heuristic.dist( from, endnode );
	from->NextNode = NULL;

	node = ReturnBestNode();
	while( node && !heuristic.done( node, endnode ) )
		{
		GenerateSuccessors( node );
		node = ReturnBestNode();
		}

	if ( !node )
		{
		path = NULL;
		if ( ai_debugpath->value )
			{
			gi.dprintf( "Search failed--no path found.\n" );
			}
		}
	else
		{
		path = CreatePath( node );
		}

	ClearPath();

   if ( checktime )
      {
      end = G_Milliseconds();
      if ( ai_timepaths->value <= ( end - start ) )
         {
         G_DebugPrintf( "%d: ent #%d : %d\n", level.framenum, heuristic.entnum, end - start );
         }
      }

	return path;
	}

template <class Heuristic>
EXPORT_FROM_DLL Path *PathFinder<Heuristic>::FindPath
	(
	Vector start,
	Vector end
	)

	{
	PathNode *from;
	PathNode *to;
   Entity *ent;

   ent = G_GetEntity( heuristic.entnum );
	from = PathManager.NearestNode( start, ent );
	to = PathManager.NearestNode( end, ent );

	if ( !from )
		{
		if ( ai_debugpath->value )
			{
			gi.dprintf( "Search failed--couldn't find closest source.\n" );
			}
		return NULL;
		}

	if ( !from || !to )
		{
		if ( ai_debugpath->value )
			{
			gi.dprintf( "Search failed--couldn't find closest destination.\n" );
			}
		return NULL;
		}

	return FindPath( from, to );
	}

template <class Heuristic>
EXPORT_FROM_DLL Path *PathFinder<Heuristic>::CreatePath
	(
	PathNode *startnode
	)

	{
	PathNode *node;
	Path *p;
	int	i;
	int	n;
	PathNode *reverse[ MAX_PATH_LENGTH ];

	// unfortunately, the list goes goes from end to start, so we have to reverse it
	for( node = startnode, n = 0; ( node != NULL ) && ( n < MAX_PATH_LENGTH ); node = node->Parent, n++ )
		{
		assert( n < MAX_PATH_LENGTH );
		reverse[ n ] = node;
		}

	p = new Path( n );
	for( i = n - 1; i >= 0; i-- )
		{
		p->AddNode( reverse[ i ] );
		}

	if ( ai_debugpath->value )
		{
		gi.dprintf( "%d nodes in path\n", n );
		gi.dprintf( "%d nodes allocated\n", PathManager.NumNodes() );
		}

	return p;
	}

template <class Heuristic>
EXPORT_FROM_DLL PathNode *PathFinder<Heuristic>::ReturnBestNode
	(
	void
	)

	{
	PathNode *bestnode;

	if ( !OPEN )
		{
		// No more nodes on OPEN
		return NULL;
		}

	// Pick node with lowest f, in this case it's the first node in list
	// because we sort the OPEN list wrt lowest f. Call it BESTNODE. 

	bestnode = OPEN;					// point to first node on OPEN
	OPEN = bestnode->NextNode;		// Make OPEN point to nextnode or NULL.

	// Next take BESTNODE (or temp in this case) and put it on CLOSED
	bestnode->NextNode	= CLOSED;
	CLOSED					= bestnode;

	bestnode->inlist = IN_CLOSED;

	return( bestnode );
	}

template <class Heuristic>
EXPORT_FROM_DLL void PathFinder<Heuristic>::GenerateSuccessors
	(
	PathNode *BestNode
	)

	{
	int			i;
	int			g;					// total path cost - as stored in the linked lists.
	PathNode		*node;
	pathway_t	*path;

	for( i = 0; i < BestNode->numChildren; i++ )
		{
		path = &BestNode->Child[ i ];
		node = AI_GetNode( path->node );

		// g(Successor)=g(BestNode)+cost of getting from BestNode to Successor 
		g = BestNode->g + heuristic.cost( BestNode, i );

		switch( node->inlist )
			{
			case NOT_IN_LIST :
				// Only allow this if it's valid
				if ( heuristic.validpath( BestNode, i ) )
					{
					node->Parent	= BestNode;
					node->g			= g;
					node->h			= heuristic.dist( node, endnode );
					node->f			= g + node->h;

					// Insert Successor on OPEN list wrt f
					Insert( node );
					}
				break;

			case IN_OPEN :
				// if our new g value is < node's then reset node's parent to point to BestNode
    			if ( g < node->g )
    				{
    				node->Parent	= BestNode;
    				node->g			= g;
    				node->f			= g + node->h;
    				}
				break;

			case IN_CLOSED :
				// if our new g value is < Old's then reset Old's parent to point to BestNode
    			if ( g < node->g )
    				{
    				node->Parent	= BestNode;
    				node->g			= g;
    				node->f			= g + node->h;

					// Since we changed the g value of Old, we need
    				// to propagate this new value downwards, i.e.
    				// do a Depth-First traversal of the tree!
    				PropagateDown( node );
    				}
				break;

			default :
				// shouldn't happen, but try to catch it during debugging phase
				assert( NULL );
				gi.error( "Corrupted path node" );
				break;
			}
		}
	}

template <class Heuristic>
EXPORT_FROM_DLL void PathFinder<Heuristic>::Insert
	(
	PathNode *node
	)

	{
	PathNode *prev;
	PathNode *next;
	int		f;

	node->inlist = IN_OPEN;
	f = node->f;

	// special case for if the list is empty, or it should go at head of list (lowest f)
	if ( ( OPEN == NULL ) || ( f < OPEN->f ) )
		{
		node->NextNode = OPEN;
		OPEN = node;
		return;
		}

	// do sorted insertion into OPEN list in order of ascending f
	prev = OPEN;
	next = OPEN->NextNode;
	while( ( next != NULL ) && ( next->f < f ) )
		{
		prev = next;
		next = next->NextNode;
		}

	// insert it between the two nodes
	node->NextNode = next;
	prev->NextNode = node;
	}

template <class Heuristic>
EXPORT_FROM_DLL void PathFinder<Heuristic>::PropagateDown
	(
	PathNode *node
	)

	{
	int			c;
	unsigned		g;
	unsigned		movecost;
	PathNode		*child;
	PathNode		*parent;
	pathway_t	*path;
	int			n;

	g = node->g;
	n = node->numChildren;
	for( c = 0; c < n; c++ )
		{
		path = &node->Child[ c ];
		child = AI_GetNode( path->node );

		movecost = g + heuristic.cost( node, c );
		if ( movecost < child->g )
			{
			child->g = movecost;
			child->f = child->g + child->h;
			child->Parent = node;

			// reset parent to new path.
			// Now the Child's branch need to be
			// checked out. Remember the new cost must be propagated down.
			stack.Push( child );
			}
		}

	while( !stack.Empty() )
		{
    	parent = stack.Pop();
		n = parent->numChildren;
		for( c = 0; c < n; c++ )
    		{
			path = &parent->Child[ c ];
			child = AI_GetNode( path->node );
  
			// we stop the propagation when the g value of the child is equal or better than 
			// the cost we're propagating
			movecost = parent->g + path->moveCost;
			if ( movecost < child->g )
    			{
				child->g = movecost;
				child->f = child->g + child->h;
    			child->Parent = parent;
    			stack.Push( child );
    			}
    		}
		}
	}

class EXPORT_FROM_DLL StandardMovement
	{
	public:
		int		minwidth;
		int		minheight;
		int		entnum;

	inline void setSize
		( 
		Vector size 
		)

		{
		minwidth = max( size.x, size.y );
		minheight = size.z;
		}

	inline int dist
		( 
		PathNode *node,
		PathNode *end
		)

		{
		Vector	delta;
		int		d1;
		int		d2;
		int		d3;
		int		h;

		delta	= node->worldorigin - end->worldorigin;
		d1		= abs( ( int )delta[ 0 ] );
		d2		= abs( ( int )delta[ 1 ] );
		d3		= abs( ( int )delta[ 2 ] );
		h		= max( d1, d2 );
		h		= max( d3, h );

		return h;
		}

	inline qboolean validpath
		(
		PathNode *node,
		int i
		)

		{
		pathway_t *path;
		PathNode *n;

		path = &node->Child[ i ];
		if ( CHECK_PATH( path, minwidth, minheight ) )
			{
			return false;
			}

		if ( path->door )
			{
			Door *door;
			
			door = ( Door * )G_GetEntity( path->door );
			if ( !door->CanBeOpenedBy( G_GetEntity( entnum ) ) )
				{
				return false;
				}
			}

		n = AI_GetNode( path->node );
		if ( n && ( n->occupiedTime > level.time ) && ( n->entnum != entnum ) )
			{
			return false;
			}

		return true;
		}

	inline int cost
		(
		PathNode *node,
		int i
		)

		{
		return node->Child[ i ].moveCost;
		}

	inline qboolean done
		(
		PathNode *node,
		PathNode *end
		)

		{
		return node == end;
		}
	};

#ifdef EXPORT_TEMPLATE
template class EXPORT_FROM_DLL PathFinder<StandardMovement>;
#endif
typedef PathFinder<StandardMovement> StandardMovePath;

#endif /* navigate.h */
