# This should only be called by the toplevel Makefile.
# It requires DATADIR to be defined on the command line.

PROGRAMS = wtf${exeext} wtfindex${exeext} wtfdump${exeext}

WTFOBJECTS = file.o search.o wtf.o wtf-help.o
WTFINDEXOBJECTS = heap.o wtfindex.o wtfindex-help.o
WTFDUMPOBJECTS = wtfdump.o wtfdump-help.o file.o
OBJECTS = $(WTFOBJECTS) $(WTFINDEXOBJECTS) $(WTFDUMPOBJECTS)

all : $(PROGRAMS)

conf.h : 
	sed -e "s:DATADIR:$(DATADIR):" conf.h.in > conf.h

wtf${exeext} : conf.h $(WTFOBJECTS)
	$(CC) $(WTFOBJECTS) -o wtf

wtfindex${exeext} : $(WTFINDEXOBJECTS)
	$(CC) $(WTFINDEXOBJECTS) -o wtfindex

wtfdump${exeext}:	$(WTFDUMPOBJECTS)
	$(CC) $(WTFDUMPOBJECTS) -o wtfdump

clean:
	rm -f $(OBJECTS) $(PROGRAMS) conf.h
