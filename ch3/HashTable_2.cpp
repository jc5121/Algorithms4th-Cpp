/************************************************************************/
/* 文件说明： 
/* 采用分离链接法实现哈希表，采用C++标准库中的vector和list实现 
/* 
/************************************************************************/
#include <iostream>
#include <vector>
#include <list>
#include <string>
// using namespace std;      Don't do that, ever.  否则 

// 前置的声明必须有 
int hash(const std::string & key, const int &tableSize);
int hash(const int & key, const int &tableSize);

template <typename HashedObj>
class HashTable
{
public:
    //typedef vector<std::list<HashedObj> >::size_type SIZE;

    HashTable(int size = 101);     //初始化哈希表的大小
    ~HashTable(){}
    bool contains(const HashedObj & obj);
    bool insert(const HashedObj & obj);
    bool remove(const HashedObj & obj);
private:
    std::vector<std::list<HashedObj> > theList;   //哈希表
    int myhash(const HashedObj & obj);   //哈希函数  不能设定为const函数 
};


//函数定义
template <typename HashedObj>
HashTable<HashedObj>::HashTable(int size /*= 101*/)
{
    /*根据哈希表的大小分配vector的空间*/
    theList.reserve(size);
    theList.resize(size);
}

template <typename HashedObj>
int HashTable<HashedObj>::myhash(const HashedObj & obj) 
{
    //根据object不同调用不同版本的hash重载函数
    return hash(obj, theList.size());
}

/************************************************************************/
/* 函数名称：contains
/* 函数功能：查找指定对象是否在哈希表中
/* 返回值：存在返回true，不存在返回false
/************************************************************************/
template <typename HashedObj>
bool HashTable<HashedObj>::contains(const HashedObj & obj)
{
    int iHashValue = myhash(obj);
    const std::list<HashedObj> & tempList = theList[iHashValue];

    typename std::list<HashedObj>::const_iterator it = tempList.cbegin();

    for (; it != tempList.cend() && *it != obj; ++it);
    
    if(it != tempList.cend())
    {
    	std::cout<<"Get."<<std::endl;
    	 return true;
	}
    else
    {
    	std::cout<<"None."<<std::endl;
    	 return false;
	}
       
}

/************************************************************************/
/* 函数名称：insert
/* 函数功能：向hash表中插入元素，如果元素已经存在则返回false，不存在则在链表的最前面插入
/* 返回值：成功返回true，失败返回返回false
/************************************************************************/
template <typename HashedObj>
bool HashTable<HashedObj>::insert(const HashedObj & obj)
{
    int iHashValue = myhash(obj);

    std::list<HashedObj> & tempList = theList[iHashValue];
    if (contains(obj))
    {
    	std::cout<<"Already exit, insert fail."<<std::endl;
        return false;   //已经存在返回false
    }
	std::cout<<"Insert success."<<std::endl;
    tempList.push_back(obj);
    return true;
}

/************************************************************************/
/* 函数名称：remove
/* 函数功能：从哈希表中删除指定元素，如果元素不存在则返回false
/* 返回值：成功返回true，失败返回返回false
/************************************************************************/
template <typename HashedObj>
bool HashTable<HashedObj>::remove(const HashedObj & obj)
{
    typename std::list<HashedObj> & tempList = theList[myhash(obj)];
    // auto it = find(tempList.begin(), tempList.end(), obj);
    typename std::list<HashedObj>::const_iterator it = tempList.cbegin();

    for (; it != tempList.cend() && *it != obj; ++it);
    
    if (it == tempList.end())
    {
    	std::cout<<"Delete fail."<<std::endl;
        return false;
    }
    
    // delete函数 erase() 
    tempList.erase(it);
    std::cout<<"Delete success."<<std::endl;
    return true;
}

// 两种不同策略的hash函数 
int hash(const std::string & key, const int &tableSize)
{
    //采用公式：h = (k1*32 + k2) * 32 + k3，将其扩展到n次多项式
    long long int hashVal = 0;
    int count = 0;
    for (auto it = key.begin(); it != key.end(); ++it) 
    {
        if (count++ % 2 == 0)
        {
            hashVal += (hashVal << 5) + *it;
        }
        
    }
    return hashVal %= tableSize;
}

int hash(const int & key, const int &tableSize)
{
    return key % tableSize;
}

int main(int argv, char** argc)
{
	HashTable<std::string> st = HashTable<std::string>();
	st.insert("a");
	st.insert("b");
	st.insert("c");
	st.insert("a");
	st.remove("a");
	st.contains("a");
	st.remove("D");
}
