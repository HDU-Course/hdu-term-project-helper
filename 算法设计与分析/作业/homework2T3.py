# -*- coding: utf-8 -*-
# @Author: TD21forever
# @Date:   2019-05-15 08:59:18
# @Last Modified by:   TD21forever
# @Last Modified time: 2019-06-18 09:19:35

'''
https://blog.csdn.net/elma_tww/article/details/86522629

举例：如果要在 1 2 3 4 5 五个数中插入两个乘号

一、 1 2 3 4 中插入一个乘号 或者
二、 1 2 3 中插入一个乘号 或者
三、 1 2 中插入一个乘号 

'''


import numpy as np

MAXLEN = 20
#在nums中加入numX个乘号
#dp[i][j] 在长度为i的字符串中插入j个乘号


def num(num_str,start,end):
	return int(num_str[start-1:end])


def solution(num_str,numX):
	dp = np.zeros((MAXLEN,MAXLEN))
	dp[0][0] = 0
	for i in range(1,len(num_str)+1):
		dp[i][0] = num(num_str,1,i)
	#在长度为i的字符串中
	for i in range(1,len(num_str)+1):
		#插入j个乘号
		for j in range(1,numX+1):
			if i-j >=1:
				for k in range(1,i):
							#等于 在长度为k的字符串中插入j-1个乘号 * 从k+1到i这段字符串的值
					dp[i][j] = max(dp[k][j-1]*num(num_str,k+1,i),dp[i][j])
	return dp[i][j]

if __name__ == '__main__':
	res = solution("123",2)
	print(res)

