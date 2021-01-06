# -*- coding: utf-8 -*-
# @Author: TD21forever
# @Date:   2019-06-06 21:31:25
# @Last Modified by:   TD21forever
# @Last Modified time: 2019-06-07 01:56:13
class Stack:
    def __init__(self):
        self.items = []

    def isEmpty(self):
        return self.items == []

    def push(self, item):
        self.items.append(item)

    def pop(self):
        return self.items.pop()

    def peek(self):
        return self.items[len(self.items)-1]

    def size(self):
        return len(self.items)
    def show(self):
    	return "".join(self.items[::-1])
