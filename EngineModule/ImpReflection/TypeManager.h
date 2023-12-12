
#pragma once
namespace ImpReflection
{
	class Type;

	/// <summary>
	/// Runtime�� ���÷����� Type�� ���� �������� �����ϴ� Ŭ����
	/// ���������� Ŭ�����̴�.
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
		/// Type�̸����� TypeIndex�� ã�� �Լ�
		std::type_index GetTypeIndex(const std::string& name)const;

		/// Type�̸����� Type�� ã�� �Լ�
		ImpReflection::Type* GetType(const std::string & name)const;

		/// TypeIndex�� Type�� ã�� �Լ�
		ImpReflection::Type* GetType(std::type_index index)const;


	private:
		std::unordered_map<std::string, TypeInfomation> _infomations;
	};

}