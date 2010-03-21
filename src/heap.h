/*
 * heap.h -    Stuff for heaps.
 *
 * thsutton <thsutton@utas.edu.au> 20030517
 */

#ifndef __HAVE_HEAP_H
#define __HAVE_HEAP_H

#include "file.h"

typedef struct HEAP_member *heap_member;
struct HEAP_member {
	char  *key;
	db_index_record rec;
};

struct heap {
	heap_member *heap;
	unsigned int size;
	unsigned int items;
	unsigned char flags;
};

typedef struct heap *heap_ptr;

heap_ptr         heap_build(heap_member *heap, const int count, const int size);
db_index_record  heap_delete(heap_ptr heap_s);
void             heap_destroy(heap_ptr heap_s);
#endif
