# -*- coding: utf-8 -*-
# @Author: TD21forever
# @Date:   2018-11-14 15:41:57
# @Last Modified by:   TD21forever
# @Last Modified time: 2018-11-15 16:50:48
file = open('input.txt','r')#读取文件

#预处理 传入字符串
def preprocess(article):
    article = article.strip()
    article = article.replace(",", ", ")
    article = article.replace(" ,", ",")
    article = article.replace(".", ". ")
    article = article.replace(" .", ".")
    article = article.replace("?", "? ")
    article = article.replace(" ?", "?")
    return article


def operate(line_num=5,word_in_line=55,margin=2,heading_len=3,footing_len=3,start_page_num=1,file = file):

    flag = 0
    article = file.read()#读到文件里的字符串
    file.close()
    f = open ('out.txt','a')
    article = preprocess(article)

    word_list = article.split()#分割每个单词，形成列表
   
    str_info = " ".join(word_list)#目的是去掉连续的空格
    str_info = str_info.replace("@", "\n        @")

    start = 0
    end = word_in_line

    while end < len(str_info):
      
        for i in range(heading_len):#顶部的空格
            print("\n",end="",file = f)

        for one in range(line_num):#每一行
            line = str_info[start:end]
            temp = end
            if end<=len(str_info):
                if str_info[temp-1] != " " or str_info[temp-1] not in word_list:#如果一行的最后一个不是空格说明那个单词被拆开了
                # 另一个条件是防止出现as被分开的这种情况
                    while str_info[temp] != " ":#下一行的第一个字母不是空格，就把这个字母加到上一行的末尾
                        line = line + (str_info[temp])
                        temp+=1
                    line = line + (str_info[temp])#temp最后移到空格，空格放在上一行的末尾
                    end = temp+1

                print(" "*margin,end="",file = f)#每一行开头的空格
                print(line,file = f)#打印一页
                start = end
                end+=word_in_line
            elif one+1 < line_num:#如果每页的行数还没有得到要求
                line = str_info[start:]
                print(" "*margin,end="",file=f)#每一行开头的空格
                print(line,file = f)#打印一页
                flag = 1
                for i in range(footing_len):#底部空格
                    if footing_len >=3 :
                        if i==1:
                            print(" "*((word_in_line+margin)//2),str(start_page_num),end = "",file = f)

                    print("\n",end = "",file = f)
                break
            else:#如果这一页的行数已经达到了，那就另起一页
                for i in range(footing_len):#底部空格
                    if footing_len >=3 :
                        if i==1:
                            print(" "*((word_in_line+margin)//2),str(start_page_num),end = "",file = f)

                    print("\n",end = "",file = f)
                for i in range(heading_len):#顶部的空格
                    print("\n",end="",file = f)
                line = str_info[start:]
                print(" "*margin,end="",file = f)#每一行开头的空格
                print(line,file = f)#打印一页
                for i in range(footing_len):#底部空格
                    if footing_len >=3 :
                        if i==1:
                            print(" "*((word_in_line+margin)//2),str(start_page_num+1),end = "",file = f)

                    print("\n",end = "",file = f)
                flag = 1

        if flag == 1:
            break

        for i in range(footing_len):#底部空格
            if footing_len >=3 :
                if i==1:
                    print(" "*((word_in_line+margin)//2),str(start_page_num),end = "",file = f)

            print("\n",end = "",file = f)

        
        start_page_num+=1


   
if __name__ == '__main__':
    while True:
        print("欢迎使用文本格式化工具")
        print("您可以给出的参数有\n1.每页内文字的行数\n2.每页内文字所占最大字符数\n3.每页文字前的固定空格数\n4.每页页顶所空行数\n5.每页页底所空行数\n6.起始页号\n")
        ans = "no"
        ans = input("是否要使用默认的参数5,55,2,3,3,1?,请输入yes或no:")
        if ans == 'yes':
            operate()
        else:
            print("请输入参数\n")
            a = int(input("1.每页内文字的行数"))
            b = int(input("2.每页内文字所占最大字符数"))
            if b>80:
                b = int(input("每页内文字所占最大字符数小于80，请重新输入："))
            c = int(input("3.每页文字前的固定空格数"))
            d = int(input("4.每页页顶所空行数"))
            e = int(input("5.每页页页底所空行数"))
            ff = int(input("6.起始页号"))            
            operate(a,b,c,d,e,ff)
            f.close()

