#pragma once

#include "math/matrix.h"
#include "core/pointer.h"
#include "texture.h"
#include "graphics/cameras/camera.h"

namespace Cherry
{
    class Renderer2D
    {
    public:
        static void Init();
        static void Shutdown();

        static void Begin(const Matrix4x4f& proj, const Matrix4x4f& transform);
        static void Begin();
        static void End();

        // Rectangle 
        static void DrawRect(const Vector2f& position, const Vector2f& size, const Scoped<Texture>& texture);
        static void DrawRect(const Vector2f& position, const Vector2f& size, const SubTexture& texture);
        static void DrawRect(const Vector2f& position, const Vector2f& size, const Vector4f& color);

        static void DrawRect(const Matrix4x4f& transform, const Shared<Texture>& texture, const Vector4f& color = { 1, 1, 1, 1 }, int entityID = -1);
        static void DrawRect(const Matrix4x4f& transform, const SubTexture& texture, const Vector4f& color = { 1, 1, 1, 1 }, int entityID = -1);
        static void DrawRect(const Matrix4x4f& transform, const Vector4f& color, int entityID = -1);

        static void DrawRect(const Vector2f& position, const float& rotation, const Vector2f& size, const Vector4f& color);
        static void DrawRect(const Vector2f& position, const float& rotation, const Vector2f& size, const Scoped<Texture>& texture);
        static void DrawRect(const Vector2f& position, const float& rotation, const Vector2f& size, const SubTexture& texture);

        // Text
        static void DrawChar(const Vector2f& coord1, const Vector2f& coord2, const SubTexture& texture, const Vector4f& color = { 1, 1, 1, 1 });

    private:
        static void Flush();
        static void NewBatch();

        static float GetTextureIndex(Texture* ptr);
    };
}
