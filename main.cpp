//����ʵ�� 
#include<iostream>
#include"Stack.h"
//���ô����Ͽ�����һ�仰�� 
//���ݹ���㷨��Ҫ���ڻ��������䣬���Ҫ�ǵݹ�ʵ�ֿ��ţ�ֻҪʹ��һ��ջ����������Ϳ����ˡ��� 
//��һ�㽫�ݹ����ĳɷǵݹ������뵽�ľ���ʹ��ջ����Ϊ�ݹ鱾�����һ��ѹջ�Ĺ��̡��� 



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
        while(left < right && array[left] <= key)//��Ϊ�п�������ͬ��ֵ����ֹԽ�磬���Լ���left < right
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
	s->push(right);//�����right������Ҫ����right
	while(!s->ifEmpty())//ջ��Ϊ��
	{
		int right = s->getFirst();
		s->pop();
		int left = s->getFirst();
		s->pop();
		
		int index = PartSort(array,left,right);
		if((index - 1) > left)//��������
		{
			s->push(left);
			s->push(index - 1);
		}
		if((index + 1) < right)//��������
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
