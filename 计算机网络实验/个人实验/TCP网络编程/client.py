# -*- coding: utf-8 -*-
# @Author: TD21forever
# @Date:   2019-11-24 01:16:56
# @Last Modified by:   TD21forever
# @Last Modified time: 2019-11-24 15:32:46
from socket import *
from time import sleep
serverHost = 'localhost'
serverPort = 50007
# 建立一个tcp/ip套接字对象
client = socket(AF_INET, SOCK_STREAM)
# 连接至服务器及端口
print("正在连接服务器")
sleep(1)
client.connect((serverHost, serverPort))
print("连接成功")

message = input("请输入想发送的消息：")
client.send(message.encode('utf-8'))
print("Client sent:", message)
# 从服务端接收到的数据，上限为1k
data = client.recv(1024)
print('Client received:', data.decode('utf-8'))
client.close()
