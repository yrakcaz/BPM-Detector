EXE=BPMDetector
CXX=g++
CXXFLAGS=-Wall -Wextra -Werror -std=c++11 -pedantic -lfmodex64-4.44.43
SRC=src/detector.cc src/sound-system.cc src/args.cc src/main.cc
OBJ=$(SRC:.cc=.o)
TAR=yrakcaz-bpmdetector

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

distclean: clean
	rm -f makefile.rules

export:
	git archive HEAD --prefix=$(TAR)/ | bzip2 > $(TAR).tar.bz2

.PHONY: all clean distclean export
