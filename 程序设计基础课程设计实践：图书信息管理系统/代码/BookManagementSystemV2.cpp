#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "bms.h"
#define MENU_COUNT 5 

void add_Book();//增加书本 
void show_allBooks();//显示所有图书 
void show_oneBook(book *p);//显示单本图书 
void search_Book();//查找图书 
void delete_Book();//删除图书 
void update_Book();//更新图书内容 
void menu();//菜单页面 
void quit();//退出并保存 
int ReadFromFile();//从文件读取书籍信息 

int main()
{
	system("color 70");
	int choice;
	ReadFromFile();
	while(choice>=0&&choice<=MENU_COUNT)
	{
		system("cls");
		menu();
		printf(">请选择要进行的操作(%d_%d):",0,MENU_COUNT);
		if(scanf("%d",&choice)!=1||choice<0||choice>MENU_COUNT)
		{
			printf(">输入有误!请选择(%d-%d)之间的数字!按任意键重试...",0,MENU_COUNT);
			fflush(stdin);   //清空输入缓冲区
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





