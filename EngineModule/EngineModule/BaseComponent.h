#pragma once


namespace EngineModule
{

	/// <summary>
	/// ������Ʈ �߻� Ŭ����
	/// </summary>
	class BaseComponent
	{
	public:
		virtual ~BaseComponent() {}


		virtual void Start() abstract;

		virtual void Update() abstract;

		virtual void UnInitialize() abstract;
	};

}
