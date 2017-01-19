# Compiler to use
CC=gcc
# Pass flags to the compiler
CFLAGS=-g
# Pass flags to the linker
LDFLAGS=
# All sources to compile
SOURCES=viglib.c vigmain.c
# All ObjectFiles to link
OBJECTS=$(SOURCES:.c=.o)
# Executable file
EXEC=vigenere.exe
# Change "del"(windows) to "rm" for linux
DELETECMD=del

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

.c.o:
	$(CC) -c $(CFLAGS) $<

clean:
	$(DELETECMD) -rf $(OBJECTS)
