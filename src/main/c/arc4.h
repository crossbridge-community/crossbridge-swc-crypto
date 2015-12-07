/*
 * =BEGIN CLOSED LICENSE
 *
 *  Copyright (c) 2013 Andras Csizmadia
 *  http://www.vpmedia.eu
 *
 *  For information about the licensing and copyright please
 *  contact us at info@vpmedia.eu
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
 *  ARC4
 *  arc4.h
 *  Purpose: ARC4 Encryption header
 *
 *  @author Andras Csizmadia
 *  @version 1.0
 */
 
//----------------------------------
//  Include Once Start
//----------------------------------

#ifndef __ARC4_H
#define __ARC4_H
 
//----------------------------------
//  Includes
//----------------------------------

#include <stdint.h>

//----------------------------------
//  CPP Start
//----------------------------------

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------
//  Type Definitions
//----------------------------------

/**
 * Define type definition structure
 */
typedef struct rc4_key {
    uint8_t state[256];
    uint8_t x;
    uint8_t y;
} rc4_key;

//----------------------------------
//  API
//----------------------------------

/**
 * Initialize keyring
 *
 * @param key_data_ptr The secret byte array pointer
 * @param key_data_len The secret byte array length
 * @param rc4_key The pointer to the rc4_key structure
 */
void arc4_init(uint8_t *key_data_ptr, int key_data_len, rc4_key *key);

/**
 * Crypt bytes
 *
 * @param buffer_ptr The byte array pointer
 * @param buffer_len The byte array length
 * @param rc4_key The pointer to the rc4_key structure
 */
void arc4_crypt(uint8_t *buffer_ptr, int buffer_len, rc4_key *key);

//----------------------------------
//  Helpers
//----------------------------------

/**
 * Swap byte pointers
 *
 * @param a The first bytes pointer to swap
 * @param b The second bytes pointer to swap
 */
/*static*/ void swap_byte(uint8_t *a, uint8_t *b);

//----------------------------------
//  CPP End
//----------------------------------

#ifdef __cplusplus
}
#endif

//----------------------------------
//  Include Once End
//----------------------------------

#endif/*__ARC4_H*/