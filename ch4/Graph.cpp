/********************************************************/
/*ʵ��ͼ���� �� 
/*1.��ʹ���ڽӾ����ʾͼ��ԭ����ҪV^2�ռ䣬�������� 
/*2.ʹ���ڽӱ�����ݽṹ���ռ���V+E������ 
/*3.Ϊ��ʹ�����࣬��ʹ��ģ���ˣ���int��ʾvertex 
/********************************************************/
#include <iostream>
#include <vector> 
#include <set> 

class Graph
{
private:
	std::vector<std::set<int> > adjoin_table; // �ڽӱ�ʹ��set������˵��ͼ��֧��ƽ�б� 
	// set �ĵײ��Ǻ��������ѯ��log����1��ʱ��ɱ����ˣ����Կ�����vector�滻��Ҳ��һ�� ���� 
	int v;	// ������ 
	int e = 0;	// ���� 
	
public:
	Graph(int size);	//���ݶ���������
	void addEdge(int v, int w);	//���һ���� v-w
	int V();	//������
	int E();	//����
	std::set<int>& adjionVertex(int v);	//��v���ڵ����ж���,������ͨ�ģ� 

};

Graph::Graph(int size) 
{
	// ���ݶ����������С 
	v = size;
	adjoin_table.reserve(v);
	adjoin_table.resize(v);
}

void Graph::addEdge(int v, int w) 
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
	adjoin_table[w].insert(v);
	e++;
	std::cout<<"��ӱߣ�"<<v<<"----" <<w<<std::endl;
}

int Graph::V()
{
	return v;
}

int Graph::E()
{
	return e;
}

std::set<int>& Graph::adjionVertex(int v)
{
	return adjoin_table[v];
}
/*
int main(int argv, char** argc)
{
	Graph G = Graph(5);
	G.addEdge(0, 1);
	G.addEdge(0, 1);
	G.addEdge(0, 2);
	G.addEdge(0, 3);
	G.addEdge(2, 3);
	G.addEdge(3, 4);
	G.addEdge(1, 4);
	std::cout<<"������"<<G.V()<<std::endl;
	std::cout<<"������"<<G.E()<<std::endl;
	
	std::set<int> tempSet = G.adjionVertex(0);
	std::cout<<"��0���ڵĶ����У�"<<std::endl; 
	std::set<int>::const_iterator i = tempSet.cbegin();
	for(;i != tempSet.cend(); i++)
		std::cout<<*i<<std::endl;
	std::cout<<tempSet.count(1);
	return 0;
}
*/
