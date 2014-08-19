VERSION = 3.02
CC	= /usr/bin/gcc
CFLAGS	= -Wall -g -fPIC
LINKER   = gcc -shared -o
LFLAGS   = -Wall -Werror
SRCDIR= src
OBJDIR= obj
LIBDIR= lib

TARGET = libtm.so

SOURCES  := $(wildcard $(SRCDIR)/*.c)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f

$(LIBDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONEY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONEY: remove
remove: clean
	@$(rm) $(LIBDIR)/$(TARGET)
	@echo "Executable removed!"
