
/**
**	Vixen Engine
**	Copyright(c) 2015 Matt Guerrette
**
**	GNU Lesser General Public License
**	This file may be used under the terms of the GNU Lesser
**  General Public License version 3 as published by the Free
**  Software Foundation and appearing in the file LICENSE.LGPLv3 included
**  in the packaging of this file. Please review the following information
**  to ensure the GNU Lesser General Public License requirements
**  will be met: https://www.gnu.org/licenses/lgpl.html
**
**/

#ifndef VIX_SHADERVARIABLE_H
#define VIX_SHADERVARIABLE_H

#include "vix_platform.h"
#include "vix_shader.h"
#include "vix_math.h"
#include "vix_texture.h"

namespace Vixen {

	class VIX_API IShaderVariable
	{
	public:
		virtual ~IShaderVariable() { };
		virtual void VBind(std::string name, Shader* shader) = 0;
        virtual void VUnbind(std::string name, Shader* shader) = 0;
	};

	class VIX_API FloatVariable : public IShaderVariable
	{
	public:
		FloatVariable(float val);

		~FloatVariable();

		void SetData(float val);
		void VBind(std::string name, Shader* shader);
        void VUnbind(std::string name, Shader* shader);

	private:
		float m_val;
	};

	class VIX_API Float4Variable : public IShaderVariable
	{
	public:
		Float4Variable(float x, float y, float z, float w);

		~Float4Variable();

		void SetData(float x, float y, float z, float w);
		void VBind(std::string name, Shader* shader);
        void VUnbind(std::string name, Shader* shader);

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

		~IntVariable();

		void SetData(int val);
		void VBind(std::string name, Shader* shader);
        void VUnbind(std::string name, Shader* shader);

	private:
		int m_val;
	};

	class VIX_API Matrix4FloatVariable : public IShaderVariable
	{
	public:
		Matrix4FloatVariable(const float val[16]);

		~Matrix4FloatVariable();

		void SetData(const float val[16]);
		void VBind(std::string name, Shader* shader);
        void VUnbind(std::string name, Shader* shader);


	private:
		float m_val[16];
	};

	class VIX_API TextureVariable : public IShaderVariable
	{
	public:
		TextureVariable(Texture* texture);

		~TextureVariable();

		void SetData(Texture* texture);
		void VBind(std::string name, Shader* shader);
        void VUnbind(std::string name, Shader* shader);

	private:
		Texture* m_texture;
	};

}

#endif
