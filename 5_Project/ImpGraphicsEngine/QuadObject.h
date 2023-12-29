#pragma once
#include "IObject.h"
#include <memory>

namespace ImpGraphics
{
	class VBIB;
	class Shader;

	class QuadObject : public IObject
	{
	public:
		QuadObject(std::shared_ptr<VBIB> vbib, std::shared_ptr<Shader> shader);
		virtual ~QuadObject();

		virtual void Update(ImpCamera* camera) override;
		virtual void Render(ImpDevice* device, ImpRenderState* renderState, ImpRenderTarget* rendertarget) override;

		virtual void SetTransformMatrix(DirectX::XMMATRIX transformMatrix) override;

	private:
		std::shared_ptr<VBIB> _VBIB;
		std::shared_ptr<Shader> _shader;
	};
}