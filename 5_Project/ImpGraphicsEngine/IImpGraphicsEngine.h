#pragma once
#include "../ImpStructure/ImpMath.h"
#include <string>
#pragma comment(lib, "d3d11.lib")
// temp
#pragma comment(lib, "../ImpGraphicsEngine/Effects11d.lib")

using namespace ImpMath;

namespace ImpGraphics
{
	struct LightInfo
	{
		Vector3 _position;
		Vector3 _rotation;

		size_t _lightType; // 0 Directional, 1 Spot, 2 Point
		Vector4 _color;
		int _intensity;
	};

	struct CameraInfo
	{
		Vector3 _position;
		Vector3 _rotation;
		Vector3 _scale;

		bool _isPerspective;
		float _fieldOfView;
		float _nearPlain;
		float _farPlain;
	};

	struct MeshObjectInfo
	{
		size_t _objectID;

		Vector3 _position;
		Vector3 _rotation;
		Vector3 _scale;

		std::string meshPath;
		std::string texturePath; // �ؽ�ó�� �������̸�?
		//Mesh ����ü�� �ʿ��ϴ�. FBX Loader���� ��� �������� �����غ���.
		// �ٵ� skinning�� ����Ǵ� Mesh�� 
		// animaition ������ �ִ� Mesh�� 
		// ������ Mesh�� ������?
		// �ƴ� �� ����.
		// ��� ������ ������?
		//Mesh* _mesh;
	};

	/// <summary>
	/// �ϴ� ���ӿ������� ����� �Լ��� ���� �ִ��� �����غ���.
	/// 1. ����Ʈ, ī�޶�, �޽��� �ʿ��ϴ�.
	/// 2. �������� �������� �ʾƵ� ������ ��ĸ� �����ϰ� �ϸ� ���� �� ����.
	/// 
	/// �������� ���� �׷��Ƚ� ������ �ʿ��� �� ������
	/// 1. �굵 interface�� ����� ������ ���� �δ� �� ������?
	/// 2. �������� �ִ� �Լ����� ������ �� �Լ����� �ñ״�ó�� �� �����;� �ϴ� �ǰ�?
	/// </summary>
	class IImpGraphicsEngine
	{
	public:
		enum class RendererType
		{
			Forward,
			Deferred
		};

	public:
		IImpGraphicsEngine() {};
		virtual ~IImpGraphicsEngine() {};

		/// �⺻ �������̽�
		virtual bool Initialize(int hinst, int hWnd, int screenWidth, int screenHeight) abstract;
		virtual void Update(float deltaTime) abstract;
		virtual void BeginRender() abstract;
		virtual void Render(RendererType rendererType) abstract;
		virtual void EndRender() abstract;
		virtual void Finalize() abstract;

		/// â ũ�� ��ȯ
		virtual void SetClientSize(int width, int height) abstract;

		/// �׸��� ���� �ʿ��� ������Ʈ��
		virtual void SetLight(LightInfo lightInfo) abstract;
		virtual void SetCamera(CameraInfo cameraInfo) abstract;
		virtual void SetMeshObject(MeshObjectInfo meshObjectInfo) abstract;

		// temp 
		/// IMGUI�� ���ؼ� �ʿ��� Device, DeviceContext ��ȯ
		// ���⿡ ID3D11Device�� ������� �Ƹ��� ���ӿ�������
		// D3D�� include �ؾ��� �� ����. �׷��ٰ� void* �� �´°ɱ�?
		virtual void* GetDevice() abstract;
		virtual void* GetDeviceContext() abstract;
	};
}