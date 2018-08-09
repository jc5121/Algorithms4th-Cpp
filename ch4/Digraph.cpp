/********************************************************/
/*����ͼ �� 
/*1.����ͼ��ʾ������ͼ����ֻ࣬��Ҫһ��insert()���� 
/*2.ʵ��һ��reverse()����������ͼ�ķ���ͼ 
/*3.Ϊ��ʹ�����࣬��ʹ��ģ���ˣ���int��ʾvertex 
/********************************************************/
#include <iostream>
#include <vector> 
#include <set> 

class Digraph
{
private:
	std::vector<std::set<int> > adjoin_table; // �ڽӱ�ʹ��set������˵��ͼ��֧��ƽ�б� 
	// set �ĵײ��Ǻ��������ѯ��log����1��ʱ��ɱ����ˣ����Կ�����vector�滻��Ҳ��һ�� ���� 
	int v;	// ������ 
	int e = 0;	// ���� 
	
public:
	Digraph(int size);	//���ݶ���������
	void addEdge(int v, int w);	//���һ���� v-w
	int V();	//������
	int E();	//����
	std::set<int>& adjionVertex(int v);	//��v���ڵ����ж���,������ͨ�ģ� 
	Digraph reverse(); //
};

Digraph::Digraph(int size) 
{
	// ���ݶ����������С 
	v = size;
	adjoin_table.reserve(v);
	adjoin_table.resize(v);
}

void Digraph::addEdge(int v, int w) 
{
	/*���ж��Ƿ���ڣ�������������û�õ�set���ԣ� 
	**���㲻���ж�setҲ�ǲ������ģ����Ǽ���������鷳�� 
	*/
	
	if(adjoin_table[v].find(w) != adjoin_table[v].cend())
	{
		std::cout<<"���Ѵ��ڣ�����ʧ�ܡ�"<<std::endl;
			return;
	}
	
	adjoin_table[v].insert(w);
	//adjoin_table[w].insert(v);
	e++;
	std::cout<<"��ӱߣ�"<<v<<"----" <<w<<std::endl;
}

int Digraph::V()
{
	return v;
}

int Digraph::E()
{
	return e;
}

std::set<int>& Digraph::adjionVertex(int v)
{
	return adjoin_table[v];
}

// Important
Digraph Digraph::reverse()
{
	Digraph R = Digraph(v);
	
	for(int i = 0; i<v; i++)
		for(int w:adjoin_table[i])
			R.addEdge(w, i);
			
	return R;
}

/*
int main(int argv, char** argc)
{
	Digraph G = Digraph(5);
	G.addEdge(0, 1);
	G.addEdge(0, 1);
	G.addEdge(0, 2);
	G.addEdge(0, 3);
	G.addEdge(2, 3);
	G.addEdge(3, 4);
	G.addEdge(1, 4);
	std::cout<<"������"<<G.V()<<std::endl;
	std::cout<<"������"<<G.E()<<std::endl;
	
	std::set<int> tempSet = G.adjionVertex(3);
	std::cout<<"��3���ڵĶ����У�"<<std::endl; 
	std::set<int>::const_iterator i = tempSet.cbegin();
	for(;i != tempSet.cend(); i++)
		std::cout<<*i<<std::endl;
	
	std::cout<<"Reversed:"<<std::endl;	
	Digraph R = G.reverse();
	
	std::cout<<"After reversed:"<<std::endl;
    tempSet = R.adjionVertex(3);
	std::cout<<"��3���ڵĶ����У�"<<std::endl; 
	i = tempSet.cbegin();
	for(;i != tempSet.cend(); i++)
		std::cout<<*i<<std::endl;
	
	std::cout<<"�����ȷ���ɻ�ͼ��֤"<<std::endl;
	//std::cout<<tempSet.count(1);
	return 0;
}
*/
