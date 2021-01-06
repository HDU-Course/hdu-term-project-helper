#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define MENU_COUNT 5

/*

�����鼮��Ϣ�Ľڵ�
����ID�����������ߡ����ͺ��롢�����硢����ʱ�䡢�۸�
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

//ȫ�ֱ���
book *head=NULL;//������ͷָ�����ó�ȫ�ֱ������������������ͳһ����
int Book_num;
//��������

/*
�� BookData.txt �ļ��ж�ȡ�鼮��Ϣ ÿ�δ򿪳��򶼻��Զ���ȡ�ļ��е�����
����ļ������� �ʹ���һ���ļ�
*/
int ReadFromFile()
{
	FILE *fp;
	int i;
	book *p = NULL;
	if((fp=fopen("BookData.txt","r+"))==NULL)//����ļ�������
	{
		fp=fopen("BookData.txt","w");//���½�һ���ļ�
		fprintf(fp,"Book_num:%d",Book_num);//���ļ���д�뵱ǰ�鼮������
	}
	fscanf(fp,"Book_num:%d",&Book_num);//��ȡ��ǰ�鼮������ ������ʱ������
	for(i=0; i<Book_num; i++) //��ȡÿһ��������Ϣ
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
		head = p;//����ͷָ��

	}
	fclose(fp);
	return 0;
}

void menu()
{
	printf("\n\n\t\t\t\t ͼ�����ϵͳ\n");
	printf("\t\t*************************************************\n");
	printf("\t\t*\t\t 1 -------- ��ʾͼ����Ϣ\t*\n");
	printf("\t\t*\t\t 2 -------- ¼��ͼ����Ϣ\t*\n");
	printf("\t\t*\t\t 3 -------- ��ѯͼ����Ϣ\t*\n");
	printf("\t\t*\t\t 4 -------- ɾ��ͼ����Ϣ\t*\n");
	printf("\t\t*\t\t 5 -------- �޸�ͼ����Ϣ\t*\n");
	printf("\t\t*\t\t 0 -------- �˳�        \t*\n");
	printf("\t\t*************************************************\n");
}

/*

 ʵ���˳������ܣ����˳�֮ǰ�������õ�������ÿ���ڵ����Ϣ��
 �浽�ļ���
 
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
	printf("��лʹ�ñ�ͼ����Ϣ����ϵͳ!\n") ;
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
	printf(">������ID��");
	scanf("%d",&p->ID);
	printf(">������������");
	scanf("%s",p->name);
	printf(">��������������");
	scanf("%s",p->author);
	printf(">���������ţ�");
	scanf("%d",&p->typenum);
	printf(">��������浥λ��");
	scanf("%s",p->publish_company);
	printf(">���������ʱ�䣺");
	scanf("%d",&p->publish_time);
	printf(">�������鱾�۸�");
	scanf("%f",&p->price);
	show_oneBook(p);
	int x;
	printf(">ȷ��¼���ͼ�飿 �ǣ�1��or ��0��\n");
	scanf("%d",&x);
	switch(x)
	{
		case 1:
			{
				p->next = head;
				head = p;
				Book_num++;
				printf("����������Ե�");
				Sleep(500);
				printf(".");
				Sleep(500);
				printf(".");
				Sleep(500);
				printf(".\n");
				printf("¼��ɹ��������������...\n");
				fflush(stdin);
				getchar();
				break;
			}
		case 0:
			{
				printf("ȡ��¼�룡�����������...\n");
				fflush(stdin);
				getchar();
				break;
			}
		default:
			{
				printf("����������������룡\n") ;
				fflush(stdin);
				getchar();
				add_Book();
				return;
			}
	}

}

/*

��ӡһ�������Ϣ�����ڲ鿴������鼮��Ϣ�Ƿ����Ҫ��

*/

void show_oneBook(book *p)
{
	printf("ID��%d\n",p->ID);
	printf("������%s\n",p->name);
	printf("��������%s\n",p->author);
	printf("����ţ�%d\n",p->typenum);
	printf("���浥λ��%s\n",p->publish_company);
	printf("����ʱ�䣺%d\n",p->publish_time);
	printf("�鱾�۸�%.2f\n",p->price);
}

/*

��ӡ���е��鼮��Ϣ

*/

void show_allBooks()
{
	printf("���ڲ�ѯ�����鼮���Ե�");
	Sleep(500);
	printf(".");
	Sleep(500);
	printf(".");
	Sleep(500);
	printf(".\n");

	if(head==NULL)
	{
		puts("��ͼ����Ϣ�����ֶ�¼�롣\n�����������...");
		fflush(stdin);
		getchar();
	}
	else
	{
		printf("��ǰ��%d����\n",Book_num);
		book *p = head;
		while(p!=NULL)
		{
			show_oneBook(p);
			puts("");
			p = p->next;
		}
		puts("�����������...");
		fflush(stdin);
		getchar();
	}

}
/*

����������鼮����ǰ�ṩ�ķ�ʽ��

1.������������
2.��������������

*/
void search_Book()
{
	system("cls");
	puts(">�����������밴 1\n>�������������밴 2\n>�����밴3");
	int x,found=0;
	char search[20];
	scanf("%d",&x);
	system("cls");
	book *p=head;
	switch(x)
	{
		case 1:
			{
				puts(">������Ҫ���ҵ�����:");
				scanf("%s",search);
				puts("");
				while(p!=NULL)
				{
					if(strcmp(search,p->name)==0)
					{
						found=1;
						
						printf("���ڲ���");
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
				puts(">������Ҫ���ҵ�������:");
				scanf("%s",search);
				puts("");
				while(p!=NULL)
				{
					if(strcmp(search,p->author)==0)
					{
						found=1;
						printf("���ڲ���");
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
				printf("�������������������\n") ;
				found = 2;
				break;
			}
	}
	if(found==1)	puts("���ҵ�����ͼ�飬�����������...");
	if(found==0) 	puts("��Ҫ���ҵ�ͼ����Ϣ������!");
	if(found==2)	search_Book();
	if(found==3)    return;
	fflush(stdin);
	getchar();
}

/*

�������������ɾ��������Ϣ
�����������鱾Ҳ���˴���ÿ������ѯ���Ƿ�Ҫɾ�� 

*/
void delete_Book()
{
	system("cls");
	int found=0;
	char name[20];
	book *p=head,*pold;//������ʱ���� pold��ʾǰһ���ڵ� 
	puts(">������Ҫɾ����������");
	scanf("%s",name);
	while(p!=NULL)
	{
		if(strcmp(name,p->name)==0)//����ҵ��Ȿ����
		{
			found = 1;//���Ϊ�ҵ���
			show_oneBook(p);//չʾһ���Ȿ��
			puts("");
			puts(">��ȷ��Ҫɾ���Ȿ���� �ǣ�1��or ��0��");
			int choice;
			scanf("%d",&choice);
			if(choice)
			{
				if(p==head)//���Ҫɾ�����ǵ�һ���� 
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
				printf("����ɾ�����Ե�");
				Sleep(500);
				printf(".");
				Sleep(500);
				printf(".");
				Sleep(500);
				printf(".\n");
				printf(">ɾ���ɹ���\n\n");
				
			}
			else break;
		}
		else//�����û�ҵ��Ȿ�飬������һ���ڵ�
		{
			pold = p;
			p = p->next;
		}
	}
	if(found==0)	puts("ɾ��ʧ�ܣ�δ�ҵ���ͼ�飡");
	puts("�����������...");
	fflush(stdin);
	getchar();

}

/*

����ͼ�����Ϣ

*/
void update_Book()
{
	system("cls");
	book *p = head;
	char name[20];
	int x,found=0;
	printf(">������Ҫ�޸ĵ�ͼ���������");
	scanf("%s",name);
	while(p!=NULL)
	{
		if(strcmp(name,p->name)==0)
		{
			found = 1;
			show_oneBook(p);
			printf(">�Ƿ�ȷ���޸ģ� �ǣ�1��or ��0��");
			scanf("%d",&x);
			if(x)
			{
				system("cls");
				printf("**********������������Ϣ*********\n");
				printf(">������ID��");
				scanf("%d",&p->ID);
				printf(">������������");
				scanf("%s",p->name);
				printf(">��������������");
				scanf("%s",p->author);
				printf(">���������ţ�");
				scanf("%d",&p->typenum);
				printf(">��������浥λ��");
				scanf("%s",p->publish_company);
				printf(">���������ʱ�䣺");
				scanf("%d",&p->publish_time);
				printf(">�������鱾�۸�");
				scanf("%f",&p->price);
				printf("���ڸ������Ե�");
				Sleep(500);
				printf(".");
				Sleep(500);
				printf(".");
				Sleep(500);
				printf(".\n");
				printf("\n>���ѣ��޸ĳɹ�!\n");
			}
		}
		p = p->next;
	}
	if(found==0)	printf(">���ѣ�û����Ҫ�޸ĵ���Ϣ��\n");
	puts("�����������...");
	fflush(stdin);
	getchar();
}

