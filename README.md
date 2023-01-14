# CGraph-NIO
基于CGraph和workflow，实现网络通信的功能

## 编译说明

* 本人在mac-m1机器上开发，并且本地已经安装openssl
* 在下载本例前，请确保本地已经安装 workflow
```
$ git clone --recursive git@github.com:CDevOrg/CGraph-NIO.git
```
* 通过CLion打开CGraph-NIO同级的CMakeList.txt文件，即设置`OPENSSL_ROOT_DIR`为本机openssl安装位置，即可编译通过。
