# -*- coding: utf-8 -*-
# @Author: TD21forever
# @Date:   2019-10-19 17:05:05
# @Last Modified by:   TD21forever
# @Last Modified time: 2019-10-26 15:52:08
import pandas as pd
from scipy.io import arff
import numpy as np
# 读取文件
data = arff.loadarff('./CM1.arff')
df = pd.DataFrame(data[0])
head_list = df.columns.values.tolist()

# 标准化
data_without_YN = df.drop("Defective", axis=1)
data_normalize = (data_without_YN - data_without_YN.mean()) / \
    (data_without_YN.std())
data_normalize['Defective'] = df.Defective

# 分离未标准化的yes样本和no样本
row_yes_data = df[df.Defective == b'Y']
row_yes_data = row_yes_data.drop("Defective", axis=1).values
row_no_data = df[df.Defective == b'N']
row_no_data = row_no_data.drop("Defective", axis=1).values

# 分离标准化后的yes样本和no样本
# 得到缺陷样本
yes_samples = data_normalize[data_normalize.Defective == b"Y"]
yes_samples = yes_samples.drop("Defective", axis=1)
# 得到无缺陷样本
no_samples = data_normalize[data_normalize.Defective == b"N"]
no_samples = no_samples.drop("Defective", axis=1)
# 近邻数k
k = len(no_samples) // len(yes_samples)


yes_samples_array = yes_samples.values
no_samples_array = no_samples.values
array = [[np.sqrt(np.sum(np.square(x - y)))
          for y in no_samples_array]for x in yes_samples_array]
array = np.array(array).argsort()[:, :k]

w = {i: 0 for i in range(yes_samples.shape[1])}
for i in range(array.shape[0]):
    for j in array[i]:
        ds = np.abs(row_yes_data[i, :] - row_no_data[j, :])
        ds = pd.Series(ds).rank(method='min')
        for index in range(len(ds)):
            w[index] += ds[index]





import pandas as pd
from scipy.io import arff
import numpy as np
import time
import numba
data = arff.loadarff('./CM1.arff')
df = pd.DataFrame(data[0]).drop("Defective", axis=1)
head_list = df.columns


def data_discretize(dataset):
    n = 20
    columns = dataset.shape[1]
    for column in range(columns):
        #每一个特征
        x = dataset.iloc[:,column]
        y = pd.cut(x,n,labels=range(n))
        dataset.iloc[:,column] = y.astype('float64')
    return dataset



def get_px(feature):
    return feature.value_counts() / df.shape[0]

# 传入一个特征


def get_hx(feature):
    px = get_px(feature)
    log2px = np.log2(px)
    Hx = -np.sum(log2px * px)
    return Hx


def get_hxy(X, Y):
    pxy = pd.crosstab(X, Y, margins=True).apply(lambda x: x / x[-1])
    log2pxy = np.log2(pxy)
    where_is_inf = np.isinf(log2pxy)
    log2pxy[where_is_inf] = 0.0
    py = get_px(Y)
    hxy = -np.sum(py * np.sum(pxy * log2pxy))
    return hxy


def get_su(X, Y):
    hx = get_hx(X)
    hy = get_hx(Y)
    hxy = get_hxy(X, Y)
    igxy = hx - hxy
    suxy = 2 * igxy / (hx + hy)
    return suxy

#离散化 20组
df = data_discretize(df)

M = np.zeros((df.shape[1], df.shape[1]))
for featurex in range(df.shape[1]):
    for featurey in range(df.shape[1]):
        res = get_su(df.iloc[:, featurex], df.iloc[:, featurey])
        M[featurex][featurey] = res
        print("M[{}][{}]={}".format(featurex, featurey, res))
M = pd.DataFrame(M)
M.index = head_list
M.columns = head_list
print(M)
