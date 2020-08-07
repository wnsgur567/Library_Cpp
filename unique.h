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

		//nullptr�ϳ��� ���� �� �ִ� ��� Ÿ�� = nullptr_t
		unique_ptr() :data(nullptr) {}
		unique_ptr(nullptr_t) :data(nullptr) {}
		unique_ptr& operator = (nullptr_t)
		{
			reset();
			return *this;
		}

		//_Unique_ptr_enable_default_t ,_Zero_then_variadic_args_t ���� ���� ���� �𸣰���
		explicit unique_ptr(pointer _Ptr) :data(_Ptr) {}
		unique_ptr(unique_ptr&& _Right) :data(_Right.release()) {}
		unique_ptr& operator=(unique_ptr&& _Right)
		{
			//�ڱ� �ڽ��� �ƴ� ��쿡�� ����
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

		//data�� _Ptr(�⺻ nullptr)��
		//delete������ �ϴ� ��...?
		void reset(pointer _Ptr = pointer())
		{
			pointer _Old = std::exchange(data, _Ptr);
			if (_Old)
			{
				//deleter �� operator()(_Old)ȣ��
				delete _Old;
			}
		}

		//data�� nullptr��
		//delete�� ����
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
		// unique_ptr�� _Mypair��� ��ü�� �����µ� std::pair�� ����մϴ�.
		// first���� _Dx. �� deleter �Լ� ��ü�� �����մϴ�.
		// second���� �����ϰ� �ִ� ������ ��ü�� �����մϴ�. 
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