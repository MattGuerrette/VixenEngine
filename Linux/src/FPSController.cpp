#include <FPSController.h>

bool FPSController::PHYSICS_ENABLED = true;

FPSController::FPSController(SDLKeyboardState* keyboard, GLCamera3D* camera)
{
    m_camera = camera;
    m_keyboard = keyboard;
}

void FPSController::Update(float dt)
{

    if(m_keyboard->KeyPress(IKEY::A))
        m_camera->Move(C3D_DIRECTION::LEFT);
    if(m_keyboard->KeyPress(IKEY::D))
        m_camera->Move(C3D_DIRECTION::RIGHT);
    if(m_keyboard->KeyPress(IKEY::W))
        m_camera->Move(C3D_DIRECTION::FORWARD);
    if(m_keyboard->KeyPress(IKEY::S))
        m_camera->Move(C3D_DIRECTION::BACKWARD);

}
