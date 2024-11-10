#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#define Maxlength 1000
using namespace std;
typedef struct {
	int length;//��ǰ˳���ĳ���
	int data[Maxlength];//����˳����Ԫ������
}SQLIST;
int Locate(int x,SQLIST L)
{
	for(int i=0;i<=L.length;i++)
	{
	  if(L.data[i]==x)
	  return i;
	}
	return L.length+1;
 }
void Delete(int x,SQLIST &L)
{
	int position=Locate(x,L);
	if(Locate(x,L)==L.length+1)//�ж�Ԫ���±��Ƿ�Խ��
	 cout<<"�޴�Ԫ��"<<endl;
    while(position!=L.length+1)
    {
	for(int j=position;j<=L.length-1;j++)
    {
    	L.data[j]=L.data[j+1];
	}
	L.length--;
	position=Locate(x,L);
    }
}
void Sort(SQLIST &L)
{
	int i,j,temp,k;
	int n=L.length+1;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
		  if(L.data[j]<L.data[j+1])
		  {
		    temp=L.data[j];
		    L.data[j]=L.data[j+1];
		    L.data[j+1]=temp;
		}
		}
	}
}
void DeleteDup(SQLIST &L)
{
	for(int i=0;i<L.length;i++)
	{
	    for(int j=i+1;j<L.length+1;j++)
		{
		    if(L.data[i]==L.data[j])
		    {
		    	for(int k=j;k<L.length;k++)
				L.data[k]=L.data[k+1];
			    L.length--;
			    --j;
		 	}

		}
	}
}
void Reverse(SQLIST &L,int left,int right)
{
	int i=left;
	int j=right;
	int temp,count=0;
	while(count<=(right-left)/2)
	{
		temp=L.data[i];
		L.data[i]=L.data[j];
		L.data[j]=temp;
		i++;
		j--;
		count++;
	}
}
void MoveRight(SQLIST &L)
{
	int k;
	cout<<"������Ҫ���Ƶ�λ����";
	cin>>k;
	k=k%(L.length+1);
	Reverse(L,0,L.length-k);
	Reverse(L,L.length-k+1,L.length);
	Reverse(L,0,L.length);
}
void MoveLeft(SQLIST &L)
{
	int k;
	cout<<"������Ҫ���Ƶ�λ����";
	cin>>k;
	k=k%(L.length+1);
	k=L.length+1-k;
	Reverse(L,0,L.length-k);
	Reverse(L,L.length-k+1,L.length);
	Reverse(L,0,L.length);
}
SQLIST Merge(SQLIST L1,SQLIST L2)
{
	SQLIST L3;
	int j=0,k=0;
	for(int i=0;i<=(L1.length+L2.length+1);i++)
	{
		if(j<=L1.length&&k<=L2.length)
		{
			if(L1.data[j]<=L2.data[k])
			{
				L3.data[i]=L1.data[j];
				j++;
			}
			else
			{
				L3.data[i]=L2.data[k];
				k++;
			}
		}
		else if(j>L1.length)
		{
			for(int m=k;m<=L2.length;m++)
			{
			  L3.data[i]=L2.data[m];
			  i++;
			}
			break;
		}
		else if(k>L2.length)
		{
			for(int m=j;m<=L1.length;m++)
			{
			  L3.data[i]=L1.data[m];
			  i++;
			}
			break;
		}
	}
	L3.length=L1.length+L2.length+1;
	Sort(L3);
	return L3;
}
void PrintList(SQLIST L)
{
	printf("�����������Ԫ���У�");
    for(int i=0;i<=L.length;i++)
	{
		printf("%d ",L.data[i]);
	}
	printf("\n");
	system("pause");
}
int Menu()
{
    int function;
    cout<<"1.ɾ������Ԫ��"<<endl;
	cout<<"2.ɾ������������ظ�Ԫ��"<<endl;
	cout<<"3.��������"<<endl;
	cout<<"4.ѭ������"<<endl;
	cout<<"5.ѭ������"<<endl;
	cout<<"6.�ϲ������������飨����"<<endl;
	cout<<"������Ҫѡ��Ĺ������:";
    cin>>function;
    return function;
}
int main() {
	int num;
	SQLIST L;
	cout<<"������Ҫ��������ݸ�����";
	cin>>num;
	L.length=num-1;
	for(int i=0;i<=L.length;i++)
	{
		cout<<"�������"<<i+1<<"��Ԫ�أ�";
		cin>>L.data[i];
	}
    while(1)
	{
    char ch=Menu();
	switch(ch)
	{
		case 1:
			int x;
			cout<<"������Ҫɾ����Ԫ�أ�";
			cin>>x;
	     	Delete(x,L);
			PrintList(L);
			break;
		case 2:
		    Sort(L);
		    DeleteDup(L);
			PrintList(L);
			break;
		case 3:
		    Reverse(L,0,L.length);
		    PrintList(L);
		    break;
		case 4:
		    MoveRight(L);
			PrintList(L);
			break;
	    case 5:
		    MoveLeft(L);
			PrintList(L);
			break;
		case 6:
		   SQLIST L1,L2;
		   int num1,num2;
		   cout<<"������Ҫ�����һ�����Ա�����ݵĸ�����";
		   cin>>num1;
		   L1.length=num1-1;
		   for(int i=0;i<=L1.length;i++)
		   {
		   	cout<<"�������"<<i+1<<"��Ԫ�أ�";
			cin>>L1.data[i];
		   }
		   Sort(L1);
		   cout<<"������Ҫ����ڶ������Ա�����ݵĸ�����";
		   cin>>num2;
		   L2.length=num2-1;
		   for(int i=0;i<=L2.length;i++)
		   {
		   	cout<<"�������"<<i+1<<"��Ԫ�أ�";
			cin>>L2.data[i];
		   }
		   Sort(L2);
		   PrintList( Merge(L1,L2));
	    case 0:
		     printf("End of program!");
		     exit(0);
		    default:printf("Input error!");
	   }
   }
	system("pause");
	return 0;
}
