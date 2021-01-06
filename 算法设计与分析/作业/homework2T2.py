# -*- coding: utf-8 -*-
# @Author: TD21forever
# @Date:   2019-05-15 08:17:58
# @Last Modified by:   TD21forever
# @Last Modified time: 2019-05-15 08:50:55

'''
最长上升子序列
Longest  Increasing Subsequence

让我们举个例子：求 2 7 1 5 6 4 3 8 9 的最长上升子序列。我们定义d(i) (i∈[1,n])来表示前i个数以A[i]结尾的最长上升子序列长度。

　　前1个数 d(1)=1 子序列为2；

　　前2个数 7前面有2小于7 d(2)=d(1)+1=2 子序列为2 7

　　前3个数 在1前面没有比1更小的，1自身组成长度为1的子序列 d(3)=1 子序列为1

　　前4个数 5前面有2小于5 d(4)=d(1)+1=2 子序列为2 5

　　前5个数 6前面有2 5小于6 d(5)=d(4)+1=3 子序列为2 5 6

　　前6个数 4前面有2小于4 d(6)=d(1)+1=2 子序列为2 4

　　前7个数 3前面有2小于3 d(3)=d(1)+1=2 子序列为2 3

　　前8个数 8前面有2 5 6小于8 d(8)=d(5)+1=4 子序列为2 5 6 8

　　前9个数 9前面有2 5 6 8小于9 d(9)=d(8)+1=5 子序列为2 5 6 8 9

　　d(i)=max{d(1),d(2),……,d(i)} 我们可以看出这9个数的LIS为d(9)=5
'''


MAXLEN=99

def LIS(alist):
	dp = [1]*MAXLEN
	for i in range(len(alist)):
			for j in range(0,i):
				#dp[i]以alist[i]结尾的序列 的 LIS 长度
				#找到比当前这个数(alist[i])小的数，当前这个数的dp(dp[i])为比它小的数的dp+1
				#由于比它小的数可能不止一个，所以求出来的dp要求最大值
				if alist[j] < alist[i]:
					dp[i] = max(dp[j] + 1,dp[i])   

	return max(dp[0:len(alist)])



alist = [2,7,1,5,6,4,3,8,9]
ans = LIS(alist)
print(ans)