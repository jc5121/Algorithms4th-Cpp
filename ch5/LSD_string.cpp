#include <iostream>
#include <string>
#include <cstring> 

using namespace std;

// ��λ���ȵ��ַ������� 
class LSD
{
public:
	// ͨ��ǰw���ַ���a[]���� 
	static void sort(string a[], int n, int w)
	{
		int N = n; 
		int R = 256;	// ʹ��ASCII��չ�ַ�����256���������������������С����Ҫ�� 
		 
		string aux[N];
		for(int d = w-1; d >= 0; d--) 
		{
			// ���ݵ�d���ַ��ü���������������
		
			int count[R+1];	//�������Ƶ��
			memset(count, 0, sizeof(int)*(R+1));
			
			for(int i = 0; i<N; i++) 
				count[a[i][d] + 1]++;
				
			for(int r = 0; r<R; r++)	// ��Ƶ��ת��Ϊ���� 
				count[r+1] += count[r];
				
			for(int i = 0; i<N; i++)	//��Ԫ�ط��� 
			{
				aux[ count[a[i][d]] ] = a[i];
				count[a[i][d]]++;
			}	
			
				
			
			for(int i = 0; i<N; i++)	//��д 
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

