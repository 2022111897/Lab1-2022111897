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
} op_s;//ջ��˳��洢ʵ�֣�����ջ 
struct STACK_NUM
{
    int top_num;
    double element[maxlen];
} num_s;//ջ��˳��洢ʵ�֣�����ջ 
char mid[100],end[100];//����������������׺�ͺ�׺
void makenull_char(STACK_CHAR &S)//�ÿ� 
{
    S.top_char=maxlen;
}
void makenull_num(STACK_NUM &S)
{
    S.top_num=maxlen;
}
bool empty_char(STACK_CHAR S)
{
    if (S.top_char>maxlen-1)   return true;//�ж��Ƿ�ջ�� 
    else return false ;
}
bool empty_num(STACK_NUM S)
{
    if (S.top_num>maxlen-1)   return true;//�ж��Ƿ�ջ�� 
    else return false ;
}
char top_char(STACK_CHAR S)
{
	return(S.element[S.top_char]);//����S.top_charλ�õ�Ԫ��ֵ 
}
double top_num(STACK_NUM S)
{
	return(S.element[S.top_num]);//����S.top_numλ�õ�Ԫ��ֵ
}
void pop_char(STACK_CHAR &S)//����ջ 
{
    if (empty_char(S))  cout << "STACK_CHAR is empty" << endl;
    else
    {
        S.top_char =S.top_char+1;
        cout << "����ջ��Ԫ�أ�" ;
        for(int i=maxlen-1; i>=S.top_char; i--)  cout << S.element[i] << " ";
        cout << endl;
    }
}
void pop_num(STACK_NUM &S)//����ջ 
{
    if (empty_num(S))  cout << "STACK_NUM is empty" << endl;
    else
    {
        S.top_num =S.top_num+1;//����һ��Ԫ�� 
        cout << "����ջ��Ԫ�أ�";
        for(int i=maxlen-1; i>=S.top_num; i--)   cout << S.element[i] << " ";
        cout << endl;
    }
}
void push(char x,STACK_CHAR &S)//ѹջ 
{
    if (S.top_char==0)   cout << " STACK_CHAR  is full " << endl;
    else
    {
        S.top_char=S.top_char-1;//����ѹһ��Ԫ�� 
        S.element[S.top_char]=x;//��ֵ 
        cout << "����ջ��Ԫ�أ�" ;
        for(int i=maxlen-1; i>=S.top_char; i--)  cout << S.element[i] <<  " ";
        cout << endl;
    }
}
void push_num(double x,STACK_NUM &S)//ѹ��ջ 
{
    if (S.top_num==0)   cout << " STACK_NUM is full " << endl;
    else
    {
        S.top_num=S.top_num-1;
        S.element[S.top_num]=x;
        cout << "����ջ��Ԫ�أ�";
        for(int i=maxlen-1; i>=S.top_num; i--)    cout << S.element[i] << " ";
        cout << endl;
    }
}
int judge(char m)//�������ȼ��ж�
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
void transfer(char a[],int n)//��׺ת��׺����
{
    int end_count=0,i,m=0;
    if(a[0]=='-')//��׺���ʽ���ǵ�һ��Ϊ����
    {
        end[end_count]='#';//�ã��ű�Ǹ���
        end_count++;
        m=1;//���Ϊ���ţ�����ѭ��ɨ���ʱ��ʹӵڶ����ַ���ʼ
    }
    for (i=m; a[i]!='\0'; i++)
    {
        if (a[i]<='9'&&a[i]>='0'&&(a[i+1]>'9'||a[i+1]<'0')&&a[i+1]!='.')
        {
            end[end_count]=a[i];
            end_count++;
            end[end_count]=' ';
            end_count++;
        }//ɨ�赽��ǰ�ַ�Ϊ0~9������һ��Ϊ���������Ϊ���ֵ����һλ����ô��ո�����һ�����ַֿ���
        else if((a[i]<='9'&&a[i]>='0'&&((a[i+1]<='9'&&a[i+1]>='0')||a[i+1]=='.'))||a[i]=='.')
        {
            end[end_count]=a[i];
            end_count++;
        }//ɨ�赽�������ֶ��Ҳ������ֵ����һλ����׺�в���ո�
        else if(a[i-1]=='('&&a[i]=='-')
        {
            end[end_count]='#';
            end_count++;
        }//��׺���ʽɨ�赽�����ֵ�ǰһ�����������򵱸��Ŵ���
        else if((a[i]=='+'||a[i]=='-'||a[i]=='*'||a[i]=='/')&&a[i-1]!='(')
        {
            while(!empty_char(op_s))
            {
                if(judge(top_char(op_s))>=judge(a[i]))//�ж���ջ��Ԫ�����ȼ����бȽϣ������ջ���߲�����ջ 
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
        }/*��������������������ջ���Ƚϣ�����������ջ����������ջ��
        �����˳�ջ��Ԫ�ز�����ں�׺���ʽ�У�Ȼ�����һ���ո����ָ�����*/
        else if (a[i]=='(') push(a[i],op_s);//�����������ţ���ջ��
        else  if(a[i]==')')
        {
            while(1)
            {
                if(top_char(op_s)=='(')//���������ž���ֹͣ 
                {
                    pop_char(op_s);
                    break;
                }
                else
                {
                    end[end_count]=top_char(op_s);
                    pop_char(op_s);
                    end_count++;
                    end[end_count]=' ';//���ÿո�ָ� 
                    end_count++;
                }
            }
        }//�����������ţ���һֱ��ջ�����ֱ���˵�������Ϊֹ��
        else  continue;
    }
    while(!empty_char(op_s))//��ջ��ʣ�µ�Ԫ�ص���
    {
        end[end_count]=top_char(op_s);
        pop_char(op_s);
        end_count++;
        end[end_count]=' ';
        end_count++;
    }
    end[end_count]='\0';//�����ַ���������ʶ
}
double calculate_end(char a[],int n)        //�����׺���ʽ��ֵ
{
    double top,sec,ans=0,number;
    int i=0,j=0,k,x;
    bool flag=true;//flag���ڱ���Ƿ�Ϊ��������ʼʱ�趨Ϊ���Ǹ���
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
            //�ڽ�ȡ����������ŵ�num�У�
            number=atof(num);//������ʱ��������char�ģ���atof��������ת������char�͵���ת��Ϊdouble
            if(flag==false)
            {
                number=(-1)*number;
                flag=true;//������Ϊ����֮����ô�ѱ�ʶ����Ϊ���Ǹ�������һ��ѭ��ʹ��
            }
            push_num(number,num_s);
            memset(num,' ',sizeof(num));//��ʼ��һ������Ϊ�ո� 
            number=0;
        }//�������ǲ���������ջ��
        else if(end[i-1]==' '&&end[i]<='9'&&end[i]>='0')  j=i;
        //ɨ�赽���ֵĵ�һ������ô��j���ó�i��һ��ѭ��ʱ��num�н�ȡ�ַ���
        else if(a[i]=='+'||a[i]=='-'||a[i]=='*'||a[i]=='/')
        {
            top=top_num(num_s);
            pop_num(num_s);//����ջ 
            sec=top_num(num_s);
            switch (a[i])  //�Բ�ͬ��������зֱ���
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
            push_num(ans,num_s);//�����Ľ���ٽ�ջ 
        }
           /*��������������ջ���˳�����Ԫ�أ�
            ���˳��ķŵ���������ұߣ����˳��ķŵ��������ߣ�
            �����Ľ���ٽ�ջ*/
        else continue;
    }
    return  top_num(num_s);//ջ��ֻ��һ��Ԫ����������Ϊ���
}
//ջ��һϵ�л�����������
int judge(char x);//���ȼ��ж�
void transfer(char a[],int n);//ת���ĺ���
double calculate_end(char end[],int n);//�����׺���ʽ����
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
    cout<<"�������ݳɹ���"<<endl;
    cout << "��׺���ʽΪ:";
    printf("%s\n",mid);
    transfer(mid,100);
    cout << endl << "��׺���ʽΪ��" ;
    for (j=0; end[j]!='\0'; j++)
    {
        if(end[j]=='#') cout << '-';//ɨ������������ô��ʾ����
        else  cout << end[j];    //��ʾ��׺���ʽ
    }
    cout << endl << endl;
    cout <<"���ʽ�ļ�����Ϊ��"<< calculate_end(end,100) << endl;
    return 0;
}
