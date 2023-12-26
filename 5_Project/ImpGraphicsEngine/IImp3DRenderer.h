#pragma once

#define WIN32_LEAN_AND_MEAN

#include "IImpGraphicsEngine.h"

/// <summary>
/// Graphics Engine �� Game Engine���� ������ �� �� ����� h�� ���� �̾ƾ� �ڴ�. �ƴѰ� ������ ������ ����� ū �� ���⵵?
/// ���, ���� �ʿ������� �� �� ����� �غ��߰ڴ�.
/// ������ Scene ���� ������ �������� �ʿ��� ��, ���۵� �������� �ʿ��� �� �ٸ� �� �ְڴ�. 
/// �׷� �Ѵ� �����ϴ� �� �´� �����̰���?
/// </summary>
namespace ImpGraphics
{
	/// <summary>
	/// ������ �������̽�
	/// 
	/// �ϴ��� �� �𸣰ھ �������� I3DRenderer.h�� �����ߴ�!
	/// 
	/// 2023.12.12 kimyujin
	/// </summary>
	class IImp3DRenderer abstract
	{
	public:
		IImp3DRenderer() {};
		virtual ~IImp3DRenderer() {};

		/// ���� �⺻������ �������� ���ư��� ���� �ʿ��� �ʼ� �Լ�
		// ���� ���۵�� ������� �ʾҴ�. 
		virtual bool Initialize(int hinst, int hWnd, int screenWidth, int screenHeight) abstract;
		virtual void Update(float deltaTime) abstract;
		virtual void BeginRender() abstract; // ���� �������� BeginRender, Render, EndRender �� �����ؼ� ȣ���ؾ� �� ������ ������?
		virtual void Render() abstract;
		virtual void EndRender() abstract;
		virtual void Finalize() abstract;

		// â ��ȯ ����
		virtual void SetClientSize(int width, int height) abstract;
		// ���� �־�� �ϴ� ������ �𸣰ڴ�.
		//virtual void SetWinMinMax(bool isMinimized, bool isMaxmized) abstract;

		// temp
		virtual void* GetDevice() abstract;
		virtual void* GetDeviceContext() abstract;

		virtual void SetLight(LightInfo lightInfo) abstract;
		virtual void SetCamera(CameraInfo cameraInfo) abstract;
		virtual void SetMeshObject(MeshObjectInfo meshObjectInfo) abstract;
	};
}