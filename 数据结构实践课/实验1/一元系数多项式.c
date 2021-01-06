/*
* @Author: TD21forever
* @Date:   2018-11-02 09:54:26
* @Last Modified by:   TD21forever
* @Last Modified time: 2018-11-05 23:14:52
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct Node
{
	double xishu;
	int zhishu;
	struct Node *next;
} Node;
int n;
// typedef Node* PolyNomial1;
void print(Node *Head);

Node *create()//返回的是一个指针，这个指针是指向结构体的
{
	Node *Head;//创建一个头结点

	Head = (Node *)malloc(sizeof(Node));
	Head -> xishu = 0;//给头结点赋值初始化
	Head -> zhishu = 0;
	Head -> next = NULL;
	Node *p, *q; //p用来存新的结点，q用来保存当前结点
	q = Head;
	printf("请先输入多项式的项数n\n" );
	scanf("%d", &n);
	if (n == 0)
	{
		p = (Node *)malloc(sizeof(Node));
		p->xishu = 0;
		p->zhishu = 0;
		p->next = NULL;
		q->next = p;
		return Head;
	}
	for (int i = 1; i <= n; ++i)
	{
		p = (Node *)malloc(sizeof(Node));
		printf("请输入第%d项的系数和指数，用空格隔开\n", i);
		scanf("%lf %d", &(p->xishu), &(p->zhishu));
		p->next = NULL;
		q->next = p;//当前节点和新创建的节点连起来
		q = p;//更新一下当前的节点
	}
	return Head;//返回头结点的指针
}


Node *sort(Node *Head) //冒泡排序
{
	if (Head->next == NULL)
	{
		return Head;
	}
	Node *pre, *cur, *next, *head, *temp, *end;
	head = Head;
	end = NULL;
	while(head->next != end)
	{
		for (pre = head, cur = pre->next, next = cur->next; next != end; pre = pre->next, cur = cur->next, next = next->next)
		{
			if (cur->zhishu < next->zhishu)//小的往后沉  节点做交换 指向节点的指针也交换
			{
				cur->next = next->next;
				pre->next = next;//这里犯错了 本来是 pre->next = cur->next;
				next->next = cur;
				temp = next;
				next = cur;
				cur = temp;
			}
		}
		end = cur;
	}
	return head;

}
Node *add(Node *A, Node *B) //设计了一个temp 一个mark 假如从A->B 那么mark先到B上 temp->next = B; temp = mark;通过temp和mark，把两组多项式从大到小串起来。
//mark 追着 a 而temp追着mark;
{
	Node *P = sort(A);
	Node *Q = sort(B);

	Node *res = P;
	Node *temp = P;
	Node *mark;

	Node *a, *b;

	a = P->next;
	b = Q->next;

	while(a != NULL && b != NULL)
	{
		if (a->zhishu < b->zhishu)
		{
			mark = b;//因为最后是指数降序，给指数大的做标记，指针后移
			b = b->next;
		}
		else if (a->zhishu == b->zhishu)//如果相等，系数相加
		{
			a->xishu = (a->xishu) + (b->xishu);
			mark = a;
			a = a->next;//两个都后移
			b = b->next;
		}
		else
		{
			mark = a;
			a = a->next;
		}
		if (mark->xishu != 0)//做连接，把系数不是零的都连起来
		{
			temp->next = mark;
			temp = mark;
		}
	}
	if (a == NULL) //若果a已经到头了 那么a就接到b上
	{
		a = b;
	}
	while(a)//这个是为什么来着
	{
		mark = a;
		a = a->next;
		temp->next = mark;
		temp = mark;
	}
	return res;
}

int count(Node *a)//输出的n，
{
	Node *b = a;
	int cnt = 0;
	while(b != NULL)
	{
		if (b->xishu != 0)//系数不能是0
		{

			cnt++;
		}
		b = b->next;
	}
	return cnt;

}

Node *repeat(Node *A)//先把多项式里指数相同的项合并
{
	Node *p, *head;
	head = A;
	p = head->next;
	Node *q;
	q = p->next;

	while(p->next != NULL)
	{

		while(q != NULL)
		{
			if (p->zhishu == q->zhishu)
			{
				p->xishu += q->xishu;
				p->next	= q->next;
				free(q);

			}
			q = q->next;
		}

		p = p->next;
		q = p->next;
	}
	return head;
}
Node *sub(Node *A, Node *B)//减法  基本与加法同理
{
	Node *P = sort(A);
	Node *Q = sort(B);

	Node *res = P;
	Node *temp = P;
	Node *mark;

	Node *a, *b;

	a = P->next;
	b = Q->next;

	while(a != NULL && b != NULL)
	{
		if (a->zhishu < b->zhishu)
		{
			mark = b;
			mark->xishu = (-1) * (mark->xishu);//0减去一个数的时候要注意下
			b = b->next;
		}
		else if (a->zhishu == b->zhishu)
		{

			a->xishu = a->xishu - b->xishu;
			mark = a;
			a = a->next;
			b = b->next;
		}
		else
		{
			mark = a;
			a = a->next;
		}
		if (mark->xishu != 0)
		{
			temp->next = mark;
			temp = mark;
		}
	}
	if (a == NULL) //若果a已经到头了 那么a就接到b上
	{
		a = b;
		Node *temp = a;
		while(temp != NULL)
		{
			temp->xishu *= -1;
			temp = temp->next;
		}
	}
	while(a)
	{
		mark = a;
		a = a->next;
		temp->next = mark;
		temp = mark;
	}

	return res;
}


void print(Node *Head)
{
	int cnt = count(Head);
	printf("%d,", cnt);
	Node *p = sort(Head);//先排下序
	p = Head->next;
	if (p == NULL)
	{
		printf("0");
		return;
	}
	else if (p->zhishu == 0)//如果第一个数的指数为零，直接输出系数
	{
		printf("%.2lf,", p->xishu);
	}
	else if(p->xishu == 0)//如果第一个数的系数为零，指针向后移
	{

		p = p->next;
	}
	else//除此之外，正常输出即可
	{
		printf("%.2lf,%d,", p->xishu, p->zhishu);
		p = p->next;

	}

	while(p != NULL)
	{
		if (p->xishu == 0 && p->next == NULL)//如果整个多项式结果为零，直接返回。
		{
			printf("\n");
			return;
		}
		printf("%.2lf,%d,", p->xishu, p->zhishu);
		p = p->next;
	}
	printf("\n");

}

void value_x(Node *Head)//计算多项式在x处的值
{
	Node *p = Head->next;
	printf("x为多少呢\n");
	double x;
	double sum = 0;
	scanf("%lf", &x);
	while(p != NULL)
	{
		sum += (p->xishu) * (pow(x, p->zhishu));
		p = p->next;
	}
	printf("%lf\n", sum);
}

void advance_print(Node *Head)//选做题，输出语义化的结果
{
	Node *p = sort(Head);//先排下序
	p = Head->next;
	if (p == NULL)
	{
		printf("0");
		return;
	}
	else if (p->zhishu == 0)//如果第一个数的指数为零，直接输出系数
	{
		printf("%.2lf,", p->xishu);
	}
	else if(p->xishu == 0)//如果第一个数的系数为零，指针向后移
	{
		p = p->next;
	}
	else
	{
		if (p->xishu == 1)
		{
			printf("x^%d", p->zhishu);

		}
		else if (p->xishu == -1)
		{
			printf("-x^%d", p->zhishu);
		}
		else
		{
			printf("%.2lf*x^%d", p->xishu, p->zhishu);
		}
		p = p->next;

	}
	while(p != NULL)
	{
		if (p->xishu == 0 && p->next == NULL)//如果最后一个数是零
		{
			printf("\n");

			return;
		}
		if (p->xishu > 0)
		{
			printf("+");
		}
		if (p->xishu == 1 && p->zhishu != 0 )
		{
			printf("x^%d", p->zhishu);

		}
		else if (p->xishu == -1)
		{
			printf("-x^%d", p->zhishu);
		}
		else if (p->zhishu == 0)
		{
			printf("%.2lf\n", p->xishu);
		}
		else
		{
			printf("%.2lf*x^%d", p->xishu, p->zhishu);
		}

		p = p->next;
	}
	printf("\n");
}
int main()
{
	printf("   *******************************************************\n");
	printf("   *                   多项式操作程序                     *\n");
	printf("   *                                                     *\n");
	printf("   *       1:输入多项式             2:输出多项式(标准版)   *\n");
	printf("   *                                                     *\n");
	printf("   *       3:代入x的值计算a         4:代入x的值计算b       *\n");
	printf("   *                                                     *\n");
	printf("   *       5:输出a+b                6:输出a-b             *\n");
	printf("   *                                                     *\n");
	printf("   *       7.加强版输出              8:退出程序            *\n");
	printf("   *                                                      *\n");
	printf("   *******************************************************\n");

	while(1)
	{
		printf("你的选择是\n");
		Node *A, *B, *res;
		Node *addA, *addB;
		Node *subA, *subB;

		int choice;
		scanf("%d", &choice);
		switch(choice)
		{
		case 1: printf("您的选择是1--->输入多项式\n"); printf("请根据提示输入链表A的数据\n"); A = create(); addA = A, subA = A;
			printf("请根据提示输入链表B的数据\n"); B = create(); addB = B, subB = B; break;

		case 2: printf("您的选择是2--->标准输出多项式a和b\n"); printf("A\n"); print(A); printf("B\n"); print(B); break;
		case 3: printf("您的选择是3--->代入x的值计算a\n"); value_x(A); break;
		case 4: printf("您的选择是4--->代入x的值计算b\n"); value_x(B); break;
		case 5: printf("您的选择是5--->输出a+b\n"); addA = repeat(A); addB = repeat(B); res = add(addA, addB); advance_print(res); printf("欢迎下次使用\n"); exit(0);
		case 6: printf("您的选择是6--->输出a-b\n"); subA = repeat(A); subB = repeat(B); res = sub(subA, subB); advance_print(res); printf("欢迎下次使用\n"); exit(0);
		case 7: printf("您的选择是7--->输出表达式\n"); printf("A\n"); advance_print(A); printf("B\n"); advance_print(B); break;
		case 8: printf("您的选择是8--->退出\n"); printf("bye~"); exit(0);
		default: printf("非法输入，请重新选择\n"); break;
		}

	}
}

