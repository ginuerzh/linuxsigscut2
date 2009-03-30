文件结构：
main.h：存放一些还未归类的函数、结构体声明；

main.c：主程序；

ipmsg.h：存放飞鸽协议的一些宏定义

userUtils.h：存放跟用户相关的函数、结构体声明，例如创建用户列表……

userUtils.c：实现userUtils.h声明的函数

messageUtils.h：存放跟消息相关的函数、结构体声明，例如创建消息列表……

messageUtils.c：实现messageUtils.h声明的函数

注：消息不是IPMSG数据包，消息是用来存放IPMSG数据包的各个字段

ipmsg_protocol.h和ipmsg_protocol.c暂时未使用

暂时只实现了以下几点：
（1）运行程序时创建用户列表、消息列表，广播登录消息
（2）创建接收UDP数据包的线程：接收UDP数据包，分析数据包，生成消息并挂到消息列表
（3）创建处理消息的线程：从消息列表获取第一条消息，还未实现消息处理

编译命令：gcc -o main userUtils.c messageUtils.c  main.c -lpthread
执行命令：./main



