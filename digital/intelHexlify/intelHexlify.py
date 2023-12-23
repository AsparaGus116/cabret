import sys
import os

specifiedOutfile = False

def getFilename(str):
	filename = ""
	for char in str:
		if char != ".":
			filename += char
		else:
			break
	return filename
	
	
def computeChecksum(bytecount, address, data):
	checksum = (int(data, 16) + address + bytecount)
	checksum ^= 0xff
	checksum += 1
	checksum %= 256
	return checksum

def getHexData(file):
	data = ""
	temp = file.read(1)
	while(temp != " " and temp != ""):
		data += temp
		temp = file.read(1)
	return data

if len(sys.argv) < 2:
	print("SYNTAX: python intelHexlify.py <filename> [-o <output filename>]")
	exit()

for i in range(len(sys.argv)):
	if(sys.argv[i] == "-o"):
		try:
			outFile = open(sys.argv[i + 1], 'w')
			specifiedOutfile = True
		except:
			print("ERR: Invalid output file or invalid permissions")
			exit()
	if(sys.argv[i] == "-h" or sys.argv[i] == "--help"):
		print("Converts txt file with hex digits into Intel .hex format. Separate hex digits with a space.")
		print("SYNTAX: python intelHexlify.py <filename> [-o <output filename>]")
		exit()

try:	
	file = open(sys.argv[1], 'r')
except:
	print("ERR: Invalid file or invalid permissions")
	exit()
	
if(specifiedOutfile == False):
	outFile = open(getFilename(sys.argv[1]) + ".hex", 'w')	



address = 0

data = getHexData(file)

bytecount = len(data) // 2

checksum = computeChecksum(bytecount, address, data)

while data:
	#print(data)

	outFile.write(":" + hex(bytecount)[2:].zfill(2) + hex(address)[2:].zfill(4) + "00" + data + hex(checksum)[2:].zfill(bytecount * 2) + '\n')
	
	address += 1
	data = getHexData(file)
	
	if data == '':
		break
	
	bytecount = len(data) // 2
	
	print("BYTECOUNT: " + str(bytecount))
	
	checksum = computeChecksum(bytecount, address, data)
	