# 1、用例图 #
http://linuxsigscut2.googlecode.com/svn/wiki/user_case.JPG
# 说明 #
> 用户可通过在控制台（或UI）输入命令进行操作。



# 2、主程序活动图 #
http://linuxsigscut2.googlecode.com/svn/wiki/main.JPG
# 说明 #
（1）主程序启动后，首先进行初始化，例如用户列表、消息列表、socket对象等的初始化；
（2）然后创建各线程，例如接收UDP数据包的线程、处理UDP数据包的线程、定时器线程（定时做一些操作，例如清除垃圾、反馈信息给用户等）、接受TCP连接的线程（用来处理传送文件的请求）等；
（3）登录用户时，需要广播加入消息；
（4）最后主进程处理用户的输入命令，并即时反馈信息给用户。需要特别说明的两个命令：
> 接收文件命令：主进程显示待接收文件列表（处理UDP数据包的线程再接收到文件传输命令后，将待接收文件的相关信息保存到此列表中），用户进一步选择要接收的文件。最后创建一个线程与发送端连接（TCP）并接收文件。
> 退出命令：主进程设置退出信号（可以是一个全局变量）。各子线程将在下一个循环周期判断退出信号被设置，并退出。



# 3、接收UDP数据包线程的活动图 #
http://linuxsigscut2.googlecode.com/svn/wiki/recvUDP.JPG
# 说明 #
> 为了防止UDP数据包过多而来不及接收，此线程只是用来接收UDP数据包，并做一些简单的分析处理，然后将结果存放到一个消息列表中，待UDP数据包处理线程做进一步分析处理。



# 4、处理UDP数据包线程的活动图 #
http://linuxsigscut2.googlecode.com/svn/wiki/dealUDP.JPG
# 说明 #
> 如上所述，此线程从消息队列中取出消息，并做相应的处理。



# 5、接受TCP连接请求线程的活动图 #
http://linuxsigscut2.googlecode.com/svn/wiki/recvTCP.JPG
# 说明 #
> 如果有接收端请求连接本发送端的TCP socket，接受连接。然后创建一个发送文件的线程（一个发送端的TCP socket对应多个接收的TCP socket）。