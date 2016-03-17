########################################################################
#                          -*- Makefile -*-                            #
########################################################################

COMPILER = g++

########################################################################
## Flags
FLAGS   = -g -std=c++11
LDFLAGS =
PREPRO  =
##verbose level 1
#DEBUG   = -D DEBUGV1
##verbose level 2
#DEBUG  += -D DEBUGV2
##verbose level 3
#DEBUG  += -D DEBUGV3
OPT     = -O2
WARN    = -Wall

### generate directory obj, if not yet existing
$(shell mkdir -p build)

########################################################################
## Paths

WORKINGDIR = $(shell pwd)
PARENTDIR  = $(WORKINGDIR)/..
NEURALNET  = $(WORKINGDIR)/Neural_Network

########################################################################
## search for the files and set paths

vpath %.cpp $(WORKINGDIR)
vpath %.cpp $(NEURALNET)
vpath %.m $(WORKINGDIR)
vpath %.a $(WORKINGDIR)/build
vpath %.o $(WORKINGDIR)/build
FINCLUDE = /Library/Frameworks/

########################################################################
## Includes
CXX  = $(COMPILER) $(FLAGS) $(OPT) $(WARN) $(DEBUG) $(PREPRO) -I$(WORKINGDIR) -I$(NEURALNET) -F$(FINCLUDE)
INCLUDE = $(wildcard *.h $(UINCLUDE)/*.h)

%.a: %.cpp $(INCLUDE)
	$(CXX) -c -o build/$@ $<

%.a: %.m $(INCLUDE)
	$(CXX) -c -o build/$@ $<

# Libraries
LIB =

# Frameworks
# -framework SDL_gfx 
FRM = -framework SDL2 -framework SDL2_image -framework SDL2_gfx -framework Cocoa

########################################################################
## Linker files

### USER Files ###
USER = Main.a Timer.a Object.a Tadpole.a SDL2_own.a
USER+= Neuron.a Brain.a Trainer.a Helper.a Interface.a Functions.a

########################################################################
## Rules
## type make -j4 [rule] to speed up the compilation

BUILD = $(USER)

Evolution: $(BUILD)
	  $(CXX) $(patsubst %,build/%,$(BUILD)) $(LDFLAGS) $(LIB) $(FRM) -o $@

clean:
	rm -f build/*.a Evolution

do:
	make && ./Evolution

########################################################################
#                       -*- End of Makefile -*-                        #
########################################################################
