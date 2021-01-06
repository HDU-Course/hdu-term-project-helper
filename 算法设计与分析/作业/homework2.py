# -*- coding: utf-8 -*-
# @Author: TD21forever
# @Date:   2019-05-26 14:13:02
# @Last Modified by:   TD21forever
# @Last Modified time: 2019-05-26 23:33:44

'''
LCS,最长公共子序列
dp[i][j] 表示长度为i和j的两个子串的 LCS
'''
import numpy as np

def solution(alist1,alist2):
	alist1.insert(0,0)
	alist2.insert(0,0)
	dp = np.zeros([len(alist1),len(alist2)])
	path = [[0 for i in range(len(alist2))] for j in range(len(alist1))]
	if len(alist1)==0 or len(alist2)==0:
		return 0
	for i in range(1,len(alist1)):
		for j in range(1,len(alist2)):
			if alist1[i] == alist2[j]:
				dp[i][j] = dp[i-1][j-1]+1
				path[i][j] = '↖'
			else:
				if dp[i-1][j] >= dp[i][j-1]:
					dp[i][j] = dp[i-1][j]
					path[i][j] = '↑' 
				else:
					dp[i][j] = dp[i][j-1]
					path[i][j] = '←' 
	return dp,path
alist1 = [1, 0, 0, 1, 0, 1, 0, 1]
alist2 = [0, 1, 0, 1, 1, 0, 1, 1, 0]
res = solution(alist2,alist1)




def MATRIX_CHAIN_ORDER(p):
	n = len(p)
	s = [[0 for j in range(n)] for i in range(n)]
	m = [[0 for j in range(n)] for i in range(n)]
	for l in range(2, n):			#l is the chain length l=j-i+1
		for i in range(1, n-l+1):
			j = i + l - 1
			m[i][j] = 1e9
			for k in range(i, j):
				q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j]
				if q < m[i][j]:
					m[i][j] = q#成本
					s[i][j] = k#分裂点k
	print()
	PRINT_OPTIMAL_PARENS(s, 1, n-1)
	print()
	
def PRINT_OPTIMAL_PARENS(s, i, j):
	if i == j:
		print('A', end = '')
		print(i, end = '')
	else:
		print('(', end = '')
		PRINT_OPTIMAL_PARENS(s, i, s[i][j])
		PRINT_OPTIMAL_PARENS(s, s[i][j]+1, j)
		print(')', end = '')
		
A = [5, 10, 3, 12, 5, 50, 6]
MATRIX_CHAIN_ORDER(A)
