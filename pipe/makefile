SOURCES:=$(wildcard *.c)
TARGETS:=$(patsubst %.c, %.out, $(SOURCES))
CPPFLAGS:=-D_GNU_SOURCE
CFLAGS:=-g -O0
LIBS:=-lpthread
all:$(TARGETS) 
	@:

$(TARGETS):%.out:%.c
	@$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ $(LIBS)

clean:
	@rm *.out
