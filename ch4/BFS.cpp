/*****************************************/
/*广度优先搜索
/*不使用递归，用一个队列存放待检索的点
/*最短路径，是广度搜索的典型应用 
/*****************************************/

#include "Graph.cpp"
#include <queue>
#include <stack>
#include <cstring> // for memset()
class BreadthFirstPaths
{
private:
	bool* marked = nullptr;	//到达该顶点的最短路径已知吗 
	int* edgeTo = nullptr;	//到达该顶点的已知路径上的最后一个顶点 
	int origin = -1;
	int count = 1;
	void bfs(Graph G, int s)
	{
		std::queue<int> queue_v;
		//queue_v.reserve(G.V());
		marked[origin] = true;	// 标记起点 
		edgeTo[origin] = origin;
		queue_v.push(origin);	//将它加入队列
		while(!queue_v.empty()) 
		{
			int v = queue_v.front();
			queue_v.pop();
			for(int w:G.adjionVertex(v))
				if(!marked[w])
				{
					edgeTo[w] = v;
					marked[w] = true;
					//count++;
			    	queue_v.push(w); 
				}
		
		}
	}
public:
	bool hasPathTo(int v)
	{
		return marked[v];
	}
	// for test,not necessary
	int* edge()
	{
		if(edgeTo != nullptr)
			return edgeTo;
		else
			return nullptr;
	}
	// 输出s-d路径 
	void path(int d)
	{
		std::stack<int> path;
		int w = d;
		while(w != origin)
		{	
			path.push(w);
			w = edgeTo[w]; 	
		}
		// output
		std::cout<<origin<<"--"<<d<<"路径为："<<std::endl;
		std::cout<<origin<<std::endl;
		while(!path.empty())
		{
			std::cout<<path.top()<<std::endl;
			path.pop();
		}
	}
	
	// 根据图和起点构造 
	BreadthFirstPaths(Graph G, int s)
	{
		marked = new bool[G.V()];
		for(int i = 0;i<G.V();i++)
		{
			marked[i] = false;
		}			
		edgeTo = new int[G.V()];
		std::memset(edgeTo, 0, sizeof(int) * G.V());
		origin = s;
		bfs(G, s);
	}
	
	~BreadthFirstPaths() 
	{
		delete [] marked;
		marked = nullptr;
		delete [] edgeTo;
		edgeTo = nullptr;
	}
};


int main(int argc, char** argv)
{
	Graph G = Graph(6);
	G.addEdge(0, 1);
	G.addEdge(1, 2);
	G.addEdge(3, 2);
	G.addEdge(5, 4);
	G.addEdge(3, 4);
	G.addEdge(5, 0);
	
	int origin = 2;
	BreadthFirstPaths bfp = BreadthFirstPaths(G,origin);
	
	// for test
	int* edge = bfp.edge(); 
	std::cout<<"以2为起点："<<std::endl;
	for(int i = 0;i<G.V();i++)
		std::cout<<i<<"的上一点是："<<edge[i]<<std::endl;
	
	bfp.path(4);
	return 0;
}
