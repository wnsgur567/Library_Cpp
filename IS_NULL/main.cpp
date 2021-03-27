#include<iostream>
#include<cassert>


#define DELETED 0x0008123
#define DELETED_REF 0xdddddddd

// 1: nullptr 인 경우 (할당하지 않았거나 nullptr)
// 2: 할당 후 delete 한 경우 (0x0008123)
// 3: delete한 포인터를 참조하는 포인터인 경우 (3번 포인터를 참조(*)하면 0xdddddddd)

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

	// 지워졌는지 확인할 때만 사용
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

// 원시 자료 타입 int
void Test1()
{
	void* addr = reinterpret_cast<void*>(DELETED);
	cout << addr << endl;

	int* data = new int(0);
	int* data2 = new int(10);
	int* ptr = data;	//	ptr 과 data는 동일함

	delete data;		// ptr 과 data 는 달라짐
		
	//cout << *data << endl; // 뻑남
	//cout << *ptr << endl;	 // 0xdddddd

	bool a = IS_NULL(data);
	bool b = IS_NULL(ptr);
	bool c = IS_NULL(data2);

	cout << a << endl;
	cout << b << endl;
	cout << c << endl;	
}


// 원시 자료 타입 double
void Test2()
{
	double* data = new double(0.0000);
	double* data2 = new double(10.23566);
	double* ptr = data;	//	ptr 과 data는 동일함

	delete data;		// ptr 과 data 는 달라짐
		
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

// 기본 클래스 string
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

// 사용자 정의 클래스
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