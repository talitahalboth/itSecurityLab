import socket
import ssl

# SET VARIABLES
packet, reply = "hello world", ""
HOST, PORT = '10.0.23.14', 443

# CREATE SOCKET
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.settimeout(10)

# WRAP SOCKET
wrappedSocket = ssl.wrap_socket(sock, 
        ssl_version=ssl.PROTOCOL_TLSv1)



# CONNECT AND PRINT REPLY
wrappedSocket.connect((HOST, PORT))

wrappedSocket.do_handshake()
#wrappedSocket.send(packet)
#print (wrappedSocket.recv(1280))

# CLOSE SOCKET CONNECTION
wrappedSocket.close()