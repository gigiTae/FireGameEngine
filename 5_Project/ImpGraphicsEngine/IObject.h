#pragma once

namespace ImpGraphics
{
	class ImpDevice;
	class ImpCamera;
	class ImpRenderState;

	class IObject
	{
	public:
		IObject() {};
		virtual ~IObject() {};

		virtual void Update(ImpCamera* camera) abstract;
		virtual void Render(ImpDevice* device, ImpRenderState* renderState) abstract;
	};
}