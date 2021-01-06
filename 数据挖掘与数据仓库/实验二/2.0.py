# -*- coding: utf-8 -*-
# @Author: TD21forever
# @Date:   2019-10-26 17:16:09
# @Last Modified by:   TD21forever
# @Last Modified time: 2019-11-08 22:30:34
MINSUPPORT = 3
MINCONF = 0.7
dataset = [[1, 3, 4], [2, 3, 5], [1, 2, 3, 5], [2, 5]]
dataFun = {
    1: "牛奶", 2: "啤酒", 3: "尿布", 4: "面包", 5: "黄油", 6: "饼干",
}
data = [
    [1, 2, 3],
    [1, 4, 5],
    [1, 3, 6],
    [4, 5, 6],
    [2, 3, 6],
    [1, 3, 4, 5],
    [3, 4, 5],
    [2, 3],
    [1, 3, 4, 5],
    [2, 6]
]


def MakeC1(dataset):
    '''
    找到dataset中不重复的元素,并且把每个元素置为frozenset
    '''
    C1 = []
    for row in data:
        for item in row:
            if not [item] in C1:
                C1.append([item])
    C1.sort()
    C1 = list(map(frozenset, C1))
    return C1


C1 = MakeC1(dataset)
# print(C1)

# 其实就是减少Ck中元素的个数


def MakeLk(D, Ck, minsupport=MINSUPPORT):
    '''
    得出Ck中的每个元素在数据集D中所占的比例
    如果达到最小支持度的要求,就将元素放入Lklist中
    '''
    cnt = {}
    for D_data in D:
        for C_data in Ck:
            # 如果Ck中的某个元素是D中某个元素的子集
            if C_data.issubset(D_data):

                cnt[C_data] = 1 if C_data not in cnt else cnt[C_data] + 1
                # if not C_data in cnt:
                #     cnt[C_data] = 1
                # else:
                #     cnt[C_data] += 1
    # 保存了所有Ck中元素的支持度
    supportValue = {}
    # 保存返回的L列表,舍弃一些不符合要求的元素后的Ck列表
    LkList = []
    numItems = float(len(D))
    for key in cnt:
        if cnt[key] >= MINSUPPORT:
            LkList.insert(0, key)
        support = cnt[key] / numItems
        supportValue[key] = support
    return LkList, supportValue


a, b = MakeLk(dataset, C1)
# print(a, b)


def apriorGen(LK, k):
    '''
    根据k的大小,相互组合
    k=2 {0},{1},{2}--->{0,1},{0,2},{1,2}
    k=3 {0,1},{1,2},{0,2}--->{0,1,2}

        如果(l1[1]=l2[1])&&( l1[2]=l2[2])&&…&& (l1[k-2]=l2[k-2])&&(l1[k-1]<l2[k-1])，
        那认为l1和l2是可连接。连接l1和l2 产生的结果是{l1[1],l1[2],……,l1[k-1],l2[k-1]}。

        比如k=3 那么l1[0]和l2[0]就应该相等
    '''
    retList = []
    lenLK = len(LK)
    for i in range(lenLK):
        for j in range(i + 1, lenLK):
            one = list(LK[i])[:k - 2]
            two = list(LK[j])[:k - 2]
            one.sort()
            two.sort()
            # 通过树状图找规律发现,保证前几位一样,在并集
            # 不然的话就得 计算所有情况然后去重 比较麻烦
            if one == two:
                retList.append(LK[i] | LK[j])
    return retList


# print(apriorGen(a, 3))


def apriori(dataset, k=2):
    '''
    找到一个dataset的所有频繁项集
    1. 求所有单个物品的项集列表 C
    2. 去掉不满足最支持度的集合 L
    3. 组合 C
    4. goto 2

    元数据去重--->C1--->筛选-->L1-->组合(apriori算法)--->C2--->筛选-->L2-->组合...
    '''

    C1 = MakeC1(data)
    D = list(map(set, dataset))
    L1, supportValue = MakeLk(D, C1)
    L = [L1]
    index = 0

    while(len(L[index]) > 0):
        # 组合
        Ck = apriorGen(L[index], k)
        # 筛选
        Lk, supportk = MakeLk(D, Ck, k)
        supportValue.update(supportk)
        L.append(Lk)
        k += 1
        index += 1
    return L, supportValue


# 最后找出所有的频繁项集
L, supportData = apriori(data)
print("所有的频繁项集:", L)

sub_set_list = []
big_rule = []
for each in range(len(L)):
    for fre_set in L[each]:
        for sub_set in sub_set_list:
            if sub_set.issubset(fre_set):
                start = fre_set - sub_set
                end = sub_set
                conf = supportData[start | end] / supportData[start]
                startName = []
                endName = []
                for one in start:
                    startName.append(dataFun[one])
                for one in end:
                    endName.append(dataFun[one])
                # print("{}-->{},conf={}".format(start, end, conf))
                # print("{}-->{},conf={}".format(startName, endName, conf))
                if conf >= MINCONF:
                    big_rule.append((startName, endName, conf))
                    print("{}-->{},conf={}".format(startName, endName, conf))
        sub_set_list.append(fre_set)
