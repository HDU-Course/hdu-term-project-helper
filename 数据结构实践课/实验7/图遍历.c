/*
* @Author: TD21forever
* @Date:   2018-11-20 14:44:29
* @Last Modified by:   TD21forever
* @Last Modified time: 2021-01-06 01:50:42
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAX_VERTEX_NUM 100
typedef int Status;
typedef enum {unvisited, isvisited} VisitIf;
typedef struct EBox
{
	VisitIf mark;
	int ivex;
	int jvex;
	struct EBox *ilink;
	struct EBox *jlink;

} EBox;
typedef struct VexBox
{
	char data[20];
	EBox *firstarc;
} VexBox;

typedef struct
{
	VexBox adjmulist[MAX_VERTEX_NUM];
	int vexnum;
	int arcnum;
} AMLGraph;

int visited[MAX_VERTEX_NUM];

Status LocateVex(AMLGraph *G, char *v)
{
	for (int i = 0; i < G->vexnum; ++i)
	{
		if (strcmp(G->adjmulist[i].data,v) == 0)
		{
			return i;
		}
	}
	return -1;
}
Status CreateGraph(AMLGraph *G)
{
	char va[200];
	char vb[200];
	EBox *p;
	int pos_i;
	int pos_j;
	printf("please enter vexnum and arcnum:");
	scanf("%d%d", &(G->vexnum), &(G->arcnum));
	for (int i = 0; i < G->vexnum; ++i)
	{
		printf("�������%d������\n",i+1);
		scanf("%s", G->adjmulist[i].data); //�ȸ������ֵ
		G->adjmulist[i].firstarc = NULL;
	}

	for (int k = 0; k < G->arcnum; ++k)
	{
		printf("�������%d����\n",k+1 );
		scanf("%s %s", va, vb); //�����������ڱߵĵ�
		pos_i = LocateVex(G, va); //�ҵ�������±�
		pos_j = LocateVex(G, vb);
		p = (EBox *)malloc(sizeof(EBox));
		p->ivex = pos_i;
		p->jvex = pos_j;
		p->mark = unvisited;
		// ÿ�β����½ڵ㶼��������ı�ͷ����
		p->ilink = G->adjmulist[pos_i].firstarc;
		p->jlink = G->adjmulist[pos_j].firstarc;
		G->adjmulist[pos_i].firstarc = p;
		G->adjmulist[pos_j].firstarc = p;

	}
	return OK;
}
void DFS(AMLGraph *G, int position)
{
	visited[position] = TRUE;
	EBox *p;
	int j;
	printf("%s ", G->adjmulist[position].data);
	p = G->adjmulist[position].firstarc;
	while(p != NULL)
	{
		j = p->ivex == position ? p->jvex : p->ivex;
		if(!visited[j])
			DFS(G, j);
		p = p->ivex == position ? p->ilink : p->jlink ;
	}
}


Status DFSTraverse(AMLGraph *G, int j)
{
	// int i;

	for(int i = 0; i < G->vexnum ; i++)
		visited[i] = FALSE;
	//ѭ����Ϊ��֤ÿ�����㶼�ܱ����ʵ�
	// for(i = 0; i < G->vexnum; i++)
	// 	if(!visited[i])
	DFS(G, j);
	return OK;

}

int main(int argc, char const *argv[])
{
	AMLGraph g;
	CreateGraph(&g);
	printf("��ָ�����\n");
	char j[20];
	scanf("%s", j);
	int i = LocateVex(&g,j);
	DFSTraverse(&g,i);
	return 0;
}


