#include <iostream>


class Component
{
public:
	Component() {}
	~Component() {}

};

class Fire : public Component
{
public:
	Fire() {};
	~Fire() {};

	static Component* Get();
};



int main() {

	Fire::Get(); 

	return 0;
}

Component* Fire::Get()
{
	Component* comp = new Fire();

	return comp;
}


