/**
* @author Danilo Wanzenried
* @required viglib.c
*
* @desc File help to encipher and decipher files with 'vigenere cipher'. It is
* possible too to hack the passphrase with clear and encrypted file.
* https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher
*
* Examples:
* Encipher(create for example image.png.encrypted)
* $ vigenere image.png
* What is your passphrase? MyComplexPassphrase

* Decipher(create for example image.png)
* $ vigenere -d image.png.encrypted
* What is your passphrase? MyComplexPassphrase

* $ vigenere -hack image.png image.png.encrypted
* The pass phrase used was: MyComplexPassphrase
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "viglib.h"

// constants
#define TXT_PHRASEIN "What is your passphrase"
#define TXT_PHRASEOUT "The pass phrase used was"
#define TXT_CANTOPEN "Can't open file!"
#define TXT_NOTENOUGHARGS "There aren't enough arguments!"
#define TXT_WRONGFILEEND "File must end with '.encrypted'!"
#define TXT_FILESNOTSAMELEN "Files haven't the same len!"
#define TXT_FILEATT ".encrypted"

#define MAXSIZE_PHRASE 64
#define MAXSIZE_PATH 256

// enum with three modes determine by arguments
typedef enum {
    ENCIPHER,
    DECIPHER,
    HACK
} vigmode;

// console arguments
typedef struct {
    vigmode vigenere_mode;
    char path_clear[MAXSIZE_PATH];
    char path_cipher[MAXSIZE_PATH];
} vigargs;

// function definitions
vigargs* args_analyse(int, char**);
void vig_run(vigargs*);
char* get_passphrase();
void file_read(const char*, unsigned char**, unsigned long*);
void file_write(const char*, unsigned char*, unsigned long);
int strend(const char*, const char*);
void error(const char*);

/**
* @desc entry point from this program
* @param int argc - count of arguments
* @param char **argv - all arguments as string
* @return int - exit number to check wether the program finish successful
*/
int main(int argc, char **argv) {

    // analyse arguments
    vigargs* args = args_analyse(argc, argv);

    // run vigenere based on arguments
    vig_run(args);

    // all worked correctly
    return 0;
}

/**
* @desc analyse arguments from user and is responsible to check
* if the input is valid.
* @param int argc - count of arguments
* @param char **argv - all arguments as string
* @return vigargs* - a categorized structure with all arguments
*/
vigargs* args_analyse(int argc, char **argv) {

    // it need at least one additional argument
    if(argc < 2) error(TXT_NOTENOUGHARGS);

    // create data structure
    vigargs *app_arguments = (vigargs*)malloc(sizeof(vigargs));

    // analyse arguments and set values
    if (strcmp(argv[1], "-d") == 0) {

        // array need at least 2 arguments
        if(argc < 3) error(TXT_NOTENOUGHARGS);

        // file must end with '.encrypted'
        if(!strend(argv[2], TXT_FILEATT)) error(TXT_WRONGFILEEND);

        // set mode to decipher
        app_arguments->vigenere_mode = DECIPHER;

        // copy path to encrypt file to structure
        strcpy(app_arguments->path_cipher, argv[2]);
    } else if (strcmp(argv[1], "-hack") == 0) {

        // array need at least 3 arguments
        if(argc < 4) error(TXT_NOTENOUGHARGS);

        // file must end with '.encrypted'
        if(!strend(argv[3], TXT_FILEATT)) error(TXT_WRONGFILEEND);

        // set mode to hack
        app_arguments->vigenere_mode = HACK;

        // copy path to clear file to structure
        strcpy(app_arguments->path_clear, argv[2]);

        // copy path to encrypt file to structure
        strcpy(app_arguments->path_cipher, argv[3]);
    } else {

        // set mode to encipher
        app_arguments->vigenere_mode = ENCIPHER;

        // copy path to encrypt file to structure
        strcpy(app_arguments->path_clear, argv[1]);
    }

    // return argument structure
    return app_arguments;
}

/**
* @desc get data from file, de-/encipher data and save to new file
* @param vigargs *args - structure with a description what to do
*/
void vig_run(vigargs *args) {

    // analyse
    switch (args->vigenere_mode) {
        case ENCIPHER: {
            unsigned char *data_clear;
            unsigned long data_clear_len;

            // get content(pointer to buffer stream) from file
            file_read(args->path_clear, &data_clear, &data_clear_len);

            // get passphrase from user
            char *passphrase = get_passphrase();

            // encipher file content with passphrase
            vig_encipher(data_clear, data_clear_len, passphrase);

            // copy path to encrypt file to structure
            // no new char array to save memory
            strcpy(args->path_cipher, args->path_clear);

            // attach '.encrypted' to path
            strcat(args->path_cipher, TXT_FILEATT);

            // output file with encrypted data
            file_write(args->path_cipher, data_clear, data_clear_len);
            break;
        }
        case DECIPHER: {
            unsigned char *data_cipher;
            unsigned long data_cipher_len;

            // get pointer to buffer stream from file
            file_read(args->path_cipher, &data_cipher, &data_cipher_len);

            // get passphrase from user
            char *passphrase = get_passphrase();

            // decipher file content with passphrase
            vig_decipher(data_cipher, data_cipher_len, passphrase);

            // copy path to encrypt file to structure
            strcpy(args->path_clear, args->path_cipher);

            // find len of string
            int len = strlen(args->path_clear);

            // remove .encrypted from path(set NULL on point '.')
            args->path_clear[len - 10] = '\0';

            // output file with encrypted data
            file_write(args->path_clear, data_cipher, data_cipher_len);
            break;
        }
        case HACK: {
            unsigned char *data_clear, *data_cipher;
            unsigned long data_clear_len, data_cipher_len;

            // get pointer to buffer stream from file with clear text
            file_read(args->path_clear, &data_clear, &data_clear_len);

            // get pointer to buffer stream from file with encrypted text
            file_read(args->path_cipher, &data_cipher, &data_cipher_len);

            // find passphrase with clear and encrypted text
            char *passphrase = (char*)malloc(sizeof(char) * MAXSIZE_PHRASE);

            // get passphrase with both byte arrays
            int error_code = vig_passphrase(passphrase, data_clear, data_clear_len,
                data_cipher, data_cipher_len);

            // error while get passphrase
            if(error_code != 0) error(TXT_FILESNOTSAMELEN);

            // print result to console
            printf("%s: %s\n", TXT_PHRASEOUT, passphrase);
            break;
        }
    }
}

/**
* @desc get user input with passphrase as char array
* @return char* - a string with passphrase from user
*/
char* get_passphrase() {

    // allocate new space for passphrase
    char *passphrase = (char*)malloc(sizeof(char) * MAXSIZE_PHRASE);

    // ask for passphrase
    printf("%s? ", TXT_PHRASEIN);

    // read user input from console
    scanf("%s", passphrase);

    // return char array
    return passphrase;
}

/**
* @desc get content from file 'file_name' as char array
* @param const char *file_name - file name(and path) to file for read
* @return char* - content from file as char(byte) array
*/
void file_read(const char *file_name, unsigned char **buffer, unsigned long *size) {

    // declare variables to default value
    FILE *file_pointer = NULL;
    *size = 0;

    // open file in read-only mode
    file_pointer = fopen(file_name, "rb");

    // can't open file(not available?)
    if (!file_pointer) {
        error(TXT_CANTOPEN);
    }

    // set pointer to end of file
    fseek(file_pointer, 0L, SEEK_END);

    // get the buffer size
    *size = ftell(file_pointer);

    // set position of stream to the beginning
    fseek(file_pointer, 0L, SEEK_SET);

    // allocate the buffer
    *buffer = (unsigned char*)malloc(*size * sizeof(unsigned char));

    // read the file into the buffer
    fread(*buffer, *size, sizeof(unsigned char), file_pointer);

    // close file stream
    fclose(file_pointer);
}

/**
* @desc write char array to file
* @param const char *file_name - file name(and path) to file for write
* @param const char *content - char(byte) array for write to file
*/
void file_write(const char *file_name, unsigned char *buffer, unsigned long buffer_len) {

    // Create file and open
    FILE *file_pointer = fopen(file_name, "wb");

    // put char array to file
    fwrite(buffer, buffer_len, 1, file_pointer);

    // close file
    fclose(file_pointer);
}

/**
* @desc check end of string is equal
* @param const char *string - full string
* @param const char *endwith - string whose full string should end with
* @return int - 1 if equal, 0 not equal
*/
int strend(const char *string, const char *endwith) {

    // get len of string
    size_t string_len = strlen(string);

    // get len of endwith
    size_t endwith_len = strlen(endwith);

    // check if 'string' is equal or bigger than 'endwith'
    if (string_len >= endwith_len) {
        // check if the last part of 'string' is equal 'endwith', then return 1
        return (0 == memcmp(endwith, string + (string_len - endwith_len), endwith_len));
    }

    // string_len was shorter than endwith_len
    return 0;
}

/**
* @desc put message to console and exit program
* @param const char *message - string with error message
*/
void error(const char *message) {

    // put message to console
    puts(message);

    // exit program
    exit(1);
}
