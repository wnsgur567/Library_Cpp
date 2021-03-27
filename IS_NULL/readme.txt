
기본적으로 c++ raw 포인터를 사용 할 경우 안천한 사용을위해 다음과 같이 선언함

int* ptr = nullptr;     // 선언 시 nullptr 초기화
ptr = new int(10);

delete ptr;             // delete 한 포인터는 nullptr 이 아니므로 
ptr = nullptr;          // 삭제 이후 다시 nullptr 초기화


// 해결책1
template<typename T>
void safe_delete(T*& a) {
  delete a;
  a = nullptr;
}

그래서 기본적으로 위 과정을 define 혹은 template 으로 정의해 놓고 사용하는 경우가 많음
-----------------------------------------------------------------------------
하지만 아래와 같은 경우, '해결책1'의 방법으로는 안전하지 않음

int* ptr = nullptr;
ptr = new int(10);

int* ptrptr = ptr;  // ptr 과 동일한 주소를 가리키는 포인터

delete ptr;
ptr = nullptr;      // ptr 만 nullptr로 초기화 되었을 뿐
                    // ptrptr 에게 추가 조치가 되지 않았음
                    // 따라서 , 
                    // ptr == nullptr
                    // ptrptr == nullptr 은 false인 상태임
if(ptr == nullptr)
    // yes
if(ptrptr == nullptr)
    // no

따라서 다음과 같은 '해결책2'를 만듬
-----------------------------------------------------------------------------
// 해결책2

#define DELETED 0x0008123
#define DELETED_REF 0xdddddddd
#define IS_NULL(ptr) \
(\
((ptr) == nullptr) || \
((ptr) == reinterpret_cast<void*>(DELETED)) || \
(( *( reinterpret_cast<unsigned int*>(ptr) )) == (DELETED_REF))\
)\
? true : false




각 변수에 임의의 주소를 사용한다 가정하면
===================================
ptr         의 address는 10번지
ptrptr      의 address는 20번지
new int(10) 의 address는 999번지
===================================
ptr 과 ptrptr이 참조하는 주소는 999번지임
===================================
delete 이후 memory는 다음과 같이 셋팅됨

ex1) 

int* ptr = new int(10);     // ptr : 10번지       // new int(10) : 999번지
delete ptr;                 // ptr : 0x0008123    // new int(10) : 0xdddddddd

평소 단순 쓰래기 값이라 생각하던 부분에도 나름대로의 규칙을 가지고 셋팅됨
===================================
ex2)

int* ptr = new int(10);     // ptr : 10번지       // new int(10) : 999번지


int* ptrptr = ptr;          // ptrptr : 20번지

delete ptr;                 // ptr : 0x0008123    // *(new int(10) 였던 것의) : 0xdddddddd
ptr = nullptr;              // ptr : 0x0000000

ptrptr;                     // ptrptr : 999번지  // *ptrptr : 0xdddddddd

===================================

 1: nullptr 인 경우 (할당하지 않았거나 nullptr)
 2: 할당 후 delete 한 경우 (0x0008123)
 3: delete한 포인터를 참조하는 포인터인 경우 (3번 포인터를 참조(*)하면 0xdddddddd)
 
그래서 '해결책2'가 됨
설명끗





