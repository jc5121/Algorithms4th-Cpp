/*****************************************/
/*深度优先搜索
/*递归实现 
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
		// c++ 也能这么用？ 可以的 
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
		// 初值均设为false，必要 
		marked = new bool[G.V()]; // 在构造函数中new，只new一次 
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



// 测试用例，通过深度搜索，查找所有和顶点v连通的顶点  p524图 
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
	
	std::cout<<"G中与2连通的点有："<<std::endl; 
	for(int i = 0;i<8;i++)
	{
		if(points[i])
			std::cout<<i<<" ";		
	}
	
	
	return 0;
}
