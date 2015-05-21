#include <vix_model.h>
#include <vix_debugutil.h>
#include <thread>

namespace Vixen {

	Model::Model()
	{
		m_initialized = false;
		m_position = Vec3(0.0f, 0.0f, -5.0f);
		m_scale = Vec3(1.0f);
		m_aabb = new AABB(this);
		m_obb = new OBB(this);
		init_shader_program();
	}

	void Model::SetPosition(const Vec3& position)
	{
		m_position = position;
	}

	void Model::SetScale(const Vec3& scale)
	{
		m_scale = scale;
	}

	void Model::SetRotation(Vec3 rot)
	{
		m_rotation = rot;
	}

	void Model::SetSize(const Vec3& size)
	{
		m_size = size;
	}

	void Model::SetCenter(const Vec3& center)
	{
		m_centroid = center;
	}

	void Model::SetMax(const Vec3& max)
	{
		m_max = max;
	}

	void Model::SetMin(const Vec3& min)
	{
		m_min = min;
	}

	void Model::SetTexture(GLTexture* tex)
	{
		m_texture = tex;
	}

	void Model::SetInitialized(bool initialized)
	{
		m_initialized = initialized;
	}

	AABB* Model::GetAABB()
	{
		return m_aabb;
	}

	OBB* Model::GetOBB()
	{
		return m_obb;
	}

	const Vec3& Model::GetPosition() const
	{
		return m_position;
	}

	const Vec3& Model::GetRotation() const
	{
		return m_rotation;
	}

	const Vec3& Model::GetCenter() const
	{
		return m_centroid;
	}

	Mat4& Model::GetWorldMatrix()
	{
		return m_world;
	}

	bool Model::IsInitialized()
	{
		return m_initialized;
	}

	void Model::RotateX(float dt)
	{
		m_rotation.x += dt * 50.0f;
	}

	void Model::RotateY(float dt)
	{
		m_rotation.y += dt * 50.0f;
	}

	void Model::RotateZ(float dt)
	{
		m_rotation.z += dt * 50.0f;
	}

	void Model::MoveX(float dt)
	{
		m_position.x += dt * 5.0f;
	}

	void Model::MoveY(float dt)
	{
		m_position.y += dt * 5.0f;
	}

	void Model::MoveZ(float dt)
	{
		m_position.z += dt * 5.0f;
	}

	void Model::Update(float dt)
	{
		m_aabb->Update();
		m_obb->Update();
	}

	Vec3 Model::GetTransformedCenter() const
	{
		Vec3 trans_center = m_centroid;
		return static_cast<Vec3>(m_world * Vec4(trans_center, 1.0f));
	}

	const Vec3& Model::GetMin() const
	{
		return m_min;
	}

	const Vec3& Model::GetMax() const
	{
		return m_max;
	}

	const Vec3& Model::GetSize() const
	{
		return m_size;
	}

	const Vec3& Model::GetScale() const
	{
		return m_scale;
	}

	GLShaderProgram* Model::GetShader() const
	{
		return m_program;
	}

	UString Model::GetDiffusePath()
	{
		return m_diffusePath;
	}

	UString Model::GetBumpPath()
	{
		return m_bumpPath;
	}

	void Model::SetDiffusePath(UString path)
	{
		m_diffusePath = path;
	}

	void Model::SetBumpPath(UString path)
	{
		m_bumpPath = path;
	}

	Model::VertexCollection Model::GetVertices()
	{
		VertexCollection vertices = m_meshes[0]->GetInfo()->Vertices;

		return vertices;
	}

	void Model::Render(GLCamera3D* camera)
	{
		size_t numMeshes = m_meshes.size();
		for(size_t i = 0; i < numMeshes; i++)
		{
			Mesh* mesh = m_meshes[i];
			mesh->Render(camera);
		}
	}

	void Model::init_shader_program()
	{
		/*vertex shader info*/
		ShaderInfo vshader_info;
		vshader_info.filePath = VTEXT("Model.vs");
		vshader_info.raw = VTEXT("");
		vshader_info.type = ShaderType::VERTEX_SHADER;

		/*fragment shader info*/
		ShaderInfo fshader_info;
		fshader_info.filePath = VTEXT("Model.fs");
		fshader_info.raw = VTEXT("");
		fshader_info.type = ShaderType::FRAGMENT_SHADER;

		/*populate shader args*/
		ShaderArgs args;
		args[0] = vshader_info;
		args[1] = fshader_info;

		/*create shader program*/
		m_program = new GLShaderProgram(args);
	}

	void Model::InitFromFile(UString filePath, ModelInit initMode)
	{
		if(initMode == ModelInit::THREADED) {

			//try initializing in dedicated thread
			auto func = [](Model* model, UString filePath) {
				model->SetTexture(new GLTexture);
				Model::InitModelThreaded(model, filePath);
			};
			std::thread t(func, this, filePath);
			t.detach();
		}
		else
			init_model(filePath); //init unthreaded
	}

	void Model::InitModelThreaded(Model* model, UString filePath)
	{
		std::string _path;
#if defined(VIX_SYS_WINDOWS) && defined(UNICODE)
		UConverter cv;
		_path = cv.to_bytes(filePath);
#else
		_path = filePath;
#endif

		Assimp::Importer imp;
		const aiScene* scene = imp.ReadFile(_path,
											aiProcess_CalcTangentSpace |
											aiProcess_Triangulate |
											aiProcess_JoinIdenticalVertices |
											aiProcess_SortByPType |
											aiProcess_GenUVCoords);
		if(!scene) {
			DebugPrintF(VTEXT("ASSIMP: Error could not read file [%s]"), _path);
			return;
		}

		size_t numMeshes = scene->mNumMeshes;
		aiString diffuse;
		aiString bump;
		for(size_t i = 0; i < numMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[i];
			size_t matIndex = mesh->mMaterialIndex;
			aiMaterial* mat = scene->mMaterials[matIndex];
			aiGetMaterialTexture(mat, aiTextureType_DIFFUSE, 0, &diffuse); 
			aiGetMaterialTexture(mat, aiTextureType_HEIGHT, 0, &bump);
			aiColor4D color;
			aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &color);
			printf("MATCOLOR [%f, %f, %f, %f]\n", color.r, color.g, color.b, color.a); 
			printf("MATTEXT [DIFFUSE: %s]\n", diffuse.data);
			printf("MATTEXT [BUMP: %s]\n", bump.data);

			/*INIT MODEL CENTROID, SIZE, MIN, AND MAX*/
			/*USED FOR COLLIDER*/
			aiVector3D min, max, center;
			FindMeshCenter(mesh, center, min, max);
			model->SetMin(Vec3(min.x, min.y, min.z));
			model->SetMax(Vec3(max.x, max.y, max.z));
			aiVector3D size = max - min;
			model->SetSize(Vec3(size.x, size.y, size.z));
			model->SetCenter(Vec3(center.x, center.y, center.z));

			model->InitMesh(mesh);
		}

		if(diffuse.C_Str()) {
			UString texPath = cv.from_bytes(diffuse.data);
			model->GetTexture()->InitFromFile(texPath);
		}

		/*if(bump.C_Str()) {
			UString texPath = cv.from_bytes(bump.data);
			m_bump = new GLTexture(texPath);
		}*/

		model->SetInitialized(true);
		
	}

	void Model::init_model(UString filePath)
	{
		std::string _path;
#if defined(VIX_SYS_WINDOWS) && defined(UNICODE)
		UConverter cv;
		_path = cv.to_bytes(filePath);
#else
		_path = filePath;
#endif

		Assimp::Importer imp;
		const aiScene* scene = imp.ReadFile(_path,
											aiProcess_CalcTangentSpace |
											aiProcess_Triangulate |
											aiProcess_JoinIdenticalVertices |
											aiProcess_SortByPType |
											aiProcess_GenUVCoords);
		if(!scene) {
			DebugPrintF(VTEXT("ASSIMP: Error could not read file [%s]"), _path);
			return;
		}

		size_t numMeshes = scene->mNumMeshes;
		aiString diffuse;
		aiString bump;
		for(size_t i = 0; i < numMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[i];
			size_t matIndex = mesh->mMaterialIndex;
			aiMaterial* mat = scene->mMaterials[matIndex];
			aiGetMaterialTexture(mat, aiTextureType_DIFFUSE, 0, &diffuse); 
			aiGetMaterialTexture(mat, aiTextureType_HEIGHT, 0, &bump);
			aiColor4D color;
			aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &color);
			printf("MATCOLOR [%f, %f, %f, %f]\n", color.r, color.g, color.b, color.a); 
			printf("MATTEXT [DIFFUSE: %s]\n", diffuse.data);
			printf("MATTEXT [BUMP: %s]\n", bump.data);

			/*INIT MODEL CENTROID, SIZE, MIN, AND MAX*/
			/*USED FOR COLLIDER*/
			aiVector3D min, max, center;
			FindMeshCenter(mesh, center, min, max);
			m_min = Vec3(min.x, min.y, min.z);
			m_max = Vec3(max.x, max.y, max.z);
			m_size = m_max - m_min;
			m_centroid = Vec3(center.x, center.y, center.z);

			InitMesh(mesh);
		}

		if(diffuse.C_Str()) {
			UString texPath = cv.from_bytes(diffuse.data);
			m_texture = new GLTexture(texPath);
		}

		if(bump.C_Str()) {
			UString texPath = cv.from_bytes(bump.data);
			m_bump = new GLTexture(texPath);
		}

		
		m_initialized = true;
	}

	GLTexture* Model::GetTexture() const
	{
		return m_texture;
	}

	GLTexture* Model::GetBump() const
	{
		return  m_bump;
	}

	void Model::InitMesh(const aiMesh* mesh)
	{
		MeshInfo* meshInfo = new MeshInfo;
		meshInfo->NumVertices = mesh->mNumVertices;
		meshInfo->NumIndices  = mesh->mNumFaces * 3;
		Mesh* modelMesh = new Mesh(this, meshInfo);

		/*READ VERTS INTO MODEL MESH*/
		size_t numVerts = mesh->mNumVertices;
		for(size_t i = 0; i < numVerts; i++)
		{
			aiVector3D vertex = mesh->mVertices[i];
			aiVector3D tangent = aiVector3D(0.0f);
			if(mesh->HasTangentsAndBitangents()) {
				tangent = mesh->mTangents[i];
			}
			aiVector3D normal(0.0f);
			float u = 0.0f;
			float v = 0.0f;
			if(mesh->HasNormals()) {
				normal = mesh->mNormals[i];
			}
			if(mesh->HasTextureCoords(0)) {
				aiVector3D uvs = mesh->mTextureCoords[0][i];
				u = uvs.x;
				v = uvs.y;
			}
			meshInfo->Vertices.push_back(Vec3(vertex.x, vertex.y, vertex.z));
			modelMesh->AddVertex(vertex.x, vertex.y, vertex.z,
							     normal.x, normal.y, normal.z,
								 u, v,
								 tangent.x, tangent.y, tangent.z);
		}

		/*READ FACES INTO MODEL MESH*/
		size_t numFaces = mesh->mNumFaces;
		for(size_t i = 0; i < numFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			modelMesh->AddFace(face.mIndices[0],
							   face.mIndices[1],
							   face.mIndices[2]);
		}

		/*INITIALIZE MESH*/
		modelMesh->Init();

		/*ADD MODELMESH TO COLLECTION*/
		m_meshes.push_back(modelMesh);

	}
}