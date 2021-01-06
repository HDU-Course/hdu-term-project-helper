#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define MENU_COUNT 5

/*

建立书籍信息的节点
包括ID、姓名、作者、类型号码、出版社、出版时间、价格
*/
typedef struct book
{
	int ID;
	char name[20];
	char author[20];
	int typenum;
	char publish_company[20];
	int publish_time;
	float price;
	struct book *next;

} book;

//全局变量
book *head=NULL;//将链表头指针设置成全局变量，解决函数参数不统一问题
int Book_num;
//函数声明

/*
从 BookData.txt 文件中读取书籍信息 每次打开程序都会自动读取文件中的内容
如果文件不存在 就创建一个文件
*/
int ReadFromFile()
{
	FILE *fp;
	int i;
	book *p = NULL;
	if((fp=fopen("BookData.txt","r+"))==NULL)//如果文件不存在
	{
		fp=fopen("BookData.txt","w");//就新建一个文件
		fprintf(fp,"Book_num:%d",Book_num);//在文件中写入当前书籍的数量
	}
	fscanf(fp,"Book_num:%d",&Book_num);//读取当前书籍的数量 存入临时变量中
	for(i=0; i<Book_num; i++) //读取每一本数的信息
	{
		p = (book*)malloc(sizeof(book));
		fscanf(fp,"\nID:%d",&p->ID);
		fscanf(fp,"\nname:%s",p->name);
		fscanf(fp,"\nauthor:%s",p->author);
		fscanf(fp,"\ntypenum:%d",&p->typenum);
		fscanf(fp,"\npublish_company:%s",p->publish_company);
		fscanf(fp,"\npublish_time:%d",&p->publish_time);
		fscanf(fp,"\nprice:%f",&p->price);
		p->next = head;
		head = p;//更新头指针

	}
	fclose(fp);
	return 0;
}

void menu()
{
	printf("\n\n\t\t\t\t 图书管理系统\n");
	printf("\t\t*************************************************\n");
	printf("\t\t*\t\t 1 -------- 显示图书信息\t*\n");
	printf("\t\t*\t\t 2 -------- 录入图书信息\t*\n");
	printf("\t\t*\t\t 3 -------- 查询图书信息\t*\n");
	printf("\t\t*\t\t 4 -------- 删除图书信息\t*\n");
	printf("\t\t*\t\t 5 -------- 修改图书信息\t*\n");
	printf("\t\t*\t\t 0 -------- 退出        \t*\n");
	printf("\t\t*************************************************\n");
}

/*

 实现退出程序功能，在退出之前将建立好的链表中每个节点的信息都
 存到文件中
 
*/
void quit()
{
	book *p = NULL;
	FILE *fpw;
	system("cls");
	fpw = fopen("BookData.txt","w");
	fprintf(fpw,"Book_num:%d\n",Book_num);
	for(p=head; p!=NULL; p=p->next)
	{
		fprintf(fpw,"ID:%d\n",p->ID);
		fprintf(fpw,"name:%s\n",p->name);
		fprintf(fpw,"author:%s\n",p->author);
		fprintf(fpw,"typenum:%d\n",p->typenum);
		fprintf(fpw,"publish_company:%s\n",p->publish_company);
		fprintf(fpw,"publish_time:%d\n",p->publish_time);
		fprintf(fpw,"price:%.2f\n",p->price);
		fprintf(fpw,"\n");
	}
	printf("\n");
	printf("感谢使用本图书信息管理系统!\n") ;
	printf("\n");
	fclose(fpw);
	exit(0);
}

void add_Book()
{
	book *p = NULL;
	FILE *fpw;
	p = (book*)malloc(sizeof(book));
	system("cls");
	printf(">请输入ID：");
	scanf("%d",&p->ID);
	printf(">请输入书名：");
	scanf("%s",p->name);
	printf(">请输入作者名：");
	scanf("%s",p->author);
	printf(">请输入分类号：");
	scanf("%d",&p->typenum);
	printf(">请输入出版单位：");
	scanf("%s",p->publish_company);
	printf(">请输入出版时间：");
	scanf("%d",&p->publish_time);
	printf(">请输入书本价格：");
	scanf("%f",&p->price);
	show_oneBook(p);
	int x;
	printf(">确认录入此图书？ 是（1）or 否（0）\n");
	scanf("%d",&x);
	switch(x)
	{
		case 1:
			{
				p->next = head;
				head = p;
				Book_num++;
				printf("正在添加请稍等");
				Sleep(500);
				printf(".");
				Sleep(500);
				printf(".");
				Sleep(500);
				printf(".\n");
				printf("录入成功！按任意键继续...\n");
				fflush(stdin);
				getchar();
				break;
			}
		case 0:
			{
				printf("取消录入！按任意键继续...\n");
				fflush(stdin);
				getchar();
				break;
			}
		default:
			{
				printf("输入错误！请重新输入！\n") ;
				fflush(stdin);
				getchar();
				add_Book();
				return;
			}
	}

}

/*

打印一本书的信息，便于查看输入的书籍信息是否符合要求

*/

void show_oneBook(book *p)
{
	printf("ID：%d\n",p->ID);
	printf("书名：%s\n",p->name);
	printf("作者名：%s\n",p->author);
	printf("分类号：%d\n",p->typenum);
	printf("出版单位：%s\n",p->publish_company);
	printf("出版时间：%d\n",p->publish_time);
	printf("书本价格：%.2f\n",p->price);
}

/*

打印所有的书籍信息

*/

void show_allBooks()
{
	printf("正在查询所有书籍请稍等");
	Sleep(500);
	printf(".");
	Sleep(500);
	printf(".");
	Sleep(500);
	printf(".\n");

	if(head==NULL)
	{
		puts("无图书信息，请手动录入。\n按任意键继续...");
		fflush(stdin);
		getchar();
	}
	else
	{
		printf("当前有%d本书\n",Book_num);
		book *p = head;
		while(p!=NULL)
		{
			show_oneBook(p);
			puts("");
			p = p->next;
		}
		puts("按任意键继续...");
		fflush(stdin);
		getchar();
	}

}
/*

按需求查找书籍，当前提供的方式有

1.按照书名查找
2.按照作者名查找

*/
void search_Book()
{
	system("cls");
	puts(">按书名查找请按 1\n>按作者名查找请按 2\n>返回请按3");
	int x,found=0;
	char search[20];
	scanf("%d",&x);
	system("cls");
	book *p=head;
	switch(x)
	{
		case 1:
			{
				puts(">请输入要查找的书名:");
				scanf("%s",search);
				puts("");
				while(p!=NULL)
				{
					if(strcmp(search,p->name)==0)
					{
						found=1;
						
						printf("正在查找");
						Sleep(500);
						printf(".");
						Sleep(500);
						printf(".");
						Sleep(500);
						printf(".\n");
						show_oneBook(p);
						puts("");
					}
					p = p->next;
				}
				break;
			}
		case 2:
			{
				puts(">请输入要查找的作者名:");
				scanf("%s",search);
				puts("");
				while(p!=NULL)
				{
					if(strcmp(search,p->author)==0)
					{
						found=1;
						printf("正在查找");
						Sleep(500);
						printf(".");
						Sleep(500);
						printf(".");
						Sleep(500);
						printf(".\n");
						show_oneBook(p);
						puts("");
					}
					p = p->next;
				}
				break;
			}
		case 3:
			{
				found = 3;
				break;
			}

		default:
			{
				printf("输入错误！请重新搜索！\n") ;
				found = 2;
				break;
			}
	}
	if(found==1)	puts("已找到以上图书，按任意键继续...");
	if(found==0) 	puts("你要查找的图书信息不存在!");
	if(found==2)	search_Book();
	if(found==3)    return;
	fflush(stdin);
	getchar();
}

/*

根据输入的书名删除此书信息
对于重名的书本也做了处理，每本都会询问是否要删除 

*/
void delete_Book()
{
	system("cls");
	int found=0;
	char name[20];
	book *p=head,*pold;//两个临时变量 pold表示前一个节点 
	puts(">请输入要删除的书名：");
	scanf("%s",name);
	while(p!=NULL)
	{
		if(strcmp(name,p->name)==0)//如果找到这本书了
		{
			found = 1;//标记为找到了
			show_oneBook(p);//展示一下这本书
			puts("");
			puts(">您确定要删除这本书吗 是（1）or 否（0）");
			int choice;
			scanf("%d",&choice);
			if(choice)
			{
				if(p==head)//如果要删掉的是第一本书 
				{
					head = head->next;
					free(p);
					p = head; 
				}
				else
				{
					pold->next = p->next;
					free(p);
					p = pold->next;
				}
				Book_num--;
				printf("正在删除请稍等");
				Sleep(500);
				printf(".");
				Sleep(500);
				printf(".");
				Sleep(500);
				printf(".\n");
				printf(">删除成功！\n\n");
				
			}
			else break;
		}
		else//如果还没找到这本书，就找下一个节点
		{
			pold = p;
			p = p->next;
		}
	}
	if(found==0)	puts("删除失败，未找到此图书！");
	puts("按任意键继续...");
	fflush(stdin);
	getchar();

}

/*

更新图书的信息

*/
void update_Book()
{
	system("cls");
	book *p = head;
	char name[20];
	int x,found=0;
	printf(">请输入要修改的图书的书名：");
	scanf("%s",name);
	while(p!=NULL)
	{
		if(strcmp(name,p->name)==0)
		{
			found = 1;
			show_oneBook(p);
			printf(">是否确定修改？ 是（1）or 否（0）");
			scanf("%d",&x);
			if(x)
			{
				system("cls");
				printf("**********请重新输入信息*********\n");
				printf(">请输入ID：");
				scanf("%d",&p->ID);
				printf(">请输入书名：");
				scanf("%s",p->name);
				printf(">请输入作者名：");
				scanf("%s",p->author);
				printf(">请输入分类号：");
				scanf("%d",&p->typenum);
				printf(">请输入出版单位：");
				scanf("%s",p->publish_company);
				printf(">请输入出版时间：");
				scanf("%d",&p->publish_time);
				printf(">请输入书本价格：");
				scanf("%f",&p->price);
				printf("正在更新请稍等");
				Sleep(500);
				printf(".");
				Sleep(500);
				printf(".");
				Sleep(500);
				printf(".\n");
				printf("\n>提醒：修改成功!\n");
			}
		}
		p = p->next;
	}
	if(found==0)	printf(">提醒：没有您要修改的信息！\n");
	puts("按任意键继续...");
	fflush(stdin);
	getchar();
}

