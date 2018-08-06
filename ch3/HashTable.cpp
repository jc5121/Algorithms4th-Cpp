/************************************************************************/
/* 文件说明：
/* 采用分离链接法实现哈希表，采用C++标准库中的vector和list实现 
/* 
/************************************************************************/
#include <iostream>
#include <vector>
#include <list> // STL中的链表 
#include <string>

// 存储项目的类型 
template <typename KeyType, typename ValueType>
struct ItemType
{
	KeyType key;
	ValueType value;
};

//template <typename KeyType, typename ValueType>


// 重载了不同参数的hash函数 
int hash(const std::string & key, const int &tableSize);
int hash(const int & key, const int &tableSize);


template <typename KeyType, typename ValueType>
class HashTable
{
	typedef typename std::list<ItemType<KeyType, ValueType>>::const_iterator ITERATOR;
public:
    HashTable(int size = 101);     //初始化哈希表的大小
    ~HashTable(){}
    
    // 为了识别typedef，定义到类内部了，真的蠢 
    
	/************************************************************************/
	/* 函数名称：contains
	/* 函数功能：查找指定对象是否在哈希表中
	/* 返回值：存在返回对象迭代器，不存在返回NULL 
	/************************************************************************/
    ITERATOR contains(const ItemType<KeyType, ValueType> & item)
    {
	    int iHashValue = myhash(item);
	    const std::list<ItemType<KeyType, ValueType>> & tempList = theList[iHashValue];
	
	    typename std::list<ItemType<KeyType, ValueType>>::const_iterator it = tempList.cbegin();
	
	    for (; it != tempList.cend() && (*it).key != item.key; ++it);
	    
	    if(it != tempList.cend())
	    {
	    	std::cout<<item.key<<" 命中："<<item.value<<std::endl;
	    	return it;
		} 
	       
	    else
	    {
	    	std::cout<<item.key<<" 未命中。"<<std::endl; 
	    	return tempList.cend();
		}
	        
    }
    
    
    void insert(const ItemType<KeyType, ValueType> & item);
    bool remove(const ItemType<KeyType, ValueType> & item);
    void get(const ItemType<KeyType, ValueType> & item);
    
private:
    
    std::vector<std::list<ItemType<KeyType, ValueType> > > theList;   //哈希表
    int myhash(const ItemType<KeyType, ValueType> & item) const;   //哈希函数
};


//函数定义
template <typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::HashTable(int size /*= 101*/)
{
    /*根据哈希表的大小分配vector的空间*/
    theList.reserve(size);
    theList.resize(size);
}

template <typename KeyType, typename ValueType>
int HashTable<KeyType, ValueType>::myhash(const ItemType<KeyType, ValueType> & item) const
{
    //根据object不同调用不同版本的hash重载函数
    return hash(item.key, theList.size());
}

/************************************************************************/
/* 函数名称：insert
/* 函数功能：向hash表中插入元素，如果元素已经存在则返回false，不存在则在链表的最前面插入
/* 返回值：成功返回true，失败返回返回false
/************************************************************************/
template <typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::insert(const ItemType<KeyType, ValueType> & item)
{
    int iHashValue = myhash(item);

    std::list<ItemType<KeyType, ValueType>> & tempList = theList[iHashValue];
	 
	typename std::list<ItemType<KeyType, ValueType>>::const_iterator it = contains(item);
	
    if (it != tempList.cend())
    {
    	//it.value = item.value;
    	std::cout<<"已存在，无法插入。"<<std::endl;
	}
        
	else
	{
		tempList.push_back(item);
		std::cout<<"插入成功！"<<std::endl;
	}
	
}

/************************************************************************/
/* 函数名称：remove
/* 函数功能：从哈希表中删除指定元素，如果元素不存在则返回false
/* 返回值：成功返回true，失败返回返回false
/************************************************************************/
template <typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::remove(const ItemType<KeyType, ValueType> & item)
{
    typename std::list<ItemType<KeyType, ValueType>> & tempList = theList[myhash(item)];
    
    typename std::list<ItemType<KeyType, ValueType>>::const_iterator it = tempList.cbegin();
	for (; it != tempList.cend() && (*it).key != item.key; ++it);
	
    if (it == tempList.end())
    {
    	std::cout<<"不存在，删除失败！" <<std::endl;
        return false;
    }
    std::cout<<"删除成功！" <<std::endl;
    tempList.erase(it);
    return true;
}

/************************************************************************/
/* 函数名称：get
/* 函数功能：根据键值从哈希表中查找元素 
/* 返回值：成功返回value值，失败提示不存在 
/************************************************************************/
/*
template <typename KeyType, typename ValueType>
// 这里应该只用key值的，改起来太麻烦了，so.... 
void HashTable<KeyType, ValueType>::get(const ItemType<KeyType, ValueType> & item)
{
	typename std::list<ItemType<KeyType, ValueType>>::const_iterator it = contains(item);
	if(it != tempList.cend())
	{
		std::cout<<item.key<<" 命中："<<it.value<<std::endl;
	}
	else
		std::cout<<item.key<<" 未命中。"<<std::endl; 
}
*/
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

int main(int argc, char** argv)
{
	ItemType<std::string, int> a; a.key = "a"; a.value = 1;
	ItemType<std::string, int> b; b.key = "b"; b.value = 2;
	ItemType<std::string, int> c; c.key = "c"; c.value = 3;
	
	HashTable<std::string, int> st = HashTable<std::string, int>(10);
	st.insert(a);
	st.insert(b);
	st.insert(c);
	st.insert(a);
	st.remove(a);
	st.remove(a);
	return 0;
}
