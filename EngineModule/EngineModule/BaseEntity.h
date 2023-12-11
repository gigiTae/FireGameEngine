#pragma once

namespace ImpEngineModule
{

	/// <summary>
	/// Entity�� �߻� Ŭ����
	/// </summary>
	class BaseEntity
	{
	public:
		virtual ~BaseEntity(){}

		virtual void Start() abstract;

		virtual void Update(float dt) abstract;

		virtual void DestroyAllComponents() abstract;
	};

}