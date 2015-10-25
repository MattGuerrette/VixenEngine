#include <vix_uitext.h>

namespace Vixen {

    UIText::UIText()
    {
        m_text = "";
    }

    UIText::UIText(std::string text)
    {
        m_text = text;
    }

    UIText::~UIText()
    {

    }

    void UIText::VRender(ICamera2D* camera)
    {

    }
}