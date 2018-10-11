SOURCES:=$(wildcard *.c)
TARGETS:=$(patsubst %.c, %.out, $(SOURCES))

# This _GNU_SOURCE macro is for non-posix extension
# pthread_setaffinity_np, the np suffix is sign for non-posix
CPPFLAGS:=-D_GNU_SOURCE
CFLAGS:=-g -O0
LIBS:=-lpthread
all:$(TARGETS) 
	@:

$(TARGETS):%.out:%.c
	@$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ $(LIBS)

clean:
	@rm *.out
