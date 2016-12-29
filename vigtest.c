// Encipher(create for example image.png.encrypted)
// $ vigenere image.png
// What is your passphrase? MyComplexPassphrase

// Decipher(create for example image.png)
// $ vigenere -d  image.png.encrypted
// What is your passphrase? MyComplexPassphrase

// $ vigenere -hack image.png image.png.encrypted
// The pass phrase used was: MyComplexPassphrase

#include <stdio.h>
#include <string.h>
#include "viglib.h"

int main(int argc, char **argv) {
    char text[] = "PingPong";
    int textSize = strlen(text);
    char passphrase[] = "Hello";
    int passphraseSize = strlen(passphrase);

    printf("Text %s\n", text);

    encipher_vigenere(text, textSize, passphrase, passphraseSize);
    printf("Encipher %s\n", text);

    decipher_vigenere(text, textSize, passphrase, passphraseSize);
    printf("Decipher %s\n", text);
    return 0;
}
