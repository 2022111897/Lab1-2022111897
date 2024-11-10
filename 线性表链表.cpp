#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
struct Link
{
	int data;
	struct Link *next;//指针域 
};
typedef struct Link Node; 
Node *Append(Node *head)//新建一个节点 
{
	Node *p=NULL,*pr=head;
	int data;
	p=(Node*)malloc(sizeof(Node));//申请空间 
	if(p==NULL)
	{
		printf("No enough memory to allocate!");
		exit(0);
	}
	if(head==NULL)//当原表为空时 
	{
		head=p;
	} 
	else
	{
		while(pr->next!=NULL)
		{
		  pr=pr->next;
		}
		pr->next=p; 
	}
	printf("Input node data:");
	scanf("%d",&data);
	p->data=data;
	p->next=NULL;
	return head; 
}
void Show(Node *head)
{
	Node *p=head;
	int j=1;
	while(p!=NULL)
	{
		printf("第%d个元素%10d\n",j,p->data);
		p=p->next;
		j++;
	}
	system("pause"); 
} 
void DeleteMemory(Node *head)//释放链表所占内存 
{
	Node *p=head,*pr=NULL;
	while(p!=NULL)
	{
		pr=p;
		p=p->next;
		free(pr);
	}
}
Node *InsertNode(Node *head,int Nodedata)
{
    Node *pr=head,*p=head,*temp=NULL;
    p=(Node *)malloc(sizeof(Node));//p指向待插结点
    if(p==NULL)//申请失败
    {
        printf("No enough memory!");
        exit(0);
    }
    p->next=NULL;//为p指向结点赋值为空
    p->data=Nodedata;
    if(head==NULL)//原链表为空表
    {
        head=p;//head指向新建结点p
    }
    else
    {
        while(pr->data<Nodedata&&pr->next!=NULL)
        {
            temp=pr;//temp保存当前结点指针
            pr=pr->next;//pr指向当前结点的下一结点
        }
        if(pr->data>=Nodedata)
        {
            if(pr==head)//若在头结点处插入新结点
            {
                p->next=head;//新结点指向原链表的头结点
                head=p;//head指向新结点
            }
            else//链表中插入新结点
            {
                pr=temp;
                p->next=pr->next;//新结点指向下一结点
                pr->next=p;//前一结点指向新结点
            }
        }
        else
        {
            pr->next=p;//末结点指向新结点
        }
    }
    return head;
}
Node *DeleteNode(Node *head, int x)		//删除所有值为x的元素
{
	int cnt = 0;
	Node *p = head;
	if(head==NULL)//表为空 
	{
		printf("Table is empty!");
		return head;
	}
	if(head->next == NULL)
		return head;
    if(p->data==x)
    {
    	head=head->next;
		free(p);
		return head; 
	}
	while(p->next!=NULL)
	{
		if(p->next->data==x)
		{
			p->next=p->next->next;
		}
		p=p->next;
	}
	return head;
}
Node *DeleteDup(Node *head)
{
	Node *p=head,*pr=head,*temp=NULL;
	if(head==NULL)
	{
		printf("Table is empty!");
		return head;
	}
	p=pr->next;
	while(p!=NULL)
	{
		if(p->data==pr->data)
		{
			pr->next=p->next;
			temp=p;
			p=p->next;
			free(temp); 
		}
		else
		{
			pr=pr->next;
			p=p->next;
		 } 
	}
	return head;
}
Node* mergeList(Node* l1,Node* l2)
    {
        if(!l1)return l2;   
        if(!l2)return l1;
        

        if(l1->data<l2->data)
        {
            l1->next=mergeList(l1->next,l2);  //l1当前结点值较小，则递归合并剩下的部分与l2
            return l1;
        }
        else 
        {
            l2->next=mergeList(l2->next,l1); //l2当前结点值较小，则递归合并剩下的部分与l1
            return l2;
        }
        
        return NULL;
	}
Node* sortList(Node* head) 
{
        if(!head||head->next==NULL)return head;
        
        Node* slow=head;    //慢指针
        Node* fast=head;    //快指针
        
        while(fast->next&&fast->next->next)
        {
            slow=slow->next;
            fast=fast->next->next;
        }
        
        Node* breakNode=slow->next;  //断点 
        slow->next=NULL;  //打断结点
        
        Node* l=sortList(head); //递归左链表
        Node* r=sortList(breakNode); //递归右链表
        
        return mergeList(l,r);  //合并链表
}
Node *Reverse(Node *head)
{
	Node*p=head,*temp=NULL;
	if(head==NULL)
	{
		printf("Table is empty!");
		return head;
	}
	else if(head->next==NULL)
	{
		printf("success!");
		return head;
	}
	else 
	{
		head=NULL;
		while(p->next!=NULL)
		{
			temp=p;//用temp记录p移动前指向的结点 
			p=p->next;//p后移 
			temp->next=head;//头指针指向temp前一个结点，完成逆置 
			head=temp;
		}
		head=p;
		p->next=temp;	
	}
}
Node *MoveLeft(Node *head,int k)//左移k位 
{
	int i=0;
	Node *p=head,*pr=head;
	while(p->next!=NULL)
	{
		p=p->next; 
	}
	p->next=head;
	for(i=0;i<k;i++)
	{
		pr=head;
		head=head->next;
	}
	pr->next=NULL;
	return head;
 }
Node *Merge(Node *head1,Node *head2,Node *head)
{
    Node *p=head1,*q=head2;//head为合并后的链表
    Node *s=NULL;
    Node *pr=NULL;

    s=(Node *)malloc(sizeof(Node));//存放新建表的头结点
    head=s;
    pr=head;
    if(p->data>=q->data)
    {
        pr->data=q->data;
        q=q->next;
    }
    else
    {
        pr->data=p->data;
        p=p->next;
    }
    //头结点建立完毕，此时pr指向头节点
    while(p != NULL&&q != NULL)
    {
        s=(Node *)malloc(sizeof(Node));
        if(s==NULL)
        {
            printf("No enough memory!");
            exit(0);
        }
        pr->next=s;//建立s成功，pr指向新结点
        if(p->data>=q->data)
        {
            s->data=q->data;
            q=q->next;
        }
        else
        {
            s->data=p->data;
            p=p->next;
        }
        pr=s;//pr指向新建完毕的结点
    }

    if(p == NULL)//p所指向的链表已空
    {
        while(q != NULL)
        {
            s=(Node *)malloc(sizeof(Node));
            pr->next=s;
            s->data=q->data;
            q=q->next;
            pr=s;
        }
    }
    else//(q->next == NULL)
    {
        while(p != NULL)
        {
            s=(Node *)malloc(sizeof(Node));
            pr->next=s;
            s->data=p->data;
            p=p->next;
            pr=s;
        }
    }
    pr->next=NULL;
    return head;
}
int Menu()
{
    int function;
    cout<<"1.删除给定元素"<<endl;
	cout<<"2.删除有序数组的重复元素"<<endl;
	cout<<"3.逆置数组"<<endl;
	cout<<"4.循环左移"<<endl;
	cout<<"5.合并两个有序数组（升序）"<<endl;
	cout<<"请输入要选择的功能序号:";
    cin>>function;
    return function;
}
int main()
{
    Node *head=NULL;//头指针
    char c;
    printf("Do you want to append a new node(Y/N)");
    scanf(" %c",&c);
    while(c=='Y'||c=='y')
    {
        head=Append(head);
        printf("Do you want to append a new node?(Y/N)");
        scanf(" %c",&c);
    }
    Show(head);//显示当前链表中各节点信息
    printf("table has been established!\n");
    while(1)
	{
    char ch=Menu(); 
	switch(ch)
	{
		case 1:
			int x;
			cout<<"请输入要删除的元素："; 
			cin>>x;
			printf("The result of deleting number %d:\n",x);
            head=DeleteNode(head,x);
            Show(head);
			break;
		case 2:
		    printf("The result of deleting duplicate elements:\n");
            head=DeleteDup(head);
            head=sortList(head); 
            Show(head);
			break;
		case 3:
		    printf("The result of reversing the table:\n");
            head=Reverse(head);
            Show(head);
		    break;
		case 4:
			printf("Please input the units of moving left:");
			int y;
			cin>>y;
		    printf("The result of moving %d units to the left\n",y);
            head=MoveLeft(head,y);
            Show(head);
            DeleteMemory(head);
			break;
		case 5:
            Node *head1=NULL;
            Node *head2=NULL;
            Node *head=NULL;
            char c;
            printf("Do you want to append a new node for table one ?(Y/N)");
            scanf(" %c",&c);
            while(c=='Y'||c=='y')
            {
            head1=Append(head1);
            printf("Do you want to append a new node?(Y/N)");
            scanf(" %c",&c);
            }
            head1=sortList(head1); 
            printf("table one has been established!\n");
            Show(head1);//显示当前链表中各节点信息
            printf("Do you want to append a new node for table two ?(Y/N)");
            scanf(" %c",&c);
            while(c=='Y'||c=='y')
            {
            head2=Append(head2);
            printf("Do you want to append a new node?(Y/N)");
            scanf(" %c",&c);
            }
            printf("Table two has been established!\n");
            head2=sortList(head2); 
            Show(head2);//显示当前链表中各节点信息
            printf("Table merged by table 1 and table 2 is:\n");
            head=Merge(head1,head2,head);
            head=sortList(head); 
            Show(head);
            DeleteMemory(head1);
            DeleteMemory(head2);
	   }
   } 
    return 0;
}

