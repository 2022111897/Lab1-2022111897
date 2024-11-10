#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
struct Link
{
	int data;
	struct Link *next;//ָ���� 
};
typedef struct Link Node; 
Node *Append(Node *head)//�½�һ���ڵ� 
{
	Node *p=NULL,*pr=head;
	int data;
	p=(Node*)malloc(sizeof(Node));//����ռ� 
	if(p==NULL)
	{
		printf("No enough memory to allocate!");
		exit(0);
	}
	if(head==NULL)//��ԭ��Ϊ��ʱ 
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
		printf("��%d��Ԫ��%10d\n",j,p->data);
		p=p->next;
		j++;
	}
	system("pause"); 
} 
void DeleteMemory(Node *head)//�ͷ�������ռ�ڴ� 
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
    p=(Node *)malloc(sizeof(Node));//pָ�������
    if(p==NULL)//����ʧ��
    {
        printf("No enough memory!");
        exit(0);
    }
    p->next=NULL;//Ϊpָ���㸳ֵΪ��
    p->data=Nodedata;
    if(head==NULL)//ԭ����Ϊ�ձ�
    {
        head=p;//headָ���½����p
    }
    else
    {
        while(pr->data<Nodedata&&pr->next!=NULL)
        {
            temp=pr;//temp���浱ǰ���ָ��
            pr=pr->next;//prָ��ǰ������һ���
        }
        if(pr->data>=Nodedata)
        {
            if(pr==head)//����ͷ��㴦�����½��
            {
                p->next=head;//�½��ָ��ԭ�����ͷ���
                head=p;//headָ���½��
            }
            else//�����в����½��
            {
                pr=temp;
                p->next=pr->next;//�½��ָ����һ���
                pr->next=p;//ǰһ���ָ���½��
            }
        }
        else
        {
            pr->next=p;//ĩ���ָ���½��
        }
    }
    return head;
}
Node *DeleteNode(Node *head, int x)		//ɾ������ֵΪx��Ԫ��
{
	int cnt = 0;
	Node *p = head;
	if(head==NULL)//��Ϊ�� 
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
            l1->next=mergeList(l1->next,l2);  //l1��ǰ���ֵ��С����ݹ�ϲ�ʣ�µĲ�����l2
            return l1;
        }
        else 
        {
            l2->next=mergeList(l2->next,l1); //l2��ǰ���ֵ��С����ݹ�ϲ�ʣ�µĲ�����l1
            return l2;
        }
        
        return NULL;
	}
Node* sortList(Node* head) 
{
        if(!head||head->next==NULL)return head;
        
        Node* slow=head;    //��ָ��
        Node* fast=head;    //��ָ��
        
        while(fast->next&&fast->next->next)
        {
            slow=slow->next;
            fast=fast->next->next;
        }
        
        Node* breakNode=slow->next;  //�ϵ� 
        slow->next=NULL;  //��Ͻ��
        
        Node* l=sortList(head); //�ݹ�������
        Node* r=sortList(breakNode); //�ݹ�������
        
        return mergeList(l,r);  //�ϲ�����
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
			temp=p;//��temp��¼p�ƶ�ǰָ��Ľ�� 
			p=p->next;//p���� 
			temp->next=head;//ͷָ��ָ��tempǰһ����㣬������� 
			head=temp;
		}
		head=p;
		p->next=temp;	
	}
}
Node *MoveLeft(Node *head,int k)//����kλ 
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
    Node *p=head1,*q=head2;//headΪ�ϲ��������
    Node *s=NULL;
    Node *pr=NULL;

    s=(Node *)malloc(sizeof(Node));//����½����ͷ���
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
    //ͷ��㽨����ϣ���ʱprָ��ͷ�ڵ�
    while(p != NULL&&q != NULL)
    {
        s=(Node *)malloc(sizeof(Node));
        if(s==NULL)
        {
            printf("No enough memory!");
            exit(0);
        }
        pr->next=s;//����s�ɹ���prָ���½��
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
        pr=s;//prָ���½���ϵĽ��
    }

    if(p == NULL)//p��ָ��������ѿ�
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
    cout<<"1.ɾ������Ԫ��"<<endl;
	cout<<"2.ɾ������������ظ�Ԫ��"<<endl;
	cout<<"3.��������"<<endl;
	cout<<"4.ѭ������"<<endl;
	cout<<"5.�ϲ������������飨����"<<endl;
	cout<<"������Ҫѡ��Ĺ������:";
    cin>>function;
    return function;
}
int main()
{
    Node *head=NULL;//ͷָ��
    char c;
    printf("Do you want to append a new node(Y/N)");
    scanf(" %c",&c);
    while(c=='Y'||c=='y')
    {
        head=Append(head);
        printf("Do you want to append a new node?(Y/N)");
        scanf(" %c",&c);
    }
    Show(head);//��ʾ��ǰ�����и��ڵ���Ϣ
    printf("table has been established!\n");
    while(1)
	{
    char ch=Menu(); 
	switch(ch)
	{
		case 1:
			int x;
			cout<<"������Ҫɾ����Ԫ�أ�"; 
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
            Show(head1);//��ʾ��ǰ�����и��ڵ���Ϣ
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
            Show(head2);//��ʾ��ǰ�����и��ڵ���Ϣ
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

