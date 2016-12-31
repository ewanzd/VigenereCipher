// Encipher(create for example image.png.encrypted)
// $ vigenere image.png
// What is your passphrase? MyComplexPassphrase

// Decipher(create for example image.png)
// $ vigenere -d image.png.encrypted
// What is your passphrase? MyComplexPassphrase

// $ vigenere -hack image.png image.png.encrypted
// The pass phrase used was: MyComplexPassphrase

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "viglib.h"

#define TXT_PASSPHRASE "What is your passphrase"
#define TXT_CANTOPEN "Can't open file!"
#define TXT_FILEATT ".encrypted"

#define SIZE_PHRASE 256
#define SIZE_PATH 256

char* getPassphrase();
char* file_read(char*);
void file_write(char*, char*);
void error(char*);

typedef enum {
    ENCIPHER,
    DECIPHER,
    HACK
} vigmode;

int main(int argc, char **argv) {
    // default mode(no extra argument)
    vigmode vigenere_mode = ENCIPHER;

    // analyse arguments
    char path[SIZE_PATH] = "test.txt";

    // analyse
    switch (vigenere_mode) {
        case ENCIPHER: {
            char* passphrase = getPassphrase();
            char* data = file_read(path);
            encipher_vigenere(data, passphrase);
            strcat(path, TXT_FILEATT);
            file_write(path, data);
            break;
        }
        case DECIPHER: {
            break;
        }
        case HACK: {
            break;
        }
    }

    return 0;
}

char* getPassphrase() {
    char* passphrase = (char*)malloc(sizeof(char) * SIZE_PHRASE);
    printf("%s? ", TXT_PASSPHRASE);
    scanf("%s", passphrase);
    return passphrase;
}

char* file_read(char* file_name) {
    FILE *file_pointer = NULL;
    char *buffer = NULL;
    size_t size = 0;

    // Open file in read-only mode
    file_pointer = fopen(file_name, 'r');

    // Cant open fail(not available?)
    if (!file_pointer) {
        error(TXT_CANTOPEN);
    }

    // Get the buffer size
    fseek(file_pointer, 0L, SEEK_END);
    size = ftell(file_pointer);

    // Set position of stream to the beginning
    rewind(file_pointer);

    // Allocate the buffer (no need to initialize it with calloc)
    // size + 1 byte for the \0
    buffer = malloc((size + 1) * sizeof(*buffer));

    // Read the file into the buffer
    // Read 1 chunk of size bytes from file_pointer into buffer
    fread(buffer, size, 1, file_pointer);

    // NULL-terminate the buffer
    buffer[size] = '\0';

    fclose(file_pointer);
    return buffer;
}

void file_write(char* file_name, char* content) {
    FILE *file_pointer = fopen(file_name, 'w');
    fprintf(file_pointer, content);
    fclose(file_pointer);
}

void error(char* message) {
    puts(message);
    exit(1);
}
