/*Binary Tree On Doubly Linked List*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2 //status定义

#define INITSIZE 80
#define INCREAMENT 10 //二叉树线性表常量定义

typedef int status;
typedef int ElemType;
typedef int KeyType;

/*各结构体定义*/
typedef struct Data//节点数据域
{
	KeyType key;
	ElemType value;
};

typedef struct BiTreeNode //节点
{
	Data data;
	BiTreeNode* lchild, * rchild;
}*BiTree;

typedef struct TreeList//二叉树线性表
{
	BiTree* trees;
	int length;
	int listsize;
};
/*结构体定义结束*/

TreeList treeL;
int flag;
Data* p; //用于带空子树的前序序列递归创建树

/*函数声明*/
status CreateBiTree(BiTree& T, int definition);
status DestroyBiTree(BiTree& T);
status ClearBiTree(BiTree& T);
status BiTreeEmpty(BiTree T);
int BiTreeDepth(BiTree T);
BiTreeNode* LocateNode(BiTree T, KeyType e);
status Assign(BiTree& T, KeyType e, ElemType value);
BiTreeNode* GetSibling(BiTree T, KeyType e);
status InsertNode(BiTree& T, KeyType e, int LR, BiTreeNode c);
status DeleteNode(BiTree& T, KeyType e);
status PreOrderTraverse(BiTree T, status(*Visit)(BiTreeNode c));
status InOrderTraverse(BiTree T, status(*Visit)(BiTreeNode c));
status PostOrderTraverse(BiTree T, status(*Visit)(BiTreeNode c));
status LevelOrderTraverse(BiTree T, status(*Visit)(BiTreeNode c));
status SaveTree(BiTree T, char* path);
status LoadTree(BiTree& T, char* path);
status ShowAllTrees();
status GetTree(BiTree& T, int lo);
status Visit(BiTreeNode c);
status FilePreOrderCreateBiTree(BiTree& T);
status PreOrderCreateBiTree(BiTree& T);
status InPreOrderCreateBiTree(BiTree& T,Data* pre, Data* in,int size);
status InPostOrderCreateBiTree(BiTree& T,Data* post, Data* in, int size);
BiTreeNode* FindParent(BiTree T, KeyType e, int& LR);
int GetSize(char* path);
/*函数声明结束*/

int main(void) {
	int op = 1;
	treeL.trees = (BiTree*)malloc(sizeof(BiTree) * INITSIZE);
	if (!treeL.trees)
	{
		exit(OVERFLOW);
	}
	treeL.trees[0] = NULL;
	BiTree T = treeL.trees[0];
	int res = -1;
	while (op) {
		system("cls");	printf("\n\n");
		printf("      Menu for Binary Tree On Doubly Linked List \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. CreateBiTree       10. DeleteNode\n");
		printf("    	  2. DestroyBiTree      11. PreOrderTraverse\n");
		printf("    	  3. ClearBiTree        12. InOrderTraverse\n");
		printf("    	  4. BiTreeEmpty        13. PostOrderTraverse\n");
		printf("    	  5. BITreeDepth        14. LevelOrderTraverse\n");
		printf("    	  6. LocateNode         15. SaveTree\n");
		printf("    	  7. Assign             16. LoadTree\n");
		printf("    	  8. GetSibling         17. ShowAllTrees\n");
		printf("    	  9. InsertNode         18. GetTree\n");
		printf("    	  0. Exit\n");
		printf("-------------------------------------------------\n");
		printf("       当前操作的树序号：%d   请选择你的操作[0~18]:",flag);
		scanf("%d", &op);
		switch (op) {
		case 1:
			int definition;
			definition = 0;
			printf("请输入构造定义\n1.带空子树的前序序列\n2.前序+中序序列\n3.后序+中序序列：");
			scanf("%d", &definition);
			res = CreateBiTree(T, definition);
			if (res == OK)
				printf("二叉树构建成功！\n");
			else
				printf("错误的定义或序列中有重复的关键字！\n");
			getchar();getchar();
			break;
		case 2:
			res = DestroyBiTree(T);
			if (res == OK)
			{
				printf("二叉树销毁成功！\n");
				int i;
				for(i = flag;i < treeL.length - 1;i++) //从线性表中删除树
				{
					treeL.trees[i] = treeL.trees[i + 1];
				}
				treeL.length--;
				T = treeL.trees[0];
				flag = 0;
			}
			else
				printf("二叉树不存在！\n");
			getchar();getchar();
			break;
		case 3:
			res = ClearBiTree(T);
			if (res == OK)
				printf("二叉树已清空！\n");
			else
				printf("二叉树不存在！\n");
			getchar();getchar();
			break;
		case 4:
			res = BiTreeEmpty(T);
			if (res == TRUE)
				printf("二叉树为空！\n");
			else if (res == FALSE)
				printf("二叉树不为空！\n");
			else
				printf("二叉树不存在！\n");
			getchar();getchar();
			break;
		case 5:
			res = BiTreeDepth(T);
			if (res == 0)
				printf("二叉树不存在！\n");
			else
				printf("二叉树深度为%d！\n", res);
			getchar();getchar();
			break;
		case 6:
			BiTreeNode * res_ln;
			KeyType e_ln;
			printf("请输入参数（查找关键字）：");
			scanf("%d", &e_ln);
			res_ln = LocateNode(T, e_ln);
			if (res_ln == NULL)
				printf("没有关键字为%d的节点或二叉树不存在！\n",e_ln);
			else
				printf("找到节点：关键字%d,值%d！\n",res_ln->data.key,res_ln->data.value);
			getchar();getchar();
			break;
		case 7:
			KeyType e_a;
			ElemType v_a;
			printf("请输入参数（查找关键字和值）：");
			scanf("%d%d", &e_a, &v_a);
			res = Assign(T, e_a, v_a);
			if (res == ERROR)
				printf("二叉树不存在！\n");
			else if (res == INFEASIBLE)
				printf("二叉树不存在关键字为%d的节点！\n",e_a);
			else
				printf("关键字为%d的节点已赋值为%d！\n",e_a,v_a);
			getchar();getchar();
			break;
		case 8:
			BiTreeNode * res_gb;
			KeyType e_gb;
			printf("请输入参数（查找关键字）：");
			scanf("%d", &e_gb);
			res_gb = GetSibling(T, e_gb);
			if (res_gb == NULL)
				printf("查找异常，可能是二叉树不存在，关键字为%d的节点不存在，或此节点没有兄弟节点！\n", e_gb);
			else
				printf("兄弟节点的关键字为%d,值为%d!\n", res_gb->data.key, res_gb->data.value);
			getchar();getchar();
			break;
		case 9:
			KeyType e_in;
			BiTreeNode c_in;
			int LR;
			printf("请输入参数（关键字，插入位置，插入节点）key,value：");
			scanf("%d%d%d%d", &e_in, &LR, &c_in.data.key, &c_in.data.value);
			res = InsertNode(T, e_in, LR, c_in);
			if (res == ERROR)
				printf("二叉树不存在！\n");
			else if (res == INFEASIBLE)
				printf("插入错误！可能是不存在关键字为%d的节点，输入了错误的模式，或已存在关键字为%d的节点\n", e_in, c_in.data.key);
			else
				printf("节点插入成功！\n");
			getchar();getchar();
			break;
		case 10:
			KeyType e_dn;
			printf("请输入参数（删除关键字）：");
			scanf("%d", &e_dn);
			res = DeleteNode(T, e_dn);
			if (res == ERROR)
				printf("二叉树不存在！\n");
			else if (res == INFEASIBLE)
				printf("不存在关键字为%d的节点！\n", e_dn);
			else
				printf("节点删除成功！\n");
			getchar();getchar();
			break;
		case 11:
			printf("先序遍历：\n");
			res = PreOrderTraverse(T,Visit);
			if (res == ERROR)
				printf("二叉树不存在！\n");
			else if (res == INFEASIBLE)
				printf("二叉树为空树！\n");
			getchar();getchar();
			break;
		case 12:
			printf("中序遍历：\n");
			res = InOrderTraverse(T, Visit);
			if (res == ERROR)
				printf("二叉树不存在！\n");
			else if (res == INFEASIBLE)
				printf("二叉树为空树！\n");
			getchar();getchar();
			break;
		case 13:
			printf("后序遍历：\n");
			res = PostOrderTraverse(T, Visit);
			if (res == ERROR)
				printf("二叉树不存在！\n");
			else if (res == INFEASIBLE)
				printf("二叉树为空树！\n");
			getchar();getchar();
			break;
		case 14:
			printf("按层遍历：\n");
			res = LevelOrderTraverse(T, Visit);
			if (res == ERROR)
				printf("二叉树不存在！\n");
			else if (res == INFEASIBLE)
				printf("二叉树为空树！\n");
			getchar();getchar();
			break;
		case 15:
			char p_s[80];
			printf("请输入参数（保存路径）：");
			scanf("%s", p_s);
			res = SaveTree(T, p_s);
			if (res == ERROR)
				printf("二叉树不存在！\n");
			else if (res == INFEASIBLE)
				printf("路径错误！\n");
			else
				printf("二叉树保存成功！\n");
			getchar();getchar();
			break;
		case 16:
			char p_l[80];
			printf("请输入参数（保存路径）：");
			scanf("%s", p_l);
			res = LoadTree(T, p_l);
			if (res == INFEASIBLE)
				printf("路径错误！\n");
			else
				printf("二叉树读取成功！\n");
			getchar();getchar();
			break;
		case 17:
			printf("----------------------------start------------------------------\n");
			res = ShowAllTrees();
			if (res == ERROR)
				printf("没有树！\n");
			getchar();getchar();
			break;
		case 18:
			int lo;
			printf("请输入参数（树编号）:");
			scanf("%d", &lo);
			res = GetTree(T, lo);
			if (res == ERROR)
				printf("不存在编号为%d的树！\n", lo);
			else
				printf("已切换到树%d！\n", lo);
			getchar();getchar();
			break;
		case 0:
			break;
		}
	}
	printf("欢迎下次再使用本系统！\n");
	return 0;
}
status CreateBiTree(BiTree &T, int definition)
{
	int size;
	Data* input1, * input2;
	int i;
	switch (definition)
	{
	default:
		return ERROR;
	case 1:
		printf("请输入序列长度：");
		scanf("%d", &size);
		if (!p) //检测全局变量p是否创建
		{
			p = (Data*)malloc(sizeof(Data) * size);
			if (!p)
				exit(OVERFLOW);
		}
		if (p)
		{
			Data* temp = p;
			p = (Data*)realloc(p, sizeof(Data) * size);
			if (!p)
			{
				free(temp);
				exit(OVERFLOW);
			}
		}
		printf("请输入节点数据序列(key为0代表空节点）：");
		for (i = 0;i < size;i++)
		{
			scanf("%d%d", &p[i].key, &p[i].value);
			int j;
			for (j = 0;j < i;j++) //关键字不能重复
				if (p[i].key != 0 && p[j].key == p[i].key)
				{
					setbuf(stdin, NULL); //检测到重复的关键字后清空输入流
					return INFEASIBLE;
				}
			Data* temp = p;
			PreOrderCreateBiTree(T);
			p = temp;
		}
		break;
	case 2:
		printf("请输入序列长度：");
		scanf("%d", &size);
		input1 = (Data*)malloc(sizeof(Data) * size);
		input2 = (Data*)malloc(sizeof(Data) * size);
		printf("请输入前序遍历序列：");
		for (i = 0;i < size;i++)
		{
			scanf("%d%d", &input1[i].key, &input1[i].value);
			int j;
			for (j = 0;j < i;j++)
				if (input1[i].key != 0 && input1[j].key == input1[i].key)
				{
					setbuf(stdin, NULL);
					return INFEASIBLE;
				}
		}
		printf("请输入中序遍历序列：");
		for (i = 0;i < size;i++)
		{
			scanf("%d%d", &input2[i].key, &input2[i].value);
			int j;
			for (j = 0;j < i;j++)
				if (input2[i].key != 0 && input2[j].key == input2[i].key)
				{
					setbuf(stdin, NULL);
					return INFEASIBLE;
				}
		}
		InPreOrderCreateBiTree(T, input1, input2, size - 1);
		break;
	case 3:
		printf("请输入序列长度：");
		scanf("%d", &size);
		input1 = (Data*)malloc(sizeof(Data) * size);
		input2 = (Data*)malloc(sizeof(Data) * size);
		printf("请输入后序遍历序列：");
		for (i = 0;i < size;i++)
		{
			scanf("%d%d", &input1[i].key, &input1[i].value);
			int j;
			for (j = 0;j < i;j++)
				if (input1[i].key != 0 && input1[j].key == input1[i].key)
				{
					setbuf(stdin, NULL);
					return INFEASIBLE;
				}
		}
		printf("请输入中序遍历序列：");
		for (i = 0;i < size;i++)
		{
			scanf("%d%d", &input2[i].key, &input2[i].value);
			int j;
			for (j = 0;j < i;j++)
				if (input2[i].key != 0 && input2[j].key == input2[i].key)
				{
					setbuf(stdin, NULL);
					return INFEASIBLE;
				}
		}
		InPostOrderCreateBiTree(T, input1, input2, size - 1);
		break;
	}
	treeL.length++;
	if (treeL.length >= treeL.listsize) //线性表达到表长
	{
		BiTree* t = treeL.trees;
		treeL.trees = (BiTree*)realloc(treeL.trees, sizeof(BiTree) * (treeL.listsize + INCREAMENT));
		if (!treeL.trees) // 扩容失败释放原空间
		{
			free(t);
			exit(OVERFLOW);
		}
		treeL.listsize += INCREAMENT;
	}
	flag = treeL.length;
	treeL.trees[treeL.length] = T;
	return OK;
}
status PreOrderCreateBiTree(BiTree& T) //带空子树的前序序列
{
	if (p->key == 0)
		T = NULL;
	else
	{
		T = (BiTreeNode*)malloc(sizeof(BiTreeNode));
		if (!T)
			exit(OVERFLOW);
		T->data = *p;
		p = p + 1;
		FilePreOrderCreateBiTree(T->lchild);
		p = p + 1;
		FilePreOrderCreateBiTree(T->rchild);
	}
	return OK;
}
status InPostOrderCreateBiTree(BiTree& T, Data* post, Data* in, int size) // 前序+中序创建树
{
	if (size < 0)
	{
		T = NULL;
		return OK;
	}
	int pos = 0;
	while (in[pos].key != post[size].key)
		pos++;
	T = (BiTreeNode*)malloc(sizeof(BiTreeNode));
	if (!T)
		exit(OVERFLOW);
	T->data = in[pos];
	if (T->data.key == 0)
	{
		T = NULL;
		return ERROR;
	}
	InPostOrderCreateBiTree(T->lchild, post, in, pos - 1);
	InPostOrderCreateBiTree(T->rchild, post + pos, in + pos + 1, size - pos - 1);
	return OK;
}
status InPreOrderCreateBiTree(BiTree& T, Data* pre, Data* in, int size) //后序+中序创建树
{
	if (size < 0)
	{
		T = NULL;
		return OK;
	}
	int pos = 0;
	while (in[pos].key != pre[0].key)
		pos++;
	T = (BiTreeNode*)malloc(sizeof(BiTreeNode));
	if (!T)
		exit(OVERFLOW);
	T->data = in[pos];
	if (T->data.key == 0)
	{
		T = NULL;
		return ERROR;
	}
	InPreOrderCreateBiTree(T->lchild, pre + 1, in, pos - 1);
	InPreOrderCreateBiTree(T->rchild, pre + pos + 1, in + pos + 1, size - pos - 1);
	return OK;
}
status DestroyBiTree(BiTree& T)
{
	if (!T)
		return ERROR;
	DestroyBiTree(T->lchild);
	DestroyBiTree(T->rchild);
	free(T);
	return OK;
}
status ClearBiTree(BiTree& T)
{
	if (!T)
		return ERROR;
	DestroyBiTree(T->lchild);
	DestroyBiTree(T->rchild);
	T->data = { 0,0 };
	T->lchild = NULL;
	T->rchild = NULL;
	return OK;
}
status BiTreeEmpty(BiTree T)
{
	if (!T)
		return ERROR;
	if (T->data.key == 0)
		return TRUE;
	return FALSE;
}int BiTreeDepth(BiTree T)
{
	if (!T || T->data.key == 0)
		return 0;
	int l, r;
	l = BiTreeDepth(T->lchild);
	r = BiTreeDepth(T->rchild);
	return r > l ? r + 1 : l + 1;
}
BiTreeNode* LocateNode(BiTree T, KeyType e)
{
	BiTreeNode* res = NULL;
	if (!T)
		return NULL;
	if (T->data.key == e)
		res = T;
	else
	{
		if (T->lchild)
		{
			res = LocateNode(T->lchild, e);
			if (res != NULL)
				return res;
		}
		if (T->rchild)
		{
			res = LocateNode(T->rchild, e);
			return res;
		}
	}
	return res;
}
status Assign(BiTree& T, KeyType e, ElemType value)
{
	if (!T)
		return ERROR;
	BiTreeNode* p = LocateNode(T, e);
	if (!p)
		return INFEASIBLE;
	p->data.value = value;
	return OK;
}
BiTreeNode* GetSibling(BiTree T, KeyType e)
{
	BiTreeNode* res = NULL;
	if (!T)
		return NULL;
	if (T->lchild)
	{
		if (T->lchild->data.key == e)
			res = T->rchild;
		else
			res = GetSibling(T->lchild, e);
		if (res != NULL)
			return res;
	}
	if (T->rchild)
	{
		if (T->rchild->data.key == e)
			res = T->lchild;
		else
			res = GetSibling(T->rchild, e);
		return res;
	}
	return res;
}
status InsertNode(BiTree& T, KeyType e, int LR, BiTreeNode c)
{
	if (!T)
		return ERROR;
	if (LocateNode(T, c.data.key)) //查找是否有关键字重复的节点
		return INFEASIBLE;
	BiTreeNode* p = LocateNode(T, e);
	BiTreeNode* n = (BiTreeNode*)malloc(sizeof(BiTreeNode));
	if (!n)
		exit(OVERFLOW);
	*n = c;
	if (!p)
		return INFEASIBLE;
	if (LR != 0 && LR != 1)
		return INFEASIBLE;
	if(LR)
	{
		n->rchild = p->rchild;
		n->lchild = NULL;
		p->rchild = n;
	}
	else
	{
		n->rchild = p->lchild;
		n->lchild = NULL;
		p->lchild = n;
	}
	return OK;
}
status DeleteNode(BiTree& T, KeyType e)
{
	int LR = 0;
	if (!T)
		return ERROR;
	BiTreeNode* p;
	if (T->data.key == e)
	{
		p = (BiTreeNode*)malloc(sizeof(BiTreeNode));
		if (!p)
			exit(OVERFLOW);
		p->lchild = T;
	}
	else
		p = FindParent(T, e, LR);
	if (!p)
		return INFEASIBLE;
	BiTreeNode* d;
	if (LR)
		d = p->rchild;
	else
		d = p->lchild;
	BiTreeNode* n = d;
	if (p->lchild != T) //判断删除的是否是头结点
	{
		if (d->lchild && d->rchild)
		{
			if (LR)
				p->rchild = d->lchild;
			else
				p->lchild = d->lchild;
			n = n->lchild;
			while (n->rchild)
				n = n->rchild;
			n->rchild = d->rchild;
			free(d);
		}
		else if (d->lchild)
		{
			if (LR)
				p->rchild = d->lchild;
			else
				p->lchild = d->lchild;
			free(d);
		}
		else if (d->rchild)
		{
			if (LR)
				p->rchild = d->rchild;
			else
				p->lchild = d->rchild;
			free(d);
		}
		else
		{
			if (LR)
				p->rchild = NULL;
			else
				p->lchild = NULL;
			free(d);
		}
	}
	else
	{
		if (d->lchild && d->rchild)
		{
			if (LR)
				p->rchild = d->lchild;
			else
				p->lchild = d->lchild;
			n = n->lchild;
			while (n->rchild)
				n = n->rchild;
			n->rchild = d->rchild;
			free(d);
		}
		else if (d->lchild)
		{
			if (LR)
				p->rchild = d->lchild;
			else
				p->lchild = d->lchild;
			free(d);
		}
		else if (d->rchild)
		{
			if (LR)
				p->rchild = d->rchild;
			else
				p->lchild = d->rchild;
			free(d);
		}
		else
		{
			if (LR)
				p->rchild = NULL;
			else
				p->lchild = NULL;
			free(d);
		}
		T = p->lchild;
		treeL.trees[flag] = T;
	}
	return OK;
}
status PreOrderTraverse(BiTree T, status(* Visit)(BiTreeNode c))
{
    if(!T)
        return ERROR;
	if (T->data.key == 0)
		return INFEASIBLE;
    Visit(*T);
    PreOrderTraverse(T->lchild, Visit);
    PreOrderTraverse(T->rchild, Visit);
	return OK;
}
status InOrderTraverse(BiTree T, status(* Visit)(BiTreeNode c))
{ // 使用栈实现
    if(!T)
        return ERROR;
	if (T->data.key == 0)
		return INFEASIBLE;
    BiTree* s;
    int size = pow(2, BiTreeDepth(T));
    s = (BiTree*)malloc(sizeof(BiTree) * size);
	if (!s)
		exit(OVERFLOW);
    BiTree n = T;
    int top = 0;
    int bottom = 0;
    while(n || top != bottom) //栈为空且n为NULL跳出循环
    {
        if(n)
        {
            s[bottom++] = n; //入栈
            n = n->lchild;
        }    
        else
        {
            n = s[--bottom]; //出栈
            Visit(*n);
            n = n->rchild;
        }
    }
	return OK;
}
status PostOrderTraverse(BiTree T, status(* Visit)(BiTreeNode c))
{
    if(!T)
        return ERROR;
	if (T->data.key == 0)
		return INFEASIBLE;
    PostOrderTraverse(T->lchild, Visit); 
    PostOrderTraverse(T->rchild, Visit);
    Visit(*T);
	return OK;
}
status LevelOrderTraverse(BiTree T, status(* Visit)(BiTreeNode c))
{
    if(!T)
        return ERROR;
	if (T->data.key == 0)
		return INFEASIBLE;
    int size = pow(2, BiTreeDepth(T));
    BiTree* q;
    q = (BiTree*)malloc(sizeof(BiTree) * size); //辅助队列
	if (!q)
		exit(OVERFLOW);
    BiTree n = T;
    int top = 0;
    int bottom = 0;
    q[bottom++] = n;
    do
    {
        if(n->lchild)
            q[bottom++] = n->lchild;
        if(n->rchild)
            q[bottom++] = n->rchild;
        Visit(*n);
        q[top++] = NULL;
		n = q[top];
    }while(top != bottom);
	return OK;
}
status SaveTree(BiTree T, char* path)
{
	if (!T)
		return ERROR;
	FILE* tree = fopen(path, "w");
	if (!tree)
		return INFEASIBLE;
	BiTree* s;
	int size = pow(2, BiTreeDepth(T));
	s = (BiTree*)malloc(sizeof(BiTree) * size);
	if (!s)
		exit(OVERFLOW);
	BiTree n = T;
	Data e = { 0,0 };
	int top = 0;
	int bottom = 0;
	while (n || top != bottom) //以栈前序遍历树，构建带空子树的前序序列
	{
		if (!n)
			fwrite(&e, sizeof(Data), 1, tree);
		if (n)
		{
			fwrite(&n->data, sizeof(Data), 1, tree);
			s[bottom++] = n;
			n = n->lchild;
		}
		else
		{
			n = s[--bottom];
			n = n->rchild;
		}
	}
	fwrite(&e, sizeof(Data), 1, tree);
	fclose(tree);
	return OK;
}
status LoadTree(BiTree& T, char* path)
{
	FILE* tree = fopen(path, "r");
	if (!tree)
		return INFEASIBLE;
	int size = GetSize(path); //获取文件中树的大小
	if (!p)
	{
		p = (Data*)malloc(sizeof(Data) * size);
		if (!p)
			exit(OVERFLOW);
	}
	if (p)
	{
		Data* temp = p;
		p = (Data*)realloc(p, sizeof(Data) * size);
		if(!p)
		{
			free(temp);
			exit(OVERFLOW);
		}
	}
	fread(p, sizeof(Data), size, tree);
	treeL.length++;
	if (treeL.length >= treeL.listsize)
	{
		BiTree* t = treeL.trees;
		treeL.trees = (BiTree*)realloc(treeL.trees, sizeof(BiTree) * (treeL.listsize + INCREAMENT));
		if (!treeL.trees)
		{
			free(t);
			exit(OVERFLOW);
		}
		treeL.listsize += INCREAMENT;
	}
	flag = treeL.length;
	Data* temp = p; //保存p原始位置
	FilePreOrderCreateBiTree(T);
	p = temp; //还原p
	treeL.trees[treeL.length] = T;
	return OK;
}
status ShowAllTrees()
{
	if (treeL.length == 0)
		return ERROR;
	int i;
	for (i = 1;i <= treeL.length;i++) //对每棵树进行前序遍历
	{
		printf("编号%d前序序列：", i);
		PreOrderTraverse(treeL.trees[i],Visit);
		printf("\n");
	}
	printf("----------------------------end------------------------------\n");
	return OK;
}
status GetTree(BiTree& T, int lo)
{
	if (lo > treeL.length || lo <= 0)
		return ERROR;
	T = treeL.trees[lo];
	flag = lo;
	return OK;
}
status Visit(BiTreeNode c)
{
    printf("(%d, %d) ", c.data.key, c.data.value);
	return OK;
}
BiTreeNode* FindParent(BiTree T,KeyType e, int& LR)
{
	BiTreeNode* res = NULL;
	if (!T)
	    return NULL;
	if (T->lchild)
	{
		if (T->lchild->data.key == e)
		{
			res = T;
			LR = 0;
		}
		else
			res = FindParent(T->lchild, e, LR);
		if (res != NULL)
			return res;
	}
	if (T->rchild)
	{
		if (T->rchild->data.key == e)
		{
			res = T;
			LR = 1;
		}
		else
			res = FindParent(T->rchild, e, LR);
		return res;
	}
	return res;
}
int GetSize(char* path) //获取文件中树的大小
{
	int count = 0;
	FILE* tree = fopen(path, "r");
	if (!tree)
		return ERROR;
	Data temp;
	while (fread(&temp, sizeof(Data), 1, tree))
		count++;
	return count;
}
status FilePreOrderCreateBiTree(BiTree& T) //根据文件中的带空子树的前序序列创建树
{
	if (p->key == 0)
		T = NULL;
	else
	{
		T = (BiTreeNode*)malloc(sizeof(BiTreeNode));
		if (!T)
			exit(OVERFLOW);
		T->data = *p;
		p = p + 1;
		FilePreOrderCreateBiTree(T->lchild);
		p = p + 1;
		FilePreOrderCreateBiTree(T->rchild);
	}
	return OK;
}
