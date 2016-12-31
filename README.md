# Vigenère cipher

A school project to create a binary Vigenère cipher in C.

## Console examples

Encipher(create image.png.encrypted)
```
$ vigenere image.png
What is your passphrase? MyComplexPassphrase
```

Decipher(create image.png)
```
$ vigenere -d image.png.encrypted
What is your passphrase? MyComplexPassphrase
```

Get passphrase with clear file and encrypted file
```
$ vigenere -hack image.png image.png.encrypted
The pass phrase used was: MyComplexPassphras
```
