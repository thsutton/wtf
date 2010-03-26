/** @file
 * Function definitions, macros, and other private code for handling data
 * files.
 *
 * @author Thomas Sutton <me@thomas-sutton.id.au>
 * @created 2003
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "file.h"
#include "debug.h"

db_handle open_db(const char *fname)
{
    int len = strlen(fname)+1;
    char *dfname = (char *)malloc(len+4);
    db_handle db = (db_handle)malloc(sizeof(struct DB_handle));

    db->strings = fopen(fname, "r");
    
    snprintf((void*)dfname, (len+4), "%s.dat", fname);
    db->index = fopen(dfname, "r");

    if (db->strings == NULL || db->index == NULL) {
        fclose(db->strings);
        fclose(db->index);
        if (db->strings == NULL)
            fprintf(stderr, "Missing file %s\n", fname);
        if (db->index == NULL)
            fprintf(stderr, "Missing index %s\n", dfname);
        free(dfname);
        free(db);
        return NULL;
    }

    db->header = (db_header)malloc(sizeof(struct DB_header));
    fread(db->header, sizeof(struct DB_header), 1, db->index);

    free(dfname);
    return db;
}

void close_db(db_handle db)
{
    fclose(db->strings);
    fclose(db->index);
    free(db->header);
    free(db);
}

db_record get_entry(db_handle db, int id)
{
    struct DB_index_record db_i;
    /* allocate memory for the database record */
    db_record db_r = (db_record)malloc(sizeof(struct DB_record));

    /* seek to and read the requested index record */
    fseek(db->index,(sizeof(struct DB_header)+
            (id*sizeof(struct DB_index_record))), SEEK_SET);
    fread(&db_i,sizeof(struct DB_index_record),1,db->index);
    
    /* allocate memory for the strings */
//    printf("get_entry(%d):\n", id);
//    printf("\tklen: %u, vlen: %u\n", db_i.keylen, db_i.valuelen);
    db_r->key = (char *)malloc(db_i.keylen + 2);
    db_r->value = (char *)malloc(db_i.valuelen + 2);

    /* seek to and read the strings */
    fseek(db->strings,db_i.offset,SEEK_SET);
    fread(db_r->key,1,db_i.keylen,db->strings);
    fseek(db->strings,1,SEEK_CUR);
    fread(db_r->value,1,db_i.valuelen,db->strings);
    db_r->key[db_i.keylen] = (char)NULL;
    db_r->value[db_i.valuelen] = (char)NULL;
	LOG("key: %s, value: %s", db_r->key, db_r->value);

    return(db_r);
}
