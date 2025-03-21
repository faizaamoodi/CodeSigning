#include <wolfssl/options.h>
#include <wolfssl/wolfcrypt/ecc.h>
#include <wolfssl/wolfcrypt/random.h>
#include <wolfssl/wolfcrypt/sha256.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRODUCTFILE "product.bin"

int main()
{
    // variable placeholders:
    ecc_key key;
    WC_RNG rng;         // wolfSSL secure PRG
    Sha256 sha;

    FILE *productFile;
    byte privKey[256], hash[WC_SHA256_DIGEST_SIZE], signature[256];
    word32 privKeyLen, signLen = sizeof(signature);

    // initializations:
    wolfCrypt_Init();
    wc_InitRng(&rng);
    wc_ecc_init(&key);
    wc_InitSha256(&sha);

    // read private key
    FILE *privFile = fopen("privKey.bin", "rb");
    privKeyLen = fread(privKey, 1, sizeof(privKey), privFile);
    fclose(privFile);

    // import private key
    wc_ecc_import_private_key(privKey, privKeyLen, NULL, 0, &key);

    // prepare and hash the product executable (binary file)
    byte buffer[1024];
    size_t bytesRead;

    productFile = fopen(PRODUCTFILE, "rb");
    while((bytesRead = fread(buffer, 1, sizeof(buffer), productFile)) > 0)
    {
        wc_Sha256Update(&sha, buffer, bytesRead);
    }
    fclose(productFile);

    wc_Sha256Final(&sha, hash);     // completed hash

    // sign the binary's hash
    wc_ecc_sign_hash(hash, WC_SHA256_DIGEST_SIZE, signature, &signLen, &rng, &key);

    // saving/ storing signature
    FILE *signFile = fopen("signature.bin", "wb");
    fwrite(signature, 1, signLen, signFile);
    fclose(signFile);

    // feedback
    printf("signature successfully generated and stored\n");

    // cleanup/ free
    wc_ecc_free(&key);
    wc_FreeRng(&rng);
    wolfCrypt_Cleanup();
}