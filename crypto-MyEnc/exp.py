#!/usr/bin/env python
from pwn import *
from Crypto.Util.number import *
import string,hashlib,gmpy2
#context.log_level = "debug"
charset = string.ascii_letters + string.digits
def solve_PoW(suffix, h):
        print("solving PoW......")
        for p1 in charset:
                for p2 in charset:
                        for p3 in charset:
                                for p4 in charset:
                                        result = p1 + p2 + p3 + p4
                                        plaintext = result + suffix
                                        m = hashlib.sha256()
                                        m.update(plaintext.encode())
                                        if m.hexdigest() == h:
                                                print("PoW solution has been found!")
                                                print(result)
                                                return result
def send_Data(num):
        r.recvuntil("give me a number:")
        r.sendline(str(num))
        r.recvuntil("done:")
        ct = int(r.recvuntil("\n")[:-1])
        return ct
def brute_flag(res,q,n,e):
        dic = ["0","1"]
        for x1 in dic:
                for x2 in dic:
                        for x3 in dic:
                                for x4 in dic:
                                        for x5 in dic:
                                                for x6 in dic:
                                                        for x7 in dic:
                                                                xx = x1 + x2 + x3 + x4 + x5 + x6 + x7
                                                                ct = 0
                                                                cnt = 0
                                                                for i in e:
                                                                        if xx[cnt]=='1':
                                                                                ct += pow(q,i,n)
                                                                                ct %= n
                                                                        cnt += 1
                                                                if ct == res:
                                                                        print("find ct: " + str(xx))
                                                                        return xx
def calc(xx,q,n,e):
        ct = 0
        cnt = 0
        for i in e:
                if xx[cnt] == '1':
                        ct += pow(q,i,n)
                        ct %= n
                cnt += 1
        return ct
r = remote("52.163.228.53",8081)
r.recvuntil("sha256(xxxx+")
prefix = r.recvuntil(") == ",drop = True).decode("utf-8")
target = r.recvuntil("\n",drop = True).decode("utf-8")
p = solve_PoW(prefix,target)
r.sendline(p)
r.recvuntil("n:")
n = int(r.recvuntil("\n")[:-1])
print(n)
rounds = (15 * 8 // 7) + 1
ct1 = send_Data(0)
ct2 = send_Data(0)
c1 = (ct1 - ct2) % n
ct3 = send_Data(0)
ct4 = send_Data(0)
c2 = (ct3 - ct4) % n
rounds -= 4
q = gmpy2.gcd(c1,c2)
q = gmpy2.gcd(q,n)
print(q)
assert(n % q == 0 and n != q)
e = []
p = n // q
assert(p * q == n)
phi = (p-1) * (q-1)
for i in range(1,8):
        tmp = (i**i**i)%phi
        e.append(int(tmp))
cts = []
for i in range(rounds):
        tmp_ct = send_Data(0)
        print(i,tmp_ct)
        cts.append(tmp_ct)
print(cts)
r.close()
flag = b"*CTF{"
flag = "00" + bin(bytes_to_long(flag))[2:]
flag = flag[:4*7]
test_flag = flag[:7]
iv = (ct1 - calc(test_flag,q,n,e)) % n
for i in cts:
        i = (i - iv) % n
        flag += brute_flag(i,q,n,e)
        print(flag)
flag = flag[:120]
flag = int(flag,2)
flag = long_to_bytes(flag)
print(flag)
# *CTF{yOuG0t1T!}
