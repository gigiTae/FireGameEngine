#pragma once



namespace ImpEngineModule
{	
	template <typename T>
	class ComponentHandle
	{
	public:
		ComponentHandle() :_component(nullptr) {}
		ComponentHandle(T* component) :_component(component) {}

		T& Get() { return *component; }
		T* operator->() { return component; }

		bool IsVaild()const { return _component != nullptr; }
	private:
		T* _component;
	};

}
