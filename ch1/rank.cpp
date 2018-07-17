#include <iostream>

using namespace std;

// 二分法 
int rank(int *a, int size, int key) 
{
	int low = 0;
	int high = size - 1;
	while(low <= high)
	{
		int mid = low + (high - low)/2;
		if(key < a[mid])  high = mid - 1;
		else if (key > a[mid])  low = mid + 1;
		else  return mid;
	}

	return -1;
}

int main(int argc, char ** argv)
{
	// 数组必须有序 
	int a[10] = {0,1,2,3,4,8,81,250,452,1234};
	int index = -1;
	for(int i = 1; i<10; i++)
	{
		index = rank(a, 10, 2*i);
		if(index >= 0)
			cout<<"Find "<<2*i<<endl;
		else
			cout<<"Not find "<<2*i<<endl;
	}
	
 	return 0;
}
