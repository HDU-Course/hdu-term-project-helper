# -*- coding: utf-8 -*-
# @Author: TD21forever
# @Date:   2019-04-13 19:07:55
# @Last Modified by:   TD21forever
# @Last Modified time: 2019-04-14 23:21:16
import re

dic_keyword = {
	'begin':1,
	'if' : 2,
	'then':3,
	'while':4,
	'do':5,
	'end':6,
}
dic_ID = {'ID':10}
dic_Num = {'Num':11}
dic_operator = {

	'+':13,
	'-':14,
	'*':15,
	'/':16,
	':':17,
	':=':18,
	'<':20,
	'<>':21,
	'<=':22,
	'>':23,
	'>=':24,
	'=':25,
	';':26,
	'(':27,
	')':28,
	'#':0
}

def tokenize(code):
	ERROR = r'(?P<ERROR>\,|(\d+\w+))'
	keywords = r'(?P<Keyword>(begin){1}|(if){1}|(then){1}|(while){1}|(do){1}|(end){1})'
	Operator = r'(?P<Operator>\:=|\:|\+|\-|\*|\/|<=|>=|<>|>|<|=|;|\(|\)|#)'
	ID = r'(?P<ID>[a-zA-Z_][a-zA-Z_0-9]*)'
	Num = r'(?P<Num>\d+(\.\d*)?)'
	res = '|'.join([ERROR,keywords,Operator,Num,ID])
	patterns = re.compile(res)
	for one in re.finditer(patterns,code):
		# print(one)
		if one.lastgroup == 'Keyword':
			print('(',dic_keyword[one.group()],',',one.group(),')')
		elif one.lastgroup == 'Operator':
			print('(',dic_operator[one.group()],',',one.group(),')')
		elif one.lastgroup == 'Num':
			print('(',dic_Num['Num'],',',one.group(),')')
		elif one.lastgroup == 'ID':
			print('(',dic_ID['ID'],',',one.group(),')')
		elif one.lastgroup == 'ERROR':
			print('(',"ERROR",one.group(),')')

tokenize('begin x:=9a; if x><9 then x<>2*x+1/3;, end #')

