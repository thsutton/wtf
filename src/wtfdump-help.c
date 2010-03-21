/*
 * wtfdump-help.h -    The help functions for wtfdump.
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
	int size = (strlen(argv0) + strlen("Usage:  <textfile>") + 2);

	char *usage = (char*)malloc(size);
	snprintf(usage,size,"Usage: %s <textfile>",argv0);
	return usage;
}
