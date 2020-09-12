//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/queue.h                          $
// $Revision:: 5                                                              $
//   $Author:: Jimdose                                                        $
//     $Date:: 10/07/98 11:59p                                                $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/queue.h                               $
// 
// 5     10/07/98 11:59p Jimdose
// Added Remove and Inqueue
// 
// 4     5/25/98 6:53a Aldie
// Added queue to game project
// 
// 2     11/17/97 8:15p Jimdose
// Created file.
// 
// 1     11/17/97 8:04p Jimdose
//
// DESCRIPTION:
// Generic Queue object
// 

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "class.h"

class QueueNode
	{
	public:
		void		 *data;
		QueueNode *next;

		QueueNode();
	};

inline QueueNode::QueueNode()
	{
	data = NULL;
	next = NULL;
	}

class EXPORT_FROM_DLL Queue
	{
	private:
		QueueNode *head;
		QueueNode *tail;

	public:
					Queue();
					~Queue();
		void		Clear( void	);
		qboolean Empty( void );
		void		Enqueue( void *data );
		void		*Dequeue( void );
      void     Remove( void *data );
      qboolean Inqueue( void *data );
	};

inline Queue::Queue()
	{
	head = NULL;
	tail = NULL;
	}

inline Queue::~Queue()
	{
	Clear();
	}

inline void Queue::Clear
	(
	void
	)

	{
	while( !Empty() )
		{
		Dequeue();
		}
	}

inline qboolean Queue::Empty
	(
	void
	)

	{
	if ( head == NULL )
		{
		assert( !tail );
		return true;
		}

	assert( tail );
	return false;
	}

inline void Queue::Enqueue
	(
	void *data
	)

	{
	QueueNode *tmp;

	tmp = new QueueNode;
	if ( !tmp )
		{
		assert( NULL );
		gi.error( "Queue::Enqueue : Out of memory" );
		}

	tmp->data = data;

	assert( !tmp->next );
	if ( !head )
		{
		assert( !tail );
		head = tmp;
		}
	else
		{
		assert( tail );
		tail->next = tmp;
		}
	tail = tmp;
	}

inline void *Queue::Dequeue
	(
	void
	)

	{
	void *ptr;
	QueueNode *node;

	if ( !head )
		{
		assert( !tail );
		return NULL;
		}

	node = head;
	ptr = node->data;

	head = node->next;
	if ( head == NULL )
		{
		assert( tail == node );
		tail = NULL;
		}

	delete node;

	return ptr;
	}

inline void Queue::Remove
   (
   void *data
   )

   {
	QueueNode *node;
	QueueNode *prev;

	if ( !head )
		{
		assert( !tail );
      
      gi.dprintf( "Queue::Remove : Data not found in queue\n" );
		return;
		}

   for( prev = NULL, node = head; node != NULL; prev = node, node = node->next )
      {
      if ( node->data == data )
         {
         break;
         }
      }

   if ( !node )
      {
      gi.dprintf( "Queue::Remove : Data not found in queue\n" );
      }
   else
      {
      if ( !prev )
         {
         // at head
         assert( node == head );
         head = node->next;
	      if ( head == NULL )
		      {
		      assert( tail == node );
		      tail = NULL;
		      }
         }
      else
         {
         prev->next = node->next;
         if ( prev->next == NULL )
            {
            // at tail
            assert( tail == node );
            tail = prev;
            }
         }
      
	   delete node;
      }
   }

inline qboolean Queue::Inqueue
   (
   void *data
   )

   {
	QueueNode *node;

   for( node = head; node != NULL; node = node->next )
      {
      if ( node->data == data )
         {
         return true;
         }
      }

   return false;
   }

#endif /* queue.h */
