# -*- coding: utf-8 -*-
# @Author: TD21forever
# @Date:   2019-04-10 16:26:33
# @Last Modified by:   TD21forever
# @Last Modified time: 2019-06-16 13:06:45

'''
一维最近对问题 
分治法
1.最优解在左侧      }
2.最优解在右侧      } 三者取最小值
3.最优解在中点附近  }

T(n) = 2T(n/2)  ====> T(n) = O(logn) （若需要自己排序 则T(n) = O(nlog^2n)）
'''
def minPointDistance(List,left,right):
	if left == right:
		return 999999
	elif right - left == 1:
		return List[right] - List[left]
	else:
		mid = (left+right)//2
		leftMinDistance = minPointDistance(List,left,mid)#得到左边的最小值
		rightMinDistance = minPointDistance(List,mid+1,right)#得到右边的最小值
		ans = min(leftMinDistance,rightMinDistance)
		tmp = min(List[mid]-List[mid-1],List[mid+1]-List[mid])#如果中轴线附近有更小的值，就更新
		if tmp < ans:
			tmp = ans
	return ans

	'''
		另一种写法 略啰嗦 舍去
		if len(List)%2 == 0: #如果是偶数
			s1 = List[mid+1] - List[mid]
			res = min(leftMinDistance,rightMinDistance,s1)
			start = mid
			end = mid+1
		else:
			s1 = List[mid+1] - List[mid]
			s2 = List[mid] - List[mid-1]
			if s1 < s2:
				start = mid
				end = mid+1
			else:
				start = mid-1
				end = mid
			res = min(leftMinDistance,rightMinDistance,s1,s2)
	'''
		
print(minPointDistance([0,2,9,19,27,39,43],0,6))#2


