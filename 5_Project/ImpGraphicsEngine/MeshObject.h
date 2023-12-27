#pragma once
#include "IObject.h"
#include <memory>

namespace ImpGraphics
{
	class VBIB;
	class Shader;

	class MeshObject : public IObject
	{
	public:
		MeshObject(std::shared_ptr<VBIB> vbib, std::shared_ptr<Shader> shader);
		MeshObject(std::shared_ptr<VBIB> vbib, std::shared_ptr<Shader> shader, std::shared_ptr<Shader> shader2);
		virtual ~MeshObject();

		virtual void Update(ImpCamera* camera) override;
		virtual void Render(ImpDevice* device, ImpRenderState* renderState, ImpRenderTarget* rendertarget) override;

		virtual void SetTransformMatrix(DirectX::XMMATRIX transformMatrix) override;

	private:
		std::shared_ptr<VBIB> _VBIB;
		std::shared_ptr<Shader> _shader;
		std::shared_ptr<Shader> _shader2;

		DirectX::XMFLOAT4X4 _worldTM;
		DirectX::XMFLOAT4X4 _viewTM;
		DirectX::XMFLOAT4X4 _projTM;
	};
}