#ifndef VIX_UITEXT_H
#define VIX_UITEXT_H

#include <vix_platform.h>
#include <vix_uicomponent.h>
#include <vix_gameobject.h>
#include <vix_stringutil.h>

namespace Vixen {

    class VIX_API UIText : public IUIComponent
    {
    public:
        UIText();
        UIText(UString text);

        ~UIText();

        void VRender(ICamera2D* camera);

    private:
        UString     m_text;
        Vector2     m_position;
        IFont*      m_font;
    };
}

#endif
