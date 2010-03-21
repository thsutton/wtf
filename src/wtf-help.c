/*
 * help.h -    The help functions for wtf.
 *
 * (c) Thomas Sutton <thsutton@utas.edu.au>, 2003.
 * This program is released under the terms of the GNU General Public License.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "help.h"

char *usage(char *argv0)
{
        /* FIXME: check for errors */
	int size = (strlen(argv0) + strlen("Usage: [-a] [is] <pattern>") + 2);

	char *usage = (char*)malloc(size);
	snprintf(usage,size,"Usage: %s [-a] [is] <pattern>",argv0);
	return usage;
}
