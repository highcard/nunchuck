#include <stdlib.h>
#include <stdio.h>

#include "nunchuck.h"

void die(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

nc_node_t *nc_add(nc_list_t *list, void *data, int flags)
{
    fprintf(stderr, "[nc_add] start\n");
    nc_node_t *next, *nextnext, *newnode;
    fprintf(stderr, "[nc_add] malloc\n");
    newnode = malloc(sizeof(nc_node_t));
    if (newnode == NULL) {
        die("malloc failed");
    }
    newnode->data = data;
    if (list->head == NULL) {
        list->head = newnode;
        list->tail = newnode;
        newnode->ptr = NULL;
    } else if (list->head == list->tail) {
        list->head = newnode;
    } else {
        next = list->head;
        list->head = newnode;
        nextnext = translate(next->ptr, list->tail);
        next->ptr = translate(nextnext, list->head);
        list->head->ptr = translate(list->tail, next);
    }
    return newnode;
}

void nc_traverse(nc_list_t *list, void (*f)(void *), int flags)
{
    nc_node_t *prev, *cur, *next;
    if (list->head == NULL) {
        return;
    }
    if (list->head == list->tail) {
        (*f)(list->head->data);
        return;
    }
    cur = list->head;
    prev = list->tail;
    fprintf(stderr, "[nc_traverse] entering loop\n");
    do {
        fprintf(stderr, "[nc_traverse] in while loop\n");
        if(cur->data) {
            fprintf(stderr, "[nc_traverse] running func\n");
            (*f)(cur->data);
        }
        next = translate(prev, cur->ptr);
        prev = cur;
        cur = next;
    } while (cur != list->head);
}









