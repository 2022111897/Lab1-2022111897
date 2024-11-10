#include <stdio.h>
#include <stdlib.h>
#define maxsize 100
typedef int ElemType;
typedef struct StaticLink 
{
    ElemType element;
    int next;
}Node;
void Print(Node arr[maxsize])//依次打印线性表中元素
{
    int temp=arr[0].next;
    while(temp!=-1)
    {
        printf("%d  ",arr[temp].element);
        temp=arr[temp].next;
    }
}

/*逆置算法*/
void Reverse(Node arr[maxsize])
{
    int p=arr[0].next;//指向第一个元素位置
    int temp;
    int tempt=arr[p].next;//记录下一个位置
    arr[p].next=-1;//第一个元素的游标改为-1
    while(p!=-1)
    {
        temp=p;//记录移动前位置
        p=tempt;//p指向下一结点
        tempt=arr[p].next;
        arr[p].next=temp;//更改next域
    }
    arr[0].next=temp;
}

int main()
{
    Node a[maxsize];
    printf("请输入数据的个数：");
	int k;
	scanf("%d",&k); 
    for(int i=0;i<k;i++)
	{
		a[i].next=i+1;
	}
	a[k].next=-1;
	int temp=a[0].next;
	printf("请输入数据：");
	while(temp!=-1)
	{
	    scanf("%d",&a[temp].element);
		temp=a[temp].next;
	}
    printf("Before reverse\n");
    Print(a);
    printf("\n");
    printf("After reverse\n");
    Reverse(a);
    Print(a);
    return 0;
}

