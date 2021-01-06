# -*- coding: utf-8 -*-
# @Author: TD21forever
# @Date:   2019-05-26 12:14:07
# @Last Modified by:   TD21forever
# @Last Modified time: 2019-06-17 23:11:15
import numpy as np
'''
dp[item][cap]的意思是  从前item个物品中拿东西 放到容量为cap 的背包中 能拿到的最大价值
'''
def solution(num,waste,value,capacity):
	dp = np.zeros([num+5,capacity+2])
	for item in range(1,num+1):
		for cap in range(1,capacity+1):
			if waste[item] > cap:#第item个太大了 拿不了
				dp[item][cap] = dp[item-1][cap]
			else:
				situation1 = dp[item-1][cap]#不拿
				situation2 = dp[item-1][cap-waste[item]] + value[item]#拿
				if situation1 > situation2:
					dp[item][cap] = situation1
				else:
					dp[item][cap] = situation2
	return dp

if __name__ == '__main__':
	waste = [0, 2, 3, 4]
	value = [0, 3, 4, 5]
	num = 3
	capacity = 10
	res = solution(num,waste,value,capacity)
	print(res)
	# print(res[5][20])

