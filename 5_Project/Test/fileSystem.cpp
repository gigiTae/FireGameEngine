#include <iostream>
#include <filesystem>

#include "../ImpEngineModule/EngineModuleHeader.h"


using namespace ImpEngineModule;

class Postion : public Component
{
public:
	Component* Clone()const override;

	float x = 11.f;
	float y = 22.f;
	float z = 33.f;
	std::string data = "이거는 저장하는 시스템이다.";
	std::wstring data2 = L"정상적으로 출력하나?";
	std::unordered_map<std::string, std::string> mius{ {"key","value"} ,{"key2","tTime"} };
};

ImpEngineModule::Component* Postion::Clone() const
{

	return nullptr;
}

REFLECTION_BEGIN(Postion)
REFLECTION_MEMBER(x)
REFLECTION_MEMBER(y)
REFLECTION_MEMBER(z)
REFLECTION_MEMBER(data)
REFLECTION_MEMBER(data2)
REFLECTION_MEMBER_UNORDERED_MAP(mius,std::string,std::string)
REFLECTION_END()

int main()
{
	World world;

	WorldManager mgr;

	//mgr.Initialize(L"dd", &world);

	mgr.LoadWorld(L"MyFirstWorld");

	Entity* ent =  world.GetByIndex(0);

	std::cout << "22";
}