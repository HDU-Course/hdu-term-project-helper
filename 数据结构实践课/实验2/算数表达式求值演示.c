
#include <stdio.h>
#include <stdlib.h>

#define OK      1
#define ERROR   0
#define TRUE    1
#define FALSE   0
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define EXPRESSIONSIZE 256
char pre[7][7] =
{
    {'>', '>', '<', '<', '<', '>', '>'},
    {'>', '>', '<', '<', '<', '>', '>'},
    {'>', '>', '>', '>', '<', '>', '>'},
    {'>', '>', '>', '>', '<', '>', '>'},
    {'<', '<', '<', '<', '<', '=', '0'},
    {'>', '>', '>', '>', '0', '>', '>'},
    {'<', '<', '<', '<', '<', '0', '='}
};
typedef struct //操作数栈结构定义
{
    int *base;
    int *top;
    int stacksize;
} OperandStack;

typedef struct //操作符栈结构定义
{
    char *base;
    char *top;
    int stacksize;
} OperatorStack;

//==========操作数栈=============//
int InitStack_OPND(OperandStack *S);
//构造一个空栈S
int GetTop_OPND(OperandStack *S, int *e);
//若栈不为空，则用e返回S的栈顶元素，并返回OK；否则返回FALSE
int Push_OPND(OperandStack *S, int e);
//插入元素e为新的栈顶元素
int Pop_OPND(OperandStack *S, int *e);
//若栈S不为空，则删除S的栈顶元素，用e返回其值，并返回OK,否则返回ERROR

//==========操作符栈=============//
int InitStack_OPTR(OperatorStack *S);
//构造一个空栈S
char GetTop_OPTR(OperatorStack *S);
//若栈不为空，则用e返回S的栈顶元素，并返回OK；否则返回FALSE
int Push_OPTR(OperatorStack *S, char e);
//插入元素e为新的栈顶元素
int Pop_OPTR(OperatorStack *S, char *e);
//若栈S不为空，则删除S的栈顶元素，用e返回其值，并返回OK,否则返回ERROR

//============运算操作================//
void Standard(char *expression);
//将表达式标准化
int EvalueateExpression(char *expression);
//算数表达式求值
int Isoperator(char c);
//判断c是否是一个操作符
char Precede(char op1, char op2);
//判断op1和op2优先级的高低，返回'>','<','='
int Operate(int a, char theta, int b);
//对操作数a，b进行theta运算
char *GetNum( char *c, int *num);
//获得以*c开始的操作数，返回后c为操作符


//==========操作数栈==========================================================================//
int InitStack_OPND(OperandStack *S)
{
    //构造一个空操作数栈S
    S->base = (int *)malloc(STACK_INIT_SIZE * sizeof(int));
    if(!S->base)//分配失败
    {
        printf("分配内存失败.\n");
        exit(0);
    }
    S->top = S->base;//初始化
    S->stacksize = STACK_INIT_SIZE;
    return OK;
}

int GetTop_OPND(OperandStack *S, int *e)//获取顶部元素，把得到的数交给e
{
    if(S->top == S->base)
    {
        printf("栈为空.\n");
        return FALSE;
    }
    else
    {
        *e = *(S->top - 1);//s->top所指的地方是空的，所以指针先下移一位
        return OK;
    }
}

int Push_OPND(OperandStack *S, int e)
{
    //插入元素e为新的栈顶元素
    if(S->top - S->base >= S->stacksize) //栈已满，追加存储空间
    {
        S->base = (int *)realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(int));
        if(!S->base)
        {
            printf("重新申请空间失败.\n");
            exit(0);
        }
        S->top = S->base + S->stacksize; //更改栈顶指针
        S->stacksize += STACKINCREMENT;
    }
    *S->top = e;
    S->top++;
    return OK;
}

int Pop_OPND(OperandStack *S, int *e)//删掉的数用e存
{
    if(S->top == S->base) //栈为空
    {
        printf("栈为空.\n");
        return ERROR;
    }
    S->top -= 1;
    *e = *(S->top);
    return OK;
}

//==========操作符栈============================================================================//
int InitStack_OPTR(OperatorStack *S)
{
    //构造一个空操作数栈S
    S->base = (char *)malloc(STACK_INIT_SIZE * sizeof(char));
    if(!S->base)//分配失败
    {
        printf("分配内存失败.\n");
        exit(0);
    }
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    return OK;
}

char GetTop_OPTR(OperatorStack *S)
{
    //若操作数栈不为空，则返回S的栈顶元素，并返回OK；否则返回FALSE
    char e;
    if(S->top == S->base)
    {
        printf("栈为空.\n");
    }
    else
    {
        e = *(S->top - 1);
    }
    return e;
}

int Push_OPTR(OperatorStack *S, char e)
{
    //插入元素e为新的栈顶元素
    if(S->top - S->base >= S->stacksize) //栈已满，追加存储空间
    {
        S->base = (char *)realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(char));
        if(!S->base)
        {
            printf("重新申请空间失败.\n");
            exit(0);
        }
        S->top = S->base + S->stacksize; //更改栈顶指针
        S->stacksize += STACKINCREMENT;
    }
    *S->top++ = e;
    return OK;
}

int Pop_OPTR(OperatorStack *S, char *e)
{
    //若栈S不为空，则删除S的栈顶元素，用e返回其值，并返回OK,否则返回ERROR
    if(S->top == S->base) //栈为空
    {
        printf("栈为空.\n");
        return ERROR;
    }
    *e = *(--S->top);
    return OK;
}

//============运算操作=======================================================================================//
int EvalueateExpression(char *expression)
{
    char *c = expression;//这里用一个指针去操作字符串
    OperandStack Operand;
    OperatorStack Operator;
    OperandStack *OPND = &Operand;//operand 操作数
    OperatorStack *OPTR = &Operator;//operator 操作符
    char x, theta;
    int a, b, num, result;
    InitStack_OPTR(OPTR);//初始化操作符栈
    InitStack_OPND(OPND);//初始化操作数栈
    Push_OPTR(OPTR, '#'); //首先将匹配符号'#'入栈
    while(*c != '#' || GetTop_OPTR(OPTR) != '#')
    {
        if(*c == '\0') //遇到回车退出
            break;
        if(!Isoperator(*c))//如果不是操作符,说明读到了数字
        {
            c = GetNum(c, &num);//处理连续的数字，返回的是出去数字的字符串，数字用num存
            Push_OPND(OPND, num);
        }
        else
            switch(Precede(GetTop_OPTR(OPTR), *c))//判断优先级
            {
            case '<'://如果还是新来的那个优先级高，就把新来的加进去
                Push_OPTR(OPTR, *c);
                c++;//下一个字符串
                break;
            case '=':
                Pop_OPTR(OPTR, &x);//如果优先级一样，说明操作符的栈顶是个左括号，不仅不加入这个右括号，还把左括号退栈
                c++;
                break;
            case '>'://如果还是原来那个操作符的优先级大，把原来那个操作做掉 具体做法是 操作符栈退一个栈 操作数栈退两个栈
                Pop_OPTR(OPTR, &theta);
                Pop_OPND(OPND, &b);
                Pop_OPND(OPND, &a);
                result = Operate(a, theta, b);
                Push_OPND(OPND, result);
                break;
            default: break;
            }
    }
    GetTop_OPND(OPND, &result);//栈里面最后一个值就是结果
    return result;
}

char *GetNum(char *c, int *num)
{
    //获得以*c开始的操作数，返回后c为操作符
    int sum = 0, temp;
    while(!Isoperator(*c)) //当c不是操作符
    {
        temp = *c - '0';//字符串转成了数字
        /*
        '0' = 0x30;
        '1' = 0x31;
        char c = '2'
        int n = c - '0' = 0x32 - 0x30 = 2;
        */
        sum = sum * 10 + temp;
        c++;
    }
    *num = sum;
    return c;
}

int Isoperator(char c)
{
    //判断c是否是一个运算操作符
    switch(c)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '(':
    case ')':
    case '#':
        return TRUE;
        break;
    default:
        return FALSE;
        break;
    }
}


//-------------------------------------------方法一-----------------------------------------------
char Precede(char s_top, char ch)
{
    int i, j;
    switch(s_top)
    {
    case '+': i = 0; break;
    case '-': i = 1; break;
    case '*': i = 2; break;
    case '/': i = 3; break;
    case '(': i = 4; break;
    case ')': i = 5; break;
    case '#': i = 6; break;
    default: i = 0; break;
    }
    switch(ch)
    {
    case '+': j = 0; break;
    case '-': j = 1; break;
    case '*': j = 2; break;
    case '/': j = 3; break;
    case '(': j = 4; break;
    case ')': j = 5; break;
    case '#': j = 6; break;
    default: j = 0; break;
    }
    return pre[i][j];
}


//-------------------------------------------方法二-------------------------------------------------
// char Precede(char op1, char op2) //op1是已经在栈里面的了，op2是后来加进来的  这里参考了网上的方法
// {
//     //判断op1和op2优先级的高低，返回'>','<','='
//     switch(op1)
//     {
//     case '+':
//         switch(op2)
//         {
//         case '*':
//         case '/':
//         case '(':
//             return '<';
//             break;
//         default:
//             return '>';
//             break;
//         }
//         break;
//     case '-':
//         switch(op2)
//         {
//         case '*':
//         case '/':
//         case '(':
//             return '<';
//             break;
//         default:
//             return '>';
//             break;
//         }
//         break;
//     case '*':
//         switch(op2)
//         {
//         case '(':
//             return '<';
//             break;
//         default:
//             return '>';
//             break;
//         }
//         break;
//     case '/':
//         switch(op2)
//         {
//         case '(':
//             return '<';
//             break;
//         default:
//             return '>';
//             break;
//         }
//         break;
//     case '(':
//         switch(op2)
//         {
//         case ')':
//             return '=';
//             break;
//         default:
//             return '<';
//             break;
//         }
//         break;
//     case ')':
//         switch(op2)
//         {
//         default:
//             return '>';
//             break;
//         }
//         break;
//     case '#':
//         switch(op2)
//         {
//         case '#':
//             return '=';
//             break;
//         default:
//             return '<';
//             break;
//         }
//         break;
//     default:
//         return '<';
//         break;
//     }
// }

int Operate(int num_a, char theta, int num_b)
{
    int result;
    switch(theta)
    {
    case '+':
        result = num_a + num_b;
        break;
    case '-':
        result = num_a - num_b;
        break;
    case '*':
        result = num_a * num_b;
        break;
    case '/':
        if(num_b == 0)
        {
            printf("errror:除数为0.");
            exit(0);
        }
        result = num_a / num_b;
        break;
    default:
        printf("输入非法.\n");
        break;
    }
    printf("%d %c %d = %d\n", num_a, theta, num_b, result);
    return result;

}

//------------------------------------------main---------------------

int main()
{
    while(1)
    {

        int result = 0;
        char *expression = (char *)malloc(sizeof(char) * EXPRESSIONSIZE);
        if(expression == NULL)
        {
            printf("内存分配失败\n");
            exit(0);
        }

        printf("\n************************************************************************\n\n");
        puts("温馨提醒：\n");
        puts("    为了方便，请您在输入表达式的结尾加一个符号 '#'，以判断您的输入完成");
        puts("\n    如若忘了输入结束字符 '#'，结果可能有误");
        printf("\n************************************************************************\n\n");
        puts("\n请输入您想要计算的表达式：\n");
        gets(expression);
        result = EvalueateExpression(expression);
        printf("\n计算结果为：%d\n", result);
    }
    return 0;


}
