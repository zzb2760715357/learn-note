### SDM439平台如何查看DDR的频率
### 通过访问如下节点查询：cat /sys/kernel/debug/clk/bimc_clk/measure
### 681.6MHz and higher frequencies use DDR CC. So, real DDR frequency is measure frequency * 2  