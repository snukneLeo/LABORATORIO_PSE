SYSTEMC=$$SYSTEMC_HOME
SYSTEMC_AMS=$$SCAMS_HOME

BASE_COMPONENTS=.

PLANT=lsf
CONTROLLER=tdf

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
EXECUTABLE=./bin/feedback_system.x

all: $(EXECUTABLE)

clean:
	@echo Cleaning
	@rm -f obj/*.o *~
	@rm -f $(EXECUTABLE)

$(EXECUTABLE): obj/main.o \
	obj/System.o \
	obj/controller_$(CONTROLLER).o \
	obj/plant_$(PLANT).o \
	obj/ControllerTransactor.o \
	obj/PlantTransactor.o \
	obj/ControllerIFace.o
	@echo Building $@
	@ $(LD) -o $@ $(INCDIR) $^ $(LIBS)

obj/System.o: src/System.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

obj/ControllerTransactor.o: src/ControllerTransactor.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

obj/PlantTransactor.o: src/PlantTransactor.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

obj/ControllerIFace.o: src/ControllerIFace.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

obj/main.o: src/main.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

obj/controller_tdf.o: $(BASE_COMPONENTS)/src/controller_tdf.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

obj/plant_lsf.o: $(BASE_COMPONENTS)/src/plant_lsf.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

.PHONY: all clean	


