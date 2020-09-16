#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "harness.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (q) {
        q->head = q->tail = NULL;
        q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (!q)
        return;

    while (q->head) {
        list_ele_t *temp = q->head;
        q->head = q->head->next;
        temp->next = NULL;
        free(temp->value);
        free(temp);
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
    if (!q)
        return false;

    list_ele_t *newh = malloc(sizeof(list_ele_t));

    if (!newh)
        return false;

    newh->value = malloc(sizeof(char) * (strlen(s) + 1));
    if (!newh->value) {
        free(newh);
        return false;
    }

    q->size++;
    strncpy(newh->value, s, strlen(s) + 1);

    if (!q->head) {
        newh->next = NULL;
        q->head = q->tail = newh;
        return true;
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
    if (!q)
        return false;

    list_ele_t *newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;

    newh->value = malloc(sizeof(char) * (strlen(s) + 1));
    if (!newh->value) {
        free(newh);
        return false;
    }

    q->size++;
    strncpy(newh->value, s, strlen(s) + 1);
    newh->next = NULL;

    if (!q->head) {
        q->head = q->tail = newh;
    } else {
        q->tail->next = newh;
        q->tail = newh;
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
    if (q && q->head) {
        if (strlen(q->head->value) >= bufsize && !sp)
            return false;
        list_ele_t *rm_node = q->head;

        memset(sp, '\0', bufsize);
        strncpy(sp, rm_node->value, bufsize - 1);

        q->head = q->head->next;
        rm_node->next = NULL;
        free(rm_node->value);
        free(rm_node);
        q->size--;

        if (q->size == 0)
            q->tail = NULL;

        return true;
    }
    return false;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (!q)
        return 0;
    return q->size;
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
    if (!q || !q->head || q->size < 2)
        return;

    list_ele_t *cursor = NULL;
    q->tail = q->head;
    while (q->head) {
        list_ele_t *next = q->head->next;
        q->head->next = cursor;
        cursor = q->head;
        q->head = next;
    }
    q->head = cursor;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */

list_ele_t *merge(list_ele_t *l1, list_ele_t *l2)
{
    list_ele_t *head = NULL;
    list_ele_t **temp = &head;

    while (l1 && l2) {
        if (strcmp(l1->value, l2->value) <= 0) {
            *temp = l1;
            l1 = l1->next;
        } else {
            *temp = l2;
            l2 = l2->next;
        }
        temp = &((*temp)->next);
    }

    if (l1)
        *temp = l1;
    if (l2)
        *temp = l2;

    return head;
}

list_ele_t *mergeSortList(list_ele_t *head)
{
    if (!head || !head->next)
        return head;

    list_ele_t *fast = head->next;
    list_ele_t *slow = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    fast = slow->next;
    slow->next = NULL;

    list_ele_t *l1 = mergeSortList(head);
    list_ele_t *l2 = mergeSortList(fast);

    return merge(l1, l2);
}

void q_sort(queue_t *q)
{
    if (!q || q->size == 1)
        return;

    q->head = mergeSortList(q->head);
    while (q->tail)
        q->tail = q->tail->next;
}
