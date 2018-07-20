#include <iostream>

using namespace std;

template<typename T>
class Quick
{
private:
	// �з�;�з�Ԫ��ѡ������ߵ� 
	// static: ��̬���ݳ�Ա����ĳ�Ա�������Ƕ���ĳ�Ա
	static int partition(T* a, int low, int high)
	{
		int i = low;
		int j = high+1;// �����õ���--j 
		T v = a[low];
		while(true)
		{
			// ɨ�����ң����ɨ���Ƿ����������Ԫ�� 
			while(less(a[++i], v)) if (i == high) break;//�ҵ������з�Ԫ�ش�� Ԫ�� 
			while(less(v, a[--j])) //if(j == low) break; ���࣬��Զ�����������жϣ���while�����о��жϹ��� 
			{
			//cout<<"��������������ġ�"<<endl;
			} 
			if(i >= j) break;// i��j����ʱ���� 
			exch(a, i, j);// �õ��˽��� 
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
		//������С����ʱ�л�����������,MΪС�����С 
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
	// ���� ������Ϊ�˲������� 
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
	
	/* ʹ���˾�̬����static���Ͳ���Ҫ���������ˣ�ֱ��������� 
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
