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

EXECUTABLE = main.x

all: $(EXECUTABLE)

install: all

$(EXECUTABLE): ./obj/bit_src.o \
	   ./obj/ltf_nd_filter.o \
	   ./obj/mixer_de.o \
	   ./obj/mixer.o \
	   ./obj/rectifier.o \
	   ./obj/sampler.o \
	   ./obj/sin_src.o \
	   ./obj/eln_source.o \
	   ./obj/lsf_in_tdf.o \
	   ./obj/main.o
	@echo Linking $@
	@$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)
	
#------------------------------------------------------------
#---------------------------Main-----------------------------
obj/main.o: main.cpp
	@echo Compiling $@
	@$(CXX) $(DEBUG) $(CFLAGS) $(INCDIR) -o $@ $<

#------------------------------------------------------------
#--------------------TDF Modules-----------------------------
obj/bit_src.o: tdf/bit_src.cpp
	@echo Compiling $@
	@$(CXX) $(DEBUG) $(CFLAGS) $(INCDIR) -o $@ $<

obj/ltf_nd_filter.o: tdf/ltf_nd_filter.cpp
	@echo Compiling $@
	@$(CXX) $(DEBUG) $(CFLAGS) $(INCDIR) -o $@ $<
	
obj/mixer_de.o: tdf/mixer_de.cpp
	@echo Compiling $@
	@$(CXX) $(DEBUG) $(CFLAGS) $(INCDIR) -o $@ $<
	
obj/mixer.o: tdf/mixer.cpp
	@echo Compiling $@
	@$(CXX) $(DEBUG) $(CFLAGS) $(INCDIR) -o $@ $<
	
obj/rectifier.o: tdf/rectifier.cpp
	@echo Compiling $@
	@$(CXX) $(DEBUG) $(CFLAGS) $(INCDIR) -o $@ $<
		
obj/sampler.o: tdf/sampler.cpp
	@echo Compiling $@
	@$(CXX) $(DEBUG) $(CFLAGS) $(INCDIR) -o $@ $<
	
obj/sin_src.o: tdf/sin_src.cpp
	@echo Compiling $@
	@$(CXX) $(DEBUG) $(CFLAGS) $(INCDIR) -o $@ $<
	
#------------------------------------------------------------
#--------------------ELN Modules-----------------------------
obj/eln_source.o: eln/eln_source.cpp
	@echo Compiling $@
	@$(CXX) $(DEBUG) $(CFLAGS) $(INCDIR) -o $@ $<
	
#------------------------------------------------------------
#--------------------LSF Modules-----------------------------
obj/lsf_in_tdf.o: lsf/lsf_in_tdf.cpp
	@echo Compiling $@
	@$(CXX) $(DEBUG) $(CFLAGS) $(INCDIR) -o $@ $<
	
clean:
	@echo "Cleaning..."
	@rm -rf obj/*.o
	@rm -rf *.x
	@rm -rf *.vcd
	@rm -rf $(EXECUTABLE)
	@echo "Done!"

.PHONY: all clean install
