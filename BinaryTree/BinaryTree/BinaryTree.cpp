/*Binary Tree On Doubly Linked List*/
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
#define OVERFLOW -2 //status����

#define INITSIZE 80
#define INCREAMENT 10 //���������Ա�������

typedef int status;
typedef int ElemType;
typedef int KeyType;

/*���ṹ�嶨��*/
typedef struct Data //�ڵ�������
{
	KeyType key;
	ElemType value;
};

typedef struct BiTreeNode //�ڵ�
{
	Data data;
	BiTreeNode* lchild, * rchild;
}*BiTree;

typedef struct TreeList //���������Ա�
{
	BiTree* trees;
	int length;
	int listsize;
};
/*�ṹ�嶨�����*/

TreeList treeL;
int flag;

/*��������*/
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
status Visit(BiTreeNode c);
status PreOrderCreateBiTree(BiTree& T);
status InPreOrderCreateBiTree(BiTree& T,Data* pre, Data* in,int size);
status InPostOrderCreateBiTree(BiTree& T,Data* post, Data* in, int size);
BiTreeNode* FindParent(BiTree T, KeyType e, int& LR);
/*������������*/

int main(void) {
	int op = 1;
	treeL.trees = (BiTree*)malloc(sizeof(BiTree) * INITSIZE);
	if (!treeL.trees)
	{
		exit(OVERFLOW);
	}
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
		printf("    	  8. GetSibLing         17. ShowAllTrees\n");
		printf("    	  9. InsertNode         18. GetTree\n");
		printf("    	  0. Exit\n");
		printf("-------------------------------------------------\n");
		printf("       ��ǰ����������ţ�%d   ��ѡ����Ĳ���[0~18]:",flag);
		scanf("%d", &op);
		switch (op) {
		case 1:
			int definition;
			definition = 0;
			printf("�����빹�춨��\n1.����������ǰ������\n2.ǰ��+��������\n3.����+�������У�");
			scanf("%d", &definition);
			res = CreateBiTree(T, definition);
			if (res == OK)
				printf("�����������ɹ���\n");
			else
				printf("����Ķ��壡\n");
			getchar();getchar();
			break;
		case 2:
			res = DestroyBiTree(T);
			if (res == OK)
				printf("���������ٳɹ���\n");
			else
				printf("�����������ڣ�\n");
			getchar();getchar();
			break;
		case 3:
			res = ClearBiTree(T);
			if (res == OK)
				printf("����������գ�\n");
			else
				printf("�����������ڣ�\n");
			getchar();getchar();
			break;
		case 4:
			res = BiTreeEmpty(T);
			if (res == TRUE)
				printf("������Ϊ�գ�\n");
			else if (res == FALSE)
				printf("��������Ϊ�գ�\n");
			else
				printf("�����������ڣ�\n");
			getchar();getchar();
			break;
		case 5:
			res = BiTreeDepth(T);
			if (res == 0)
				printf("�����������ڣ�\n");
			else
				printf("���������Ϊ%d��\n", res);
			getchar();getchar();
			break;
		case 6:
			BiTreeNode * res_ln;
			KeyType e_ln;
			printf("��������������ҹؼ��֣���");
			scanf("%d", &e_ln);
			res_ln = LocateNode(T, e_ln);
			if (res_ln == NULL)
				printf("û�йؼ���Ϊ%d�Ľڵ������������ڣ�\n",e_ln);
			else
				printf("�ҵ��ڵ㣺�ؼ���%d,ֵ%d��\n",res_ln->data.key,res_ln->data.value);
			getchar();getchar();
			break;
		case 7:
			KeyType e_a;
			ElemType v_a;
			printf("��������������ҹؼ��ֺ�ֵ����");
			scanf("%d%d", &e_a, &v_a);
			res = Assign(T, e_a, v_a);
			if (res == ERROR)
				printf("�����������ڣ�\n");
			else if (res == INFEASIBLE)
				printf("�����������ڹؼ���Ϊ%d�Ľڵ㣡\n",e_a);
			else
				printf("�ؼ���Ϊ%d�Ľڵ��Ѹ�ֵΪ%d��\n",e_a,v_a);
			getchar();getchar();
			break;
		case 8:
			BiTreeNode * res_gb;
			KeyType e_gb;
			printf("��������������ҹؼ��֣���");
			scanf("%d", &e_gb);
			res_gb = GetSibling(T, e_gb);
			if (res_gb == NULL)
				printf("�����쳣�������Ƕ����������ڣ��ؼ���Ϊ%d�Ľڵ㲻���ڣ���˽ڵ�û���ֵܽڵ㣡\n", e_gb);
			else
				printf("�ֵܽڵ�Ĺؼ�ֵΪ%d,ֵΪ%d!\n", res_gb->data.key, res_gb->data.value);
			getchar();getchar();
			break;
		case 9:
			KeyType e_in;
			BiTreeNode c_in;
			int LR;
			printf("������������ؼ��֣�����λ�ã�����ڵ㣩key,value��");
			scanf("%d%d%d%d", &e_in, &LR, &c_in.data.key, &c_in.data.value);
			res = InsertNode(T, e_in, LR, c_in);
			if (res == ERROR)
				printf("�����������ڣ�\n");
			else if (res == INFEASIBLE)
				printf("�ؼ���Ϊ%d�Ľڵ㲻���ڻ�ģʽ����\n", e_in);
			else
				printf("�ڵ����ɹ���\n");
			getchar();getchar();
			break;
		case 10:
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
		case 17:
			getchar();getchar();
			break;
		case 18:
			getchar();getchar();
			break;
		case 0:
			break;
		}
	}
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
	return 0;
}
status CreateBiTree(BiTree &T, int definition)
{
	int size;
	Data* input1, * input2;
	int i;
	treeL.length++;
	if(treeL.length >= treeL.listsize)
	{
		BiTree* t = treeL.trees;
		treeL.trees = (BiTree*)realloc(treeL.trees, sizeof(BiTree) * (treeL.listsize + INCREAMENT));
		if(!treeL.trees)
		{
			free(t);
			exit(OVERFLOW);
		}
		treeL.listsize += INCREAMENT;
	}
	T = treeL.trees[treeL.length];
	flag = treeL.length;
	switch (definition)
	{
	default:
		return ERROR;
	case 1:
		printf("������ڵ���������key,value��keyΪ0����սڵ㣩��");
		PreOrderCreateBiTree(T);
		break;
	case 2:
		printf("���������г��ȣ�");
		scanf("%d", &size);
		input1 = (Data*)malloc(sizeof(Data) * size);
		input2 = (Data*)malloc(sizeof(Data) * size);
		printf("������ǰ��������У�");
		for (i = 0;i < size;i++)
		{
			scanf("%d%d", &input1[i].key, &input1[i].value);
		}
		printf("����������������У�");
		for (i = 0;i < size;i++)
		{
			scanf("%d%d", &input2[i].key, &input2[i].value);
		}
		InPreOrderCreateBiTree(T, input1, input2, size - 1);
		break;
	case 3:
		printf("���������г��ȣ�");
		scanf("%d", &size);
		input1 = (Data*)malloc(sizeof(Data) * size);
		input2 = (Data*)malloc(sizeof(Data) * size);
		printf("���������������У�");
		for (i = 0;i < size;i++)
		{
			scanf("%d%d", &input1[i].key, &input1[i].value);
		}
		printf("����������������У�");
		for (i = 0;i < size;i++)
		{
			scanf("%d%d", &input2[i].key, &input2[i].value);
		}
		InPostOrderCreateBiTree(T, input1, input2, size - 1);
		break;
	}
	return OK;
}
status PreOrderCreateBiTree(BiTree& T)
{
	Data temp = {0,0};
	scanf("%d%d", &temp.key, &temp.value);
	if (temp.key == 0)
		T = NULL;
	else
	{
		T = (BiTreeNode*)malloc(sizeof(BiTreeNode));
		if (!T)
			exit(OVERFLOW);
		T->data = temp;
		PreOrderCreateBiTree(T->lchild);
		PreOrderCreateBiTree(T->rchild);
	}
	return OK;
}
status InPostOrderCreateBiTree(BiTree& T, Data* post, Data* in, int size)
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
status InPreOrderCreateBiTree(BiTree& T, Data* pre, Data* in, int size)
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
	T = treeL.trees[0];
	flag = 0;
	return OK;
}
status ClearBiTree(BiTree& T)
{
	if (!T)
		return ERROR;
	DestroyBiTree(T->lchild);
	DestroyBiTree(T->rchild);
	T->data = { 0,0 };
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
	if (!T)
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
	BiTreeNode* p = LocateNode(T, e);
	if (!p)
		return INFEASIBLE;
	if (LR != 0 && LR != 1)
		return INFEASIBLE;
	if(LR)
	{
		c.rchild = p->lchild;
		c.lchild = NULL;
		p->rchild = &c;
	}
	else
	{
		c.rchild = p->rchild;
		c.lchild = NULL;
		p->lchild = &c;
	}
	return OK;
}
status DeleteNode(BiTree& T, KeyType e)
{
	int LR;
	if (!T)
		return ERROR;
	BiTreeNode* p = FindParent(T, e, LR);
	BiTreeNode* d;
	if (LR)
		d = p->rchild;
	else
		d = p->lchild;
	BiTreeNode* n = d;
	if(d->lchild && d->rchild)
	{
		if (LR)
			p->rchild = d->lchild;
		else
			p->lchild = d->lchild;
		while (n->rchild)
			n = n->rchild;
		n->rchild = d->rchild;
		free(d);
	}
	else if(d->lchild)
	{
		if (LR)
			p->rchild = d->lchild;
		else
			p->lchild = d->lchild;
		free(d);
	}
	else if(d->rchild)
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
	return OK;
}
status PreOrderTraverse(BiTree T, status(* Visit)(BiTreeNode c))
{
	return OK;
}
status InOrderTraverse(BiTree T, status(* Visit)(BiTreeNode c))
{
	return OK;
}
status PostOrderTraverse(BiTree T, status(* Visit)(BiTreeNode c))
{
	return OK;
}
status LevelOrderTraverse(BiTree T, status(* Visit)(BiTreeNode c))
{
	return OK;
}
status Visit(BiTreeNode c)
{
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