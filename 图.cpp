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
typedef struct marixgraph//邻接矩阵图 
{
	char vertex[MAX];//存储的顶点表 
	int edge[MAX][MAX];//边表，存储各顶点之间的邻接关系                                        
	int v,e;//顶点数,边数                                                                                                                                                                                                                                                                                   
}MTgraph;
typedef struct node//邻接表 
{
	int v;//邻接点域（下标） 
	int cost;
	struct node*next;//指下一边的指针域 
}EDGE;//边表结点 
typedef struct vertex//顶点表结点 
{
	char vertex;//顶点的数据域 
	EDGE *firstedge;//指向边表首结点的指针域 
}VERTEX;
typedef struct Adjgraph//图的邻接表 
{
	VERTEX verlist[MAX];//顶点表 
	int v,e;//图的顶点个数和边数 
}Adjgraph;
typedef struct
{
	char vertex;
	char parent;
}GeneTree;
bool visit[MAX];
int dfsorders[MAX];
int countdfs=1;
void  CreateMatrix(MTgraph *G)//建立邻接矩阵，存储顶点值和边的关系 
{
	int i,j,x,y;
	cin>>G->v>>G->e;
	cout<<"顶点数为"<<G->v<<",边数为"<<G->e<<endl;
    cout<<"顶点值依次为"<<endl; 
    for(i=0; i<G->v; i++)  
	{
	cin >> G->vertex[i];
	cout<< G->vertex[i]<<" ";
    }
    cout<<endl;
    cout<<"邻接矩阵为："<<endl;
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
        G->edge[y][x]=1;//无向图
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
    }//输出邻接矩阵
}
void CreateList(Adjgraph *G)
{
    int k,i,j;
    cin >> G->v>> G->e;//节点和边
    for (k=0; k<G->v; k++)
    {
        cin >> G->verlist[k].vertex;
        G->verlist[k].firstedge=NULL;
    }//头结点的初始化
    for(k=0; k<G->e; k++)
    {
        cin >> j >> i;
        EDGE* p=new EDGE;
        p->v=i;
        p->next=G->verlist[j].firstedge;
        G->verlist[j].firstedge=p;//在表头插入
        p=new EDGE;//建立无向图，所以还要反过来链接
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
    }//邻接表打印
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
	cout<<"将邻接表转化为邻接矩阵："<<endl;
	for(int i=0; i<m.v; i++)
    {
        for(int j=0; j<m.v; j++)
             {
			m.edge[i][i]=0;
            cout << m.edge[i][j] << " ";
        }
        cout << endl;
    }//输出邻接矩阵
}
void  MatrixToLink(MTgraph G)
{
    Adjgraph link;//邻接矩阵转邻接表
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
	cout<<"将邻接矩阵转换为邻接表为："<<endl; 
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
    }//邻接表打印
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
    if ((Q->rear+1)%MAXSIZE == Q->front)	/* 队列满的判断 */
        return 0;
    Q->data[Q->rear]=k;			/* 将元素e赋值给队尾 */
    Q->rear=(Q->rear+1)%MAXSIZE;/* rear指针向后移一位置， */								/* 若到最后则转到数组头部 */
    return  1;
}
int DeQueue(Queue *Q)
{
    int e;
    if (Q->front == Q->rear)			/* 队列空的判断 */
        return 0;
    e=Q->data[Q->front];				/* 将队头元素赋值给e */
    Q->front=(Q->front+1)%MAXSIZE;	/* front指针向后移一位置， */
    return  e;
}
#define    MAXSIZE 50
void DFS_NOT_REC(MTgraph G, int v) {
    int w;//顶点
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
        k = stack[top--];//当一个节点的所有临接点都已经入栈时，栈顶元素出栈并访问，然后这层访问完毕，下层入栈
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


void DFS_(MTgraph *G)//非递归深度邻接矩阵
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
void DFS1(MTgraph *G, int i)//递归深度邻接矩阵
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

void DFSTraverse1(MTgraph *G)//递归深度邻接矩阵
{
    int i;
    for(i = 0; i < G->v; i++)
        visited[i] = FALSE;
    for(i = 0; i < G->v; i++)
        if(!visited[i])
            DFS1(G, i);
}
void BFS1(MTgraph *G,int k)//非递归广度邻接矩阵
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
void BFSTraverse1(MTgraph *G)//非递归广度邻接矩阵
{
    int i;
    for(i = 0; i < G->v; i++)
        visited[i] = FALSE;
    for(i = 0; i < G->v; i++)
        if(!visited[i])
            BFS1(G, i);
}
int count =0;
void MBFS1(MTgraph *G,int k)//非递归广度邻接矩阵编码
{
    int i;

    Queue Q;
    MakeNull(&Q);
    visited[k]=TRUE;
    printf("顶点%d编码为%d ",k,count++);
    EnQueue(k,&Q);
    while(!Empty(&Q))
    {
        i=DeQueue(&Q);
        for(int j=0; j<G->v; j++)
        {
            if((G->edge[i][j]==1)&&(!visited[j]))
            {
                visited[j]=TRUE;
                printf("顶点%d编码为%d ",j,count++);
                EnQueue(j,&Q);
            }
        }
    }
}
void MBFSTraverse1(MTgraph *G)//非递归广度邻接矩阵编码
{
    int i;
    for(i = 0; i < G->v; i++)
        visited[i] = FALSE;
    for(i = 0; i < G->v; i++)
        if(!visited[i])
            MBFS1(G, i);
}

void DFS2(Adjgraph *G, int i)//递归深度邻接表
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
void DFSTraverse2(Adjgraph *G)//递归深度邻接表
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
void DFS__(Adjgraph *G)//非递归深度邻接表
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

void BFS2(Adjgraph *G,int k)//非递归广度邻接表
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
void BFSTraverse2(Adjgraph *G)//非递归广度邻接表
{
    int i;
    for(i = 0; i < G->v; i++)
        visited[i] = FALSE;
    for(i = 0; i < G->v; i++)
        if(!visited[i])
            BFS2(G, i);
}
int count2 =0;
void ABFS2(Adjgraph *G,int k)//非递归广度邻接表编码
{
    int i;

    EDGE *p;
    Queue Q;
    MakeNull(&Q);
    printf("顶点%d编码为%d ",k,count2++);
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
                printf("顶点%d编码为%d ",p->v,count2++);
                visited[p->v]=TRUE;
                EnQueue(p->v,&Q);
            }
            p=p->next;
        }
    }
}
void ABFSTraverse2(Adjgraph *G)//非递归广度邻接表编码
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
    visited[i] = TRUE; // 标记一下该点 已经被访问
    int first = 1;// 标记第一棵子树
    Node *q;
    for(int j= 0; j < G->v; j++)
    {
        if((G->edge[i][j]==1)&&(!visited[j]))
        {
            Node *p = (Node *)malloc(sizeof(Node));//申请空间 ， 创建节点
            p->data = j;
            p->firstchild =NULL;
            p->nextsibling = NULL;
            if(first)// 如果是第一个
            {
                T = p;
                first = 0;
            }
            else
            {
                q->nextsibling = p;
            }
            q  = p;
            DFSTree(G, j, q->firstchild);//构建 左子树
        }
    }
}
Node* DFSForest(MTgraph *G, Node *T)
{
    T = NULL;// 初始化 该森林为空
    int i;
    for( i = 0; i <G->v; i++) // 初始化标记数组
        visited[i] = FALSE;

    Node *q = NULL;// 指向 上一个兄弟
    for( i = 0; i < G->v; i++)
    {
        if(!visited[i])
        {
            Node *p = (Node *)malloc(sizeof(Node)); // 申请 空间
            //赋值 初始化节点
            p->data = i;
            p->firstchild = NULL;
            p->nextsibling = NULL;

            if(!T) // 如果该森林为空， 就让第一颗树的根， 作为森林的根
            {
                T = p;
            }
            else // 否则就是上一个兄弟 的右子树
            {
                q->nextsibling = p;
            }
            q = p; // 更新一下q

            DFSTree(G, i, p->firstchild); //  将 子树组成的森林  构建成 左子树
        }
    }
    return T;
}
void DFS_Tree(Adjgraph *G, int i, Node* T)
{
    visited[i] = TRUE; // 标记一下该点 已经被访问
    int first = 1;// 标记第一棵子树
    Node *q;
    EDGE *pe;
    pe = G->verlist[i].firstedge;
    while(pe)
    {
        if(!visited[pe->v])
        {
            Node *p = (Node *)malloc(sizeof(Node));//申请空间 ， 创建节点
            p->data =pe->v;
            p->firstchild =NULL;
            p->nextsibling = NULL;
            if(first)// 如果是第一个
            {
                T->firstchild = p;
                first = 0;
            }
            else
            {
                q->nextsibling = p;
            }
            q  = p;
            DFS_Tree(G, pe->v, q);//构建 左子树
        }
        pe = pe->next;
    }
}
Node* DFS_Forest(Adjgraph *G, Node *T)
{
    T = NULL;// 初始化 该森林为空
    int i;
    for( i = 0; i <G->v; i++) // 初始化标记数组
        visited[i] = FALSE;
    Node *q = NULL;// 指向 上一个兄弟
    for( i = 0; i < G->v; i++)
    {
        if(!visited[i])
        {
            Node *p = (Node *)malloc(sizeof(Node)); // 申请 空间
            //赋值 初始化节点
            p->data = i;
            p->firstchild = NULL;
            p->nextsibling = NULL;
            if(!T) // 如果该森林为空， 就让第一颗树的根， 作为森林的根
            {
                T = p;
            }
            else // 否则就是上一个兄弟 的右子树
            {
                q->nextsibling = p;
            }
            q = p; // 更新一下q
            DFS_Tree(G, i, p); //  将 子树组成的森林  构建成 左子树
        }
    }
    return T;
}
void PreOrder(Node *T)
{
    if(T==NULL)
        return;
    printf("%d  ",T->data);/* 显示结点数据，可以更改为其它对结点操作 */
    PreOrder(T->firstchild); /* 再先序遍历左子树 */
    PreOrder(T->nextsibling); /* 最后先序遍历右子树 */
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
        printf("顶点%d的度数为%d\n",i,degrees[i]);
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
        printf("顶点%d的度数为%d\n",i,degrees[i]);
    }
}
int main()
{
	MTgraph G1;
	Adjgraph G2;
	int N,degrees[MAX];
    freopen("tu.txt", "r", stdin);
    CreateMatrix(&G1);//建立邻接矩阵
	MatrixToLink(G1);
	printf("\n邻接矩阵各顶点度数\n");
    degree(&G1,degrees);
    fclose(stdin);
    freopen("tu.txt", "r", stdin);
    CreateList(&G2);
	LinkToMatrix(G2);
	printf("\n邻接表各顶点度数\n");
    degree2(&G2,degrees);
    fclose(stdin);  
	printf("\n非递归深度优先搜索邻接矩阵\n"); 
    DFS_1(&G1);
    printf("\n递归深度优先搜索邻接矩阵\n");
    DFSTraverse1(&G1);
    printf("\n广度优先搜索邻接矩阵\n");
    BFSTraverse1(&G1);
    printf("\n广度优先搜索邻接矩阵编码\n");
    MBFSTraverse1(&G1);
    printf("\n非递归深度优先搜索邻接表\n");
    DFS_2(&G2);
    printf("\n递归深度优先搜索邻接表\n");
    DFSTraverse2(&G2);
    printf("\n广度优先搜索邻接表\n");
    BFSTraverse2(&G2);
    printf("\n广度优先搜索邻接表编码\n");
    ABFSTraverse2(&G2);
    Node *T;
    T = DFSForest(&G1, T);
    printf("\n先序遍历邻接矩阵生成树\n");
    Node *T1;
    T1 = DFS_Forest(&G2, T1);
    PreOrder(T1); 
    printf("\n先序遍历邻接表生成树\n");
    PreOrder(T1);   
	return 0;	 
}
