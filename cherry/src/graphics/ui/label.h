#pragma once

#include "core/pointer.h"
#include "math/vector.h"
#include "renderer/utils/font.h"
#include "uiComponent.h"

namespace Cherry {
    class Label : public UIElement
    {
    public:
        Label(std::string filepath, std::string text, uint32_t fontSize, Vector2f position);
        Label(Shared<Font> font, std::string text, Vector2f position);

        inline std::string GetText() { return m_Text; };

        inline Vector4f GetColor() { return m_Color; };

        inline Vector2f GetScale() { return m_Scale; };

        inline Vector2f GetPosition() { return m_Pos; };

        inline float GetWidth() { return m_Font->GetWidth(m_Text) * m_Scale.x; };

        inline float GetHeight() {
            return m_FontSize * m_Scale.y / Application::GetApplication().GetWindow()->GetHeight();
        };

        inline uint32_t GetFontSize() { return m_FontSize; };

        inline void SetText(std::string text) { m_Text = text; };

        inline void SetColor(Vector4f color) { m_Color = color; };

        inline void SetScale(Vector2f scale) { m_Scale = scale; };

        inline void SetPosition(Vector2f pos) { m_Pos = pos; };

        virtual void OnUpdate() override;

    private:
        Shared<Font> m_Font;
        uint32_t m_FontSize;

        std::string m_Text;

        Vector2f m_Pos;
        Vector2f m_Scale;
        Vector4f m_Color;
    };
}
