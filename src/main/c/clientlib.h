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
 *  clientlib.h
 *  Purpose: Client library header
 *
 *  @author Andras Csizmadia
 *  @version 1.0
 */
 
//----------------------------------
//  Include Once Start
//----------------------------------

#ifndef __CLIENTLIB_H
#define __CLIENTLIB_H

//----------------------------------
//  Includes
//----------------------------------

#include <stdint.h>
#include "rsa.h"

//----------------------------------
//  CPP Start
//----------------------------------

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------
//  Constants
//----------------------------------

#define VERSION "1.0.0"  

//----------------------------------
//  API
//----------------------------------

/**
 * Returns the payload to the flash client.
 *
 * @param out Pointer to a Pointer of a Flash String
 * @param outsize Pointer to Flash Integer (String Length)
 *
 * @return void
 */
void getPayload(char** out, int* outsize);

/**
 * ARC4 Symmetric Encryption
 *
 * @param buffer
 * @param bufferSize
 * @param keyData
 * @param keySize
 *
 * @return void
 */
void arc4(uint8_t* buffer, int bufferSize, uint8_t* keyData, int keySize);

/**
 * AES-256 Encryption
 *
 * @param buffer
 * @param keyData
 *
 * @return void
 */
void aes256_encrypt(uint8_t* buffer, uint8_t* keyData);

/**
 * AES-256 Decryption
 *
 * @param buffer
 * @param keyData
 *
 * @return void
 */
void aes256_decrypt(uint8_t* buffer, uint8_t* keyData);

/**
 * SHA1 Hash
 *
 * @param buffer
 * @param bufferSize
 * @param digest
 *
 * @return void
 */
void sha1(uint8_t* buffer, int bufferSize, uint8_t* digest);

/**
 * SHA256 Hash
 *
 * @param buffer
 * @param bufferSize
 * @param digest
 *
 * @return void
 */
void sha256(uint8_t* buffer, int bufferSize, uint8_t* digest);

/**
 * RSA Verify
 *
 * @return int
 */
int rsa(RSAPublicKey *key, uint8_t* signature, int len, uint8_t* hash, int hash_len);

//----------------------------------
//  CPP End
//----------------------------------

#ifdef __cplusplus
}
#endif

//----------------------------------
//  Include Once End
//----------------------------------

#endif/*__CLIENTLIB_H*/