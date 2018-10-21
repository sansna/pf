SOURCES=$(wildcard *.c)
TARGETS=$(patsubst %.c,%.out,$(SOURCES))
LIBS=-lpthread
#CPPFLAGS=-D_DEBUG
CFLAGS=-g -O2
all: $(TARGETS)

$(TARGETS):%.out:%.c
	@$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBS)

clean:
	@rm *.out
