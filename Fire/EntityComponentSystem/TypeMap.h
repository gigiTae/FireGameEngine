#pragma once

#include <unordered_map>
#include <string>
#include <typeindex>
#include <typeinfo>

namespace Fire
{
	namespace Reflect
	{
		struct ITypeResolver;
		struct TypeDescriptor;

		/// <summary>
		/// �̱��� ������ ���
		/// Reflection�� ������ Ÿ�Ե��� �����ϴ� Ŭ����
		/// 
		/// </summary>
		class TypeMap
		{
			using TypeName = std::string;
		public:
			static TypeMap* GetTypeMap() { static TypeMap typeMap; return &typeMap; }

			void AddType(const std::string typeName,TypeDescriptor* desc);
			template<typename T>
			void AddTypeIndex(const std::string& typeName);
			

			/// <summary>
			/// Type�� �ش��ϴ� �ν��Ͻ��� ��ȯ. 
			/// �ش��ϴ� Ÿ������ ĳ�����ؼ� ����Ѵ�.
			/// </summary>
			void* Get(const std::string typeName);

			TypeDescriptor* GetTypeDescriptor(std::type_index index);
			TypeDescriptor* GetTypeDescriptor(const std::string& typeName);

			const std::unordered_map<std::type_index, TypeName>& GetTypeIndexMap() const{ return typeIndexMap; }

		private:
			std::unordered_map<TypeName, TypeDescriptor*> typeDescritors;
			std::unordered_map<std::type_index, TypeName> typeIndexMap;

			TypeMap() =default;
			~TypeMap() = default;
		};


		template<typename T>
		inline void TypeMap::AddTypeIndex(const std::string& typeName)
		{
			std::type_index index = typeid(T);
			
			auto iter = typeIndexMap.find(index);
			if (iter != typeIndexMap.end())
				return;

			typeIndexMap.insert(std::make_pair(index, typeName));
		}

	}
}

