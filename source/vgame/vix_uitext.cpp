#include <vix_uitext.h>
#include <vix_renderer_singleton.h>

namespace Vixen {

    UIText::UIText()
    {
        m_text = VTEXT("");
        m_font = NULL;
        m_position = Vector2(0, 0);
    }

    UIText::UIText(UString text)
    {
        m_text = text;
        m_font = NULL;
        m_position = Vector2(0, 0);
    }

    UIText::~UIText()
    {

    }

    void UIText::VRender(ICamera2D* camera)
    {
        if(m_font)
            Renderer::Render2DText(m_font, 
                                   m_text, 
                                   m_position);
    }
}