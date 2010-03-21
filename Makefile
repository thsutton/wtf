# Until I can figure out how to use autoconf and automake, this will have to
# do. Just point prefix at where you want it installed. The default should be
# good for most systems.
prefix = /usr/local
exeext =
DESTDIR =
INSTALL = /usr/bin/install

#
# You shouldn't need to change anything below here...
# 

bindir	= ${prefix}/bin
datadir	= ${prefix}/share/wtf
mandir	= ${prefix}/man/man6
DATADIR	= ${datadir}

DATAFILES = suffixes acronyms os companies

DATAINDEXES = suffixes.dat acronyms.dat os.dat companies.dat

BINARIES = src/wtf${exeext} src/wtfindex${exeext} src/wtfdump${exeext}

DOCUMENTS = wtf.6.gz

all : $(BINARIES) $(DATAFILES) $(DOCUMENTS)

wtf: src/wtf${exeext}
src/wtf${exeext} : 
	@cd src && make DATADIR=$(DATADIR) exeext=${exeext} wtf${exeext}
	
wtfindex: src/wtfindex${exeext}
src/wtfindex${exeext} :
	@cd src && make DATADIR=$(DATADIR) exeext=${exeext} wtfindex${exeext}

wtfdump: src/wtfdump${exeext}
src/wtfdump${exeext} :
	@cd src && make DATADIR=$(DATADIR) exeext=${exeext} wtfdump${exeext}

wtf.6.gz :
	@cd man && make clean && make DATADIR=$(DATADIR) wtf.6.gz

suffixes	: wtfindex data
acronyms	: wtfindex data
os			: wtfindex data
companies	: wtfindex data


data : wtfindex
	@cd data && make

dist:
	-rm `find . -type f -name "*~"`

clean:
	@cd src && make clean
	@cd man && make clean
	@cd data && make clean

install: all 
	@mkdir -p $(DESTDIR)/$(bindir) $(DESTDIR)/$(datadir) $(DESTDIR)/$(mandir)
	@$(INSTALL) -m 755 $(BINARIES) $(DESTDIR)/$(bindir)
	@cd data && $(INSTALL) -m 644 $(DATAFILES) $(DATAINDEXES) $(DESTDIR)/$(datadir)
	@$(INSTALL) -m 644 man/wtf.6.gz $(DESTDIR)/$(mandir)
	@cd $(DESTDIR)/$(mandir) && ln -s wtf.6.gz wtfindex.6.gz
	@cd $(DESTDIR)/$(mandir) && ln -s wtf.6.gz wtfdump.6.gz
