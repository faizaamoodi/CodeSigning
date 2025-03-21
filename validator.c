#include <wolfssl/options.h>
#include <wolfssl/wolfcrypt/ecc.h>
#include <wolfssl/wolfcrypt/sha256.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRODUCTFILE "product.bin"

int main()
{
    // variable placeholders:
    ecc_key key;
    Sha256 sha;

    FILE *productFile;
    byte pubKey[256], hash[WC_SHA256_DIGEST_SIZE], signature[256];
    word32 pubKeyLen, signLen;

    // initializations:
    wolfCrypt_Init();
    wc_ecc_init(&key);

    // read public key
    FILE *pubFile = fopen("pubKey.bin", "rb");
    pubKeyLen = fread(pubKey, 1, sizeof(pubKey), pubFile);
    fclose(pubFile);

    // import public key
    wc_ecc_import_x963(pubKey, pubKeyLen, &key);

    // read signature
    FILE *signFile = fopen("signature.bin", "rb");
    signLen = fread(signature, 1, sizeof(signature), signFile);
    fclose(signFile);

    // open the product executable binary
    productFile = fopen(PRODUCTFILE, "rb");

    // initialize sha256 hash
    wc_InitSha256(&sha);

    byte buffer[1024];
    size_t bytesRead;
    // read and compute hash of product executable
    while((bytesRead = fread(buffer, 1, sizeof(buffer), productFile)) > 0)
    {
        wc_Sha256Update(&sha, buffer, bytesRead);
    }
    fclose(productFile);

    // final hash
    wc_Sha256Final(&sha, hash);

    int tempVal;        // required to store result of verification

    // read and compute hash value
    wc_ecc_verify_hash(signature, signLen, hash, WC_SHA256_DIGEST_SIZE, &tempVal, &key);

    // result of certificate verification
    if(tempVal)
    {
        printf("code certificate valid: execution allowed\n");
    } else
    {
        printf("code certificate invalid: execution denied\n");
    }

    // cleanup/ free
    wc_ecc_free(&key);
    wolfCrypt_Cleanup();
}