#include <iostream>
#include <string>
#include <cstring> 

using namespace std;

// 低位优先的字符串排序 
class LSD
{
public:
	// 通过前w个字符将a[]排序 
	static void sort(string a[], int n, int w)
	{
		int N = n; 
		int R = 256;	// 使用ASCII扩展字符表，有256个，满足键索引计数法的小整数要求 
		 
		string aux[N];
		for(int d = w-1; d >= 0; d--) 
		{
			// 根据第d个字符用键索引计数法排序
		
			int count[R+1];	//计算出现频率
			memset(count, 0, sizeof(int)*(R+1));
			
			for(int i = 0; i<N; i++) 
				count[a[i][d] + 1]++;
				
			for(int r = 0; r<R; r++)	// 将频率转换为索引 
				count[r+1] += count[r];
				
			for(int i = 0; i<N; i++)	//将元素分类 
			{
				aux[ count[a[i][d]] ] = a[i];
				count[a[i][d]]++;
			}	
			
				
			
			for(int i = 0; i<N; i++)	//回写 
				a[i]  = aux[i];
		}
		cout<<"sort done."<<endl;
	}
};

int main(int argc, char** argv)
{
	string a[13] = {"4PGC938", "2IYE230", "3CI0720", "1ICK750", "10HV845",
	"4JZY524", "1ICK750", "3CI0720", "10HV845", "10HV845", "2RLA629", "2RLA629",
	"3ATW723"
	};
	
	//for(int i = 0;i<13;i++)
	//cout<<'R' + 1<<endl;
	
	LSD::sort(a, 13, 7);
	
	for(int i = 0;i<13;i++)
		cout<<a[i]<<endl;
		
	return 0;
}

