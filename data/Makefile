OBJECTS = suffixes.dat acronyms.dat companies.dat os.dat

all: $(OBJECTS)

suffixes.dat:
	../src/wtfindex suffixes
acronyms.dat:
	../src/wtfindex acronyms
companies.dat:
	../src/wtfindex companies
os.dat:
	../src/wtfindex os
	

clean:
	rm -f $(OBJECTS)
