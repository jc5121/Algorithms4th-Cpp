/*
**�������ַ��������㷨 
*/ 

#include <iostream> 
#include <string>

using namespace std;

// ����ʾ�˻� 
int search1(string pat, string txt)
{
	int M = pat.length();
	int N = txt.length();
	// i����Զ���˻ص� 
	for(int i = 0; i<N; i++)	
	{
		int j;
		for(j = 0; j<M; j++)
			if(txt[i+j] != pat[j])
				break;
		
		if(j == M) 
		{
			cout<<"found "<<pat<<" at "<<i<<"."<<endl;
			return i;	// �ҵ�ƥ�� 
		}
		
	}
	
	cout<<"not found "<<pat<<" ."<<endl;
	return N;	// δ�ҵ�ƥ�� 
}

// 2��ʾ�˻� 
int search2(string pat, string txt)
{
	int j, M = pat.length();
	int i, N = txt.length();
	// i���˻�
	for(i = 0, j = 0;i<N && j<M; i++) 
	{
		if(txt[i] == pat[j]) j++;
		else
		{
			// �˻� 
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
