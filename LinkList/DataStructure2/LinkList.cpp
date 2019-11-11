/* Linear Table On Linked List */
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

typedef int status;
typedef int ElemType; //数据元素类型定义

typedef struct Node //链表节点定义
{
	ElemType data;
	Node* next;
};
typedef struct //线性表（链式结构）结构定义
{
	Node* head;
	int length;
	char name[80];
}LinkList;

LinkList Lists[80];//多表
int ListCount = 0;

status InitList(LinkList** L);
status DestroyList(LinkList** L);
status ClearList(LinkList* L);
status ListEmpty(LinkList* L);
int ListLength(LinkList* L);
status GetElem(LinkList* L, int i, ElemType& e);
int LocateElem(LinkList* L, ElemType e, status(*compare)(ElemType a, ElemType b));
status PriorElem(LinkList* L, ElemType cur, ElemType& pre_e);
status NextElem(LinkList* L, ElemType cur, ElemType& next_e);
status ListInsert(LinkList* L, int i, ElemType e);
status ListDelete(LinkList* L, int i, ElemType& e);
status ListTraverse(LinkList* L, void(*visit)(ElemType e));
status SaveList(LinkList* L, char* path);
status LoadList(LinkList** L, char* path);
status ShowAllLists();
status GetList(char* name, LinkList** L);
status compare(ElemType a, ElemType b);//比较两个int是否相等，可自定义
void print(ElemType e);//打印数据域保存的int，可自定义
/*--------------------------------------------*/
void main(void)
{
	LinkList* L = Lists;//指向当前操作表
	int op = 1;
	while (op)
	{
		system("cls");	printf("\n\n");
		printf("      Menu for Linear Table On Linked List \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. InitList        9. NextElem\n");
		printf("    	  2. DestroyList     10. ListInsert\n");
		printf("    	  3. ClearList       11. ListDelete\n");
		printf("    	  4. ListEmpty       12. ListTraverse\n");
		printf("    	  5. ListLength      13. SaveList\n");
		printf("    	  6. GetElem         14. LoadList\n");
		printf("    	  7. LocateElem      15. ShowAllLists\n");
		printf("    	  8. PriorElem       16. GetList\n");
		printf("    	  0. Exit\n");
		printf("-------------------------------------------------\n");
		printf("    当前操作对象：%s       请选择你的操作[0~16]:", L->name);
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			status res_il;
			res_il = InitList(&L);
			if (res_il == OK)
				printf("线性表创建成功！\n");
			else if (res_il == INFEASIBLE)
				printf("已存在同名线性表！\n");
			else
				printf("线性表创建失败！\n");
			getchar();getchar();
			break;
		case 2:
			if (DestroyList(&L) == OK)
				printf("线性表删除成功！\n");
			else
				printf("线性表删除失败！\n");
			getchar();getchar();
			break;
		case 3:
			if (ClearList(L) == OK)
				printf("线性表清空成功！\n");
			else
				printf("线性表清空失败！\n");
			getchar();getchar();
			break;
		case 4:
			status le;
			le = ListEmpty(L);
			;			if (le == TRUE)
				printf("线性表为空！\n");
			else if (le == ERROR)
				printf("线性表不存在！\n");
			else
				printf("线性表不为空！\n");
			getchar();getchar();
			break;
		case 5:
			printf("线性表长为%d!\n", ListLength(L));
			getchar();getchar();
			break;
		case 6:
			int i_ge;
			ElemType e_ge;
			printf("请输入参数（元素位置）：");
			scanf("%d", &i_ge);
			status ge;
			ge = GetElem(L, i_ge, e_ge);
			if (ge == ERROR)
				printf("线性表不存在！\n");
			else if (ge == OVERFLOW)
				printf("元素位置有误！\n");
			else
				printf("线性表中第%d位元素值为%d！\n", i_ge, e_ge);
			getchar();getchar();
			break;
		case 7:
			ElemType e_le;
			printf("请输入参数（元素值）：");
			scanf("%d", &e_le);
			int lte;
			lte = LocateElem(L, e_le, compare);
			if (lte == ERROR)
				printf("线性表不存在或元素在线性表中不存在！\n");
			else
				printf("元素%d在线性表中的位置为%d！\n", e_le, lte);
			getchar();getchar();
			break;
		case 8:
			ElemType cur_pe, pre_pe;
			printf("请输入参数（元素值）：");
			scanf("%d", &cur_pe);
			status pe;
			pe = PriorElem(L, cur_pe, pre_pe);
			if (pe == ERROR)
				printf("线性表不存在或元素在线性表中不存在！\n");
			else if (pe == INFEASIBLE)
				printf("元素为线性表首元素！\n");
			else
				printf("元素%d的前驱元素为%d！\n", cur_pe, pre_pe);
			getchar();getchar();
			break;
		case 9:
			ElemType cur_ne, next_ne;
			printf("请输入参数（元素值）：");
			scanf("%d", &cur_ne);
			status ne;
			ne = NextElem(L, cur_ne, next_ne);
			if (ne == ERROR)
				printf("线性表不存在或元素在线性表中不存在！\n");
			else if (ne == INFEASIBLE)
				printf("元素为线性表尾元素！\n");
			else
				printf("元素%d的后继元素为%d！\n", cur_ne, next_ne);
			getchar();getchar();
			break;
		case 10:
			int i_li;
			ElemType e_li;
			printf("请输入参数（插入位置 元素值）：");
			scanf("%d%d", &i_li, &e_li);
			status li;
			li = ListInsert(L, i_li, e_li);
			if (li == ERROR)
				printf("线性表不存在！\n");
			else if (li == INFEASIBLE)
				printf("插入位置超出表长！\n");
			else
				printf("元素%d插入成功！", e_li);
			getchar();getchar();
			break;
		case 11:
			int i_ld;
			ElemType e_ld;
			printf("请输入参数（元素位置）：");
			scanf("%d", &i_ld);
			status ld;
			ld = ListDelete(L, i_ld, e_ld);
			if (ld == ERROR)
				printf("线性表不存在！\n");
			else if (ld == OVERFLOW)
				printf("元素位置错误！\n");
			else
				printf("元素%d已删除！\n", e_ld);
			getchar();getchar();
			break;
		case 12:
			if (ListTraverse(L, print) == ERROR)
				printf("线性表不存在或是空表！\n");
			getchar();getchar();
			break;
		case 13:
			char path_sl[80];
			printf("请输入参数（保存路径）：");
			scanf("%s", path_sl);
			status res_sl;
			res_sl = SaveList(L, path_sl);
			if (res_sl == ERROR)
				printf("线性表不存在！\n");
			else if (res_sl == INFEASIBLE)
				printf("路径错误！\n");
			else
				printf("线性表保存成功！\n");
			getchar();getchar();
			break;
		case 14:
			char path_ll[80];
			printf("请输入参数（保存路径）：");
			scanf("%s", path_ll);
			status res_ll;
			res_ll = LoadList(&L, path_ll);
			if (res_ll == ERROR)
				printf("线性表不存在！\n");
			else if (res_ll == INFEASIBLE)
				printf("路径错误！\n");
			else
				printf("线性表读取成功！\n");
			getchar();getchar();
			break;
		case 15:
			if (ShowAllLists() == ERROR)
				printf("没有任何线性表！");
			else
				printf("\n------------------ end ------------------------\n");
			getchar();getchar();
			break;
		case 16:
			char name_ltl[80];
			printf("请输入参数（名称）：");
			scanf("%s", name_ltl);
			if (GetList(name_ltl, &L) == ERROR)
				printf("不存在名字为%s的线性表！", name_ltl);
			else
				printf("已切换到表%s\n", L->name);
			getchar();getchar();
			break;
		case 0:
			break;
		}
	}
	printf("欢迎下次再使用本系统！\n");
}
status InitList(LinkList** L)
{
	printf("请输入线性表名：");
	char temp[80];
	scanf("%s", temp);
	int i = 0;
	for (i = 1;i <= ListCount;i++)
		if (strcmp(temp, Lists[i].name) == 0)
			return INFEASIBLE;
	ListCount++;
	*L = Lists + ListCount;
	Node* head;
	head = (Node*)malloc(sizeof(Node));
	head->next = NULL;
	if (!head)
		exit(OVERFLOW);
	(*L)->head = head;
	(*L)->length = 0;
	strcpy((*L)->name, temp);
	return OK;
}
status DestroyList(LinkList** L)
{
	if (!((*L)->head)) //表不存在
		return ERROR;
	Node* p, *q;
	p = (*L)->head;
	q = p->next;
	while(p)
	{
		free(p);
		p = q;
		if(p)
			q = p->next;
	}
	int i, j;
	for (i = 1;i <= ListCount;i++)//在线性表数组中移除被摧毁的表
		if (strcmp(Lists[i].name, (*L)->name) == 0)
			for (j = i;j < ListCount;j++)
				Lists[j] = Lists[j + 1];
	ListCount--;
	*L = Lists;
	return OK;
}
status ClearList(LinkList* L)
{
	if (!(L->head)) //表不存在
		return ERROR;
	int i;
	Node* p = L->head->next;
	if (!p)
		return OK;
	Node* q = p->next;
	while (p)
	{
		free(p);
		p = q;
		if (p)
			q = p->next;
	}
	L->head->next = NULL;
	L->length = 0;
	return OK;
}
status ListEmpty(LinkList* L)
{
	if (!(L->head)) //表不存在
		return ERROR;
	if (L->length == 0)
		return TRUE;
	return FALSE;
}
int ListLength(LinkList* L)
{
	if (!(L->head)) //表不存在
		return ERROR;
	return L->length;
}
status GetElem(LinkList* L, int i, ElemType& e)
{
	if (!(L->head)) //表不存在
		return ERROR;
	if (i > L->length || i <= 0)
		return OVERFLOW;
	Node* p = L->head;
	while(i--)
	{
		p = p->next;
	}
	e = p->data;
	return OK;
}
int LocateElem(LinkList* L, ElemType e, status(*compare)(ElemType a, ElemType b))
{
	if (!(L->head)) //表不存在
		return ERROR;
	int i = 1;
	Node* p = L->head->next;
	while(p)
	{
		if (compare(p->data, e))
			return i;
		p = p->next;
		i++;
	}
	return 0;
}
status PriorElem(LinkList* L, ElemType cur_e, ElemType& pre_e)
{
	if (!(L->head)) //表不存在
		return ERROR;
	if ((L->head->next->data) == cur_e) //当前元素为表首元素
		return INFEASIBLE;
	Node* p = L->head->next;
	while(p->next)
	{
		if (p->next->data == cur_e)
		{
			pre_e = p->data;
			return OK;
		}
		p = p->next;	
	}
	return ERROR;
}
status NextElem(LinkList* L, ElemType cur_e, ElemType& next_e)
{
	if (!(L->head))//表不存在
		return ERROR;
	Node* p = L->head->next;
	while(p->next)
	{
		if (p->data == cur_e)
		{
			next_e = p->next->data;
			return OK;
		}
		p = p->next;
	}
	if (p->data == cur_e) //当前元素为表尾元素
		return INFEASIBLE;
	return ERROR;
}
status ListInsert(LinkList* L, int i, ElemType e)
{
	if (!(L->head)) //表不存在
		return ERROR;
	if (i > L->length + 1)
		return INFEASIBLE;
	Node* p = L->head;
	while(--i)
	{
		p = p->next;
	}
	Node* n = (Node*)malloc(sizeof(Node));
	if (!n)
		exit(OVERFLOW);
	n->next = p->next;
	n->data = e;
	p->next = n;
	L->length++;
	return OK;
}
status ListDelete(LinkList* L, int i, ElemType& e)
{
	if (!(L->head)) //表不存在
		return ERROR;
	if (i > L->length || i <= 0)
		return OVERFLOW;
	Node* p = L->head;
	Node* q;
	while(--i)
	{
		p = p->next;
	}
	e = p->next->data;
	q = p->next;
	p->next = p->next->next;
	free(q);
	L->length--;
	return OK;
}
status ListTraverse(LinkList* L, void(*visit)(ElemType e))
{
	if (!(L->head)) //表不存在
		return ERROR;
	if (L->length == 0)
		return ERROR;
	Node* p = L->head->next;
	printf("\n-----------all elements -----------------------\n");
	while(p)
	{
		visit(p->data);
		p = p->next;
	}
	printf("\n------------------ end ------------------------\n");
	return OK;
}
status SaveList(LinkList* L, char* path)
{
	if (!(L->head))
		return ERROR;
	FILE* List = fopen(path, "w");
	if (!List)
		return INFEASIBLE;
	fprintf(List, "%d ", L->length);
	Node* p = L->head->next;
	while(p)
	{
		fwrite(&p->data, sizeof(ElemType), 1, List);//写入数据域
		p = p->next;
	}
	fprintf(List, "\n");
	fclose(List);
	return OK;
}
status LoadList(LinkList** L, char* path)
{
	FILE* List = fopen(path, "r");
	if (!List)
		return INFEASIBLE;
	InitList(L);
	if (!((*L)->head))
		return ERROR;
	fscanf(List, "%d", &((*L)->length));
	fgetc(List);
	int i = (*L)->length;
	Node* p = (*L)->head;
	while(i--)
	{
		Node* n = (Node*)malloc(sizeof(Node));
		if (!n)
			exit(OVERFLOW);
		fread(&n->data, sizeof(ElemType), 1, List);
		p->next = n;
		n->next = NULL;
		p = p->next;
	}
	fclose(List);
	return OK;
}
status ShowAllLists()
{
	if (!(Lists+1)->head)
		return ERROR;
	int i;
	for (i = 1;i <= ListCount;i++)
		printf("线性表Lists[%d]，名字：%s\n", i, Lists[i].name);
	return OK;
}
status GetList(char* name, LinkList** L)
{
	if (!(Lists+1)->head)
		return ERROR;
	int i;
	for (i = 1;i <= ListCount;i++)
		if (strcmp(name, Lists[i].name) == 0)
		{
			*L = Lists + i;
			return OK;
		}
	return ERROR;
}
status compare(ElemType a, ElemType b)
{
	return a == b;
}
void print(ElemType e)
{
	printf("%d ", e);
	return;
}