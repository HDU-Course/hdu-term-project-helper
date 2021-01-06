# -*- coding: utf-8 -*-
# @Author: TD21forever
# @Date:   2019-05-08 13:35:17
# @Last Modified by:   TD21forever
# @Last Modified time: 2019-05-08 19:22:13
from math import sqrt
import random



global_list = []
tmp = []
def Merge(leftlist,rightlist):
	i = 0
	j = 0
	result = []
	while i < len(leftlist) and j < len(rightlist):#两个列表中拿到小的数
		if leftlist[i] < rightlist[j]:
			result.append(leftlist[i])
			i += 1
		else:
			result.append(rightlist[j])
			j += 1
	#剩下的数直接放后面
	while i < len(leftlist):
		result.append(leftlist[i])
		i += 1
	while j < len(rightlist):
		result.append(rightlist[j])
		j += 1
	return result

def MergeSort(questionList):
	global global_list
	#规模足够小的时候直接返回
	if len(questionList) == 1:
		return questionList
	if len(questionList) == 2:
		return sorted(questionList)
	if len(questionList) == 3:
		return sorted(questionList)

	if len(questionList) > 3:

		N = len(questionList)
		#一共多少组
		groupNum = int(sqrt(N))
		#判断是否有余数
		perGroup = N%groupNum
		reminder = False
		if perGroup !=0:
			reminder = True
		#每组多少个
		perGroup = N//groupNum
		start = 0
		end = perGroup
		#------------`

		for i in range(groupNum):
			if reminder and i+1 == groupNum:
				res = questionList[start:]
			else:
				res = questionList[start:end]
			start = end
			end += perGroup
			ans = MergeSort(res)
			if ans == None:
				continue
			global_list = Merge(ans,global_list)
			
	

questionList = [11,15,27,88,99,102,5,23,8,10,6,99,4,3,2,1,0]
MergeSort(questionList)
random.shuffle(questionList)
print("原来的数组:",questionList)
print("排序后:",global_list)


