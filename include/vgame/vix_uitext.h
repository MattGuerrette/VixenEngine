#ifndef VIX_UITEXT_H
#define VIX_UITEXT_H

#include <vix_platform.h>
#include <vix_uicomponent.h>
#include <vix_stringutil.h>

namespace Vixen {

    class VIX_API UIText : public IUIComponent
    {
    public:
        UIText();
        UIText(std::string text);

        ~UIText();

        void VRender(ICamera2D* camera);

    private:
        std::string m_text;
    };
}

#endif
