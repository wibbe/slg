
#ifndef SLG_FLY_CONTROLLER_HPP
#define SLG_FLY_CONTROLLER_HPP

#include "slg/Camera.hpp"
#include "slg/Input.hpp"

namespace slg {

  void flyController(Camera & camera, Input & input, double dt);

}

#endif

