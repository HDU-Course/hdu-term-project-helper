# -*- coding: utf-8 -*-
# @Author: TD21forever
# @Date:   2019-11-24 18:12:41
# @Last Modified by:   TD21forever
# @Last Modified time: 2019-11-24 19:07:50
from socket import *
from time import ctime, sleep
host = "localhost"
port = 50007
addr = (host, port)
client = socket(AF_INET, SOCK_DGRAM)
while True:
    msg = input("输入要发送的消息:")
    print("正在发送...")
    sleep(1)
    client.sendto(msg.encode(), addr)
    print("发送成功")
    data, address = client.recvfrom(1024)
    print("Server: ", data.decode())
    print("*" * 20)
client.close()
