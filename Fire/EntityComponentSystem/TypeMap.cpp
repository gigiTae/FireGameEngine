#include "TypeMap.h"
#include "TypeDescriptor.h"
#include "ITypeResolver.h"
#include <assert.h>


namespace Fire
{
	namespace Reflect
	{
		void TypeMap::AddType(const std::string typeName, TypeDescriptor* desc)
		{
			auto iter = typeDescritors.find(typeName);

			if (iter != typeDescritors.end())
				return;

			typeDescritors.insert(std::make_pair(typeName, desc));
		}

		
		
		void* TypeMap::Get(const std::string typeName)
		{
			auto* desc = GetTypeDescriptor(typeName);
			
			if (desc == nullptr)
				return nullptr;

			size_t memorySize = desc->size;
			void* instance = new char[memorySize];

			return instance;
		}

		
		std::type_index TypeMap::GetTypeIndex(const std::string typeName)
		{
			for (auto& iter : typeIndexMap)
			{
				if (typeName == iter.second)
				{
					return iter.first;
				}

			}

			assert("해당하는 TypeIndex가 없습니다");
			return std::type_index(typeid(int));
		}

		TypeDescriptor* TypeMap::GetTypeDescriptor(std::type_index index)
		{
			auto iter = typeIndexMap.find(index);

			if (iter == typeIndexMap.end())
				return nullptr;

			return GetTypeDescriptor(iter->second);
		}

		TypeDescriptor* TypeMap::GetTypeDescriptor(const std::string& typeName)
		{
			auto iter = typeDescritors.find(typeName);

			if (iter == typeDescritors.end())
				return nullptr;

			return iter->second;
		}

		
	}
}

