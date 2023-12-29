#pragma once
#include "../ImpStructure/ImpMath.h"
#include <string>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "../x64/Debug/ImpFBXLoader.lib")

#ifdef IMPGRAPHICS
#define IMPGRAPHICS __declspec(dllexport)
#else
#define IMPGRAPHICS __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif 

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

		bool _isPerspective = false;
		float _fieldOfView = false;
		float _nearPlain = false;
		float _farPlain = false;
	};

	struct MeshObjectInfo
	{
		size_t _objectID;

		std::wstring _meshPath;

		std::wstring _vertexShaderPath;
		std::wstring _pisxelShaderPath;
	};

	/// <summary>
	/// 일단 게임엔진에서 사용할 함수가 뭐가 있는지 생각해보자.
	/// 1. 라이트, 카메라, 메쉬가 필요하다.
	/// 2. 렌더러를 생각하지 않아도 렌더링 방식만 선택하게 하면 좋을 것 같다.
	/// 
	/// 렌더러를 감싼 그래픽스 엔진이 필요할 것 같은데
	/// 1. 얘도 interface를 만들고 구현은 따로 두는 게 좋겠지?
	/// 2. 렌더러에 있는 함수들을 쓰려면 그 함수들의 시그니처를 또 가져와야 하는 건가?
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

		/// 기본 인터페이스
		virtual IMPGRAPHICS bool Initialize(int hinst, int hWnd, int screenWidth, int screenHeight) abstract;
		virtual IMPGRAPHICS void Update(float deltaTime) abstract;
		virtual IMPGRAPHICS void BeginRender() abstract;
		virtual IMPGRAPHICS void Render(RendererType rendererType) abstract;
		virtual IMPGRAPHICS void EndRender() abstract;
		virtual IMPGRAPHICS void Finalize() abstract;

		/// 창 크기 변환
		virtual IMPGRAPHICS void SetClientSize(int width, int height) abstract;

		/// 그리기 위해 필요한 오브젝트들
		virtual IMPGRAPHICS void SetLight(LightInfo lightInfo) abstract;
		virtual IMPGRAPHICS void SetCamera(CameraInfo cameraInfo) abstract;

		virtual IMPGRAPHICS void AddMeshObejct(MeshObjectInfo meshObjectInfo) abstract;
		virtual IMPGRAPHICS void SetMeshObject(size_t objectID, Matrix transformMatrix) abstract;
		virtual IMPGRAPHICS void DeleteMeshObject(size_t objectID) abstract;

		// temp 
		/// IMGUI를 위해서 필요한 Device, DeviceContext 반환
		// 여기에 ID3D11Device를 써버리면 아마도 게임엔진에서
		// D3D를 include 해야할 것 같다. 그렇다고 void* 가 맞는걸까?
		virtual IMPGRAPHICS void* GetDevice() abstract;
		virtual IMPGRAPHICS void* GetDeviceContext() abstract;
	};

	class EngineExporter
	{
	public:
		static IMPGRAPHICS IImpGraphicsEngine* GetEngine();
		static IMPGRAPHICS void DeleteEngine();

	private:
		static IImpGraphicsEngine* _engine;
	};
}

#ifdef __cplusplus
}
#endif 