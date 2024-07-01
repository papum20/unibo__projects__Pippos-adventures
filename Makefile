
## PROJECT'S REQUIREMENTS

BDIR = bin
IDIR = include
IDIRS = $(wildcard $(IDIR)/*) # include sub-directories
ODIR = obj
SDIR = src
SDIRS = $(wildcard $(SDIR)/*) # source sub-directories
EXE_NAME = pippos-adventures

INCS = $(wildcard $(IDIR)/*/*.hpp)

# obj directory structure copies the structure of the main folder (.)
_OBJS_NAMES = $(wildcard $(SDIR)/*/*.cpp)
OBJS = $(patsubst %.cpp, $(ODIR)/$(notdir %).o, $(_OBJS_NAMES))


## COMMANDS

DEFS = $(INCS) Makefile

# CFLAGS suggested by project pdf
# CFLAGS = -ffreestanding -ansi -Wall -c -mips1 -mabi=32 -mfp32 \
# 	-mno-gpopt -G 0 -fno-pic -mno-abicalls -o
# this CFLAGS' options:
# std=gnu99 supports: inline, typeof
CFLAGS = -c -o
CFLAGSINC = -iquote$(IDIR)
# CFLAGSINC = $(patsubst %, -iquote%, $(IDIRS))	# all subdirs too
LDFLAGS = -lncurses

CC = g++
LD = g++


# keep the .o
.PRECIOUS: $(ODIR)/*


## MAKE


# main target

.PHONY: all
all: mk_obj_dirs src exe


.PHONY: exe
exe: $(BDIR)/$(EXE_NAME)
$(BDIR)/$(EXE_NAME): $(OBJS)
	$(LD) -o $(BDIR)/$(EXE_NAME) $(OBJS) $(LDFLAGS)

.PHONY: src
src: $(OBJS)

#objects
$(ODIR)/%.o: %.cpp $(DEFS) 
	$(CC) $(CFLAGS) $@ $< $(CFLAGSINC)


# create src directories structure in obj dir

.PHONY: mk_obj_dirs
mk_obj_dirs:
	@mkdir -p $(patsubst %, $(ODIR)/%, $(SDIRS)) $(BDIR)


# show help screen

.PHONY: help
help: 
	@echo "make"
	@echo "make			: make mk_obj_dirs && make src"
	@echo "make src		: compile src"
	@echo "make exe		: make executable, after object files"
	@echo "make mk_obj_dirs	: create output dirs tree (obj/*)"
	@echo "make help		: show this help message"
	@echo "make clean		: clean"


# sets the tests to compile, if specified as make command-line arguments

	


# CLEAN
.PHONY: clean
clean:
	rm $(wildcard $(ODIR)/$(SDIR)/*/*.o) $(BDIR)/$(filter-out .placeholder, *)