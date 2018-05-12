#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stack>
using namespace std;

/**************最小堆**********/
class MinHeap
{
public:
	void createHeap()
	{
		make_heap(heap.begin(), heap.end()); //堆化
		sort_heap(heap.begin(), heap.end());//排序
	}
/**************每次插入一个元素后需要对整体进行排序，维持优先序列特性*****************/
	void push(int i)
	{
		heap.push_back(i);//插入
		createHeap();//排序，最小值为第一个元素
	}
	int top()
	{
		return heap[0];//返回最小值
	}
/***************返回最最小值中的最后一个元素**************/
	int back()
	{
		int a = heap[heap.size()-1];
//		heap.pop_back();
		return a;
	}
	int size()
	{
		return heap.size();
	}
	void print()
	{
		for(auto i : heap)
		{
			cout << i << " ";
		}
		cout << endl;
	}
/**************删除最后的一个元素，即最小堆中最大元素************/
	void pop()
	{
		heap.pop_back();
	}
public:
	vector<int> heap;
};

class MaxHeap
{
public:
	void createHeap()
	{
		make_heap(heap.begin(), heap.end());
		sort_heap(heap.begin(), heap.end());
		reverse(heap.begin(), heap.end());//首元素为最大一个元素
	}
/**************每次插入一个元素后需要对整体进行排序，维持优先序列特性*****************/
	void push(int i)
	{
		heap.push_back(i);
		createHeap();
	}
/************返回最大的元素************/
	int top()
	{
		return heap[0];		
	}
	int back()
	{
		int a = heap[heap.size()-1];
//		heap.pop_back();
		return a;
	}
/*****************删除最后一个元素********************/
	void pop()
	{
		heap.pop_back();
	}
	int size()
	{
		return heap.size();
	}
	void print()
	{
		for(auto i : heap)
		{
			cout << i << " ";
		}
		cout << endl;
	}
public:
	vector<int> heap;

};
/* 1.i个元素中较大值的一半放在最大堆中，较小的部分放在最小堆中
 * 2.在保持两个堆的大小较为平衡
 * 3.中位数分布在最大堆中的最后一个值和最小堆中的最后一个元素
 * 4.插入元素j时，j>Max_heap_min,放入最大堆，j<Min_heap_max,最小堆
 * 5.两者之间随意，需要保持两个堆的平衡
 */
/****************输入第i个元素时，计算此时的i个元素的中位数****************/
class Median
{
public:
	void get_data(MaxHeap &maxheap, MinHeap &minheap)
	{
		ifstream fin("Median.txt");
		string line;
		stringstream stream;
		int count = 1;
		while(getline(fin, line))
		{
			int data;
			stream.clear();
			stream << line;
			stream >> data;
			_storage.push_back(data);	
			median(data, maxheap, minheap);
			count ++;
		}
	}

	void median(int data, MaxHeap &maxheap, MinHeap &minheap)
	{	
		if(_storage.size() == 1) //只有一个元素的情况
		{
			_median.push_back(data);
		} else if(_storage.size() == 2) { //只有两个元素
			if(_storage[0] < _storage[1])
			{
				_median.push_back(_storage[0]);
				maxheap.heap.push_back(_storage[1]);
				minheap.heap.push_back(_storage[0]);
			} else {
				_median.push_back(_storage[1]);
				maxheap.heap.push_back(_storage[0]);
				minheap.heap.push_back(_storage[1]);
			}
		} else { //两个以上元素
			int max = minheap.back();
			int min = maxheap.back();
			if(data > min)
			{
				maxheap.push(data);
			} else {
				minheap.push(data);
			}	
			balance(maxheap, minheap);	
			if(minheap.size() >= maxheap.size())
			{
				_median.push_back( minheap.back() );
			} else {
				_median.push_back( maxheap.back() );
			}
		}
	}
/*******************保持两个堆数目的平衡*******************/	
	void balance(MaxHeap &maxheap, MinHeap &minheap)
	{
		int size1 = maxheap.size();
		int size2 = minheap.size();
		if(size1 - size2 == 2)	
		{
		//取出最大堆中最后一个元素放入最小堆
			int temp = maxheap.back();		
			maxheap.pop();
			minheap.push(temp);
		} else if (size2 - size1 == 2){
			int temp = minheap.back();//最后一个元素
			minheap.pop();//删除最后一个元素
			maxheap.push(temp);//将最后一个元素放入最大堆
		} else {
			;		
		}
	}

	void write()
	{
		ofstream fout;
		fout.open("output.txt");
		for(int i = 0; i < _median.size(); i++)
		{
			fout << "[" << i << "]:" << _median[i] << endl;
		}

	}
	void modo()
	{
		int sum = 0;
		for(auto i : _median)
		{
			sum += i;
		}
		cout << sum % 10000;
	}

public:
	vector<int> _median;
	vector<int> _storage;
};

int main()
{
	clock_t start, end;
	start = clock();
	MinHeap min_heap;
	MaxHeap max_heap;
	Median med;
	med.get_data(max_heap, min_heap);
	med.write();
	med.modo();
	end = clock();
	cout << "running time:" << (double)(end-start)/CLOCKS_PER_SEC << "s" << endl;
	return 0;
}




