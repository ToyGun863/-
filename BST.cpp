#include<iostream>
#include <algorithm>
using namespace std;

struct Node
{
    Node *left,*right;
    int data;
    Node(int value)
    {
        left = NULL; 
		right = NULL;
        data = value;
    }
};

class BST
{
public:
    BST():root(NULL){};
    BST(int* arr,int n);
    ~BST();

    bool Insert(Node *&f,const int& value);

    bool Delete(Node* &p,const int& value);
	
	void Clear(Node* &p);
	
    void InOrderPrint(Node* p);

    Node* Search(int value);

public:
    Node* root;
};

BST::BST(int *arr,int n)
{
    int temp = arr[0];
    arr[0] = arr[n/2];
    arr[n/2] = temp;
    root = new Node(arr[0]);
    for(int i=1;i<n;i++)
    {
        Insert(root,arr[i]);
    }
}

BST::~BST()
{
    Clear(root);
}

bool BST::Insert(Node* &f,const int& value)
{
    if(f==NULL)
    {
        f = new Node(value);
        return true;
    }
    if(value<f->data)
    {
        Insert(f->left,value);
        return true;
    }
    if(value>f->data)
    {
        Insert(f->right,value);
        return true;
    }
    else
    {
        return false;
    }
    
}

bool BST::Delete(Node* &p,const int& value)
{
	//没有节点 
	if(p==NULL)
		return false;
	
	//只有一个节点
	if(p->left == NULL&&p->right==NULL)
	{
		if(p->data==value)
		{
			delete p;
			p = NULL;
			return true;	
		}	
		else
			return false;
	} 
	
	//递归删除
	if(value<p->data)
	{
		Delete(p->left,value);	
	} 
	else if(value>p->data)
	{
		Delete(p->right,value);
	}
	else
	{
		Node* del = NULL;
		
		if(p->left==NULL)
		{
			del = p;
			p = p->right;
			delete del;
			del = NULL;
			return true;
		}
		else if(p->right==NULL)
		{
			del = p;
			p = p->left;
			delete del;
			del = NULL;
			return true;
		}
		else
		{
			Node* rightFirst = p->right;
			
			while(rightFirst->left)
			{
				rightFirst = rightFirst->left;
			}
			
			swap(p->data,rightFirst->data);
			
			Delete(p->right,value); 
			return true;
		}
	}
}

void BST::Clear(Node* &p)
{
	delete p;
	p = NULL;
	cout<<"Cleared"<<endl;
	return;
}

//中序打印 
void BST::InOrderPrint(Node* p)
{
    if(p==NULL)
        return;
    InOrderPrint(p->left);
    cout<<p->data<<" ";
    InOrderPrint(p->right);
    return;
}

Node* BST::Search(int value)
{   
	Node* p = root;
	while(p)
	{
    	if(value<p->data)
        	p = p->left;
    	else if(value>p->data)
        	p = p->right;
    	else
    	{
    		cout<<"founded!"<<endl;
    		return p;
		}
	}
	cout<<"not found!"<<endl;
    return NULL;
}

int main()
{
    int arr[9]={10,5,12,4,81,65,33,49,71};
    BST * ptr=new BST(arr,9);//构建BST 
    ptr->InOrderPrint(ptr->root);//中序输出 
    Node* a = ptr->Search(12);
    cout<<a->left->data<<endl;//12的左节点 
    ptr->Delete(ptr->root,12);//删除12 
    ptr->InOrderPrint(ptr->root);
    return 0;
}