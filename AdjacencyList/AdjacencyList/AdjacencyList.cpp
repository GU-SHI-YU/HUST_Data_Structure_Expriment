/*Graph On Adjacency List*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define DG 1
#define DN 2
#define UDG 3
#define UDN 4 //常量定义

#define INITLENGTH 80
#define INCREMENT 20
#define MAXVERTEXNUM 20

typedef int status;
typedef int ElemType;
typedef int KeyType;//数据元素类型定义

typedef struct Data {
	KeyType key;
	ElemType value;
};
typedef struct ArcNode {
	KeyType key;
	ArcNode* next;
};
typedef struct Vertex {
	Data data;
	ArcNode* firstArc;
};
typedef struct Graph{
	Vertex elem[MAXVERTEXNUM];
	char name[80];
    int type;
	int vernum;
	int arcnum;
};
typedef struct GraphList{
	Graph** graphs;
	int length;
	int listLength;
};

GraphList graphL;

status CreateGraph(Graph*& G, Data* V, int* VR);
status DestroyGraph(Graph*& G);
status LocateVex(Graph* G, KeyType u);
status PutVex(Graph* G, KeyType u, ElemType value);
int FirstAdjVex(Graph* G, int u);
int NextAdjVex(Graph* G, int v, int w);
status InsertVex(Graph* G, KeyType v);
status DeleteVex(Graph* G, KeyType v);
status InsertArc(Graph* G, KeyType v, KeyType w);
status DelteArc(Graph* G, KeyType v, KeyType w);
status DFSTraverse(Graph* G, status(*Visit)(Vertex v));
status BFSTraverse(Graph* G, status(*Visit)(Vertex v));
status SaveGraph(Graph* G, char* path);
status LoadGraph(Graph* G, char* path);
status Visit(Vertex v);

int main(void)
{
	graphL.graphs = (Graph**)malloc(sizeof(Graph*) * INITLENGTH);
	if (!graphL.graphs)
		exit(OVERFLOW);
	graphL.length = 0;
	graphL.listLength = INITLENGTH;
	graphL.graphs[0] = (Graph*)malloc(sizeof(Graph));
	if (!graphL.graphs[0])
		exit(OVERFLOW);
	strcpy(graphL.graphs[0]->name, "");
	Graph* G = graphL.graphs[0];//指向当前操作表
	int op = 1;
	status res;
	while (op)
	{
		system("cls");	printf("\n\n");
		printf("      Menu for Linear Table On Linked List \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. CreateGraph       9. InsertArc\n");
		printf("    	  2. DestroyGraph      10. DeleteArc\n");
		printf("    	  3. LocateVex         11. DFSTraverse\n");
		printf("    	  4. PutVex            12. BFSTraverse\n");
		printf("    	  5. FirstAdjVex       13. SaveGraph\n");
		printf("    	  6. NextAdjVex        14. LoadGraph\n");
		printf("    	  7. InsertVex         15. ShowAllGraphs\n");
		printf("    	  8. DeleteVex         16. GetGraph\n");
		printf("    	  0. Exit\n");
		printf("-------------------------------------------------\n");
		printf("    当前操作对象：%s       请选择你的操作[0~16]:", G->name);
		scanf("%d", &op);
		switch (op)
		{
        default:
            break;
		case 1:
			int asize, vsize;
			printf("请输入顶点数和边数：");
			scanf("%d%d", &vsize, &asize);
			printf("请输入顶点集（key，value）：");
			Data* V = (Data*)malloc(sizeof(Data) * vsize);
			int i;
			for (i = 0;i < vsize;i++)
				scanf("%d%d", &V[i].key, &V[i].value);
			printf("请输入边集(Vi,Vj的顶点角标)：");
			int* VR = (int*)malloc(sizeof(int) * (asize * 2));
			for (i = 0;i < asize;i += 2)
				scanf("%d%d", &VR[i], &VR[i + 1]);
			G = (Graph*)malloc(sizeof(Graph));
			if(!G)
				exit(OVERFLOW);
			G->arcnum = asize;
			G->vernum = vsize;
			res = CreateGraph(G,V,VR);
			if (res == ERROR)
				printf("顶点集有重复的关键字！\n");
			else if (res == INFEASIBLE)
				printf("图名已存在！\n");
			else if (res == OVERFLOW)
				printf("顶点数超过顶点上限！\n");
			else
				printf("无向图创建成功！\n");
			getchar();getchar();
			break;
		case 2:
			getchar();getchar();
			break;
		case 3:
			getchar();getchar();
			break;
		case 4:
			getchar();getchar();
			break;
		case 5:
			getchar();getchar();
			break;
		case 6:
			getchar();getchar();
			break;
		case 7:
			getchar();getchar();
			break;
		case 8:
			getchar();getchar();
			break;
		case 9:
			getchar();getchar();
			break;
		case 11:
			getchar();getchar();
			break;
		case 12:
			getchar();getchar();
			break;
		case 13:
			getchar();getchar();
			break;
		case 14:
			getchar();getchar();
			break;
		case 15:
			getchar();getchar();
			break;
		case 16:
			getchar();getchar();
			break;
		case 0:
			break;
		}
		printf("欢迎下次再使用本系统！\n");
		return 0;
	}
}
status CreateGraph(Graph*& G, Data* V, int* VR)
{
	char temp[80];
	printf("请输入图名：");
	scanf("%s", temp);
	int i, j;
	for (i = 1;i < graphL.length;i++)
		if (strcmp(temp, graphL.graphs[i]->name))
			return INFEASIBLE;
	if (G->vernum > MAXVERTEXNUM)
		return OVERFLOW;
	for (i = 0;i < G->vernum;i++)
		for (j = i;j < G->vernum;j++)
			if (V[i].key == V[j].key)
				return ERROR;
	graphL.length++;
	if(graphL.length >= graphL.listLength)
	{
		Graph** tempG = graphL.graphs;
		graphL.graphs = (Graph**)realloc(graphL.graphs, sizeof(Graph) * (graphL.length + INCREMENT));
		if(!graphL.graphs)
		{
			free(tempG);
			exit(OVERFLOW);
		}
		graphL.listLength += INCREMENT;
	}
	strcpy(G->name, temp);
	for(i = 0;i < G->vernum;i++)
	{
		G->elem[i].data = V[i];
		G->elem[i].firstArc = NULL;
	}
	for(i = 0;i < G->arcnum; i+=2)
	{
		ArcNode* p = (ArcNode*)malloc(sizeof(ArcNode));
		if (!p)
			exit(OVERFLOW);
		p->key = G->elem[VR[i + 1]].data.key;
		p->next = G->elem[VR[i]].firstArc;
		G->elem[VR[i]].firstArc = p;
		if(VR[i] != VR[i + 1])
		{
			p = (ArcNode*)malloc(sizeof(ArcNode));
	        if (!p)
			    exit(OVERFLOW);
			p->key = G->elem[VR[i]].data.key;
			p->next = G->elem[VR[i + 1]].firstArc;
			G->elem[VR[i + 1]].firstArc = p;
		}
	}
	graphL.graphs[graphL.length] = G;
	return OK;
}
status BFSTraverse(Graph* G, status(*Visit)(Vertex v))
{
    if(!G)
        return ERROR;
    int *visited;
    visited = (int*)malloc(sizeof(int) * G->vernum);
    if(!visited)
        exit(OVERFLOW);
    int i;
    for(i = 0; i < G->vernum; i++)
    {
        visited[i] = 0;
    }
    Vertex* q;
    q = (Vertex*)malloc(sizeof(Vertex) * G->vernum);
    if(!q)
        exit(OVERFLOW);
    int top = 0;
    int bottom = 0;
    q[top++] = G->elem[0];
    visited[0] = 1;
    Vertex n;
    while(top != bottom)
    {
        n = q[top--];
        Visit(n);
        ArcNode* p = n.firstArc;
        while(p)
        {
            if(visited[p->key] == 0)
            {
                visited[p->key] = 1;
                q[top++] = G->elem[p->key];
            }
            p = p->next;
        }
    }
    return OK;
}
