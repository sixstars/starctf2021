## babypac

### Idea

The idea derives from https://googleprojectzero.blogspot.com/2019/02/examining-pointer-authentication-on.html and I just want to introduce this mechanism to everyone.

The program is basically a authenticate system which allows you to input a number and do some encryption. If the authentication passes, there will be a simple stack overflow.

The point is that the binary is compiled with `-march=armv8.3a -mbranch-protection=pac-ret`, so simply overflow doesn't work. You need to find out how to forge the correct return address to anywhere we want.

### Vulnerability

There are obvious negative index vulns in `enc()` and `auth()` functions, so we can put useful data in `name`.

The crucial point of bypassing PAC is that there is a implicit signing gadget before encryption which is not visible in IDA decompile code:

```assembly
.text:0000000000400B70 loc_400B70                              ; CODE XREF: sub_400AFC+70↑j
.text:0000000000400B70                 LDURSW          X8, [X29,#var_4]
.text:0000000000400B74                 LSL             X8, X8, #4
.text:0000000000400B78                 ADRL            X9, qword_412050
.text:0000000000400B80                 LDR             X8, [X9,X8]
.text:0000000000400B84                 STR             X8, [SP,#0x20+var_10]
.text:0000000000400B88                 LDR             X8, [SP,#0x20+var_10]
.text:0000000000400B8C                 PACIA           X8, SP
.text:0000000000400B90                 STR             X8, [SP,#0x20+var_10]
.text:0000000000400B94                 LDR             X0, [SP,#0x20+var_10]
.text:0000000000400B98                 STR             X9, [SP,#0x20+var_20]
.text:0000000000400B9C                 BL              do_encryption
```

So we can use this `PACIA` to sign our assigned return address and leak it by printf.

### Exploit

- `enc(-2)` to forge return address, `show()` to leak it
- `enc(-1)` and `auth(-1)` to pass authentication
- do simple stack overflow on qemu-user

### What's else

Apparently pow is too weak and some team just brute force it out. My fault :P
