# Vigenère cipher

A application which offer the functionality to encrypt and decrypt all kind of files with [Vigenère cipher](https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher). The encrypted files are proctected with a special passphrase. When you own the origin file and encrypted file, you can find the passphrase.

## Run

To run the application you need first a C compiler (e.g. visual studio, mingw or cygwin for windows). l In all three examples for compiler are also included a possibility to run makefiles. Then clone this project to a folder of your choice. To easily run the program, call `make` in the console in the folder with the project files and run console examples below.

## Console examples

`image.png` is only an example file. In your case choice a own file to encrypt.

Encipher(will create image.png.encrypted)
```
$ vigenere image.png
What is your passphrase? MyComplexPassphrase
```

Decipher(will create image.png)
```
$ vigenere -d image.png.encrypted
What is your passphrase? MyComplexPassphrase
```

Get passphrase with clear file and encrypted file
```
$ vigenere -hack image.png image.png.encrypted
The pass phrase used was: MyComplexPassphras
```
