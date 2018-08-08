/*****************************************/
/*�����������
/*�ݹ�ʵ�� 
/*****************************************/

#include "Graph.cpp"

class DepthFirstSearch
{
private:
	bool* marked = nullptr;
	int count = 0; 
	
	void dfs(Graph &G, int v)
	{
		marked[v] = true;
		count++;
		// c++ Ҳ����ô�ã� ���Ե� 
		for(int w : G.adjionVertex(v))
			if (!marked[w])
				dfs(G, w);
	}
public:
	
	bool* adjoin_v()
	{
		return marked;
	}
	
	DepthFirstSearch(Graph &G, int s)
	{
		// ��ֵ����Ϊfalse����Ҫ 
		marked = new bool[G.V()]; // �ڹ��캯����new��ֻnewһ�� 
		for(int i = 0;i<G.V();i++)
			marked[i] = false;
		dfs(G, s);
	}
	
	~DepthFirstSearch()
	{
		delete [] marked;
		marked = nullptr;
	}
	
};



// ����������ͨ������������������кͶ���v��ͨ�Ķ���  p524ͼ 
int main(int argc, char** argv)
{
	Graph G = Graph(8);
	G.addEdge(0, 1);
	G.addEdge(0, 2);
	G.addEdge(1, 3);
	G.addEdge(2, 4);
	G.addEdge(3, 5);
	G.addEdge(6, 7);
	
	DepthFirstSearch dfs = DepthFirstSearch(G, 2);
	
	bool* points = dfs.adjoin_v();
	
	std::cout<<"G����2��ͨ�ĵ��У�"<<std::endl; 
	for(int i = 0;i<8;i++)
	{
		if(points[i])
			std::cout<<i<<" ";		
	}
	
	
	return 0;
}
