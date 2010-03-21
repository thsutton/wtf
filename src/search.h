/*
 * search.h -    Search functions for wtf.
 *
 * (c) Thomas Sutton <thsutton@utas.edu.au>, 2003.
 * This program is released under the terms of the GNU General Public License.
 */
#ifndef __HAVE_SEARCH_H
#define __HAVE_SEARCH_H

extern int flags;
extern int state;

char *search(const char *db_f, char *target);
#endif
