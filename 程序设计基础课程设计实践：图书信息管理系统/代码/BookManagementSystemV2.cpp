#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "bms.h"
#define MENU_COUNT 5 

void add_Book();//�����鱾 
void show_allBooks();//��ʾ����ͼ�� 
void show_oneBook(book *p);//��ʾ����ͼ�� 
void search_Book();//����ͼ�� 
void delete_Book();//ɾ��ͼ�� 
void update_Book();//����ͼ������ 
void menu();//�˵�ҳ�� 
void quit();//�˳������� 
int ReadFromFile();//���ļ���ȡ�鼮��Ϣ 

int main()
{
	system("color 70");
	int choice;
	ReadFromFile();
	while(choice>=0&&choice<=MENU_COUNT)
	{
		system("cls");
		menu();
		printf(">��ѡ��Ҫ���еĲ���(%d_%d):",0,MENU_COUNT);
		if(scanf("%d",&choice)!=1||choice<0||choice>MENU_COUNT)
		{
			printf(">��������!��ѡ��(%d-%d)֮�������!�����������...",0,MENU_COUNT);
			fflush(stdin);   //������뻺����
			getchar();
		}
		else
		{
			switch(choice)
			{
				case 0:
					quit();
					{
						break;
					}
				case 1:
					show_allBooks();
					{
						break;
					}
				case 2:
					add_Book();
					{
						break;
					}
				case 3:
					search_Book();
					{
						break;
					}
				case 4:
					delete_Book();
					{
						break;
					}
				case 5:
					update_Book();
					{
						break;
					}
			}
		}
		choice = 0;
	}
	return 0;
}





