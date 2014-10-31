EXE=musical-feature-extractor
CXX=g++
CXXFLAGS=-Wall -Wextra -Werror -std=c++11 -pedantic -lfmodex64-4.44.43
SRC=src/detector.cc src/sound-system.cc src/extractor.cc src/main.cc
OBJ=$(SRC:.cc=.o)
TAR=yrakcaz-$(EXE)
DIR=/usr/bin

-include makefile.rules

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(EXE) $^

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $^

clean:
	rm -f $(OBJ) $(EXE) $(TAR).tar.bz2

check: all
	tests/test.py

cleandoc:
	rm -rf doc/html doc/latex doc/refman.pdf

distclean: clean cleandoc
	rm -f makefile.rules

doc:
	doxygen doc/Doxyfile
	$(MAKE) -C doc/latex
	mv doc/latex/refman.pdf doc/

install:
ifeq ($(DIR),/usr/bin)
	sudo cp $(EXE) $(DIR)
else
	cp $(EXE) $(DIR)
endif

export:
	git archive HEAD --prefix=$(TAR)/ | bzip2 > $(TAR).tar.bz2

.PHONY: all clean distclean export doc
