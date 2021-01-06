# -*- coding: utf-8 -*-
# @Author: TD21forever
# @Date:   2019-05-22 17:53:35
# @Last Modified by:   TD21forever
# @Last Modified time: 2019-05-22 20:37:39
import numpy as np

alist = np.array([[7,0,0,0,0],[3,8,0,0,0],[8,1,0,0,0],[2,7,4,4,0],[4,5,2,6,5]])
def solution(alist):
	rowNum = alist.shape[0]
	dp = np.zeros([rowNum,rowNum])
	for i in range(rowNum):
		dp[rowNum-1][i] = alist[rowNum-1][i] 
	#从倒数第二行开始
	for i in range(rowNum-2,-1,-1):
		for j in range(i+1):
			dp[i][j] = max(dp[i+1][j],dp[i+1][j+1])+alist[i][j] 
	return dp
res = solution(alist)[0][0]
print("原始三角形")
print(alist)
print("最优解")
print(res)
print("动态规划数组")
print(solution(alist))