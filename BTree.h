#pragma once
#ifndef _BTREE_H//避免重复定义，对于本次接口可有可无，主要用于多个源文件包含头文件的情况，语法为如果未定义则运行以下操作
#define _BTREE_H

const int m = 5;	//定义B树阶数，可以任意更换
const int max = m - 1;  //节点最大关键字数
const int min = (m - 1) / 2;//节点最小关键字数
const int inf = -10000;
typedef int KeyType;      //设定关键字类型

//需要的抽象数据类型
typedef struct BTNode {
	int Keynum;				//结点当前的关键字数
	KeyType key[m + 1];		//关键字数组，key[0]未用
	struct BTNode* parent;  //双亲结点指针
	struct BTNode* ptr[m + 1];//孩子结点指针数组
}BTNode, * BTree;				  //结点及指针类型

typedef struct {//B树的查找结果类型
	BTree pt;	//指向找到的节点
	int i;		//1<=i<=m，在结点中的关键字位序
	int tag;	//1表示查找成功，0，查找失败
}result;


typedef enum status {	//枚举类型（递增）返回类型，可有可无吧，当前用不上
	TRUE = 1,
	FALSE,
	OK,
	ERROR,
	OVERFLOW,
	EMPTY
}Status;

typedef struct LNode {               //链表和链表结点类型 
	BTree data;                     //数据域
	struct LNode* next;             //指针域
}LNode, * LinkList;

//声明的函数体
Status InitBTree(BTree& bt);						//初始化B树

int SearchBTNode(BTNode* p, KeyType k);				//在结点p中查找关键字k的插入位置i

result SearchBTree(BTree bt, KeyType k);			/*在树t上查找关键字k,返回结果(pt,i,tag)。若查找成功,则特征值
													 tag=1,关键字k是指针pt所指结点中第i个关键字;否则特征值tag=0,
													 关键字k的插入位置为pt结点的第i个*/
void InsertBTNode(BTNode*& p, int i, KeyType k, BTNode* q);//将关键字k和结点q分别插入到p->key[i+1]和p->ptr[i+1]中

void SplitBTNode(BTNode*& p, int s, BTNode*& q);					 //将p结点分裂成两个结点，前一半保留，后一半移入结点q

void NewRoot(BTNode*& bt, KeyType k, BTNode* p, BTNode* q);    //生成新的结点bt，原结点p和q为子树指针

void InsertBTree(BTree& bt, int i, KeyType k, BTNode* p);   //在树bt的结点q的key[i]和key[i+1]插入k，若引起结点过大，则沿双亲分裂

void Remove(BTNode* p, int i);							 //从结点p删除key[i]和它的孩子指针ptr[i]

void Successor(BTNode* p, int i);						 //	查找被删关键字p->key[i](在非叶子结点中)的替代叶子结点（右子树值最小的关键字）

void MoveRight(BTNode* p, int i);							 //将双亲结点p的最后一个关键字移入右结点q，将左结点aq最后一个关键字移入双亲结点p

void MoveLeft(BTNode* p, int i);							 //将双亲结点p的第一个关键字移入左结点aq，将结点q的第一个关键字移入p

void Combine(BTNode* p, int i);							  //将双亲p、右结点q合并入左结点aq，并调整p剩余关键字的位置

void Restore(BTNode* p, int i);						     //删除p中第i个关键字后，调整B树

void BTNodeDelete(BTNode* p, KeyType k);					 //在p查找并删除k

void BTreeDelete(BTNode*& bt, KeyType k);//删除框架，保护根节点，修bug补全

void DestroyBTree(BTree& bt);							 //递归释放B树

void FindBTNode(BTree& bt, KeyType k);								//查找节点是否存在

Status InitQueue(LinkList& L);							 //初始化队列 

LNode* CreateNode(BTree bt);							 //新建一个结点 

Status Enqueue(LNode* p, BTree bt);						 //元素q入队列

Status Dequeue(LNode* p, BTNode*& q);					 //出队列，并以q返回值

Status IfEmpty(LinkList L);								 //队列判空 

void DestroyQueue(LinkList L);							 //销毁队列

Status Traverse(BTree bt, LinkList L, int newline, int sum);//用队列遍历输出B树 

Status PrintBTree(BTree bt);								 //输出B树

void PrintfBTree(BTree bt, int deep);//凹入表形式

void Test();											 //测试B树功能函数

#endif 
