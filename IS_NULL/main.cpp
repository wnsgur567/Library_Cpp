#include<iostream>
#include<cassert>


#define DELETED 0x0008123
#define DELETED_REF 0xdddddddd

// 1: nullptr �� ��� (�Ҵ����� �ʾҰų� nullptr)
// 2: �Ҵ� �� delete �� ��� (0x0008123)
// 3: delete�� �����͸� �����ϴ� �������� ��� (3�� �����͸� ����(*)�ϸ� 0xdddddddd)

#define IS_NULL(ptr) \
(\
((ptr) == nullptr) || \
((ptr) == reinterpret_cast<void*>(DELETED)) || \
(( *( reinterpret_cast<unsigned int*>(ptr) )) == (DELETED_REF))\
)\
? true : false

#define IS_NULL_CONST(ptr,non_const_type) \
(\
((ptr) == nullptr) || \
((ptr) == reinterpret_cast<void*>(DELETED)) || \
(( *( reinterpret_cast<unsigned int*>(  const_cast<non_const_type> (ptr) ) )) == (DELETED_REF))\
)\
? true : false

using namespace std;

template<typename T>
struct ListNode
{
public:
	ListNode* next;
	T value;
public:
	ListNode() :next(nullptr), value(T()) {}
	ListNode(T _value) : next(nullptr), value(_value)
	{}

	// ���������� Ȯ���� ���� ���
	bool operator == (const int& is_deleted)
	{
		assert(is_deleted == DELETED);
		return false;
	}

	template<typename T>
	friend std::ostream& operator<<(std::ostream& os, const ListNode<T>& _node);
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const ListNode<T>& _node)
{
	os << _node.value;
	return os;
}


void Test1();
void Test2();
void Test3();
void Test4();

int main()
{
	//Test1();
	//Test2();
	//Test3();
	//Test4();
}

//*data == NULL;
//*data == nullptr;	

// ���� �ڷ� Ÿ�� int
void Test1()
{
	void* addr = reinterpret_cast<void*>(DELETED);
	cout << addr << endl;

	int* data = new int(0);
	int* data2 = new int(10);
	int* ptr = data;	//	ptr �� data�� ������

	delete data;		// ptr �� data �� �޶���
		
	//cout << *data << endl; // ����
	//cout << *ptr << endl;	 // 0xdddddd

	bool a = IS_NULL(data);
	bool b = IS_NULL(ptr);
	bool c = IS_NULL(data2);

	cout << a << endl;
	cout << b << endl;
	cout << c << endl;	
}


// ���� �ڷ� Ÿ�� double
void Test2()
{
	double* data = new double(0.0000);
	double* data2 = new double(10.23566);
	double* ptr = data;	//	ptr �� data�� ������

	delete data;		// ptr �� data �� �޶���
		
	cout << hex << *(reinterpret_cast<unsigned int*>(ptr)) << endl;	 // 0xdddddd
	cout << hex << DELETED_REF << endl;
	if (*(reinterpret_cast<unsigned int*>(ptr)) == DELETED_REF)
	{
		cout << endl;
	}

	bool a = IS_NULL(data);
	bool b = IS_NULL(ptr);
	bool c = IS_NULL(data2);

	cout << a << endl;
	cout << b << endl;
	cout << c << endl;
}

// �⺻ Ŭ���� string
void Test3()
{
	string* data = new string("abc");
	string* data2 = new string("def");
	string* ptr = data;

	delete data;

	bool a = IS_NULL(data);
	bool b = IS_NULL(ptr);
	bool c = IS_NULL(data2);

	cout << a << endl;
	cout << b << endl;
	cout << c << endl;	
}

class A
{
public:
	int a;
	char* b;
	std::string c;
};

// ����� ���� Ŭ����
void Test4()
{
	ListNode<A>* data = new ListNode<A>();
	ListNode<A>* data2 = new ListNode<A>();
	ListNode<A>* ptr = data;

	delete data;

	bool a = IS_NULL(data);
	bool b = IS_NULL(ptr);
	bool c = IS_NULL(data2);

	cout << a << endl;
	cout << b << endl;
	cout << c << endl;
}