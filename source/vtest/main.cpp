
#include <vix_game.h>
#include <vix_filemanager.h>
#include <vix_dxtexture.h>
#include <vix_dxrenderer.h>
#include <vix_pathmanager.h>
#include <vix_resourcemanager.h>
#include <vix_dxshader.h>
#include <vix_dxvertexshader.h>
#include <vix_dxpixelshader.h>

using namespace Vixen;
using namespace DirectX;

struct SimpleVert
{
    XMFLOAT3 pos;
    XMFLOAT4 color;
};

#define DXRENDERER ((DXRenderer*)m_renderer)

HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;

    // Disable optimizations to further improve shader debugging
    dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    ID3DBlob* pErrorBlob = nullptr;
    hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
        dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
    if (FAILED(hr))
    {
        if (pErrorBlob)
        {
            OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
            pErrorBlob->Release();
        }
        return hr;
    }
    if (pErrorBlob) pErrorBlob->Release();

    return S_OK;
}

class TestGame : public IGame
{
public:
    TestGame();

    void VOnStartup();
    void VOnShutdown();
    void VOnUpdate(float dt);
    void VOnRender(float dt);

private:
    ITexture* tex;
    DXShader*  vShader;
    DXShader*  pShader;
    ID3D11Device* _device;
    ID3D11DeviceContext* _context;
    ID3D11Buffer* vertexBuffer;
    ID3D11Buffer* indexBuffer;
    ID3D11InputLayout* g_pVertexLayout;
    ID3D11VertexShader* g_pVertexShader;
    ID3D11PixelShader* g_pPixelShader;
    DirectX::XMFLOAT4X4 worldMatrix;
    DirectX::XMFLOAT4X4 viewMatrix;
    DirectX::XMFLOAT4X4 projectionMatrix;
};

TestGame::TestGame()
    : IGame()
{

}

void TestGame::VOnStartup()
{
    FileManager::Initialize();
    PathManager::Initialize();

    m_renderer->VSetClearColor(Vixen::Colors::CornflowerBlue);

    
    vShader = (DXShader*)ResourceManager::OpenShader(VTEXT("VertexShader.hlsl"), ShaderType::VERTEX_SHADER);
    pShader = (DXShader*)ResourceManager::OpenShader(VTEXT("PixelShader.hlsl"), ShaderType::PIXEL_SHADER);

    FileManager::PrintOpen();

    XMFLOAT4 red = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
    XMFLOAT4 green = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
    XMFLOAT4 blue = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
    // Create vertex buffer
    SimpleVert vertices[] =
    {
        { XMFLOAT3(0.0f, 0.5f, 0.5f), red },
        { XMFLOAT3(0.5f, -0.5f, 0.5f), green },
        { XMFLOAT3(-0.5f, -0.5f, 0.5f), blue }
    };
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(SimpleVert) * 3;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory(&InitData, sizeof(InitData));
    InitData.pSysMem = vertices;
    DXRENDERER->Device()->CreateBuffer(&bd, &InitData, &vertexBuffer);

    // Set vertex buffer
    UINT stride = sizeof(SimpleVert);
    UINT offset = 0;
    DXRENDERER->DeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

    // Set primitive topology
    DXRENDERER->DeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void TestGame::VOnUpdate(float dt)
{

}

void TestGame::VOnRender(float dt)
{
    vShader->Activate();
    pShader->Activate();

    DXRENDERER->DeviceContext()->Draw(3, 0);

}

void TestGame::VOnShutdown()
{
    ReleaseCOM(vertexBuffer);
    delete vShader;
    delete pShader;
}

int main(int argc, char* argv[])
{
    TestGame game;

    return game.Run();
}