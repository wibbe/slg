
#include "slg/CameraControllers.hpp"

namespace slg {

  void flyController(Camera & camera, Input & input, double dt)
  {
    if (input.isKeyDown('W'))
      camera.move(10.0 * dt);
    else if (input.isKeyDown('S'))
      camera.move(-10.0 * dt);

    if (input.isKeyDown('D'))
      camera.strafe(5.0 * dt);
    else if (input.isKeyDown('A'))
      camera.strafe(-5.0 * dt);

    if (input.mouseButton(1))
    {
      camera.yaw(input.mouseRelX() * 0.3);
      camera.pitch(input.mouseRelY() * 0.3);
    }
  }

}

