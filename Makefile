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

# Examples without external dependencies.
main% : main%.cc $(PREFIX_LIB)/libpythia8.a
	$(CXX) $^ -o $@ $(CXX_COMMON)


# HEPMC2.
main41 main42 main43 main85 main86 main87 main88 main89: $$@.cc\
	$(PREFIX_LIB)/libpythia8.a
ifeq ($(HEPMC2_USE),true)
	$(CXX) $^ -o $@ -I$(HEPMC2_INCLUDE) $(CXX_COMMON)\
	 -L$(HEPMC2_LIB) -Wl,-rpath,$(HEPMC2_LIB) -lHepMC
else
	@echo "Error: $@ requires HEPMC2"
endif


# ROOT (turn off all warnings for readability).
main91 EventGen : $$@.cc MyUserHooks.cpp $(PREFIX_LIB)/libpythia8.a
ifeq ($(ROOT_USE),true)

	$(CXX) $^ -o $@ -w -I$(ROOT_INCLUDE) -I$(HEPMC2_INCLUDE) $(CXX_COMMON)\
	 -L$(HEPMC2_LIB) -Wl,-rpath,$(HEPMC2_LIB) -lHepMC\
	 -Wl,-rpath,$(ROOT_LIB) `$(ROOT_BIN)root-config --glibs`
else
	@echo "Error: $@ requires ROOT"
endif


main92: $$@.cc $$@.h $$@LinkDef.h $(PREFIX_LIB)/libpythia8.a
ifeq ($(ROOT_USE),true)
	export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$(ROOT_LIB);\
	 $(ROOT_BIN)rootcint -f $@Dct.cc -c -I$(PREFIX_INCLUDE) $@.h $@LinkDef.h
	$(CXX) $@Dct.cc $^ -o $@ -w -I$(ROOT_INCLUDE) $(CXX_COMMON)\
	 -Wl,-rpath,$(ROOT_LIB) `$(ROOT_BIN)root-config --glibs`
else
	@echo "Error: $@ requires ROOT"
endif

# User-written examples for tutorials, without external dependencies.
mymain% : mymain%.cc $(PREFIX_LIB)/libpythia8.a
	$(CXX) $^ -o $@ $(CXX_COMMON)

# Internally used tests, without external dependencies.
test% : test%.cc $(PREFIX_LIB)/libpythia8.a
	$(CXX) $^ -o $@ $(CXX_COMMON)

# Clean.
clean:
	@rm -f main[0-9][0-9]; rm -f out[0-9][0-9];\
	rm -f mymain[0-9][0-9]; rm -f myout[0-9][0-9];\
	rm -f test[0-9][0-9][0-9]; rm -f out[0-9][0-9][0-9];\
	rm -f weakbosons.lhe; rm -f Pythia8.promc; rm -f hist.root;\
	rm -f *~; rm -f \#*; rm -f core*; rm -f *Dct.*
	rm -f $(EXE) hist.root pythiaDict.* \
               NoMuonCutDict.cc NoMuonCutDict.h NoMuonCut.root NinoTrialDict.cc NinoTrialDict.h NinoTrial.root
