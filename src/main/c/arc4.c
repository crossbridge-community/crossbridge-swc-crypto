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
 *  ARC4
 *  arc4.h
 *  Purpose: ARC4 Encryption Implementation
 *
 *  @author Andras Csizmadia
 *  @version 1.0
 */
 
//----------------------------------
//  Imports
//----------------------------------

#include "arc4.h"

//----------------------------------
//  Constants
//----------------------------------

#define BLOCK_SIZE 256

//----------------------------------
//  API
//----------------------------------

/**
 * @see arc4.h
 */
void arc4_init(uint8_t *key_data_ptr, int key_data_len, rc4_key *key)
{
    uint8_t index1;
    uint8_t index2;
    uint8_t *state;
    short counter;
    
    state = &key->state[0];
    
    for (counter = 0; counter < 256; counter++)
        state[counter] = counter;
    
    key->x = 0;     
    key->y = 0;     
    index1 = 0;     
    index2 = 0;             
    
    for (counter = 0; counter < 256; counter++) {               
        index2 = (key_data_ptr[index1] + state[counter] + index2) % 256;
        swap_byte(&state[counter], &state[index2]);
        index1 = (index1 + 1) % key_data_len;
    }
}

/**
 * @see arc4.h
 */
void arc4_crypt(uint8_t *buffer_ptr, int buffer_len, rc4_key *key)
{ 
    uint8_t x;
    uint8_t y;
    uint8_t *state;
    uint8_t xorIndex;
    short counter;
    
    x = key->x;
    y = key->y;
    state = &key->state[0];
    
    for (counter = 0; counter < buffer_len; counter++) {
        x = (x + 1) % 256;
        y = (state[x] + y) % 256;
        swap_byte(&state[x], &state[y]);
        xorIndex = state[x] + (state[y]) % 256;
        buffer_ptr[counter] ^= state[xorIndex];
    }
    
    key->x = x;
    key->y = y;
}

//----------------------------------
//  Helpers
//----------------------------------

/**
 * @see arc4.h
 */
/*static*/ void swap_byte(uint8_t *a, uint8_t *b)
{
    uint8_t swapByte;
    
    swapByte = *a;
    *a = *b;
    *b = swapByte;
}
