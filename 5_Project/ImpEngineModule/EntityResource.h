#pragma once
#include "Resource.h"


namespace ImpEngineModule
{
	class Entity;

	/// <summary>
	/// Entity의 정보를 가지고 있는 리소스 ( 유니티로 생각하면 Prefab의 개념)
	/// Entity를 복사해서 전달한다.(프로토 타입 패턴 )
	/// </summary>
	class EntityResource : public Resource
	{
	public:
		EntityResource(const std::wstring& path);
		~EntityResource();

		/// 복사해서 Entity를 생성한다.
		[[nodiscard]]Entity* Clone();

		/// Entity를 복사한다.
		void Clone(Entity* ent) const;

		/// Entity 리소스 데이터를 읽어서 Entity객체를 생성
		void Load()override;
	private:
		void LoadEntity(); 


	private:
		std::unique_ptr<Entity> _entity; 
	};
	
}
