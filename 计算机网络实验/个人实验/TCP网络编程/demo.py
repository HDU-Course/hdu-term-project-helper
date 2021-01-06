# -*- coding: utf-8 -*-
# @Author: TD21forever
# @Date:   2019-11-24 00:57:57
# @Last Modified by:   TD21forever
# @Last Modified time: 2019-11-24 01:12:12
from socket import *
'''
服务器
'''
# AF_INET 采用ipv4的tcp或udp通信机制
# SOCK_STREAM代表tcp通信
sockobj = socket(AF_INET, SOCK_STREAM)
socket.bind(())
sockobj.listen(max_client)
# 返回一个套接字(通路)，客户端ip和端口
connection, address = sockobj.accept()
# 从客户端发送或者接受数据
connection.send()
data = connection.recv()
# 关闭
connection.close()
sockobj.close()
'''
客户端
'''
sockobj.connect()
sockobj.recv()
sockobj.send()
