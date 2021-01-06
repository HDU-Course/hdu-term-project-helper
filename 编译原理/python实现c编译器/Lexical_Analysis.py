# -*- coding: utf-8 -*-
# @Author: TD21forever
# @Date:   2019-04-14 17:13:37
# @Last Modified by:   TD21forever
# @Last Modified time: 2019-04-14 23:24:04

'''
今天上机用正则表达式匹配了程序代码，来完成词法分析，验收蒙混过关。其实这样并没有很好地掌握词法分析的实际方法，所以决定
用python实现对C语言的词法分析
'''
#关键字
keywordList = [ "auto", "break", "case", "char", "const", "continue",
			"default", "do", "double", "else", "enum", "extern",
			"float", "for", "goto", "if", "int", "long",
			"register", "return", "short", "signed", "sizeof", "static",
			"struct", "switch", "typedef", "union", "unsigned", "void",
			"volatile", "while"]

#操作符和界符
#注意单引号和双引号的表达
operatorOrDeimiter = ["+","-","*","/","<","<=",">",">=","=","==",
		   "!=",";","(",")","^",",","\"","\'","#","&",
		   "&&","|","||","%","~","<<",">>","[","]","{",
		   "}","\\",".","?",":","!"]

#快速建立一个字典，为关键字和操作符等添加识别码
keywordDic = {word:syn for syn,word in enumerate(keywordList,1)}
operatorOrDeimiterDic = {op:syn for syn,op in enumerate(operatorOrDeimiter,33)}

def scanner(code):
	#ans作为左后的输出列表
	ans = []
	#index控制字符串的位置
	index = 0
	while index < len(code):
		#过滤空格
		if code[index] == " ":
			index += 1 
			continue
		#token作为一个临时变量，记录当前拿到的字符串
		token = ""	
		#如果开头为字母
		if code[index].isalpha():
			token+=code[index]
			index+=1
			#如果再来一个字母或者再来一个数字都ok
			while code[index].isalpha() or code[index].isdigit():
				token+=code[index]
				index+=1 
			#如果是关键字
			if token in keywordList:
				ans.append({token:keywordDic[token]})
			else:
				ans.append({token:100})
		#如果首字符是数字
		elif code[index].isdigit():
			token+=code[index]
			index+=1
			while code[index].isdigit() or code[index].isalpha():
				token+=code[index]
				index += 1
			if token.isdigit():
				ans.append({token:99})
			else:
				print("ERROR",token)
				
		#如果首字符是操作符或者界符
		#对 != == << >>  && || <= >= 这八种特殊情况分别做处理
		elif code[index] in operatorOrDeimiter:
			if code[index] == '<' and code[index+1] == '=':
				ans.append({'<=':operatorOrDeimiterDic['<=']})#<=
				index += 2

			elif code[index] == '>' and code[index+1] == '=':
				ans.append({'>=':operatorOrDeimiterDic['>=']})#>=
				index += 2

			elif code[index] == '>' and code[index+1] == '>':
				ans.append({'>>':operatorOrDeimiterDic['>>']})#>>
				index += 2

			elif code[index] == '<' and code[index+1] == '<':
				ans.append({'<<':operatorOrDeimiterDic['<<']})#<<
				index += 2

			elif code[index] == '!' and code[index+1] == '=':
				ans.append({'!=':operatorOrDeimiterDic['!=']})#!=
				index += 2

			elif code[index] == '=' and code[index+1] == '=':
				ans.append({'==':operatorOrDeimiterDic['==']})#==
				index += 2

			elif code[index] == '|' and code[index+1] == '|':
				ans.append({'||':operatorOrDeimiterDic['||']})#||
				index += 2

			elif code[index] == '&' and code[index+1] == '&':
				ans.append({'&&':operatorOrDeimiterDic['&&']})#||
				index += 2

			else:
				ans.append({code[index]:operatorOrDeimiterDic[code[index]]})
				index += 1
		else:
			print("error somewhere")
	return ans

code = """for (int 999i9i = 1; i <= k; ++i){int j = 1;while(i * j < n)"""
if __name__ == '__main__':
	res = scanner(code)
	for i in res:
		for j in i:
			print('(',i[j],',',j,')')








				



