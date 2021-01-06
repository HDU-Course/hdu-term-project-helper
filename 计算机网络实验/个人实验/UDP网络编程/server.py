# -*- coding: utf-8 -*-
# @Author: TD21forever
# @Date:   2019-11-24 18:01:52
# @Last Modified by:   TD21forever
# @Last Modified time: 2019-11-24 18:33:09
from socket import *
from time import sleep, ctime
host = ""
port = 50007
addr = (host, port)
server = socket(AF_INET, SOCK_DGRAM)
server.bind(addr)
print("服务器建立成功")
while True:
    data, address = server.recvfrom(1024)
    print("从{}中获得数据{}".format(address, data.decode()))
    server.sendto("Got it!".encode(), address)
    print("*" * 20)
