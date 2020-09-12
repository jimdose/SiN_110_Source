//-----------------------------------------------------------------------------
//
//  $Logfile:: /Quake 2 Engine/Sin/code/game/stack.h                          $
// $Revision:: 6                                                              $
//   $Author:: Jimdose                                                        $
//     $Date:: 3/02/98 5:27p                                                  $
//
// Copyright (C) 1997 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source is may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
// $Log:: /Quake 2 Engine/Sin/code/game/stack.h                               $
// 
// 6     3/02/98 5:27p Jimdose
// Changed stack into a template to make it more flexible.
// 
// 5     2/20/98 12:08p Jimdose
// Changed for Q2 dlls
// 
// 3     11/17/97 8:17p Jimdose
// Fixed a bug where Pop was checking an uninitialized variable instead of
// testing head.
// Added assertions
// 
// 2     11/17/97 7:38p Jimdose
// Created file.
//
// DESCRIPTION:
// Generic Stack object.
// 

#ifndef __STACK_H__
#define __STACK_H__

#include "g_local.h"
#include "class.h"

template <class Type>
class StackNode
	{
	public:
		Type		 data;
		StackNode *next;

		StackNode( Type d );
	};

template <class Type>
inline StackNode<Type>::StackNode( Type d ) : data( d )
	{
	next = NULL; 
	}

template <class Type>
class EXPORT_FROM_DLL Stack
	{
	private:
		StackNode<Type> *head;

	public:
					Stack();
					~Stack<Type>();
		void		Clear( void	);
		qboolean Empty( void );
		void		Push( Type data );
		Type		Pop( void );
	};

template <class Type>
inline Stack<Type>::Stack()
	{
	head = NULL;
	}

template <class Type>
inline Stack<Type>::~Stack<Type>()
	{
	Clear();
	}

template <class Type>
inline void EXPORT_FROM_DLL Stack<Type>::Clear
	(
	void
	)

	{
	while( !Empty() )
		{
		Pop();
		}
	}

template <class Type>
inline qboolean EXPORT_FROM_DLL Stack<Type>::Empty
	(
	void
	)

	{
	if ( head == NULL )
		{
		return true;
		}
	return false;
	}

template <class Type>
inline void EXPORT_FROM_DLL Stack<Type>::Push
	(
	Type data
	)

	{
	StackNode<Type> *tmp;

	tmp = new StackNode<Type>( data );
	if ( !tmp )
		{
		assert( NULL );
		gi.error( "Stack::Push : Out of memory" );
		}

	tmp->next = head;
	head = tmp;
	}

template <class Type>
inline Type EXPORT_FROM_DLL Stack<Type>::Pop
	(
	void
	)

	{
	Type ret;
	StackNode<Type> *node;

	if ( !head )
		{
		return NULL;
		}

	node	= head;
	ret	= node->data;
	head	= node->next;

	delete node;

	return ret;
	}

#endif /* stack.h */
