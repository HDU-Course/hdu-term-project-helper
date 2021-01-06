/*
* @Author: TD21forever
* @Date:   2018-12-01 17:35:43
* @Last Modified by:   TD21forever
* @Last Modified time: 2018-12-04 14:11:55
*/

#include <stdio.h>
#include <stdlib.h>
#include "Huffman_Tree.h"
#define Yes 1 //当程序已经调用过初始化赫夫曼树的InitHuff_T()函数，或已从htfTree文件读取过，则将Init_Mode置为Yes，否则为No
#define No 0
void InitHuff_T( HuffmanTree &HT, HuffmanCode &HC, char ch[], int &n ) //初始化赫夫曼数，要求用户输入字符和相应权值
{
	int i = 1, w[100], tem, j;
	char a[20];
	FILE *save;
	printf("请输入编码字符集的大小n:");
	scanf("%d", &n); //获取用户输入的字符集个数
	while( i <= n )  //获取用户输入的字符和相应权值，分别存储在ch[]和w[]数组中
	{
		printf("请输入第%d个字符和该字符的权值w:", i);
		fflush(stdin);//防止多余的回车干扰
		scanf("%c%d", &ch[i], &w[i]);//字符集都存在了ch里 权重存在了w里
		i++;
	}
	ch[i] = '\0';
	HuffmanCoding(HT, HC, w, n); //根据用户的输入，生成赫夫曼数及各个字符相应的赫夫曼编码，分别存在HT树和HC中
	if(( save = fopen("htfTree", "w")) == NULL ) //打开用于存储赫夫曼树的文件
	{
		printf("Open file fail......\n");
		exit(0);
	}
	tem = n; //接下来的14行是将字符集大小转换成字符形式写入到文件中
	j = 0;
	while( tem != 0 )//n有几位
	{
		tem = tem / 10;
		j++;
	}
	tem = n;
	a[j] = '\0';
	while( tem != 0 )
	{
		a[j - 1] = (char)(tem % 10 + 48);//每一位都转换成为字符 100->‘100’
		tem = tem / 10;
		j--;
	}
	fputs(a, save);
	printf("%d\n", n); //向屏幕输出字符集大小n
	fputc('\n', save);
	for( i = 1; i <= n; i++ )  //分别向文件和屏幕输出各个字符和相应的赫夫曼编码
	{
		fputc(ch[i], save); printf("%c\t", ch[i]);//字符
		fputc('\t', save);
		fputs(HC[i], save); printf("%s\n", HC[i]);//哈夫曼编码
		fputc('\n', save);
	}
	for(i = 1; i <= 2 * n - 1; i++ )  //将赫夫曼树各个结点的parent,lchild,rchild分别写入到文件中
	{
		tem = HT[i].parent; //将i结点的parent转换成字符并写入到文件中
		if(tem == 0)
		{
			fputc(tem + 48, save);
			fputc(' ', save);
		}
		else
		{
			j = 0;
			while( tem != 0 )
			{
				tem = tem / 10;
				j++;
			}
			tem = HT[i].parent;
			a[j] = '\0';
			while( tem != 0 )
			{
				a[j - 1] = (char)(tem % 10 + 48);
				tem = tem / 10;
				j--;
			}
			fputs(a, save);
			fputc(' ', save);
		}
		tem = HT[i].lchild; //将i结点的lchild转换成字符并写入到文件中
		if(tem == 0)
		{
			fputc(tem + 48, save);
			fputc(' ', save);
		}
		else
		{
			j = 0;
			while( tem != 0 )
			{
				tem = tem / 10;
				j++;
			}
			tem = HT[i].lchild;
			a[j] = '\0';
			while( tem != 0 )
			{
				a[j - 1] = (char)(tem % 10 + 48);
				tem = tem / 10;
				j--;
			}
			fputs(a, save);
			fputc(' ', save);
		}
		tem = HT[i].rchild; //将i结点的rchild转换成字符并写入到文件中
		if(tem == 0)
		{
			fputc(tem + 48, save);
			fputc('\n', save);
		}
		else
		{
			j = 0;
			while( tem != 0 )
			{
				tem = tem / 10;
				j++;
			}
			tem = HT[i].rchild;
			a[j] = '\0';
			while( tem != 0 )
			{
				a[j - 1] = (char)(tem % 10 + 48);
				tem = tem / 10;
				j--;
			}
			fputs(a, save);
			fputc('\n', save);
		}
	}
	fclose(save);
}
void Encoding(HuffmanTree &HT, HuffmanCode &HC, char ch[])  //根据赫夫曼编码将用户指定的文件中的字符编成相应的编码,并将所得编码存储到用户指定文件
{
	FILE *ToBeTran, *CodeFile;
	char ToBeTran_Name[100], CodeFile_Name[100]; //存储用户指定文件的文件名
	int i;
	char c;
	printf("请输入所要进行编码的文件的文件名:");
	scanf("%s", ToBeTran_Name); //获得所要进行编码的文件的文件名
	if(( ToBeTran = fopen(ToBeTran_Name, "r")) == NULL ) //打开文件
	{
		printf("Open file fail......\n");
		exit(0);
	}
	printf("请输入编码后编码表示的信息所存储到的文件的文件名:");
	scanf("%s", CodeFile_Name); //获得编码后编码表示的信息所存储到的文件的文件名
	if(( CodeFile = fopen(CodeFile_Name, "w")) == NULL ) //打开文件
	{
		printf("Open file fail......\n");
		exit(0);
	}
	c = fgetc(ToBeTran); //从文件读取一个字符
	while( c != EOF )  //对文件中的各个字符进行编码，直至文件结尾
	{
		i = 1;
		while( c != ch[i] && ch[i] != '\0' ) //在ch[]数组中查找从文件读取的字符
			i++;
		if(ch[i] == '\0')  //未找到，c不在ch[]数组中，c无法被识别，程序出错，退出
		{
			printf("字符%c无法识别，程序将退出。\n", c);
			exit(0);
		}
		fputs(HC[i], CodeFile); //若找到，则将c相应的赫夫曼编码写入到文件中
		printf("%s", HC[i]); //将c相应的赫夫曼编码输出到屏幕
		c = fgetc(ToBeTran); //读入文件中的下一个字符
	}
	printf("\n");
	fclose(ToBeTran);
	fclose(CodeFile);
}
void Decoding(HuffmanTree HT, char ch[], int n)   //对指定的存储由赫夫曼编码表示的信息的文件进行译码，翻译成相应的字符表示，并存储到指定文件
{
	int p, i = 1;
	char code[1000], c;
	char CodeFile_Name[100], TextFile_Name[100]; //存储用户指定文件的文件名
	p = 2 * n - 1;
	FILE *CodeFile, *TextFile;
	printf("请输入所要译的文件名:");
	scanf("%s", CodeFile_Name); //获得所要译的文件的文件名
	if(( CodeFile = fopen(CodeFile_Name, "r")) == NULL ) //打开文件
	{
		printf("Open file fail......\n");
		exit(0);
	}
	printf("请输入译后的字符存储到的文件的文件名:");
	scanf("%s", TextFile_Name); //获得译后的字符存储到的文件的文件名
	if(( TextFile = fopen(TextFile_Name, "w")) == NULL ) //打开文件
	{
		printf("Open file fail......\n");
		exit(0);
	}
	c = fgetc(CodeFile);
	while( c != EOF )
	{
		code[i] = c;
		i++;
		c = fgetc(CodeFile);
	}//从文件中读取已经编码好的代码
	code[i] = '\0'; //从文件读取字符，存储在code[]数组中
	i = 1;
	while ( code[i] != '\0' && p != 0 )  //对数组code[]中的赫夫曼编码进行译码
	{
		if ( code[i] == '0' )
			p = HT[p].lchild; //进入左分支
		else
			p = HT[p].rchild; //进入右分支
		if (!HT[p].lchild && !HT[p].rchild) //进入叶子结点
		{
			fputc(ch[p], TextFile); //将相应的字符写入到文件中
			printf("%c", ch[p]); //将相应的字符输出到屏幕
			p = 2 * n - 1; //重新从树根出发进行译码
		}
		i++;
	}
	printf("\n");
}
void ReadHuff_T( HuffmanTree &HT, HuffmanCode &HC, char ch[], int &n)  //从文件读取赫夫曼树
{
	FILE *htfTree;
	char c[100], ch1;
	int i, j, t;
	if(( htfTree = fopen("htfTree", "r")) == NULL ) //打开存有赫夫曼树信息的文件
	{
		printf("Open file fail......\n");
		exit(0);
	}
	fgets(c, 10, htfTree); //获取赫夫曼树叶子结点个数的字符串表示形式
	i = 0; //以下6行将字符串形式转换成整数形式
	while( c[i] != '\n' )
		i++;
	n = 0;
	for( j = 0; j < i; j++ )
		n = 10 * n + c[j] - '0'; //求出叶子结点数n
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char *)); //申请HC空间
	HT = (HuffmanTree)malloc((2 * n) * sizeof(HTNode)); //申请赫夫曼树存储空间
	i = 1;
	while( i <= n )
	{
		ch[i] = fgetc(htfTree); //读取字符集中的一个字符
		HC[i] = (char *)malloc((10) * sizeof(char)); //申请用于存储读取到的字符集中的字符的赫夫曼编码的空间
		fgetc(htfTree); //将‘\t’输出
		ch1 = fgetc(htfTree); //读取赫夫曼编码，存储在相应的HC[i][]数组里
		int j = 0;
		while( ch1 != '\n' )
		{
			HC[i][j] = ch1;
			j++;
			ch1 = fgetc(htfTree);
		}
		HC[i][j] = '\0';
		i++;
	}
	ch[i] = '\0';
	i = 0;
	while( i < 2 * n - 1 )  //读取赫夫曼树的各个结点的parent,lchild,rchild.并赋值到赫夫曼树HT中
	{
		ch1 = fgetc(htfTree); //读取parent的字符串形式,存储在c[]中，并将其转换成整数形式，赋给HT[i].parent
		j = 0;
		while( ch1 != ' ' )
		{
			c[j] = ch1;
			j++;
			ch1 = fgetc(htfTree);
		}
		HT[i + 1].parent = 0;
		for( t = 0; t < j; t++ )
			HT[i + 1].parent = 10 * HT[i + 1].parent + c[t] - '0';
		ch1 = fgetc(htfTree); //读取lchild的字符串形式，并将其转换成整数形式，赋给HT[i].lchild
		j = 0;
		while( ch1 != ' ' )
		{
			c[j] = ch1;
			j++;
			ch1 = fgetc(htfTree);
		}
		HT[i + 1].lchild = 0;
		for( t = 0; t < j; t++ )
			HT[i + 1].lchild = 10 * HT[i + 1].lchild + c[t] - '0';
		ch1 = fgetc(htfTree); //读取rchild的字符串形式，并将其转换成整数形式，赋给HT[i].rchild
		j = 0;
		while( ch1 != '\n' )
		{
			c[j] = ch1;
			j++;
			ch1 = fgetc(htfTree);
		}
		HT[i + 1].rchild = 0;
		for( t = 0; t < j; t++ )
			HT[i + 1].rchild = 10 * HT[i + 1].rchild + c[t] - '0';
		i++;
	}
}
int main()
{
	HuffmanTree HT;
	HuffmanCode HC;
	char ch[100]; //用于存储字符集
	int n, Init_Mode = No; //n为字符集的大小，Init_Mode = No 表示内存中没有赫夫曼树的信息
	char mode; //让用户选择不同的操作
	printf("请输入你要选择的功能\n");
	printf("\t\tI -- 初始化\t\tE -- 编码\n");
	printf("\t\tD -- 译码 \t\tQ -- 退出程序\n");
	scanf("%c", &mode); //获得用户选择的操作
	while( mode != 'Q' && mode != 'q' )  //当用户输入不为Q或q时，执行相应操作
	{
		switch(mode)
		{
		case 'I' :
			InitHuff_T(HT, HC, ch, n);
			Init_Mode = Yes;
			break;
		case 'i' :
			InitHuff_T(HT, HC, ch, n);
			Init_Mode = Yes;
			break;
		case 'E' :
			if( No == Init_Mode )
				ReadHuff_T(HT, HC, ch, n);
			Encoding(HT, HC, ch);
			Init_Mode = Yes;
			break;
		case 'e' :
			if( No == Init_Mode )
				ReadHuff_T(HT, HC, ch, n);
			Encoding(HT, HC, ch);
			Init_Mode = Yes;
			break;
		case 'D' :
			if( No == Init_Mode )
				ReadHuff_T(HT, HC, ch, n);
			Decoding(HT, ch, n);
			Init_Mode = Yes;
			break;
		case 'd' :
			if( No == Init_Mode )
				ReadHuff_T(HT, HC, ch, n);
			Decoding(HT, ch, n);
			Init_Mode = Yes;
		default :
			printf("您的输入有错，请重新选择.\n");
		}
		printf("请输入你要选择的功能\n");
		printf("\tI -- 初始化\tE -- 编码\n");
		printf("\tD -- 译码 \tQ -- 退出程序\n");
		fflush(stdin);
		scanf("%c", &mode); //让用户继续选择相应的操作，直至用户选择退出
	}
	return 0;
}