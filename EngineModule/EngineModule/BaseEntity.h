#pragma once

namespace EngineModule
{

	/// <summary>
	/// Entity�� �߻� Ŭ����
	/// </summary>
	class BaseEntity
	{
	public:
		virtual ~BaseEntity() {}

		virtual void Start() abstract;

		virtual void Update() abstract;

		virtual void DestroyAll() abstract;
	};

}