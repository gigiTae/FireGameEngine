#pragma once
#include "Resource.h"


namespace ImpEngineModule
{
	class Entity;

	/// <summary>
	/// Entity�� ������ ������ �ִ� ���ҽ� ( ����Ƽ�� �����ϸ� Prefab�� ����)
	/// Entity�� �����ؼ� �����Ѵ�.(������ Ÿ�� ���� )
	/// </summary>
	class EntityResource : public Resource
	{
	public:
		EntityResource(const std::wstring& path);
		~EntityResource();

		/// �����ؼ� Entity�� �����Ѵ�.
		[[nodiscard]]Entity* Clone();

		/// Entity�� �����Ѵ�.
		void Clone(Entity* ent) const;

		/// Entity ���ҽ� �����͸� �о Entity��ü�� ����
		void Load()override;
	private:
		void LoadEntity(); 


	private:
		std::unique_ptr<Entity> _entity; 
	};
	
}
