/*
* @Author: TD21forever
* @Date:   2018-11-29 21:48:02
* @Last Modified by:   TD21forever
* @Last Modified time: 2018-12-01 17:03:50
*/
#include<stdio.h>
#include<stdlib.h>
#include<map>
#include<string>
#include <algorithm>
using namespace std;

/*
8
a b c d e f g h
14
a b 4
a c 3
b c 5
b d 5
c d 5
b e 9
c h 5
d e 7
d h 4
d f 6
d g 5
e f 3
f g 2
h g 6
*/


struct Node
{
	int x;
	int y;
	int distance;
	char start;
	char end;
};
Node arc[5000];
int boss_list[1050];//用来检测是否属于同一个

int findboss(int x)
{
	int boss = x;
	while(boss_list[boss] != boss)
	{
		boss = boss_list[boss];
	}
	return boss;
}

void merge(int a, int b)
{
	a = findboss(a);//a说我问问老板的意见
	b = findboss(b);//b说我问问老板的意见
	if (a != b)//如果a和b的老板是同一个 那么他们本来就在一个集合里
	{
		boss_list[a] = b;//否则的话就合并了
	}
}

bool cmp( Node a, Node b)
{
	return a.distance < b.distance;
}

int main(int argc, char const *argv[])
{
	int N, n;//N是顶点的数量，n是边的数量
	char start, end;
	int weight;
	map<char, int> mp;
	map<char, int> :: iterator it;

	printf("请输入一共的顶点数\n");
	scanf("%d", &N);
	printf("请输入顶点\n");
	for (int i = 1; i <= N; ++i)
	{
		char vex;
		scanf("%s", &vex);//用%s
		mp[vex] = i;//为方便操作 这里用map给顶点名赋一个int类型的位置
	}
	for (int i = 1; i <= N; ++i)
	{
		boss_list[i] = i;//初始化 每一个顶点都是独立的顶点
	}

	printf("请输入边数\n");
	scanf("%d", &n);
	printf("接下来请输入开始顶点，结束顶点，权值，用空格隔开\n");
	for (int j = 0; j < n; ++j)
	{
		getchar();//吸收掉多余的回车
		scanf("%c", &start);
		getchar();
		scanf("%c", &end);
		scanf("%d", &weight);

		arc[j].x = mp[start];
		arc[j].y = mp[end];
		arc[j].distance = weight;
		arc[j].start = start;
		arc[j].end = end;


	}
	sort(arc, arc + n, cmp);//对节点进行排序
	for (int i = 0; i < n ; ++i)
	{
		if (findboss(arc[i].x) != findboss(arc[i].y))//因为已经从小到大排序了  只要他们的老板不是同一个 就拉他们入伙
		{
			merge(arc[i].x, arc[i].y);
			printf("%c - %c,%d\n", arc[i].start, arc[i].end, arc[i].distance);
		}
	}


	return 0;
}