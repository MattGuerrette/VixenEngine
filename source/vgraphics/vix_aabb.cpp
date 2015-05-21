#include <vix_aabb.h>
#include <vix_model.h>

namespace Vixen {

	AABB::AABB(Model* parent)
	{
		m_parent = parent;
		m_min = parent->GetMin();
		m_max = parent->GetMax();
		m_centroid = parent->GetCenter();
		UpdateTransformed();
		m_box = new PrimitiveCube;
	}
	
	AABB::AABB(const Vec3& centroid, const Vec3& halfSize)
	{
		m_parent = NULL;
		m_centroid = centroid;
		m_min = centroid - halfSize;
		m_max = centroid + halfSize;
		m_box = new PrimitiveCube;
		UpdateTransformed();
	}

	AABB::~AABB()
	{
		delete m_box;
	}

	const Vec3& AABB::Max() const
	{
		return m_max;
	}

	const Vec3& AABB::Min() const
	{
		return m_min;
	}

	const Vec3& AABB::Centroid() const
	{
		return m_centroid;
	}

	Vec3 AABB::TransformedCentroid()
	{
		return static_cast<Vec3>(m_parent->GetWorldMatrix() * Vec4(m_centroid, 1.0f));
	}

	std::vector<Vec3> AABB::TransformedCorners()
	{
		std::vector<Vec3> verts;
		//Get the 8 vertices that compose the AABB
		Vec3 v3Vertex[8];
		Vec3 min = m_min;
		Vec3 max = m_max;
		v3Vertex[0] = Vec3(min.x, min.y, min.z);
		v3Vertex[1] = Vec3(max.x, min.y, min.z);
		v3Vertex[2] = Vec3(max.x, max.y, min.z);
		v3Vertex[3] = Vec3(min.x, max.y, min.z);

		v3Vertex[4] = Vec3(min.x, min.y, max.z);
		v3Vertex[5] = Vec3(max.x, min.y, max.z);
		v3Vertex[6] = Vec3(max.x, max.y, max.z);
		v3Vertex[7] = Vec3(min.x, max.y, max.z);

		//Get those vertices in global space
		for(int nVertex = 0; nVertex < 8; nVertex++)
		{
			verts.push_back(v3Vertex[nVertex]);
		}

		return verts;
	}

	const Vec3& AABB::Size() const
	{
		return m_size;
	}
	
	const Mat4& AABB::World() const
	{
		return m_parent->GetWorldMatrix();
	}
	
	void AABB::UpdateTransformed()
	{
		//We need to recalculate the centroid and size and min and max,
		//based on the transformed model. To do this, we need the vertices of the model again

		//Get the 8 vertices that compose the AABB
		Vec3 v3Vertex[8];
		Vec3 min = (m_parent !=  NULL) ? m_parent->GetMin() : m_min;
		Vec3 max = (m_parent != NULL) ? m_parent->GetMax() : m_max;
		v3Vertex[0] = Vec3(min.x, min.y, min.z);
		v3Vertex[1] = Vec3(max.x, min.y, min.z);
		v3Vertex[2] = Vec3(max.x, max.y, min.z);
		v3Vertex[3] = Vec3(min.x, max.y, min.z);

		v3Vertex[4] = Vec3(min.x, min.y, max.z);
		v3Vertex[5] = Vec3(max.x, min.y, max.z);
		v3Vertex[6] = Vec3(max.x, max.y, max.z);
		v3Vertex[7] = Vec3(min.x, max.y, max.z);

		if(m_parent) {
			//Get those vertices in global space
			for(int nVertex = 0; nVertex < 8; nVertex++)
			{
				v3Vertex[nVertex] = static_cast<Vec3>(m_parent->GetWorldMatrix() * Vec4(v3Vertex[nVertex], 1));
			}
		}

		m_min = m_max = v3Vertex[0];
		for(int nVertex = 1; nVertex < 8; nVertex++)
		{
			if(v3Vertex[nVertex].x > m_max.x)
				m_max.x = v3Vertex[nVertex].x;
			else if(v3Vertex[nVertex].x < m_min.x)
				m_min.x = v3Vertex[nVertex].x;

			if(v3Vertex[nVertex].y > m_max.y)
				m_max.y = v3Vertex[nVertex].y;
			else if(v3Vertex[nVertex].y < m_min.y)
				m_min.y = v3Vertex[nVertex].y;
		
			if(v3Vertex[nVertex].z > m_max.z)
				m_max.z = v3Vertex[nVertex].z;
			else if(v3Vertex[nVertex].z < m_min.z)
				m_min.z = v3Vertex[nVertex].z;
		}
		//m_centroid = (m_max + m_min) * 0.5f;
		m_size = m_max - m_min;
	}

	void AABB::Update()
	{
		if(m_parent) {
			m_position = m_parent->GetPosition();
			UpdateTransformed();

			Vec3 centroidG = static_cast<Vec3>(m_parent->GetWorldMatrix() * Vec4(m_centroid, 1.0f));
			m_world = 
			glm::translate(Mat4(1.0f), centroidG) *
			glm::scale(Mat4(1.0f), m_size * .5f);
			m_box->SetWorldMatrix(m_world);
		}
		else {
			Vec3 centroidG = m_centroid; //assumed to be in world
			m_world = 
				glm::translate(Mat4(1.0f), centroidG) *
				glm::scale(Mat4(1.0f), m_size * .5f);
			m_box->SetWorldMatrix(m_world);
		}
			
		
	}

	void AABB::Render(GLCamera3D* camera)
	{
		m_box->SetColor(m_highlight);
		m_box->Render(camera);
	}

	void AABB::SetHighlight(const Color& color)
	{
		m_highlight = color;
	}


	bool AABB::CheckCollision(AABB* a, AABB* b)
	{
		bool colliding = true;
		Vec3 aMin = a->Min();
		Vec3 aMax = a->Max();
		Vec3 bMin = b->Min();
		Vec3 bMax = b->Max();
		
		a->SetHighlight(Colors::LimeGreen);
		b->SetHighlight(Colors::LimeGreen);
		if(aMax.x < bMin.x || aMin.x > bMax.x)
			colliding = false;
		else if(aMax.y < bMin.y || aMin.y > bMax.y)
			colliding = false;
		else if(aMax.z < bMin.z || aMin.z > bMax.z)
			colliding = false;

		if(colliding) {
			a->SetHighlight(Colors::Yellow);
			b->SetHighlight(Colors::Yellow);
		}

		return colliding;
	}
}