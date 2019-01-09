#!/usr/bin/env python

# Format: TRANSFER AMOUNT $1000000 REASON Salary Jan. 2016 DEST #78384 END

from Crypto.Cipher import AES
import base64
import sys


if __name__ == '__main__':
	l = "wUHhFdm5le/fLoF/G4U0u6FGSNVtkxFA3ZIEwYombzhGF2eYUCOutHTg0h16BtYlBd5FO/XlJkQ058Ev+8hTIA=="
	l = base64.b64decode(l)
	l2 = "TRANSFER AMOUNT $1000000 REASON Salary Jan. 2016 DEST #78384 END"

	l3 = "TRANSFER AMOUNT $1000000 REASON Salary Jan. 2016 DEST #31337 END"

	#i need to modify the 4th block 
	#i don't care about the 3rd

	cipher = list(l)
	dec1 = list(l)
	original = list(l2)
	modified = list(l3)
	for x in xrange(0,15):
		dec1[16*3+x] = chr(ord(cipher[16*2+x]) ^ ord(original[16*3+x]))
		cipher[16*2+x] = chr(ord(dec1[16*3+x]) ^ ord(modified[16*3+x]))
	l = ''.join(cipher)
	l = base64.b64encode(l)
	print l


