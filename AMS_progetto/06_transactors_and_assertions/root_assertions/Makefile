DESIGN_NAME=root
ABSTRACTION_LEVEL=RTL


SYSTEMC=$$SYSTEMC_HOME
SYSTEMC_AMS=$$SCAMS_HOME

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

EXECUTABLE=bin/$(DESIGN_NAME)_$(ABSTRACTION_LEVEL).x

all: $(EXECUTABLE)

$(EXECUTABLE): obj/main_$(DESIGN_NAME)_$(ABSTRACTION_LEVEL).o obj/$(DESIGN_NAME)_$(ABSTRACTION_LEVEL)_testbench.o obj/$(DESIGN_NAME)_$(ABSTRACTION_LEVEL).o
	@echo Building $@
	$(LD) -g $(INCDIR) -o $@ $^ $(LIBS)

obj/main_$(DESIGN_NAME)_$(ABSTRACTION_LEVEL).o: src/main_$(DESIGN_NAME)_$(ABSTRACTION_LEVEL).cc
	@echo Building $@
	$(CXX) -g $(CFLAGS) $(INCDIR) -o $@ $< 

obj/$(DESIGN_NAME)_$(ABSTRACTION_LEVEL)_testbench.o: src/$(DESIGN_NAME)_$(ABSTRACTION_LEVEL)_testbench.cc include/$(DESIGN_NAME)_$(ABSTRACTION_LEVEL)_testbench.hh
	@echo Building $@
	$(CXX) -g $(CFLAGS) $(INCDIR) -o $@ $< 

obj/$(DESIGN_NAME)_$(ABSTRACTION_LEVEL).o: src/$(DESIGN_NAME)_$(ABSTRACTION_LEVEL).cc include/$(DESIGN_NAME)_$(ABSTRACTION_LEVEL).hh
	@echo Building $@
	$(CXX) -g $(CFLAGS) $(INCDIR) -o $@ $<


clean:
	@echo Cleaning
	@rm -f obj/*.o *~
	@rm -f $(EXECUTABLE)

.PHONY: all clean
