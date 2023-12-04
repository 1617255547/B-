#pragma once
#ifndef _BTREE_H//�����ظ����壬���ڱ��νӿڿ��п��ޣ���Ҫ���ڶ��Դ�ļ�����ͷ�ļ���������﷨Ϊ���δ�������������²���
#define _BTREE_H

const int m = 5;	//����B�������������������
const int max = m - 1;  //�ڵ����ؼ�����
const int min = (m - 1) / 2;//�ڵ���С�ؼ�����
typedef int KeyType;      //�趨�ؼ�������

//��Ҫ�ĳ�����������
typedef struct BTNode {
	int Keynum;				//��㵱ǰ�Ĺؼ�����
	KeyType key[m + 1];		//�ؼ������飬key[0]δ��
	struct BTNode* parent;  //˫�׽��ָ��
	struct BTNode* ptr[m + 1];//���ӽ��ָ������
}BTNode, * BTree;				  //��㼰ָ������

typedef struct {//B���Ĳ��ҽ������
	BTree pt;	//ָ���ҵ��Ľڵ�
	int i;		//1<=i<=m���ڽ���еĹؼ���λ��
	int tag;	//1��ʾ���ҳɹ���0������ʧ��
}result;


typedef enum status {	//ö�����ͣ��������������ͣ����п��ްɣ���ǰ�ò���
	TRUE = 1,
	FALSE,
	OK,
	ERROR,
	OVERFLOW,
	EMPTY
}Status;

typedef struct LNode {               //��������������� 
	BTree data;                     //������
	struct LNode* next;             //ָ����
}LNode, * LinkList;

//�����ĺ�����
Status InitBTree(BTree& bt);						//��ʼ��B��

int SearchBTNode(BTNode* p, KeyType k);				//�ڽ��p�в��ҹؼ���k�Ĳ���λ��i

result SearchBTree(BTree bt, KeyType k);			/*����t�ϲ��ҹؼ���k,���ؽ��(pt,i,tag)�������ҳɹ�,������ֵ
													 tag=1,�ؼ���k��ָ��pt��ָ����е�i���ؼ���;��������ֵtag=0,
													 �ؼ���k�Ĳ���λ��Ϊpt���ĵ�i��*/
void InsertBTNode(BTNode*& p, int i, KeyType k, BTNode* q);//���ؼ���k�ͽ��q�ֱ���뵽p->key[i+1]��p->ptr[i+1]��

void SplitBTNode(BTNode*& p, int s, BTNode*& q);					 //��p�����ѳ�������㣬ǰһ�뱣������һ��������q

void NewRoot(BTNode*& bt, KeyType k, BTNode* p, BTNode* q);    //�����µĽ��bt��ԭ���p��qΪ����ָ��

void InsertBTree(BTree& bt, int i, KeyType k, BTNode* p);   //����bt�Ľ��q��key[i]��key[i+1]����k�����������������˫�׷���

void Remove(BTNode* p, int i);							 //�ӽ��pɾ��key[i]�����ĺ���ָ��ptr[i]

void Successor(BTNode* p, int i);						 //	���ұ�ɾ�ؼ���p->key[i](�ڷ�Ҷ�ӽ����)�����Ҷ�ӽ�㣨������ֵ��С�Ĺؼ��֣�

void MoveRight(BTNode* p, int i);							 //��˫�׽��p�����һ���ؼ��������ҽ��q��������aq���һ���ؼ�������˫�׽��p

void MoveLeft(BTNode* p, int i);							 //��˫�׽��p�ĵ�һ���ؼ�����������aq�������q�ĵ�һ���ؼ�������p

void Combine(BTNode* p, int i);							  //��˫��p���ҽ��q�ϲ�������aq��������pʣ��ؼ��ֵ�λ��

void Restore(BTNode* p, int i);						     //ɾ��p�е�i���ؼ��ֺ󣬵���B��

void BTNodeDelete(BTNode* p, KeyType k);					 //��p���Ҳ�ɾ��k

void DestroyBTree(BTree& bt);							 //�ݹ��ͷ�B��

void FindBTNode(BTree& bt, KeyType k);								//���ҽڵ��Ƿ����

Status InitQueue(LinkList& L);							 //��ʼ������ 

LNode* CreateNode(BTree bt);							 //�½�һ����� 

Status Enqueue(LNode* p, BTree bt);						 //Ԫ��q�����

Status Dequeue(LNode* p, BTNode*& q);					 //�����У�����q����ֵ

Status IfEmpty(LinkList L);								 //�����п� 

void DestroyQueue(LinkList L);							 //���ٶ���

Status Traverse(BTree t, LinkList L, int newline, int sum);//�ö��б������B�� 

Status PrintBTree(BTree t);								 //���B�� 

void Test();											 //����B�����ܺ���

#endif 