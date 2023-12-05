#pragma once

#include <d3d11.h> // dx11 �������� tool

#include "../EntityComponentSystem/World.h"

namespace ToolModule
{

/// <summary>
/// Interface ToolModule
/// </summary>
class IToolModule
{
public:
	virtual ~IToolModule(){}

	/// <summary>
	/// �ʱ�ȭ �Լ�
	/// </summary>
	virtual void Initialize(HWND hWnd, ID3D11Device* device, ID3D11DeviceContext* deviceContext) abstract;
	
	/// <summary>
	/// ���� �Լ�
	/// </summary>
	virtual void Finalize() abstract;

	/// <summary>
	/// World �����͸� �ҷ��´�  
	/// </summary>
	virtual void Load(class Fire::ECS::World* world) abstract;

	/// <summary>
	/// ���ο� ������ ����
	/// </summary>
	virtual void NewFrame() abstract;

	/// <summary>
	/// ������ ����
	/// </summary>
	virtual void EndRender() abstract;
};

}