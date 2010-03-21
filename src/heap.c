/*
 * heap.c -    Stuff for heaps.
 *
 * thsutton <thsutton@utas.edu.au> 20030517
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "heap.h"

/* static functions */
static void heap_sink(heap_ptr heap_s, int current);

heap_ptr heap_build(heap_member *heap, const int count, const int size)
	/* build a heap using the populated array *heap.
	 */
{
	int current;
    heap_ptr heap_s = NULL;
    heap_s = (heap_ptr)malloc(sizeof(struct heap));
    heap_s->items = count;
    heap_s->size = size;
    heap_s->heap = heap;

	for (current=((pow(2,log2(count)))/2);current >= 0;current--){
        heap_sink(heap_s, current);
    }
    return(heap_s);
}

void heap_destroy(heap_ptr heap_s)
	/* free all memory used by the given heap.
	 */
{
	int i;
	for (i=0;i < heap_s->items;i++) {
		if (heap_s->heap[i]) free((heap_s->heap[i]));
	}
	free(heap_s->heap);
	free(heap_s);
}

db_index_record heap_delete(heap_ptr heap_s)
	/* remove and return the root element of the heap heap_s.
	 */
{
	heap_member *heap;
	db_index_record retval;
	heap_member tmp;

	retval = NULL;
    heap = heap_s->heap;

    /* FIXME: Check that a root element exists */
    retval = heap[0]->rec;
	tmp = heap[0];

    heap[0] = heap[(heap_s->items - 1)];
    heap[(heap_s->items - 1)] = NULL;
    heap_s->items--;
	free(tmp->key);
	free(tmp);
    heap_sink(heap_s, 0);
    return retval;
}

static void heap_sink(heap_ptr heap_s, int current)
	/* Sink the item at position current in heap heap_s if required...
	 */
{
	int left, right, lower;
	heap_member tmp, *heap;

	tmp = NULL;
	heap = heap_s->heap;
	left = (current * 2)+1;
	right = (current * 2)+2;
	lower = 0;

	if ((right < heap_s->items)||(left < heap_s->items)) {
		/* who to swap with...*/
		lower = left;
		if (right < heap_s->items) {
			if (strcmp(heap[right]->key,heap[left]->key) < 0)
				lower = right; 
		}

		/* swap */
		if (strcmp(heap[lower]->key, heap[current]->key) < 0) {
			tmp = heap[lower];
			heap[lower] = heap[current];
			heap[current] = tmp;
			heap_sink(heap_s,lower);
		}
	}
}