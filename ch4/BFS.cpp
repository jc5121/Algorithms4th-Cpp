/*****************************************/
/*�����������
/*��ʹ�õݹ飬��һ�����д�Ŵ������ĵ�
/*���·�����ǹ�������ĵ���Ӧ�� 
/*****************************************/

#include "Graph.cpp"
#include <queue>
#include <stack>
#include <cstring> // for memset()
class BreadthFirstPaths
{
private:
	bool* marked = nullptr;	//����ö�������·����֪�� 
	int* edgeTo = nullptr;	//����ö������֪·���ϵ����һ������ 
	int origin = -1;
	int count = 1;
	void bfs(Graph G, int s)
	{
		std::queue<int> queue_v;
		//queue_v.reserve(G.V());
		marked[origin] = true;	// ������ 
		edgeTo[origin] = origin;
		queue_v.push(origin);	//�����������
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
	// ���s-d·�� 
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
		std::cout<<origin<<"--"<<d<<"·��Ϊ��"<<std::endl;
		std::cout<<origin<<std::endl;
		while(!path.empty())
		{
			std::cout<<path.top()<<std::endl;
			path.pop();
		}
	}
	
	// ����ͼ����㹹�� 
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
	std::cout<<"��2Ϊ��㣺"<<std::endl;
	for(int i = 0;i<G.V();i++)
		std::cout<<i<<"����һ���ǣ�"<<edge[i]<<std::endl;
	
	bfp.path(4);
	return 0;
}
