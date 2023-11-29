#pragma once

#include <string>

namespace Fire
{
	namespace ECS
	{
		class World;
		class Entity;

		/// <summary>
		/// ����ȭ, ������ȭ �߻� Ŭ����
		/// </summary>
		class IDataConverter 
		{
		public:
			virtual ~IDataConverter() {}

			/// <summary>
			/// World ����ȭ
			/// </summary>
			virtual void SerializeWorld(World* world, const std::wstring& path, const std::wstring& name) = 0;

			/// <summary>
			/// World ������ȭ
			/// </summary>
			virtual void DeserializeWorld(World* world, const std::wstring& path)=0;
		};
	}
}


