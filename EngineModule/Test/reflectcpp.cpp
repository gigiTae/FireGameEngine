#include <iostream>

#include "../ImpReflection/ImpReflectionHeader.h"


class Position
{
	float x;
	float y;
	float z;

public:
	RTTR_FRIEND(Position);
};

BEGIN_REFLECTION(Position)
MEMBER_RFLECTION(x)
MEMBER_RFLECTION(y)
MEMBER_RFLECTION(z)
END_REFLECTION()



int main()
{
	using namespace ImpReflection;

	Type* type = TypeConverter<Position>::Get();

	ClassType* classType = dynamic_cast<ClassType*>(type);

	return 0;
}