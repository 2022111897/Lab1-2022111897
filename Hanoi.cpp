#include <iostream>
using namespace std;
void Hanoi(int n,char a,char b,char c);
void Move(int n,char a,char b);
int main()
{   int n;
    printf("Input the number of disks:");
    scanf("%d",&n);
    cout<<"Steps of moving"<<n<<" disks from A to B by means of C:"<<endl;
    Hanoi(n,'A','B','C');
	return 0;
}
void Hanoi(int n,char a,char b,char c)
{if (n==1)
{Move(n,a,b);
}
else
{Hanoi(n-1,a,c,b);
 Move(n,a,b);
 Hanoi(n-1,c,b,a);
}
}
void Move(int n,char a,char b)
{cout<<"Move"<<n<<": from "<<a<<" to "<<b<<endl;
}
//modified for lab branch practice step R11
//modified for lab branch practice step
//modified for lab branch practice step

