#include "TypeMap.h"


namespace Fire
{
	namespace Reflect
	{
		void TypeMap::AddType(const std::string name, TypeDescriptor* desc)
		{
			typeDescritors[name] = desc;
		}

	}
}

