# -*- coding: utf-8 -*-
# @Author: TD21forever
# @Date:   2019-06-04 11:20:26
# @Last Modified by:   TD21forever
# @Last Modified time: 2019-06-04 22:34:41
'''
实现最小堆
'''

class BinHeap:
	def __init__(self):
		self.heapList = [0]#这样下标可以从1开始 
		self.currentSize = 0#加入一个数后 当前的index变为1
	def percUp(self,index):#自下而上地调整 用于加入数据时
		while index //2 > 0:#为什么是//2>0？ 因为1这个位置是树根
			if self.heapList[index] < self.heapList[index//2]: #儿子小于爸爸
				self.heapList[index],self.heapList[index//2] = self.heapList[index//2],self.heapList[index]
			index //=2 	
	def insert(self,value):
		self.heapList.append(value)
		self.currentSize += 1
		percUp(self.currentSize)
	def percDown(self,index):#自上而下调整
		while index *2 < self.currentSize:
			mc= self.minChild(index)
			if self.heapList[index] > self.heapList[mc]:#如果发现爸爸比儿子大
				self.heapList[index],self.heapList[mc] = self.heapList[mc], self.heapList[index]
			index *= 2	
	#找到两个儿子节点中 较小的拿一个
	def minChild(self,index):
		if index*2+1 > self.currentSize:
			return index*2
		else:
			return index*2 if self.heapList[index*2] < self.heapList[index*2+1] else index*2+1 #找到小儿子
	def delMin(self):
		res = self.heapList[1]
		#第一个和最后一个值作交换
		self.heapList[1] = self.heapList[self.currentSize]

		#减少一个数
		self.currentSize -= 1
		self.heapList.pop()
		#因为现在根节点变了 从上到下调整根节点的位置
		self.percDown(1)
		return res
	def buildHeap(self,alist):
		#为什么从长度的一半开始？ 因为堆是一个完整的二叉树，超过中途点的任何节点都将是树叶， 因此没有子节点。
		i = len(alist)//2
		self.currentSize = len(alist)
		self.heapList = [0]+alist[:]
		while i>0 :
			self.percDown(i)
			i = i-1

if __name__ == '__main__':

	bh = BinHeap()

	bh.buildHeap([9,5,6,2,3])
	print(bh.delMin())
	print(bh.delMin())
	print(bh.delMin())
	print(bh.delMin())
	print(bh.delMin())


	


