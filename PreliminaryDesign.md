# The Structure #
![http://linuxsigscut2.googlecode.com/svn/wiki/designStructrue.png](http://linuxsigscut2.googlecode.com/svn/wiki/designStructrue.png)

# Details #
  * user interface
> > 用来处理与用户的交互，可以为(GUI或CML)。接受用户的操作命令，并转化为Ipmsg protocol需要的数据，由Ipmsg protocol执行；显示来自的Ipmsg protocol的消息；显示member list。

  * member list
> > 管理在线用户的所有信息，包括user name, host name, ip等。提供添加，删除，查询等接口给其它模块使用。

  * Ipmsg protocol
> > 实现协议的模块。例如在收到来自user interface的发送消息命令时，应该生成什么样的数据；对收到来自其它主机的数据时进行解释。还要实现对member list的管理。

  * Packager
> > 把Ipmsg protocol传递过来的数据打包成ip包，然后发送。

  * Unpackager
> > 与Packager做相反的动作。