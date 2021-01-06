# -*- coding: utf-8 -*-
# @Author: TD21forever
# @Date:   2019-06-08 11:47:21
# @Last Modified by:   TD21forever
# @Last Modified time: 2019-06-15 14:17:13
import collections

tblptr = []
offset = []


class stitem:
	'''
	符号表的表项
	'''

	def __init__(self, name, typename, offset):
		self.name = name
		self.typename = typename
		self.offset = offset
	def __str__(self):
		return "{} {} {}".format(self.name,self.typename,self.offset)



def enter(table, name, typename, offset):
	'''
	在table指向的符号表中为名字name建立新表项，同时将类型type及相对地址offset放入该表项的属性域中。
	'''
	item = stitem(name, typename, offset)
	table.push(item)



class tbl:
	'''
	符号表
	'''
	tbl = collections.OrderedDict()  # 有序字典

	def __init__(self, width=None):
		self.width = width

	def pop(self):  # 栈的pop操作
		popitem = self.tbl.popitem()
		return popitem

	def push(self, item):  # 栈的push操作
		self.tbl[item.name] = item
	def addTable(self,key,value):
		self.tbl[key] = value

	def show(self):
		return self.tbl
	# def __str__(self):
	# 	return self.tbl


def mktable():
	'''
	创建一张新的符号表，并返回指向新表的指针。参数previous指向先前创建的符号，放在新符号表的表头。
	'''
	table = tbl()

	return table




class ID:
	def __init__(self,name,state):
		self.name = name
		self.state = state
class T:
	def __init__(self,type_=None,name=None,width=None,state=None):
		self.type_ = type_
		self. width = width 		
		self.state = state

def addwidth(table, width):
	'''
	将table指向的符号表中所有表项的宽度之和记录在与符号表关联的表头中。
	'''
	table.width = width


def enterproc(table, name, newtable):
	'''
	在table指向的符号表中为过程name建立一个新表项，参数newtable指向过程name的符号表。
	'''
	table.addTable(name,newtable)
	return table

def testOne():

	T1 = T(name="T1",state=1)
	id1 = ID(name="id1",state=1)
	t1 = mktable()
	tblptr.append(t1)
	offset.append(0)
	T1.type_ = 'real'
	T1.width = 8

	enter(tblptr[-1],id1.name,T1.type_,offset[-1])
	offset[-1] = offset[-1] + T1.width
	# print(offset)

	T3 = T(name="T3",state=3)
	T3.type_ = "integer"
	T3.width = 4

	T2 = T(name="T2",state=2)
	T2.type_="ptr "+str(T3.type_)
	T2.width = 4

	id2 = ID("id2",2)

	enter(tblptr[-1],id2.name,T2.type_,offset[-1])
	offset[-1] = offset[-1] + T2.width

	return t1.show()

def testTwo():

	t1 = mktable()
	tblptr.append(t1)
	offset.append(0)
	id1 = ID(name="id1",state=1)
	T1 = T(name="T1",state=1)
	T1.type_ = "real"
	T1.width = 8
	enter(tblptr[-1],id1.name,T1.type_,offset[-1])
	offset[-1] = offset[-1] + T1.width
	T3 = T(name="T3",state=3)
	T3.type_ = "integer"
	T3.width = 4

	T2 = T(name="T2",state=2)
	T2.type_ = "ptr " + T3.type_
	T2.width = 4
	id2 = ID("id2",2)
	enter(tblptr[-1],id2.name,T2.type_,offset[-1])
	offset[-1] = offset[-1] + T2.width

	T4 = T(name="T4",state=4)
	T4.type_ = "real"
	T4.width = 8
	id3 = ID(name="id3",state=3)
	enter(tblptr[-1],id3.name,T4.type_,offset[-1])
	offset[-1] = offset[-1] + T4.width

	return t1.show()

def testThree():

	t1 = mktable()
	tblptr.append(t1)
	offset.append(0)

	T1 = T(name="T1",state=1)
	T1.type_ = "real"
	T1.width = 8

	id1 = ID("id1",state=1)

	enter(tblptr[-1],id1.name,T1.type_,offset[-1])
	offset[-1] = offset[-1] + T1.width

	t2 = mktable()
	tblptr.append(t2)
	offset.append(0)

	T2 = T(name="T2",state=2)
	T2.type_ = "real"
	T2.width = 8

	id3 = ID("id3",state=3)

	enter(tblptr[-1],id3.name,T2.type_,offset[-1])
	offset[-1] = offset[-1] + T2.width

	id2 = ID("id2",state=2)

	t = tblptr[-1]
	addwidth(t,offset[-1])
	tblptr.pop()
	offset.pop()
	enterproc(tblptr[-1],id2.name,t)



	return t1.show()



# resultThree = testThree()
# itemsGroup =  resultThree.items()
# for i in itemsGroup:
# 	# print(i)
# 	if i[0] != 'id2':
# 		print(i[1])
# 	else:
# 		for one,two in i[1].show().items():
# 			print(one,two)
		# for j in i[1].show():
		# 	print(j)
		


# id1:real;id2:^integer;id3:integer$
resultTwo = testTwo()
for one,two in resultTwo.items():
	print(two)

# id1 : real ; id2 :↑integer; id3:integer
# resultOne = testOne()
# for one,two in resultOne.items():
# 	print(two)






id1:real;id2:↑real;proc id3;id4:real; proc id5;id6:real;id7:real
Width : 16
---------------------------
name   type    offset  
---------------------------
 id1    real    0       
 id2    ↑real   8       
 id3    proc            

 id4    real    0       
 id5    proc            

 id6    real    0       
 id7    real    8       