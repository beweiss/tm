CC		 = gcc -c
CCLD		 = gcc
MERGE		 = ld -r
LD		 = ld
LDSO		 = ld

RM		 = rm -f
STRIP		 = strip

CFLAGS		+= -Wall -ggdb
CPPFLAGS	+= -I$(TREE)/include
LDFLAGS		+= -ggdb

TREE		:= $(CURDIR)
MBUILD		 = $(TREE)/Makefile.build

export CC CCLD MERGE LD LDSO RM STRIP CFLAGS CPPFLAGS LDFLAGS TREE MBUILD \
       DEBUG

targets		+= libtm.so
rm_targets	+= libtm.so

desc_targets	 = src/ test/
targets		+= $(desc_targets)
clean_targets	+= $(desc_targets)

include $(MBUILD)/Makefile.build

libtm.so: src/src.o.o
