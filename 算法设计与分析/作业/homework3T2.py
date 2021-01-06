# -*- coding: utf-8 -*-
# @Author: TD21forever
# @Date:   2019-05-25 00:18:44
# @Last Modified by:   TD21forever
# @Last Modified time: 2019-05-26 11:36:12

'''
保证差距最远的两个磁道的概率最小
'''
def solution(k,alist):
	sumRate = sum(alist)
	rate = [i/sumRate for i in alist]
	rate.sort()
	j = 0
	k = 0
	result = 0
	tmp = rate.copy()
	for i in range(len(rate)):
		if i %2 == 0:
			tmp[0+j] = rate[i]
			j += 1
		else:
			tmp[-1-k] = rate[i]
			k += 1
	for i in range(len(tmp)):
		for j in range(i+1,len(tmp)):
			result += tmp[i]*tmp[j]*(j-i)
	return result

if __name__ == '__main__':
	rate = [33, 55, 22, 11, 9]
	k = 5
	res = solution(k,rate)
	print(res)