#include <iostream>

using namespace std;

template<typename T>
class Quick
{
private:
	// 切分;切分元素选择最左边的 
	// static: 静态数据成员是类的成员，而不是对象的成员
	static int partition(T* a, int low, int high)
	{
		int i = low;
		int j = high+1;// 下面用的是--j 
		T v = a[low];
		while(true)
		{
			// 扫描左右，检查扫描是否结束并交换元素 
			while(less(a[++i], v)) if (i == high) break;//找到左侧比切分元素大的 元素 
			while(less(v, a[--j])) //if(j == low) break; 冗余，永远不会进行这个判断，在while条件中就判断过了 
			{
			//cout<<"测试条件是冗余的。"<<endl;
			} 
			if(i >= j) break;// i、j相遇时结束 
			exch(a, i, j);// 用到了交换 
		}
		exch(a, low, j);
		return j;
	}
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
	
	static void sort(T* a, int low, int high)
	{
		if(high <= low)	return;
		// if(high <= low + M){ Insertion<double>().sort(a, low, high);return}
		//在排序小数组时切换到插入排序,M为小数组大小 
		int j = partition(a, low, high);
		sort(a, low, j-1);
		sort(a, j+1, high);
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
	// 排序 这样是为了参数合理 
	static void sort(T* a ,int N)
	{
		sort(a, 0, N-1);
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
	double a[10] = {2.3, 1.0, 5.6, 5.6, 145, 23.1, 0.1, 0.3, 5.6, 8.9};
	
	/* 使用了静态方法static，就不需要创建对象了，直接用类调用 
	Quick<double> quick_sort = Quick<double>();
	quick_sort.show(a, 10);
	quick_sort.sort(a, 10);
	if(quick_sort.isSorted(a, 10))
		cout<<"YES!------------------------------------QUICK"<<endl;
	quick_sort.show(a, 10);
	*/
	
	Quick<double>().show(a, 10);
	Quick<double>().sort(a, 10);
	if(Quick<double>().isSorted(a, 10))
		cout<<"YES!------------------------------------QUICK"<<endl;
	Quick<double>().show(a, 10);
	return 0;
}
