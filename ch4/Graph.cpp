/********************************************************/
/*实现图的类 ： 
/*1.不使用邻接矩阵表示图，原因：需要V^2空间，不能满足 
/*2.使用邻接表的数据结构，空间与V+E成正比 
/*3.为了使代码简洁，不使用模版了，用int表示vertex 
/********************************************************/
#include <iostream>
#include <vector> 
#include <set> 

class Graph
{
private:
	std::vector<std::set<int> > adjoin_table; // 邻接表使用set容器，说明图不支持平行边 
	// set 的底层是红黑树，查询是log不是1，时间成本高了，可以考虑用vector替换（也不一定 ）。 
	int v;	// 顶点数 
	int e = 0;	// 边数 
	
public:
	Graph(int size);	//根据定点数构造
	void addEdge(int v, int w);	//添加一条边 v-w
	int V();	//顶点数
	int E();	//边数
	std::set<int>& adjionVertex(int v);	//和v相邻的所有顶点,不是连通的！ 

};

Graph::Graph(int size) 
{
	// 根据顶点数分配大小 
	v = size;
	adjoin_table.reserve(v);
	adjoin_table.resize(v);
}

void Graph::addEdge(int v, int w) 
{
	/*先判断是否存在，可是这样好像没用到set特性？ 
	**就算不加判断set也是不会插入的，可是计算边数又麻烦了 
	*/
	
	if(adjoin_table[v].find(w) != adjoin_table[v].cend())
	{
		std::cout<<"边已存在，插入失败。"<<std::endl;
			return;
	}
	
	adjoin_table[v].insert(w);
	adjoin_table[w].insert(v);
	e++;
	std::cout<<"添加边："<<v<<"----" <<w<<std::endl;
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
	std::cout<<"点数："<<G.V()<<std::endl;
	std::cout<<"边数："<<G.E()<<std::endl;
	
	std::set<int> tempSet = G.adjionVertex(0);
	std::cout<<"与0相邻的顶点有："<<std::endl; 
	std::set<int>::const_iterator i = tempSet.cbegin();
	for(;i != tempSet.cend(); i++)
		std::cout<<*i<<std::endl;
	std::cout<<tempSet.count(1);
	return 0;
}
*/
