SYSTEMC=$$SYSTEMC_HOME
SYSTEMC_AMS=$$SCAMS_HOME

BASE_COMPONENTS=.

CONTROLLER=AMS_TDF_testbench
VALVE=valve_AMS_TDF
TEST=AMS_TDF_testbench
MAIN=main_AMS
WATERTANK=waterTank_AMS_LSF

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
EXECUTABLE=./bin/piattaformaAMS.x

all: $(EXECUTABLE)

clean:
	@echo Cleaning
	@rm -f obj/*.o *~
	@rm -f $(EXECUTABLE)

$(EXECUTABLE): obj/main.o obj/testbench.o obj/valve.o obj/water.o
	@echo Building $@
	@ $(LD) -o $@ $(INCDIR) $^ $(LIBS)

obj/main.o: src/$(MAIN).cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

obj/valve.o: src/$(VALVE).cc include/$(VALVE).hh
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

obj/testbench.o: src/$(TEST).cc include/$(TEST).hh
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

obj/water.o: src/$(WATERTANK).cc include/$(WATERTANK).hh
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<


.PHONY: all clean	


