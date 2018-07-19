#include <iostream>

using namespace std;

template<typename T>
class Selection
{
private:
	static bool less(T x, T y)
	{
		return x < y;
	}
	
	static void exch(T* a, int i, int j)
	{
		T temp = a[i];
		a [i] = a[j];
		a[j] = temp;
	}
	
public:
	static bool isSorted(T* a, int N)
	{
		for(int i = 1;i<N;i++)
		{
			if(less(a[i], a[i-1])) return false;
		}
		return true;
	}
	
	static void sort(T* a ,int N)
	{
		for(int i = 0;i<N;i++)
		{
			int min = i;//最小元素的索引
			for(int j = i+1;j<N;j++) 
			{
				if(less(a[j], a[min]))
					min = j;
			}
			exch(a, i, min);
			cout<<" exchange "<<a[i]<<"-"<<a[min]<<endl;
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
	double a[10] = {2.3, 1.0, 5.6, 7.0, 145, 23.1, 0.1, 0.3, 4.4, 8.9};
	Selection<double> select_sort = Selection<double>();
	select_sort.show(a, 10);
	select_sort.sort(a, 10);
	if(select_sort.isSorted(a, 10))
		cout<<"YES!------------------------------------"<<endl;
	select_sort.show(a, 10);
	return 0;
}
