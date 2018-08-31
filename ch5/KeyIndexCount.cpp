/*
**键索引计数法 
**一种适用与小整数键的简单排序方法 
*/

#include <iostream>
#include <string>
#include <vector>
#include <cstring>  
using namespace std;

struct student
{
	string name;
	int key;
	
	student(string name, int key)
	{
		this->name = name;
		this->key = key;
	}
};

// N 学生个数, R 分组数 默认有第0组 
void key_index(vector<student>& a, int R)
{
	int N = a.size();
	vector<student> aux(a);
	int count[R+1];
	memset(count, 0, sizeof(int)*(R+1));	//必须有，以后养成这个习惯 
	
	//第一步，计算出现的频率 
	for(int i = 0; i<N; i++)
		count[a[i].key + 1]++;
	// for test	
	for(int i = 0; i<R+1; i++)
		cout<<count[i]<<endl;
	cout<<"1st done"<<endl;
	
	//第二步，将频率转化成索引
	for(int r = 0;r<R;r++) 
		count[r+1] += count[r];
	// for test	
	for(int i = 0; i<R+1; i++)
		cout<<count[i]<<endl;
	cout<<"2nd done"<<endl;	
	
	//第三步，将元素分类
	//这里后置++，容易出错 为了保证位置正确 
	for(int i = 0;i<N;i++) 	
	{
		aux[count[a[i].key]].name = a[i].name;
		aux[count[a[i].key]].key = a[i].key;
		count[a[i].key]++;
	}
	
	cout<<"3rd done"<<endl;	
	
	//第四步，回写
	for(int i = 0;i<N;i++) 
		a[i] = aux[i];
	cout<<"4th done"<<endl;
} 

int main(int argc, char** argv)
{
	vector<student> a;
	a.push_back(student("Anderson", 2)); 
	a.push_back(student("Brown", 3));
	a.push_back(student("Davis", 3));
	a.push_back(student("Garcia", 4));
	a.push_back(student("Harris", 1));
	a.push_back(student("Jackson", 3));
	a.push_back(student("Martinez", 2));
	a.push_back(student("Miller", 2));
	a.push_back(student("Moore", 1));
	a.push_back(student("Robinson", 2));
	
	cout<<a.size()<<endl;
	for(int i = 0;i<a.size();i++)
		cout<<a[i].name<<" "<<a[i].key<<endl;
	
	key_index(a, 5);
	
	for(int i = 0;i<a.size();i++)
		cout<<a[i].name<<" "<<a[i].key<<endl;
	return 0;
}
