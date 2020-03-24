# LCD 调试总结
### 1. 调试LCD主要参考高通的文档:80-ph241-22_a_sdm439_sdm429_linux_android_display_bringup_guide.pdf
### 2. MIPI-DSI的三种模式:
	https://blog.csdn.net/eliot_shao/article/details/52474348?depth_1-utm_source=distribute.pc_relevant.none-task&utm_source=distribute.pc_relevant.none-task

### 3. LCD MIPI DSI简析:
	https://blog.csdn.net/liwei16611/article/details/70245686?depth_1-utm_source=distribute.pc_relevant.none-task&utm_source=distribute.pc_relevant.none-task

# TP调试总结

![TP电路](https://github.com/zzb2760715357/Picture/blob/master/3-misc/1.jpg)

#### TP主要的管脚有TP_INIT、TP_RST、TP_I2C_SDA、TP_I2C_SCL以及供电引脚VREG_L6_1P8
### AB协议
	A协议:如何把所有的原始触摸数据发送给接收者
	B协议:如何把每个触摸点的单独更新通过事件slots发送给接受者。
	
	A/B协议的划分:
	B协议又称为slot协议，那么input子系统里面使用的slot是什么，A/B协议究竟是如何划分的？
	slot直译为位置、槽，有两层含义:一层是位置，另一层是容器。在Input子系统中，它扮演的就是这两个角色。它产生于这样一个背景：
	如果从Device获取的当前数据与上一个数据相同，我们有必要再上报当前数据吗？如果我们不管两次数据是否一致都上报，那就是A协议；如果我们选择不上报，那么既然需要比较，总需要把上一次数据存起来吧，slot就是做这个事情的，显然这就是Slot(B)协议。
	需要注意的是，想要测试Device驱动的input部分是否正常的时候，假如使用的是B协议，input_report数据的时候要记得每次都要report不同的值，否则在HAL层是看不到数据不停上报的，因为前后两个数据相同的时候，B协议是不会上报到系统的。另外，在上层测试数据上报频率的时候，采用 数据总量/时间差 的方法，如果驱动采用的是B协议，测试结果也是不准确的。
	
	B:协议
	ABS_MT_TRACKING_ID  表示一次接触；  -1 代表一个不用的slot；
	释放事件：
	input_mt_slot(data->input_dev, i);
	input_mt_report_slot_state(data->input_dev, MT_TOOL_FINGER, false);  
	点击事件：
	input_mt_slot(data->input_dev, i);
	input_mt_report_slot_state(data->input_dev, MT_TOOL_FINGER, true);
	input_report_abs(data->input_dev, ABS_MT_TOUCH_MAJOR, 1);
	input_report_abs(data->input_dev, ABS_MT_POSITION_X,  current_events[i].x);
	input_report_abs(data->input_dev, ABS_MT_POSITION_Y,  current_events[i].y)
  

### 软件流程
![墩泰代码架构](https://github.com/zzb2760715357/Picture/blob/master/3-misc/2.jpg)

#### 设备节点:/sys/bus/i2c/drivers/fts_ts/3-0038

### linux下SPI结构主要通讯的流程如下:
	struct spi_message msg;
	struct spi_device *spi

	memset(&xfer[0], 0, sizeof(struct spi_transfer));
    memset(&xfer[1], 0, sizeof(struct spi_transfer));

	spi_message_init(&msg);
	xfer[0].tx_buf = &tx_buf[0];
    xfer[0].rx_buf = &rx_buf[0];
    xfer[0].len = 1;
    xfer[0].delay_usecs = DELAY_AFTER_FIRST_BYTE;
	spi_message_add_tail(&xfer[0], &msg);

	spi_sync(spi, &msg);

### 重要的结构体:
	static struct spi_driver fts_ts_driver = {
	    .probe = fts_ts_probe,
	    .remove = fts_ts_remove,
	    .driver = {
	        .name = FTS_DRIVER_NAME,
	        .owner = THIS_MODULE,
	        .of_match_table = of_match_ptr(fts_dt_match),
	    },
	    .id_table = fts_ts_id,
	};

	struct fts_ts_platform_data {
	    u32 irq_gpio;
	    u32 irq_gpio_flags;
	    u32 reset_gpio;
	    u32 reset_gpio_flags;
	    bool have_key;
	    u32 key_number;
	    u32 keys[FTS_MAX_KEYS];
	    u32 key_y_coords[FTS_MAX_KEYS];
	    u32 key_x_coords[FTS_MAX_KEYS];
	    u32 x_max;
	    u32 y_max;
	    u32 x_min;
	    u32 y_min;
	    u32 max_touch_number;
	};

	手势识别重要的结构体:
	/*****************************************************************************/
	/*
	 * gesture_id    - mean which gesture is recognised
	 * point_num     - points number of this gesture
	 * coordinate_x  - All gesture point x coordinate
	 * coordinate_y  - All gesture point y coordinate
	 * mode          - gesture enable/disable, need enable by host
	 *               - 1:enable gesture function(default)  0:disable
	 * active        - gesture work flag,
	 *                 always set 1 when suspend, set 0 when resume
	 */
	struct fts_gesture_st {
	    u8 gesture_id;
	    u8 point_num;
	    u16 coordinate_x[FTS_GESTURE_POINTS_MAX];
	    u16 coordinate_y[FTS_GESTURE_POINTS_MAX];
	};

	struct ts_event {
	    int x;      /*x coordinate */
	    int y;      /*y coordinate */
	    int p;      /* pressure */
	    int flag;   /* touch event flag: 0 -- down; 1-- up; 2 -- contact */
	    int id;     /*touch ID */
	    int area;
	};


### DTS的配置 墩泰Focaltech_touch FT3528

	I2C通讯方式设备树的配置
	i2c@f9927000 { 
		focaltech@38{ 
			compatible = "focaltech,fts";                   // 跟设备驱动匹配的名字	 
			reg = <0x38>;                                   // 设备的I2C地址  					
			interrupt-parent = <&msm_gpio>;				
			interrupts = <13 0x02>;                         // 设置中断号，以及中断触发模式
			focaltech,reset-gpio = <&msm_gpio 12 0x01>;     // 设置TP的复位引脚
			focaltech,irq-gpio = <&msm_gpio 13 0x02>; 	    // 设置TP的中断引脚
			focaltech,max-touch-number = <10>;              // 设置支持的最大触点数			
			focaltech,display-coords =  <0 0 1080 1920>;    // 设置屏的分辨率	 
			
			pinctrl-names = "pmx_ts_active","pmx_ts_suspend","pmx_ts_release";  // 使用pinctrl来设置，TP的中断引脚，复位引脚在active、suspend、release状态下gpio口的驱动能力，以及上拉下拉的状态，达到节省功耗的目的
			pinctrl-0 = <&ts_int_active &ts_reset_active>;
			pinctrl-1 = <&ts_int_suspend &ts_reset_suspend>;
			pinctrl-2 = <&ts_release>;

			/*
			focaltech,have-key;
			focaltech,key-number = <3>;	
			focaltech,keys = <139 102 158>; 	
			focaltech,key-x-coords = <200 600 800>;
			focaltech,key-y-coords = <2000 2000 2000>; 
			*/
		};
	};

	SPI通讯方式设备树的配置:
	spi@78b9000 {
		focaltech@0 { 
			compatible = "focaltech,fts";
			reg = <0x0>;
			spi-max-frequency = <6000000>;
			interrupt-parent = <&msm_gpio>;
			interrupts = <13 0x2>;
			focaltech,reset-gpio = <&msm_gpio 12 0x01>; 
			focaltech,irq-gpio = <&msm_gpio 13 0x02>; 	
			focaltech,max-touch-number = <10>;			
			focaltech,display-coords =  <0 0 1080 1920>;
			
			pinctrl-names = "pmx_ts_active","pmx_ts_suspend","pmx_ts_release";
			pinctrl-0 = <&ts_int_active &ts_reset_active>;
			pinctrl-1 = <&ts_int_suspend &ts_reset_suspend>;
			pinctrl-2 = <&ts_release>;
		};
	}; 

### fts_ts_init代码流程:
		fts_ts_init
			spi_register_driver(&fts_ts_driver); // 主要是注册struct spi_driver这个结构体
				fts_ts_probe
					spi->mode = SPI_MODE_1;      // 如果CPOL=0，串行同步时钟的空闲状态为低电平；如果CPOL=1，串行同步时钟的空闲状态为高电平。时钟相位(CPHA)能够配置用于选择两种不同的传输协议之一进行数据传输。如果 CPHA=0，在串行同步时钟的第一个跳变沿(上升或下降)数据被采样；如果CPHA=1，在串行同步时钟的第二个跳变沿(上升或下降)数据被采样
    				spi->bits_per_word = 8;
    				spi_setup(spi);              // 设置SPI的模式
					ts_data->spi = spi;
    				ts_data->dev = &spi->dev;
					spi_set_drvdata(spi, ts_data);
					fts_ts_probe_entry
						fts_parse_dt            // 解析设备树
						ts_data->ts_workqueue = create_singlethread_workqueue("fts_wq")  //创建一个线程
						fts_bus_init           // 为spi接口的TP分别申请256个字节作为发生数据和接收数据的缓存
						fts_input_init             // 初始化输入子系统struct input_dev
							input_allocate_device
							__set_bit(EV_SYN, input_dev->evbit);     // 同步事件
	    					__set_bit(EV_ABS, input_dev->evbit);     // 绝对坐标事件
	    					__set_bit(EV_KEY, input_dev->evbit);     // 按键事件
	    					__set_bit(BTN_TOUCH, input_dev->keybit); // 压力事件 
	    					__set_bit(INPUT_PROP_DIRECT, input_dev->propbit);
							input_mt_init_slots(input_dev, pdata->max_touch_number, INPUT_MT_DIRECT); // B协议
							input_set_abs_params(input_dev, ABS_MT_POSITION_X, pdata->x_min, pdata->x_max, 0, 0);  // 设置，x,y轴的最大和最小值
		    				input_set_abs_params(input_dev, ABS_MT_POSITION_Y, pdata->y_min, pdata->y_max, 0, 0);
		    				input_set_abs_params(input_dev, ABS_MT_TOUCH_MAJOR, 0, 0xFF, 0, 0);
							input_register_device(input_dev);
						fts_report_buffer_init
							ts_data->events = (struct ts_event *)kzalloc(events_num, GFP_KERNEL);  // 支持10点触控，为每个点分配一个结构体
						fts_gpio_configure     // 申请中断脚作为输入引脚，复位引脚为输出引脚
						fts_power_source_init  // 设置vdd-supply、vcc_i2c-supply供电部分
							fts_pinctrl_init   // 设置相关的pinctrl
							fts_pinctrl_select_normal  // 将引脚设置为normal模式
						fts_get_ic_information  // 读取TP芯片的IC信息
							fts_reset_proc      // 拉高、拉低复位引脚
							fts_read_bootid     // 读取芯片的ID
						fts_create_apk_debug_channel  // 创建APK调试的一些节点,关闭ESD,读寄存器，写寄存器，复位芯片等操作
							proc->proc_entry->write_proc = fts_debug_write;
		    				proc->proc_entry->read_proc = fts_debug_read;
						fts_create_sysfs       // 创建调试的节点
							&dev_attr_fts_fw_version.attr,
						    &dev_attr_fts_rw_reg.attr,
						    &dev_attr_fts_dump_reg.attr,
						    &dev_attr_fts_upgrade_bin.attr,
						    &dev_attr_fts_force_upgrade.attr,
						    &dev_attr_fts_driver_info.attr,
						    &dev_attr_fts_hw_reset.attr,
						    &dev_attr_fts_irq.attr,
						    &dev_attr_fts_boot_mode.attr,
						    &dev_attr_fts_touch_point.attr,
						    &dev_attr_fts_log_level.attr,
						fts_ex_mode_init       // 创建口袋模式，防误触，充电模式等节点
							&dev_attr_fts_glove_mode.attr,
						    &dev_attr_fts_cover_mode.attr,
						    &dev_attr_fts_charger_mode.attr,
						fts_gesture_init      // 手势识别的初始化,设置支持的手机识别的事件,同时创建节点
							input_set_capability(input_dev, EV_KEY, KEY_POWER);
							 __set_bit(KEY_GESTURE_RIGHT, input_dev->keybit);
							.attrs = fts_gesture_mode_attrs,
						fts_esdcheck_init     // 设置ESD功能
							INIT_DELAYED_WORK(&ts_data->esdcheck_work, esdcheck_func);  // 创建ESD的工作队列
						fts_irq_registration  // 注册中断，中断线程化
							request_threaded_irq(ts_data->irq, NULL, fts_irq_handler,
		                               pdata->irq_gpio_flags,
		                               FTS_DRIVER_NAME, ts_data);
						fts_fwupg_init        // 固件升级流程

						if (ts_data->ts_workqueue) {    // TP跟LCD的数据交互过程
					        INIT_WORK(&ts_data->resume_work, fts_resume_work);
					    }
					    ts_data->fb_notif.notifier_call = fb_notifier_callback;
					    ret = fb_register_client(&ts_data->fb_notif);
					    if (ret) {
					        FTS_ERROR("[FB]Unable to register fb_notifier: %d", ret);
					    }


### SPI接口发送数据和读取数据的流程
	1、 fts_fts_writewrite     先发送命令，之后发送数据，无论发送数据还是发送命令，在发送之前需要等待空闲时间才进行
		fts_read_bootid
			fts_write                  // 先发送命令，之后发送数据
				fts_boot_write
					fts_wait_idle      // txbuf 填充的是STATUS_PACKAGE
						txbuf[0] = STATUS_PACKAGE; // 封装发送的数据		
						fts_spi_transfer(txbuf, rxbuf, txlen);
							spi_message_init
							spi_message_add_tail
							spi_sync(spi, &msg);
					fts_cmdpkg_wirte   // txbuf 填充的是COMMAND_PACKAGE	

	2、 fts_read(id_cmd, id_cmd_len, chip_id, 2);   // id_cmd 封装的是读的命令
		fts_wait_idle                           // 等待空闲
		fts_cmdpkg_wirte                        // 写命令
		fts_wait_idle                           // 等待空闲
		txbuf[0] = DATA_PACKAGE;
        txlen = CD_PACKAGE_BUFLEN + datalen;
		fts_spi_transfer
	
	
### fts_esdcheck_init的流程
		fts_esdcheck_init
			INIT_DELAYED_WORK(&ts_data->esdcheck_work, esdcheck_func);
			fts_esdcheck_switch(ENABLE);
			queue_delayed_work(ts_data->ts_workqueue,
                               &ts_data->esdcheck_work, msecs_to_jiffies(ESDCHECK_WAIT_TIME));
			esdcheck_func
				esdcheck_algorithm(ts_data);
					fts_esdcheck_data.suspend == 1   系统休眠的时候是关闭ESD功能
        		queue_delayed_work(ts_data->ts_workqueue, &ts_data->esdcheck_work,
                           msecs_to_jiffies(ESDCHECK_WAIT_TIME));
					idc_esdcheck_lcderror            // LCD的ESD功能
					get_chip_id                      // 通过读取芯片的ID来判断，ESD是否需要复位TP
					get_flow_cnt                     // 读取0x91寄存器来判断是否需要复位芯片
					fts_esdcheck_tp_reset            // 复位TP芯片
						fts_reset_proc
						fts_release_all_finger
						fts_tp_state_recovery        // 复位之后等待TP状态的恢复

		
###	报点上报的流程.
		fts_irq_handler
			fts_irq_read_report
				fts_esdcheck_set_intr
				fts_prc_queue_work                   // 纠正和防止误报的功能
				fts_read_parse_touchdata             // 解析TP的数据
					ret = fts_read(buf, 1, buf + 1, data->pnt_buf_size - 1);   // 读取中断过程中上报的数据
					fts_fw_recovery                  // 检测TP是否需要recovery
					fts_gesture_readdata(data, buf + FTS_TOUCH_DATA_LEN);      // 解析手势识别模式的数据,之前读取的数据包含手势识别相关的
					input_report_key(input_dev, gesture, 1);
			        input_sync(input_dev);
			        input_report_key(input_dev, gesture, 0);
			        input_sync(input_dev);                                    // 上报识别到的手势状态
				fts_input_report_b                                            // 上报识别到的触摸点
					fts_input_report_key                                      // 跟进每个手指触摸的区域，判断是否在虚拟按键的区间
					按下:
					input_mt_report_slot_state(data->input_dev, MT_TOOL_FINGER, true);
					input_report_abs(data->input_dev, ABS_MT_TOUCH_MAJOR, events[i].area);
		            input_report_abs(data->input_dev, ABS_MT_POSITION_X, events[i].x);
		            input_report_abs(data->input_dev, ABS_MT_POSITION_Y, events[i].y);
					释放:
					input_mt_report_slot_state(data->input_dev, MT_TOOL_FINGER, false);
					input_sync(data->input_dev);

	5. 固件升级流程


	6. TP的数据是如何跟LCD的关联起来
	7. 虚拟按键的原理，就是在处理TP数据的时候，判断一下，TP触摸的点十分在这个区域如果在这个区域就上报对应的按键值
	
					    





	




# Linux基础知识
	使用likely(),执行if后面的语句的机会更大，使用unlikely(),执行else后面的语句机会更大一些。
	linux下regulator知识
