#ifndef VIX_MODEL_H
#define VIX_MODEL_H

#include <vix_platform.h>
#include <vix_mesh.h>
#include <vix_glm.h>
#include <vix_glcamera3d.h>
#include <vix_glshaderprogram.h>
#include <vix_gltexture.h>
#include <vix_aabb.h>
#include <vix_obb.h>
#include <vector>

namespace Vixen {

	enum class ModelInit
	{
		THREADED,
		UNTHREADED
	};


	/**
	*
	*	class Model
	*
	*   Represents a Model consisting of potentially many
	*   Mesh objects, and the corresponding Animation, Texture,
	*   and Material data.
	*
	*/
	class VIX_API Model
	{
		typedef std::vector<Mesh*> MeshCollection;
		typedef std::vector<Vec3>  VertexCollection;

	public:
		Model();


		void RotateX(float dt);
		void RotateY(float dt);
		void RotateZ(float dt);
		void MoveX(float dt);
		void MoveY(float dt);
		void MoveZ(float dt);
		void Update(float dt);

		/*SETTERS*/
		void SetPosition(const Vec3& position);
		void SetScale(const Vec3& scale);
		void SetMin(const Vec3& min);
		void SetMax(const Vec3& max);
		void SetSize(const Vec3& size);
		void SetCenter(const Vec3& center);
		void SetTexture(GLTexture* tex);
		void SetInitialized(bool initialized);
		void SetDiffusePath(UString path);
		void SetBumpPath(UString path);
		void SetRotation(Vec3 rot);

		/*GETTERS*/
		AABB*         GetAABB();
		OBB*          GetOBB();
		const Vec3&		    GetPosition() const;
		const Vec3&         GetRotation() const;
		const Vec3&         GetCenter() const;
		Vec3				GetTransformedCenter() const;
		const Vec3&         GetMin() const;
		const Vec3&         GetMax() const;
		const Vec3&         GetSize() const;
		const Vec3&         GetScale() const;
		Mat4&               GetWorldMatrix();
		GLShaderProgram*	GetShader() const;
		GLTexture*		    GetTexture() const;
		GLTexture*          GetBump() const;
		VertexCollection    GetVertices();
		UString             GetDiffusePath();
		UString             GetBumpPath();
		bool                IsInitialized();

		/*Render Model*/
		void Render(GLCamera3D* camera);

		void InitFromFile(UString filePath, ModelInit initMode = ModelInit::UNTHREADED);
		void InitMesh(const aiMesh* mesh);


	private:
		void init_shader_program();
		void init_model(UString filePath);
		static void InitModelThreaded(Model* model, UString filePath);

	private:
		AABB*               m_aabb;
		OBB*                m_obb;
		MeshCollection		m_meshes;
		Mat4				m_world;
		Vec3				m_position;
		Vec3                m_rotation;
		Vec3				m_scale;
		Vec3                m_min;
		Vec3                m_max;
		Vec3                m_size;
		Vec3                m_centroid;
		GLShaderProgram*	m_program;
		UString             m_diffusePath;
		UString             m_bumpPath;
		GLTexture*          m_texture;
		GLTexture*          m_bump;
		bool				m_initialized;
	};

}

#endif