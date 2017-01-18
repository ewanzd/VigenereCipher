/**
* @author Danilo Wanzenried
*
* @desc File help to encipher and decipher files with 'vigenere cipher'. It is
* possible too to hack the passphrase with clear and encrypted file.
*
* 1) clear text + passphrase = encrypted text
* 2) encrypted text - passphrase = clear text
* 3) encrypted text - clear text = passphrase
*/

#include <string.h>
#include <stdio.h>

// function definitions
void cipher(char[], unsigned long, const char[], unsigned char);

/**
* @desc encipher byte array with vigenere
* @param char bytes[] - byte array to encipher
* @param unsigned long bytes_len - len of byte array
* @param const char passphrase[] - the key to encipher bytes
*/
void vig_encipher(char bytes[], unsigned long bytes_len, const char passphrase[]) {

    // encipher bytes with key
    cipher(bytes, bytes_len, passphrase, 1);
}

/**
* @desc decipher byte array with vigenere
* @param char bytes[] - byte array to decipher
* @param unsigned long bytes_len - len of byte array
* @param const char passphrase[] - the key to decipher bytes
*/
void vig_decipher(char bytes[], unsigned long bytes_len, const char passphrase[]) {

    // decipher bytes with key
    cipher(bytes, bytes_len, passphrase, 0);
}

/**
* @desc decipher or encipher byte array with vigenere
* @param char bytes[] - byte array to de-/encipher
* @param unsigned long bytes_len - len of byte array
* @param const char passphrase[] - the key to de-/encipher bytes
* @param unsigned char encipher - (bool) 1 for encipher, 0 for decipher
*/
void cipher(char bytes[], unsigned long bytes_len, const char passphrase[],
    unsigned char encipher) {

    // get size of passphrase
    size_t passphrase_len = strlen(passphrase);

    // loop every byte in array
    unsigned long i, j;
    unsigned short c;
    for (i = 0, j = 0; i < bytes_len; i++) {

        // plus if encipher and minus if decipher
        c = bytes[i] + ((encipher) ? passphrase[j] : -passphrase[j]);

        // char can't be bigger than 256
        bytes[i] = c % 256;

        // reset passphrase counter
        if(++j == passphrase_len) j = 0;
    }
}

/**
* @desc find passphrase with clear and encrypted bytes
* @param char passphrase[] - result will return in this char array
* @param const char clear_bytes[] - clear byte array
* @param unsigned long clear_bytes_len - len of clear byte array
* @param const char encrypted_bytes[] - encrypted byte array
* @param unsigned long encrypted_bytes_len - len of encrypted byte array
* @return int - error code (0 - successful, 1 - not same len)
*/
int vig_passphrase(char passphrase[], const unsigned char clear_bytes[],
    unsigned long clear_bytes_len, const unsigned char encrypted_bytes[],
    unsigned long encrypted_bytes_len) {

    // check if both arrays have the same len
    if(clear_bytes_len != encrypted_bytes_len) return 1;

    // initialize new temp byte array with result between both arrays
    unsigned char temp_bytes[clear_bytes_len];

    // loop all bytes in clear_bytes and encrypted_bytes
    for (unsigned long i = 0; i < clear_bytes_len; i++) {

        // encrypted_bytes minus clear_bytes to get passphrase
        temp_bytes[i] = (encrypted_bytes[i] - clear_bytes[i]) % 256;
    }

    // bool to check if innerloop quit normal or with 'break'
    unsigned char finished = 0;

    // find the length of the passphrase
    unsigned long i, j, last_equal = 0;
    while (finished == 0) {

        // loop every char until the sequences are difference
        for (finished = 1, j = 0, i = last_equal; i < clear_bytes_len; j++, i++) {

            // start again if phrase reach the end
            if(j >= last_equal) j = 0;

            // check wether both sequences are equal
            if(passphrase[j] != temp_bytes[i]) {

                // they werent equal, so add new char to phrase
                passphrase[last_equal] = temp_bytes[last_equal];

                // to next char in phrase
                last_equal++;

                // start again
                finished = 0;

                // loop havent run to end
                break;
            }
        }
    }

    // set NULL to the end of passphrase
    passphrase[last_equal] = '\0';

    // all was successful
    return 0;
}
