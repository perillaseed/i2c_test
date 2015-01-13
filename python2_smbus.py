import smbus
import time

import struct

address = 0x04

if __name__=="__main__":
	bus = smbus.SMBus(1)    # 0 = /dev/i2c-0 (port I2C0), 1 = /dev/i2c-1 (port I2C1)
	
	while True:
		values = [] 
		try:
			value = int(str(input("Enter 0 - 255:")).strip())
		except Exception as e:
			print(e)
			continue
		bus.write_byte(address, value)  #等同于 bus.write_i2c_block_data(address, value, [])
		#bus.write_byte_data(address, value, None) #最后一个必须是整形，不能为空。
		#bus.write_i2c_block_data(address, value, [])
		time.sleep(1)
		#sensors = bus.read_i2c_block_data(address, 1) #不行，错误
		time.sleep(2)
		sensors = bus.read_byte(address)
		#sensors = bus.read_byte_data(address, 1) #不行，错误
		print(sensors)
		
		#Sensors = namedtuple("Sensors", "address A0 A1 A2 A3")
		#s = Sensors._make(struct.unpack("<BHHHH", sensors))
		#print(s)
		#sensors = bus.read_byte(address)
		#sensors2 = bus.read_byte(address)
		#sensors = bus.read_byte(address)
		#sensors2 = bus.read_byte(address)
		#sensors = bus.read_byte_data(address, value)
		#print(sensors1, sensors2)
		
		#datas = [(sensors[i]<<8) + sensors[i+1] for i in range(1,9,2)] #1,3,5,7
		#print(datas)
		
		#val = reverseByteOrder(sensors[1:3])
		#print(val)


	
