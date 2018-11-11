import sys
import struct
import socket



def h2bin(x):
    return x.replace(' ', '').replace('\n', '').decode('hex')

#found on the internet 
hello = h2bin('''
16 03 02 00  dc 01 00 00 d8 03 02 53
43 5b 90 9d 9b 72 0b bc  0c bc 2b 92 a8 48 97 cf
bd 39 04 cc 16 0a 85 03  90 9f 77 04 33 d4 de 00
00 66 c0 14 c0 0a c0 22  c0 21 00 39 00 38 00 88
00 87 c0 0f c0 05 00 35  00 84 c0 12 c0 08 c0 1c
c0 1b 00 16 00 13 c0 0d  c0 03 00 0a c0 13 c0 09
c0 1f c0 1e 00 33 00 32  00 9a 00 99 00 45 00 44
c0 0e c0 04 00 2f 00 96  00 41 c0 11 c0 07 c0 0c
c0 02 00 05 00 04 00 15  00 12 00 09 00 14 00 11
00 08 00 06 00 03 00 ff  01 00 00 49 00 0b 00 04
03 00 01 02 00 0a 00 34  00 32 00 0e 00 0d 00 19
00 0b 00 0c 00 18 00 09  00 0a 00 16 00 17 00 08
00 06 00 07 00 14 00 15  00 04 00 05 00 12 00 13
00 01 00 02 00 03 00 0f  00 10 00 11 00 23 00 00
00 0f 00 01 01                                  
''') 
hb = h2bin(''' 
18 03 02 00 03
01 40 00
''')

#called hexdump even tho i ignored the hex
def hexdump(s):
    for b in xrange(0, len(s), 16):
        lin = [c for c in s[b : b + 16]]
        pdat = ''.join((c if 32 <= ord(c) <= 126 else '.' )for c in lin)
        sys.stdout.write(pdat)
    print

def recvall(sock, count):
    buf = b''
    while count:
        newbuf = sock.recv(count)
        if not newbuf: 
            return None
        buf += newbuf
        count -= len(newbuf)
    return buf


def hit_hb(sock):
    sock.send(hb)
    while True:
        hdr = sock.recv(5)
        tipo,versao,tam = struct.unpack('>BHH', hdr)
        if hdr is None:
            print 'ERROR'
            return False

        if tipo is None:
            print 'ERROR'
            return False

        pay = recvall(sock, tam)
        if pay is None:
            print 'ERROR'
            return False

        if tipo == 24:
            hexdump(pay)
            return True

        if tipo == 21:
            hexdump(pay)
            print 'Server returned error'
            return False

def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    HOST = sys.argv[1]
    PORT = 443
    sock.connect_ex((HOST, PORT))
    #client sends hello
    sock.send (hello)
    #wating for server hello
    while 1:
        #get 5 bytes of the request
        hdr = sock.recv(5)
        #unpack it to make easier 
        tipo,versao,tam = struct.unpack('>BHH', hdr)
        #python don't have a recvall 
        pay = recvall(sock,tam)
        #look for hello done message
        if tipo == 22 and ord(pay[0]) == 0x0E:
            break
    sock.send(hb)
    hit_hb(sock)


if __name__ == '__main__':
    main()