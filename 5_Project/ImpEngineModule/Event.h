#pragma once


namespace ImpEngineModule
{
	class Entity;
}

namespace ImpEngineModule::Event
{
	// Entity 생성 이벤트 
	struct OnEntityCreated
	{
		Entity* entity;
	};
	
	// Entity 삭제 이벤트
	struct OnEntityDestroyed
	{
		Entity* entity;
	};

}
