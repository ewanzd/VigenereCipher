// 1) clear text + passphrase = encrypted text
// 2) encrypted text - passphrase = clear text
// 3) encrypted text - clear text = passphrase

// - passphrase will begin on start if loop reach the end
// - modulo 256

#include <stdbool.h>

void cipher(char[], int, char[], int, bool);

void encipher_vigenere(char text[], int textSize, char passphrase[], int passphraseSize) {
    cipher(text, textSize, passphrase, passphraseSize, true);
}

void decipher_vigenere(char text[], int textSize, char passphrase[], int passphraseSize) {
    cipher(text, textSize, passphrase, passphraseSize, false);
}

void cipher(char text[], int textSize, char passphrase[], int passphraseSize, bool encipher) {
    int i, j;
    for (i = 0, j = 0; i < textSize; i++) {
        char c = passphrase[j];
        c = text[i] + (encipher) ? c : -c;
        text[i] = c % 256;

        if(j++ == passphraseSize) j = 0;
    }
}

char* getPassphrase__vigenere(char clearText[], int clearTextSize, char encryptedText[], int encryptedTextSize) {

}
