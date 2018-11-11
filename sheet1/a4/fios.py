import socket
import ssl
from threading import Thread
from threading import Lock
import time, sys




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
    def decrement(self):
        self.lock.acquire()
        try:
            self.value = self.value - 1
        finally:
            self.lock.release()


class Error(object):
    def __init__(self, start = 0):
        self.lock = Lock()
        self.value = start
    #it's called "set" but it actually increments.
    def set(self):
        self.lock.acquire()
        try:
            self.value = self.value + 1
        finally:
            self.lock.release()

def openSocketSSL(i,c, e, HOST):
    connected = 0
    # SET VARIABLES
    #HOST, PORT = '10.0.23.14', 443
    PORT = 443

    # CREATE SOCKET
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.settimeout(10)
    # WRAP SOCKET
    wrappedSocket = ssl.wrap_socket(sock, 
            ssl_version=ssl.PROTOCOL_TLSv1)

    #try to connect
    try:
        wrappedSocket.connect((HOST, PORT))

        
        try:
            #try to do handshake
            wrappedSocket.do_handshake()

            #if could do a handshake, increment counter
            c.increment()
            connected = 1

            count = 0;
            data = "this is actually garbage".encode()
            #tries keeps the conection open by sending data 
            #if the max handshakes is reached ('e' variable) waits a while and then also drops the connection
            while count < 2:
                if e.value >=15: 
                    count=count+1
                try:
                    wrappedSocket.send(data)
                    time.sleep(1)
                except:
                    print ("conexao morreu..?")
            

            # CLOSE SOCKET CONNECTION
            wrappedSocket.close()

        #if could not do a handshake:
        except:
            handshakeError = 1

        

    #if could not connect:
    except:
        e.set()

    #if it was connected and it dropped the connection by itself, decrement the counter
    if (connected and (not e.value)):
        c.decrement()
    
def main():
    #this is the connections counter. Keeps track of how many connections were successful
    counter = Counter()
    #this variable is set to 1 if we reach the max. number of handshakes
    err = Error()
    HOST = sys.argv[1]
    for i in range (200):
        t = Thread(target=openSocketSSL, args=(i,counter, err, HOST))
        t.start()
    a=0
    #keeps waiting until the max value is found
    while (err.value < 15):
        pass
    #print the content of the counter
    print("Handshakes perfoermed before server started rejecting new connections: %d" %counter.value)

if __name__ == '__main__':
    main()