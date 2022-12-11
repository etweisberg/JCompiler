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

#include <stdio.h>
#include <stdlib.h>
#ifndef HW7_DEQUE_H_
#include "Deque.h"
#endif
///////////////////////////////////////////////////////////////////////////////
// Deque implementation.

Deque *Deque_Allocate()
{
  // TODO: The rest of this function
  Deque *deque;
  deque = malloc(sizeof(Deque));
  if (deque == NULL)
  {
    printf("ERROR");
    exit(EXIT_FAILURE);
  }
  deque->front = NULL;
  deque->back = NULL;
  deque->num_elements = 0;
  return deque;
}

void Deque_Free(Deque *dq)
{
  int payload;
  while (Deque_Pop_Front(dq, &payload))
    ;
  free(dq);
}

int Deque_Size(Deque *dq)
{
  if (!dq)
  {
    return 0;
  }
  else
  {
    return dq->num_elements;
  }
}

void Deque_Push_Front(Deque *dq, int payload)
{
  // memory allocation
  DequeNode *dn = malloc(sizeof(DequeNode));
  if (dn == NULL)
  {
    printf("ERROR");
    exit(EXIT_FAILURE);
  }

  // adding node to front
  dn->next = dq->front;
  dn->prev = NULL;
  dn->payload = payload;
  if (dq->front)
  {
    dq->front->prev = dn;
    dq->front = dn;
  }
  else
  {
    dq->front = dn;
    dq->back = dn;
  }
  dq->num_elements++;
}

bool Deque_Pop_Front(Deque *dq, int *payload_ptr)
{
  if (dq->front == NULL)
  {
    return false;
  }
  DequeNode *next_first = dq->front->next;
  *payload_ptr = dq->front->payload;
  if (dq->front == dq->back)
  {
    dq->back = NULL;
    next_first = NULL;
  }
  else
  {
    next_first = dq->front->next;
    next_first->prev = NULL;
  }
  free(dq->front);
  dq->front = next_first;
  dq->num_elements--;
  return true;
}

bool Deque_Peek_Front(Deque *dq, int *payload_ptr)
{
  if (!dq->front)
  {
    return false;
  }
  else
  {
    *payload_ptr = dq->front->payload;
    return true;
  }
}

void Deque_Push_Back(Deque *dq, int payload)
{

  DequeNode *dn = malloc(sizeof(DequeNode));

  if (dn == NULL)
  {
    printf("Couldn't allocate space for a new Deque Node\n");
    exit(EXIT_FAILURE);
  }

  dn->next = NULL;
  dn->prev = dq->back;
  dn->payload = payload;

  if (dq->back)
  {
    dq->back->next = dn;
    dq->back = dn;
  }
  else
  {
    dq->front = dn;
    dq->back = dn;
  }
  dq->num_elements++;
}

bool Deque_Pop_Back(Deque *dq, int *payload_ptr)
{
  if (dq->back == NULL)
  {
    return false;
  }
  DequeNode *prev_last = dq->back->prev;
  *payload_ptr = dq->back->payload;
  if (dq->front == dq->back)
  {
    dq->front = NULL;
    prev_last = NULL;
  }
  else
  {
    prev_last = dq->back->prev;
    prev_last->next = NULL;
  }
  dq->num_elements--;
  free(dq->back);
  dq->back = prev_last;
  return true;
}

bool Deque_Peek_Back(Deque *dq, int *payload_ptr)
{
  if (!dq->back)
  {
    return false;
  }
  else
  {
    *payload_ptr = dq->back->payload;
    return true;
  }
}
