### 第一章 简介和概述
1、unix操作系统中有两种创建新进程的机制  

1.1 fork可以创建当前进程的一个副本，父进程和子进程只有PID不同  

1.2 exec将一个新程序加载到当前的内存中并执行    

1.3 内存区域是通过指针寻址的，因此CPU的字长决定了所能管理的地址空间的最大长度    

1.4 虚拟地址空间：地址空间的最大长度与实际可用的物理内存数量无关，因此被称为虚拟地址空间.虚拟地址分成两部分：内核空间（TASK_SIZE-2^32）和用户空间(0-TASK_SIZE)    

1.5 Linux只使用两种不同的状态，核心态和用户态。    

1.6 页表:用来将虚拟地址空间映射到物理地址空间的数据结构称为页表。    

1.7 Linux内核采用四级页表,虚拟地址：PGD+PMD+PTE+offset,全局页表、中间页表、页表、页帧  
页帧：物理内存页经常称作页帧。  
页：则专指虚拟地址空间中的页。  
PGD:用于索引进程中的一个数组。  
PTE:虚拟内存页和页帧之间的映射。  
offset:指定页内部的一个字节位置.  
优点：对虚拟地址空间中不需要的区域，不必创建中间页目录或页表。  
缺点：每次访问内存时，必须逐级访问多个数组才能将虚拟地址转换为物理地址。CPU中有一个专门的部分称为MMU,优化内存的访问操作。地址转换中出现最频繁的那些地址保存在TLB中。

1.8 物理内存的分配  
伙伴系统:作用快速检测内存中连续的区域。内核对所有大小相同的伙伴，都放置到同一个列表中管理。 在应用程序释放内存时，内核可以直接检查地址，来判断是否能够创建一组伙伴，并合并为一个更大的内存块放到伙伴列表中。   
伙伴系统分配的流程图大致如下:    
![伙伴系统](https://github.com/zzb2760715357/Picture/blob/master/1-Dive_into_the_Linux_kernel_architecture/1-chapter/1.jpg)  

1.9 slab缓存  
内核本身经常需要比完整页帧小的多的内存块。因此必须在伙伴系统基础上自行定义额外的内存管理，将伙伴系统提供的页划分为更小的部分。  
伙伴系统、slab分配器以及内核其他方面之间的联系如下:  
![关系图](https://github.com/zzb2760715357/Picture/blob/master/1-Dive_into_the_Linux_kernel_architecture/1-chapter/2.jpg)  

2.0 页面交换
页面交换通过利用磁盘空间作为扩展内存，从而增大了可用的内存。在内核需要更多内存时，不经常使用的页可以写入硬盘。如果在需要访问相关数据，内核会将相应的页切换回内存（缺页异常）。  

2.1 文件系统  
Ext2基于inode,它对每个文件都构造了一个单独的管理结构，称为inode,并存储到磁盘上，inode包含了文件所有的元信息，以及指向相关数据块的指针。目录可以表示为普通文件，其数据包含了指向目录下所有文件的inode的指针，因而层次结构得以建立。  

VFS:虚拟文件系统，将各种底层文件系统的具体特性与应用层隔离开来。  
![虚拟文件系统层、文件系统实现和块设备层之间的互操作](https://github.com/zzb2760715357/Picture/blob/master/1-Dive_into_the_Linux_kernel_architecture/1-chapter/3.jpg)  

2.2 内核链表  
内核提供的标准链表可用于将任何类型的数据结构彼此链接起来，加入链表的数据结构必须包含一个类型为list_head的成员。     
```c
List.h 
struct list_head {
  struct list_head *next, *prev;
};
包含类型为list_head的成员  
struct task_struct{
  ...
  struct list_head run_list;
  ...
}
```
使用LIST_HEAD宏来声明并初始化。  
标准内核双向链表结构图如下:  
![标准双链表](https://github.com/zzb2760715357/Picture/blob/master/1-Dive_into_the_Linux_kernel_architecture/1-chapter/4.jpg)  
查找链表元素必须使用list_entry(ptr, type,member) ，ptr指向数据结构中list_head成员实例的一个指针，type是该数据结构的类型，而member则是数据结构中表示链表元素的成员名。  
如果在链表中查找task_struct的实例，则需要下列示例调用：
```c
struct task_struct = list_entry(ptr, struct task_struct,run_list)。
```  

2.3 对象管理和引用对象  
kobject:对象管理  
kset:对象管理集合  
kobj_type:给结构体提供了与sysfs文件系统的接口。  
kref:引用计数  

2.4 字节序  
大端序：最高有效字节存储在最低地址。  
小端序：最低有效字节存储在最低地址。 
cpu_to_le64将64位数据类型转换为小端序格式，le64_to_cpu所做的刚好相反。
![字节序](https://github.com/zzb2760715357/Picture/blob/master/1-Dive_into_the_Linux_kernel_architecture/1-chapter/5.jpg)  









