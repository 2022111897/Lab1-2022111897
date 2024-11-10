#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#define max 20
#include<ctime>
using namespace std;
typedef struct celltype
{
	int data;
	celltype *lchild,*rchild;
}BSTNode;
typedef BSTNode* BST;
typedef int records;
typedef records *List;
List l1,l2; 
void Insert(BST *G,int k)
{
	if((*G)==NULL)
	{
		(*G) = (BST)malloc(sizeof(BSTNode));
		(*G)->data=k;
		(*G)->lchild=NULL;
		(*G)->rchild=NULL;
	}
	else if((*G)->data==k){
	cout<<"该关键字已经存在，请插入其他的关键字"<<endl;//存在相同关键字，插入失败
    }
	else if((*G)->data<k)
	{
	Insert(&(*G)->rchild,k);
	}
	else{
	Insert(&(*G)->lchild,k); 
	} 
}
BST Create(){//生成数据
    fstream file1,file2;
    BST p=NULL;
    file1.open("jishu.txt");
    int a[max],temp,w;
    for(int i=0;i<max;i++)
    {
	a[i]=2*i+1;
    file1<<2*i+1<<endl;
	}
    file1.close();
	fstream in;
	in.open("jishu.txt");
	int k;
	for(int i=0;i<max;i++){
		in>>k;
		Insert(&p,k);
	}
	in.close();
	return p;
}
int count;
int Search(BST p,int  k)//BST查找 
{	
 	if(p==NULL){
    	return count*(-1);
 	}
 	else if(p->data ==k)
    	return count+1;
 	else if(k<p->data){
	 	count=count+1;
    	return (Search(p->lchild,k));
	}	
	else{	
		count=count+1;
    	return (Search(p->rchild ,k)); 
	}
}
int BinSearch(int k,int a[],int low,int up)
{
    int mid;
    if(low>up)
        return count*(-1);
    else
    {
        mid = (low+up)/2;
        if(k<a[mid])
        {
            count=count+1;
            return BinSearch(k,a, low,mid-1);
        }
        else if(k>a[mid])
        {
            count=count+1;
            return BinSearch(k,a, mid+1,up);
        }
        else
            return count;
    }
}
int DeleteMin(BST &F)
{
	int tmp;BST P;
	if(F->lchild==NULL)
	{
		P=F;
		tmp=F->data;
		F=F->rchild;
		delete P;
		return tmp;
	}
	else 
	return(DeleteMin(F->lchild));
 } 
void Delete(BST &F,int k)//删除BST树的关键字为k的节点
{
	if(F!=NULL)
	{
		if(F->data>k)
		Delete(F->lchild,k);//递归的到左子树去删除
		else if(F->data<k)
		Delete(F->rchild,k);//递归地到右子树去删除
		else
		{
			if(F->rchild==NULL)
			F=F->lchild;//左链继承
			else if(F->lchild==NULL)
			F=F->rchild;//右链继承 
			else{
				F->data=DeleteMin(F->rchild);//用右子树中关键字最小的元素继承 
			} 
		 } 
	}
}
void Inorder(BST T,int a[]){  
    if(T==NULL)
       return ;
    Inorder(T->lchild,a);
    a[count++]=T->data;
    Inorder(T->rchild,a);
}
void Sort(BST T){  
    if(T==NULL)
       return ;
    Sort(T->lchild);
    cout<<T->data<<" ";
    Sort(T->rchild);
}
int Menu()
{
    int function;
    cout<<"1.BST的查找"<<endl;
	cout<<"2.BST的插入"<<endl;
	cout<<"3.BST的删除"<<endl;
	cout<<"4.折半查找"<<endl;
	cout<<"0.退出"<<endl;
	cout<<"请输入要选择的功能序号:";
    scanf("%d",&function);
    return function;
}
void countnum(BST T)
{
	int i;
	float success=0,failure=0;
	int num;
	for(i=1;i<=2048;i++)
	{
		count=0;
		num=Search(T,i);
		if(num<0)
		{
			failure+=num*(-1); 
		}
		else
	    {
			success+=num; 
		}
    }  
	printf("平均成功查找次数%f\n",success/1024);
    printf("平均失败查找次数%f\n",failure/1024);
}
void countnum2(int a[])
{
    int i;
    float success =0,failure=0;
    int num;
    for(i=1; i<=2048; i++)
    {
        count=0;
        num=BinSearch(i,a,0,1023);
        if(num<0)
        {
            failure+=num*(-1);
        }
        else
        {
            success+=num;
        }
    }
    printf("平均成功查找次数%f\n",success/1024);
    printf("平均失败查找次数%f\n",failure/1024);
}
int main()
{
	int a[1024];
    int i,j;
    j=0;
    BST F1=NULL;
    printf("顺序奇数数列为：\n");
    for(i=1; i<2048; i=i+2)
    {
        Insert(&F1,i);
        a[j]=i;
        cout<<a[j]<<" ";
        j++;
    }
    printf("\n");
    printf("有序插入结果\n");
    countnum(F1);
    int T=1000,n=1024,tmp;
    srand((unsigned)time(0));
    while(T--)
    {
        i=rand()%n;
        j=rand()%n;
        tmp=a[i];
        a[i]=a[j];
        a[j]=tmp;
    }
    BST F2=NULL;
    printf("随机数列数据为：\n");
    for(i=0; i<1024; i++)
    {
        Insert(&F2,a[i]);
        cout<<a[i]<<" ";
    }
    printf("\n");
    printf("乱序插入结果\n");
    countnum(F2);
    count=0;
    Inorder( F1,a);
    printf("第一个折半查找结果\n");
    countnum2(a);
    count=0;
    Inorder( F2,a);
    printf("第二个折半查找结果\n");
    countnum2(a);	BST P=F1;
    //P=Create();
	printf("The creation result is as follows:\n");
    Sort(P);
    printf("\n");
    char ch;
    while(1)
    {
	  	ch=Menu();
   		int m;int p;int n;int u,h; 
   		switch(ch){
   			case 1:
				printf("\nEnter the number you want to find:\n");
    			scanf("%d",&m);
    			p=Search(P,m);
    			if(p>0){
				printf("Found!\n查找次数为: %d\n",p);
				}
    			else{ 
					printf("Not Found!\n");
				}
				printf("\n"); 
				countnum(P);
    			break;
    		case 2: 
			 	printf("\nEnter the number you want to insert:\n");
    			scanf("%d",&n);
    			Insert(&P,n);
    			printf("The result of the insert operation.\n");
    			Sort(P);
    			printf("\n"); 
    			break;
    		case 3:
    			printf("\nPlease enter the element you want to delete:\n");
    			int n1;
    			scanf("%d",&n1);
    			Delete(P,n1);
   				printf("The result of the delete operation.\n");
    			Sort(P);
    			printf("\n"); 
    			break;
    		case 4:
				printf("\nEnter the number you want to find by zheban:\n");
				scanf("%d",&u);
    			h=BinSearch(u,a,0,1023);
    			if(h>0){
				printf("Found!\n");
				}
    			else{ 
					printf("Not Found!\n");
				}
				printf("\n"); 
    			break;
    		case 0:
    			printf("End of program!");
    			exit(0); 
    		default:
    			printf("Error!");
		}
	}
	return 0;
 } 
