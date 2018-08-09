#include "Digraph.cpp"
#include <iostream>
#include <stack>
#include <cstring>

class DirectedCycle
{
private:
	bool* marked = nullptr;
	int* edgeTo = nullptr;
	std::stack<int> cycle_stack; // 不能叫cycle，会和cycle()冲突，编译不通过 
	bool* onStack = nullptr; 
	
	void dfs(Digraph G, int v)
	{
		onStack[v] = true;
		marked[v] = true;
		for(int w: G.adjionVertex(v))
		{
			if(this->hasCycle())
				return;
			else if(!marked[w])
			{
				edgeTo[w] = v;
				dfs(G, w);
			}
			else if(onStack[w])	// 存在环
			{
				for(int x = v;x != w; x = edgeTo[x])	
				{
					cycle_stack.push(x);
					std::cout<<"push:"<<x<<std::endl;
				}
					
				cycle_stack.push(w);
				std::cout<<"push:"<<w<<std::endl;
				cycle_stack.push(v);
				std::cout<<"push:"<<v<<std::endl;
			} 
		}
		onStack[v] = false;
	}
	
public:
	DirectedCycle(Digraph G)
	{
		onStack = new bool[G.V()];
		memset(onStack, false, G.V());
		edgeTo = new int[G.V()];
		memset(edgeTo, 0, G.V());
		marked = new bool[G.V()];
		memset(marked, false, G.V());
		
		for(int i = 0;i<G.V();i++)
			if(!marked[i])
				dfs(G,i);
	}
	~DirectedCycle()
	{
		delete[] onStack;
		onStack = nullptr;
		delete[] edgeTo;
		edgeTo = nullptr;
		delete[] marked;
		marked = nullptr;
	}
	bool hasCycle()
	{
		return !cycle_stack.empty();
	}
	
	std::stack<int>& cycle()
	{
		return cycle_stack;
	}
};

int main(int argc, char** argv)
{
	Digraph G = Digraph(4);
	G.addEdge(0, 1);
	G.addEdge(1, 2);
	G.addEdge(2, 3);
	G.addEdge(3, 1);
	
	DirectedCycle dc = DirectedCycle(G);
	std::stack<int> cycle;
	if(dc.hasCycle())
	{
		std::cout<<"存在环："<<std::endl;
		cycle = dc.cycle();
		// 不能在循环判断条件中使用size()，原因：pop()会减少size 
		int n = cycle.size(); 
		for(int i = 0;i<n;i++)
		{
			std::cout<<cycle.top()<<std::endl;
			cycle.pop();
		}
			
	}
	return 0;
}
