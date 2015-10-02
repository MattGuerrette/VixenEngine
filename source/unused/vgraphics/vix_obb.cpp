#include <vix_obb.h>
#include <vix_model.h>

namespace Vixen {

	OBB::OBB(Model* parent)
	{
		m_parent = parent;
		m_centroid = m_parent->GetCenter();
		m_size = m_parent->GetSize();
		m_min = m_parent->GetMin();
		m_max = m_parent->GetMax();
		m_box = new PrimitiveCube;
		SetHighlight(Colors::Pink);
		UpdateTransformed();
	}

	OBB::~OBB()
	{
		delete m_box;
	}

	const Vec3& OBB::Max() const
	{
		return m_max;
	}

	const Vec3& OBB::Min() const
	{
		return m_min;
	}
	
	const Vec3& OBB::Centroid() const
	{
		return m_centroid;
	}

	Vec3 OBB::TransformedCentroid()
	{
		return static_cast<Vec3>(m_parent->GetWorldMatrix() * Vec4(m_centroid, 1.0f));
	}

	const Vec3& OBB::Size() const
	{
		return m_size;
	}
	
	const Mat4& OBB::World() const
	{
		return m_parent->GetWorldMatrix();
	}

	void OBB::UpdateTransformed()
	{
		if(!m_parent->IsInitialized())
			return;

		//We need to recalculate the centroid and size and min and max,
		//based on the transformed model. To do this, we need the vertices of the model again

		std::vector<Vec3> verts = m_parent->GetVertices();
		size_t numVerts = verts.size();
		Vec3 min, max, size, centroid;
		min = verts[0];
		max = verts[0];
		for(size_t i = 0; i < numVerts; i++) {
			Vec3 transformed_vert = verts[i];
			min.x = std::min(transformed_vert.x, min.x);
			min.y = std::min(transformed_vert.y, min.y);
			min.z = std::min(transformed_vert.z, min.z);

			max.x = std::max(transformed_vert.x, max.x);
			max.y = std::max(transformed_vert.y, max.y);
			max.z = std::max(transformed_vert.z, max.z);
		} //Now we have the correct min and max based off the transformed (rotated) vertices

		//Calculate the new centroid
		centroid = (min + max) * 0.5f;

		//Calculate the new size
		size = max - min;

		//copy data over
		m_centroid = centroid;
		m_size = size;
		m_min = min;
		m_max = max;
	}

	void OBB::Update()
	{
		m_position = m_parent->GetPosition();
		UpdateTransformed();
			
		m_world = m_parent->GetWorldMatrix() *
				  glm::translate(Mat4(1.0f), m_centroid) *
				  glm::scale(Mat4(1.0f), m_size * .5f);
		m_box->SetWorldMatrix(m_world);
	}

	void OBB::Render(GLCamera3D* camera)
	{
		m_box->SetColor(m_highlight);
		m_box->Render(camera);
	}

	void OBB::SetHighlight(const Color& color)
	{
		m_highlight = color;
	}


	bool OBB::CheckCollision(OBB* a, OBB* b)
	{
		
		//SEPARATING AXIS THEOREM

		a->SetHighlight(Colors::Purple);
		b->SetHighlight(Colors::Purple);

		Vec3 aCentroid = a->TransformedCentroid();
		Vec3 bCentroid = b->TransformedCentroid();
		Vec3 halfA = a->Size() * 0.5f;
		Vec3 halfB = b->Size() * 0.5f;

		float aE[3] = { halfA.x, halfA.y, halfA.z };
		float bE[3] = { halfB.x, halfB.y, halfB.z };

		//calculate local axis for each space
		Vec4 aU[3];
		aU[0] = a->World() * Vec4(1.0f, 0.0f, 0.0f, 0.0f);
		aU[1] = a->World() * Vec4(0.0f, 1.0f, 0.0f, 0.0f);
		aU[2] = a->World() * Vec4(0.0f, 0.0f, 1.0f, 0.0f);

		Vec4 bU[3];
		bU[0] = b->World() * Vec4(1.0f, 0.0f, 0.0f, 0.0f);
		bU[1] = b->World() * Vec4(0.0f, 1.0f, 0.0f, 0.0f);
		bU[2] = b->World() * Vec4(0.0f, 0.0f, 1.0f, 0.0f);


		Mat3 R;
		//calculate rotation matrix rep. b in a space
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 3; j++) {
				R[i][j] = glm::dot(aU[i], bU[j]);
			}
		}

		//compute translation vector in A's space
		Vec4 t = Vec4(bCentroid - aCentroid, 1.0f);
		t = Vec4(
			glm::dot(t, aU[0]),
			glm::dot(t, aU[1]),
			glm::dot(t, aU[2]),
			0.0f);

		//take into account rounding errors
		Mat3 AbsR;
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 3; j++) {
				AbsR[i][j] = glm::abs(R[i][j]) + FLT_EPSILON;
			}	
		}

		float radiusA, radiusB;

		bool colliding = true;

			// Test axes L = A0, L = A1, L = A2
		for (int i = 0; i < 3; i++) {
			radiusA = aE[i];
			radiusB = bE[0] * AbsR[i][0] + bE[1] * AbsR[i][1] + bE[2] * AbsR[i][2];
			if (glm::abs(t[i]) > radiusA + radiusB) colliding = false;
		}
		// Test axes L = B0, L = B1, L = B2
		for (int i = 0; i < 3; i++) {
			radiusA = aE[0] * AbsR[0][i] + aE[1] * AbsR[1][i] + aE[2] * AbsR[2][i];
			radiusB = bE[i];
			if (glm::abs(t[0] * R[0][i] + t[1] * R[1][i] + t[2] * R[2][i]) > radiusA + radiusB) colliding = false;
		}

		// Test axis L = A0 x B0
		radiusA = aE[1] * AbsR[2][0] + aE[2] * AbsR[1][0];
		radiusB = bE[1] * AbsR[0][2] + bE[2] * AbsR[0][1];
		if (abs(t[2] * R[1][0] - t[1] * R[2][0]) > radiusA + radiusB) colliding = false;

		// Test axis L = A0 x B1
		radiusA = aE[1] * AbsR[2][1] + aE[2] * AbsR[1][1];
		radiusB = bE[0] * AbsR[0][2] + bE[2] * AbsR[0][0];
		if (abs(t[2] * R[1][1] - t[1] * R[2][1]) > radiusA + radiusB) colliding = false;

		// Test axis L = A0 x B2
		radiusA = aE[1] * AbsR[2][2] + aE[2] * AbsR[1][2];
		radiusB = bE[0] * AbsR[0][1] + bE[1] * AbsR[0][0];
		if (abs(t[2] * R[1][2] - t[1] * R[2][2]) > radiusA + radiusB) colliding = false;

		// Test axis L = A1 x B0
		radiusA = aE[0] * AbsR[2][0] + aE[2] * AbsR[0][0];
		radiusB = bE[1] * AbsR[1][2] + bE[2] * AbsR[1][1];
		if (abs(t[0] * R[2][0] - t[2] * R[0][0]) > radiusA + radiusB) colliding = false;

		// Test axis L = A1 x B1
		radiusA = aE[0] * AbsR[2][1] + aE[2] * AbsR[0][1];
		radiusB = bE[0] * AbsR[1][2] + bE[2] * AbsR[1][0];
		if (abs(t[0] * R[2][1] - t[2] * R[0][1]) > radiusA + radiusB) colliding = false;

		// Test axis L = A1 x B2
		radiusA = aE[0] * AbsR[2][2] + aE[2] * AbsR[0][2];
		radiusB = bE[0] * AbsR[1][1] + bE[1] * AbsR[1][0];
		if (abs(t[0] * R[2][2] - t[2] * R[0][2]) > radiusA + radiusB) colliding = false;
		// Test axis L = A2 x B0
		radiusA = aE[0] * AbsR[1][0] + aE[1] * AbsR[0][0];
		radiusB = bE[1] * AbsR[2][2] + bE[2] * AbsR[2][1];
		if (abs(t[1] * R[0][0] - t[0] * R[1][0]) > radiusA + radiusB) colliding = false;
		// Test axis L = A2 x B1
		radiusA = aE[0] * AbsR[1][1] + aE[1] * AbsR[0][1];
		radiusB = bE[0] * AbsR[2][2] + bE[2] * AbsR[2][0];
		if (abs(t[1] * R[0][1] - t[0] * R[1][1]) > radiusA + radiusB) colliding = false;
		// Test axis L = A2 x B2
		radiusA = aE[0] * AbsR[1][2] + aE[1] * AbsR[0][2];
		radiusB = bE[0] * AbsR[2][1] + bE[1] * AbsR[2][0];
		if (abs(t[1] * R[0][2] - t[0] * R[1][2]) > radiusA + radiusB) colliding = false;

		if(colliding) {
			a->SetHighlight(Colors::Red);
			b->SetHighlight(Colors::Red);
		}

		return colliding;
	}

}