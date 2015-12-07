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

package app {
import app.ClientLib.CModule;

import flash.display.Sprite;
import flash.utils.ByteArray;

import flexunit.framework.Assert;

public class ClientLibTest extends Sprite {

    private static const TEST_DATA:Array = [24,202,104,101,75,52,105,67,190,92];
    
    [Before]
    public function setUp():void {
        if(!CModule.rootSprite) {
        CModule.throwWhenOutOfMemory = true;
            CModule.rootSprite = this;
            CModule.startAsync(this);
            CModule.serviceUIRequests();        
        }
        
    }

    [After]
    public function tearDown():void {
    }
    
    [Test]
    public function test_getPayload():void {
        // Program start
        var outputPtr:int = CModule.malloc(4);
        var outputLengthPtr:int = CModule.malloc(4);
        ClientLib.getPayload(outputPtr, outputLengthPtr);
        var outputLength:int = CModule.read32(outputLengthPtr);
        var outputString:String = CModule.readString(CModule.read32(outputPtr), outputLength);
        // printLine("Payload: " + outputString + " (length=" + outputLength + ")");
        CModule.free(outputPtr);
        CModule.free(outputLengthPtr);
        Assert.assertNotNull(outputString);
        Assert.assertEquals(outputString.length, outputLength);
        Assert.assertEquals(outputString, "key12345");
    }
         
    [Test]
    public function test_arc4_fl():void {
         var keyBytes:ByteArray = new ByteArray();
         keyBytes.writeUTF("key12345");
         keyBytes.position = 0;
         var dataBytes:ByteArray = new ByteArray();
         dataBytes.endian = "littleEndian";
         for (var i:int = 0; i < 10; i++) {
            dataBytes.writeByte(i);
         }
         var arc:ARC4 = new ARC4(keyBytes);
         arc.encrypt(dataBytes);
         for (var j:int = 0; j < 10; j++) {
            Assert.assertEquals(TEST_DATA[j], dataBytes[j]);
         }
    }
          
    [Test]
    public function test_arc4():void {
        var n:uint = 10;
        var dataBytes:ByteArray = new ByteArray();
        dataBytes.endian = "littleEndian";
        for (var i:int = 0; i < n; i++) {
            dataBytes.writeByte(i);
        }
        dataBytes.position = 0;
        var dataBytesPtr:int = CModule.malloc(dataBytes.length);
        CModule.writeBytes(dataBytesPtr, dataBytes.length, dataBytes);

        var keyBytes:ByteArray = new ByteArray();
        //keyBytes.endian = "littleEndian";
        keyBytes.writeUTF("key12345");
        keyBytes.position = 0;
        var keyBytesPtr:int = CModule.malloc(keyBytes.length);
        CModule.writeBytes(keyBytesPtr, keyBytes.length, keyBytes);
        ClientLib.arc4(dataBytesPtr, dataBytes.length, keyBytesPtr, keyBytes.length);
        // get the output

        //var newData:ByteArray = new ByteArray();
        dataBytes.position = 0;
        CModule.readBytes(dataBytesPtr, n, dataBytes)
        for (var j:int = 0; j < n; j++) {
            Assert.assertEquals(TEST_DATA[j], dataBytes[j]);
        }

        // free memory
        CModule.free(dataBytesPtr);
        CModule.free(keyBytesPtr);
    }
    
    [Test]
    public function test_aes():void {
        var n:uint = 10;
        var dataBytes:ByteArray = new ByteArray();
        dataBytes.endian = "littleEndian";
        for (var i:int = 0; i < n; i++) {
            dataBytes.writeByte(i);
            Assert.assertEquals(i, dataBytes[i]);
        }
        dataBytes.position = 0;
        var dataBytesPtr:int = CModule.malloc(dataBytes.length);
        CModule.writeBytes(dataBytesPtr, dataBytes.length, dataBytes);

        var keyBytes:ByteArray = new ByteArray();
        //keyBytes.endian = "littleEndian";
        keyBytes.writeUTF("TEST");
        keyBytes.position = 0;
        var keyBytesPtr:int = CModule.malloc(keyBytes.length);
        CModule.writeBytes(keyBytesPtr, keyBytes.length, keyBytes);
        ClientLib.aes256_encrypt(dataBytesPtr, keyBytesPtr);
        // get the output

        //var newData:ByteArray = new ByteArray();
                
        ClientLib.aes256_decrypt(dataBytesPtr, keyBytesPtr);
        
        dataBytes.position = 0;
        CModule.readBytes(dataBytesPtr, n, dataBytes)
        for (var j:int = 0; j < n; j++) {
            Assert.assertEquals(j, dataBytes[j]);
        }
        
        // free memory
        CModule.free(dataBytesPtr);
        CModule.free(keyBytesPtr);
    }   
}
}
