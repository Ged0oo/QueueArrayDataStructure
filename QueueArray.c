/*
 * QueueArray.c
 *
 * Created: 26 OCT 2022
 * Author : Mohamed Nagy
 */


#include "QueueArray.h"


 /**
   * @brief  Returns the queue state full or not.
   * @param  (queueObj) pointer to stack head structure.
   * @retval Status of the queue full or not.
   */
static uint8 QueueIsFull(ST_Queue_t* queueObj)
{
    return ((queueObj->ElementCount) == (queueObj->QueueMaxSize));
}



/**
  * @brief  Returns the queue state empty or not.
  * @param  (queueObj) pointer to queue head structure.
  * @retval Status of the queue empty or not.
  */
static uint8 QueueIsEmpty(ST_Queue_t* queueObj)
{
    return (0 == (queueObj->ElementCount));
}




/**
  * @brief  This algorithm creates an empty queue by allocating the head
            structure and the array from dynamic memory.
  * @param  (maxSize) queue maximum number of elements.
  * @param  (ret_status) Status returned while performing this operation
  * @retval Pointer to the allocated queue in the heap
  */
ST_Queue_t* CreateQueue(uint32 maxSize, EN_QueueStatus_t* retStatus)
{
    ST_Queue_t* MyQueue;
    /* Create queue object in the heap to hold the queue information */
    MyQueue = (ST_Queue_t*)malloc(sizeof(ST_Queue_t));
    if (NULL == MyQueue)
    {
        *retStatus = QUEUE_NULL_POINTER;
        MyQueue = NULL;
    }
    else
    {
        /* Create array of <void *> to hold the addresses of the Queue elements */
        MyQueue->QueueArray = (void**)calloc(maxSize, sizeof(void*));
        if (NULL == MyQueue->QueueArray)
        {
            *retStatus = QUEUE_NOK;
            MyQueue = NULL;
        }
        else
        {
            MyQueue->ElementCount = 0;
            MyQueue->QueueFront = -1;
            MyQueue->QueueRear = -1;
            MyQueue->QueueMaxSize = maxSize;
            *retStatus = QUEUE_OK;
        }
    }
    return MyQueue;
}



/**
  * @brief  This algorithm validate if the queue full or not,
            then increment queue rear,
            and validate the case of the queue was empty or not.
  * @param  (queueObj) pointer to queue head structure.
  * @param  (itemPtr) pointer to the new queue item to be added.
  * @retval The finall queue status while performing this operation.
  */
EN_QueueStatus_t EnqueueElement(ST_Queue_t* queueObj, void* itemPtr)
{
    EN_QueueStatus_t status = QUEUE_NOK;
    if ((NULL == queueObj) || (NULL == itemPtr))
    {
        status = QUEUE_NULL_POINTER;
    }
    else
    {
        /* Validate if the queue is not full */
        if (QueueIsFull(queueObj))
        {
            status = QUEUE_FULL; /* Queue is full, can't enqueue new element */
        }
        else
        {
            /* Increment Queue Rear Index */
            (queueObj->QueueRear)++;
            /* Queue wraps to element 0 (Circular Queue) */
            if (queueObj->QueueRear == queueObj->QueueMaxSize)
            {
                queueObj->QueueRear = 0;
            }
            /* Insert the input data in to the rear position */
            queueObj->QueueArray[queueObj->QueueRear] = itemPtr;
            /* validate if the queue was empty, (front and rear points to the first element) */
            if (queueObj->ElementCount == 0)
            {
                queueObj->QueueFront = 0;
                queueObj->ElementCount = 1;
            }
            else
            {
                (queueObj->ElementCount)++; /* New element has been added to the Queue */
            }
            status = QUEUE_OK;
        }
    }
    return status;
}


/**
  * @brief  This algorithm validate if the queue empty or not,
            then increment queue Front index,
            and validate if this element is the last element in the Queue.
  * @param  (queueObj) pointer to queue head structure.
  * @param  (retStatus) Status returned while performing this operation.
  * @retval Pointer to the dequeued element.
  */
void* DequeueElement(ST_Queue_t* queueObj, EN_QueueStatus_t* retStatus)
{
    void* ReturnEelem = NULL;
    if ((NULL == queueObj) || (NULL == retStatus))
    {
        *retStatus = QUEUE_NULL_POINTER;
    }
    else
    {
        /* Check if the queue is empty */
        if (!queueObj->ElementCount)
        {
            *retStatus = QUEUE_EMPTY; /* Queue is empty */
            ReturnEelem = NULL;
        }
        else
        { /* Queue is not empty */
            ReturnEelem = queueObj->QueueArray[queueObj->QueueFront];
            /* Increment Queue Front Index */
            (queueObj->QueueFront)++;
            /* Queue front has wrapped to element 0 (Circular Queue) */
            if (queueObj->QueueFront == queueObj->QueueMaxSize)
            {
                queueObj->QueueFront = 0;
            }
            /* Check if the element is the last element in the Queue */
            if (1 == queueObj->ElementCount)
            {
                queueObj->QueueFront = -1; /* Queue is empty */
                queueObj->QueueRear = -1;  /* Queue is empty */
            }
            (queueObj->ElementCount)--; /* Element has been deleted from the Queue */
            *retStatus = QUEUE_OK;
        }
    }
    return ReturnEelem;
}


/**
  * @brief  This algorithm validate if the queue empty or not,
            then it returned a Pointer to the front element.
  * @param  (queueObj) pointer to queue head structure.
  * @param  (retStatus) Status returned while performing this operation.
  * @retval Pointer to the front element int the queue.
  */
void* QueueFront(ST_Queue_t* queueObj, EN_QueueStatus_t* retStatus)
{
    void* ReturnEelem = NULL;
    if ((NULL == queueObj) || (NULL == retStatus))
    {
        *retStatus = QUEUE_NULL_POINTER;
    }
    else
    {
        /* Check if the queue is empty */
        if (!queueObj->ElementCount)
        {
            *retStatus = QUEUE_EMPTY; /* Queue is empty */
            ReturnEelem = NULL;
        }
        else
        { /* Queue is not empty */
            ReturnEelem = queueObj->QueueArray[queueObj->QueueFront];
            *retStatus = QUEUE_OK;
        }
    }
    return ReturnEelem;
}


/**
  * @brief  This algorithm validate if the queue empty or not,
            then it returned a Pointer to the rear element.
  * @param  (queueObj) pointer to queue head structure.
  * @param  (retStatus) Status returned while performing this operation.
  * @retval Pointer to the rear element int the queue.
  */
void* QueueRear(ST_Queue_t* queueObj, EN_QueueStatus_t* retStatus)
{
    void* ReturnEelem = NULL;
    if ((NULL == queueObj) || (NULL == retStatus))
    {
        *retStatus = QUEUE_NULL_POINTER;
    }
    else
    {
        /* Check if the queue is empty */
        if (!queueObj->ElementCount)
        {
            *retStatus = QUEUE_EMPTY; /* Queue is empty */
            ReturnEelem = NULL;
        }
        else
        { /* Queue is not empty */
            ReturnEelem = queueObj->QueueArray[queueObj->QueueRear];
            *retStatus = QUEUE_OK;
        }
    }
    return ReturnEelem;
}


/**
  * @brief  This algorithm validate if the queue empty or not,
            then it returned the value stored in the ElementCount argument
            in the Queue Configrations.
  * @param  (queueObj) pointer to queue head structure.
  * @param  (QueueCount) Number of elements in Queue.
  * @retval The finall queue status while performing this operation.
  */
EN_QueueStatus_t GetQueueCount(ST_Queue_t* queueObj, uint32* QueueCount)
{
    EN_QueueStatus_t status = QUEUE_NOK;
    if ((NULL == queueObj) || (NULL == QueueCount))
    {
        status = QUEUE_NULL_POINTER;
    }
    else
    {
        /* Check if the queue is empty */
        if (!queueObj->ElementCount)
        {
            *QueueCount = 0;    /* Queue is empty */
        }
        else
        { /* Queue is not empty */
            *QueueCount = queueObj->ElementCount;
        }
        status = QUEUE_OK;
    }
    return status;
}


/**
  * @brief  This function releases all memory to the heap.
  * @param  (queueObj) pointer to stack head structure
  * @retval The finall queue status while performing this operation.
  */
EN_QueueStatus_t DestroyQueue(ST_Queue_t* queueObj)
{
    EN_QueueStatus_t status = QUEUE_NOK;
    if (NULL == queueObj)
    {
        status = QUEUE_NULL_POINTER;
    }
    else
    {
        free(queueObj->QueueArray);
        free(queueObj);
        status = QUEUE_OK;
    }
    return status;
}