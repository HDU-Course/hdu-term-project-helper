# -*- coding: utf-8 -*-
# @Author: TD21forever
# @Date:   2019-04-10 00:04:32
# @Last Modified by:   TD21forever
# @Last Modified time: 2019-04-12 23:09:24

'''
求树的层数
分治算法
1.求左子树的层数
2.求右子树的层数
3.树的层数 = max(左右子树)+1

T(n) = 2T(n/2) ====> T(n) = O(logn)

'''
class BinaryTree:
	def __init__(self,rootObj):
		self.root = rootObj
		self.leftChild = None
		self.rightChild = None
	def insertLeft(self,newNode):
		if self.leftChild == None:
			self.leftChild = BinaryTree(newNode)
		else:
			t = BinaryTree(newNode)
			t.leftChild = self.leftChild
			self.leftChild = t
	def insertRight(self,newNode):
		if self.rightChild == None:
			self.rightChild = BinaryTree(newNode)
		else:
			t = BinaryTree(newNode)
			t.rightChild = self.rightChild
			self.rightChild = t
	def getRightChild(self):
		return self.rightChild
	def getLeftChild(self):
		return self.leftChild
	def setRootVal(self,obj):
		self.root = obj
	def getRootVal(self):
		return self.root

def preorder(tree):
	if tree:
		print(tree.getRootVal())
		preorder(tree.getLeftChild())
		preorder(tree.getRightChild())

#------------------------------------测试---------------
tree = BinaryTree('a')
tree.insertLeft('b')
tree.insertRight('c')
tree.getLeftChild().insertLeft('d')
tree.getLeftChild().insertRight('e')
tree.getRightChild().insertLeft('f')
tree.getLeftChild().getRightChild().insertLeft('G')

def getNumLevel(tree):
	num = 0
	if tree:
		num = 1+max(getNumLevel(tree.getLeftChild()),getNumLevel(tree.getRightChild()))
	else:
		return 0
	return num	

print(getNumLevel(tree))#4
'''
		a
	   / \
	  b   c
	 / \
	d   f
	   /
	  G
测试用例为上图，层数为4
'''
