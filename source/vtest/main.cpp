
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

#define DXRENDERER ((DXRenderer*)m_renderer)

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
    DXShader*  sbVShader;
    DXShader*  sbPShader;
    DirectX::XMFLOAT4X4 viewMatrix;
    DirectX::XMFLOAT4X4 projectionMatrix;
    IModel*        model;
    IModel*        model2;
    IModel*        model3;
    Transform      modelTransform;
    Transform      modelTransform2;
    Transform      modelTransform3;
    Transform      texTransform;
    ITexture*  tex;
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
    sbVShader = (DXShader*)ResourceManager::OpenShader(VTEXT("SpriteBatch_VS.hlsl"), ShaderType::VERTEX_SHADER);
    sbPShader = (DXShader*)ResourceManager::OpenShader(VTEXT("SpriteBatch_PS.hlsl"), ShaderType::PIXEL_SHADER);
    model = ResourceManager::OpenModel(VTEXT("monkey.obj"));
    model2 = ResourceManager::OpenModel(VTEXT("ZombiDog.obj"));
    model3 = ResourceManager::OpenModel(VTEXT("thing.obj"));
    tex = ResourceManager::OpenTexture(VTEXT("stackedTileSheet.png"));

    // Initialize the view matrix
    DirectX::XMVECTOR Eye = DirectX::XMVectorSet(0.0f, 0.0f, -3.0f, 0.0f);
    DirectX::XMVECTOR At = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
    DirectX::XMVECTOR Up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    XMMATRIX V = DirectX::XMMatrixLookAtLH(Eye, At, Up);
    XMStoreFloat4x4(&viewMatrix, XMMatrixTranspose(V));

    // Initialize the projection matrix
    XMMATRIX P = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(75.0f), 
        m_window->VGetClientBounds().w / (FLOAT)m_window->VGetClientBounds().h, 0.01f, 1000.0f);
    XMStoreFloat4x4(&projectionMatrix, XMMatrixTranspose(P));


    model->VSetVertexShader(vShader);
    model->VSetPixelShader(pShader);
    model2->VSetVertexShader(vShader);
    model2->VSetPixelShader(pShader);
    model3->VSetVertexShader(vShader);
    model3->VSetPixelShader(pShader);


    modelTransform = Transform( 0.0f, 0.0f, 10.0f,
                                0.0f, 0.0f, 0.0f,
                                1.0f, 1.0f, 1.0f);
    modelTransform2 = Transform(10.0f, 0.0f, 10.0f,
        0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f);
    modelTransform3 = Transform(-10.0f, 0.0f, 10.0f,
        0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f);
    model->VSetTransform(&modelTransform);
    model2->VSetTransform(&modelTransform2);
    model3->VSetTransform(&modelTransform3);

    texTransform = Transform(20.0f, 20.0f, 0.0f,
                             0.0f, 0.0f, 0.0f,
                             1.0f, 1.0f, 0.0f);

    DXRENDERER->SpriteBatch()->SetVertexShader((DXVertexShader*)sbVShader);
    DXRENDERER->SpriteBatch()->SetPixelShader((DXPixelShader*)sbPShader);
}

void TestGame::VOnUpdate(float dt)
{
    modelTransform.RotateY(dt);
    modelTransform2.RotateY(dt);
    modelTransform3.RotateY(dt);

    //texTransform.TranslateX(50.0f * dt);
    texTransform.RotateZ(50 * dt);
}

void TestGame::VOnRender(float dt)
{
    vShader->SetMatrix4x4("view", viewMatrix);
    vShader->SetMatrix4x4("projection", projectionMatrix);

    model->VRender();
    model2->VRender();
    model3->VRender();

    m_renderer->VRenderTexture2D(tex, texTransform, Rect(0, 0, 32, 32));
}

void TestGame::VOnShutdown()
{
    delete tex;
    delete model;
    delete model2;
    delete model3;
    delete vShader;
    delete pShader;
    delete sbVShader;
    delete sbPShader;
}

int main(int argc, char* argv[])
{
    TestGame game;

    return game.Run();
}