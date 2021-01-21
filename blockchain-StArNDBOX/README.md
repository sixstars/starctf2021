# BLOCKCHAIN-StArNDBOX
ZH: 题目给出了源代码，我们可以看到是一个沙箱模型，需要选手创建合约调用此合约，合约会调用参数地址的合约并检查字节码通过给出的check，题目给的是个质数检查函数，但是函数并不是完整的质数检查函数，其中0也包含在其中，这样由于RETURN函数的字节码并非质数，所以我们用00（stop）替代，即可。调用call 将参数布置好布属合约即可。下面是exp。

0x61000061000061000061000061006161000301610000619789f100

EN: The game gives the source code, we can see that it is a sandbox model, the player needs to create a contract to call this contract, the contract will call the contract of the parameter address and check the byte code through the given check, the question gives a prime number check function, but the function is not a complete prime number check function, in which 0 is also included, so that since the byte code of the RETURN function is not prime
number, so we use 00 (stop) instead, can be. Call call will be laid out the parameters of the genus contract can be. Here are the exploit.

0x61000061000061000061000061006161000301610000619789f100
