/**
**	Vixen Engine
**	Copyright(c) 2015 Matt Guerrette
**
**	GNU Lesser General Public License
**	This file may be used under the terms of the GNU Lesser
**  General Public License version 3 as published by the Free
**  Software Foundation and appearing in the file LICENSE.LGPLv3 included
**  in the packaging of this file. Please review the following information
**  to ensure the GNU Lesser General Public License requirements
**  will be met: https://www.gnu.org/licenses/lgpl.html
**
**/

#ifndef VIX_UITEXT_H
#define VIX_UITEXT_H

#include "vix_platform.h"
#include "vix_component.h"
#include "vix_rendercomponent2D.h"
#include "vix_stringutil.h"

namespace Vixen {

    class GameObject;

    class VIX_API UIText : public IRenderComponent2D, public Component
    {
    public:
        UIText();
        UIText(UString text);
        UIText(UString text, Font* font);

        ~UIText();

		void VOnInit();
		void VOnEnable();
		void VUpdate();
		void VOnDisable();
		void VOnDestroy();
        void VRender(ICamera2D* camera, Viewport v);
		void VBindParent(GameObject* parent);

        std::string GetText();
        UString     GetTextW();
        void        SetText(std::string text);

        Font*       GetFont();

    private:
        UString     m_text;
        Font*       m_font;
		GameObject* m_parent;
    };
}

#endif
