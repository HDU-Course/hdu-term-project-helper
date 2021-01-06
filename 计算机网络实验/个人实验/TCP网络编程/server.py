# -*- coding: utf-8 -*-
# @Author: TD21forever
# @Date:   2019-11-24 01:12:39
# @Last Modified by:   TD21forever
# @Last Modified time: 2019-11-24 15:40:39
from socket import *
import threading


def stoc(client_socket, addr):
    while True:
        try:
            client_socket.settimeout(500)
            buf = client_socket.recv(1024)
            print("*" * 10)
            print("msg from:", addr[1])
            print("msg:", buf.decode('utf-8'))
            print("*" * 10)
        except socket.timeout:
            print("Time Out")
            break


#""表示localhost
myHost = ""
myPort = 50007
# 设置一个TCP socket对象
server = socket(AF_INET, SOCK_STREAM)
# 绑定端口号
server.bind((myHost, myPort))
# 监听，允许5个连结
server.listen(5)
while True:
        # 等待客户端连接
    client, address = server.accept()
    print("Server conneted by", address)
    thread = threading.Thread(target=stoc, args=(client, address))
    thread.start()
