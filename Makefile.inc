# PYTHIA configuration file.
# Generated on Sun Jun 12 11:48:54 CDT 2016 with the user supplied options:
# --with-hepmc2=/usr/local/hepmc
# --with-root=/usr/local/root
# --prefix=/usr/local/pythia8219

# Install directory prefixes.
PREFIX_BIN=/usr/local/pythia8219/bin
PREFIX_INCLUDE=/usr/local/pythia8219/include
PREFIX_LIB=/usr/local/pythia8219/lib
PREFIX_SHARE=/usr/local/pythia8219/share/Pythia8

# Compilation flags (see ./configure --help for further documentation).
ENABLE_SHARED=false
CXX=g++
CXX_COMMON=-O2 -ansi -pedantic -W -Wall -Wshadow -fPIC
CXX_SHARED=-dynamiclib -flat_namespace -undefined suppress
CXX_SONAME=-Wl,-dylib_install_name
LIB_SUFFIX=.dylib

# EVTGEN configuration.
EVTGEN_USE=false
EVTGEN_BIN=
EVTGEN_INCLUDE=./
EVTGEN_LIB=./

# FASTJET3 configuration.
FASTJET3_USE=false
FASTJET3_BIN=
FASTJET3_INCLUDE=./
FASTJET3_LIB=./

# HEPMC2 configuration.
HEPMC2_USE=true
HEPMC2_BIN=/usr/local/hepmc/bin/
HEPMC2_INCLUDE=/usr/local/hepmc/include
HEPMC2_LIB=/usr/local/hepmc/lib

# HEPMC3 configuration.
HEPMC3_USE=false
HEPMC3_BIN=
HEPMC3_INCLUDE=./
HEPMC3_LIB=./

# LHAPDF5 configuration.
LHAPDF5_USE=false
LHAPDF5_BIN=
LHAPDF5_INCLUDE=./
LHAPDF5_LIB=./
LHAPDF5_PLUGIN=LHAPDF5.h

# LHAPDF6 configuration.
LHAPDF6_USE=false
LHAPDF6_BIN=
LHAPDF6_INCLUDE=./
LHAPDF6_LIB=./
LHAPDF6_PLUGIN=LHAPDF5.h

# POWHEG configuration.
POWHEG_USE=false
POWHEG_BIN=
POWHEG_INCLUDE=./
POWHEG_LIB=./

# PROMC configuration.
PROMC_USE=false
PROMC_BIN=
PROMC_INCLUDE=./
PROMC_LIB=./

# ROOT configuration.
ROOT_USE=true
ROOT_BIN=/usr/local/root/bin/
ROOT_INCLUDE=/usr/local/root/include
ROOT_LIB=/usr/local/root/lib

# GZIP configuration.
GZIP_USE=false
GZIP_BIN=
GZIP_INCLUDE=./
GZIP_LIB=./

# BOOST configuration.
BOOST_USE=false
BOOST_BIN=
BOOST_INCLUDE=./
BOOST_LIB=./

# PYTHON configuration.
PYTHON_USE=false
PYTHON_BIN=
PYTHON_INCLUDE=./
PYTHON_LIB=./
