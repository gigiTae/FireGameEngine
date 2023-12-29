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
		std::wstring GetFBXPath() const { return _fbx; }
		void SetFBXPath(std::wstring val) { _fbx = val; }

		// ���� �׷��Ƚ��� ����Ǿ��ִ���
		bool IsBindGraphics() const { return _isBindGraphics; }
		
		// �׷��Ƚ��� ������¸� �����Ѵ�.
		void SetBindGraphics(bool val) { _isBindGraphics = val; }
	private:
		std::wstring _pixelShader = L"../ImpGraphicsEngine/FirstNormalPS.hlsl";
		std::wstring _vertexShader = L"../ImpGraphicsEngine/FirstNormalVS.hlsl";
		std::wstring _fbx;

		bool _isBindGraphics;

		REFLECTION_FRIEND(ImpEngineModule::Mesh);
	};
}

