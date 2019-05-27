### SDM439平台出现部分机型SD卡不能识别mmc1: error -110 whilst initialising SD card
#### 打印了如下的log：
	05-10 18:01:02.699 <3>[ 3079.000640] mmc1: data txfr (0x00100000) error: -110 after 163 ms
	05-10 18:01:02.699 <6>[ 3079.000652] sdhci: =========== REGISTER DUMP (mmc1)===========
	05-10 18:01:02.699 <6>[ 3079.000655] sdhci: Sys addr: 0x00000000 | Version:  0x00004d02
	05-10 18:01:02.699 <6>[ 3079.000658] sdhci: Blk size: 0x00004040 | Blk cnt:  0x00000001
	05-10 18:01:02.699 <6>[ 3079.000660] sdhci: Argument: 0x80ff3fff | Trn mode: 0x00000013
	05-10 18:01:02.699 <6>[ 3079.000663] sdhci: Present:  0x03f80206 | Host ctl: 0x0000001a
	05-10 18:01:02.699 <6>[ 3079.000665] sdhci: Power:    0x0000000d | Blk gap:  0x00000000
	05-10 18:01:02.699 <6>[ 3079.000667] sdhci: Wake-up:  0x00000000 | Clock:    0x00000007
	05-10 18:01:02.699 <6>[ 3079.000670] sdhci: Timeout:  0x00000001 | Int stat: 0x00000000
	05-10 18:01:02.699 <6>[ 3079.000672] sdhci: Int enab: 0x03ff900b | Sig enab: 0x03ff100b
	05-10 18:01:02.699 <6>[ 3079.000674] sdhci: AC12 err: 0x00000000 | Slot int: 0x00000000
	05-10 18:01:02.699 <6>[ 3079.000677] sdhci: Caps:     0x362dc8b2 | Caps_1:   0x00008007
	05-10 18:01:02.699 <6>[ 3079.000679] sdhci: Cmd:      0x0000063a | Max curr: 0x00000000
	05-10 18:01:02.699 <6>[ 3079.000682] sdhci: Resp 1:   0x5b590000 | Resp 0:   0x00000900
	05-10 18:01:02.699 <6>[ 3079.000684] sdhci: Resp 3:   0x0a404012 | Resp 2:   0x76b27f80
	05-10 18:01:02.699 <6>[ 3079.000686] sdhci: Host ctl2: 0x00000008
	05-10 18:01:02.699 <6>[ 3079.000689] sdhci: ADMA Err: 0x00000003 | ADMA Ptr: 0x00000000f5c9820c
	05-10 18:01:02.699 <6>[ 3079.000695] ----------- VENDOR REGISTER DUMP -----------
	05-10 18:01:02.699 <6>[ 3079.000699] Data cnt: 0x00000040 | Fifo cnt: 0x00000040 | Int sts: 0x000c0000
	05-10 18:01:02.700 <6>[ 3079.000702] DLL cfg:  0x6002642c | DLL sts:  0x00000000 | SDCC ver: 0x1000004d
	05-10 18:01:02.700 <6>[ 3079.000705] Vndr func: 0x00018a9c | Vndr adma err : addr0: 0x000a3f80 addr1: 0x00000000
	05-10 18:01:02.700 <6>[ 3079.000707] Vndr func2: 0xfa8018a8
	05-10 18:01:02.700 <6>[ 3079.000746]  Test bus[0 to 3]: 0x00000000 0x00000000 0x00000000 0x00000000
	05-10 18:01:02.700 <6>[ 3079.000748]  Test bus[4 to 7]: 0x00000000 0x00000000 0x00000000 0x00000000
	05-10 18:01:02.700 <6>[ 3079.000751]  Test bus[8 to 11]: 0x00000000 0x00000000 0x00000000 0x00000000
	05-10 18:01:02.700 <6>[ 3079.000753]  Test bus[12 to 15]: 0x00000000 0x00000000 0x00000000 0x00000000
	05-10 18:01:02.700 <6>[ 3079.000755]  Test bus[16 to 19]: 0x00000000 0x00000000 0x00000000 0x00000000
	05-10 18:01:02.700 <6>[ 3079.000758]  Test bus[20 to 23]: 0x00000000 0x00000000 0x00000000 0x00000000
	05-10 18:01:02.700 <6>[ 3079.000760]  Test bus[24 to 27]: 0x00000000 0x00000000 0x00000000 0x00000000
	05-10 18:01:02.700 <6>[ 3079.000763]  Test bus[28 to 31]: 0x00000000 0x00000000 0x00000000 0x00000000
	05-10 18:01:02.700 <6>[ 3079.000766]  Test bus[32 to 35]: 0x00000000 0x00000000 0x00000000 0x00000000
	05-10 18:01:02.700 <6>[ 3079.000768]  Test bus[36 to 39]: 0x00000000 0x00000000 0x00000000 0x00000000
	05-10 18:01:02.700 <6>[ 3079.000770]  Test bus[40 to 43]: 0x00000000 0x00000000 0x00000000 0x00000000
	05-10 18:01:02.700 <6>[ 3079.000773]  Test bus[44 to 47]: 0x00000000 0x00000000 0x00000000 0x00000000
	05-10 18:01:02.700 <6>[ 3079.000776]  Test bus[48 to 51]: 0x00000000 0x00000000 0x00000000 0x00000000
	05-10 18:01:02.700 <6>[ 3079.000778]  Test bus[52 to 55]: 0x00000000 0x00000000 0x00000000 0x00000000
	05-10 18:01:02.700 <6>[ 3079.000781]  Test bus[56 to 59]: 0x00000000 0x00000000 0x00000000 0x00000000
	05-10 18:01:02.700 <6>[ 3079.000785] mmc1: clk: 400000 clk-gated: 0 claimer: kworker/7:5 pwr: 12 host->irq = 131072
	05-10 18:01:02.700 <6>[ 3079.000788] mmc1: rpmstatus[pltfm](runtime-suspend:usage_count:disable_depth)(0:1:0)
	05-10 18:01:02.700 <6>[ 3079.000790] sdhci: ===========================================
	05-10 18:01:02.765 <6>[ 3079.066337] [FTS][Info]TP Ready, Device ID = 0x54
	05-10 18:01:03.559 <3>[ 3079.862932] mmc1: mmc_sd_init_card() failure (err = -110)
	05-10 18:01:03.559 <3>[ 3079.862944] mmc1: error -110 whilst initialising SD card

#### 从log上分析出错的应该是在SD的初始化的阶段有问题(mmc1: error -110 whilst initialising SD card)。有可能是SD卡在上电的时候出现电源还没有稳定，需要增大上电等待的延迟,延迟的时间自己设定。代码修改如下:
	diff --git a/drivers/mmc/core/core.c b/drivers/mmc/core/core.c 
	index eb9ff36..7842f45 100644 
	--- a/drivers/mmc/core/core.c 
	+++ b/drivers/mmc/core/core.c 
	@@ -3313,6 +3313,9 @@ void mmc_power_up(struct mmc_host *host, u32 ocr) 
	
	host->ios.vdd = fls(ocr) - 1; 
	host->ios.power_mode = MMC_POWER_UP; 
	+ 
	+ printk(KERN_ERR"zhuangzebin:>>>>>%s-%d<<<<<<<\r\n",__func__,__LINE__); 
	+ dev_dbg(mmc_dev(host), "zhuangzebin mmc before init\n"); 
	/* Set initial state and call mmc_set_ios */ 
	mmc_set_initial_state(host); 
	
	@@ -3328,7 +3331,7 @@ void mmc_power_up(struct mmc_host *host, u32 ocr) 
	* This delay should be sufficient to allow the power supply 
	* to reach the minimum voltage. 
	*/ 
	- mmc_delay(10); 
	+ mmc_delay(100); 
	
	mmc_pwrseq_post_power_on(host); 
	
	@@ -3341,9 +3344,11 @@ void mmc_power_up(struct mmc_host *host, u32 ocr) 
	* This delay must be at least 74 clock sizes, or 1 ms, or the 
	* time required to reach a stable voltage. 
	*/ 
	- mmc_delay(10); 
	+ mmc_delay(100); 
	
	mmc_host_clk_release(host); 
	+ 
	+ mmc_delay(100); 
	}

#### 编译重新烧录固件，仍然有这个问题的存在，已经把延迟的时间增大了10倍，排除软件问题，后面找硬件分析，SD卡的一颗物料没有焊接。而且机器有拆过的痕迹，那颗物料刚好处于边缘的地方，有可能是拆卸的时候导致物料脱落，后面硬件把物料焊接上，可以识别到SD卡。