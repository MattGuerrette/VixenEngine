#ifndef VIX_DXLIGHTBUFFER_H
#define VIX_DXLIGHTBUFFER_H

#include <vix_platform.h>
#include <vix_directx.h>
#include <vix_lightbuffer.h>
#include <vix_light.h>

namespace Vixen {

	class VIX_API DXLightBuffer : public LightBuffer
	{
	public:
		DXLightBuffer(size_t count, size_t size, ID3D11Device* device, ID3D11DeviceContext* context);

		~DXLightBuffer();

		void VSetData(const void* data);
		void VUpdateSubData(size_t offset, size_t stride, size_t count, const void* data);
		void VBind();
		void VUnbind();

		ID3D11ShaderResourceView* GetSRV();

	private:
		ID3D11Device*          m_device;
		ID3D11DeviceContext*   m_context;
		ID3D11Buffer*          m_buffer;
		size_t				   m_size;

		ID3D11ShaderResourceView* m_srv;
	};
	
}

#endif