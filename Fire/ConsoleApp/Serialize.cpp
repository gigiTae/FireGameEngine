#include <iostream>
#include <fstream>
#include "StringConverter.h"
#include "World.h"

int main()
{
	using namespace Fire::ECS;

	World* world = new World();

	StringConverter converter{};
	converter.SerializeWorld(world, L"D:\\Fire\\data", L"firstFile");

	return 0;
}