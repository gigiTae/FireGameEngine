
#pragma once
namespace ImpReflection
{
	class Type;

	/// <summary>
	/// Runtime에 리플렉션한 Type에 대한 정보들을 저장하는 클래스
	/// 전역적인인 클래스이다.
	/// </summary>
	class TypeManager
	{
		struct TypeInfomation
		{
			std::type_index index;
			ImpReflection::Type* type;
		};

#pragma region Singleton
	
	public:
		static TypeManager* GetInstance() { TypeManager mgr; return &mgr; }
	private:
		TypeManager(){}
		~TypeManager(){}

#pragma endregion

	public:
		/// Type이름으로 TypeIndex를 찾는 함수
		std::type_index GetTypeIndex(const std::string& name)const;

		/// Type이름으로 Type을 찾는 함수
		ImpReflection::Type* GetType(const std::string & name)const;

		/// TypeIndex로 Type을 찾는 함수
		ImpReflection::Type* GetType(std::type_index index)const;


	private:
		std::unordered_map<std::string, TypeInfomation> _infomations;
	};

}