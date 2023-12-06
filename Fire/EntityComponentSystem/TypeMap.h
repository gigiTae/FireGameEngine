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
		/// 싱글톤 패턴을 사용
		/// Reflection에 성공한 타입들을 저장하는 클래스
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
			/// Type에 해당하는 인스턴스를 반환. 
			/// 해당하는 타입으로 캐스팅해서 사용한다.
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

