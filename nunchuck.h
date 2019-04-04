#ifndef _NCLIST_H_
#define _NCLIST_H_

#define NC_FORE 1
#define NC_BACK 2

/*
 * A node in a doubly-linked list.
 * ptr is the xor'd memory address values of next and prev nodes
 *
 * Cases:
 * List contains <2 items: ptr == NULL
 * List contains 3+ items: ptr = &next ^ &prev
 *
 */
struct Node {
    void *data;
    struct Node *ptr;
};
typedef struct Node nc_node_t;

/*
 * A doubly-linked list.  
 * head & tail point to the true memory addresses.
 * that's about as straightforward as it gets
 *
 * Cases
 * List is empty:          head == NULL
 * List contains 1 item:   head != NULL && head == tail;
 * List contains 2+ items:  head != NULL && head != tail;
 */
struct List {
    nc_node_t *head;
    nc_node_t *tail;
};
typedef struct List nc_list_t;

static inline nc_node_t *translate(const nc_node_t *from, const nc_node_t *to)
{
    nc_node_t *translated;
    translated = (nc_node_t*) ((long long) from ^ (long long) to);
    return translated;
}

/*
 * init empty list
 */
static inline void initList(nc_list_t *list)
{
    fprintf(stderr, "in init\n");
    list->head = 0;
    list->tail= 0;
    fprintf(stderr, "end init\n");
}

/*
 * Creates new node which points to data, and inserts it into list 
 *
 */
nc_node_t *nc_add(nc_list_t *list, void *data, int flags);

/*
 * List traversal. Calls (*f) on each data (if not NULL)
 */
void nc_traverse(struct List *list, void (*f)(void *), int flags);

#endif /* #ifndef _NCLIST_H_ */
