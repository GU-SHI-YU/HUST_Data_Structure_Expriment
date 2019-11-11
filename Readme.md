# 华中科技大学数据结构实验
### 一、线性表的顺序表实现
实现基于顺序表储存结构的线性表的16种操作。  
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
配以简单的用户界面。  
实现了文件的存储读取，多表管理。
### 二、线性表的链表实现
实现基于链式储存结构的线性表的16种操作。
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
配以简单的用户界面。  
实现了文件的存储读取，多表管理。