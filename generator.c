#include <wolfssl/options.h>
#include <wolfssl/wolfcrypt/ecc.h>
#include <wolfssl/wolfcrypt/random.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    // variable placeholders:
    ecc_key key;
    WC_RNG rng;         // wolfSSL secure PRG

    FILE *privFile, * pubFile;
    byte privKey[256], pubKey[256];
    word32 privKeyLen = sizeof(privKey);
    word32 pubKeyLen = sizeof(pubKey);

    // initializations:
    wolfCrypt_Init();
    wc_InitRng(&rng);
    wc_ecc_init(&key);

    // generating ecc pub-priv key pair
    wc_ecc_make_key(&rng, 32, &key);

    // exporting private key
    wc_ecc_export_private_only(&key, privKey, &privKeyLen);

    // saving/ storing the private key
    privFile = fopen("privKey.bin", "wb");
    fwrite(privKey, 1, privKeyLen, privFile);
    fclose(privFile);

    // exporting public key
    wc_ecc_export_x963(&key, pubKey, &pubKeyLen);

    // saving/ storing the public key
    pubFile = fopen("pubKey.bin", "wb");
    fwrite(pubKey, 1, pubKeyLen, pubFile);
    fclose(pubFile);

    // feedback
    printf("pub-priv keys successfully generated and stored\n");

    // cleanup/ free
    wc_ecc_free(&key);
    wc_FreeRng(&rng);
    wolfCrypt_Cleanup();
}