from random import randint
import os
from flag import flag
N=64
key=randint(0,2**N)
#print key
key=bin(key)[2:].rjust(N,'0')
count=0
while True:
	p=0
	q=0
	new_key=''
	zeros=[0]
	for j in range(len(key)):
		if key[j]=='0':
			zeros.append(j)
	p=zeros[randint(0,len(zeros))-1]
	q=zeros[randint(0,len(zeros))-1]
	try:
		mask=int(raw_input("mask:"))
	except:
		exit(0)
	mask=bin(mask)[2:]
	if p>q:
		tmp=q
		q=p
		p=tmp
	cnt=0
	for j in range(0,N):
		if j in range(p,q+1):
			new_key+=str(int(mask[cnt])^int(key[j]))
		else:
			new_key+=key[j]
		cnt+=1
		cnt%=len(mask)
	key=new_key
	try:
		guess=int(raw_input("guess:"))
	except:
		exit(0)
	if guess==int(key,2):
		count+=1
		print 'Nice.'
	else:
		count=0
		print 'Oops.'
	if count>2:
		print flag




