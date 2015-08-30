
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
    ITexture* tex;
    DXShader*  vShader;
    DXShader*  pShader;
    ID3D11Buffer* vertexBuffer;
    ID3D11Buffer* indexBuffer;
    ID3D11InputLayout* g_pVertexLayout;
    ID3D11VertexShader* g_pVertexShader;
    ID3D11PixelShader* g_pPixelShader;
    DirectX::XMFLOAT4X4 worldMatrix;
    DirectX::XMFLOAT4X4 viewMatrix;
    DirectX::XMFLOAT4X4 projectionMatrix;
    IVertexBuffer* vBuffer;
    IIndexBuffer*  iBuffer;
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

    m_renderer->VSetClearColor(Vixen::Colors::CornflowerBlue);

    vShader = (DXShader*)ResourceManager::OpenShader(VTEXT("VertexShader.hlsl"), ShaderType::VERTEX_SHADER);
    pShader = (DXShader*)ResourceManager::OpenShader(VTEXT("PixelShader.hlsl"), ShaderType::PIXEL_SHADER);

    XMFLOAT4 red = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
    XMFLOAT4 green = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
    XMFLOAT4 blue = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
    XMFLOAT4 yellow = XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f);
    XMFLOAT4 purple = XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f);
    // Create vertex buffer
    SimpleVert vertices[] =
    {
        {DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f), red},
        {DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f), green}, 
        {DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), purple},
        {DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f), blue },
        {DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), yellow},
        {DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), green },
        {DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f), blue },
        {DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f), red}
    };
    vBuffer = new DXVPCBuffer(8, DXRENDERER->Device(), DXRENDERER->DeviceContext());
  

    USHORT indices[36] =
    {
        3,1,0,
        2,1,3,

        0,5,4,
        1,5,0,

        3,4,7,
        0,4,3,

        1,6,5,
        2,6,1,

        2,7,6,
        3,7,2,

        6,4,5,
        7,4,6,
    };
    iBuffer = new DXIndexBuffer(36, DXRENDERER->Device(), DXRENDERER->DeviceContext());

    //Set Buffer data
    vBuffer->VSetData(vertices);
    vBuffer->VBind();
    iBuffer->VSetData(indices);
    iBuffer->VBind();

    // Set primitive topology
    DXRENDERER->DeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


    // Initialize the world matrix
    XMMATRIX W = DirectX::XMMatrixIdentity();
    XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(W));

    // Initialize the view matrix
    DirectX::XMVECTOR Eye = DirectX::XMVectorSet(0.0f, 0.0f, -5.0f, 0.0f);
    DirectX::XMVECTOR At = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
    DirectX::XMVECTOR Up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    XMMATRIX V = DirectX::XMMatrixLookAtLH(Eye, At, Up);
    XMStoreFloat4x4(&viewMatrix, XMMatrixTranspose(V));

    // Initialize the projection matrix
    XMMATRIX P = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(75.0f), 800 / (FLOAT)600, 0.01f, 100.0f);
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

    DXRENDERER->DeviceContext()->DrawIndexed(36, 0, 0);

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