.section .text
.global _start
_start:
li a0, 0
auipc a1, 0
li a2, 0x200
li a7, 63
ecall
nop
