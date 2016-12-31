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

#define TXT_PHRASEIN "What is your passphrase"
#define TXT_PHRASEOUT "The pass phrase used was"
#define TXT_CANTOPEN "Can't open file!"
#define TXT_FILEATT ".encrypted"

#define SIZE_PHRASE 256
#define SIZE_PATH 256

char* getPassphrase();
char* file_read(char*);
void file_write(char*, char*);
void error(char*);

// enum with three modes determine by arguments
typedef enum {
    ENCIPHER,
    DECIPHER,
    HACK
} vigmode;

// entry point
int main(int argc, char **argv) {
    // default mode(no extra argument)
    vigmode vigenere_mode = ENCIPHER;

    // analyse arguments ...
    char path[SIZE_PATH] = "test.txt";

    // analyse
    switch (vigenere_mode) {
        case ENCIPHER: {
            // get content from file
            char* file_data = file_read(path);

            // get passphrase from user
            char* passphrase = getPassphrase();

            // encipher file content with passphrase
            vig_encipher(file_data, passphrase);

            // create path for new file
            strcat(path, TXT_FILEATT);

            // output file with encrypted data
            file_write(path, file_data);
            break;
        }
        case DECIPHER: {
            // get content from file
            char* file_data = file_read(path);

            // get passphrase from user
            char* passphrase = getPassphrase();

            // decipher file content with passphrase
            vig_decipher(file_data, passphrase);

            // create path for new file(remove '.encrypted')
            int len = strlen(path);
            path[len - 10] = '\0';

            // output file with encrypted data
            file_write(path, file_data);
            break;
        }
        case HACK: {
            break;
        }
    }

    return 0;
}

// get user input with passphrase as char array
char* getPassphrase() {
    // allocate new space for passphrase
    char* passphrase = (char*)malloc(sizeof(char) * SIZE_PHRASE);

    // ask for passphrase
    printf("%s? ", TXT_PHRASEIN);

    // read user input from console
    scanf("%s", passphrase);

    // return char array
    return passphrase;
}

// get content from file 'file_name' as char array
char* file_read(char* file_name) {
    // declare variables to default value
    FILE *file_pointer = NULL;
    char *buffer = NULL;
    size_t size = 0;

    // open file in read-only mode
    file_pointer = fopen(file_name, "r");

    // can't open file(not available?)
    if (!file_pointer) {
        error(TXT_CANTOPEN);
    }

    // get the buffer size
    fseek(file_pointer, 0L, SEEK_END);
    size = ftell(file_pointer);

    // set position of stream to the beginning
    rewind(file_pointer);

    // allocate the buffer
    // size + 1 byte for the \0
    buffer = malloc((size + 1) * sizeof(*buffer));

    // read the file into the buffer
    // read 1 chunk of size bytes from file_pointer into buffer
    fread(buffer, size, 1, file_pointer);

    // NULL-terminate the buffer
    buffer[size] = '\0';

    // close file stream
    fclose(file_pointer);

    // return char array
    return buffer;
}

// write char array to file(need /0 at end!)
void file_write(char* file_name, char* content) {
    // Create file and open
    FILE *file_pointer = fopen(file_name, "w");

    // put char array to file
    fprintf(file_pointer, content);

    // close file
    fclose(file_pointer);
}

// put message to console and exit program
void error(char* message) {
    // put message to console
    puts(message);

    // exit program
    exit(1);
}
