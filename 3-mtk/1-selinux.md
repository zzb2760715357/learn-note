### Selinux的完整结构图
![Selinux的完整结构图](https://i.imgur.com/5Rn4rrY.png)

### 基本的访问流程
![基本的访问流程](https://i.imgur.com/cPqqrSZ.png)

### Selinux Mode主要分成两种permissive、enforce模式
	1、Permissive Mode 只通过Audit System 记录LOG, 但不真正拦截访问.
   	2、Enforcing Mode 在打印LOG 的同时，还会真正的拦截访问.

### 查看Security Context
	1、查看进程的Security Context:ps -Z 
	2、查看文件的Security Context:ls -Z

### 创建一个selinux demo
	▪情景:  定义一个init 启动的service, demo_service, 对应的执行档是/system/bin/demo.
	▪(1).  创建一个demo.te 在/device/mediatke/common/sepolicy 目录下, 然后在/device/mediatke/common/BoardConfig.mk 的BOARD_SEPOLICY_UNION 宏中新增 demo.te
	▪(2).  定义demo 类型，init 启动service 时类型转换, demo.te 中
	•type  demo, domain;
	•type  demo_exec, exec_type, file_type;
	•init_daemon_domain(demo)
	▪(3).  绑定执行档 file_contexts 类型
	•/system/bin/demo  u:object_r:demo_exec:s0
	▪(4). 根据demo 需要访问的文件以及设备,  定义其它的权限在demo.te 中.

	▪情景:  一个native service demo, 需要设置一个自定义的system property,  demo.setting.case1.
	▪(1).  定义system property类型. 在property.te
	•type demo_prop, property_type;
	▪(2).  绑定system property 类型.  在property_contexts
	•demo.        u:object_r:demo_prop:s0
	▪(3). 在demo.te 中新增
	•   unix_socket_connect(demo,property,init);
	•   allow demo demo_prop:property_service set;
