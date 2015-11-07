/*
	Copyright (C) 2015  Matt Guerrette

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef VIX_SHADER_H
#define VIX_SHADER_H

#include <vix_platform.h>
#include <vix_stringutil.h>
#include <vix_file.h>
#include <vix_texture.h>
#include <vix_asset.h>

namespace Vixen {

	enum class ShaderType
	{
		VERTEX_SHADER, /*DIRECTX & OPENGL*/
		GEOMETRY_SHADER, /*DIRECTX & OPENGL */
		TESSELATION_CONTROL_SHADER, /*OPENGL*/
		TESSELATION_EVAL_SHADER, /*OPENGL*/
		FRAGMENT_SHADER, /*OPENGL*/
        PIXEL_SHADER /*DIRECTX*/
	};

	struct ShaderInfo
	{
		ShaderType type;       /*type of shader*/
		UString    filePath;   /*path to shader*/
		UString    raw;        /*raw contents of shader*/
	};

	class VIX_API Shader : public Asset
	{
	public:
		Shader();

		virtual ~Shader() { };

		virtual bool	VSetData(std::string name, const void* data, size_t size) = 0;
		virtual bool	VSetInt(std::string name, int data) = 0;
		virtual bool	VSetFloat(std::string name, float data) = 0;
		virtual bool	VSetFloat2(std::string name, const float data[2]) = 0;
		virtual bool	VSetFloat3(std::string name, const float data[3]) = 0;
		virtual bool	VSetFloat4(std::string name, const float data[4]) = 0;
		virtual bool	VSetMatrix4x4(std::string name, const float data[16]) = 0;

		virtual bool    VBindTexture(std::string name, Texture* texture) = 0;
    protected:
        virtual void VBind() = 0;
        virtual void VUnbind() = 0;
	};

}

#endif
