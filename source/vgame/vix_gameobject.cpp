#include <vix_gameobject.h>
#include <vix_vector2.h>
#include <vix_rectangle.h>

namespace Vixen {

	GameObject::GameObject(void)
	{
		m_texture = nullptr;
		m_position = Vector2(0,0);
		m_origin = Vector2(0,0);
		m_rotation = 0.0f;
		m_bounds = Rect(0,0,0,0);
		m_alpha = 1.0f;
	}

	void GameObject::Update(float dt)
	{

	}

	void GameObject::Render(GLRenderer* renderer, float dt)
	{
		if(m_texture)
			renderer->Render2DTexture((GLTexture*)m_texture, m_position,
			Rect(0,0,0,0), m_origin, Vector2(1,1), m_rotation, m_alpha, Colors::White, 0.0f);
	}

	/*SETTERS*/

	void GameObject::SetID(UString id)
	{
		m_id = id;
	}

	void GameObject::SetTexture(Texture* texture)
	{
		m_texture = texture;
		m_bounds = Rect(m_position.x, m_position.y, 32, 32);
	}

	void GameObject::SetPosition(Vector2 position)
	{
		m_position = position;
		m_bounds.x = m_position.x;
		m_bounds.y = m_position.y;
	}

	void GameObject::SetOrigin(Vector2 origin)
	{
		m_origin = origin;
	}

	void GameObject::SetRotation(float rotation)
	{
		m_rotation = rotation;
	}
	
	/*GETTERS*/

	const UString& GameObject::GetID() const
	{
		return m_id;
	}

	const Texture* GameObject::GetTexture() const
	{
		return m_texture;
	}

	const Vector2& GameObject::GetPosition() const
	{
		return m_position;
	}

	const Vector2& GameObject::GetOrigin() const
	{
		return m_origin;
	}

	const float GameObject::GetRotation() const
	{
		return m_rotation;
	}

	const Rect& GameObject::GetBounds()
	{
		return m_bounds;
	}


	void GameObject::Serialize(XMLDOC& doc)
	{
		using namespace tinyxml2;

#ifdef VIX_SYS_WINDOWS
		UConverter cv;
		std::string id = cv.to_bytes(m_id);
#else
		UString id = m_id;
#endif
		XMLElement* root = doc.RootElement();
		XMLElement* element = doc.NewElement("gameobject");
		element->SetAttribute("id", id.c_str());
	
		root->InsertEndChild(element);
	}

	void GameObject::Deserialize(XMLDOC& doc)
	{

	}
}