#pragma once

namespace ImpReflect
{
	/// <summary>
	/// 리플렉션으로 객체를 생성하고 래핑하는 클래스
	/// </summary>
	class BaseVariant
	{
	public:
		virtual ~BaseVariant(){}

		/// 생성한 객체의 주소를 얻어온다.
		virtual void* Get()const abstract;

		/// 객체가 유효한지 확인
		virtual bool IsVaild()const abstract;

	};


}