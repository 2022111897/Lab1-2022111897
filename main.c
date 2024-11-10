#include <stdio.h>
#include <stdlib.h>
void Bubblesort(int a[],int size)
{
    int temp;
    for(int i=0;i<size-1;i++)
    {
        int count = 0;
        for(int j=0;j<size-i-1;j++)
        {
            if(a[j]>a[j+1])
            {
               temp=a[j];
               a[j]=a[j+1];
               a[j+1]=temp;
               count=1;
            }
        }
        if(count==0)
        {
            break;
        }
    }
}
//modified for lab  R3
int main()
{
   int a[10]={1,5,9,7,8,4,6,3,2,0};
    printf("����10����Ϊ��");
    for(int i=0;i<10;i++)
    {
        printf("%d ",a[i]);
    }
    Bubblesort(a,10);
    printf("ð�������Ϊ��\n");
    for(int i=0;i<10;i++)
    {
        printf("%d ",a[i]);
    }
    return 0;
}
//modified for lab branch practice step R11
//modified for lab branch practice step
//modified for lab branch practice step
