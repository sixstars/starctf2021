FLAG01 = flag{have_you_tried_ghidra9.2_decompiler_
FLAG02 = if_you_have_hexriscv_plz_share_it_with_me_thx:P}
FLAG1 = flag{an_easy_rv64_stack_overflow_in_qemu_user}
FLAG2 = flag{qemu_user_s4ndb0x_is_dangerous}
RV = riscv64-linux-gnu-

all: main

main: main.c chacha20.c flag1.h flag2.h
	riscv64-linux-gnu-gcc main.c chacha20.c -fno-stack-protector -static -o main
	riscv64-linux-gnu-strip main

clean:
	rm main gen gen2
	rm flag1.h flag2.h
	rm flag1.enc flag2.enc
	rm sc.bin loader.bin
	rm sc loader

gen: gen.c chacha20.c

gen2: gen2.c

flag1.h: gen Makefile
	./gen $(FLAG01) > flag1.enc
	xxd -i flag1.enc > $@

flag2.h: gen2 Makefile
	./gen2 $(FLAG02) > flag2.enc
	xxd -i flag2.enc > $@

test: main
	echo $(FLAG01)$(FLAG02) | ./qemu-riscv64  ./main

sc: sc.c syscall.s
	$(RV)gcc $^ -Wa,-R -fPIC -nostdlib -Os -o $@

sc.bin: sc
	$(RV)objcopy -S -O binary -j .text $< $@

loader: loader.s
	$(RV)gcc $^ -Wa,-R -fPIC -nostdlib -Os -o $@

loader.bin: loader
	$(RV)objcopy -S -O binary -j .text $< $@

shellcode: sc.bin loader.bin

deploy: all
	cp main share
	cp qemu-riscv64 share
	echo $(FLAG1) > share/flag1
	echo $(FLAG2) > flag2
	tar czvf favourite_arch.tgz Dockerfile build.sh patch share docker-compose.yml readflag2 flag2 README.md xinetd

release: all
	cp main share
	cp qemu-riscv64 share
	echo flag1 > share/flag1
	echo flag2 > flag2
	tar czvf ../release/favourite_arch.tgz Dockerfile build.sh patch share docker-compose.yml readflag2 flag2 README.md xinetd
