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
		/// 데이터를 stirng 형태로 관리
		/// </summary>
		class StringConverter :
			public IDataConverter
		{
			const std::wstring fileFomat = L".txt";
		public:
			StringConverter();
			~StringConverter();

			/// <summary>
			/// World 직렬화
			/// - Entity :  
			/// - System : 
			/// </summary>
		    void SerializeWorld(World* world, const std::wstring& path, const std::wstring& name) override;

			/// <summary>
			/// World 역직렬화
			/// </summary>
			void DeserializeWorld(World* world, const std::wstring& path) override;

			/// <summary>
			/// Entity 역직렬화
			/// </summary>
			void DeserializeEntity(Entity* ent);
			
		private:
			/// <summary>
			/// Entity 직렬화
			/// - Component : 
			/// </summary>
			void SerializeEntity(Entity* ent, std::ofstream& outputFile);

			/// <summary>
			/// C++ Reflection의 구현이 필요하다....
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

