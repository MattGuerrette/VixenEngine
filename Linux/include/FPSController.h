#ifndef FPS_CONTROLLER_H
#define FPS_CONTROLLER_H

#include <vix_glcamera3d.h>
#include <vix_sdlinput.h>

using namespace Vixen;

class FPSController
{
public:
    FPSController(SDLKeyboardState* keyboard, GLCamera3D* camera);

    void Update(float dt);

    static const int SPEED = 15;
    static const int MAX_SPEED = 10;

    static bool PHYSICS_ENABLED;

private:
    GLCamera3D*         m_camera;
    SDLKeyboardState*   m_keyboard;
};

#endif // FPS_CONTROLLER_H
