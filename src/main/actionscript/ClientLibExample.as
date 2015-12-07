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
package {
import app.ClientLib.CModule;
import app.ClientLib.vfs.ISpecialFile;

import flash.display.Sprite;
import flash.display.StageScaleMode;
import flash.events.Event;
import flash.text.TextField;
import flash.utils.ByteArray;

/**
 * ClientLib Example
 */
[SWF(width="1024", height="768", frameRate="60", backgroundColor="#FFFFFF")]
public class ClientLibExample extends Sprite implements ISpecialFile {
    /**
     * @private
     */
    private var output:TextField;

    //----------------------------------
    //  Constructor
    //----------------------------------

    /**
     * Constructor
     */
    public function ClientLibExample() {
        CModule.rootSprite = this;
        CModule.throwWhenOutOfMemory = true;
        CModule.vfs.console = this;
        addEventListener(Event.ADDED_TO_STAGE, onAdded);
    }

    /**
     * @private
     */
    private function onAdded(event:Event):void {
        removeEventListener(Event.ADDED_TO_STAGE, onAdded);

        // setup the output text area
        output = new TextField();
        output.multiline = true;
        output.width = stage.stageWidth;
        output.height = stage.stageHeight;
        addChild(output);

        stage.frameRate = 60;
        stage.scaleMode = StageScaleMode.NO_SCALE;

        CModule.startAsync(this);

        printLine("CModule.canUseWorkers: " + CModule.canUseWorkers);
        printLine("CModule.throwWhenOutOfMemory: " + CModule.throwWhenOutOfMemory);

        addEventListener(Event.ENTER_FRAME, enterFrame);

        // const test
        printLine("Const: " + ClientLib.VERSION);

        testProcessBytes();
    }
        
    /**
     * @private
     */
    private function testProcessBytes():void {
        printLine("# testProcessBytes");
        var n:uint = 10;
        var dataBytes:ByteArray = new ByteArray();
        dataBytes.endian = "littleEndian";
        for (var i:int = 0; i < n; i++) {
            dataBytes.writeByte(i);
            printLine("Byte before " + i + ": " + dataBytes[i]);
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
            printLine("Byte after " + j + ": " + dataBytes[j]);
        }

        // free memory
        CModule.free(dataBytesPtr);
        CModule.free(keyBytesPtr);
    }
     
    /**
     * @private
     */
    private function dumpBA(input:ByteArray):void {
        input.position = 0;
        trace(input.readUTF());
        input.position = 0;
    }

    /**
     * @private
     */
    private function printLine(string:String):void {
        output.appendText(string + "\n");
        trace(string);
    }

    /**
     * The enterFrame callback will be run once every frame. UI thunk requests should be handled
     * here by calling CModule.serviceUIRequests() (see CModule ASdocs for more information on the UI thunking functionality).
     */
    private function enterFrame(e:Event):void {
        CModule.serviceUIRequests();
    }

    // ISpecialFile API implementation

    /**
     * The callback to call when FlasCC code calls the posix exit() function. Leave null to exit silently.
     * @private
     */
    public var exitHook:Function;

    /**
     * The PlayerKernel implementation will use this function to handle
     * C process exit requests
     */
    public function exit(code:int):Boolean {
        // default to unhandled
        return exitHook ? exitHook(code) : false;
    }

    /**
     * The PlayerKernel implementation will use this function to handle
     * C IO write requests to the file "/dev/tty" (e.g. output from
     * printf will pass through this function). See the ISpecialFile
     * documentation for more information about the arguments and return value.
     */
    public function write(fd:int, bufPtr:int, nbyte:int, errnoPtr:int):int {
        var str:String = CModule.readString(bufPtr, nbyte)
        printLine(str)
        return nbyte
    }

    /**
     * The PlayerKernel implementation will use this function to handle
     * C IO read requests to the file "/dev/tty" (e.g. reads from stdin
     * will expect this function to provide the data). See the ISpecialFile
     * documentation for more information about the arguments and return value.
     */
    public function read(fd:int, bufPtr:int, nbyte:int, errnoPtr:int):int {
        return 0
    }

    /**
     * The PlayerKernel implementation will use this function to handle
     * C fcntl requests to the file "/dev/tty"
     * See the ISpecialFile documentation for more information about the
     * arguments and return value.
     */
    public function fcntl(fd:int, com:int, data:int, errnoPtr:int):int {
        return 0
    }

    /**
     * The PlayerKernel implementation will use this function to handle
     * C ioctl requests to the file "/dev/tty"
     * See the ISpecialFile documentation for more information about the
     * arguments and return value.
     */
    public function ioctl(fd:int, com:int, data:int, errnoPtr:int):int {
        return 0
    }

}
}
