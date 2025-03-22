# CodeSigning
This project focuses on a study of code signing, which is a process that uses digital certificates to verify the authenticity and integrity of software, scripts, and other files.

> This project utilizes the wolfSSL cryptographic library to implement Elliptic Curve Function (ECC), random number generation, and SHA-256 hashing.

### Required definitions:
`define HAVE_ECC`
`#define WOLFSSL_SHA256`

### Execution
1. Compile the `generator.c` `product.c` `signor.c` and `validator.c` files:
```sh
   gcc -o keygenerator generator.c -lwolfssl
   gcc -o product.bin product.c
   gcc -o signor signor.c -lwolfssl
   gcc -o validator validator.c -lwolfssl
```
2. Run the executables:
```sh
    ./keygenerator
    ./signor
    ./validator
```