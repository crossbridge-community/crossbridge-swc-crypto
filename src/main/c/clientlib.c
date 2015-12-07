/*
 * =BEGIN CLOSED LICENSE
 *
 *  Copyright (c) 2013 Docmet Systems
 *  http://www.docmet.com
 *
 *  For information about the licensing and copyright please
 *  contact us at info@docmet.com
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 *
 * =END CLOSED LICENSE
 */

/**
 *  ClientLib
 *  clientlib.c
 *  Purpose: Client library implementation
 *
 *  @author Andras Csizmadia
 *  @version 1.0
 */

//----------------------------------
//  Imports
//----------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "arc4.h"
#include "aes256.h"
#include "rsa.h"
#include "sha.h"
#include "sha256.h"
#include "clientlib.h"

//----------------------------------
//  Constants
//----------------------------------

/**
 * @private
 */
//const char *PAYLOAD = "key12345";
#define PAYLOAD "key12345";

//----------------------------------
//  API
//----------------------------------

/**
 * @see clientlib.h 
 */
void getPayload(char** out, int* outsize){
    char* payload = PAYLOAD;
    *out = payload;
    *outsize = strlen(payload);
}

/**
 * @see clientlib.h
 */
void arc4(uint8_t* buffer, int bufferSize, uint8_t* keyData, int keySize){
    rc4_key key;  
    // init rc4
    arc4_init(keyData, keySize, &key);
    // process bytes
    int i;    
    for (i = 0; i < bufferSize; i++){
        arc4_crypt(buffer, 1, &key);
        buffer++;
    }
}

/**
 * @see clientlib.h
 */
void aes256_encrypt(uint8_t* buffer, uint8_t* keyData)
{
    aes256_context ctx; 
    aes256_init(&ctx, keyData);
    aes256_encrypt_ecb(&ctx, buffer);
    aes256_done(&ctx);
}

/**
 * @see clientlib.h
 */
void aes256_decrypt(uint8_t* buffer, uint8_t* keyData)
{
    aes256_context ctx; 
    aes256_init(&ctx, keyData);
    aes256_decrypt_ecb(&ctx, buffer);
    aes256_done(&ctx);
}

/**
 * @see clientlib.h
 */
void sha1(uint8_t* buffer, int bufferSize, uint8_t* digest) 
{
    SHA_hash(buffer, bufferSize, digest);
}

/**
 * @see clientlib.h
 */
void sha256(uint8_t* buffer, int bufferSize, uint8_t* digest)
{
    SHA256_hash(buffer, bufferSize, digest);
}

/**
 * @see clientlib.h
 */
int rsa(RSAPublicKey *key, uint8_t* signature, int len, uint8_t* hash, int hash_len)
{
    return RSA_verify(key, signature, len, hash, hash_len);
}
