#pragma once

namespace EngineModule
{

	/// <summary>
	/// Entity의 추상 클래스
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