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


#ifndef VIX_GLINDEXBUFFER_H
#define VIX_GLINDEXBUFFER_H

#include <vix_platform.h>
#include <vix_indexbuffer.h>
#include <vix_gl.h>

namespace Vixen {

	class VIX_API GLIndexBuffer : public IIndexBuffer
	{
	public:
		GLIndexBuffer(size_t count);

		~GLIndexBuffer();

		void VSetData(const unsigned short* data);
		void VBind();
		void VUnbind();

	private:
		GLuint  m_buffer;
		GLenum m_target;
	};
}

#endif
