#pragma once
#include "Type.h"
#include "Meta.h"

namespace ImpReflection
{
	/// <summary>
	/// Class, Struct 정보를 저장한다
	/// 클래스의 멤버변수, 멤버변수 타입, 멤버변수의 오프셋등등
	/// 
	/// 하지만 상속관련해서 정보를 저장하지는 못한다 - 시간이 남는다면 도전
	/// </summary>
	class ClassType :
		public Type
	{
	public:
		struct Member
		{
			std::string _name; // 멤버변수 이름
			size_t _offset; // 멤버변수 오프셋
			Type* _type; // 멤버변수 Type정보
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
			/// Read 귀찮다...
		}
	
	private:
		std::vector<Member> _members;

		template <typename T> friend class ImpReflection::Meta;
	};


}