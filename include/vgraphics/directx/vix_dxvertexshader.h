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

#ifndef VIX_DXVERTEXSHADER_H
#define VIX_DXVERTEXSHADER_H

#include <vix_platform.h>
#include <vix_dxshader.h>

namespace Vixen {

    class VIX_API DXVertexShader : public DXShader
    {
    public:
        DXVertexShader(ID3D11Device* device,
                       ID3D11DeviceContext* context);

        ~DXVertexShader();


        ID3D11VertexShader* GetShader();
        ID3D11InputLayout*  GetLayout();

        bool VSetShaderResourceView(std::string name, ID3D11ShaderResourceView* rv);
        bool VSetSamplerState(std::string name, ID3D11SamplerState* ss);

    protected:
        bool VInitShader(File* file) override;
        void VBind() override;
        void VUnbind() override;

    private:
        ID3D11VertexShader*     m_shader;
        ID3D11InputLayout*      m_inputLayout;
    };

}

#endif
