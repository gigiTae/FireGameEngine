#pragma once

namespace Fire
{
	namespace ECS
	{
		template <typename ComponentType>
		class ComponentHandle
		{	
		public:
			ComponentHandle() :component(nullptr){}
			ComponentHandle(ComponentType* component)
				:component(component) {}
		
			ComponentType& Get() { return *component; }
			ComponentType* operator ->() const { return component; }

			bool IsValid() { return component != nullptr; }

		private:
			ComponentType* component;
		};
	}
}

