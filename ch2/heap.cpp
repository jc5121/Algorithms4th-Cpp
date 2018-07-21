#include <iostream>

using namespace std;

template<typename T>
class Heap
{
private:
	
   /***************************************************************************
    * Helper functions for comparisons and swaps.
    * Indices are "off-by-one" to support 1-based indexing.
    ***************************************************************************/
	static bool less(T*a, int x, int y)
	{
		return a[x-1] <= a[y-1];
	}
	
	static void exch(T* a, int i, int j)
	{
		T temp = a[i-1];
		a [i-1] = a[j-1];
		a[j-1] = temp;
	}
	
	static void sink(T* a, int k, int N)
	{
		while(2*k <= N)
		{
			int j = 2*k;
			if(j < N && less(a, j, j+1)) j++;
			if(!less(a, k, j)) break;
			exch(a, k, j);
			k = j;
		}
	} 
	/*
	// 上浮操作，在排序中没有用到 
	static void swim(T* a, int k)
	{
		while(k > 1 && less(a, k/2, k))
		{
			exch(k/2, k);
			k = k/2;
		}
	}
	*/
public:
	static bool isSorted(T* a, int N)
	{
		for(int i = 1;i<N;i++)
		{
			if(a[i] < a[i-1])
			{
				cout<<a[i-1]<<">"<<a[i]<<endl;
				return false;
			}
		}
		
		return true;
	}
	
	
	// 堆排序
	static void sort(T* a ,int N)
	{
		int n = N;
		// 构造阶段 
		for(int k = n/2; k >= 1; k--)
		{
			sink(a, k, n);
		}
		
		// 下沉排序 
		while(n > 1)
		{
			exch(a, 1, n--);
			sink(a, 1, n);
		}
	}
	
	static void show(T* a, int N)
	{
		for(int i = 0;i<N;i++)
		{
			cout<<a[i]<<" ";
		}
		cout<<endl;
	}
};

int main(int argc, char** argv)
{
	double a[10] = {0, 1.0, 5.6, 5.6, 145, 23.1, 0.1, 0.3, 5.6, 8.9};
	
	/* 使用了静态方法static，就不需要创建对象了，直接用类调用 
	Quick<double> quick_sort = Quick<double>();
	quick_sort.show(a, 10);
	quick_sort.sort(a, 10);
	if(quick_sort.isSorted(a, 10))
		cout<<"YES!------------------------------------QUICK"<<endl;
	quick_sort.show(a, 10);
	*/
	
	Heap<double>().show(a, 10);
	Heap<double>().sort(a, 10);
	if(Heap<double>().isSorted(a, 10))
		cout<<"YES!------------------------------------HEAP"<<endl;
	Heap<double>().show(a, 10);
	return 0;
}
