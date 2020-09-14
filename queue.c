#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if(q)
    {
        q->head = q->tail = NULL;
        q->size = 0 ;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    list_ele_t *temp ;

    if(!q)  return ;

    while(q->head)
    {
        temp = q->head ;
        q->head = q->head->next ;
        temp->next = NULL ;
        free(temp->value) ;
        free(temp) ;
    }
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh = malloc(sizeof(list_ele_t));

    if(!newh)	return false ;

    newh->value = malloc(sizeof(char)*( strlen(s)+1 )) ;
    if(!newh->value)
    {
    	free(newh) ;
    	return false ;
    }

    q->size ++ ;
    strcpy(newh->value,s) ;

    if(!q->head)
    {
        newh->next = NULL ;
        q->head = q->tail = newh ;
        return true ;
    }

    newh->next = q->head;
    q->head = newh;

    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    list_ele_t *newh = malloc(sizeof(list_ele_t*)) ;
    if(!newh)
            return false ;

    newh->value = malloc(sizeof(char)*(strlen(s) + 1));
    if(!newh->value)
    {
            free(newh) ;
            return false ;
    }

    q->size ++ ;
    strcpy(newh->value, s) ;
    newh->next = NULL ;

    if(!q->head)
    {
        q->head = q->tail = newh ;
    }
    else
    {
        q->tail->next = newh ;
        q->tail = newh ;
    }
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    list_ele_t *rm_node ;

    if(q && q->head)
    {
        if(strlen(q->head->value) >= bufsize && !sp)   return false ;
        rm_node = q->head ;

        memset(sp, '\0', bufsize) ;
        strncpy(sp, rm_node->value, bufsize-1) ;

        q->head = q->head->next ;
        rm_node->next = NULL ;
        free(rm_node->value) ;
        free(rm_node) ;
        q->size -- ;

        if(q->size == 0)        q->tail = NULL ;

        return true ;
    }
    return false ;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    return q->size ;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}
