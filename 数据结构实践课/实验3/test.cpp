#include <string>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
using namespace std;
int main()
{

	char Y = 'n';                 //�Ƿ���Ҫ����
	cout << "����������ӭʹ��high�ı���ʽ������" << endl;
	while(Y == 'n')
	{
		bool F = false;            //���һҳҳ������ж�
		char ch;//�ز��ַ�
		int  line;         //ÿ���ַ���
		int k = line - 1;
		FILE *stream;           //ָ���ļ���ָ��
		char buf[160];         //��󻺳�������
		char buffer[255];     //����Ϸ��Լ��

		int marx;              //�ӵڼ�ҳ��ʼ��ǣ�
		int r;             //ÿҳ������

		int count = 0;              //��ͳ��
		int m = 0;                 //��λ�ļ�ָ��
		cout << "��������ÿҳ������" << endl;
		cin >> r;
		while( cin.fail() )
		{
			cin.clear();
			cout << "�������ò��Ϸ�������������:" << endl;
			cin.getline( buffer, 255 );

		}
		cout << "�����뿪ʼҳ��" << endl;
		cin >> marx;
		while( cin.fail() )
		{
			cin.clear();
			cout << "�������벻�ԣ�����������:" << endl;
			cin.getline( buffer, 255 );
			cin >> marx;
		}

		cout << "��������ÿ���ַ���" << endl;
		cin >> line;
		while( cin.fail() )
		{
			cin.clear();
			cout << "ÿ���ַ������ò��Ϸ�������������:" << endl;
			cin.getline( buffer, 255 );
			cin >> line;
		}
		cout << "���ڽ��б༭����" << endl;
		cout << endl;

		stream = fopen("wo.txt", "r");          //�Ѷ�д�ķ�ʽ���ļ���
		if (stream == NULL)
		{
			cout << "���ļ�������" << endl;
			exit(1);
		}
		while (fgets(buf, line, stream) != NULL)   //��ȡ�ļ���ֱ���ļ�����
		{
			count++;
			int n = 0;	   m += strlen(buf);
			ch = fgetc(stream);

			if(buf[20] == 32 || buf[20] == 13 || ch == 32 || buf[20] == 3 || ch == 3) //�ж�ÿһ�ζ�ȡ���ļ�������ʲô��ʽ��β
				//�ո��л��ǻ�������
			{
				for(int i = 0; i < strlen(buf) + 1; i++)
				{
					int r = 0;
					if(!(buf[i] == 32 && buf[i + 1] == 32))	        //�����i���ַ��͵�i+1���ַ���ͬʱΪ�ձ����
						cout << buf[i];
				}
			}

			else
			{
				k = line - 1;                                 //������ѻ�����������һ���ַ���Ϊ�գ����ļ�ָ��
				while(buf[k] != 32)
				{
					k--;    //���ݵ�ǰһ���ո񣬼�������һ��β���ַָ�����
					m--;
					n++;
				}
				for(int i = 0; i < line - n; i++)
				{
					if(!(buf[i] == 32 && buf[i + 1] == 32) && buf[i] <= 127 && buf[i] >= 0)

						cout << buf[i];
				}

			}

			fseek(stream, m, SEEK_SET);                   //ָ�����¶�λ
			cout << endl;
			memset(buf, ' ', sizeof(buf));               //�����������

			if(count % (r - 3) == 0)                   //�ж��Ƿ�һҳ����
			{
				cout << endl;
				for(n = 0; n < line; n++)                //���ҳ��
				{
					if(n == int(line / 2)) cout << marx;
					else cout << ' ';
				}
				cout << endl;

				marx++;
			}
			Sleep(2000);

		}
		while (count % (r - 3) != 0)          //���һҳ��ҳ�����
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
		cout << "���Ƿ���������༭�ĸ�ʽ����������������������ø�ʽ����y/n" << endl;
		cin >> Y;
	}
	return 0;


}
