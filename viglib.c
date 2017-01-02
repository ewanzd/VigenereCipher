// 1) clear text + passphrase = encrypted text
// 2) encrypted text - passphrase = clear text
// 3) encrypted text - clear text = passphrase

// - passphrase will begin on start if loop reach the end
// - modulo 256

#include <string.h>

void cipher(char[], size_t, char[], size_t, unsigned short);

/*
*
*/
void vig_encipher(char text[], char passphrase[]) {
    //
    size_t text_len = strlen(text);

    //
    size_t passphrase_len = strlen(passphrase);

    //
    cipher(text, text_len, passphrase, passphrase_len, 1);
}

/*
*
*/
void vig_decipher(char text[], char passphrase[]) {
    //
    size_t text_len = strlen(text);

    //
    size_t passphrase_len = strlen(passphrase);

    //
    cipher(text, text_len, passphrase, passphrase_len, 0);
}

/*
*
*/
void cipher(char text[], size_t text_len, char passphrase[], size_t passphrase_len, unsigned short encipher) {
    // declare counters
    int i, j;

    // loop every byte in text
    for (i = 0, j = 0; i < text_len; i++) {
        // get position from passphrase
        unsigned short c = passphrase[j];

        // plus if encipher and minus if decipher
        c = text[i] + ((encipher) ? c : -c);

        // char can't be bigger than 256
        text[i] = c % 256;

        // reset passphrase counter
        if(j++ == passphrase_len) j = 0;
    }
}

/*
*
*/
char* vig_passphrase(char clearText[], char encryptedText[]) {

}
