## babyxv6

### Idea

Just made a new syscall which does simply stack overflow in kernel space. You can clone the recent [xv6-riscv repository](https://github.com/mit-pdos/xv6-riscv), and diff to find changed files. Besides the syscall code, I also patched `console.c` to allow `\x00` input.

### Exploit

The first point is to construct rop chain. I do find some a0 gadgets like below:

```assembly
800003fa:   fec42783                lw      a5,-20(s0)
800003fe:   853e                    mv      a0,a5
80000400:   70a2                    ld      ra,40(sp)
80000402:   7402                    ld      s0,32(sp)
80000404:   6145                    addi    sp,sp,48
80000406:   8082                    ret
```

But actually we don't need gadgets to control arguments at all. Let's look at the overflow function:

```c
return copyin(myproc()->pagetable, buf, src, sz);
```

Go deeper into `copyin`, and the last called function is:

```c
memmove(dst, (void *)(pa0 + (srcva - va0)), n);
// ...
return 0;
```

So, when overflow happens, `a0` is 0, `a1` is the **"physical address"** of user stack, and `a2` is the length. It's natural to think about `read()`, actually `consoleread()` in this kernel.

```c
// user read()s from the console go here.
// copy (up to) a whole input line to dst.
// user_dist indicates whether dst is a user
// or kernel address.
//
int consoleread(int user_dst, uint64 dst, int n)
```

And obviously, this address is writable. 

```c
// vm.c
// map kernel data and the physical RAM we'll make use of.
kvmmap(kpgtbl, (uint64)etext, (uint64)etext, PHYSTOP - (uint64)etext, PTE_R | PTE_W);
```

In a nutshell:

1. use `consoleread()` to modify user stack
2. use `usertrapret()` to switch back to user mode
3. return to shellcode in user mode with ASLR

There is (maybe) another thing to take care of, the buffer size of xv6 console is `0x80`:

```c
struct
{
    struct spinlock lock;

    // input
#define INPUT_BUF 128
    char buf[INPUT_BUF];
    uint r; // Read index
    uint w; // Write index
    uint e; // Edit index
} cons;
```

You may need packetization to make your exploit stable.