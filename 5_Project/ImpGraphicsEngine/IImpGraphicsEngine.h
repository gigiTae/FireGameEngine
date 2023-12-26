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
		std::string texturePath; // 텍스처가 여러장이면?
		//Mesh 구조체가 필요하다. FBX Loader에서 어떻게 가져올지 생각해보자.
		// 근데 skinning이 적용되는 Mesh랑 
		// animaition 정보가 있는 Mesh랑 
		// 정적인 Mesh가 같을까?
		// 아닌 거 같다.
		// 상속 구조로 만들어볼까?
		//Mesh* _mesh;
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
		virtual bool Initialize(int hinst, int hWnd, int screenWidth, int screenHeight) abstract;
		virtual void Update(float deltaTime) abstract;
		virtual void BeginRender() abstract;
		virtual void Render(RendererType rendererType) abstract;
		virtual void EndRender() abstract;
		virtual void Finalize() abstract;

		/// 창 크기 변환
		virtual void SetClientSize(int width, int height) abstract;

		/// 그리기 위해 필요한 오브젝트들
		virtual void SetLight(LightInfo lightInfo) abstract;
		virtual void SetCamera(CameraInfo cameraInfo) abstract;
		virtual void SetMeshObject(MeshObjectInfo meshObjectInfo) abstract;

		// temp 
		/// IMGUI를 위해서 필요한 Device, DeviceContext 반환
		// 여기에 ID3D11Device를 써버리면 아마도 게임엔진에서
		// D3D를 include 해야할 것 같다. 그렇다고 void* 가 맞는걸까?
		virtual void* GetDevice() abstract;
		virtual void* GetDeviceContext() abstract;
	};
}