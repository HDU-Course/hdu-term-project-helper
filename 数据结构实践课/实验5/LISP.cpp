/*
* @Author: TD21forever
* @Date:   2018-11-19 20:30:55
* @Last Modified by:   TD21forever
* @Last Modified time: 2018-11-26 23:25:33
*/
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<stack>
using namespace std;
int f(char a[])
{
	stack<int>int_s1;//建立两个栈 一个数字栈
	stack<char>char_s2;//一个操作符栈
	int num;
	int i = 0;
	char operate;
	int num1;
	int num2;
	int res;
	while(a[i] != '\0')
	{
		if (isdigit(a[i]))
		{
			num = (a[i] - '0');
			int_s1.push(num);
		}
		else
		{
			switch(a[i])
			{
			case '(': char_s2.push(a[i]); break;
			case '+': char_s2.push(a[i]); break;
			case ')':
				operate = char_s2.top();
				char_s2.pop();
				char_s2.pop();//退两次操作符栈栈
				num1 = int_s1.top();
				int_s1.pop();
				num2 = int_s1.top();
				int_s1.pop();//拿出两个数字
				if (operate == '+')//做加法
				{
					res = num1 + num2;
					int_s1.push(res);//把结果压入栈
				}
				break;
			}
		}
		i++;
	}
	res = int_s1.top();
	return res;
}

int main(int argc, char const *argv[])
{
	printf("-----------------------------------\n");
	printf("欢迎使用简单LISP算数表达式计算器\n");
	while(1)
	{
		char a[20];
		printf("请输入表达式\n");
		gets(a);
		int res = f(a);
		printf("表达式结果为\n");
		printf("%d\n", res);

	}
	return 0;
}