#!/usr/bin/python3 -u
# encoding: utf-8

import random, string, sys, os
from hashlib import sha256

os.chdir(os.path.dirname(os.path.realpath(__file__)))

def proof_of_work():
    proof = "".join([random.choice(string.ascii_letters+string.digits) for i in range(20)])
    digest = sha256(proof.encode("utf8")).hexdigest()
    print("sha256(xxxx+%s) == %s"%(proof[4:],digest))
    print("Give me xxxx:")
    x = input() 
    if len(x) != 4 or x != proof[:4]:
        return False
    return True

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("./pow.py prog timeout")
        exit(0)
    if not proof_of_work():
        exit(0)
    else:
        os.execv("/bin/sh", ["sh", "-c", "timeout %s %s 2>/dev/null" % (sys.argv[2], sys.argv[1])])

