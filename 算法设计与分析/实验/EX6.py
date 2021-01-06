# -*- coding: utf-8 -*-
# @Author: TD21forever
# @Date:   2019-05-28 21:13:11
# @Last Modified by:   TD21forever
# @Last Modified time: 2019-05-29 09:12:05
def maxAndSec(alist):
	if len(alist) == 2:
		if alist[0] > alist[1]:
			maxNum = alist[0]
			secNum = alist[1]
		else:
			maxNum = alist[1]
			secNum = alist[0]
		return maxNum,secNum
	elif len(alist) == 1:
		maxNum = alist[0]
		secNum = alist[0]
		return maxNum,secNum
	else:
		start = 0
		end = len(alist)
		mid = (start+end)//2
		left = maxAndSec(alist[start:mid])
		right = maxAndSec(alist[mid:end])
		#如果在左边产生了最大值
		if left[0] > right[0]:
			finalMax = left[0] 
			#亚军一定和冠军比过赛 
			fianlSec = max(left[1],right[0])
		else:
			finalMax = right[0] 
			fianlSec = max(right[1],left[0])
	return (finalMax,fianlSec)	

alist = [8,7,9,2,3,6,10,12]
maxNum,secNum = maxAndSec(alist)
print(maxNum,secNum)



