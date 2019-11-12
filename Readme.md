# ���пƼ���ѧ���ݽṹʵ��
### һ�����Ա��˳���ʵ��
ʵ�ֻ���˳�����ṹ�����Ա��16�ֲ�����  
```C
status InitList(SqList** L);
status DestroyList(SqList *L);
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
```
���Լ򵥵��û����档  
ʵ�����ļ��Ĵ洢��ȡ��������
### �������Ա������ʵ��
ʵ�ֻ�����ʽ����ṹ�����Ա��16�ֲ�����
```C
status InitList(SqList** L);
status DestroyList(SqList *L);
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
```
���Լ򵥵��û����档  
ʵ�����ļ��Ĵ洢��ȡ��������
### �����������Ķ�������ʵ��
ʵ�ֻ��ڶ�������ṹ�Ķ�������18�ֲ�����
```C
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
```
���Լ򵥵��û����档  
ʵ�����ļ��Ĵ洢��ȡ����������