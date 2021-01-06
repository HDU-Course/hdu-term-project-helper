#ifndef Huffman_Tree_h
#define Huffman_Tree_h
#endif

#include <stdio.h>
typedef struct
{
	unsigned int weight;
	unsigned int parent, lchild, rchild;
} HTNode, * HuffmanTree; //存储赫夫曼树的结点类型
typedef char * *HuffmanCode;  //用于存储字符集中各个字符相应的赫夫曼编码
void strcpy(char *S1, char *S2) //将字符串S2复制到S1
{
	int i = 0;
	while( S2[i] != '\0' )
	{
		S1[i] = S2[i];
		i++;
	}
	S1[i] = '\0';
}
void Select(HuffmanTree HT, int t, int &s1, int &s2) //在HT[1]到HT[t-1]中找出权值最小的两个S1和S2
{
	int i = 1;
	s1 = s2 = 0;
	HT[0].weight = 65535;
	while( i <= t )  //遍历查找权值最小的结点S1
	{
		if( HT[i].parent == 0 && HT[i].weight < HT[s1].weight )
			s1 = i;
		i++;
	}
	i = 1;
	while( i <= t )  //遍历查找除S1外权值最小的结点S2
	{
		if( i != s1 && HT[i].parent == 0 && HT[i].weight < HT[s2].weight )
			s2 = i;
		i++;
	}
}
int HuffmanCoding( HuffmanTree HT, HuffmanCode HC, int *w, int n) //根据各个字符的权值构造赫夫曼树HT，将对应的赫夫曼编码存储在HC中
{
	int s1, s2, m, i, start;
	unsigned int c, f;
	HTNode *p;
	char *cd;
	if( n <= 1 ) return 0;
	m = 2 * n - 1; //赫夫曼树的总结点树为m
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode)); //申请存储赫夫曼树的空间
	for(p = HT + 1, i = 1; i <= n; ++i, ++p, ++w)  //将各个叶子结点的weight赋以相应的权值，parent,lchild,rchild均赋为0
	{
		p->weight = *(w + 1);
		p->parent = p->lchild = p->rchild = 0;
	}
	for( ; i <= m; ++i, ++p )  //将各个非叶子结点的weight,parent,lchild,rchild均赋为0
	{
		p->weight = p->parent = p->lchild = p->rchild = 0;
	}
	for( i = n + 1; i <= m; ++i )  //构造赫夫曼树，给各个非叶子结点赋值
	{
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i; HT[s2].parent = i;
		HT[i].lchild = s1; HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char *)); //申请空间，用于存储指向存储各个字符相应赫夫曼编码的字符数组的指针
	cd = (char *)malloc(n * sizeof(char)); //申请用于求赫夫曼编码
	cd[n - 1] = '\0'; //编码结束符
	for( i = 1; i <= n; ++i)  //逐个字符求赫夫曼编码
	{
		start = n - 1; //编码在数组cd[]中的最前位置
		for(c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent) //从叶子到根逆向求编码
			if(HT[f].lchild == c)
				cd[ --start ] = '0';
			else
				cd[ --start ] = '1';
		HC[i] = (char *)malloc((n - start) * sizeof(char)); //为第i个字符编码分配空间
		strcpy(HC[i], &cd[start]); //将cd[]数组的start位置到n-1位置复制给HC[i]
	}
	free(cd); //释放空间
	return 1;
}
