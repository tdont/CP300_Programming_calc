# Allow the command to be displayed
VERBOSE ?= FALSE

# Hide or not based on VERBOSE
ifeq ($(VERBOSE),TRUE)
    HIDE =
else
    HIDE = @
endif


DEV_CPP_PATH = C:/Program\ Files\ \(x86\)/Dev-Cpp/
DEV_CPP_BIN = Bin/
DEV_CPP_LIB = lib
CLASSPAD_PATH = C:/PROGRA~2/CASIO/CLASSP~2/
CLASSPAD_LIB = lib/
CLASSPAD_INC = CP_Include

TARGET_DIRECTORY = outputdir/
SRC_DIRECTORY = ./

APP_CPP_SRC= $(wildcard $(SRC_DIRECTORY)*.cpp) 
APP_CPP_OBJ := $(subst $(SRC_DIRECTORY),$(TARGET_DIRECTORY),$(APP_CPP_SRC:.cpp=.o))

CPP  = $(DEV_CPP_PATH)$(DEV_CPP_BIN)g++.exe -D__DEBUG__
CC   = $(CPP)

WINDRES = windres.exe
RES  = 
OBJ  = $(TARGET_DIRECTORY)/Pegmain.o \
			$(TARGET_DIRECTORY)/HelloWindow.o\
			$(RES)
LIBS =  -L"$(DEV_CPP_PATH)$(CLASSPAD_LIB)" -g "$(CLASSPAD_PATH)$(CLASSPAD_LIB)/gcc_main.a" "$(CLASSPAD_PATH)$(CLASSPAD_LIB)/ClassPadDLLgcc.a" -w  -g3 
INCS =  -I"$(CLASSPAD_PATH)$(CLASSPAD_INC)" 
CXXINCS =  -I"$(CLASSPAD_PATH)$(CLASSPAD_INC)" 

CXXFLAGS = $(CXXINCS)   -DWIN32 -w -g3
CFLAGS = $(INCS)   -DWIN32 -w -g3

BINARY  = $(TARGET_DIRECTORY)/ProgrammingCalc.exe


VPATH = $(SRC_DIRECTORY)

${TARGET_DIRECTORY}%.o: %.cpp
	@echo "CXX    $?"	
	$(HIDE)$(CPP) -c $< -o $@ $(CXXFLAGS)

all: directory all-before $(BINARY) all-after

directory:
	$(HIDE)mkdir -p $(TARGET_DIRECTORY)

clean: clean-custom
	rm -f $(OBJ) $(BINARY)

mrproper:
	rm -rf $(TARGET_DIRECTORY)

$(BINARY): $(APP_CPP_OBJ)
	@echo "LD     $(BINARY)"
	$(HIDE)$(CPP) $(APP_CPP_OBJ) -o "$(BINARY)" $(LIBS)

.PHONY: all all-before all-after clean clean-custom mrproper