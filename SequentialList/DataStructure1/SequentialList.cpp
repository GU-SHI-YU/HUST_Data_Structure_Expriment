/* Linear Table On Sequence Structure */
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
#define OVERFLOW -2 //����ֵ����

typedef int status;
typedef int ElemType; //����Ԫ�����Ͷ���

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct {  //˳���˳��ṹ���Ķ���
	ElemType* elem;
	int length;
	int listsize;
	char name[80];
}SqList;

SqList Lists[80];
int ListCount = 0;

status InitList(SqList** L);
status DestroyList(SqList **L);
status ClearList(SqList *L);
status ListEmpty(SqList *L);
int ListLength(SqList *L);
status GetElem(SqList *L,int i,ElemType &e);
int LocateElem(SqList *L, ElemType e, status(*compare)(ElemType a, ElemType b));
status PriorElem(SqList *L,ElemType cur,ElemType &pre_e);
status NextElem(SqList *L,ElemType cur,ElemType &next_e);
status ListInsert(SqList *L,int i,ElemType e);
status ListDelete(SqList *L, int i, ElemType &e);
status ListTraverse(SqList *L, void(*visit)(ElemType e));
status SaveList(SqList *L, char* path);
status LoadList(SqList** L, char* path);
status ShowAllLists();
status GetList(char* name, SqList **L);
status compare(ElemType a, ElemType b);//�Ƚ�����int�Ƿ���ȣ����Զ���
void print(ElemType e);//��ӡ�����򱣴��int�����Զ���
/*--------------------------------------------*/
void main(void)
{
	SqList* L = Lists;//ָ��ǰ������
	int op = 1;
	while (op) 
	{
		system("cls");	printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
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
		printf("    ��ǰ��������%s       ��ѡ����Ĳ���[0~16]:", L->name);
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			status res_il;
			res_il = InitList(&L);
			if (res_il == OK)
				printf("���Ա����ɹ���\n");
			else if (res_il == INFEASIBLE)
				printf("�Ѵ���ͬ�����Ա�\n");
			else
				printf("���Ա���ʧ�ܣ�\n");
			getchar();getchar();
			break;
		case 2:
			if (DestroyList(&L) == OK)
				printf("���Ա�ɾ���ɹ���\n");
			else
				printf("���Ա�ɾ��ʧ�ܣ�\n");
			getchar();getchar();
			break;
		case 3:
			if (ClearList(L) == OK)
				printf("���Ա���ճɹ���\n");
			else
				printf("���Ա����ʧ�ܣ�\n");
			getchar();getchar();
			break;
		case 4:
			status le;
			le = ListEmpty(L);
;			if (le == TRUE)
				printf("���Ա�Ϊ�գ�\n");
			else if (le == ERROR)
				printf("���Ա����ڣ�\n");
			else
				printf("���Ա�Ϊ�գ�\n");
			getchar();getchar();
			break;
		case 5:
			printf("���Ա�Ϊ%d!\n",ListLength(L));
			getchar();getchar();
			break;
		case 6:
			int i_ge;
			ElemType e_ge;
			printf("�����������Ԫ��λ�ã���");
			scanf("%d", &i_ge);
			status ge;
			ge = GetElem(L, i_ge, e_ge);
			if (ge == ERROR)
				printf("���Ա����ڣ�\n");
			else if (ge == OVERFLOW)
				printf("Ԫ��λ������\n");
			else
				printf("���Ա��е�%dλԪ��ֵΪ%d��\n", i_ge, e_ge);
			getchar();getchar();
			break;
		case 7:
			ElemType e_le;
			printf("�����������Ԫ��ֵ����");
			scanf("%d", &e_le);
			int lte;
			lte = LocateElem(L, e_le, compare);
			if (lte == ERROR)
				printf("���Ա����ڻ�Ԫ�������Ա��в����ڣ�\n");
			else
				printf("Ԫ��%d�����Ա��е�λ��Ϊ%d��\n", e_le, lte);
			getchar();getchar();
			break;
		case 8:
			ElemType cur_pe, pre_pe;
			printf("�����������Ԫ��ֵ����");
			scanf("%d", &cur_pe);
			status pe;
			pe = PriorElem(L, cur_pe, pre_pe);
			if (pe == ERROR)
				printf("���Ա����ڻ�Ԫ�������Ա��в����ڣ�\n");
			else if (pe == INFEASIBLE)
				printf("Ԫ��Ϊ���Ա���Ԫ�أ�\n");
			else
				printf("Ԫ��%d��ǰ��Ԫ��Ϊ%d��\n", cur_pe, pre_pe);
			getchar();getchar();
			break;
		case 9:
			ElemType cur_ne, next_ne;
			printf("�����������Ԫ��ֵ����");
			scanf("%d", &cur_ne);
			status ne;
			ne = NextElem(L, cur_ne, next_ne);
			if (ne == ERROR)
				printf("���Ա����ڻ�Ԫ�������Ա��в����ڣ�\n");
			else if (ne == INFEASIBLE)
				printf("Ԫ��Ϊ���Ա���Ԫ�أ�\n");
			else
				printf("Ԫ��%d�ĺ��Ԫ��Ϊ%d��\n", cur_ne, next_ne);
			getchar();getchar();
			break;
		case 10:
			int i_li;
			ElemType e_li;
			printf("���������������λ�� Ԫ��ֵ����");
			scanf("%d%d", &i_li, &e_li);
			status li;
			li = ListInsert(L, i_li, e_li);
			if (li == ERROR)
				printf("���Ա����ڣ�\n");
			else if (li == INFEASIBLE)
				printf("����λ�ó�������\n");
			else
				printf("Ԫ��%d����ɹ���", e_li);
			getchar();getchar();
			break;
		case 11:
			int i_ld;
			ElemType e_ld;
			printf("�����������Ԫ��λ�ã���");
			scanf("%d", &i_ld);
			status ld;
			ld = ListDelete(L, i_ld, e_ld);
			if (ld == ERROR)
				printf("���Ա����ڣ�\n");
			else if (ld == OVERFLOW)
				printf("Ԫ��λ�ô���\n");
			else
				printf("Ԫ��%d��ɾ����\n", e_ld);
			getchar();getchar();
			break;
		case 12:   
			if (ListTraverse(L, print) == ERROR) 
				printf("���Ա����ڻ��ǿձ�\n");
			getchar();getchar();
			break;
		case 13:
			char path_sl[80];
			printf("���������������·������");
			scanf("%s", path_sl);
			status res_sl;
			res_sl = SaveList(L, path_sl);
			if (res_sl == ERROR)
				printf("���Ա����ڣ�\n");
			else if (res_sl == INFEASIBLE)
				printf("·������\n");
			else
				printf("���Ա���ɹ���\n");
			getchar();getchar();
			break;
		case 14:
			char path_ll[80];
			printf("���������������·������");
			scanf("%s", path_ll);
			status res_ll;
			res_ll = LoadList(&L, path_ll);
			if (res_ll == ERROR)
				printf("���Ա����ڣ�\n");
			else if (res_ll == INFEASIBLE)
				printf("·������\n");
			else
				printf("���Ա��ȡ�ɹ���\n");
			getchar();getchar();
			break;
		case 15:
			if (ShowAllLists() == ERROR)
				printf("û���κ����Ա�");
			else
				printf("\n------------------ end ------------------------\n");
			getchar();getchar();
			break;
		case 16:
			char name_ltl[80];
			printf("��������������ƣ���");
			scanf("%s", name_ltl);
			if (GetList(name_ltl,&L) == ERROR)
				printf("����������Ϊ%s�����Ա�",name_ltl);
			else
				printf("���л�����%s\n", L->name);
			getchar();getchar();
			break;
		case 0:
			break;
		}
	}
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}
status InitList(SqList** L)
{
	printf("���������Ա�����");
	char temp[80];
	scanf("%s", temp);
	int i = 0;
	for (i = 1;i <= ListCount;i++)
		if (strcmp(temp, Lists[i].name) == 0)
			return INFEASIBLE;
	ListCount++;
	*L = Lists + ListCount;
	((*L)->elem) = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!((*L)->elem)) //�ڴ����ʧ��
		exit(OVERFLOW);
	(*L)->length = 0;
	strcpy((*L)->name, temp);
	(*L)->listsize = LIST_INIT_SIZE;
	return OK;
}
status DestroyList(SqList **L)
{
	if (!((*L)->elem)) //������
		return ERROR;
	free(((*L)->elem));
	int i, j;
	for (i = 1;i <= ListCount;i++)//�����Ա��������Ƴ����ݻٵı�
		if (strcmp(Lists[i].name,(*L)->name) == 0)
			for (j = i;j < ListCount;j++)
				Lists[j] = Lists[j + 1];
	ListCount--;
	*L = Lists;
	return OK;
}
status ClearList(SqList *L)
{
	if (!(L->elem)) //������
		return ERROR;
	int i;
	for (i = 1;i <= L->length;i++)
		(L->elem)[i] = 0;
	L->length = 0;
	return OK;
}
status ListEmpty(SqList *L)
{
	if (!(L->elem)) //������
		return ERROR;
	if (L->length == 0)
		return TRUE;
	return FALSE;
}
int ListLength(SqList *L)
{
	if (!(L->elem)) //������
		return ERROR;
	return L->length;
}
status GetElem(SqList *L, int i, ElemType& e)
{
	if (!(L->elem)) //������
		return ERROR;
	if (i > L->length || i <= 0)
		return OVERFLOW;
	e = (L->elem)[i];
	return OK;
}
int LocateElem(SqList *L, ElemType e, status(*compare)(ElemType a, ElemType b))
{
	if (!(L->elem)) //������
		return ERROR;
	int i;
	for (i = 1;i <= L->length;i++)
		if (compare((L->elem)[i], e))
			return i;
	return 0;
}
status PriorElem(SqList *L, ElemType cur_e, ElemType& pre_e)
{
	if (!(L->elem)) //������
		return ERROR;
	if ((L->elem)[1] == cur_e) //��ǰԪ��Ϊ����Ԫ��
		return INFEASIBLE;
	int i = LocateElem(L, cur_e, compare);
	if(i != 0)
	{
		pre_e = L->elem[i - 1];
		return  OK;
	}
	return ERROR;
}
status NextElem(SqList *L, ElemType cur_e, ElemType& next_e)
{
	if (!(L->elem)) //������
		return ERROR;
	if ((L->elem)[L->length] == cur_e) //��ǰԪ��Ϊ��βԪ��
		return INFEASIBLE;
	int i = LocateElem(L,cur_e,compare);
	if(i != 0)
	{
		next_e = L->elem[i + 1];
		return OK;
	}
	return ERROR;
}
status ListInsert(SqList *L, int i, ElemType e)
{
	if (!(L->elem)) //������
		return ERROR;
	if (i > L->length + 1 || i < 1)
		return INFEASIBLE;
	if (L->length == L->listsize - 1) //���ﵽ�����ޣ����·�������ڴ�
	{
		ElemType* temp = (L->elem);
		(L->elem) = (ElemType*)realloc((L->elem), (L->listsize + LISTINCREMENT) * sizeof(ElemType));
		if (!(L->elem)) //����ʧ�ܣ��ͷžɱ�ռ����-2�˳�����
		{
			free(temp);
			exit(OVERFLOW);
		}
		L->listsize += LISTINCREMENT;
	}
	int j;
	for (j = L->length;j >= i;j--)
		(L->elem)[j + 1] = (L->elem)[j];
	(L->elem)[i] = e;
	L->length++;
	return OK;
}
status ListDelete(SqList *L, int i, ElemType &e)
{
	if (!(L->elem)) //������
		return ERROR;
	if (i > L->length || i <= 0)
		return OVERFLOW;
	e = (L->elem)[i];
	int j;
	for (j = i;j <= L->length - 1;j++)
		(L->elem)[j] = (L->elem)[j + 1];
	L->length--;
	return OK;
}
status ListTraverse(SqList *L, void(*visit)(ElemType e))
{
	if (!(L->elem)) //������
		return ERROR;
	if (L->length == 0)
		return ERROR;
	int i;
	printf("\n-----------all elements -----------------------\n");
	for (i = 1;i <= L->length;i++)
		visit((L->elem)[i]);
	printf("\n------------------ end ------------------------\n");
	return OK;
}
status SaveList(SqList *L, char* path)
{
	if (!(L->elem))
		return ERROR;
	FILE* List = fopen(path, "w");
	if (!List)
		return INFEASIBLE;
	fprintf(List, "%d ", L->length);
	fwrite((L->elem) + 1, sizeof(ElemType), L->length, List);
	fprintf(List, "\n");
	fclose(List);
	return OK;
}
status LoadList(SqList** L, char* path)
{
	FILE* List = fopen(path, "r");
	if (!List)
		return INFEASIBLE;
	InitList(L);
	if (!((*L)->elem))
		return ERROR;
	fscanf(List,"%d",&((*L)->length));
	fgetc(List);
	if ((*L)->length >= (*L)->listsize)
	{
		while ((*L)->length >= (*L)->listsize)
			(*L)->listsize += LISTINCREMENT;
		ElemType* temp = ((*L)->elem);
		((*L)->elem) = (ElemType*)realloc(((*L)->elem), (*L)->listsize * sizeof(ElemType));
		if (!((*L)->elem))
		{
			free(temp);
			exit(OVERFLOW);
		}
	}
	fread(((*L)->elem) + 1, sizeof(ElemType), (*L)->length, List);
	fclose(List);
	return OK;
}
status ShowAllLists()
{
	if (!Lists[1].elem)
		return ERROR;
	int i;
	for (i = 1;i <= ListCount;i++)
		printf("���Ա�Lists[%d]�����֣�%s\n", i, Lists[i].name);
	return OK;
}
status GetList(char* name, SqList **L)
{
	if (!Lists[1].elem)
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