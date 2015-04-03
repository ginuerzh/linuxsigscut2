# Introduction #
原文链接：http://bbs.chinaunix.net/viewthread.php?tid=1015775
转载请注明作者名及原文出处

<pre>
最近看到一些朋友在编写网络程序是遇到一些问题，故把以前做IPMSG时翻译的文档贴过来，希望对网络编程新手有所帮助，在寻找编程项目的同学们也可参照此文档写出自己的IPMSG。<br>
<br>
本文只包含其中几个比较重要的命令以及运行机制的中文翻译，更详细的内容请参照文后的IPMSG 协议英文文档<br>
<br>
声明：下述协议内容略去了一些在编写程序过程中没有用到协议内容，最初的Ipmsg协议是用日文写的，下面协议内容由本人(cugb_cat)翻译自Mr.Kanazawa的英文文档。本翻译文档可任意传播和使用。<br>
<br>
IP信使传输协议(第9版草案)         1996/02/21<br>
2003/01/14 修订<br>
<br>
H.Shirouzu<br>
[email]shirouzu@h.email.ne.jp[/email]<br>
</pre>


# Details #

<pre>
关于IP信使：<br>
IP信使使用TCP/UDP协议提供收发消息及文件(目录)。<br>
特性：<br>
IP信使能够安装在任何一个安装了TCP/IP协议栈的操作系统上，使用在线用户的动态识别机制，可以和在线所有用户进行信息交换。<br>
运行机制介绍：<br>
使用TCP/UDP端口(默认端口为2425)，消息的收发使用UDP协议，文件(文件夹)的收发使用TCP协议。<br>
1、   命令字：<br>
1)   基本命令字(32位命令字的低8位)<br>
IPMSG_NOOPERATION     不进行任何操作<br>
IPMSG_BR_ENTRY     用户上线<br>
IPMSG_BR_EXIT         用户退出<br>
IPMSG_ANSENTRY     通报在线<br>
IPMSG_SENDMSG         发送消息<br>
IPMSG_RECVMSG         通报收到消息<br>
IPMSG_GETFILEDATA     请求通过TCP传输文件<br>
IPMSG_RELEASEFILES   停止接收文件<br>
IPMSG_GETDIRFILES     请求传输文件夹<br>
2)   选项位(32位命令字的高24位)<br>
IPMSG_SENDCHECKOPT   传送检查(需要对方返回确认信息)<br>
IPMSG_FILEATTACHOPT   传送文件选项<br>
3)   附件类型命令(文件类型命令字的低8位)<br>
IPMSG_FILE_REGULAR   普通文件<br>
IPMSG_FILE_DIR     目录文件<br>
IPMSG_FILE_RETPARENT   返回上一级目录<br>
2、   数据包格式(使用字符串)：<br>
1)   数据包格式(版本1的格式)<br>
版本号(1):包编号:发送者姓名:发送者主机名:命令字:附加信息<br>
2)   举例如下<br>
“1:100:shirouzu:Jupiter:32:Hello”<br>
3、   数据包处理总述：<br>
1)   用户识别<br>
当IPMSG 启动时，命令IPMSG_BR_ENTRY被广播到网络中，向所有在线的用户提示一个新用户的到达(即表示“我来了”)；所有在线用户将把该新上线用户添加到自己的用户列表中，并向该新上线用户发送IPMSG_ANSENTRY命令(即表示“我在线”)；该新上线用户接收到 IPMSG_ANSENTRY命令后即将在线用户添加到自己的用户列表中。<br>
2)   收发消息<br>
使用IPMSG_SENDMSG命令发送消息，消息内容添加在附加信息中；在接收消息时，如果对方要求回信确认(IPMSG_SENDCHECKOPT位打开)，则需发送IPMSG_RECVMSG命令并将对方发送的数据包的编号放在附加信息中一同发送至发送消息方<br>
3)   附加文件的扩充(添加于第9版)<br>
带有IPMSG_FILEATTACHOPT位的IPMSG_SENDMSG命令可用来传输文件，文件属性及内容添加在附加信息中，文件内容添加在消息内容后并以’\0’与之分隔开。传输文件时以下信息将被添加到消息内容之后(包括格式)：文件序号:文件名:大小(单位:字节):最后修改时间:文件属性[: 附加属性=val1[,val2…][:附加信息=…]]:\a:文件序号…<br>
(文件大小、最后修改时间和文件属性为十六进制数，如果文件名中包含’:’则使用“::”代替)。<br>
接收端开始接收文件时，请求传输文件命令IPMSG_GETFILEDATA将发送到发送端的TCP端口(和UDP的发送端口相同)，并将发送端发送的包编号:文件序号:偏移量(全为十六进制格式)写到附加信息区一同发送，文件发送端接收到该请求信息并进行校验正确后即开始发送文件(不使用任何格式，亦不进行加密)。<br>
当接收端接收到目录文件时，将发送附加信息区为发送端发送的包编号:文件序号:偏移量(全为十六进制格式) 的 IPMSG_GETDIRFILES命令，以用来请求传输目录文件；发送端则将头信息长度:文件名:文件大小:文件属性:文件内容添加到附加信息区 (除了文件名和文件内容外，其余皆为十六进制)，头信息长度是从头信息长度开始到文件内容前的‘:’分割符为止的字符个数。<br>
当文件属性为IPMSG_FILE_DIR时，IPMsg能够自动识别其为目录，下一个文件的数据在该目录之后。<br>
当文件属性为IPMSG_FILE_RETPARENT时，IPMsg识别其动作为返回上一级目录，在这种情况下，文件名为‘.’其属性为当前目录的值。<br>
</pre>