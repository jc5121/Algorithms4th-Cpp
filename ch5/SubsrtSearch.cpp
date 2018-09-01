/*
**暴力子字符串查找算法 
*/ 

#include <iostream> 
#include <string>

using namespace std;

// 非显示退回 
int search1(string pat, string txt)
{
	int M = pat.length();
	int N = txt.length();
	// i是永远不退回的 
	for(int i = 0; i<N; i++)	
	{
		int j;
		for(j = 0; j<M; j++)
			if(txt[i+j] != pat[j])
				break;
		
		if(j == M) 
		{
			cout<<"found "<<pat<<" at "<<i<<"."<<endl;
			return i;	// 找到匹配 
		}
		
	}
	
	cout<<"not found "<<pat<<" ."<<endl;
	return N;	// 未找到匹配 
}

// 2显示退回 
int search2(string pat, string txt)
{
	int j, M = pat.length();
	int i, N = txt.length();
	// i会退回
	for(i = 0, j = 0;i<N && j<M; i++) 
	{
		if(txt[i] == pat[j]) j++;
		else
		{
			// 退回 
			i -= j;
			j = 0;
		}
	}
	
	if(j == M) 
	{
		cout<<"found "<<pat<<" at "<<i-M<<"."<<endl;
		return i-M;
	} 
	else
	{
		cout<<"not found "<<pat<<" ."<<endl;
		return N;
	}

}



int main(int argc, char** argv)
{
	
	search1("jc","kooobe,beeeko,jjjjc,cccj");
	search1("jay","kooobe,beeeko,jjjjc,cccj");
	
	search2("jc","kooobe,beeeko,jjjjc,cccj");
	search2("jay","kooobe,beeeko,jjjjc,cccj");
	return 0;
}
