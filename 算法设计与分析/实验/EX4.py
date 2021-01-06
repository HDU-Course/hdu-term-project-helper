# -*- coding: utf-8 -*-
# @Author: TD21forever
# @Date:   2019-05-21 17:40:08
# @Last Modified by:   TD21forever
# @Last Modified time: 2019-05-22 17:12:04

def solution(alist,k):
	cnt = 0
	while k>1:
		alist.sort()
		m = alist.pop(0)
		n = alist.pop(0)
		alist.append(m+n)
		cnt += m+n-1
		print(m,"与",n,"合并,得到",m+n,",花费",m+n-1,"次比较,此时cnt为",cnt)
		k -= 1
	return cnt
print(solution([1,2,3,4],4))
