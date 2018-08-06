/************************************************************************/
/* �ļ�˵���� 
/* ���÷������ӷ�ʵ�ֹ�ϣ������C++��׼���е�vector��listʵ�� 
/* 
/************************************************************************/
#include <iostream>
#include <vector>
#include <list>
#include <string>
// using namespace std;      Don't do that, ever.  ���� 

// ǰ�õ����������� 
int hash(const std::string & key, const int &tableSize);
int hash(const int & key, const int &tableSize);

template <typename HashedObj>
class HashTable
{
public:
    //typedef vector<std::list<HashedObj> >::size_type SIZE;

    HashTable(int size = 101);     //��ʼ����ϣ��Ĵ�С
    ~HashTable(){}
    bool contains(const HashedObj & obj);
    bool insert(const HashedObj & obj);
    bool remove(const HashedObj & obj);
private:
    std::vector<std::list<HashedObj> > theList;   //��ϣ��
    int myhash(const HashedObj & obj);   //��ϣ����  �����趨Ϊconst���� 
};


//��������
template <typename HashedObj>
HashTable<HashedObj>::HashTable(int size /*= 101*/)
{
    /*���ݹ�ϣ��Ĵ�С����vector�Ŀռ�*/
    theList.reserve(size);
    theList.resize(size);
}

template <typename HashedObj>
int HashTable<HashedObj>::myhash(const HashedObj & obj) 
{
    //����object��ͬ���ò�ͬ�汾��hash���غ���
    return hash(obj, theList.size());
}

/************************************************************************/
/* �������ƣ�contains
/* �������ܣ�����ָ�������Ƿ��ڹ�ϣ����
/* ����ֵ�����ڷ���true�������ڷ���false
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
/* �������ƣ�insert
/* �������ܣ���hash���в���Ԫ�أ����Ԫ���Ѿ������򷵻�false�������������������ǰ�����
/* ����ֵ���ɹ�����true��ʧ�ܷ��ط���false
/************************************************************************/
template <typename HashedObj>
bool HashTable<HashedObj>::insert(const HashedObj & obj)
{
    int iHashValue = myhash(obj);

    std::list<HashedObj> & tempList = theList[iHashValue];
    if (contains(obj))
    {
    	std::cout<<"Already exit, insert fail."<<std::endl;
        return false;   //�Ѿ����ڷ���false
    }
	std::cout<<"Insert success."<<std::endl;
    tempList.push_back(obj);
    return true;
}

/************************************************************************/
/* �������ƣ�remove
/* �������ܣ��ӹ�ϣ����ɾ��ָ��Ԫ�أ����Ԫ�ز������򷵻�false
/* ����ֵ���ɹ�����true��ʧ�ܷ��ط���false
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
    
    // delete���� erase() 
    tempList.erase(it);
    std::cout<<"Delete success."<<std::endl;
    return true;
}

// ���ֲ�ͬ���Ե�hash���� 
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
