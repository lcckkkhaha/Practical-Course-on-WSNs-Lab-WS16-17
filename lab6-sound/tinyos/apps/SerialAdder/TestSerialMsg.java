/**
 * This class is automatically generated by mig. DO NOT EDIT THIS FILE.
 * This class implements a Java interface to the 'TestSerialMsg'
 * message type.
 */

public class TestSerialMsg extends net.tinyos.message.Message {

    /** The default size of this message type in bytes. */
    public static final int DEFAULT_MESSAGE_SIZE = 6;

    /** The Active Message type associated with this message. */
    public static final int AM_TYPE = 137;

    /** Create a new TestSerialMsg of size 6. */
    public TestSerialMsg() {
        super(DEFAULT_MESSAGE_SIZE);
        amTypeSet(AM_TYPE);
    }

    /** Create a new TestSerialMsg of the given data_length. */
    public TestSerialMsg(int data_length) {
        super(data_length);
        amTypeSet(AM_TYPE);
    }

    /**
     * Create a new TestSerialMsg with the given data_length
     * and base offset.
     */
    public TestSerialMsg(int data_length, int base_offset) {
        super(data_length, base_offset);
        amTypeSet(AM_TYPE);
    }

    /**
     * Create a new TestSerialMsg using the given byte array
     * as backing store.
     */
    public TestSerialMsg(byte[] data) {
        super(data);
        amTypeSet(AM_TYPE);
    }

    /**
     * Create a new TestSerialMsg using the given byte array
     * as backing store, with the given base offset.
     */
    public TestSerialMsg(byte[] data, int base_offset) {
        super(data, base_offset);
        amTypeSet(AM_TYPE);
    }

    /**
     * Create a new TestSerialMsg using the given byte array
     * as backing store, with the given base offset and data length.
     */
    public TestSerialMsg(byte[] data, int base_offset, int data_length) {
        super(data, base_offset, data_length);
        amTypeSet(AM_TYPE);
    }

    /**
     * Create a new TestSerialMsg embedded in the given message
     * at the given base offset.
     */
    public TestSerialMsg(net.tinyos.message.Message msg, int base_offset) {
        super(msg, base_offset, DEFAULT_MESSAGE_SIZE);
        amTypeSet(AM_TYPE);
    }

    /**
     * Create a new TestSerialMsg embedded in the given message
     * at the given base offset and length.
     */
    public TestSerialMsg(net.tinyos.message.Message msg, int base_offset, int data_length) {
        super(msg, base_offset, data_length);
        amTypeSet(AM_TYPE);
    }

    /**
    /* Return a String representation of this message. Includes the
     * message type name and the non-indexed field values.
     */
    public String toString() {
      String s = "Message <TestSerialMsg> \n";
      try {
        s += "  [first=0x"+Long.toHexString(get_first())+"]\n";
      } catch (ArrayIndexOutOfBoundsException aioobe) { /* Skip field */ }
      try {
        s += "  [second=0x"+Long.toHexString(get_second())+"]\n";
      } catch (ArrayIndexOutOfBoundsException aioobe) { /* Skip field */ }
      try {
        s += "  [result=0x"+Long.toHexString(get_result())+"]\n";
      } catch (ArrayIndexOutOfBoundsException aioobe) { /* Skip field */ }
      return s;
    }

    // Message-type-specific access methods appear below.

    /////////////////////////////////////////////////////////
    // Accessor methods for field: first
    //   Field type: int, unsigned
    //   Offset (bits): 0
    //   Size (bits): 16
    /////////////////////////////////////////////////////////

    /**
     * Return whether the field 'first' is signed (false).
     */
    public static boolean isSigned_first() {
        return false;
    }

    /**
     * Return whether the field 'first' is an array (false).
     */
    public static boolean isArray_first() {
        return false;
    }

    /**
     * Return the offset (in bytes) of the field 'first'
     */
    public static int offset_first() {
        return (0 / 8);
    }

    /**
     * Return the offset (in bits) of the field 'first'
     */
    public static int offsetBits_first() {
        return 0;
    }

    /**
     * Return the value (as a int) of the field 'first'
     */
    public int get_first() {
        return (int)getUIntBEElement(offsetBits_first(), 16);
    }

    /**
     * Set the value of the field 'first'
     */
    public void set_first(int value) {
        setUIntBEElement(offsetBits_first(), 16, value);
    }

    /**
     * Return the size, in bytes, of the field 'first'
     */
    public static int size_first() {
        return (16 / 8);
    }

    /**
     * Return the size, in bits, of the field 'first'
     */
    public static int sizeBits_first() {
        return 16;
    }

    /////////////////////////////////////////////////////////
    // Accessor methods for field: second
    //   Field type: int, unsigned
    //   Offset (bits): 16
    //   Size (bits): 16
    /////////////////////////////////////////////////////////

    /**
     * Return whether the field 'second' is signed (false).
     */
    public static boolean isSigned_second() {
        return false;
    }

    /**
     * Return whether the field 'second' is an array (false).
     */
    public static boolean isArray_second() {
        return false;
    }

    /**
     * Return the offset (in bytes) of the field 'second'
     */
    public static int offset_second() {
        return (16 / 8);
    }

    /**
     * Return the offset (in bits) of the field 'second'
     */
    public static int offsetBits_second() {
        return 16;
    }

    /**
     * Return the value (as a int) of the field 'second'
     */
    public int get_second() {
        return (int)getUIntBEElement(offsetBits_second(), 16);
    }

    /**
     * Set the value of the field 'second'
     */
    public void set_second(int value) {
        setUIntBEElement(offsetBits_second(), 16, value);
    }

    /**
     * Return the size, in bytes, of the field 'second'
     */
    public static int size_second() {
        return (16 / 8);
    }

    /**
     * Return the size, in bits, of the field 'second'
     */
    public static int sizeBits_second() {
        return 16;
    }

    /////////////////////////////////////////////////////////
    // Accessor methods for field: result
    //   Field type: int, unsigned
    //   Offset (bits): 32
    //   Size (bits): 16
    /////////////////////////////////////////////////////////

    /**
     * Return whether the field 'result' is signed (false).
     */
    public static boolean isSigned_result() {
        return false;
    }

    /**
     * Return whether the field 'result' is an array (false).
     */
    public static boolean isArray_result() {
        return false;
    }

    /**
     * Return the offset (in bytes) of the field 'result'
     */
    public static int offset_result() {
        return (32 / 8);
    }

    /**
     * Return the offset (in bits) of the field 'result'
     */
    public static int offsetBits_result() {
        return 32;
    }

    /**
     * Return the value (as a int) of the field 'result'
     */
    public int get_result() {
        return (int)getUIntBEElement(offsetBits_result(), 16);
    }

    /**
     * Set the value of the field 'result'
     */
    public void set_result(int value) {
        setUIntBEElement(offsetBits_result(), 16, value);
    }

    /**
     * Return the size, in bytes, of the field 'result'
     */
    public static int size_result() {
        return (16 / 8);
    }

    /**
     * Return the size, in bits, of the field 'result'
     */
    public static int sizeBits_result() {
        return 16;
    }

}
