#include <string>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
using namespace std;
int main()
{

	char Y = 'n';                 //是否需要重做
	cout << "～～～您欢迎使用high文本格式化工具" << endl;
	while(Y == 'n')
	{
		bool F = false;            //最后一页页脚输出判断
		char ch;//回查字符
		int  line;         //每行字符数
		int k = line - 1;
		FILE *stream;           //指向文件的指针
		char buf[160];         //最大缓冲区设置
		char buffer[255];     //输入合法性检查

		int marx;              //从第几页开始标记；
		int r;             //每页的行数

		int count = 0;              //行统计
		int m = 0;                 //定位文件指针
		cout << "请您设置每页的行数" << endl;
		cin >> r;
		while( cin.fail() )
		{
			cin.clear();
			cout << "行数设置不合法，请重新输入:" << endl;
			cin.getline( buffer, 255 );

		}
		cout << "请输入开始页码" << endl;
		cin >> marx;
		while( cin.fail() )
		{
			cin.clear();
			cout << "数据输入不对，请重新输入:" << endl;
			cin.getline( buffer, 255 );
			cin >> marx;
		}

		cout << "请您设置每行字符数" << endl;
		cin >> line;
		while( cin.fail() )
		{
			cin.clear();
			cout << "每行字符数设置不合法，请重新输入:" << endl;
			cin.getline( buffer, 255 );
			cin >> line;
		}
		cout << "正在进行编辑处理" << endl;
		cout << endl;

		stream = fopen("wo.txt", "r");          //已读写的方式打开文件；
		if (stream == NULL)
		{
			cout << "该文件不存在" << endl;
			exit(1);
		}
		while (fgets(buf, line, stream) != NULL)   //读取文件流直到文件结束
		{
			count++;
			int n = 0;	   m += strlen(buf);
			ch = fgetc(stream);

			if(buf[20] == 32 || buf[20] == 13 || ch == 32 || buf[20] == 3 || ch == 3) //判断每一次读取的文件流是以什么方式结尾
				//空格换行还是缓冲区满
			{
				for(int i = 0; i < strlen(buf) + 1; i++)
				{
					int r = 0;
					if(!(buf[i] == 32 && buf[i + 1] == 32))	        //如果第i个字符和第i+1个字符不同时为空便输出
						cout << buf[i];
				}
			}

			else
			{
				k = line - 1;                                 //如果是已缓冲区满且下一个字符不为空，则将文件指针
				while(buf[k] != 32)
				{
					k--;    //回溯到前一个空格，即处理在一行尾将字分割的情况
					m--;
					n++;
				}
				for(int i = 0; i < line - n; i++)
				{
					if(!(buf[i] == 32 && buf[i + 1] == 32) && buf[i] <= 127 && buf[i] >= 0)

						cout << buf[i];
				}

			}

			fseek(stream, m, SEEK_SET);                   //指针重新定位
			cout << endl;
			memset(buf, ' ', sizeof(buf));               //缓冲区情况，

			if(count % (r - 3) == 0)                   //判断是否一页已满
			{
				cout << endl;
				for(n = 0; n < line; n++)                //输出页脚
				{
					if(n == int(line / 2)) cout << marx;
					else cout << ' ';
				}
				cout << endl;

				marx++;
			}
			Sleep(2000);

		}
		while (count % (r - 3) != 0)          //最后一页的页脚输出
		{
			F = true;
			cout << endl;
			count++;
		}
		if(F)
		{

			for(int n = 0; n < line; n++)
			{
				if(n == int(line / 2)) cout << marx;
				else cout << ' ';
			}
			cout << endl;
		}

		fclose(stream);
		cout << "您是否满意上面编辑的格式，如果不满意请您重新设置格式参数y/n" << endl;
		cin >> Y;
	}
	return 0;


}
