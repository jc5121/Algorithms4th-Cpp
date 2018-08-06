/************************************************************************/
/* �ļ�˵����
/* ���÷������ӷ�ʵ�ֹ�ϣ������C++��׼���е�vector��listʵ�� 
/* 
/************************************************************************/
#include <iostream>
#include <vector>
#include <list> // STL�е����� 
#include <string>

// �洢��Ŀ������ 
template <typename KeyType, typename ValueType>
struct ItemType
{
	KeyType key;
	ValueType value;
};

//template <typename KeyType, typename ValueType>


// �����˲�ͬ������hash���� 
int hash(const std::string & key, const int &tableSize);
int hash(const int & key, const int &tableSize);


template <typename KeyType, typename ValueType>
class HashTable
{
	typedef typename std::list<ItemType<KeyType, ValueType>>::const_iterator ITERATOR;
public:
    HashTable(int size = 101);     //��ʼ����ϣ��Ĵ�С
    ~HashTable(){}
    
    // Ϊ��ʶ��typedef�����嵽���ڲ��ˣ���Ĵ� 
    
	/************************************************************************/
	/* �������ƣ�contains
	/* �������ܣ�����ָ�������Ƿ��ڹ�ϣ����
	/* ����ֵ�����ڷ��ض���������������ڷ���NULL 
	/************************************************************************/
    ITERATOR contains(const ItemType<KeyType, ValueType> & item)
    {
	    int iHashValue = myhash(item);
	    const std::list<ItemType<KeyType, ValueType>> & tempList = theList[iHashValue];
	
	    typename std::list<ItemType<KeyType, ValueType>>::const_iterator it = tempList.cbegin();
	
	    for (; it != tempList.cend() && (*it).key != item.key; ++it);
	    
	    if(it != tempList.cend())
	    {
	    	std::cout<<item.key<<" ���У�"<<item.value<<std::endl;
	    	return it;
		} 
	       
	    else
	    {
	    	std::cout<<item.key<<" δ���С�"<<std::endl; 
	    	return tempList.cend();
		}
	        
    }
    
    
    void insert(const ItemType<KeyType, ValueType> & item);
    bool remove(const ItemType<KeyType, ValueType> & item);
    void get(const ItemType<KeyType, ValueType> & item);
    
private:
    
    std::vector<std::list<ItemType<KeyType, ValueType> > > theList;   //��ϣ��
    int myhash(const ItemType<KeyType, ValueType> & item) const;   //��ϣ����
};


//��������
template <typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::HashTable(int size /*= 101*/)
{
    /*���ݹ�ϣ��Ĵ�С����vector�Ŀռ�*/
    theList.reserve(size);
    theList.resize(size);
}

template <typename KeyType, typename ValueType>
int HashTable<KeyType, ValueType>::myhash(const ItemType<KeyType, ValueType> & item) const
{
    //����object��ͬ���ò�ͬ�汾��hash���غ���
    return hash(item.key, theList.size());
}

/************************************************************************/
/* �������ƣ�insert
/* �������ܣ���hash���в���Ԫ�أ����Ԫ���Ѿ������򷵻�false�������������������ǰ�����
/* ����ֵ���ɹ�����true��ʧ�ܷ��ط���false
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
    	std::cout<<"�Ѵ��ڣ��޷����롣"<<std::endl;
	}
        
	else
	{
		tempList.push_back(item);
		std::cout<<"����ɹ���"<<std::endl;
	}
	
}

/************************************************************************/
/* �������ƣ�remove
/* �������ܣ��ӹ�ϣ����ɾ��ָ��Ԫ�أ����Ԫ�ز������򷵻�false
/* ����ֵ���ɹ�����true��ʧ�ܷ��ط���false
/************************************************************************/
template <typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::remove(const ItemType<KeyType, ValueType> & item)
{
    typename std::list<ItemType<KeyType, ValueType>> & tempList = theList[myhash(item)];
    
    typename std::list<ItemType<KeyType, ValueType>>::const_iterator it = tempList.cbegin();
	for (; it != tempList.cend() && (*it).key != item.key; ++it);
	
    if (it == tempList.end())
    {
    	std::cout<<"�����ڣ�ɾ��ʧ�ܣ�" <<std::endl;
        return false;
    }
    std::cout<<"ɾ���ɹ���" <<std::endl;
    tempList.erase(it);
    return true;
}

/************************************************************************/
/* �������ƣ�get
/* �������ܣ����ݼ�ֵ�ӹ�ϣ���в���Ԫ�� 
/* ����ֵ���ɹ�����valueֵ��ʧ����ʾ������ 
/************************************************************************/
/*
template <typename KeyType, typename ValueType>
// ����Ӧ��ֻ��keyֵ�ģ�������̫�鷳�ˣ�so.... 
void HashTable<KeyType, ValueType>::get(const ItemType<KeyType, ValueType> & item)
{
	typename std::list<ItemType<KeyType, ValueType>>::const_iterator it = contains(item);
	if(it != tempList.cend())
	{
		std::cout<<item.key<<" ���У�"<<it.value<<std::endl;
	}
	else
		std::cout<<item.key<<" δ���С�"<<std::endl; 
}
*/
int hash(const std::string & key, const int &tableSize)
{
    //���ù�ʽ��h = (k1*32 + k2) * 32 + k3��������չ��n�ζ���ʽ
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
