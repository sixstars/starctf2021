## Little Tricks

**Type**: Forensic
***
文件类型为vhdx，用磁盘管理加载镜像。
加载后，磁盘要求输入密码解密bitlocker。
用bitcraker(https://github.com/e-ago/bitcracker)或其他破解工具暴力破解。
当然密码(12345678)其实是弱密码，可以直接猜到。
打开后，里面只有一个password.txt。
查找到$RECYCLE.BIN中有一个pdf。打开后是一个假flag。使用dd或其他工具分离出另一个pdf，获取到真flag.

***

The file is a vhdx image, use DiskManager to load it.
After loading, the disk asks for a password to decrypt bitlocker.
Using bitcraker(https://github.com/e-ago/bitcracker) or other crack tools to decrypt it.
The password(12345678) is weak and we can simply guess as well.
Inside the disk is a password txt. Useless
There is a pdf in $RECYCLE.BIN. Open it and ignore the fake flag. Use dd or other tools to get another pdf inside it.(pdf incredible update) 
Find flag!
