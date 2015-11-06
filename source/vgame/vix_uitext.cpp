#include <vix_uitext.h>
#include <vix_renderer_singleton.h>

namespace Vixen {

    UIText::UIText() : Component(Type::UI_TEXT)
    {
        m_text = VTEXT("");
        m_font = NULL;
		m_parent = NULL;
    }

    UIText::UIText(UString text) : Component(Type::UI_TEXT)
    {
        m_text = text;
        m_font = NULL;
		m_parent = NULL;
    }

    UIText::UIText(UString text, IFont* font) : Component(Type::UI_TEXT)
    {
        m_text = text;
        m_font = font;
        m_parent = NULL;
    }

    UIText::~UIText()
    {
        delete m_font;
    }

    void UIText::SetText(std::string text)
    {
        m_text = UStringFromCharArray(text.c_str());
    }

    std::string UIText::GetText()
    {
        return UStringToStd(m_text);
    }

	void UIText::VOnInit()
	{

	}

	void UIText::VOnEnable()
	{

	}
	
	void UIText::VUpdate()
	{

	}

	void UIText::VOnDisable()
	{

	}

	void UIText::VOnDestroy()
	{

	}

	void UIText::VBindParent(GameObject* parent)
	{
		m_parent = parent;
        m_parent->MarkForLateRender();
	}

    void UIText::VRender(ICamera2D* camera)
    {
        if(m_font && m_parent)
            Renderer::Render2DText(m_font, 
                                   m_text, 
                                   Vector2(m_parent->GetTransform()->X(),
										   m_parent->GetTransform()->Y()));
    }
}
