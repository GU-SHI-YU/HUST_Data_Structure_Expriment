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
#define UDN 4 

#define INITLENGTH 80
#define INCREMENT 20
#define MAXVERTEXNUM 20 //常量定义

typedef int status;
typedef int ElemType;
typedef int KeyType;//数据元素类型定义

typedef struct Data {
	KeyType key;
	ElemType value;
};
typedef struct ArcNode {
	int pos;
	ArcNode* next;
};
typedef struct Vertex {
	Data data;
	ArcNode* firstArc;
};
typedef struct Graph{
	Vertex elem[MAXVERTEXNUM];
	char name[80];
    //int type;
	int vernum;
	int arcnum;
};
typedef struct GraphList{
	Graph** graphs;
	int length;
	int listLength;
}; //结构体类型定义

GraphList graphL;
/*函数定义开始*/
status CreateGraph(Graph*& G, Data* V, int* VR);
status DestroyGraph(Graph*& G);
int LocateVex(Graph* G, KeyType u);
status PutVex(Graph* G, KeyType u, ElemType value);
int FirstAdjVex(Graph* G, int u);
int NextAdjVex(Graph* G, int v, int w);
status InsertVex(Graph* G, Vertex v);
status DeleteVex(Graph* G, int v);
status InsertArc(Graph* G, int v, int w);
status DeleteArc(Graph* G, int v, int w);
status DFSTraverse(Graph* G, status(*Visit)(Vertex v));
status BFSTraverse(Graph* G, status(*Visit)(Vertex v));
status SaveGraph(Graph* G, char* path);
status LoadGraph(Graph*& G, char* path);
status ShowAllGraphs();
status GetGraph(Graph*& G, char* name);
status Visit(Vertex v);
/*函数定义结束*/
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
	Graph* G = graphL.graphs[0];//指向当前操作图
	int op = 1;
	status res = -1;
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
		case 1:
			int asize, vsize;
			printf("请输入顶点数和边数：");
			scanf("%d%d", &vsize, &asize);
			printf("请输入顶点集（key，value）：");
			Data* V;
			V = (Data*)malloc(sizeof(Data) * vsize);
			int i;
			for (i = 0;i < vsize;i++)
				scanf("%d%d", &V[i].key, &V[i].value);
			printf("请输入边集(Vi,Vj的顶点角标)：");
			int* VR;
			VR = (int*)malloc(sizeof(int) * (asize * 2));
			for (i = 0;i < asize * 2;i += 2)
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
			res = DestroyGraph(G);
			if (res == OK)
				printf("无向图销毁成功！\n");
			else
				printf("无向图不存在！\n");
			getchar();getchar();
			break;
		case 3:
			int res_lv;
			KeyType e_lv;
			printf("请输入参数（查找关键字）：");
			scanf("%d", &e_lv);
			res_lv = LocateVex(G,e_lv);
			if (res_lv == -2)
				printf("无向图不存在！\n");
			else if (res_lv == -1)
				printf("没有关键字为%d的顶点！\n", e_lv);
			else
				printf("找到顶点：关键字%d,值%d！\n", G->elem[res_lv].data.key, G->elem[res_lv].data.value);
			getchar();getchar();
			break;
		case 4:
			KeyType e_pv;
			ElemType v_pv;
			printf("请输入参数（查找关键字和值）：");
			scanf("%d%d", &e_pv, &v_pv);
			res = PutVex(G, e_pv, v_pv);
			if (res == ERROR)
				printf("无向图不存在！\n");
			else if (res == INFEASIBLE)
				printf("无向图不存在关键字为%d的顶点！\n",e_pv);
			else
				printf("关键字为%d的顶点已赋值为%d！\n",e_pv,v_pv);
			getchar();getchar();
			break;
		case 5:
			int res_fa;
			int e_fa;
			printf("请输入参数（查找顶点角标）：");
			scanf("%d", &e_fa);
			res_fa = FirstAdjVex(G, e_fa);
			if (res_fa == -2)
				printf("无向图不存在！\n");
			else if (res_fa == -1)
				printf("角标为%d的顶点没有邻接点！\n", e_fa);
			else if (res_fa == -3)
				printf("输入参数有误！\n");
			else
				printf("找到关键字为%d顶点第一个邻接点：关键字%d,值%d！\n", G->elem[e_fa].data.key, G->elem[res_fa].data.key, G->elem[res_fa].data.value);
			getchar();getchar();
			break;
		case 6:
			int res_na;
			int e_na;
			int w_na;
			printf("请输入参数（查找顶点角标,邻接点角标）：");
			scanf("%d%d", &e_na, &w_na);
			res_na = NextAdjVex(G, e_na, w_na);
			if (res_na == -2)
				printf("无向图不存在！\n");
			else if (res_na == -1)
				printf("没有角标为%d的顶点！\n", e_fa);
			else if (res_na == -3)
				printf("输入参数有误！\n");
			else
				printf("找到关键字为%d顶点的角标为%d的邻接点后一个邻接点：关键字%d,值%d！\n", G->elem[e_na].data.key, G->elem[w_na].data.key, G->elem[res_na].data.key, G->elem[res_na].data.value);
			getchar();getchar();
			break;
		case 7:
			Vertex v_iv;
			printf("请输入参数（插入节点关键字，值）：");
			scanf("%d%d", &v_iv.data.key, &v_iv.data.value);
			res = InsertVex(G, v_iv);
			if (res == ERROR)
				printf("无向图不存在！\n");
			else if (res == INFEASIBLE)
				printf("已经存在关键字为%d的顶点！\n", v_iv.data.key);
			else if (res == OVERFLOW)
				printf("图顶点已达最大值！\n");
			else
				printf("顶点已插入！\n");
			getchar();getchar();
			break;
		case 8:
			int v_dv;
			printf("请输入参数（删除节点角标）：");
			scanf("%d", &v_dv);
			res = DeleteVex(G, v_dv);
			if (res == ERROR)
				printf("无向图不存在！\n");
			else if (res == INFEASIBLE)
				printf("不存在角标为%d的顶点！\n", v_dv);
			else
				printf("顶点已删除！\n");
			getchar();getchar();
			break;
		case 9:
			int v_ia;
			int w_ia;
			printf("请输入参数（插入边顶点角标i, j）：");
			scanf("%d%d", &v_ia, &w_ia);
			res = InsertArc(G, v_ia, w_ia);
			if (res == ERROR)
				printf("无向图不存在！\n");
			else if (res == INFEASIBLE)
				printf("不存在角标为%d或%d的顶点！\n", v_ia, w_ia);
			else
				printf("边已插入！\n");
			getchar();getchar();
			break;
		case 10:
			int v_da;
			int w_da;
			printf("请输入参数（删除边顶点角标i, j）：");
			scanf("%d%d", &v_da, &w_da);
			res = DeleteArc(G, v_da, w_da);
			if (res == ERROR)
				printf("无向图不存在！\n");
			else if (res == INFEASIBLE)
				printf("不存在角标为%d或%d的顶点！\n", v_da, w_da);
			else
				printf("边已删除！\n");
			getchar();getchar();
			break;
		case 11:
			res = DFSTraverse(G, Visit);
			if (res == OK)
			{
				printf("深度优先遍历完毕！\n");
			}
			else
			{
				printf("图不存在！\n");
			}
			getchar();getchar();
			break;
		case 12:
			res = BFSTraverse(G, Visit);
			if(res == OK)
			{
				printf("宽度优先遍历完毕！\n");
			}
			else
			{
				printf("图不存在！\n");
			}
			getchar();getchar();
			break;
		case 13:
			char path_sg[80];
			printf("请输入参数（保存路径）：");
			scanf("%s", path_sg);
			res = SaveGraph(G, path_sg);
			if (res == ERROR)
				printf("无向图不存在！\n");
			else if (res == INFEASIBLE)
				printf("路径错误！\n");
			else
				printf("图已保存！\n");
			getchar();getchar();
			break;
		case 14:
			char path_lg[80];
			printf("请输入参数（保存路径）：");
			scanf("%s", path_lg);
			res = LoadGraph(G, path_lg);
			if (res == INFEASIBLE)
				printf("路径错误！\n");
			if (res == OVERFLOW)
				printf("已存在图名为%s的图！\n",path_lg);
			else
				printf("图已加载到%s！\n",G->name);
			getchar();getchar();
			break;
		case 15:
			res = ShowAllGraphs();
			if (res == ERROR)
				printf("图线性表为空！\n");
			else
				printf("所有图的宽度优先序列打印完毕！\n");
			getchar();getchar();
			break;
		case 16:
			char name_gg[80];
			printf("请输入参数（图名）");
			scanf("%s", name_gg);
			res = GetGraph(G, name_gg);
			if (res == ERROR)
				printf("图线性表为空！\n");
			else if (res == INFEASIBLE)
				printf("没有名字为%s的图！\n", name_gg);
			else
				printf("已切换到%s！\n", name_gg);
			getchar();getchar();
			break;
		case 0:
			break;
		}
	}
	printf("欢迎下次再使用本系统！\n");
	return 0;
}
status CreateGraph(Graph*& G, Data* V, int* VR)
{
	char temp[80];
	printf("请输入图名：");
	scanf("%s", temp);
	int i, j;
	for (i = 1;i <= graphL.length;i++) //检测图名是否唯一
		if (!strcmp(temp, graphL.graphs[i]->name))
			return INFEASIBLE;
	if (G->vernum > MAXVERTEXNUM)
		return OVERFLOW;
	for (i = 0;i < G->vernum;i++)
		for (j = 0;j < i;j++)
			if (V[i].key == V[j].key) //检测关键字是否唯一
			{
				setbuf(stdin, NULL); //清空输入流
				return ERROR;
			}
	for(i = 0;i < 20;i++)
	{
		G->elem[i].data.key = 0;
		G->elem[i].firstArc = NULL;
	}
	for(i = 0;i < G->vernum;i++)
	{
		G->elem[i].data = V[i];
		G->elem[i].firstArc = NULL;
	}
	for(i = 0;i < G->arcnum * 2; i+=2)
	{
		ArcNode* p = (ArcNode*)malloc(sizeof(ArcNode));
		if (!p)
			exit(OVERFLOW);
		p->pos = VR[i + 1];
		p->next = G->elem[VR[i]].firstArc;
		G->elem[VR[i]].firstArc = p;
		if(VR[i] != VR[i + 1])
		{
			p = (ArcNode*)malloc(sizeof(ArcNode));
	        if (!p)
			    exit(OVERFLOW);
			p->pos = VR[i];
			p->next = G->elem[VR[i + 1]].firstArc;
			G->elem[VR[i + 1]].firstArc = p;
		}
	}
	graphL.length++;
	if (graphL.length >= graphL.listLength) //如果图表达到上限，扩展表
	{
		Graph** tempG = graphL.graphs;
		graphL.graphs = (Graph * *)realloc(graphL.graphs, sizeof(Graph) * (graphL.length + INCREMENT));
		if (!graphL.graphs)
		{
			free(tempG);
			exit(OVERFLOW);
		}
		graphL.listLength += INCREMENT;
	}
	strcpy(G->name, temp);
	graphL.graphs[graphL.length] = G;
	return OK;
}
status DestroyGraph(Graph*& G)
{
	if (!G)
		return ERROR;
	ArcNode* p, * q;
	int i;
	for (i = 0;i < G->vernum;i++)
	{
		p = G->elem[i].firstArc;
		if (!p)
			continue;
		q = p->next;
		while (p)
		{
			free(p);
			p = q;
			if(p)
				q = p->next;
		}
	}
	free(G->elem);
	int j;
	for (i = 0;i < graphL.length;i++) //从图表中删除图
	{
		if (strcmp(G->name, graphL.graphs[i]->name))
			for (j = i;j < graphL.length - 1;j++)
			{
				graphL.graphs[j] = graphL.graphs[j + 1];
			}
	}
	graphL.length--;
	G = graphL.graphs[0];
	return OK;
}
int LocateVex(Graph* G, KeyType u)
{
	if (!G)
		return -2;
	int i;
	for(i = 0;i < G->vernum;i++)
	{
		if (u == G->elem[i].data.key)
			return i;
	}
	return -1;
}
status PutVex(Graph* G, KeyType u, ElemType value)
{
	if (!G)
		return ERROR;
	int lo = LocateVex(G, u); //找到顶点
	if (lo == -1)
		return INFEASIBLE;
	G->elem[lo].data.value = value;
	return OK;
}
int FirstAdjVex(Graph* G, int u)
{
	if (!G)
		return -2;
	if (G->elem[u].firstArc)
		return G->elem[u].firstArc->pos;
	if (u < 0 || u >= G->vernum || G->elem[u].data.key == 0) //顶点是否存在
		return -3;
	else
		return -1;
}
int NextAdjVex(Graph* G, int v, int w)
{
	if (!G)
		return -2;
	ArcNode* p = G->elem[v].firstArc;
	if (v < 0 || v >= G->vernum || G->elem[v].data.key == 0 || w < 0 || w >= G->vernum || G->elem[w].data.key == 0) //顶点是否存在
		return -3;
	while(p)
	{
		if (p->pos == w)
			if (p->next)
				return p->next->pos;
			else
				return -1;
		p = p->next;
	}
	return -3;
}
status InsertVex(Graph* G, Vertex v)
{
	if (!G)
		return ERROR;
	if (LocateVex(G, v.data.key) >= 0) //检查关键字是否已存在
		return INFEASIBLE;
	if (G->vernum == MAXVERTEXNUM)
		return OVERFLOW;
	G->vernum++;
	G->elem[G->vernum - 1].data = v.data;
	G->elem[G->vernum - 1].firstArc = NULL;
	return OK;
}
status DeleteVex(Graph* G, int v)
{
	if (!G)
		return ERROR;
	if (v < 0 || v >= G->vernum || G->elem[v].data.key == 0)
		return INFEASIBLE;
	int i;
	ArcNode* p, * q;
	for (i = 0;i < G->vernum;i++)
	{
		if (i == v) //删除顶点及顶点内的边
		{
			p = G->elem[i].firstArc;
			q = p->next;
			while (p)
			{
				free(p);
				p = q;
				if(p)
					q = p->next;
			}
			G->elem[i].data.key = 0;
			G->elem[i].firstArc = NULL;
			continue;
		}
		p = G->elem[i].firstArc;
		if (!p)
			continue;
		q = p->next;
		if (p->pos == v) //删除其他顶点内连接到删除顶点的边
		{
			G->elem[i].firstArc = p->next;
			free(p);
		}
		else
			while (p->next)
			{
				if(p->next->pos == v)
				{
					p->next = q->next;
					free(q);
					break;
				}
				p = q;
				if(p)
					q = p->next;
			}
	}
	G->vernum--;
	return OK;
}
status InsertArc(Graph* G, int v, int w)
{
	if (!G)
		return ERROR;
	if (v < 0 || v >= G->vernum || G->elem[v].data.key == 0 || w < 0 || w > G->vernum || G->elem[w].data.key == 0) //检查顶点是否存在
		return INFEASIBLE;
	ArcNode* p = (ArcNode*)malloc(sizeof(ArcNode));
	if (!p)
		exit(OVERFLOW);
	p->pos = w;
	p->next = G->elem[v].firstArc;
	G->elem[v].firstArc = p;
	if(v != w)
	{
		p = (ArcNode*)malloc(sizeof(ArcNode));
		if (!p)
			exit(OVERFLOW);
		p->pos = v;
		p->next = G->elem[w].firstArc;
		G->elem[w].firstArc = p;
	}
	G->arcnum++;
	return OK;
}
status DeleteArc(Graph* G, int v, int w)
{
	if (!G)
		return ERROR;
	if (v < 0 || v >= G->vernum || G->elem[v].data.key == 0 || w < 0 || w > G->vernum || G->elem[w].data.key == 0) //检查顶点是否存在
		return INFEASIBLE;
	ArcNode* p, * q;
	p = G->elem[v].firstArc;
	if (!p)
		return OVERFLOW;
	q = p->next;
	if(p->pos == w)
	{
		G->elem[v].firstArc = p->next;
		free(p);
	}
	else
		while(p->next)
		{
			if(p->next->pos == w)
			{
				p->next = p->next->next;
				free(q);
				break;
			}
			p = p->next;
			q = p->next;
		}
	if (v != w) 
	{
		p = G->elem[w].firstArc;
		if (!p)
			return OVERFLOW;
		q = p->next;
		if (p->pos == v)
		{
			G->elem[w].firstArc = p->next;
			free(p);
		}
		else
			while (p->next)
			{
				if (p->next->pos == v)
				{
					p->next = p->next->next;
					free(q);
					break;
				}
				p = p->next;
				q = q->next;
			}
	}
	G->arcnum--;
	return OK;
}
status DFSTraverse(Graph* G, status(*Visit)(Vertex v))
{
    if(!G)
        return ERROR;
    int *visited;
	int count = 0;
    visited = (int*)malloc(sizeof(int) * 20); //保存顶点是否被访问过
    if(!visited)
        exit(OVERFLOW);
    int i;
    for(i = 0; i < 20; i++)
    {
        visited[i] = 0;
    }
    Vertex* s;
    s = (Vertex*)malloc(sizeof(Vertex) * 20); //使用辅助栈遍历
    if(!s)
        exit(OVERFLOW);
    int top = 0;
    int bottom = 0;
    Vertex n;
	int vnum;
	while (count != G->vernum) //每个顶点都被遍历后结束
	{
		vnum = 0;
		for(i = 0;vnum < G->vernum;i++)
		{
			if (G->elem[i].data.key != 0)
			{
				vnum++;
				if (visited[i] == 0)
				{
					s[top++] = G->elem[i];
					visited[i] = 1;
					break;
				}
			}
		}
		while (top != bottom) //空栈子树遍历完毕
		{
			n = s[--top];
			Visit(n);
			count++;
			ArcNode* p = n.firstArc;
			while (p) //点p的邻接点入栈
			{
				if (visited[p->pos] == 0)
				{
					visited[p->pos] = 1;
					s[top++] = G->elem[p->pos];
				}
				p = p->next;
			}
		}
		printf("\n");
	}
    return OK;
}
status BFSTraverse(Graph* G, status(* Visit)(Vertex v))
{
	if (!G)
		return ERROR;
	int* visited;
	int count = 0;
	visited = (int*)malloc(sizeof(int) * 20);
	if (!visited)
		exit(OVERFLOW);
	int i;
	for (i = 0; i < 20; i++)
	{
		visited[i] = 0;
	}
	Vertex* q;
	q = (Vertex*)malloc(sizeof(Vertex) * 20); //辅助队列
	if (!q)
		exit(OVERFLOW);
	int top = 0;
	int bottom = 0;
	Vertex n;
	int vnum;
	while (count != G->vernum) //每个顶点都被遍历后结束
	{
		vnum = 0;
		for (i = 0;vnum < G->vernum;i++)
		{
			if (G->elem[i].data.key != 0)
			{
				vnum++;
				if (visited[i] == 0)
				{
					q[bottom++] = G->elem[i];
					visited[i] = 1;
					break;
				}
			}
		}
		while (top != bottom) //队列为空子树遍历完毕
		{
			n = q[top++];
			Visit(n);
			count++;
			ArcNode* p = n.firstArc;
			while (p)
			{
				if (visited[p->pos] == 0)
				{
					visited[p->pos] = 1;
					q[bottom++] = G->elem[p->pos];
				}
				p = p->next;
			}
		}
		printf("\n");
	}
	return OK;
}
status SaveGraph(Graph* G, char* path)
{
	if (!G)
		return ERROR;
	FILE* graph = fopen(path, "w");
	if (!graph)
		return INFEASIBLE;
	fwrite(&G->vernum, sizeof(int), 1, graph);
	fwrite(&G->arcnum, sizeof(int), 1, graph);
	int i;
	int end = -1;
	ArcNode* p;
	for (i = 0;i < 20;i++)
	{
		fwrite(&(G->elem[i].data), sizeof(Data), 1, graph);
		p = G->elem[i].firstArc;
		while (p)
		{
			fwrite(&(p->pos), sizeof(int), 1, graph);
			p = p->next;
		}
		fwrite(&end, sizeof(int), 1, graph);
	}
	fclose(graph);
	return OK;
}
status LoadGraph(Graph*& G, char* path)
{
	if (!G)
		return ERROR;
	G = (Graph*)malloc(sizeof(Graph));
	if (!G)
		exit(OVERFLOW);
	FILE* graph = fopen(path, "r");
	if (!graph)
		return INFEASIBLE;
	printf("请输入图名：");
	char temp[80];
	scanf("%s", temp);
	int i;
	for (i = 1;i <= graphL.length;i++) //检查图名是否已存在
		if (!strcmp(temp, graphL.graphs[i]->name))
			return OVERFLOW;
	fread(&(G->vernum), sizeof(int), 1, graph);
	fread(&(G->arcnum), sizeof(int), 1, graph);
	ArcNode* p;
	for(i = 0;i < 20;i++)
	{
		fread(&G->elem[i].data, sizeof(Data), 1, graph);
		G->elem[i].firstArc = NULL;
		while (true)
		{
			p = (ArcNode*)malloc(sizeof(ArcNode));
			if (!p)
				exit(OVERFLOW);
			fread(&p->pos, sizeof(int), 1, graph);
			if(p->pos == -1)
			{
				free(p);
				break;
			}
			p->next = G->elem[i].firstArc;
			G->elem[i].firstArc = p;
		}
	}
	graphL.length++;
	if (graphL.length >= graphL.listLength) //如果图表长度已达上限，扩充表
	{
		Graph** tempG = graphL.graphs;
		graphL.graphs = (Graph * *)realloc(graphL.graphs, sizeof(Graph) * (graphL.length + INCREMENT));
		if (!graphL.graphs)
		{
			free(tempG);
			exit(OVERFLOW);
		}
		graphL.listLength += INCREMENT;
	}
	graphL.graphs[graphL.length] = G;
	strcpy(G->name, temp);
	fclose(graph);
	return OK;
}
status ShowAllGraphs()
{
	if (graphL.length == 0)
		return ERROR;
	printf("---------------------start-------------------------\n");
	int i;
	for(i = 1;i <= graphL.length;i++)
	{
		printf("图名：%s BFT序列：",graphL.graphs[i]->name);
		BFSTraverse(graphL.graphs[i], Visit);
		printf("\n");
	}
	printf("----------------------end--------------------------\n");
	return OK;
}
status GetGraph(Graph*& G, char* name)
{
	int i;
	for(i = 1;i <= graphL.length;i++)
	{
		if (!strcmp(graphL.graphs[i]->name, name))
		{
			G = graphL.graphs[i];
			return OK;
		}
	}
	return ERROR;
}
status Visit(Vertex v)
{
	printf("(%d, %d) ", v.data.key, v.data.value);
	return OK;
}
