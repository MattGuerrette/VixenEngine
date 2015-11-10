#ifndef VIX_RENDERER_SINGLETON_H
#define VIX_RENDERER_SINGLETON_H

#include <vix_platform.h>
#include <vix_singleton.h>
#include <vix_renderer.h>

namespace Vixen {

    class VIX_API Renderer : public Singleton<Renderer>
    {
    public:
        static bool		    Initialize(void* HWND);

        static void		    DeInitialize();

        static void         InitializeSpriteBatch();

        static void         SetClearColor(const Color& c);

        static void         ClearBuffer(ClearArgs args);

        static void         SwapBuffers();

        static void         Render2DText(Font* font, UString text, const Vector2& position);

        static void         ResizeBuffers(uint32_t width, uint32_t height);

        static IRenderer*   Handle();

		static ICamera2D*   Camera2D();
    private:
        IRenderer*  m_renderer;
    };

}

#endif