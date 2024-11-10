#include <iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include <stdbool.h>
#define MAX_SIZE 100
#define ElemType BTtree
#define  maxlen 100
#define maxSize 1000
using namespace std;
typedef struct BTtree
{
    char data;
    struct BTtree  *lchild;
    struct BTtree  *rchild;
}BTtree;
typedef struct St
{
	BTtree *p;
	int lno;
}St;
typedef struct SqQueue {
    BTtree data[100];
    int front, rear;
} SqQueue;
char genelist[100];//��������
int i;
BTtree* pre_creat_bt()//������������
{
    char ch;
    BTtree  *T;
    cin >> ch;
    if(ch=='#')  T=NULL;
    else
    {
        T=(BTtree*)malloc(sizeof(BTtree));//����һ���ڵ�
        T->data=ch;
        //printf("\n������%c�������ӽ��(���û����ô����#�����):",T->data );
        T->lchild=pre_creat_bt();
        //printf("\n������%c�������ӽ��(���û����ô����#�����):",T->data );
        T->rchild=pre_creat_bt();
    }
    return T;
}
BTtree * level_create()//��ν�����������
{
    BTtree* s[maxlen];
    int j;
    char ch;
    BTtree *T,*p;
    while(cin >> i >> ch&&(i!=0||ch!='#'))
    {
        p=(BTtree*)malloc(sizeof(BTtree));
        p->data=ch;
        p->lchild=NULL;
        p->rchild=NULL;
        s[i]=p;
        if(i==1)T=p;
        else
        {
            j=i/2;
            if(i%2==0)s[j]->lchild=p;//�ڵ�Ϊż����iΪj�������
            else    s[j]->rchild=p;//�ڵ�Ϊż����iΪj�������
        }
    }
    return T;
}
int complete_or_not(struct BTtree* T){//�ж��Ƿ�����ȫ������
    if(!T) return 0;//���Ϊ�գ�������ȫ������
    struct BTtree a[100];
    int rear=0,front=-1;
    a[rear] = *T;
    if(T->lchild==NULL&&T->rchild==NULL)return 1;//���ֻ��һ�����ڵ��򷵻�1
    if(T->lchild==NULL||T->rchild==NULL)return 0;//������ڵ���һ������Ϊ���򷵻�0
    while(front!=rear){
        front++;
        //�ýڵ�����Һ��Ӷ���Ϊ�������
        if(a[front].lchild!=NULL&&a[front].rchild!=NULL){
            rear++;
            a[rear] = *a[front].lchild;
            rear++;
            a[rear] = *a[front].rchild;
        }else if(a[front].lchild==NULL&&a[front].rchild!=NULL){ //�ýڵ������Ϊ���Һ��Ӳ�Ϊ�������ȫ������
            return 0;
        }else if((a[front].lchild!=NULL&&a[front].rchild==NULL)||(a[front].lchild==NULL&&a[front].rchild==NULL)){ //�ýڵ�����Ӳ�Ϊ���Һ���Ϊ�գ������Ҷ�Ϊ�յĻ���������ʵĽڵ���趼��Ҷ�ӽڵ�
            for(int i=front+1;i<=rear;i++){
                if(a[i].lchild!=NULL||a[i].rchild!=NULL){
                    return 0;
                }
            }//���������ʣ��ڵ���б���
        }
    }
    return 1;
}
void pre_order(BTtree *T)//�ݹ��ȸ�����������
{
    if(T!=NULL)
    {
        cout << T->data;
        pre_order(T->lchild);
        pre_order(T->rchild);
    }
}
void in_order(BTtree *T)//�ݹ��������������
{
    if(T!=NULL)
    {
        in_order(T->lchild);
        cout << T->data;
        in_order(T->rchild);
    }
}
void post_order(BTtree *T)//�ݹ�������������
{
    if(T!=NULL)
    {
        post_order(T->lchild);
        post_order(T->rchild);
        cout << T->data;
    }
}
void npre_order(BTtree *T)//�ǵݹ��ȸ�����������
{
    BTtree* STACK[maxlen];
    int top=maxlen;
    while(T!=NULL||top!=maxlen)
    {
        while(T!=NULL)
        {
            cout << T->data;
            STACK[--top]=T;
            T=T->lchild;
        }
        if(top!=maxlen)
        {
            T=STACK[top++];
            T=T->rchild;
        }
    }
}
/*
�����ǿ���ôѭ�������ʣ�����
��S���գ�ȡջ������
*/
void nin_order(BTtree *T)//�ǵݹ��������������
{
    BTtree* STACK[maxlen];
    int top=maxlen;
    while(T!=NULL||top!=maxlen)
    {
        if(T!=NULL)
        {
            STACK[--top]=T;
            T=T->lchild;
        }
        else
        {
            T=STACK[top++];
            cout << T->data ;
            T=T->rchild;
        }
    }
}
/*
  �����գ�����һ��������
  ��ջ���գ�ȡ��ջ������ �ٷ��ʸ��ף�������
*/
void npost_order(BTtree *T)//�ǵݹ�������������
{
    struct STACK
    {
        BTtree*  tree;
        int  flag;
    } S[maxlen];
    int top=maxlen;
    BTtree * temp;
    temp=T;
    while(temp!=NULL||top!=maxlen)
    {
        if(temp!=NULL)
        {
            S[--top].tree=temp;
            S[top].flag=1;
            temp=temp->lchild;
        }
        else
        {
            if(S[top].flag==2)
            {
                T=S[top++].tree;
                cout << T->data;
            }
            else
            {
                S[top].flag=2;
                temp=S[top].tree->rchild;
            }
        }
    }
}
void lev_order(BTtree* T)
{
    BTtree* Q[maxlen],*q=NULL;
    int front=0,rear=0;//����һ���յĶ���
    if(T==NULL)return;
    Q[rear++]=T;//����ָ�����
    while(front!=rear)
    {
        q=Q[front];
        cout << q->data;
        if(q->lchild!=NULL)
        {
            Q[rear]=q->lchild;//����Ӳ��ǿգ����������
            rear++;
        }
        if(q->rchild!=NULL)
        {
            Q[rear]=q->rchild;//�ұ߶��Ӳ��ǿգ����������
            rear++;
        }
        front++;//�������֮�󽫶���Ԫ�ؾͿ��Գ��ӽ�����һ��ѭ������
    }
}
void  order(BTtree * T)//������������
{
    printf("********�ݹ������������***********\n");
    printf("\n����ݹ������������:");
    pre_order(T);
    printf("\n����ݹ������������:");
    in_order(T);
    printf("\n����ݹ������������:");
    post_order(T);
    printf("\n********�ǵݹ������������***********\n");
    printf("\n����ǵݹ������������:");
    npre_order(T);
    printf("\n����ǵݹ������������:");
    nin_order(T);
    printf("\n����ǵݹ������������:");
    npost_order(T);
    printf("\n**********��α�����������***********:\n");
    lev_order(T);
}
void print_tree(BTtree *T) /*�������ʽ��ӡ*/
{
    if(T!=NULL)
    {
        if(T->lchild==NULL&&T->rchild==NULL)
        {
            genelist[i]=T->data;
            i++;
        }
        else
        {
            genelist[i]=T->data;
            i++;
            genelist[i]='(';
            i++;
            print_tree(T->lchild);
            genelist[i]=',';
            i++;
            print_tree(T->rchild);
            genelist[i]=')';
            i++;
        }
    }
}
void print(BTtree *T)
{
    BTtree *t=T;
    i=0;
    genelist[i]='(';
    i++;
    print_tree(t);
    genelist[i]=')';
    i++;
    genelist[i]='\0';
}
int maxNode(BTtree *b)
{
	St que[maxSize];
	int front,rear;	//����˳���ѭ������
	int Lno=0,i,j,n,max=0;
	front=0,rear=0;	//��ͷ��βΪ�㣬�Ѷ����ÿ�
	BTtree *q;
	if(b!=NULL)
	{
		++rear;
		que[rear].p=b;	//�������ĸ����
		que[rear].lno=1;	//�������ڵĲ�κ���Ϊ1��������ָ����һ����Ϊ0�����ļ���
		while(front!=rear)
		{
			++front;
			q=que[front].p;
			Lno=que[front].lno;	//Lno�����洢��ǰ�ڵ�Ĳ�κ�
			if(q->lchild!=NULL)
			{
				++rear;
				que[rear].p=q->lchild;
				que[rear].lno=Lno+1;	//���ݵ�ǰ�Ĳ�κ���֪�亢�ӽڵ�Ĳ�κ�
			}
			if(q->rchild!=NULL)
			{
				++rear;
				que[rear].p=q->rchild;
				que[rear].lno=Lno+1;	//ͬ�����ݵ�ǰ��κ��Ʋ�֪���亢�ӽ��Ĳ�κ�
			}
		}//��ѭ��������ʱ��Lno���������ö�������������
		//Ȼ���ҳ������н�����Ĳ��еĽڵ���Ŀ
		max=0;
		for(i=0;i<=Lno;++i)
		{
			n=0;
			for(j=1;j<=rear;++j)//�����1����ʼ�洢������ʱ��rear��������
			{
				if(que[j].lno==i)
				{
					++n;
				}
				if(max<n)
				{
					max=n;
				}
			}
		}
		return max;
	}
	else
	{
		return 0;	//����ǿ������򷵻�0
	}
}
int main()
{
    BTtree *pre_t=NULL,*lev_t=NULL;
	int k;
    int N;
    printf("********����1������������***********\n********����2�������������ø��ֱ�����ʾ***********\n********����3�ж��Ƿ�����ȫ������***********\n********����4�жϸö������Ŀ��***********\n");
    while(cin >> N)
    {
        switch(N)
        {
        case 1:
            printf("********��������������***********\n����ڵ�(���û����ô����#�����):");
            pre_t=pre_creat_bt();
            order(pre_t);//������������
            printf("\n********�������ù�����ʾΪ********:\n");
            print(pre_t);
            for(i=0; genelist[i]!='\0'; i++) cout << genelist[i];
            printf("\n");
            break;
        case 2:
            printf("********������������***********\n����ڵ�(���û����ô����#�����):");
            pre_t=pre_creat_bt();
            order(pre_t);//������������
            printf("\n********�������ù�����ʾΪ********:\n");
            print(pre_t);
            for(i=0; genelist[i]!='\0'; i++) cout << genelist[i];
            printf("\n");
            break;
        case 3:
        	pre_t=pre_creat_bt();
		    if(complete_or_not(pre_t)){
             printf("Exactly,a complete binary tree!!!\n");
            }else{
            printf("this is not a complete binary tree.");
            }
            break;
        case 4:
            pre_t=pre_creat_bt();
			k=maxNode(pre_t);
			printf("�˶������Ŀ��Ϊ%d",k);
        case 0:
            break;
        default :
            break;
        }
        memset(genelist,' ',sizeof(genelist));
        printf("********����1��������������ʾ***********\n********����2������������***********\n********����3�ж��Ƿ�����ȫ������***********\n********����4�жϸö������Ŀ��***********\n");
    }
    return 0;
}
