CC=/home/zhuangzebin/project/linux5.0/BiscuitOS/output/linux-5.0-aarch/aarch64-linux-gnu/aarch64-linux-gnu/bin/aarch64-linux-gnu-gcc
prom=test.bin
obj=test.o
CFLAGS=-static

$(prom):$(obj)
	$(CC) -o $(prom) $(obj) $(CFLAGS)

%.o:%.c
	$(CC) -c $^ -o $@

clean:
	rm -rf $(obj) $(prom)

install:
	cp $(prom)  /home/zhuangzebin/project/linux5.0/BiscuitOS/output/linux-5.0-aarch/rootfs/ext4/mnt/
