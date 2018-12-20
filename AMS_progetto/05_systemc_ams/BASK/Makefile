SYSTEMC_AMS=$$SCAMS_HOME
SYSTEMC=$$SYSTEMC_HOME

PLATFORM= $(shell uname -s)
ARCH=$(shell getconf LONG_BIT)

ifeq ($(PLATFORM),Darwin)
SYSC_LIBDIR := $(SYSTEMC)/lib-macosx
SCAMS_LIBDIR := $(SYSTEMC_AMS)/lib-macosx
endif
ifeq ($(PLATFORM),Linux)
SYSC_LIBDIR := $(SYSTEMC)/lib-linux
SCAMS_LIBDIR := $(SYSTEMC_AMS)/lib-linux
endif

ifeq ($(ARCH),64)
SYSC_LIBDIR := $(SYSC_LIBDIR)64
SCAMS_LIBDIR := $(SCAMS_LIBDIR)64
endif

LIBS = $(SCAMS_LIBDIR)/libsystemc-ams.a \
	   $(SYSC_LIBDIR)/libsystemc.a \
	   -lpthread

INCDIR = -I./include/ -I. -I$(SYSTEMC)/include/ -I$(SYSTEMC_AMS)/include

CXX=g++
CFLAGS= -c
LD=g++

EXECUTABLE=./bin/bask.x

all: $(EXECUTABLE)

clean:
	@echo Cleaning
	@rm -f obj/*.o *~
	@rm -f $(EXECUTABLE)

$(EXECUTABLE): obj/bask.o \
	obj/bask_demod.o obj/bask_mod.o obj/bit_src.o obj/ltf_nd_filter.o \
	obj/mixer.o obj/rectifier.o obj/sampler.o obj/sin_src.o 
	@ $(LD) -o $@ $(INCDIR) $^ $(LIBS)


obj/bask.o: src/bask.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

obj/bask_demod.o: src/bask_demod.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

obj/bask_mod.o: src/bask_mod.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

obj/bit_src.o: src/bit_src.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

obj/ltf_nd_filter.o: src/ltf_nd_filter.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

obj/mixer.o: src/mixer.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

obj/rectifier.o: src/rectifier.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

obj/sampler.o: src/sampler.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

obj/sin_src.o: src/sin_src.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

.PHONY: all clean	
