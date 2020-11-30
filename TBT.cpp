#include<iostream>
#include<malloc.h>
using namespace std;

typedef struct BiThrNode {
    int val;
    struct BiThrNode* lchild, * rchild;
    bool LTag, RTag;
}BiThrNode, * BiThrTree;

//�Զ�����������
void InThreading(BiThrTree p, BiThrTree& pre) {
    if (p) {
        InThreading(p->lchild, pre);    

        if (!p->lchild) {                    
            p->LTag = true;
            p->lchild = pre;
        }
        else p->LTag = false;
        if (!pre->rchild) {                
            pre->RTag = true;
            pre->rchild = p;
        }
        else pre->RTag = false;

        pre = p;           //����p��λ��

        InThreading(p->rchild, pre);    
    }
}

//Thr��ͷ���,������ָ����ڵ㣬 �Һ���ָ���������һ�����
//�������һ�������Һ���ָ��Thr������һ���ػ�

void InOrderThreading(BiThrTree& Thrt, BiThrTree& T) {
    Thrt = (BiThrNode*)malloc(sizeof(BiThrNode));
    Thrt->LTag = false; Thrt->RTag = true;
    Thrt->rchild = Thrt;
    BiThrTree pre;
    if (!T) Thrt->lchild = Thrt;
    else {
        Thrt->lchild = T;
        pre = Thrt;
        InThreading(T, pre);                    //�������������
        pre->rchild = Thrt; pre->RTag = true; //���һ�����������
        Thrt->rchild = pre;
    }
}

void InOrderTraverse(BiThrTree Thrt) {
    BiThrNode* p = Thrt->lchild;    //��pָ�����ĸ��ڵ�
    while (p != Thrt) {
        while (p->LTag == false) p = p->lchild;    //ָ�����������·�
        cout << p->val << " ";
        while (p->RTag == true && p->rchild != Thrt) {
            p = p->rchild;
            cout << p->val << " ";
        }
        p = p->rchild;
    }
    cout << endl;
}

BiThrTree CreateBiTree(BiThrTree T, int val) {
    if (!T) {
        T = (BiThrNode*)malloc(sizeof(BiThrNode));
        T->val = val;
        T->lchild = T->rchild = NULL;
        return T;
    }
    if (val < T->val) T->lchild = CreateBiTree(T->lchild, val);
    if (val > T->val) T->rchild = CreateBiTree(T->rchild, val);
    return T;
}

void inorder(BiThrTree T) {
    if (!T) return;
    if (T->lchild) inorder(T->lchild);
    cout << T->val << " ";
    if (T->rchild) inorder(T->rchild);
}

int main() {
    int t[] = { 4,2,5,1,3,6,7 }, i;
    BiThrTree T = NULL, Thrt;
    for (i = 0; i < 7; i++) T = CreateBiTree(T, t[i]);
    inorder(T);
    cout << endl;
    InOrderThreading(Thrt, T);
    InOrderTraverse(Thrt);
    return 0;
}
