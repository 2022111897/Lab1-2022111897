#include <stdio.h>
#include <stdlib.h>
#define maxsize 100
typedef int ElemType;
typedef struct StaticLink 
{
    ElemType element;
    int next;
}Node;
void Print(Node arr[maxsize])//���δ�ӡ���Ա���Ԫ��
{
    int temp=arr[0].next;
    while(temp!=-1)
    {
        printf("%d  ",arr[temp].element);
        temp=arr[temp].next;
    }
}

/*�����㷨*/
void Reverse(Node arr[maxsize])
{
    int p=arr[0].next;//ָ���һ��Ԫ��λ��
    int temp;
    int tempt=arr[p].next;//��¼��һ��λ��
    arr[p].next=-1;//��һ��Ԫ�ص��α��Ϊ-1
    while(p!=-1)
    {
        temp=p;//��¼�ƶ�ǰλ��
        p=tempt;//pָ����һ���
        tempt=arr[p].next;
        arr[p].next=temp;//����next��
    }
    arr[0].next=temp;
}

int main()
{
    Node a[maxsize];
    printf("���������ݵĸ�����");
	int k;
	scanf("%d",&k); 
    for(int i=0;i<k;i++)
	{
		a[i].next=i+1;
	}
	a[k].next=-1;
	int temp=a[0].next;
	printf("���������ݣ�");
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

