/********************************************************/
/*有向图 ： 
/*1.有向图表示比无向图更简洁，只需要一个insert()即可 
/*2.实现一个reverse()方法来返回图的反向图 
/*3.为了使代码简洁，不使用模版了，用int表示vertex 
/********************************************************/
#include <iostream>
#include <vector> 
#include <set> 

class Digraph
{
private:
	std::vector<std::set<int> > adjoin_table; // 邻接表使用set容器，说明图不支持平行边 
	// set 的底层是红黑树，查询是log不是1，时间成本高了，可以考虑用vector替换（也不一定 ）。 
	int v;	// 顶点数 
	int e = 0;	// 边数 
	
public:
	Digraph(int size);	//根据定点数构造
	void addEdge(int v, int w);	//添加一条边 v-w
	int V();	//顶点数
	int E();	//边数
	std::set<int>& adjionVertex(int v);	//和v相邻的所有顶点,不是连通的！ 
	Digraph reverse(); //
};

Digraph::Digraph(int size) 
{
	// 根据顶点数分配大小 
	v = size;
	adjoin_table.reserve(v);
	adjoin_table.resize(v);
}

void Digraph::addEdge(int v, int w) 
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
	//adjoin_table[w].insert(v);
	e++;
	std::cout<<"添加边："<<v<<"----" <<w<<std::endl;
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
	std::cout<<"点数："<<G.V()<<std::endl;
	std::cout<<"边数："<<G.E()<<std::endl;
	
	std::set<int> tempSet = G.adjionVertex(3);
	std::cout<<"与3相邻的顶点有："<<std::endl; 
	std::set<int>::const_iterator i = tempSet.cbegin();
	for(;i != tempSet.cend(); i++)
		std::cout<<*i<<std::endl;
	
	std::cout<<"Reversed:"<<std::endl;	
	Digraph R = G.reverse();
	
	std::cout<<"After reversed:"<<std::endl;
    tempSet = R.adjionVertex(3);
	std::cout<<"与3相邻的顶点有："<<std::endl; 
	i = tempSet.cbegin();
	for(;i != tempSet.cend(); i++)
		std::cout<<*i<<std::endl;
	
	std::cout<<"输出正确，可画图验证"<<std::endl;
	//std::cout<<tempSet.count(1);
	return 0;
}
*/
