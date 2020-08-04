#include<iostream>
// a read-write property with data store and
// automatically generated get/set functions.
// this is what C++/CLI calls a trivial scalar property
template <class T>
class Property;

// a read-only property calling a user-defined getter
template <
	class T,
	class Object,
	typename T(Object::* real_getter)()
>
class ROProperty;
// a write-only property calling a user-defined setter
template <
	class T,
	class Object,
	typename T(Object::* real_setter)(T const&)
>
class WOProperty;
// a read-write property which invokes user-defined functions
template <
	class T,
	class Object,
	typename T(Object::* real_getter)(),
	typename T(Object::* real_setter)(T const&)
>
class RWProperty;
// a read-write named property with indexed access to own data store
template <
	class Key,
	class T,
	class Compare = std::less<Key>,
	class Allocator = std::allocator<std::pair<const Key, T> >
>
class IndexedProperty;


#include"Propery.hpp"