# Makefile is a part of the PYTHIA event generator.
# Copyright (C) 2016 Torbjorn Sjostrand.
# PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
# Please respect the MCnet Guidelines, see GUIDELINES for details.
# Author: Philip Ilten, September 2014.
#
# This is is the Makefile used to build PYTHIA examples on POSIX systems.
# Example usage is:
#     make main01
# For help using the make command please consult the local system documentation,
# i.e. "man make" or "make --help".

################################################################################
# VARIABLES: Definition of the relevant variables from the configuration script.
################################################################################

# Include the configuration.
-include Makefile.inc

# Handle GZIP support.
ifeq ($(GZIP_USE),true)
  CXX_COMMON+= -DGZIPSUPPORT -I$(GZIP_INCLUDE)
  CXX_COMMON+= -L$(GZIP_LIB) -Wl,-rpath,$(GZIP_LIB) -lz
endif

# Check distribution (use local version first, then installed version).
ifneq ("$(wildcard ../lib/libpythia8.a)","")
  PREFIX_LIB=../lib
  PREFIX_INCLUDE=../include
endif
CXX_COMMON:=-I$(PREFIX_INCLUDE) $(CXX_COMMON) -Wl,-rpath,$(PREFIX_LIB) -ldl

################################################################################
# RULES: Definition of the rules used to build the PYTHIA examples.
################################################################################

# Rules without physical targets (secondary expansion for specific rules).
.SECONDEXPANSION:
.PHONY: all clean

# All targets (no default behavior).
all:
	@echo "Usage: make mainXX"

# The Makefile configuration.
Makefile.inc:
	$(error Error: PYTHIA must be configured, please run "./configure"\
                in the top PYTHIA directory)

# PYTHIA libraries.
$(PREFIX_LIB)/libpythia8.a :
	$(error Error: PYTHIA must be built, please run "make"\
                in the top PYTHIA directory)


################################################################################
################################################################################
# My own program # ROOT (turn off all warnings for readability).
################################################################################
################################################################################

EventGen EventGen_ee: $$@.cc MyUserHooks.cpp $(PREFIX_LIB)/libpythia8.a
ifeq ($(ROOT_USE),true)

	$(CXX) $^ -o $@ -w -I$(ROOT_INCLUDE) -I$(HEPMC2_INCLUDE) $(CXX_COMMON)\
	 -L$(HEPMC2_LIB) -Wl,-rpath,$(HEPMC2_LIB) -lHepMC\
	 -Wl,-rpath,$(ROOT_LIB) `$(ROOT_BIN)root-config --glibs`
else
	@echo "Error: $@ requires ROOT"
endif


main92: $$@.cc $(PREFIX_LIB)/libpythia8.a Pythia8Dict.so
ifeq ($(ROOT_USE),true)
	$(CXX) $^ -o $@ -w -I$(ROOT_INCLUDE) $(CXX_COMMON)\
	 `$(ROOTBIN)root-config --cflags` -Wl,-rpath,./\
	 -Wl,-rpath,$(ROOT_LIB) `$(ROOT_BIN)root-config --glibs`
else
	@echo "Error: $@ requires ROOT"
endif
Pythia8Dict.so: Pythia8Dict.cc $(PREFIX_LIB)/libpythia8.a
	$(CXX) $^ -o $@ -w -I$(ROOT_INCLUDE) $(CXX_SHARED) $(CXX_COMMON)\
	 `$(ROOTBIN)root-config --cflags`
Pythia8Dict.cc: main92.h Pythia8Link.h 
	export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$(ROOT_LIB);\
	 $(ROOT_BIN)rootcint -f $@ -c -I$(PREFIX_INCLUDE) $^




# Clean.
clean:
	rm -f weakbosons.lhe; rm -f Pythia8.promc; rm -f hist.root;
	rm -f *~; rm -f \#*; rm -f core*; rm -f *Dct.*
	rm -f $(EXE) hist.root pythiaDict.* ;
	rm -f Pythia8Dict.h Pythia8Dict.cc *.so main92 EventGen;
