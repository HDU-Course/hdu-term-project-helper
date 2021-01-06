/*
* @Author: TD21forever
* @Date:   2018-11-19 16:24:17
* @Last Modified by:   TD21forever
* @Last Modified time: 2018-11-26 22:41:40
*/
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 12500
typedef int ElemType;
typedef struct
{
	int i, j;
	ElemType e;
} Triple;

typedef struct
{
	Triple array[MAXSIZE];//存的都是三元组 非零元素
	int mrow, mcol, num;
} TSMatrix;

void input(TSMatrix *m)
{
	int row, col;
	printf("你的矩阵一共有几行几列(行，列)\n");
	scanf("%d %d", &row, &col);
	m->mrow = row;
	m->mcol = col;
	int i, j, e;
	m->num = 0;
	printf("请按照行优先输入三元组，-1 -1 -1 结束\n");
	while(scanf("%d %d %d", &i, &j, &e) == 3)
	{
		if (i == -1 && j == -1 && e == -1)
		{
			break;
		}
		m->array[m->num].i = i;
		m->array[m->num].j = j;
		m->array[m->num].e = e;
		m->num ++;
	}

}

void add(TSMatrix *m1, TSMatrix *m2, TSMatrix *res)
{
	if (m1->mrow != m2->mrow || m1->mcol != m2->mcol)
	{
		printf("两个矩阵的行数或者列数不相等\n");
		return;
	}
	res->mrow = m1->mrow;//矩阵相加 新的矩阵行列和原来的一样
	res->mcol = m1->mcol;
	res->num = 0;//一开始没有三元组
	for (int i = 1; i <= res->mrow; ++i)
	{
		for (int j = 1; j <= res->mcol; ++j)//可以看成res是一个新的矩阵，遍历每一个格子
		{
			int flag = 0;
			for (int k = 0; k < m1->num; ++k)//一开始其实是第一个矩阵的copy (这个等号)
			{
				if (m1->array[k].i == i && m1->array[k].j == j)//如果当前这个格子的位置 和 存在m1三元组里的位置是一样的 更新下
				{
					res->array[res->num].i = i;
					res->array[res->num].j = j;
					res->array[res->num].e = m1->array[k].e;//加入一个三元组
					flag = 1;
					break;//同一位置只可能有一个元素
				}
			}
			for (int k = 0; k < m2->num; ++k)
			{
				if (m2->array[k].i == i && m2->array[k].j == j)
				{
					res->array[res->num].i = i;
					res->array[res->num].j = j;
					if (!flag)
					{
						res->array[res->num].e = m2->array[k].e;
					}
					else
					{
						res->array[res->num].e += m2->array[k].e;
					}
					flag = 1;
				}
			}
			if (flag)
			{
				res->num++;
			}
		}
	}
	int cnt = 0;
	for (int i = 0; i < res->num; ++i)
	{
		if (res->array[i].e == 0)//如果一正一负加起来变成零了 把这个节点删掉
		{
			for (int j = i + 1 ; j < res->num; ++j)
			{
				res->array[j - 1] = res->array[j];
			}
			cnt ++;
		}
	}
	res->num -= cnt;//现在还有几个

}
void sub(TSMatrix *m1, TSMatrix *m2, TSMatrix *res)
{
	for (int i = 0; i < m2->num; ++i)
	{
		m2->array[i].e *= -1;//是m2乘-1 不是m1
	}
	add(m1, m2, res);
	for (int i = 0; i < m2->num; ++i)//记得乘回去
	{
		m2->array[i].e *= -1;
	}
}

void mult(TSMatrix *m1, TSMatrix *m2, TSMatrix *res)//乘法先把三元组转成普通矩阵
{
	if (m1->mcol != m2->mrow)
	{
		printf("矩阵列数不等于行数，错误\n");
		return;
	}
	res->mrow = m1->mrow;//行 是 m1的列
	printf("%d\n", res->mrow);
	res->mcol = m2->mcol;//列 是 m2的行
	printf("%d\n", res->mcol);
	int arr1[m1->mrow][m1->mcol];
	int arr2[m2->mrow][m2->mcol];
	int arr3[res->mrow][res->mcol];

	for (int i = 0; i < m1->mrow; ++i)
	{
		for (int j = 0; j < m1->mcol ; ++j)
		{
			arr1[i][j] = 0;
		}
	}
	for (int i = 0; i < m2->mrow; ++i)
	{
		for (int j = 0; j < m2->mcol ; ++j)
		{
			arr2[i][j] = 0;
		}
	}
	for (int i = 0; i < res->mrow; ++i)
	{
		for (int j = 0; j < res->mcol ; ++j)
		{
			arr3[i][j] = 0;
		}
	}

	for (int i = 0; i <= m1->num; ++i)//这里的等号忘记了 有m1->num 这么多数据
	{
		arr1[m1->array[i].i - 1][m1->array[i].j - 1] =  m1->array[i].e; //把三元组的值赋给数组 元组里的行列 是从1开始的 默认加了1 记得要减一
	}

	for (int i = 0; i <= m2->num; ++i)
	{
		arr2[m2->array[i].i - 1][m2->array[i].j - 1] =  m2->array[i].e;
	}
	for (int i = 0; i < res->mrow; ++i)
	{
		for (int j = 0; j < res->mcol; ++j)
		{
			for (int k = 0; k < m1->mcol; ++k)
			{
				arr3[i][j] += arr1[i][k] * arr2[k][j]; //矩阵乘法 三层循环 再看看
			}

			if (arr3[i][j] != 0)
			{
				res->array[res->num].i = i + 1;
				res->array[res->num].j = j + 1;
				res->array[res->num].e = arr3[i][j];
				res->num++;
			}
		}
	}
}
void Printf(TSMatrix *m)                                 //打印矩阵
{
	int a[m->mrow][m->mcol];
	for(int i = 0; i < m->mrow; i++)
		for(int j = 0; j < m->mcol; j++)
			a[i][j] = 0;

	for(int k = 0; k <= m->num; k++)//这里有等号，数组从0开始 三元组 从1开始
		a[m->array[k].i - 1][m->array[k].j - 1] = m->array[k].e;

	//printf("\n\n矩阵为：\n");
	for(int i = 0; i < m->mrow; i++)
	{
		for(int j = 0; j < m->mcol; j++)
			printf("%-2d ", a[i][j]);
		printf("\n");
	}
}

int main()
{
	printf("/*****************稀疏矩阵运算器 ****************/\n\n");
	printf("功能选择：\n1.矩阵相加\n2.矩阵相减\n3.矩阵相乘\n");
	int n;
	printf("选择功能：");
	scanf("%d", &n);
	TSMatrix M1;
	TSMatrix M2;
	TSMatrix M3;
	TSMatrix *m1 = &M1;
	TSMatrix *m2 = &M2;
	TSMatrix *res = &M3;
	// 4 5 1 1 4 1 2 -3 1 5 1 2 4 8 3 3 1 4 5 70 -1 -1 -1 5 3 1 1 3 2 1 4 2 2 2 3 2 1 4 1 1 -1 -1 -1
	// 1 1 3 2 1 4 2 2 2 3 2 1 4 1 1

	switch(n)
	{
	case 1:
		printf("\n请输入矩阵1：\n");
		input(m1);
		printf("\n请输入矩阵2：\n");
		input(m2);
		add(m1, m2, res);
		printf("\n结果为：\n");
		Printf(res);
		break;
	case 2:
		printf("\n请输入矩阵1：\n");
		input(m1);
		printf("\n请输入矩阵2：\n");
		input(m2);
		sub(m1, m2, res);
		printf("\n结果为：\n");
		Printf(res);
		break;
	case 3:
		printf("\n请输入矩阵1：\n");
		input(m1);
		printf("\n请输入矩阵2：\n");
		input(m2);
		mult(m1, m2, res);
		printf("\n结果为：\n");
		Printf(res);
		break;
	}
	return 0;
}
