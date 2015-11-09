#include <vix_renderer_singleton.h>

#ifdef VIX_SYS_WINDOWS
#include <vix_dxrenderer.h>
#else

#endif

namespace Vixen {

    bool Renderer::Initialize(void* HWND)
    {
        Renderer& _renderer = Renderer::instance();

#ifdef VIX_SYS_WINDOWS
        _renderer.m_renderer = new DXRenderer;
        _renderer.m_renderer->VAttachNativeHandle(HWND);
#endif

        if (!_renderer.m_renderer->VInitialize())
            return false;
    }

    void Renderer::InitializeSpriteBatch()
    {
        Renderer& _renderer = Renderer::instance();


        _renderer.m_renderer->VInitializeSpriteBatch();
    }

    void Renderer::DeInitialize()
    {
        Renderer& _renderer = Renderer::instance();

        _renderer.m_renderer->VDeInitialize();
    }

    void Renderer::ClearBuffer(ClearArgs args)
    {
        Renderer& _renderer = Renderer::instance();

        _renderer.m_renderer->VClearBuffer(args);
    }

    void Renderer::SetClearColor(const Color& c)
    {
        Renderer& _renderer = Renderer::instance();

        _renderer.m_renderer->VSetClearColor(c);
    }

    void Renderer::SwapBuffers()
    {
        Renderer& _renderer = Renderer::instance();

        _renderer.m_renderer->VSwapBuffers();
    }

    void Renderer::Render2DText(Font* font, UString text, const Vector2& position)
    {
        Renderer& _renderer = Renderer::instance();

        _renderer.m_renderer->VRenderText2D(font, text, position);
    }

    void Renderer::ResizeBuffers(uint32_t width, uint32_t height)
    {
        Renderer& _renderer = Renderer::instance();

        _renderer.m_renderer->VResizeBuffers(width, height);
    }

    IRenderer* Renderer::Handle()
    {
        Renderer& _renderer = Renderer::instance();

        return _renderer.m_renderer;
    }

	ICamera2D* Renderer::Camera2D()
	{
		Renderer& _renderer = Renderer::instance();

		return _renderer.m_renderer->VCamera2D();
	}

}