.section .text
.global syscall
syscall:
mv a7, a0
mv a0, a1
mv a1, a2
mv a2, a3
mv a3, a4
mv a4, a5
mv a5, a6
ecall
ret

#.global flag_path 
#flag_path:
#.string "flag"
#.global maps_path 
#maps_path:
#.string "/proc/self/maps"
#.global shell_path
#shell_path:
#.string "/bin/sh"
