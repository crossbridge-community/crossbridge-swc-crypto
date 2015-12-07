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
 *  AS3API
 *  as3api.h
 *  Purpose: AS3 API Definition for SWIG wrapper generator
 *  Please check Adobe CrossBridge documentation about details.
 *
 *  @author Andras Csizmadia
 *  @version 1.0
 */
 
#ifdef SWIG
    %module ClientLibModule
    %{
        #include "AS3/AS3.h"
        #include "clientlib.h"
        // Define entry point. 
        int main() {
            AS3_GoAsync();
        }
    %}
    %include "clientlib.h"
#else
    #include "clientlib.h"
#endif