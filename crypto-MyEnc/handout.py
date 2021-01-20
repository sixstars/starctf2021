from Crypto.Util.number import getPrime,bytes_to_long
import time,urandom
from flag import flag
iv=bytes_to_long(urandom(128))
assert len(flag)==15
keystream=bin(int(flag.encode('hex'),16))[2:].rjust(8*len(flag),'0')
p=getPrime(1024)
q=getPrime(1024)
n=p*q
print "n:",n
cnt=0
while True:
	try:
		print 'give me a number:'
		m=int(raw_input())
	except:
		break
	ct=iv
	for i in range(1,8):
		if keystream[cnt]=='1':
			ct+=pow(m^q,i**i**i,n)
			ct%=n
		cnt=(cnt+1)%len(keystream)
	print "done:",ct
