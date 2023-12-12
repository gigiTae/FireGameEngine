#pragma once
#include "Type.h"
#include "Meta.h"

namespace ImpReflection
{
	/// <summary>
	/// Class, Struct ������ �����Ѵ�
	/// Ŭ������ �������, ������� Ÿ��, ��������� �����µ��
	/// 
	/// ������ ��Ӱ����ؼ� ������ ���������� ���Ѵ� - �ð��� ���´ٸ� ����
	/// </summary>
	class ClassType :
		public Type
	{
	public:
		struct Member
		{
			std::string _name; // ������� �̸�
			size_t _offset; // ������� ������
			Type* _type; // ������� Type����
		};
	public:
		ClassType(void(*Initailize)(ClassType*))
			:Type("", 0, TypeCategory::Class), _members{}
		{
			Initailize(this);
		}

		ClassType(std::string name, size_t size, const std::initializer_list<Member>& init)
			:Type("", 0, TypeCategory::Class), _members{init} {}

		void Write(const void* object, std::string& data, int indentLevel /* = 0 */)const override
		{
			data += GetFullName();
			data += "{\n";
			for (const auto& member : _members)
			{
				data += std::string(2 * (indentLevel + 1), ' ');
				data += member._name;
				data += " = ";
				member._type->Write(reinterpret_cast<const char*>(object) + member._offset, data, indentLevel + 1);
			}
			data += std::string(2 * indentLevel, ' ') + "}";
		}

		void Read(void* object, const std::string& data, size_t begin, size_t end)const override
		{
			/// Read ������...
		}
	
	private:
		std::vector<Member> _members;

		template <typename T> friend class ImpReflection::Meta;
	};


}