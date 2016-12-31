# Compiler to use
CC=gcc
# Pass flags to the compiler
CFLAGS=-c -g
# Pass flags for linking
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
	$(CC) -o $(EXEC) $(OBJECTS)  $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) $<

clean:
	$(DELETECMD) -rf $(OBJECTS) $(EXEC)
