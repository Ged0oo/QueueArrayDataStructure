/*
 * QueueArray.h
 *
 * Created: 26 OCT 2022
 * Author : Mohamed Nagy
 */


#ifndef _QUEUE_ARRAY_H
#define _QUEUE_ARRAY_H


 /************************************************************************/
 /*                   section : includes                                 */
 /************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "StdTypes.h"


 /************************************************************************/
 /*                   section: data type declaration                     */
 /************************************************************************/

typedef enum {
    QUEUE_NOK = 0,     /* Queue operation not performed successfully */
    QUEUE_OK,          /* Queue operation performed successfully  */
    QUEUE_FULL,        /* Queue is full */
    QUEUE_EMPTY,       /* Queue is empty */
    QUEUE_NULL_POINTER /* NULL pointer passed to the Queue */
}EN_QueueStatus_t;


typedef struct {
    void** QueueArray;   /* Pointer to array of void pointers */
    uint32 QueueMaxSize; /* Maximum elements in the Queue */
    sint32 ElementCount; /* Number of elements in the Queue */
    sint32 QueueFront;   /* Index of the front elements */
    sint32 QueueRear;    /* Index of the rear elements */
}ST_Queue_t;


/************************************************************************/
/*                   section: functions declarations                    */
/************************************************************************/

ST_Queue_t* CreateQueue(uint32 maxSize, EN_QueueStatus_t* retStatus);
EN_QueueStatus_t EnqueueElement(ST_Queue_t* queueObj, void* itemPtr);
void* DequeueElement(ST_Queue_t* queueObj, EN_QueueStatus_t* retStatus);
void* QueueFront(ST_Queue_t* queueObj, EN_QueueStatus_t* retStatus);
void* QueueRear(ST_Queue_t* queueObj, EN_QueueStatus_t* retStatus);
EN_QueueStatus_t GetQueueCount(ST_Queue_t* queueObj, uint32* QueueCount);
EN_QueueStatus_t DestroyQueue(ST_Queue_t* queueObj);

#endif // _QUEUE_ARRAY_H
