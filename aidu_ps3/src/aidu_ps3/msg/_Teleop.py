"""autogenerated by genpy from aidu_ps3/Teleop.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class Teleop(genpy.Message):
  _md5sum = "21df767a8510b60ed3c0a04b4d2be358"
  _type = "aidu_ps3/Teleop"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """#This message contains the input of the ps3 controller
float32 leftx
float32 lefty
float32 rightx
float32 righty
float32 circle

"""
  __slots__ = ['leftx','lefty','rightx','righty','circle']
  _slot_types = ['float32','float32','float32','float32','float32']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       leftx,lefty,rightx,righty,circle

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(Teleop, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.leftx is None:
        self.leftx = 0.
      if self.lefty is None:
        self.lefty = 0.
      if self.rightx is None:
        self.rightx = 0.
      if self.righty is None:
        self.righty = 0.
      if self.circle is None:
        self.circle = 0.
    else:
      self.leftx = 0.
      self.lefty = 0.
      self.rightx = 0.
      self.righty = 0.
      self.circle = 0.

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_struct_5f.pack(_x.leftx, _x.lefty, _x.rightx, _x.righty, _x.circle))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
      _x = self
      start = end
      end += 20
      (_x.leftx, _x.lefty, _x.rightx, _x.righty, _x.circle,) = _struct_5f.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_struct_5f.pack(_x.leftx, _x.lefty, _x.rightx, _x.righty, _x.circle))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      end = 0
      _x = self
      start = end
      end += 20
      (_x.leftx, _x.lefty, _x.rightx, _x.righty, _x.circle,) = _struct_5f.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_5f = struct.Struct("<5f")
