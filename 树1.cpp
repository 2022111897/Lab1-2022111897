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
char genelist[100];//保存广义表
int i;
BTtree* pre_creat_bt()//先序建立二叉树
{
    char ch;
    BTtree  *T;
    cin >> ch;
    if(ch=='#')  T=NULL;
    else
    {
        T=(BTtree*)malloc(sizeof(BTtree));//建立一个节点
        T->data=ch;
        //printf("\n请输入%c结点的左子结点(如果没有那么输入#代表空):",T->data );
        T->lchild=pre_creat_bt();
        //printf("\n请输入%c结点的右子结点(如果没有那么输入#代表空):",T->data );
        T->rchild=pre_creat_bt();
    }
    return T;
}
BTtree * level_create()//层次建立二叉链表
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
            if(i%2==0)s[j]->lchild=p;//节点为偶数，i为j的左儿子
            else    s[j]->rchild=p;//节点为偶数，i为j的左儿子
        }
    }
    return T;
}
int complete_or_not(struct BTtree* T){//判断是否是完全二叉树
    if(!T) return 0;//如果为空，不是完全二叉树
    struct BTtree a[100];
    int rear=0,front=-1;
    a[rear] = *T;
    if(T->lchild==NULL&&T->rchild==NULL)return 1;//如果只有一跟根节点则返回1
    if(T->lchild==NULL||T->rchild==NULL)return 0;//如果根节点有一个子树为空则返回0
    while(front!=rear){
        front++;
        //该节点的左右孩子都不为空则都入队
        if(a[front].lchild!=NULL&&a[front].rchild!=NULL){
            rear++;
            a[rear] = *a[front].lchild;
            rear++;
            a[rear] = *a[front].rchild;
        }else if(a[front].lchild==NULL&&a[front].rchild!=NULL){ //该节点的左孩子为空右孩子不为空则非完全二叉树
            return 0;
        }else if((a[front].lchild!=NULL&&a[front].rchild==NULL)||(a[front].lchild==NULL&&a[front].rchild==NULL)){ //该节点的左孩子不为空右孩子为空，或左右都为空的话，后面访问的节点必需都是叶子节点
            for(int i=front+1;i<=rear;i++){
                if(a[i].lchild!=NULL||a[i].rchild!=NULL){
                    return 0;
                }
            }//对这颗树的剩余节点进行遍历
        }
    }
    return 1;
}
void pre_order(BTtree *T)//递归先根遍历二叉树
{
    if(T!=NULL)
    {
        cout << T->data;
        pre_order(T->lchild);
        pre_order(T->rchild);
    }
}
void in_order(BTtree *T)//递归中序遍历二叉树
{
    if(T!=NULL)
    {
        in_order(T->lchild);
        cout << T->data;
        in_order(T->rchild);
    }
}
void post_order(BTtree *T)//递归后根遍历二叉树
{
    if(T!=NULL)
    {
        post_order(T->lchild);
        post_order(T->rchild);
        cout << T->data;
    }
}
void npre_order(BTtree *T)//非递归先根遍历二叉树
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
当树非空那么循环，访问，左走
若S不空，取栈顶右走
*/
void nin_order(BTtree *T)//非递归中序遍历二叉树
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
  树不空，左走一步不访问
  若栈不空，取出栈顶访问 再访问父亲，再右走
*/
void npost_order(BTtree *T)//非递归后根遍历二叉树
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
    int front=0,rear=0;//建立一个空的队列
    if(T==NULL)return;
    Q[rear++]=T;//将根指针入队
    while(front!=rear)
    {
        q=Q[front];
        cout << q->data;
        if(q->lchild!=NULL)
        {
            Q[rear]=q->lchild;//左儿子不是空，将它入队列
            rear++;
        }
        if(q->rchild!=NULL)
        {
            Q[rear]=q->rchild;//右边儿子不是空，将它入队列
            rear++;
        }
        front++;//完成上面之后将队首元素就可以出队进行下一次循环操作
    }
}
void  order(BTtree * T)//遍历二叉链表
{
    printf("********递归遍历二叉链表***********\n");
    printf("\n先序递归遍历二叉链表:");
    pre_order(T);
    printf("\n中序递归遍历二叉链表:");
    in_order(T);
    printf("\n后序递归遍历二叉链表:");
    post_order(T);
    printf("\n********非递归遍历二叉链表***********\n");
    printf("\n先序非递归遍历二叉链表:");
    npre_order(T);
    printf("\n中序非递归遍历二叉链表:");
    nin_order(T);
    printf("\n后序非递归遍历二叉链表:");
    npost_order(T);
    printf("\n**********层次遍历二叉链表***********:\n");
    lev_order(T);
}
void print_tree(BTtree *T) /*按广义表方式打印*/
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
	int front,rear;	//定义顺序非循环队列
	int Lno=0,i,j,n,max=0;
	front=0,rear=0;	//队头队尾为零，把队列置空
	BTtree *q;
	if(b!=NULL)
	{
		++rear;
		que[rear].p=b;	//二叉树的根入队
		que[rear].lno=1;	//树根所在的层次号设为1；若题中指定第一层层号为0，更改即可
		while(front!=rear)
		{
			++front;
			q=que[front].p;
			Lno=que[front].lno;	//Lno用来存储当前节点的层次号
			if(q->lchild!=NULL)
			{
				++rear;
				que[rear].p=q->lchild;
				que[rear].lno=Lno+1;	//根据当前的层次号推知其孩子节点的层次号
			}
			if(q->rchild!=NULL)
			{
				++rear;
				que[rear].p=q->rchild;
				que[rear].lno=Lno+1;	//同理，根据当前层次号推测知道其孩子结点的层次号
			}
		}//当循环结束的时候，Lno保存的是这棵二叉树的最大层数
		//然后找出来含有结点最多的层中的节点数目
		max=0;
		for(i=0;i<=Lno;++i)
		{
			n=0;
			for(j=1;j<=rear;++j)//数组从1处开始存储，结束时，rear处有数据
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
		return 0;	//如果是空树，则返回0
	}
}
int main()
{
    BTtree *pre_t=NULL,*lev_t=NULL;
	int k;
    int N;
    printf("********输入1建立二叉链表***********\n********输入2建立二叉链表并用各种遍历表示***********\n********输入3判断是否是完全二叉树***********\n********输入4判断该二叉树的宽度***********\n");
    while(cin >> N)
    {
        switch(N)
        {
        case 1:
            printf("********先序建立二叉链表***********\n输入节点(如果没有那么输入#代表空):");
            pre_t=pre_creat_bt();
            order(pre_t);//遍历二叉链表
            printf("\n********二叉树用广义表表示为********:\n");
            print(pre_t);
            for(i=0; genelist[i]!='\0'; i++) cout << genelist[i];
            printf("\n");
            break;
        case 2:
            printf("********建立二叉链表***********\n输入节点(如果没有那么输入#代表空):");
            pre_t=pre_creat_bt();
            order(pre_t);//遍历二叉链表
            printf("\n********二叉树用广义表表示为********:\n");
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
			printf("此二叉树的宽度为%d",k);
        case 0:
            break;
        default :
            break;
        }
        memset(genelist,' ',sizeof(genelist));
        printf("********输入1建立二叉链表并表示***********\n********输入2建立二叉链表***********\n********输入3判断是否是完全二叉树***********\n********输入4判断该二叉树的宽度***********\n");
    }
    return 0;
}
