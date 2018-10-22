SOURCES=$(wildcard *.c)
TARGETS=$(patsubst %.c,%.out,$(SOURCES))
LIBS=-lpthread
#CPPFLAGS=-D_DEBUG -D_LINGER -DM=1000
CFLAGS=-g -O2
all: $(TARGETS)

$(TARGETS):%.out:%.c
	@$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBS)

clean:
	@rm *.out
