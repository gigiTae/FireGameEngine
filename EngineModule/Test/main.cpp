#include <iostream>
#include <type_traits>

class Base
{
public:
	Base(){}
};

class Guitar :Base
{
public:
	Guitar():Base(){}
};

class Container
{
public:
	template <typename T>
	T* Create();

};

template <typename T>
T* Container::Create()
{
	static_assert(std::is_base_of<Base, T>::value, "Component 상속관계가 아닙니다");

	T* base = new T();
	return base;
}

int main()
{
	Container c;

	c.Create<Guitar>();

	return 0;
}