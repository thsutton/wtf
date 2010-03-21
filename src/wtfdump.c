/*
 * wtfdump.c -    This program is a database information dumper for the wtf(6) 
 *                package.
 * 
 * (c) Thomas Sutton <thsutton@utas.edu.au>, 2003.
 * This program is released under the terms of the GNU General Public License.
 */

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "file.h"
#include "help.h"

int state;

int main(int argc, char **argv)
{
	int i;
	db_handle db;
	db_record r;

	if (argc < 2) {
		fprintf(stderr, "%s\n", usage(argv[0]));
		exit(-1);
	}

	db = open_db(argv[1]); 
	if (db == NULL)
		exit(1);

	printf("Textfile: %s\nDatafile: %s.dat\nItems: %u\n",argv[1],argv[1],db->header->items);

	printf("Offset\tKey\tValue\n");
	for (i = 0; i < db->header->items;i++)
	{
		r = get_entry(db,i);
		printf("%u\t%s\t%s\n",i,r->key,r->value);
		free(r->key);
		free(r->value);
		free(r);
	}	
	
	close_db(db);
    return(0);
}
