#pragma once
#include "Component.h"

namespace ImpEngineModule
{
	/// <summary>
	/// �ӽ������� ������ Mesh
	/// ���� �κ� ��������
	/// </summary>
	class Mesh : public Component
	{
	public:
		Mesh();
		~Mesh();

		Component* Clone()const override;

		void Start() override;
		void Update(float dt) override;

		std::wstring GetPixelShaderPath() const { return _pixelShader; }
		void SetPixelShaderPath(std::wstring path) { _pixelShader = path; }
		std::wstring GetVertexShaderPath() const { return _vertexShader; }
		void SetVertexShaderPath(std::wstring path) { _vertexShader = path; }
		std::wstring GetMeshPath() const { return _texture; }
		void SetMeshPath(std::wstring val) { _texture = val; }

	private:
		std::wstring _pixelShader;
		std::wstring _vertexShader;
		std::wstring _texture;

		REFLECTION_FRIEND(ImpEngineModule::Mesh);
	};
}

