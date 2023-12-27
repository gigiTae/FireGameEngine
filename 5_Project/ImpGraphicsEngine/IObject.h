#pragma once

namespace ImpGraphics
{
	class ImpDevice;
	class ImpCamera;
	class ImpRenderTarget;
	class ImpRenderState;

	class IObject
	{
	public:
		IObject() {};
		virtual ~IObject() {};

		virtual void Update(ImpCamera* camera) abstract;
		virtual void Render(ImpDevice* device, ImpRenderState* renderState, ImpRenderTarget* rendertarget) abstract;

		virtual void SetTransformMatrix(DirectX::XMMATRIX transformMatrix) abstract;
	};
}