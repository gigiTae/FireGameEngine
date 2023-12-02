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
		/// �̱��� ������ ���
		/// Reflection�� ������ Ÿ�Ե��� �����ϴ� Ŭ����
		/// 
		/// </summary>
		class TypeMap
		{
			using TypeName = std::string;
		public:
			static TypeMap* GetTypeMap() { static TypeMap typeMap; return &typeMap; }

			void AddType(const std::string typeName,ITypeDescriptor* desc);
			
			/// <summary>
			/// Type�� �ش��ϴ� �ν��Ͻ��� ��ȯ. 
			/// �ش��ϴ� Ÿ������ ĳ�����ؼ� ����Ѵ�.
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

