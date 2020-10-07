#include<iostream>
using namespace std;
#ifndef STACK_H
#define STACK_H

//定义双向链表的一个节点
template<class T>
class Node
{
	public:
		T value;
		Node* pre;
		Node* next;
	public:
		Node(){}
		Node(T value,Node *pre,Node*next){
			this->value=value;
			this->pre=pre;
			this->next=next;
		}
};

//简单版迭代器
template<class T>
struct  MyIterator
{
	typedef Node<T>* node;
	node data;

	MyIterator(){
		data = 0;
	}
	MyIterator(node other){
		data = other;
	}
	MyIterator(const MyIterator &rhs){
		data = rhs.data;
	}
	MyIterator& operator ++(){//重载前置自增符号
		data = data->next;
		return *this;
	}
	T& operator *(){
		return data->value;
	}
	bool operator != (const MyIterator& rhs){
		return rhs.data != data;
	}
	bool operator == (const MyIterator& rhs){
		return rhs.data == data;
	}

};

//双向链表
template<class 	T>
class DoubleLink{
public:
	typedef MyIterator<T> iteratorL;

public:

	DoubleLink();
	~DoubleLink();


//-------------以下五个函数都应为const
	int getLength() const;//链表长度
	int ifEmpty() const;//判空

	T get(int position) const;//获取节点的值
	T getFirst() const;//获取头节点的值
	T getLast() const;//获取尾节点的值
//-------------

	int insert(int position,T data);//插入
	int insertFirst(T data);//插入到最前
	int insertLast(T data);//插入到最后

	int del(int position);//删除
	int deleteFirst();//删除最前
	int deleteLast();//删除最后

	iteratorL begin();
	iteratorL end();

private:
	int length;
	Node<T> *pRoot;
	Node<T> *pTail;

private:
	Node<T> *getNode(int position) const;//获取节点指针
	//由于const成员函数无法调用非const成员函数，此处也应该加上const

};


template<class T>
DoubleLink<T>::DoubleLink():length(0)
{
	//长度初始化为0

	//创建链表头，无存储值
	pRoot = new Node<T>();
	pRoot->pre = pRoot->next = pRoot;

}

template<class T>
DoubleLink<T>::~DoubleLink()
{
	//删除所有含存储值的节点
	Node<T>* pTemp;
	Node<T>* pNode = pRoot->next;
	while(pNode!=pRoot)
	{
		pTemp=pNode;
		pNode=pNode->next;
		delete pTemp;
	}

	//删除链表头
	delete pRoot;
	pRoot = NULL;

}

//返回链表长度
template<class T>
int DoubleLink<T>::getLength() const
{
	return length;
}

//判断链表是否为空
template<class T>
int DoubleLink<T>::ifEmpty() const
{
	return length==0;
}

//获取第position位置的节点
template<class T> 
Node<T>* DoubleLink<T>::getNode(int position) const
{
	//判断参数是否有效
	if(position<0||position>=length)
	{
		cout<<"empty"<<endl;
		return NULL;
	}

	//查找
	int i=0;
	Node<T>* pPosition = pRoot->next;
	while(i++<position)
	{
		pPosition=pPosition->next;
	}

	return pPosition;
}

//获取第position位置节点的值
template<class T>
T DoubleLink<T>::get(int position) const
{
	return getNode(position)->value;
}

//获取头节点的值
template<class T>
T DoubleLink<T>::getFirst() const
{
	return getNode(0)->value;
}

//获取尾节点的值
template<class T>
T DoubleLink<T>::getLast() const
{
	return getNode(length-1)->value;
}

//插入新节点到第position位置之前
template<class T>
int DoubleLink<T>::insert(int position,T data)
{
	if(position==0)
		return insertFirst(data);

	Node<T>* pPosition=getNode(position);
	Node<T>* pNode=new Node<T>(data,pPosition->pre,pPosition);
	pPosition->pre->next=pNode;
	pPosition->pre=pNode;
	length++;

	return 0;
}

//插入新节点到链表开头
template<class T>
int DoubleLink<T>::insertFirst(T data)
{
	Node<T> *pNode=new Node<T>(data,pRoot,pRoot->next);
	pRoot->next->pre=pNode;
	pRoot->next=pNode;
	length++;

	return 0;
}

//插入新节点到链表尾部
template<class T>
int DoubleLink<T>::insertLast(T data)
{
	Node<T> *pNode = new Node<T>(data,pRoot->pre,pRoot);
	pRoot->pre->next=pNode;
	pRoot->pre=pNode;
	length++;

	return 0;
}


//删除第position位置的节点
template<class T>
int DoubleLink<T>::del(int position) 
{
	Node<T>* pPosition = getNode(position);
	pPosition->next->pre = pPosition->pre;
	pPosition->pre->next = pPosition->next;
	delete pPosition;
	length--;
 
	return 0;
}

//删除链表头节点
template<class T>
int DoubleLink<T>::deleteFirst() 
{
	return del(0);
}

//删除链表尾节点
template<class T>
int DoubleLink<T>::deleteLast()
{
	return del(length-1);
}

//迭代器函数
//获取第一个节点
template<class T>
typename DoubleLink<T>::iteratorL DoubleLink<T>::begin()
{
	return iteratorL(pRoot->next);
}

//获取最后一个节点的下一位置
template<class T>
typename DoubleLink<T>::iteratorL DoubleLink<T>::end()
{
	return iteratorL(getNode(length-1)->next);
}


//接下来定义一个堆栈
template<class T>
class Stack:public DoubleLink<T>
{
public:
	Stack();
	~Stack();

	void push(T data);//入堆栈
	void pop();//出堆栈
	T top() const;//查看顶部元素
};

template<class T>
Stack<T>::Stack(){}

template<class T>
Stack<T>::~Stack(){}

//入堆栈
template<class T>
void Stack<T>::push(T data)
{
	if(this->getLength()==0)
		this->insert(0,data);
	else
		this->insertFirst(data);

	return;
}

//出堆栈
template<class T>
void Stack<T>::pop()
{
	if(this->ifEmpty())
		return;
	else
		this->deleteFirst();

	return;
}

//查看顶部元素
template<class T>
T Stack<T>::top() const
{
	return	this->getFirst();
}

#endif
