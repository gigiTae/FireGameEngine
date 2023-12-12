#pragma once

/// Reflection Macro Header

#define RTTR_FRIEND(type)\
friend class ImpReflection::Meta<type>;

/// ���ø� Ư��ȭ ����, static ���� �ʱ�ȭ�� ����ؼ� type������ �����Ѵ�.

/// class 
#define REFLECT_CHECK(type)\
		template<>\
		class ImpReflection::Meta<type>\
		{\
		public:\
			constexpr static bool IsReflect = true;\
			static class ImpReflection::ClassType _type;\
			static void Initialize(ImpReflection::ClassType*);\
		};

#define BEGIN_REFLECTION(type)\
		REFLECT_CHECK(type)\
		ImpReflection::ClassType ImpReflection::Meta<type>::_type\
			{ImpReflection::Meta<type>::Initialize};\
		void ImpReflection::Meta<type>::Initialize(ImpReflection::ClassType* classType)\
		{\
			using T = type;\
			classType->Set(TypeCategory::Class,#type,sizeof(T),[]()->void*{return new T();});\
		
#define MEMBER_RFLECTION(name)\
		 classType->_members.push_back(ImpReflection::ClassType::Member\
		{#name,offsetof(T,name),ImpReflection::TypeConverter<decltype(T::name)>::Get()});

#define END_REFLECTION() }

/// enum class

