/*
 * search.h -    Search functions for wtf.
 *
 * (c) Thomas Sutton <thsutton@utas.edu.au>, 2003.
 * This program is released under the terms of the GNU General Public License.
 *
 * CHANGES:
 *	2003-08-21	Igor Pechtchanski	<pechtcha@cs.nyu.edu>
 *		search.c (search): Switch to case-insensitive string comparison
 */

#include <stdlib.h>
#include <string.h>
#include "search.h"
#include "file.h"

char *search(const char *db_f, char *target)
/* FIXME: bounds checking */
{
	int top,middle,bottom,i;
	char *response = NULL;

	db_record db_r;
	db_handle db = open_db(db_f);
	top = db->header->items - 1;
	bottom = 0;
	middle = top / 2;


	do {
		db_r = get_entry(db, middle);
		i = strcasecmp(db_r->key,target);
		if (i == 0) {
			response = db_r->value;
			free(db_r->key);
			free(db_r);
			close_db(db);
		} else if (i < 0) {
			bottom = middle+1;
			middle = ((top-bottom)/2)+bottom;
		} else if (i > 0) {
			top = middle-1;
			middle = ((top-bottom)/2)+bottom;
		}
	} while ((i!=0) && (bottom <= top));
	
        return response;
}
