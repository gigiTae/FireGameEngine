#pragma once


namespace ImpEngineModule
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
	};

}
