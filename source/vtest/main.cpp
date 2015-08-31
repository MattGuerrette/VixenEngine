
#include <vix_game.h>
#include <vix_filemanager.h>
#include <vix_dxtexture.h>
#include <vix_dxrenderer.h>
#include <vix_pathmanager.h>
#include <vix_resourcemanager.h>
#include <vix_dxshader.h>
#include <vix_dxvertexshader.h>
#include <vix_dxpixelshader.h>
#include <vix_dxvertexbuffer.h>
#include <vix_dxindexbuffer.h>

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
    DXShader*  vShader;
    DXShader*  pShader;
    DirectX::XMFLOAT4X4 worldMatrix;
    DirectX::XMFLOAT4X4 viewMatrix;
    DirectX::XMFLOAT4X4 projectionMatrix;
    IVertexBuffer* vBuffer;
    IIndexBuffer*  iBuffer;
    IModel*        model;

    float rot;
};

TestGame::TestGame()
    : IGame()
{

}

void TestGame::VOnStartup()
{
    FileManager::Initialize();
    PathManager::Initialize();

    m_renderer->VSetClearColor(Vixen::Colors::Black);

    vShader = (DXShader*)ResourceManager::OpenShader(VTEXT("VertexShader.hlsl"), ShaderType::VERTEX_SHADER);
    pShader = (DXShader*)ResourceManager::OpenShader(VTEXT("PixelShader.hlsl"), ShaderType::PIXEL_SHADER);
    model = ResourceManager::OpenModel(VTEXT("monkey.obj"));

  
    // Set primitive topology
    DXRENDERER->DeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Initialize the world matrix
    XMMATRIX W = DirectX::XMMatrixIdentity();
    XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(W));

    // Initialize the view matrix
    DirectX::XMVECTOR Eye = DirectX::XMVectorSet(0.0f, 0.0f, -3.0f, 0.0f);
    DirectX::XMVECTOR At = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
    DirectX::XMVECTOR Up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    XMMATRIX V = DirectX::XMMatrixLookAtLH(Eye, At, Up);
    XMStoreFloat4x4(&viewMatrix, XMMatrixTranspose(V));

    // Initialize the projection matrix
    XMMATRIX P = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(75.0f), 
        m_window->VGetClientBounds().w / (FLOAT)m_window->VGetClientBounds().h, 0.01f, 100.0f);
    XMStoreFloat4x4(&projectionMatrix, XMMatrixTranspose(P));

    rot = 0.0f;

}

void TestGame::VOnUpdate(float dt)
{

}

void TestGame::VOnRender(float dt)
{
    rot += dt;

    XMMATRIX rotM = XMMatrixRotationRollPitchYaw(0.0f, rot, 0.0f);
    XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(rotM));

    vShader->SetMatrix4x4("world", worldMatrix);
    vShader->SetMatrix4x4("view", viewMatrix);
    vShader->SetMatrix4x4("projection", projectionMatrix);

    

    vShader->Activate();
    pShader->Activate();
    model->VRender();
  

}

void TestGame::VOnShutdown()
{
    delete model;
    delete vBuffer;
    delete iBuffer;
    delete vShader;
    delete pShader;
}

int main(int argc, char* argv[])
{
    TestGame game;

    return game.Run();
}