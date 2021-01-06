# -*- coding: utf-8 -*-
# @Author: TD21forever
# @Date:   2019-05-24 15:48:23
# @Last Modified by:   TD21forever
# @Last Modified time: 2019-05-25 00:18:33


'''
越是放在前面，读取的次数越是多。所以放在前面的用时尽量小
贪心的思想
'''
def solution(rate,length,n):
	multiResult = []
	sumRate = sum(rate)
	for i in range(len(rate)):
		rate[i] = rate[i]/sumRate
	for i in range(n):
		tmp = rate[i]*length[i]
		multiResult.append(tmp)
	multiResult.sort()
	Sum = 0
	for i in range(n):
		Sum += multiResult[i]*(n-i)
	return Sum



if __name__ == '__main__':
	n = 5
	rate = [872,452,265,120,87]
	length = [71,46,9,73,35]
	res = solution(rate,length,n)
	print(res)
