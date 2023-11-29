#pragma once
#include "IDataConverter.h"
#include "ECSHeader.h"

#include <fstream>
#include "ComponentContainer.h"

namespace Fire
{
	namespace ECS
	{
		/// <summary>
		/// �����͸� stirng ���·� ����
		/// </summary>
		class StringConverter :
			public IDataConverter
		{
			const std::wstring fileFomat = L".txt";
		public:
			StringConverter();
			~StringConverter();

			/// <summary>
			/// World ����ȭ
			/// - Entity :  
			/// - System : 
			/// </summary>
		    void SerializeWorld(World* world, const std::wstring& path, const std::wstring& name) override;

			/// <summary>
			/// World ������ȭ
			/// </summary>
			void DeserializeWorld(World* world, const std::wstring& path) override;

			/// <summary>
			/// Entity ������ȭ
			/// </summary>
			void DeserializeEntity(Entity* ent);
			
		private:
			/// <summary>
			/// Entity ����ȭ
			/// - Component : 
			/// </summary>
			void SerializeEntity(Entity* ent, std::ofstream& outputFile);

			/// <summary>
			/// C++ Reflection�� ������ �ʿ��ϴ�....
			/// </summary>
			template<typename T>
			void SerializeComponent(const T* component, std::ostream& outputFile);
		private:
			std::wstring GetFilePath(const std::wstring& path, const std::wstring& name);

		};
		
		template<typename T>
		inline void StringConverter::SerializeComponent(const T* component, std::ostream& outputFile)
		{
			TypeIndex index = GetTypeIndex<T>();
			std::string type = index.name();

			outputFile <<"componentType: " << type << " ";
			outputFile.write(reinterpret_cast<const char*>(component), sizeof(component)) << std::endl;
		}
		
	}
}

