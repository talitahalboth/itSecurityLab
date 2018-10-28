import socket
import ssl
from threading import Thread
from threading import Lock
import time
import sys
import time




#counter (needs to have a lock or it'll count wrong)
class Counter(object):
    def __init__(self, start = 0):
        self.lock = Lock()
        self.value = start
    def increment(self):
        self.lock.acquire()
        try:
            self.value = self.value + 1
        finally:
            self.lock.release()


def openSocketSSL(i,c):
    global erro
    # SET VARIABLES
    HOST, PORT = '10.0.23.14', 443

    # CREATE SOCKET
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.settimeout(10)
    # WRAP SOCKET
    wrappedSocket = ssl.wrap_socket(sock, 
            ssl_version=ssl.PROTOCOL_TLSv1)

    # DEBUG
    if (i <10):
        print('0', end='')
    if (i <100):
        print('0', end='')
    print("%d thread connect" % i)
    #try to connect
    try:
        wrappedSocket.connect((HOST, PORT))


        #DEBUG
        if (i <10):
            print('0', end='')
        if (i <100):
            print('0', end='')
        print ("%d conectou" %i)

        if (i <10):
            print('0', end='')
        if (i <100):
            print('0', end='')
        print("%d thread handshake" % i)



        
        try:
            #try to do handshake
            wrappedSocket.do_handshake()


            #DEBUG
            if (i <10):
                print('0', end='')
            if (i <100):
                print('0', end='')
            print("%d Fez o handshake" %i)

            #if could do a handshake, increment counter
            c.increment()

            count = 0;
            #this was supposed to keep sending data to test if the connection is still open
            data = "this is actually garbage".encode()
            while 1:
                if erro: 
                    count=count+1
                try:
                    wrappedSocket.send(data)
                    time.sleep(10)
                except:
                    print ("conexao morreu..?")
            

            # CLOSE SOCKET CONNECTION
            wrappedSocket.close()



        #if could not do a handshake:
        except:
            #DEBUG
            if (i <10):
                print('0', end='')
            if (i <100):
                print('0', end='')
            print("%d Erro no handshake!" %i)


            erro = 1



        

    #if could not connect:
    except:
        #DEBUG
        if (i <10):
            print('0', end='')
        if (i <100):
            print('0', end='')
        print("%d nao conectou!" % i)


        erro = 1
    if (i <10):
        print('0', end='')
    if (i <100):
        print('0', end='')
    print("%d conexao acabou" %i )
    print ('Counter: %d' % c.value)
    

counter = Counter()
erro = 0
for i in range (400):
    t = Thread(target=openSocketSSL, args=(i,counter))
    t.start()
a=0

