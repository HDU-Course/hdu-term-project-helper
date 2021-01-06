# -*- coding: utf-8 -*-
# @Author: TD21forever
# @Date:   2019-05-14 20:29:02
# @Last Modified by:   TD21forever
# @Last Modified time: 2019-05-15 08:11:02
import numpy as np


MAX_LEN = 10

def distance(a,b):
	return abs(ord(str(a))-ord(str(b)))

def solution(str1,str2,k):
	max_i = len(str1)
	max_j = len(str2)
	dp = np.zeros((MAX_LEN,MAX_LEN))
	#dp[0][0]表示两个空串
	dp[0][0] = 0
	#str1和空串
	for i in range(0,max_i+1):
		dp[i][0] = i*k
	#str2和空串
	for j in range(0,max_j+1):
		dp[0][j] = j*k
	#str1 是行
	for i in range(1,max_i+1):
		for j in range(1,max_j+1):

			#A串最后一个字符是字母，B串最后一个字符是字母
			# j:"bc " j指向c    ====>   "bc"
			# i:"a" i指向a      ====>   " a"
			choice_1 = dp[i-1][j-1]+distance(str1[i-1],str2[j-1]) 

			#A串最后一个字符是空格，B串最后一个字符是字母
			# j:"bc " j指向c    ====>   "bc "
			# i:"a" i指向a      ====>   "  a"
			choice_2 = dp[i-1][j]+k

			#A串最后一个字符是字符，B串最后一个字符是空格
			# j:"bc " j指向c    ====>   "bc"
			# i:"a" i指向a      ====>   "a "
			choice_3 = dp[i][j-1]+k

			dp[i][j] = min(choice_1,choice_2,choice_3)
	# print(i,j)
	print(dp)
	return dp[max_i][max_j]

if __name__ == '__main__':
	str1 = "cmc"
	str2 = "snmn"
	ans = solution(str1,str2,2)
	print(ans)
