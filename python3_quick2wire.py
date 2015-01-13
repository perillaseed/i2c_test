from quick2wire.i2c import I2CMaster, writing_bytes, reading
import time

import struct
from collections import namedtuple

address = 0x04

if __name__=="__main__":		
	with I2CMaster() as master:
		while True:
			try:
				value = int(str(input("Enter 0 - 255:")).strip())
			except Exception as e:
				print(e)
				continue
			
			master.transaction(writing_bytes(address,value))
			time.sleep(1)
			
			sensors = master.transaction(reading(address, 8))[0]
			print(sensors)
			Sensors = namedtuple("Sensors", "A0 A1 A2 A3")
			s = Sensors._make(struct.unpack("<HHHH", sensors))
			print(s)
			time.sleep(1)