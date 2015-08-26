#ifndef VIX_GAMEOBJECT_H
#define VIX_GAMEOBJECT_H

#include <vix_platform.h>
#include <vix_texture.h>
#include <vix_glrenderer.h>

namespace Vixen {
	

	class VIX_API GameObject
	{
	public:
		GameObject();


		/*SETTERS*/
		void SetID(UString id);
		void SetTexture(Texture* texture);
		void SetPosition(Vector2 position);
		void SetOrigin(Vector2 origin);
		void SetRotation(float rotation);
		void SetBounds(Rect bounds);

		/*GETTERS*/
		const UString&  GetID() const;
		const Texture*	GetTexture()  const;
		const Vector2&	GetPosition() const;
		const Vector2&	GetOrigin()   const;
		const float		GetRotation() const;
		const Rect&		GetBounds();

		void Update(float dt);
		void Render(GLRenderer* renderer, float dt);


		/*Writes GameObject to XML document file*/
		void Serialize(XMLDOC& doc);

		/*Reads GameObject from XML document file*/
		void Deserialize(XMLDOC& doc);

	private:
		UString         m_id;
		Texture*		m_texture;
		Vector2         m_position;
		Vector2         m_origin;
		float           m_rotation;
		float           m_alpha;
		Rect            m_bounds;
	};
}

#endif