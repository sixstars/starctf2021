## Puzzle

**Type**: Game

***
这道题有四种思路：
1. 手动拼:)
2. 写脚本，对比图片边缘进行拼合，flag使用的颜色比较独特(43,42,42)，相邻两块的flag断开后，(43,42,42)在两边缘上的位置只有1~2像素之差，长度也是一样，照此拼合即可。
3. 比较简单的一种方法，通过Google识图等找到原图，将原图切成同样块数，和puzzle对比每一块的像素，没有flag的块存在100%符合的对应块，有flag的块的符合度也应在70%以上，按原图拼回即可。
4. 最简单的一种方法，通过gaps工具拼图，然后猜测未拼出的字段内容即可(这种算是非预期方法，flag忘记混淆了 :( )

***
There are four ways to solve this question.
1. manually fix :)
2. write a script that compares the edges of the image for the puzzle, the flags use a unique colour (43,42,42), after the flags of two adjacent blocks are broken, the position of (43,42,42) on the two edges is only 1~2 pixels different, the length is also the same, so the puzzle can be put together accordingly.
3. A simpler method is to find the original image through Google, cut the original image into the same number of blocks, and compare the pixels of each block with those of the puzzle, so that the blocks without flags have a 100% match, and those with flags have a match of 70% or more.
4. The easiest way is to use the gaps tool and then guess the content of the unpieced fields (this is not the expected method, I forgot to mix up the flags...)
