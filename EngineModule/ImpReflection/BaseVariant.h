#pragma once

namespace ImpReflect
{
	/// <summary>
	/// ���÷������� ��ü�� �����ϰ� �����ϴ� Ŭ����
	/// </summary>
	class BaseVariant
	{
	public:
		virtual ~BaseVariant(){}

		/// ������ ��ü�� �ּҸ� ���´�.
		virtual void* Get()const abstract;

		/// ��ü�� ��ȿ���� Ȯ��
		virtual bool IsVaild()const abstract;

	};


}