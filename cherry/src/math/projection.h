#pragma once

#include "matrix.h"

namespace Cherry {
    Matrix4x4f ortho(float left, float right, float top, float bottom, float farPlane = 1,
                     float nearPlane = -1);
    // Matrix4x4f perspective();
}
