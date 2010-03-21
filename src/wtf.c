/*
 * wtf.c -    This program is a reimplementation of wtf(6), from NetBSD 1.5
 *            and later and Slackware 9.0 and later.
 * 
 * (c) Thomas Sutton <thsutton@utas.edu.au>, 2003.
 * This program is released under the terms of the GNU General Public License.
 *
 * CHANGES:
 *	2003-08-24	Thomas Sutton	<thsutton@utas.edu.au>
 *		wtf.c:	Implemented $WTFPATH and return all hits.
 */

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "search.h"
#include "help.h"
#include "conf.h"


#define OPTION_ALL 1
#define OPTION_USER 2

int main(int argc, char **argv)
{
	char	*searchPath;					/* For search path processing... */
	char	*cPath;
	int 	tmp;
	DIR 	*dirp = NULL;					/* For directory reading... */
	struct 	dirent *dirent_p = NULL;
    char 	*target, *def, *dbfile_n,		/* For searching... */
			*file_n, *userdir_n;
    int file_n_l = 0;
	int options = 0;


	/* Handle the command line... 
	 * Really, really badly. I need to look at getopt :-) */
	if ((argc < 2) || (argc > 4)) {
		fprintf(stderr, "%s\n", usage(argv[0]));
		exit(-1);
	}
	if (argc == 3) {
		if (strcmp(argv[1], "is") == 0) { 
			target = argv[2];
		} else if (strcmp(argv[1], "-a") == 0) {
			target = argv[2];
			options |= OPTION_ALL;
		} else {
			fprintf(stderr, "%s\n", usage(argv[0]));
			exit(-1);
		}
	} else if (argc == 4) {
		for (tmp=1;tmp<3;tmp++){
			if (strcmp(argv[tmp], "is") == 0) { 
			} else if (strcmp(argv[tmp], "-a") == 0) {
				options |= OPTION_ALL;
			} else {
				fprintf(stderr, "%s\n", usage(argv[0]));
				exit(-1);
			}
		}
		target = argv[3];
	} else {
		target = argv[1];
	}

			
	/* Get our search path. */
	searchPath = getenv("WTFPATH");
	tmp = 0;

	/* If we don't have one... */
	if (!searchPath) {
		/* Do we know the users home directory? */
		cPath = getenv("HOME");
		if (cPath)	tmp = strlen(cPath)+5+2; else tmp = 1;
		
		/* Home much memory is our search path?*/
		tmp += strlen(datadir_n);
		searchPath = (char*)malloc(tmp);
		
		/* Write the user data dir and system data dir into the new search
		 * path...*/
		if (cPath) {
			snprintf(searchPath, tmp, "%s/.wtf:%s", cPath, datadir_n);
		} else {
			snprintf(searchPath, tmp, "%s", datadir_n);
		}
	}

	/* Walk through the search path performing the search...*/
	cPath = strtok(searchPath, ":");
	while (cPath) {
			/* Open the directory... */
			dirp = opendir(cPath);
			if (dirp) {
				/* skip . and .. */
				dirent_p = readdir(dirp);
				dirent_p = readdir(dirp);
				/* for each file... */
			    while (((dirent_p = readdir(dirp)) != NULL)) {
					file_n = dirent_p->d_name;
					file_n_l = strlen(file_n);

					/* If the file looks like an index...*/
					if (strcmp(((dirent_p->d_name)+file_n_l-4), ".dat")==0) {
						/* Assume the equiv text file exists... */
						file_n[file_n_l-4] = 0;
						file_n_l += strlen(cPath+2);
						dbfile_n = malloc(file_n_l);
						snprintf(dbfile_n, file_n_l, "%s/%s", cPath, file_n);

						/* Search the database we have found for the target. */
						def = search(dbfile_n, target);
						free(dbfile_n);
						if (def) {
							/* Should this output target or the key from the
							 * db? */
							printf("%s: %s\n",target,def);
							free(def);
							if (!(options & OPTION_ALL)) {
								exit(0);
							}
						}
					}
			    }
			}
			
			/* get next token... */
			cPath = strtok(NULL,":");
	}

	/* Free searchPath if we created it. */
	if (tmp) free(searchPath);
}
