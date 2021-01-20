读了一下选手们的回复发现这道题目我自己准备的解才是非预期，所以这里参考Kap0K战队的exp给出预期解：
	连续输入0，将得到的ct相减并gcd得到q，根据flag格式可以得到iv，之后每7bit爆破即可得到flag。
	Input 0s, and calc the differences between cts and use gcd to get q. The flag starts with '*CTF' so you can get iv, then bruteforce each 7-bit and you can get flag.