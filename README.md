## 使用C实现了一个简易的socket（其实就是调用<sys/socket.h>的函数）
## 目前存在的问题（ToDo)
### 1.仅能在本地运行
目前因为ip地址是写死的（localhost）所以仅能在本地传输数据，之所以这样是因为我还没深入看一些函数的内部实现，不太敢直接用
等我看完了（或者chatGPT解决了）我就再改改
### 2.对TCP/Socket整体流程尚未理解透彻
该项目都是参考网络上的实现写的，让我自己只看流程图写我也写不出来，所以打算再看看为什么这样设计

## 参考资料
https://www.geeksforgeeks.org/socket-programming-cc/
https://gist.github.com/browny/5211329
https://hansimov.gitbook.io/csapp/part3/ch11-network-programming/11.4-the-sockets-interface
