#pragma once

#include <string>

namespace Fire
{
	namespace ECS
	{
		class World;
		class Entity;

		/// <summary>
		/// 직렬화, 역직렬화 추상 클래스
		/// </summary>
		class IDataConverter 
		{
		public:
			virtual ~IDataConverter() {}

			/// <summary>
			/// World 직렬화
			/// </summary>
			virtual void SerializeWorld(World* world, const std::wstring& path, const std::wstring& name) = 0;

			/// <summary>
			/// World 역직렬화
			/// </summary>
			virtual void DeserializeWorld(World* world, const std::wstring& path)=0;
		};
	}
}


