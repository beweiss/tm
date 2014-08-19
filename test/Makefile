VERSION = 3.02
CC	= /usr/bin/gcc
CFLAGS	= -Wall -g
LINKER   = gcc -o
LIBDIR := ../lib/
LFLAGS   = -L$(LIBDIR) -Wl,-rpath=$(LIBDIR) -Wall -Werror -ltm
BINDIR= bin
SRCDIR= src
OBJDIR= obj

TARGET = tm_test

SOURCES  := $(SRCDIR)/tm_test.c
OBJECTS  := $(OBJDIR)/tm_test.o
rm       = rm -f

$(BINDIR)/$(TARGET): libtm.so $(OBJECTS)
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONEY: libtm.so
libtm.so:
	cd .. && $(MAKE)

.PHONEY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONEY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"
