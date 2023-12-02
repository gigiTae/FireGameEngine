#pragma once

#include <unordered_map>
#include <string>


namespace Fire
{
	namespace Reflect
	{
		struct ITypeResolver;
		struct ITypeDescriptor;

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

			void AddType(const std::string typeName,ITypeDescriptor* desc);
			
			/// <summary>
			/// Type에 해당하는 인스턴스를 반환. 
			/// 해당하는 타입으로 캐스팅해서 사용한다.
			/// </summary>
			void* Get(const std::string typeName);

			ITypeDescriptor* GetTypeDescriptor(const std::string& typeName);

		private:
			std::unordered_map<TypeName, ITypeDescriptor*> typeDescritors;

			TypeMap() =default;
			~TypeMap() = default;
		};


	}
}

