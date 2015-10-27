#include <vix_uitext.h>
#include <vix_renderer_singleton.h>

namespace Vixen {

    UIText::UIText()
    {
        m_text = VTEXT("");
        m_font = NULL;
		m_parent = NULL;
    }

    UIText::UIText(UString text)
    {
        m_text = text;
        m_font = NULL;
		m_parent = NULL;
    }

    UIText::~UIText()
    {

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
	}

    void UIText::VRender(ICamera2D* camera)
    {
        if(m_font && m_parent)
            Renderer::Render2DText(m_font, 
                                   m_text, 
                                   Vector2(m_parent->GetTransform()->X(),
										   m_parent->GetTransform()->Y()));
    }

	void UIText::VSetType(IComponent::Type type)
	{
		m_type = type;
	}

	IComponent::Type UIText::VGetType()
	{
		return m_type;
	}
}
