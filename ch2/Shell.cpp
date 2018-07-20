#include <iostream>

using namespace std;

template<typename T>
class Shell
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
		int h = 1;
		while(h < N/3) h = 3*h + 1;//这是怎么设置的？ +1是为了保证 h最后的值为 1 
		while(h >= 1)
		{
			for(int i = h;i<N;i++)
			{
				cout<<"insert "<<a[i]<<endl;  //这个输出要放在排序前面 
				for(int j = i; j>= h && less(a[j], a[j-h]); j-=h)
				{
					// 边比较边交换 
					exch(a, j, j-1);
				}
			}
			h = h/3;
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
	Shell<double> shell_sort = Shell<double>();
	shell_sort.show(a, 10);
	shell_sort.sort(a, 10);
	if(shell_sort.isSorted(a, 10))
		cout<<"YES!------------------------------------SHELL"<<endl;
	shell_sort.show(a, 10);
	return 0;
}
