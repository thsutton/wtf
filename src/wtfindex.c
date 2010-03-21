/*
 * wtfindex.c -    The index generator for wtf(6).
 * 
 * It writes the index records into a temporary file, then reads them and the 
 * keys they describe into memory again, and sorts them before writing the real
 * index file.
 *
 * (c) Thomas Sutton <thsutton@utas.edu.au>, 2003.
 * This program is released under the terms of the GNU General Public License.
 *
 * CHANGES:
 *	2003-08-22	Igor Pechtchanski
 *		Check that the read succeeds along with checking for EOF.  Remove the 
 *		now redundant off-by-one correction. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "help.h"
#include "file.h"
#include "heap.h"

int flags;
int state;
char tmp_template[] = "/tmp/wtfindex.XXXXXX";

int main(int argc, char **argv)
{
    char *string_fn, *index_fn;
    FILE *string_fd, *index_fd, *tmp_fd;
    struct DB_header db_h;
    db_index_record db_i;
    char buff;
    int length, items, position, i;
    heap_ptr heap;
	heap_member *heap_a;

    /* process command line arguments */
    if ((argc != 2)){
		fprintf(stderr,"%s\n",usage(argv[0]));
		exit(-1);
    }

    /* setup files */
    string_fn = argv[1];
    index_fn = (char*)malloc((strlen(string_fn)+5));
    snprintf(index_fn,(strlen(string_fn)+5),"%s.dat",string_fn);
	tmp_fd = fdopen(mkstemp(tmp_template), "w+b"); 
    string_fd = fopen(string_fn, "r");
    index_fd  = fopen(index_fn, "w");
    
    /* write temporary header */
    db_h.version = 0;
    db_h.flags = 0;
    db_h.items = 0;
    fwrite(&db_h,sizeof(struct DB_header),1,tmp_fd);
    items = 0;
    position = 0;
    length = 0;

	/* build index */
	db_i = (db_index_record)malloc(sizeof(struct DB_index_record));
	db_i->offset = 0;
	while ((!feof(string_fd)) && fread((void*)(&buff), 1, 1, string_fd)) {
		/* this could probably do with being a bit smarter, but that might
		 * be starting to poach on fortunes territory :-) */
		position++;
		switch (buff) {
			case '\t':	db_i->keylen = length;
						length = 0;
						break;
			case '\n':	db_i->valuelen = length;
						fwrite(db_i,sizeof(struct DB_index_record),1,tmp_fd);
						db_i->offset = position;
						db_i->keylen = 0;
						db_i->valuelen = 0;
						items++;
						length = 0;
						break;
			default:	length++;
						break;
		}
    }
    /* write the correct header */
    fseek(tmp_fd,0,SEEK_SET);
    db_h.items = items;
    fwrite(&db_h,sizeof(struct DB_header),1,tmp_fd);
	/* The temporary index is now constructed. */

	/* Read the records into memory. */
	fseek(tmp_fd,sizeof(struct DB_header),SEEK_SET);
	heap_a = (heap_member*)malloc(sizeof(heap_member)*items);
	for (i = 0; i < items; i++){
		heap_a[i] = (heap_member)malloc(sizeof(struct HEAP_member));
		heap_a[i]->rec = (db_index_record)malloc(sizeof(struct 
			DB_index_record));
		fread(((void*)heap_a[i]->rec),sizeof(struct DB_index_record),1,tmp_fd);
		heap_a[i]->key = (char*)malloc(heap_a[i]->rec->keylen + 1);
		fseek(string_fd, heap_a[i]->rec->offset, SEEK_SET);
		fread((void*)heap_a[i]->key,1,heap_a[i]->rec->keylen,string_fd);
		heap_a[i]->key[heap_a[i]->rec->keylen] = 0;
	}
	heap = heap_build(heap_a, items, items);
    fwrite(&db_h,sizeof(struct DB_header),1,index_fd);

	for (i=0;i<items;i++) {
		db_i = heap_delete(heap);
		fwrite(db_i,sizeof(struct DB_index_record),1,index_fd);
	}

	/* FIXME: do some free()ing */
    /* finish up */
	heap_destroy(heap);
	fclose(tmp_fd);
	remove(tmp_template);
    fclose(string_fd);
    fclose(index_fd);
    exit(0);
}
