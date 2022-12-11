/*
 * Copyright ©2022 Travis McGaha.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Pennsylvania
 * CIS 2400 for use solely during Fall Semester 2022 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */
#ifndef HW7_DEQUE_H_
#define HW7_DEQUE_H_

#include <stdbool.h>

// for bool type (true, false)

///////////////////////////////////////////////////////////////////////////////
// A Deque is a Double Ended Queue.
//
// Here we are providing the interface to implement a Deque, with an
// internal implementation of a doubly linked dq.
///////////////////////////////////////////////////////////////////////////////

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Internal structures for our Deque implementation.
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// A single node within a deque.
//
// A node contains next and prev pointers as well as a customer-supplied
// payload.
typedef struct dq_node_st
{
  int payload;             // customer-supplied payload
  struct dq_node_st *next; // next node in deque, or NULL
  struct dq_node_st *prev; // prev node in deque, or NULL
} DequeNode;

// The entire Deque.
// This struct contains metadata about the deque.
typedef struct dq_st
{
  int num_elements; //  # elements in the list
  DequeNode *front; // beginning of deque, or NULL if empty
  DequeNode *back;  // end of deque, or NULL if empty
} Deque;

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// "Methods" for our Deque implementation.
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// Allocates and returns a pointer to a new Deque.
// It is the Caller's responsibility to at some point call Deque_Free to free
// the associated memory.
//
// Arguments: none.
//
// Returns:
// - the newly-allocated linked list, or NULL on error.
Deque *Deque_Allocate(void);

// Free a Deque that was previously allocated by Deque_Allocate.
//
// Arguments:
// - dq: the deque to free.  It is unsafe to use "dq" after this
//   function returns.
void Deque_Free(Deque *dq);

// Return the number of elements in the deque.
//
// Arguments:
// - dq:  the deque to query.
//
// Returns:
// - deque size.
int Deque_Size(Deque *dq);

// Adds a new element to the front of the Deque.
//
// Arguments:
// - dq: the Deque to push onto.
// - payload: the payload to push to the front
void Deque_Push_Front(Deque *dq, int payload);

// Pop an element from the front of the deque.
//
// Arguments:
// - dq: the Deque to pop from.
// - payload_ptr: a return parameter; on success, the popped node's payload
//   is returned through this parameter.
//
// Returns:
// - false on failure (eg, the deque is empty).
// - true on success.
bool Deque_Pop_Front(Deque *dq, int *payload_ptr);

// Peeks at the element at the front of the deque.
//
// Arguments:
// - dq: the Deque to peek.
// - payload_ptr: a return parameter; on success, the peeked node's payload
//   is returned through this parameter.
//
// Returns:
// - false on failure (eg, the deque is empty).
// - true on success.
bool Deque_Peek_Front(Deque *dq, int *payload_ptr);

// Pushes a new element to the end of the deque.
//
// This is the "end" version of Deque_Push_Front.
//
// Arguments:
// - dq: the Deque to push onto.
// - payload: the payload to push to the end
void Deque_Push_Back(Deque *dq, int payload);

// Pops an element from the end of the deque.
//
// This is the "end" version of Deque_Pop_Front.
//
// Arguments:
// - dq: the Deque to remove from
// - payload_ptr: a return parameter; on success, the popped node's payload
//   is returned through this parameter.
//
// Returns:
// - false: on failure (eg, the deque is empty).
// - true: on success.
bool Deque_Pop_Back(Deque *dq, int *payload_ptr);

// Peeks at the element at the back of the deque.
//
// Arguments:
// - dq: the Deque to peek.
// - payload_ptr: a return parameter; on success, the peeked node's payload
//   is returned through this parameter.
//
// Returns:
// - false on failure (eg, the deque is empty).
// - true on success.
bool Deque_Peek_Back(Deque *dq, int *payload_ptr);
#endif