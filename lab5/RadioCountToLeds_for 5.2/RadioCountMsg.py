#
# This class is automatically generated by mig. DO NOT EDIT THIS FILE.
# This class implements a Python interface to the 'RadioCountMsg'
# message type.
#

import tinyos.message.Message

# The default size of this message type in bytes.
DEFAULT_MESSAGE_SIZE = 4

# The Active Message type associated with this message.
AM_TYPE = 6

class RadioCountMsg(tinyos.message.Message.Message):
    # Create a new RadioCountMsg of size 4.
    def __init__(self, data="", addr=None, gid=None, base_offset=0, data_length=4):
        tinyos.message.Message.Message.__init__(self, data, addr, gid, base_offset, data_length)
        self.amTypeSet(AM_TYPE)
    
    # Get AM_TYPE
    def get_amType(cls):
        return AM_TYPE
    
    get_amType = classmethod(get_amType)
    
    #
    # Return a String representation of this message. Includes the
    # message type name and the non-indexed field values.
    #
    def __str__(self):
        s = "Message <RadioCountMsg> \n"
        try:
            s += "  [counter=0x%x]\n" % (self.get_counter())
        except:
            pass
        try:
            s += "  [mydata=0x%x]\n" % (self.get_mydata())
        except:
            pass
        try:
            s += "  [length=0x%x]\n" % (self.get_length())
        except:
            pass
        return s

    # Message-type-specific access methods appear below.

    #
    # Accessor methods for field: counter
    #   Field type: int, unsigned
    #   Offset (bits): 0
    #   Size (bits): 16
    #

    #
    # Return whether the field 'counter' is signed (False).
    #
    def isSigned_counter(self):
        return False
    
    #
    # Return whether the field 'counter' is an array (False).
    #
    def isArray_counter(self):
        return False
    
    #
    # Return the offset (in bytes) of the field 'counter'
    #
    def offset_counter(self):
        return (0 / 8)
    
    #
    # Return the offset (in bits) of the field 'counter'
    #
    def offsetBits_counter(self):
        return 0
    
    #
    # Return the value (as a int) of the field 'counter'
    #
    def get_counter(self):
        return self.getUIntElement(self.offsetBits_counter(), 16, 1)
    
    #
    # Set the value of the field 'counter'
    #
    def set_counter(self, value):
        self.setUIntElement(self.offsetBits_counter(), 16, value, 1)
    
    #
    # Return the size, in bytes, of the field 'counter'
    #
    def size_counter(self):
        return (16 / 8)
    
    #
    # Return the size, in bits, of the field 'counter'
    #
    def sizeBits_counter(self):
        return 16
    
    #
    # Accessor methods for field: mydata
    #   Field type: short, unsigned
    #   Offset (bits): 16
    #   Size (bits): 8
    #

    #
    # Return whether the field 'mydata' is signed (False).
    #
    def isSigned_mydata(self):
        return False
    
    #
    # Return whether the field 'mydata' is an array (False).
    #
    def isArray_mydata(self):
        return False
    
    #
    # Return the offset (in bytes) of the field 'mydata'
    #
    def offset_mydata(self):
        return (16 / 8)
    
    #
    # Return the offset (in bits) of the field 'mydata'
    #
    def offsetBits_mydata(self):
        return 16
    
    #
    # Return the value (as a short) of the field 'mydata'
    #
    def get_mydata(self):
        return self.getUIntElement(self.offsetBits_mydata(), 8, 0)
    
    #
    # Set the value of the field 'mydata'
    #
    def set_mydata(self, value):
        self.setUIntElement(self.offsetBits_mydata(), 8, value, 0)
    
    #
    # Return the size, in bytes, of the field 'mydata'
    #
    def size_mydata(self):
        return (8 / 8)
    
    #
    # Return the size, in bits, of the field 'mydata'
    #
    def sizeBits_mydata(self):
        return 8
    
    #
    # Accessor methods for field: length
    #   Field type: short, unsigned
    #   Offset (bits): 24
    #   Size (bits): 8
    #

    #
    # Return whether the field 'length' is signed (False).
    #
    def isSigned_length(self):
        return False
    
    #
    # Return whether the field 'length' is an array (False).
    #
    def isArray_length(self):
        return False
    
    #
    # Return the offset (in bytes) of the field 'length'
    #
    def offset_length(self):
        return (24 / 8)
    
    #
    # Return the offset (in bits) of the field 'length'
    #
    def offsetBits_length(self):
        return 24
    
    #
    # Return the value (as a short) of the field 'length'
    #
    def get_length(self):
        return self.getUIntElement(self.offsetBits_length(), 8, 0)
    
    #
    # Set the value of the field 'length'
    #
    def set_length(self, value):
        self.setUIntElement(self.offsetBits_length(), 8, value, 0)
    
    #
    # Return the size, in bytes, of the field 'length'
    #
    def size_length(self):
        return (8 / 8)
    
    #
    # Return the size, in bits, of the field 'length'
    #
    def sizeBits_length(self):
        return 8
    
