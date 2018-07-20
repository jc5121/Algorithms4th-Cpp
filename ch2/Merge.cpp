#include <iostream> 
#include <algorithm>    // std::min
using namespace std;

template <typename T>
class Merge
{
private:
	T* aux = nullptr;  // 为编译器添加 -std=c++11
	static bool less(T x, T y)
	{
		return x < y;
	}
	
	// 基于归并操作的排序 
	void merge(T* a, int low, int mid, int high)
	{
		int i = low;
		int j = mid+1;
		
		for(int k = low; k<=high; k++)
			aux[k] = a[k];
			
		for(int k = low; k<= high; k++)
		{
			if(i > mid)						a[k] = aux[j++];
			else if(j > high)				a[k] = aux[i++];
			else if(less(aux[j], aux[i]))	a[k] = aux[j++];
			else							a[k] = aux[i++];
		}
	}
	
	
	void sort(T* a, int low, int high)
	{ 
		if(high <= low) return;
		int mid = low + (high-low)/2;
		sort(a, low, mid);
		sort(a, mid+1, high);
		merge(a, low, mid, high);
	}
	
public:
	/*
	~Merge()
	{
		if(aux != nullptr)
			delete []aux;
	}*/
	static bool isSorted(T* a, int N)
	{
		for(int i = 1;i<N;i++)
		{
			if(less(a[i], a[i-1])) return false;
		}
		return true;
	}
	
	static void show(T* a, int N)
	{
		for(int i = 0;i<N;i++)
		{
			cout<<a[i]<<" ";
		}
		cout<<endl;
	}
	
	// 自顶向下 
	void sort(T* a, int N)
	{
		aux = new T[N];
		sort(a, 0, N-1);
		delete []aux;
	}
	
	// 自底向上 代码看起来简单 没有递归 
	void sort_BU(T* a, int N) 
	{
		// 进行lgN次两两归并
		aux = new T[N];
		for(int size = 1; size < N; size *= 2) // size 子数组大小 
			for(int low = 0; low<N - size; low += (size + size)) // low 子数组索引
				merge(a, low, low+size-1, min(low + 2*size - 1, N-1));
		
		delete []aux;
	}
};


int main(int argc, char** argv)
{
	double a[10] = {2.3, 1.0, 5.6, 7.0, 145, 23.1, 0.1, 0.3, 4.4, 8.9};
	Merge<double> merge_sort = Merge<double>();
	merge_sort.show(a, 10);
	//merge_sort.sort(a, 10);
	merge_sort.sort_BU(a, 10);
	if(merge_sort.isSorted(a, 10))
		cout<<"YES!------------------------------------MERGE"<<endl;
	merge_sort.show(a, 10);
	return 0;
}

