#include <iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
#define  maxlen 100
#define N 100 
struct STACK_CHAR
{ 
    char element[maxlen];
    int top_char;   
} op_s;//栈的顺序存储实现，符号栈 
struct STACK_NUM
{
    int top_num;
    double element[maxlen];
} num_s;//栈的顺序存储实现，数字栈 
char mid[100],end[100];//定义两个数组存放中缀和后缀
void makenull_char(STACK_CHAR &S)//置空 
{
    S.top_char=maxlen;
}
void makenull_num(STACK_NUM &S)
{
    S.top_num=maxlen;
}
bool empty_char(STACK_CHAR S)
{
    if (S.top_char>maxlen-1)   return true;//判断是否栈空 
    else return false ;
}
bool empty_num(STACK_NUM S)
{
    if (S.top_num>maxlen-1)   return true;//判断是否栈空 
    else return false ;
}
char top_char(STACK_CHAR S)
{
	return(S.element[S.top_char]);//返回S.top_char位置的元素值 
}
double top_num(STACK_NUM S)
{
	return(S.element[S.top_num]);//返回S.top_num位置的元素值
}
void pop_char(STACK_CHAR &S)//弹出栈 
{
    if (empty_char(S))  cout << "STACK_CHAR is empty" << endl;
    else
    {
        S.top_char =S.top_char+1;
        cout << "符号栈中元素：" ;
        for(int i=maxlen-1; i>=S.top_char; i--)  cout << S.element[i] << " ";
        cout << endl;
    }
}
void pop_num(STACK_NUM &S)//弹出栈 
{
    if (empty_num(S))  cout << "STACK_NUM is empty" << endl;
    else
    {
        S.top_num =S.top_num+1;//弹出一个元素 
        cout << "数字栈中元素：";
        for(int i=maxlen-1; i>=S.top_num; i--)   cout << S.element[i] << " ";
        cout << endl;
    }
}
void push(char x,STACK_CHAR &S)//压栈 
{
    if (S.top_char==0)   cout << " STACK_CHAR  is full " << endl;
    else
    {
        S.top_char=S.top_char-1;//往下压一个元素 
        S.element[S.top_char]=x;//赋值 
        cout << "符号栈中元素：" ;
        for(int i=maxlen-1; i>=S.top_char; i--)  cout << S.element[i] <<  " ";
        cout << endl;
    }
}
void push_num(double x,STACK_NUM &S)//压进栈 
{
    if (S.top_num==0)   cout << " STACK_NUM is full " << endl;
    else
    {
        S.top_num=S.top_num-1;
        S.element[S.top_num]=x;
        cout << "数字栈中元素：";
        for(int i=maxlen-1; i>=S.top_num; i--)    cout << S.element[i] << " ";
        cout << endl;
    }
}
int judge(char m)//符号优先级判断
{
    int flag=0;
    switch(m)
    {
    case '(':
        flag=1;
        break;
    case ')':
        flag=1;
        break;
    case '+':
        flag=2;
        break;
    case '-':
        flag=2;
        break;
    case '*':
        flag=3;
        break;
    case '/':
        flag=3;
        break;
    default :
        break;
    }
    return flag;
}
void transfer(char a[],int n)//中缀转后缀函数
{
    int end_count=0,i,m=0;
    if(a[0]=='-')//中缀表达式中是第一个为负号
    {
        end[end_count]='#';//用＃号标记负号
        end_count++;
        m=1;//如果为负号，进入循环扫描的时候就从第二个字符开始
    }
    for (i=m; a[i]!='\0'; i++)
    {
        if (a[i]<='9'&&a[i]>='0'&&(a[i+1]>'9'||a[i+1]<'0')&&a[i+1]!='.')
        {
            end[end_count]=a[i];
            end_count++;
            end[end_count]=' ';
            end_count++;
        }//扫描到当前字符为0~9而且下一个为运算符（即为数字的最后一位，那么设空格与下一个数字分开）
        else if((a[i]<='9'&&a[i]>='0'&&((a[i+1]<='9'&&a[i+1]>='0')||a[i+1]=='.'))||a[i]=='.')
        {
            end[end_count]=a[i];
            end_count++;
        }//扫描到的是数字而且不是数字的最后一位，后缀中不设空格
        else if(a[i-1]=='('&&a[i]=='-')
        {
            end[end_count]='#';
            end_count++;
        }//中缀表达式扫描到的数字的前一个是左括号则当负号处理
        else if((a[i]=='+'||a[i]=='-'||a[i]=='*'||a[i]=='/')&&a[i-1]!='(')
        {
            while(!empty_char(op_s))
            {
                if(judge(top_char(op_s))>=judge(a[i]))//判断与栈顶元素优先级进行比较，级别比栈顶高才能入栈 
                {
                    end[end_count]=top_char(op_s);
                    pop_char(op_s);
                    end_count++;
                    end[end_count]=' ';
                    end_count ++;
                }
                else break;
            }
            push(a[i],op_s);
        }/*若遇到运算符，则必须与栈顶比较，运算符级别比栈顶级别高则进栈，
        否则退出栈顶元素并存放在后缀表达式中，然后输出一个空格作分隔符；*/
        else if (a[i]=='(') push(a[i],op_s);//若遇到左括号，进栈；
        else  if(a[i]==')')
        {
            while(1)
            {
                if(top_char(op_s)=='(')//遇到左括号就退停止 
                {
                    pop_char(op_s);
                    break;
                }
                else
                {
                    end[end_count]=top_char(op_s);
                    pop_char(op_s);
                    end_count++;
                    end[end_count]=' ';//设置空格分隔 
                    end_count++;
                }
            }
        }//若遇到右括号，则一直退栈输出，直到退到左括号为止。
        else  continue;
    }
    while(!empty_char(op_s))//将栈中剩下的元素弹出
    {
        end[end_count]=top_char(op_s);
        pop_char(op_s);
        end_count++;
        end[end_count]=' ';
        end_count++;
    }
    end[end_count]='\0';//设置字符串结束标识
}
double calculate_end(char a[],int n)        //计算后缀表达式的值
{
    double top,sec,ans=0,number;
    int i=0,j=0,k,x;
    bool flag=true;//flag用于标记是否为负数，开始时设定为不是负数
    char num[100];
    STACK_NUM num_s;
    makenull_num(num_s);
    for(i=0; end[i]!='\0'; i++)
    {
        if(end[i]=='#')
        {
            flag=false;
            j=i+1;
        }
        if(end[i]==' '&&end[i-1]>='0'&&end[i-1]<='9')
        {
            for(k=j,x=0; k<=i; k++,x++) num[x]=end[k];
            //在截取完整的数存放到num中，
            number=atof(num);//但是这时的数还是char的，用atof函数进行转化，将char型的数转化为double
            if(flag==false)
            {
                number=(-1)*number;
                flag=true;//处理完为负数之后那么把标识又设为不是负数，下一次循环使用
            }
            push_num(number,num_s);
            memset(num,' ',sizeof(num));//初始化一个数组为空格 
            number=0;
        }//遇到的是操作数，进栈；
        else if(end[i-1]==' '&&end[i]<='9'&&end[i]>='0')  j=i;
        //扫描到数字的第一个，那么把j设置成i，一遍循环时候num中截取字符串
        else if(a[i]=='+'||a[i]=='-'||a[i]=='*'||a[i]=='/')
        {
            top=top_num(num_s);
            pop_num(num_s);//弹出栈 
            sec=top_num(num_s);
            switch (a[i])  //对不同运算符进行分别处理
            {
            case'+':
                ans=sec+top;
                break;
            case'-':
                ans=sec-top;
                break;
            case'*':
                ans=sec*top;
                break;
            case'/':
                ans=sec/top;
                break;
            }
            pop_num(num_s);
            push_num(ans,num_s);//运算后的结果再进栈 
        }
           /*若遇运算符，则从栈中退出两个元素，
            先退出的放到运算符的右边，后退出的放到运算符左边，
            运算后的结果再进栈*/
        else continue;
    }
    return  top_num(num_s);//栈中只有一个元素啦，返回为结果
}
//栈的一系列基本操作函数
int judge(char x);//优先级判断
void transfer(char a[],int n);//转化的函数
double calculate_end(char end[],int n);//计算后缀表达式函数
int main()
{
    int j,k=0;
	makenull_char(op_s);
	FILE *fp;
	char x[100];
    int m=1,n=0;
    fp=fopen("D:\\bds.txt","r");
    if(fp==NULL)
    {
        printf("bds.txt can not be read!\n");
        exit(0);
    }
    fscanf(fp,"%s",x);
    fclose(fp);
    for(m=1; x[m]!='#'; m++)
    {
        mid[n]=x[m];
        n++;
    }
    mid[n]='\0';
    cout<<"导入数据成功！"<<endl;
    cout << "中缀表达式为:";
    printf("%s\n",mid);
    transfer(mid,100);
    cout << endl << "后缀表达式为：" ;
    for (j=0; end[j]!='\0'; j++)
    {
        if(end[j]=='#') cout << '-';//扫描遇到井号那么显示负号
        else  cout << end[j];    //显示后缀表达式
    }
    cout << endl << endl;
    cout <<"表达式的计算结果为："<< calculate_end(end,100) << endl;
    return 0;
}
