#include <iostream>


int main()
{
	char* c = new char[4];

	int* i = reinterpret_cast<int*>(c);

	delete i;

	return 0;
}