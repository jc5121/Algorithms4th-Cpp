// union-find
#include <iostream> 
#include <fstream>
using namespace std;

class UF
{
private:
	int * id; //分量id（以节点作为索引） 
	int * size;
	int count;	

public:
	UF(int N)
	{
		count = N;
		id = new int[N];
		for(int i = 0;i<N;i++)
		{
			id[i] = i;
		}
		
		size = new int[N];
		for(int i = 0;i<N;i++)
		{
			size[i] = 1;
		}
	}
	
	~UF()
	{
		delete []id;
	}
	
	int find(int p);
	void union_node(int p, int q);
	
	int count_component() //不能用count() 
	{
		return count;
	}
	
	bool connected(int p, int q)
	{
		return find(p) == find(q);
	}
};

int UF::find(int p) 
{
	//跟随链接找到根节点
	while(p != id[p]) p = id[p];
	return p;
}

// 加权quick-union方法 
void UF::union_node(int p, int q)
{
	int i = find(p);
	int j = find(q);
	if(i == j) return;
	//将小树的根节点连接到大树的根节点 
	if(size[i] < size[j]){id[i] = j; size[j] += size[i];}
	else				 {id[j] = i; size[i] += size[j];}
	count--;
}

int main(int argc, char** argv)
{
	// 输入重定向 
	//ifstream fin("tinyUF.txt"); 0.005s, 2 components
	ifstream fin("mediumUF.txt"); //0.2s, 3 components
	//ifstream fin("largeUF.txt"); 143.6s, 6 components
	streambuf* cinbackup=cin.rdbuf(fin.rdbuf());
	/* 
	int a;
	while(cin)
	{
		cin>>a;
		cout<<a<<endl;
	 }
	*/ 
	int N;
	cin>>N;
	int p, q;
	UF uf =  UF(N);
	while(cin)
	{
		cin>>p>>q;
		if(uf.connected(p, q)) continue;
		uf.union_node(p, q);
		cout<<p<<" "<<q<<endl;
	}
	cout<<uf.count_component()<<" components."<<endl;
	return 0;
}


