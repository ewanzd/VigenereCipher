# Compiler to use
CC=gcc
# Pass flags to the compiler
CFLAGS=-c -g
# All sources to compile
SOURCES=viglib.c vigtest.c
# All ObjectFiles to link
OBJECTS=$(SOURCES:.c=.o)
# Executable file
EXECUTABLE=vigenere.exe
# Change "del" to "rm" for linux
DELETECMD=del

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $(EXECUTABLE) $(OBJECTS)

.c.o:
	$(CC) $(CFLAGS) $<

clean:
	$(DELETECMD) -rf $(OBJECTS) $(EXECUTABLE)
