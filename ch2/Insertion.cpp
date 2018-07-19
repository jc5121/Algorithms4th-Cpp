#include <iostream>

using namespace std;

template<typename T>
class Insertion
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
	// 排序 
	static void sort(T* a ,int N)
	{
		for(int i = 1;i<N;i++)
		{
			cout<<"insert "<<a[i]<<endl;  //这个输出要放在排序前面 
			for(int j = i; j>0 && less(a[j], a[j-1]); j--)
			{
				// 边比较边交换 
				exch(a, j, j-1);
			}
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
	Insertion<double> insert_sort = Insertion<double>();
	insert_sort.show(a, 10);
	insert_sort.sort(a, 10);
	if(insert_sort.isSorted(a, 10))
		cout<<"YES!------------------------------------INSERT"<<endl;
	insert_sort.show(a, 10);
	return 0;
}
