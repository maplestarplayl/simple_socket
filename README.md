# 使用C和Cython实现了一个简易的对话软件（其实就是socket+GUI）
## v3 & v3.5
### 新增特性
#### 1.能够通过GUI进行交互（Server端）(Remember to press the connect Button)
## v2
### 新增特性
#### 1.能够实现两个ip间的通信
#### 2.可以持久对话（但必须彼此轮流）
## 目前存在的问题（ToDo)
### 1.仅能在本地运行(已解决 v2)
目前因为ip地址是写死的（localhost）所以仅能在本地传输数据，之所以这样是因为我还没深入看一些函数的内部实现，不太敢直接用
等我看完了（或者chatGPT解决了）我就再改改
### 2.无法持续对话（已解决 v2)
### 3.对TCP/Socket整体流程尚未理解透彻
该项目都是参考网络上的实现写的，让我自己只看流程图写我也写不出来，所以打算再看看为什么这样设计
### 4.缺乏GUI（仅剩Client端）
### 5.只能在Linux环境下运行
### 6.会出现Buffer Overflow现象

## 参考资料
https://www.geeksforgeeks.org/socket-programming-cc/
https://gist.github.com/browny/5211329
https://hansimov.gitbook.io/csapp/part3/ch11-network-programming/11.4-the-sockets-interface
