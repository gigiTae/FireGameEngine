#pragma once

#include <d3d11.h> // dx11 종속적인 tool

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
	/// 초기화 함수
	/// </summary>
	virtual void Initialize(HWND hWnd, ID3D11Device* device, ID3D11DeviceContext* deviceContext) abstract;
	
	/// <summary>
	/// 종료 함수
	/// </summary>
	virtual void Finalize() abstract;

	/// <summary>
	/// World 데이터를 불러온다  
	/// </summary>
	virtual void Load(class Fire::ECS::World* world) abstract;

	/// <summary>
	/// 새로운 프레임 갱신
	/// </summary>
	virtual void NewFrame() abstract;

	/// <summary>
	/// 랜더링 종료
	/// </summary>
	virtual void EndRender() abstract;
};

}