#include<iostream>
#include<stdio.h>
#include<stdlib.h> 
using namespace std;
#define MAX 50
#define TRUE 1
#define FALSE 0
#define MAXSIZE 50
#define MAX 50
#define INFINITY   65535
typedef struct marixgraph//�ڽӾ���ͼ 
{
	char vertex[MAX];//�洢�Ķ���� 
	int edge[MAX][MAX];//�߱��洢������֮����ڽӹ�ϵ                                        
	int v,e;//������,����                                                                                                                                                                                                                                                                                   
}MTgraph;
typedef struct node//�ڽӱ� 
{
	int v;//�ڽӵ����±꣩ 
	int cost;
	struct node*next;//ָ��һ�ߵ�ָ���� 
}EDGE;//�߱��� 
typedef struct vertex//������� 
{
	char vertex;//����������� 
	EDGE *firstedge;//ָ��߱��׽���ָ���� 
}VERTEX;
typedef struct Adjgraph//ͼ���ڽӱ� 
{
	VERTEX verlist[MAX];//����� 
	int v,e;//ͼ�Ķ�������ͱ��� 
}Adjgraph;
typedef struct
{
	char vertex;
	char parent;
}GeneTree;
bool visit[MAX];
int dfsorders[MAX];
int countdfs=1;
void  CreateMatrix(MTgraph *G)//�����ڽӾ��󣬴洢����ֵ�ͱߵĹ�ϵ 
{
	int i,j,x,y;
	cin>>G->v>>G->e;
	cout<<"������Ϊ"<<G->v<<",����Ϊ"<<G->e<<endl;
    cout<<"����ֵ����Ϊ"<<endl; 
    for(i=0; i<G->v; i++)  
	{
	cin >> G->vertex[i];
	cout<< G->vertex[i]<<" ";
    }
    cout<<endl;
    cout<<"�ڽӾ���Ϊ��"<<endl;
    for(i=0; i<G->v; i++)
    {
        for(j=0; j<G->v; j++)
        {
			G->edge[i][j]=0;
		}
	}
    for(i=0; i<G->e; i++)
    {
        cin >> x >> y;
        G->edge[x][y]=1;
        G->edge[y][x]=1;//����ͼ
    }
    for(i=0; i<G->v; i++)
    {
			G->edge[i][i]=0;
	}
    for(i=0; i<G->v; i++)
    {
        for(j=0; j<G->v; j++)
            cout << G->edge[i][j] << " ";
        cout << endl;
    }//����ڽӾ���
}
void CreateList(Adjgraph *G)
{
    int k,i,j;
    cin >> G->v>> G->e;//�ڵ�ͱ�
    for (k=0; k<G->v; k++)
    {
        cin >> G->verlist[k].vertex;
        G->verlist[k].firstedge=NULL;
    }//ͷ���ĳ�ʼ��
    for(k=0; k<G->e; k++)
    {
        cin >> j >> i;
        EDGE* p=new EDGE;
        p->v=i;
        p->next=G->verlist[j].firstedge;
        G->verlist[j].firstedge=p;//�ڱ�ͷ����
        p=new EDGE;//��������ͼ�����Ի�Ҫ����������
        p->v=j;
        p->next=G->verlist[i].firstedge;
        G->verlist[i].firstedge=p;
    }
    for(i=0; i<G->v; i++)
    {
        cout << G->verlist[i].vertex;
        EDGE *m=G->verlist[i].firstedge;
        while(m!=NULL)
        {
            cout<<"->"<<G->verlist[m->v].vertex;
            m=m->next;
        }
        printf("->NULL\n");
    }//�ڽӱ��ӡ
}
void LinkToMatrix(Adjgraph L)
{
	MTgraph m;
	EDGE *p=NULL;
	m.v=L.v;
	for(int i=0;i<m.v;i++)
	{
		m.vertex[i]=L.verlist[i].vertex;
		for(int j=0;j<m.v;j++)
		{
			m.edge[i][j]=0;
		}
	}
	for(int i=0;i<L.v;i++)
	{
		p=L.verlist[i].firstedge;
		while(p!=NULL)
		{
			m.edge[i][p->v]=1;
			p=p->next;
		}
	}
	cout<<"���ڽӱ�ת��Ϊ�ڽӾ���"<<endl;
	for(int i=0; i<m.v; i++)
    {
        for(int j=0; j<m.v; j++)
             {
			m.edge[i][i]=0;
            cout << m.edge[i][j] << " ";
        }
        cout << endl;
    }//����ڽӾ���
}
void  MatrixToLink(MTgraph G)
{
    Adjgraph link;//�ڽӾ���ת�ڽӱ�
	for (int i = 0; i < G.v; i++)
	{
		link.verlist[i].vertex = G.vertex[i];
		link.verlist[i].firstedge = NULL;
		link.v++;
		for (int j = 0; j < G.v; j++)
		{
			if (G.edge[i][j] != 0)
			{
				EDGE* p = new EDGE, * q = link.verlist[i].firstedge;
				if (q == NULL)
				{
					p->v = j;
					p->cost = G.edge[i][j];
					p->next = NULL;
					link.verlist[i].firstedge = p;
				}
				else
				{
					while (q->next != NULL)
						q = q->next;
					p->v = j;
					p->cost =G.edge[i][j];
					p->next = NULL;
					q->next = p;
				}
				link.e++;
			}
		}
	}
	cout<<"���ڽӾ���ת��Ϊ�ڽӱ�Ϊ��"<<endl; 
	for(int i=0; i<link.v; i++)
    {
        cout << link.verlist[i].vertex;
        EDGE *m=link.verlist[i].firstedge;
        while(m!=NULL)
        {
            cout<<"->"<<link.verlist[m->v].vertex;
            m=m->next;
        }
        printf("->NULL\n");
    }//�ڽӱ��ӡ
}
#define TRUE 1
#define FALSE 0
typedef int Boolean;
Boolean visited[MAX];
typedef struct
{
    int data[MAXSIZE];
    int front;
    int rear;
} Queue;
void MakeNull(Queue*Q)
{
    Q->front=0;
    Q->rear=0;
}
int Empty(Queue*Q)
{
    if(Q->front=Q->rear)
        return 1;
    else
        return 0;
}
int EnQueue(int k,Queue*Q)
{
    if ((Q->rear+1)%MAXSIZE == Q->front)	/* ���������ж� */
        return 0;
    Q->data[Q->rear]=k;			/* ��Ԫ��e��ֵ����β */
    Q->rear=(Q->rear+1)%MAXSIZE;/* rearָ�������һλ�ã� */								/* ���������ת������ͷ�� */
    return  1;
}
int DeQueue(Queue *Q)
{
    int e;
    if (Q->front == Q->rear)			/* ���пյ��ж� */
        return 0;
    e=Q->data[Q->front];				/* ����ͷԪ�ظ�ֵ��e */
    Q->front=(Q->front+1)%MAXSIZE;	/* frontָ�������һλ�ã� */
    return  e;
}
#define    MAXSIZE 50
void DFS_NOT_REC(MTgraph G, int v) {
    int w;//����
    int top = -1;
    int stack[30];
    int visited[30];
    for (int i = 0; i < G.v; i++) {
        visited[i] = 0;
    }
    stack[++top] = v;
    visited[v] = 1;
    int k;
    while (top != -1) {
        k = stack[top--];//��һ���ڵ�������ٽӵ㶼�Ѿ���ջʱ��ջ��Ԫ�س�ջ�����ʣ�Ȼ����������ϣ��²���ջ
        printf("%d", k);
        for (int i = 0; i < G.v; i++) {
            w = i;
            if (G.edge[k][i] != 0 && !visited[w]) {
                stack[++top] = w;
                visited[w] = 1;
            }
        }
    }
}


void DFS_(MTgraph *G)//�ǵݹ�����ڽӾ���
{
    int stacks[MAXSIZE];
    int i;
    for(i = 0; i < G->v; i++)
        visited[i] = FALSE;
    int top = -1;
    i=0;
    visited[i] = TRUE;
    printf("%d ",i);
    stacks[++top] =i;
    while(top !=-1)
    {
        i = stacks[top];
        int tmp = 0;
        for(int j = 0 ; j <G->v; j++)
        {
            if( G->edge[i][j] ==1&& !visited[j])
            {
                visited[j] = TRUE;
                printf("%d ",j);
                stacks[++top] =j;
                break;
            }
            tmp = j;
        }
        if( tmp == G->v-1)
            top--;
    }
}
void DFS1(MTgraph *G, int i)//�ݹ�����ڽӾ���
{
    int j;
    visited[i] = TRUE;
    printf("%d ",i);
    for(j=0; j<G->v; j++)
    {
        if((G->edge[i][j]==1)&&(!visited[j]))
            DFS1(G, j);
    }
}
void DFS_1(MTgraph *G)
{
    int i;
    for(i = 0; i < G->v; i++)
        visited[i] = FALSE;
    for(i = 0; i < G->v; i++)
        if(!visited[i])
            DFS1(G, i);
}

void DFSTraverse1(MTgraph *G)//�ݹ�����ڽӾ���
{
    int i;
    for(i = 0; i < G->v; i++)
        visited[i] = FALSE;
    for(i = 0; i < G->v; i++)
        if(!visited[i])
            DFS1(G, i);
}
void BFS1(MTgraph *G,int k)//�ǵݹ����ڽӾ���
{
    int i;
    Queue Q;
    MakeNull(&Q);
    visited[k]=TRUE;
    printf("%d ",k);
    EnQueue(k,&Q);
    while(!Empty(&Q))
    {
        i=DeQueue(&Q);
        for(int j=0; j<G->v; j++)
        {
            if((G->edge[i][j]<INFINITY)&&(!visited[j]))
            {
                visited[j]=TRUE;
                printf("%d ",j);
                EnQueue(j,&Q);
            }
        }
    }
}
void BFSTraverse1(MTgraph *G)//�ǵݹ����ڽӾ���
{
    int i;
    for(i = 0; i < G->v; i++)
        visited[i] = FALSE;
    for(i = 0; i < G->v; i++)
        if(!visited[i])
            BFS1(G, i);
}
int count =0;
void MBFS1(MTgraph *G,int k)//�ǵݹ����ڽӾ������
{
    int i;

    Queue Q;
    MakeNull(&Q);
    visited[k]=TRUE;
    printf("����%d����Ϊ%d ",k,count++);
    EnQueue(k,&Q);
    while(!Empty(&Q))
    {
        i=DeQueue(&Q);
        for(int j=0; j<G->v; j++)
        {
            if((G->edge[i][j]==1)&&(!visited[j]))
            {
                visited[j]=TRUE;
                printf("����%d����Ϊ%d ",j,count++);
                EnQueue(j,&Q);
            }
        }
    }
}
void MBFSTraverse1(MTgraph *G)//�ǵݹ����ڽӾ������
{
    int i;
    for(i = 0; i < G->v; i++)
        visited[i] = FALSE;
    for(i = 0; i < G->v; i++)
        if(!visited[i])
            MBFS1(G, i);
}

void DFS2(Adjgraph *G, int i)//�ݹ�����ڽӱ�
{
    EDGE *p;
    visited[i] = TRUE;
    printf("%d ",i);
    p = G->verlist[i].firstedge;
    while(p)
    {
        if(!visited[p->v])
            DFS2(G, p->v);
        p = p->next;
    }
}
void DFSTraverse2(Adjgraph *G)//�ݹ�����ڽӱ�
{
    int i;
    for(i = 0; i < G->v; i++)
        visited[i] = FALSE;
    for(i = 0; i < G->v; i++)
        if(!visited[i])
            DFS2(G, i);
}
void DFS_2(Adjgraph *G)
{
	int i;
    for(i = 0; i < G->v; i++)
        visited[i] = FALSE;
    for(i = 0; i < G->v; i++)
        if(!visited[i])
            DFS2(G, i);
}
void DFS__(Adjgraph *G)//�ǵݹ�����ڽӱ�
{
    int stacks[MAXSIZE];
    int i;
    for(i = 0; i < G->v; i++)
        visited[i] = FALSE;
    int top = -1;
    i=0;
    visited[i] = TRUE;
    printf("%d ",i);
    stacks[++top] =i;
    while(top !=-1)
    {
        i = stacks[top];
        int tmp = 0;
        EDGE *p;
        p = G->verlist[i].firstedge;
        while(p)
        {
            if(!visited[p->v])
            {
                visited[p->v]=TRUE;
                printf("%d ",p->v);
                stacks[++top] =p->v;
                break;
            }
            p = p->next;
        }
        if( p==NULL)
            top--;
    }
}

void BFS2(Adjgraph *G,int k)//�ǵݹ����ڽӱ�
{
    int i;
    EDGE *p;
    Queue Q;
    MakeNull(&Q);
    printf("%d ",k);
    visited[k]=TRUE;
    EnQueue(k,&Q);
    while(!Empty(&Q))
    {
        i=DeQueue(&Q);
        p=G->verlist[i].firstedge;
        while(p)
        {
            if(!visited[p->v])
            {
                printf("%d ",p->v);
                visited[p->v]=TRUE;
                EnQueue(p->v,&Q);
            }
            p=p->next;
        }
    }
}
void BFSTraverse2(Adjgraph *G)//�ǵݹ����ڽӱ�
{
    int i;
    for(i = 0; i < G->v; i++)
        visited[i] = FALSE;
    for(i = 0; i < G->v; i++)
        if(!visited[i])
            BFS2(G, i);
}
int count2 =0;
void ABFS2(Adjgraph *G,int k)//�ǵݹ����ڽӱ����
{
    int i;

    EDGE *p;
    Queue Q;
    MakeNull(&Q);
    printf("����%d����Ϊ%d ",k,count2++);
    visited[k]=TRUE;
    EnQueue(k,&Q);
    while(!Empty(&Q))
    {
        i=DeQueue(&Q);
        p=G->verlist[i].firstedge;
        while(p)
        {
            if(!visited[p->v])
            {
                printf("����%d����Ϊ%d ",p->v,count2++);
                visited[p->v]=TRUE;
                EnQueue(p->v,&Q);
            }
            p=p->next;
        }
    }
}
void ABFSTraverse2(Adjgraph *G)//�ǵݹ����ڽӱ����
{
    int i;
    for(i = 0; i < G->v; i++)
        visited[i] = FALSE;
    for(i = 0; i < G->v; i++)
        if(!visited[i])
            ABFS2(G, i);
}
typedef struct Tnode
{
    int data;
    struct Tnode *firstchild;
    struct Tnode *nextsibling;
} Node;
void DFSTree(MTgraph *G, int i, Node* T)
{
    visited[i] = TRUE; // ���һ�¸õ� �Ѿ�������
    int first = 1;// ��ǵ�һ������
    Node *q;
    for(int j= 0; j < G->v; j++)
    {
        if((G->edge[i][j]==1)&&(!visited[j]))
        {
            Node *p = (Node *)malloc(sizeof(Node));//����ռ� �� �����ڵ�
            p->data = j;
            p->firstchild =NULL;
            p->nextsibling = NULL;
            if(first)// ����ǵ�һ��
            {
                T = p;
                first = 0;
            }
            else
            {
                q->nextsibling = p;
            }
            q  = p;
            DFSTree(G, j, q->firstchild);//���� ������
        }
    }
}
Node* DFSForest(MTgraph *G, Node *T)
{
    T = NULL;// ��ʼ�� ��ɭ��Ϊ��
    int i;
    for( i = 0; i <G->v; i++) // ��ʼ���������
        visited[i] = FALSE;

    Node *q = NULL;// ָ�� ��һ���ֵ�
    for( i = 0; i < G->v; i++)
    {
        if(!visited[i])
        {
            Node *p = (Node *)malloc(sizeof(Node)); // ���� �ռ�
            //��ֵ ��ʼ���ڵ�
            p->data = i;
            p->firstchild = NULL;
            p->nextsibling = NULL;

            if(!T) // �����ɭ��Ϊ�գ� ���õ�һ�����ĸ��� ��Ϊɭ�ֵĸ�
            {
                T = p;
            }
            else // ���������һ���ֵ� ��������
            {
                q->nextsibling = p;
            }
            q = p; // ����һ��q

            DFSTree(G, i, p->firstchild); //  �� ������ɵ�ɭ��  ������ ������
        }
    }
    return T;
}
void DFS_Tree(Adjgraph *G, int i, Node* T)
{
    visited[i] = TRUE; // ���һ�¸õ� �Ѿ�������
    int first = 1;// ��ǵ�һ������
    Node *q;
    EDGE *pe;
    pe = G->verlist[i].firstedge;
    while(pe)
    {
        if(!visited[pe->v])
        {
            Node *p = (Node *)malloc(sizeof(Node));//����ռ� �� �����ڵ�
            p->data =pe->v;
            p->firstchild =NULL;
            p->nextsibling = NULL;
            if(first)// ����ǵ�һ��
            {
                T->firstchild = p;
                first = 0;
            }
            else
            {
                q->nextsibling = p;
            }
            q  = p;
            DFS_Tree(G, pe->v, q);//���� ������
        }
        pe = pe->next;
    }
}
Node* DFS_Forest(Adjgraph *G, Node *T)
{
    T = NULL;// ��ʼ�� ��ɭ��Ϊ��
    int i;
    for( i = 0; i <G->v; i++) // ��ʼ���������
        visited[i] = FALSE;
    Node *q = NULL;// ָ�� ��һ���ֵ�
    for( i = 0; i < G->v; i++)
    {
        if(!visited[i])
        {
            Node *p = (Node *)malloc(sizeof(Node)); // ���� �ռ�
            //��ֵ ��ʼ���ڵ�
            p->data = i;
            p->firstchild = NULL;
            p->nextsibling = NULL;
            if(!T) // �����ɭ��Ϊ�գ� ���õ�һ�����ĸ��� ��Ϊɭ�ֵĸ�
            {
                T = p;
            }
            else // ���������һ���ֵ� ��������
            {
                q->nextsibling = p;
            }
            q = p; // ����һ��q
            DFS_Tree(G, i, p); //  �� ������ɵ�ɭ��  ������ ������
        }
    }
    return T;
}
void PreOrder(Node *T)
{
    if(T==NULL)
        return;
    printf("%d  ",T->data);/* ��ʾ������ݣ����Ը���Ϊ�����Խ����� */
    PreOrder(T->firstchild); /* ��������������� */
    PreOrder(T->nextsibling); /* ���������������� */
}
void degree(MTgraph *G,int degrees[])
{
    int i,j;
    for(i=0; i<G->v; i++)
    {
        degrees[i]=0;
        for(j=0; j<G->v; j++)
        {
            if(G->edge[i][j]==1)
                degrees[i]++;
        }
        printf("����%d�Ķ���Ϊ%d\n",i,degrees[i]);
    }
}
void degree2(Adjgraph *G,int degrees[])
{
    int i,j;
    for(i=0; i<G->v; i++)
    {
        degrees[i]=0;
        EDGE *p;
        p= G->verlist[i].firstedge;
        while(p)
        {
            degrees[i]++;
            p=p->next;
        }
        printf("����%d�Ķ���Ϊ%d\n",i,degrees[i]);
    }
}
int main()
{
	MTgraph G1;
	Adjgraph G2;
	int N,degrees[MAX];
    freopen("tu.txt", "r", stdin);
    CreateMatrix(&G1);//�����ڽӾ���
	MatrixToLink(G1);
	printf("\n�ڽӾ�����������\n");
    degree(&G1,degrees);
    fclose(stdin);
    freopen("tu.txt", "r", stdin);
    CreateList(&G2);
	LinkToMatrix(G2);
	printf("\n�ڽӱ���������\n");
    degree2(&G2,degrees);
    fclose(stdin);  
	printf("\n�ǵݹ�������������ڽӾ���\n"); 
    DFS_1(&G1);
    printf("\n�ݹ�������������ڽӾ���\n");
    DFSTraverse1(&G1);
    printf("\n������������ڽӾ���\n");
    BFSTraverse1(&G1);
    printf("\n������������ڽӾ������\n");
    MBFSTraverse1(&G1);
    printf("\n�ǵݹ�������������ڽӱ�\n");
    DFS_2(&G2);
    printf("\n�ݹ�������������ڽӱ�\n");
    DFSTraverse2(&G2);
    printf("\n������������ڽӱ�\n");
    BFSTraverse2(&G2);
    printf("\n������������ڽӱ����\n");
    ABFSTraverse2(&G2);
    Node *T;
    T = DFSForest(&G1, T);
    printf("\n��������ڽӾ���������\n");
    Node *T1;
    T1 = DFS_Forest(&G2, T1);
    PreOrder(T1); 
    printf("\n��������ڽӱ�������\n");
    PreOrder(T1);   
	return 0;	 
}
