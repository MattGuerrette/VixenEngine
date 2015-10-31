#ifndef VIX_SHADERVARIABLE_H
#define VIX_SHADERVARIABLE_H

#include <vix_platform.h>
#include <vix_shader.h>
#include <vix_math.h>
#include <vix_texture.h>

namespace Vixen {

	class VIX_API IShaderVariable
	{
	public:
		virtual ~IShaderVariable() { };

		virtual void VBind(std::string name, IShader* shader) = 0;
	};

	class VIX_API FloatVariable : public IShaderVariable
	{
	public:
		FloatVariable(float val);

		void VBind(std::string name, IShader* shader);

	private:
		float m_val;
	};

	class VIX_API Float4Variable : public IShaderVariable
	{
	public:
		Float4Variable(float x, float y, float z, float w);

		void VBind(std::string name, IShader* shader);

	private:
		float m_x;
		float m_y;
		float m_z;
		float m_w;
	};

	class VIX_API IntVariable : public IShaderVariable
	{
	public:
		IntVariable(int val);

		void VBind(std::string name, IShader* shader);
		
	private:
		int m_val;
	};

	class VIX_API Matrix4FloatVariable : public IShaderVariable
	{
	public:
		Matrix4FloatVariable(const float val[16]);

		void VBind(std::string name, IShader* shader);

	private:
		float m_val[16];
	};

	class VIX_API TextureVariable : public IShaderVariable
	{
	public:
		TextureVariable(ITexture* texture);

		void VBind(std::string name, IShader* shader);

	private:
		ITexture* m_texture;
	};

}

#endif