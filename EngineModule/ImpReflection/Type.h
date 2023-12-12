#pragma once
#include "Meta.h"

namespace ImpReflection
{
	/// <summary>
	/// Type�� ���� �������� �����ϴ� Ŭ����
	/// </summary>
	class Type
	{
	public:
		using EnumMember = std::pair<std::string, int>;

	public:
		Type(const std::string& name, size_t size, TypeCategory category);

		virtual ~Type(){}

		/// Type �̸��� ��ȯ�Ѵ�.
		virtual const std::string& GetFullName()const { return _name; }
		
		/// string �����͸� object�� �ҷ��´�
		virtual void Read(void* object, const std::string& data, size_t begin, size_t end) const abstract;

		/// ������Ʈ�� �����͸� string �����ͷ� ��ȯ�Ѵ�.
		virtual void Write(const void* object,std::string& data, int indentLevel = 0)const abstract;

		/// category�� enum class�� ��� member���� ��ȯ�Ѵ�.
		virtual const std::vector<EnumMember>& GetEnumMembers() const;

		/// Ÿ�� ī�װ��� ��ȯ�Ѵ�.
		TypeCategory GetTypeCategory()const { return _category; }

		/// Type�� size�� ��ȯ�Ѵ�.
		size_t GetSize() const { return _size; }

	protected:
		void Set(TypeCategory category, const std::string& name, size_t size, std::function<void*()> func);

	private:
		TypeCategory _category = TypeCategory::None;
		std::string _name;
		size_t _size;
		std::function<void*()> Get;
	};
}
