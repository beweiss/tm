elf_targets += tm_test
targets += $(elf_targets)
rm_targets += $(elf_targets)

#LFLAGS   = -L$(LIBDIR) -Wl,-rpath=$(LIBDIR) -Wall -Werror -ltm
include $(MBUILD)/Makefile.build

tm_test: LDFLAGS += -L$(TREE) -ltm
tm_test: CFLAGS += -Wl,-rpath=$(TREE)
tm_test: tm_test.c.o $(TREE)/libtm.so
