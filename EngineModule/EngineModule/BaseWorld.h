#pragma once



namespace ImpEngineModule
{
	class Entity;

	/// <summary>
	/// World의 추상클래스
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