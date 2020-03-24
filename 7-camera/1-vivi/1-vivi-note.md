# vivi.c驱动分析
### 本实验的最终目的是找出vivi.c中关键的接口，去掉一些不必要的接口
### 1、 xawtv.log 这分log是使用strace -o xawtv.log xawtv这样播放摄像头抓取的log，我们根据这份log分析xawtv打开vivi驱动的调用流程
### 2、 xawtv涉及的vivi驱动的系统调用.txt  这份log是从xawtv.log中筛选出跟vivi驱动相关的系统调用.
### 3、 xawtv的主要代码drv0-v4l2.c
### camera相关不错的文档
	https://www.cnblogs.com/emouse/archive/2013/03/04/2943243.html

### 调用的过程
	open("/dev/video0"                                          // 打开camera
	ioctl(4, VIDIOC_QUERYCAP                                    // 查询设备的属性  
	ioctl(4, VIDIOC_G_FMT                                       // 列举输入源
	for() 
		ioctl(4, VIDIOC_ENUM_FMT                                // 查询并显示支持的格式                                              
	
	ioctl(4, VIDIOC_QUERYCAP
	ioctl(4, VIDIOC_G_INPUT,
	ioctl(4, VIDIOC_ENUMINPUT,
	ioctl(4, VIDIOC_QUERYCAP
	fcntl64(4, F_SETFD,
	ioctl(4, VIDIOC_ENUMINPUT,
	ioctl(4, VIDIOC_ENUMINPUT,
	ioctl(4, VIDIOC_ENUMINPUT,
	ioctl(4, VIDIOC_ENUMINPUT,
	ioctl(4, VIDIOC_ENUMSTD,
	ioctl(4, VIDIOC_ENUMSTD,
	ioctl(4, VIDIOC_ENUMSTD,
	ioctl(4, VIDIOC_ENUMSTD,
	ioctl(4, VIDIOC_ENUMSTD,
	ioctl(4, VIDIOC_ENUMSTD,
	ioctl(4, VIDIOC_ENUMSTD,
	ioctl(4, VIDIOC_ENUM_FMT
	ioctl(4, VIDIOC_ENUM_FMT
	ioctl(4, VIDIOC_ENUM_FMT
	ioctl(4, VIDIOC_ENUM_FMT
	ioctl(4, VIDIOC_ENUM_FMT
	ioctl(4, VIDIOC_G_PARM,
	ioctl(4, MATROXFB_TVOQUERYCTRL
	ioctl(4, MATROXFB_TVOQUERYCTRL
	ioctl(4, MATROXFB_TVOQUERYCTRL
	ioctl(4, MATROXFB_TVOQUERYCTRL
	ioctl(4, MATROXFB_TVOQUERYCTRL
	ioctl(4, VIDIOC_G_STD,
	ioctl(4, VIDIOC_G_INPUT,