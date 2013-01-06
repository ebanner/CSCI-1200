# Makefile -- creates a kernel image
#          --  + bootable by QEMU
#          --  + used to make a bootable floppy for bochs    

CC   := g++
RM   := rm

CFILES   := $(shell find $(PROJDIRS) -type f -name '*.c')
GCHFILES   := $(shell find $(PROJDIRS) -type f -name '*.gch')

# gcc flags
CFLAGS := -g

# This is what gets executed when we just type `make'.
all: $(CFILES)
	$(CC) $(CFLAGS) $(CFILES) -o multill

# `-@' tells make to continue even on error and to be silent
clean :
	-@$(RM) $(GCHFILES)

# Create a phony target so if one of these targets are passed to make, make
# won't check to see if it is actually a file in our currect directory.
.PHONY: all clean
