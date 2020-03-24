# vivi.c驱动分析
### 本实验的最终目的是找出vivi.c中关键的接口，去掉一些不必要的接口
### 1、 xawtv.log 这分log是使用strace -o xawtv.log xawtv这样播放摄像头抓取的log，我们根据这份log分析xawtv打开vivi驱动的调用流程
### 2、 xawtv涉及的vivi驱动的系统调用.txt  这份log是从xawtv.log中筛选出跟vivi驱动相关的系统调用.
### 3、 xawtv的主要代码drv0-v4l2.c
### camera相关不错的文档
	https://www.cnblogs.com/emouse/archive/2013/03/04/2943243.html

### 调用的过程
	对应这份应用程序没有用到的接口
	ioctl(4, VIDIOC_G_FMT                                           // 列举输入源
	for 
		ioctl(4, VIDIOC_ENUM_FMT                                    // 查询并显示支持的格式
	ioctl(4, VIDIOC_QUERYCAP                                        // 查询设备的属性
	ioctl(4, VIDIOC_G_INPUT                                         // 查询当前的输入设备
	ioctl(4, VIDIOC_ENUMINPUT                                       // 列举输入设备

	ioctl(4, VIDIOC_QUERYCAP                                        // 查询当前的输入设备 

	v4l2_open
		open("/dev/video0"                                              // 打开camera
		ioctl(4, VIDIOC_QUERYCAP                                        // 查询设备的属性

		get_device_capabilities
			for()
				ioctl(4, VIDIOC_ENUMINPUT                                   // 列举输入设备
	
			for()
				ioctl(4, VIDIOC_ENUMSTD                                     // 列举标准(制式)
		
			for()
				ioctl(4, VIDIOC_ENUM_FMT                                // 列举格式

			ioctl(4, VIDIOC_G_PARM                                      // 得到Stream信息
	
			for()
				VIDIOC_QUERYCTRL                                        // 查询属性
	
	v4l2_read_attr
		ioctl(4, VIDIOC_G_STD                                           // 查询当前使用的标准制式
		ioctl(4, VIDIOC_G_INPUT                                         // 查询当前的输入设备
		ioctl(4, VIDIOC_G_CTRL                                          // 获得当前属性, 比如亮度是多少
	
	v4l2_overlay
		ioctl(4, VIDIOC_TRY_FMT                                     // 试试能否支持某种格式
    	ioctl(4, VIDIOC_S_FMT                                       // 设置摄像头使用某种格式

	v4l2_start_streaming
		ioctl(4, VIDIOC_REQBUFS                                     // 请求系统分配缓冲区
		for()
			ioctl(4, VIDIOC_QUERYBUF                                // 查询所分配的缓冲区
		mmap
	
		for()
			ioctl(4, VIDIOC_QBUF                                        // 把缓冲区放入队列
		ioctl(4, VIDIOC_STREAMON                                        // 启动摄像头
	v4l2_write_attr
		for()
			ioctl(4, VIDIOC_S_CTRL                                      // 设置属性

		ioctl(4, VIDIOC_S_INPUT                                         // 设置输入源
		ioctl(4, VIDIOC_S_STD                                           // 设置标准制式

	v4l2_waiton
		select(5, 
		ioctl(4, VIDIOC_DQBUF                                       // 把缓冲区从队列中取出


		ioctl(4, VIDIOC_QBUF                                        // 把缓冲区入队列
	
	ioctl(4, VIDIOC_STREAMOFF                                       // 关闭摄像头

	经过以上的分析xawtv的几大函数为:
	v4l2_open
	v4l2_read_attr
	v4l2_start_streaming
	v4l2_write_attr
	

### 将上面的调用过程跟drv0-v4l2.c 结合一起分析
	open("/dev/video0"                                              // 打开camera
	ioctl(4, VIDIOC_QUERYCAP                                        // 查询设备的属性
	ioctl(4, VIDIOC_G_FMT                                           // 列举输入源
	for 
		ioctl(4, VIDIOC_ENUM_FMT                                    // 查询并显示支持的格式                     
	
	ioctl(4, VIDIOC_QUERYCAP                                        // 查询设备的属性
	ioctl(4, VIDIOC_G_INPUT                                         // 查询当前的输入设备
	ioctl(4, VIDIOC_ENUMINPUT                                       // 列举输入设备

	ioctl(4, VIDIOC_QUERYCAP                                        // 查询当前的输入设备
	for()
		ioctl(4, VIDIOC_ENUMINPUT                                   // 列举输入设备

	for()
		ioctl(4, VIDIOC_ENUMSTD                                     // 列举标准(制式)
	
	for()
		ioctl(4, VIDIOC_ENUM_FMT                                    // 列举格式

	ioctl(4, VIDIOC_G_PARM                                          // 得到Stream信息
	
	for()
		VIDIOC_QUERYCTRL                                            // 查询属性

	ioctl(4, VIDIOC_G_STD                                           // 查询当前使用的标准制式

	ioctl(4, VIDIOC_G_INPUT                                         // 查询当前的输入设备

	for()
		ioctl(4, VIDIOC_G_CTRL                                      // 获得当前属性, 比如亮度是多少
	ioctl(4, VIDIOC_TRY_FMT                                         // 试试能否支持某种格式
    ioctl(4, VIDIOC_S_FMT                                           // 设置摄像头使用某种格式
	ioctl(4, VIDIOC_REQBUFS                                         // 请求系统分配缓冲区
	for()
		ioctl(4, VIDIOC_QUERYBUF                                    // 查询所分配的缓冲区
		mmap
	
	for()
		ioctl(4, VIDIOC_QBUF                                        // 把缓冲区放入队列
	ioctl(4, VIDIOC_STREAMON                                        // 启动摄像头

	for()
		ioctl(4, VIDIOC_S_CTRL                                      // 设置属性

	ioctl(4, VIDIOC_S_INPUT                                         // 设置输入源
	ioctl(4, VIDIOC_S_STD                                           // 设置标准制式

	select(5, 
		ioctl(4, VIDIOC_DQBUF                                       // 把缓冲区从队列中取出
		ioctl(4, VIDIOC_QBUF                                        // 把缓冲区入队列
	
	ioctl(4, VIDIOC_STREAMOFF                                       // 关闭摄像头

### 精简vivi.c驱动，筛选出必要的ioctl,如下11个
	static const struct v4l2_ioctl_ops vivi_ioctl_ops = {
		.vidioc_querycap      = vidioc_querycap,

		.vidioc_enum_fmt_vid_cap  = vidioc_enum_fmt_vid_cap,
		.vidioc_g_fmt_vid_cap     = vidioc_g_fmt_vid_cap,
		.vidioc_try_fmt_vid_cap   = vidioc_try_fmt_vid_cap,
		.vidioc_s_fmt_vid_cap     = vidioc_s_fmt_vid_cap,

		.vidioc_reqbufs       = vidioc_reqbufs,
		.vidioc_querybuf      = vidioc_querybuf,
		.vidioc_qbuf          = vidioc_qbuf,
		.vidioc_dqbuf         = vidioc_dqbuf,

		.vidioc_streamon      = vidioc_streamon,
		.vidioc_streamoff     = vidioc_streamoff,
	};
	

### 分析vivi.c这个驱动，并总结获取数据的过程
	vidioc_querycap
		cap->device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING | V4L2_CAP_READWRITE;   // 设置设备的属性

	vidioc_enum_fmt_vid_cap   // 设置数据的格式
		formats              
		strlcpy(f->description, fmt->name, sizeof(f->description));

	vidioc_g_fmt_vid_cap      // 列举支持的格式

	vidioc_try_fmt_vid_cap    // 测试数据的格式
		get_format

	vidioc_s_fmt_vid_cap      // 设置数据的格式

	vidioc_reqbufs            // 分配缓冲区
		__vb2_queue_free      // 释放buffer
		
	vidioc_querybuf           // 查询缓冲区的信息
		    
		


	struct vb2_queue	   vb_vidq;

	struct v4l2_requestbuffers
	{
		__u32	                count;
		enum v4l2_buf_type      type;
		enum v4l2_memory        memory;
		__u32	                reserved[2];
	};



	static struct vivi_fmt formats[] = {
		{
			.name     = "4:2:2, packed, YUYV",
			.fourcc   = V4L2_PIX_FMT_YUYV,
			.depth    = 16,
		},
		{
			.name     = "4:2:2, packed, UYVY",
			.fourcc   = V4L2_PIX_FMT_UYVY,
			.depth    = 16,
		},
		{
			.name     = "RGB565 (LE)",
			.fourcc   = V4L2_PIX_FMT_RGB565, /* gggbbbbb rrrrrggg */
			.depth    = 16,
		},
		{
			.name     = "RGB565 (BE)",
			.fourcc   = V4L2_PIX_FMT_RGB565X, /* rrrrrggg gggbbbbb */
			.depth    = 16,
		},
		{
			.name     = "RGB555 (LE)",
			.fourcc   = V4L2_PIX_FMT_RGB555, /* gggbbbbb arrrrrgg */
			.depth    = 16,
		},
		{
			.name     = "RGB555 (BE)",
			.fourcc   = V4L2_PIX_FMT_RGB555X, /* arrrrrgg gggbbbbb */
			.depth    = 16,
		},
	};
