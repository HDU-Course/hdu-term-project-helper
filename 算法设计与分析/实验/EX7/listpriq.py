# -*- coding: utf-8 -*-
# @Author: TD21forever
# @Date:   2019-06-04 18:41:25
# @Last Modified by:   TD21forever
# @Last Modified time: 2019-06-16 12:40:44

'''
用列表实现优先队列
左大 右小
'''

class ListPriQueue:
	def __init__(self):
		self.items = []
	def enqueue(self,item):
		i = 0
		while i < len(self.items):
			if item > self.items[i]:
				break            
			else:
				i+=1
		self.items.insert(i,item)

	def dequeue(self):
		return self.items.pop()
	def isEmpty(self):
		return self.items == []
	def size(self):
		return len(self.items)
	def buildPriQueue(self,alist):
		self.items = alist.copy()
		self.items.sort(reverse=True)
if __name__ == '__main__':
	q = ListPriQueue()
	q.buildPriQueue([5,21,1,4])
	print(q.dequeue())
	print(q.dequeue())
	print(q.dequeue())
	print(q.dequeue())
	

	