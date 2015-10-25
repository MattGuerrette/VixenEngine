#include <vix_renderer_singleton.h>

#ifdef VIX_SYS_WINDOWS
#include <vix_dxrenderer.h>
#else

#endif

namespace Vixen {

    bool Renderer::Initialize(void* HWND, IRenderer::RendererType type)
    {
        Renderer& _renderer = Renderer::instance();

#ifdef VIX_SYS_WINDOWS
        _renderer.m_renderer = new DXRenderer;
        _renderer.m_renderer->VAttachNativeHandle(HWND);
#endif

        if (!_renderer.m_renderer->VInitialize())
            return false;
    }

    void Renderer::DeInitialize()
    {
        Renderer& _renderer = Renderer::instance();

        delete _renderer.m_renderer;
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

}