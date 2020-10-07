//递推实现 
#include<iostream>
#include"Stack.h"
//引用从网上看到的一句话： 
//“递归的算法主要是在划分子区间，如果要非递归实现快排，只要使用一个栈来保存区间就可以了。” 
//“一般将递归程序改成非递归首先想到的就是使用栈，因为递归本身就是一个压栈的过程。” 



void Swap(int &a,int &b)
{
	int temp = b;
	b = a;
	a = temp;
	
	return;
}

int PartSort(int* array,int left,int right)
{
    
    int& key = array[right];
    while(left < right)
    {
        while(left < right && array[left] <= key)//因为有可能有相同的值，防止越界，所以加上left < right
            ++left;
        while(left < right && array[right] >= key)
            --right;

        Swap(array[left],array[right]);
    }

    Swap(array[left],key);
    return left;
}

void QuickSort(int* array,int left,int right)
{

	Stack<int> *s = new Stack<int>();
	s->push(left);
	s->push(right);//后入的right，所以要先拿right
	while(!s->ifEmpty())//栈不为空
	{
		int right = s->getFirst();
		s->pop();
		int left = s->getFirst();
		s->pop();
		
		int index = PartSort(array,left,right);
		if((index - 1) > left)//左子序列
		{
			s->push(left);
			s->push(index - 1);
		}
		if((index + 1) < right)//右子序列
		{
			s->push(index + 1);
			s->push(right);
		}
	}
}


int main(int argc, char** argv) {
	
	int test[10] = {1,5,4,8,6,9,7,2,3,0};
	QuickSort(test,0,9);
	for(int i = 0;i<10;i++)
		cout<<test[i]<<" ";
	return 0;
}
