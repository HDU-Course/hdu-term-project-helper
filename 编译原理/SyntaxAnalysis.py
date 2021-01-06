# -*- coding: utf-8 -*-
# @Author: TD21forever
# @Date:   2019-05-30 20:27:33
# @Last Modified by:   TD21forever
# @Last Modified time: 2019-06-08 15:00:21
from stack import Stack
SYNTAX = ["E->Te","e->+Te|#","T->Ft","t->*Ft|#","F->(E)|i"]
VT = ['i','+','*','(',')']
FIRST = {}
FOLLOW = {}
SELECT = {}
TABLE = {}
#切分文法 初始化first集 FOLLOW集 SELECT集
def processSyntax(syntax):
	newsyntax = []
	for i in syntax:
		if i.find('|') == -1:
			newsyntax.append(i)
		else:
			index_1 = i.find('>')
			index_2 = i.find('|')#|所在的下标
			syntax_1 = i[:index_2]
			syntax_2 = i[:index_1+1]+i[index_2+1:]
			newsyntax.append(syntax_1)
			newsyntax.append(syntax_2)

	for i in newsyntax:
		tmp = i.split('->')
		FIRST[tmp[0]] = []

	for i in newsyntax:
		tmp = i.split('->')
		FOLLOW[tmp[0]] = []

	for i in newsyntax:
		SELECT[i] = []

	for i in newsyntax:
		syntaxSplit = i.split('->')
		left = syntaxSplit[0]
		TABLE[left] = {}

	return newsyntax

#获取first集，传入的参数是某一条产生式
def getFirst(syntax):
	for j in range(len(syntax)-1):
		for i in syntax:
			syntaxSplit = i.split('->')
			left = syntaxSplit[0]
			right = syntaxSplit[1]
			if right == '#':
				FIRST[left].append(right)
			elif right[0] in VT:
				FIRST[left].append(right[0])
			else:
				FIRST[left].extend(FIRST[right[0]])
			FIRST[left] = list(set(FIRST[left]))

def getFollow(syntax):
	#文法的开始符号
	start = syntax[0].split('->')[0]
	FOLLOW[start].append("$")
	for i in range(len(syntax)-1):
		for i in syntax:
			syntaxSplit_1 = i.split('->')
			#左部
			left_1 = syntaxSplit_1[0]
			for j in syntax:
				syntaxSplit_2 = j.split('->')
				left_2 = syntaxSplit_2[0]
				right_2 = syntaxSplit_2[1]
				if left_1 in right_2:
					index = right_2.find(left_1)
					#如果index可以加一
					if index+1 < len(right_2):
						#index+1的地方的值是终结符
						if right_2[index+1] in VT:
							#那FOLLOW集加入终结符
							FOLLOW[left_1].append(right_2[index+1])							
						else:
							#如果不是终结符，加他的FIRST集，再分两种情况 有空串 和 没有空串
							FOLLOW[left_1].extend(FIRST[right_2[index+1]])
							#如果有空串
							if '#' in FIRST[right_2[index+1]]:
								FOLLOW[left_1].remove('#')
								FOLLOW[left_1].extend(FOLLOW[left_2])
					#去重
					FOLLOW[left_1] = list(set(FOLLOW[left_1]))

					#如果index不可以+1 T->FT'  放在T后面也要放在T'后面
					if index+1 == len(right_2):
						FOLLOW[left_1].extend(FOLLOW[left_2])
						FOLLOW[left_1] = list(set(FOLLOW[left_1]))
def getSelect(syntax):
	for i in syntax:
		syntaxSplit = i.split('->')
		left = syntaxSplit[0]
		right = syntaxSplit[1]
		if right[0] in VT:
			SELECT[i].append(right[0])
		elif right == '#':
			SELECT[i]= FOLLOW[left].copy()
		else:
			SELECT[i]= FIRST[left].copy()

def preTable(syntax):

	for i in syntax:
		syntaxSplit = i.split('->')
		left = syntaxSplit[0]
		right = syntaxSplit[1]
		tmp = {}
		for j in SELECT[i]:
			tmp[j] = i
		for j in FOLLOW[left]:
			if tmp.get(j) == None:
				tmp[j] = 'SYNCH'
		TABLE[left].update(tmp)

def analysis(String,syntax):
	print("{: >8}{: ^20}{: >9}".format('栈','剩余输入','动作'))
	start = syntax[0].split('->')[0]
	stack = Stack()
	stack.push('$')
	stack.push(start)
	index = 0
	count = 1
	ERROR = False
	print("{: <8}{: <8}{: <22}{: <23}".format(count,stack.show(),String[index:],"初始化"))
	while True:
		count += 1
		top = stack.peek() 

		if top == '$' and String[index] == '$':
			print("{: <8}{: <8}{: <22}{: <22}".format(count,stack.show(),String[index:],"结束"))
			break
		if top == String[index]:
			print("{: <8}{: <8}{: <22}{: <22}".format(count,stack.show(),String[index:],top+"匹配"))
			stack.pop()
			index += 1
			continue
		if top in VT and top != String[index]:
			print("{: <8}{: <8}{: <22}{: <22}".format(count,stack.show(),String[index:],"错误 终结符不匹配"))
			ERROR = True
			stack.pop()
			continue
		#预测分析表中的产生式 找不到默认是None
		production = TABLE[top].get(String[index])
		#如果[A,a]为空 报错 忽略a
		if production == None:
			print("{: <8}{: <8}{: <22}报错 忽略{: <22}".format(count,stack.show(),String[index:],String[index]))
			ERROR = True
			index += 1
		#如果为SYNCH 弹出栈顶非终结符A
		elif production == "SYNCH":
			ERROR = True
			print("{: <8}{: <8}{: <22}{: <22}".format(count,stack.show(),String[index:],"报错 为SYNCH"))
			stack.pop()
		else:
			print("{: <8}{: <8}{: <22}{: <22}".format(count,stack.show(),String[index:],production))
			syntaxSplit = production.split('->')
			left = syntaxSplit[0]
			right = syntaxSplit[1]
			stack.pop()
			if right != '#':
				for i in right[::-1]:
					stack.push(i)
	if ERROR:
		print("文法不合法")
	else:
		print("文法合法")


res = processSyntax(SYNTAX)
print(res)
getFirst(res)
print(FIRST)
getFollow(res)
print(FOLLOW)
getSelect(res)
print(SELECT)
preTable(res)
print(TABLE)

#i++i**i
#(i+i*i)+i
#i+i*i+
String = 'i+i*i+$'

analysis(String,res)