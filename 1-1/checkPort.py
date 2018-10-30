#!/usr/bin/env python
import socket
import subprocess
import sys, time
import string

HOST = '10.0.23.15'

#ports = [22,210,777,1408,2100,2121,2589,3890,4739,5533,6371,6966,8223,8486,9813,10388,10423,11901,12080,12346,13967,14673,15047,15302,16663,17773,18254,18769,18824,18948,20545,20863,21000,21241,22012,22461,23255,23439,23955,24542,24584,25797,26378,27890,28072,28975,29058,31331,31711,33210,33922,36424,36798,37707,38090,38591,38603,39207,40074,40110,40126,40305,40642,40671,41347,42037,42715,44113,46382,47963,48870,48915,49241,50187,50318,50356,50525,50775,50844,51250,51359,52028,52347,52381,52867,53559,53968,53999,55159,56617,56662,56900,57311,58689,59480,60284,60346,60835,61210,61299,61556,64065,64220,64442,64947]
ports = [210, 2100, 2121, 21000]

def testSignature(output):
    file = open("ftpSignatures.txt", "r") 
    signatures = file.read() 
    index = signatures.index(output)
    while (signatures[index]!='$'):
        index = index + 1
    if(signatures.find("Pro", index, index+10) != -1):
        file.close()
        return 0

    if(signatures.find("Pure", index, index+10) != -1):
        file.close()
        return 1

    if(signatures.find("Vs", index, index+10) != -1):
        file.close()
        return 2

    if(signatures.find("Py", index, index+10) != -1):
        file.close()
        return 3
    file.close()
    return 4


try:
    for port in ports:
        #range(1,65535):
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        result = sock.connect_ex((HOST, port))
        sock.settimeout(5)
        #find if port is open
        if result == 0:
            #DEBUG

            try:
                #send http request
                #sock.send('GET / HTTP/1.0\r\n\r\n')

                #[0] - proftpd, [1] - pureftpd, [2] - vsftpd, [3] - pyftpd, [4] - unknown
                #count how many times the answer to a command is the same as in the answers that are already known
                ftpServer = [0,0,0,0,0]
                #get welcome banner
                sock.recv(1000)
                #send not recognized request                
                sock.send(b'WHOAREYOU \n\n')
                #wait a while or it wont send everything
                time.sleep(0.1)
                requestOutput = (sock.recv(10000))
                ftpServer[(testSignature(requestOutput))]+=1

                #send help request
                sock.send(b'HELP \n\n')
                time.sleep(0.1)
                requestOutput = (sock.recv(10000))
                ftpServer[(testSignature(requestOutput))]+=1


                #try to quit
                sock.send(b'QUIT \n\n')
                time.sleep(0.1)
                requestOutput = (sock.recv(10000))
                ftpServer[(testSignature(requestOutput))]+=1

                #finds out which probable server is it
                server = ftpServer.index(max(ftpServer))
                if (server == 0):
                    print ("Port %d Server: ProFTPD" % port)
                elif (server == 1):
                    print ("Port %d Server: Pure-FTPd" % port)
                elif (server == 2):
                    print ("Port %d Server: vsftpd" % port)
                elif (server == 3):
                    print ("Port %d Server: pyftpd" % port)
                else:
                    print ("I dont recognize Port %d Server" % port)

            except:
                print("Error")

        sock.close()
except socket.error:
    print "Couldn't connect to server"
    sys.exit()
