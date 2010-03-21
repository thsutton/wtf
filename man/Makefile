wtf.6:
	sed -e "s:DATADIR:$(DATADIR):" wtf.6.in > wtf.6

wtf.6.gz: wtf.6
	gzip wtf.6

clean:
	rm -f wtf.6.gz wtf.6
