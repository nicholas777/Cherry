#pragma once

#include "math/vector.h"

#include <cmath>

namespace Cherry {
    class ColorUtils
    {
    public:
        inline static Vector3i RGBToInt(Vector3f color) {
            return Vector3i(floor(color.x * 255), floor(color.y * 255), floor(color.z * 255));
        }

        // TODO: Consider making Color struct
        inline static Vector3f RGBToFloat(Vector3i color) {
            return Vector3f(floor((float)color.x / 255), floor((float)color.y / 255),
                            floor((float)color.z / 255));
        }

        inline static Vector4i RGBAToInt(Vector4f color) {
            return Vector4i(floor(color.x * 255), floor(color.y * 255), floor(color.z * 255),
                            floor(color.w * 255));
        }

        inline static Vector4f RGBAToFloat(Vector4i color) {
            return Vector4f(floor((float)color.x / 255), floor((float)color.y / 255),
                            floor((float)color.z / 255), floor((float)color.w / 255));
        }

        inline static uint32_t RGBToHex(Vector3i color) {
            return ((color.x & 0xff) << 16) + ((color.y & 0xff) << 8) + (color.z & 0xff);
        }

        inline static uint32_t RGBAToHex(Vector4i color) {
            return ((color.x & 0xff) << 24) + ((color.y & 0xff) << 16) + ((color.z & 0xff) << 8) +
                   (color.w & 0xff);
        }

        inline static Vector3i HexToRGB(uint32_t color) {
            Vector3i result;
            result.x = ((color >> 16) & 0xFF);
            result.y = ((color >> 8) & 0xFF);
            result.z = ((color)&0xFF);

            return result;
        }

        inline static Vector4i HexToRGBA(uint32_t color) {
            Vector4i result;
            result.x = ((color >> 24) & 0xFF);
            result.y = ((color >> 16) & 0xFF);
            result.z = ((color >> 8) & 0xFF);
            result.w = ((color)&0xFF);

            return result;
        }
    };
}
