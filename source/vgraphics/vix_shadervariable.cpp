#include <vix_shadervariable.h>

namespace Vixen {

	/////////////////////////////////////////////////////////
	// Float Variable
	////////////////////////////////////////////////////////

	FloatVariable::FloatVariable(float val)
	{
		m_val = val;
	}

	FloatVariable::~FloatVariable()
	{

	}

	void FloatVariable::VBind(std::string name, IShader* shader)
	{
		if (!shader)
			return;

		shader->VSetFloat(name, m_val);
	}

	/////////////////////////////////////////////////////////
	// Float4 Variable
	////////////////////////////////////////////////////////

	Float4Variable::Float4Variable(float x, float y, float z, float w)
	{
		m_x = x;
		m_y = y;
		m_z = z;
		m_w = w;
	}

	Float4Variable::~Float4Variable()
	{

	}

	void Float4Variable::VBind(std::string name, IShader* shader)
	{
		if (!shader)
			return;

		float data[4] = { m_x, m_y, m_z, m_w };
		shader->VSetFloat4(name, data);
		
	}

	/////////////////////////////////////////////////////////
	// Int Variable
	////////////////////////////////////////////////////////

	IntVariable::IntVariable(int val)
	{
		m_val = val;
	}

	IntVariable::~IntVariable()
	{

	}

	void IntVariable::VBind(std::string name, IShader* shader)
	{
		if (!shader)
			return;

		shader->VSetInt(name, m_val);
	}

	/////////////////////////////////////////////////////////
	// Matrix4 Float Variable
	////////////////////////////////////////////////////////

	Matrix4FloatVariable::Matrix4FloatVariable(const float val[16])
	{
		for (int i = 0; i < 16; i++)
			m_val[i] = val[i];
	}

	Matrix4FloatVariable::~Matrix4FloatVariable()
	{

	}

	void Matrix4FloatVariable::VBind(std::string name, IShader* shader)
	{
		if (!shader)
			return;

		shader->VSetMatrix4x4(name, m_val);
	}

	/////////////////////////////////////////////////////////
	// Texture Variable
	////////////////////////////////////////////////////////

	TextureVariable::TextureVariable(ITexture* texture)
	{
		m_texture = texture;
	}

	TextureVariable::~TextureVariable()
	{
		delete m_texture;
	}

	void TextureVariable::VBind(std::string name, IShader* shader)
	{
		if (!shader)
			return;

		shader->VBindTexture(name, m_texture);
	}
}