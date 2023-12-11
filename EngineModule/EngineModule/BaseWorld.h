#pragma once



namespace ImpEngineModule
{
	class Entity;

	/// <summary>
	/// World�� �߻�Ŭ����
	/// </summary>
	class BaseWorld
	{
	public:
		virtual ~BaseWorld() {}

		virtual void Reset() abstract;

		virtual void Start() abstract;

		virtual void Update(float dt) abstract;
	};

}