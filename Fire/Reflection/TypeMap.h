#pragma once

#include <unordered_map>
#include <string>
#include "TypeDescriptor.h"

namespace Fire
{
	namespace Reflect
	{
		/// <summary>
		/// Type������ �������� �����ϴ� Ŭ����
		/// </summary>
		class TypeMap
		{
			using typeName = std::string;
		public:
			static TypeMap* Get() { static TypeMap typeMap; return &typeMap; }

			void AddType(const std::string name,TypeDescriptor* desc);
			
			
		public:
			std::unordered_map<typeName, TypeDescriptor*> typeDescritors;

			TypeMap() {};
		};


	}
}

