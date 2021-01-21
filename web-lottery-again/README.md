# lottery again

Lottery is encrypted with Rijndael 256 ECB mode. It's obviously that we can replace ECB block.

Block size is 32 bytes here. Look at the block:

```
{"lottery":"dbad9437-d763-46cb-9
796-f1ae8a53b870","user":"da757b
a3-b195-458d-8039-9f5f37e31efd",
"coin":4}
```

If we simply replace the second and third block for user id, the lottery id will be illegal.
However, we can replace only the third block with both the second and third block. The result will be:

```
{"lottery":"dbad9437-d763-46cb-9
796-f1ae8a53b870","user":"da757b
XXXXXXXXXXXXXXXX","user":"AAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
"coin":4}
```

There will be two user fields and only the last one will take effect.

By the way, we can replace the coin block with bigger one to speed up the exploit.
