import os
import string

tab = string.printable
tab = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ{}*'
sz = 46
a = [0]*sz

with open('../output','rb') as f:
    ct = f.read()

def se(i):
    global a
    print i,a
    if i>=sz:
        print ''.join(map(chr,a))
        exit()
    found = False
    for ch in tab:
        idx = (7*i+4)%sz
        a[idx] = ord(ch)
        with open('flag','wb') as f:
            f.write(''.join(map(chr, a)))
        os.system("../task")
        with open('output','rb') as f:
            outp = f.read()
        if ct[idx] == outp[idx]:
            se(i+1)
        
#a[:5] = [42, 99, 116, 102, 123]
se(0)
