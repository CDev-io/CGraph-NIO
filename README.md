# CGraph-NIO
基于CGraph和workflow，实现网络通信的功能

## 编译说明

* 本人在mac-m1机器上开发，并且本地已经安装openssl，安装路径为`/opt/homebrew/opt/openssl`，下方设置需要用到。
* 首先，按照如下方式，编译workflow，并且生成对应库文件。
```
$ git clone --recursive git@github.com:CDevOrg/CGraph-NIO.git
$ cd 3rd-party/workflow/
$ cmake -DOPENSSL_ROOT_DIR=/opt/homebrew/opt/openssl -DOPENSSL_LIBRARIES=/opt/homebrew/opt/openssl/lib    # 根据实际情况，设置这两个值
$ make    # 生成对应的_lib文件夹和_include文件夹
```
* 通过CLion打开CGraph-NIO同级的CMakeList.txt文件，即设置`OPENSSL_ROOT_DIR`为本机openssl安装位置，即可编译通过。

