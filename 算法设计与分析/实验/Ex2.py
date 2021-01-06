# -*- coding: utf-8 -*-
# @Author: TD21forever
# @Date:   2019-05-08 18:39:57
# @Last Modified by:   TD21forever
# @Last Modified time: 2019-05-08 19:54:16
def min_max(alist):
	if len(alist) == 1:
		return (alist[0],alist[0])
	if len(alist) == 2:
		a = min(alist)
		b = max(alist)		
		return (a,b)
	if len(alist) >=3 :
		start = 0
		end = len(alist)
		mid = (start+end)//2
		res = min_max(alist[start:mid])
		res2 = min_max(alist[mid:end])
		return min(res[0],res2[0]),max(res[1],res2[1])
alist = [4,5,23,55,43,7,2]
res = min_max(alist)
print(res)



