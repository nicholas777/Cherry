#pragma once

#include "camera.h"
#include "core/application.h"
#include "math/projection.h"

namespace Cherry {
    class StaticCamera : public Camera
    {
    public:
        StaticCamera() = default;

        StaticCamera(float span, float znear, float zfar)
            : m_Span(span), m_Near(znear), m_Far(zfar) {
            float aspect = WINDOW_WIDTH / WINDOW_HEIGHT;
            m_Projection = ortho(-span * aspect, span * aspect, span, -span, zfar, znear);
            m_Transform = Matrix4x4f::Identity();
        }

        void RecelcProjection(float aspect = WINDOW_WIDTH / WINDOW_HEIGHT) {
            m_Projection = ortho(-m_Span * aspect, m_Span * aspect, m_Span, -m_Span, m_Far, m_Near);
        }

        void ResizeViewport(float width, float height) {
            float aspect = width / height;
            m_Projection = ortho(-m_Span * aspect, m_Span * aspect, m_Span, -m_Span, m_Far, m_Near);
        }

        Vector2f GetTransformCorrection(float aspect = WINDOW_WIDTH / WINDOW_HEIGHT) {
            return Vector2f((-m_Span * aspect) / 2, -m_Span / 2);
        }

        float GetSpan() { return m_Span; }

        float GetNear() { return m_Near; }

        float GetFar() { return m_Far; }

        void SetSpan(float span) { m_Span = span; };

        void SetNear(float Near) { m_Near = Near; };

        void SetFar(float Far) { m_Far = Far; };

        Matrix4x4f& GetTransform() { return m_Transform; }
        void SetTransform(const Matrix4x4f& mat) { m_Transform = mat; }

    private:
        Matrix4x4f m_Transform;
        float m_Span, m_Near, m_Far;
    };
}
