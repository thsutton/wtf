/** @file
 * Function prototypes, type declarations and other public code for handling
 * data files.
 *
 * @author Thomas Sutton <me@thomas-sutton.id.au>
 * @created 2003
 */

#ifndef __HAVE_FILE_H
#define __HAVE_FILE_H

#include <stdio.h>

typedef struct DB_header *db_header;
struct DB_header {
	unsigned long version;
	unsigned long items;
	unsigned long flags;
};

typedef struct DB_handle *db_handle;
struct DB_handle {
	FILE *strings;
	FILE *index;
	db_header header;
};

typedef struct DB_index_record *db_index_record;
struct DB_index_record {
	unsigned long offset;
	unsigned long keylen;
	unsigned long valuelen;
};

typedef struct DB_record *db_record;
struct DB_record {
	unsigned long db_i;
	char *key;
	char *value;
};

db_handle open_db(const char *fname);
void close_db(db_handle db);
db_record get_entry(db_handle db, int id);
#endif
