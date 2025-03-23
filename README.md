# DS-OS
An ordinary Operating System for ARM-CONTEX-A7,which imitate xv6(OS from MIT)

# 相关链接
[中文翻译](https://th0ar.gitbooks.io/xv6-chinese/content/)
[原项目](https://github.com/Xv64/OS.git)

# 内容
## bootloader  
### 内容
将操作系统装载进内存，并进行一系列初始化
1. 加载中断向量表，为后续进程切换提供跳转地址
2. 设置栈防止初始化的栈覆盖掉其他位置
## 内存映射
- 手动实现第一进程的内容映射
![](./image/first.png)
1. 手动构建二级页表，并将页表首地址放在专门的寄存器内，开启虚拟页表形式
2. 将内存二级页表最小单位进行分割，并用结构体以链表的形式进行保存，用于进程请求时的回收和分配。
3. 新进程构建是，要为每个进程分配一个页表



## 进程切换

![](./image/schedule.png)
- 开启中断，利用时钟中断，实现进行切换(包括保存和恢复寄存器，切换二级页表，切换进程描述符)

- 进程创建，构建上下文(分配栈，构建页表，指定程序运行pc地址)
