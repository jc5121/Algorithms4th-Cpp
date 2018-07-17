#include <iostream>
using namespace std;

int gdc(int p, int q)
{
	if(q == 0)
		return p;
	int r = p % q;
	return gdc(q, r); 
}

int main(int argc, char** argv){
	cout<<gdc(256, 100)<<endl;
	return 0;
}
