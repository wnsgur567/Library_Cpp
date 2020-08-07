#pragma		once

#include<iostream>

namespace cha
{
	template<typename T>
	class unique_ptr
	{

	public:
		using pointer = T*;
		using element_type = T;

		//nullptr하나만 받을 수 있는 상수 타입 = nullptr_t
		unique_ptr() :data(nullptr) {}
		unique_ptr(nullptr_t) :data(nullptr) {}
		unique_ptr& operator = (nullptr_t)
		{
			reset();
			return *this;
		}

		//_Unique_ptr_enable_default_t ,_Zero_then_variadic_args_t 어디다 쓰는 건지 모르겠음
		explicit unique_ptr(pointer _Ptr) :data(_Ptr) {}
		unique_ptr(unique_ptr&& _Right) :data(_Right.release()) {}
		unique_ptr& operator=(unique_ptr&& _Right)
		{
			//자기 자신이 아닐 경우에만 수행
			if (this != std::addressof(_Right))
			{
				reset(_Right.release());
				data = std::forward(_Right.data);
			}
			return *this;
		}

		//unique_ptr(pointer _Ptr, const _Dx& _Dt) noexcept : _Mypair(_One_then_variadic_args_t(), _Dt, _Ptr) {}

		~unique_ptr()
		{
			if (data)
			{
				delete data;
			}
		}

	public:

		//data를 _Ptr(기본 nullptr)로
		//delete수행을 하는 듯...?
		void reset(pointer _Ptr = pointer())
		{
			pointer _Old = std::exchange(data, _Ptr);
			if (_Old)
			{
				//deleter 를 operator()(_Old)호출
				delete _Old;
			}
		}

		//data를 nullptr로
		//delete는 안함
		pointer release()
		{
			return std::exchange(data, pointer());
		}

		void swap(unique_ptr& _Right)
		{
			std::swap(data, _Right.data);
		}
	public:
		pointer operator->() const
		{
			return data;
		}
		pointer get() const
		{
			return data;
		}

		element_type operator * () const
		{
			return *data;
		}
		operator unique_ptr* ()
		{
			return this;
		}
	public:
		unique_ptr(const unique_ptr&) = delete;
		unique_ptr& operator=(const unique_ptr&) = delete;

	private:
		// unique_ptr은 _Mypair라는 객체를 가지는데 std::pair와 비슷합니다.
		// first에는 _Dx. 즉 deleter 함수 객체를 저장합니다.
		// second에는 저장하고 있는 포인터 객체를 저장합니다. 
		//_Compressed_pair<_Dx, pointer> _Mypair;

		T* data;
	};


	/*template<typename T>
	unique_ptr<T> make_unique(T&& _Args)
	{
		return unique_ptr<T>(new T(std::forward<T>(_Args)));
	}*/

	template<typename T, typename... Types>
	unique_ptr<T> make_unique(Types&&... _Args)
	{
		return unique_ptr<T>(new T(std::forward<Types>(_Args)...));	//new T(1) , new T(2) ....
	}


}