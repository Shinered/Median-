#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stack>
using namespace std;


class MinHeap
{
public:
	void createHeap()
	{
		make_heap(heap.begin(), heap.end());
		sort_heap(heap.begin(), heap.end());
	}
	void push(int i)
	{
		heap.push_back(i);
		createHeap();
	}
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
		reverse(heap.begin(), heap.end());
	}
	void push(int i)
	{
		heap.push_back(i);
		createHeap();
	}
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
			//cout << "data:" << data << endl;
			median(data, maxheap, minheap);
//			maxheap.print();
//			minheap.print();
			count ++;
		}
	}

	void median(int data, MaxHeap &maxheap, MinHeap &minheap)
	{	
		if(_storage.size() == 1)
		{
			_median.push_back(data);
		} else if(_storage.size() == 2) {
			if(_storage[0] < _storage[1])
			{
				_median.push_back(_storage[0]);
				maxheap.heap.push_back(_storage[1]);
//				maxheap.createHeap();
				minheap.heap.push_back(_storage[0]);
//				minheap.createHeap();
			} else {
				_median.push_back(_storage[1]);
				maxheap.heap.push_back(_storage[0]);
//				maxheap.createHeap();
				minheap.heap.push_back(_storage[1]);
		//		minheap.createHeap();
			}
		} else {
			int max = minheap.back();
			int min = maxheap.back();
			if(data > min)
			{
				maxheap.push(data);
			} else {
				minheap.push(data);
			}	
			balance(maxheap, minheap);	
/*			maxheap.print();
			minheap.print();
			cout << "min:" << minheap.back() << endl;*/
			if(minheap.size() >= maxheap.size())
			{
				_median.push_back( minheap.back() );
			} else {
				_median.push_back( maxheap.back() );
			}
		}
//		cout << 4 << endl;
	}
		
	void balance(MaxHeap &maxheap, MinHeap &minheap)
	{
		int size1 = maxheap.size();
		int size2 = minheap.size();
		if(size1 - size2 == 2)	
		{
			int temp = maxheap.back();		
			maxheap.pop();
			minheap.push(temp);
		} else if (size2 - size1 == 2){
			int temp = minheap.back();
			minheap.pop();
			maxheap.push(temp);
		} else {
			;		
		}
//		cout << 3 << endl;
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




