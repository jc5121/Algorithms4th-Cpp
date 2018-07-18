#include <deque>  
#include <stdexcept>  
#include <iostream>  
using namespace std;  
  
template <typename T>  
class stack  
{  
private:  
    deque<T> elems; //ʵ������  
  
public:  
    void push(T const&);  
    void pop(void);  
    T top() const;  
    bool empty() const //const���γ�Ա�����������޸ı����ö����ֵ 
    {  
        return elems.empty();  
    }  
  
    template<typename T2> //���Աģ��  
    stack <T>& operator= (stack<T2> const&);  
  
    //ʵ�ֵ�������  
    typedef const T* const_iterator;  
    T* end(void);  
    T* begin(void);  
};  
  
template <typename T>  
template <typename T2>  
stack<T>& stack<T>::operator =(const stack<T2> &op2) //override " = "
{  
    if((void*)this == (void*)&op2)  
        return *this;  
    stack<T2> tmp(op2);  
    elems.clear();  
  
    while(!tmp.empty())  
    {  
        elems.push_front(tmp.top());  
        tmp.pop();  
    }  
    return *this;  
}  
  
template <typename T>  
void stack<T>::push(T const& elem)  
{  
    elems.push_back(elem);  
}  
  
template <typename T>  
void stack<T>::pop()  
{  
    if(elems.empty())  
    throw out_of_range("stack<>::pop() :empty stack");  
        elems.pop_back();  
}  
//����ջ��Ԫ�� 
template <typename T>  
T stack<T>::top() const  
{  
    if(elems.empty())  
        throw out_of_range("stack<>::top() :empty stack");  
    return elems.back();  
}  
//ʵ�ֵ�����, ָ���һ��Ԫ�ء�
template <typename T>  
T* stack<T>::begin()  
{  
    return (&(elems.front()));  
}  
//����Ҫʵ�ֵ���ָ��δ�˵���һԪ�ء�  
template <typename T>  
T* stack<T>::end()  
{  
    return ((&(elems.back()))+1);  
}  
  
int main()  
{  
    stack<int> intStack;  
    stack<int> charStack;  
  
    intStack.push(10);  
    intStack.push(19);  
    intStack.push(39);  
  
    cout<<"top��"<<intStack.top()<<endl;  
    cout<<"��ֵ�������"<<endl;  
  
    charStack = intStack;  
  
    stack<int>::const_iterator iterator;  
    iterator = charStack.begin();  
    while(iterator != charStack.end())  
    {  
        cout<< *iterator<<endl;  
        ++iterator;  
    }  
}  
