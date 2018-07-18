#include <iostream> 
using namespace std;

//recursive
int rank(int* a, int key, int low, int high)
{
	if(low > high)  return -1;
	int mid = low + (high - low)/2;
	if (key < a[mid])  return rank(a, key, low, mid-1);
	else if (key > a[mid])  return rank(a, key, mid+1, high);
	else  return mid;
}

int main(int argc, char** argv)
{
	// 数组必须有序 
	int a[10] = {0,1,2,3,4,8,81,250,452,1234};
	int index = -1;
	for(int i = 0; i<10; i++)
	{
		index = rank(a, 2*i, 0, 9);
		if(index >= 0)
			cout<<"Find "<<2*i<<endl;
		else
			cout<<"Not find "<<2*i<<endl;
	}
	
 	return 0;
}
