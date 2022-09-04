#pragma once

#include "core/Core.h"
#include "core/Pointer.h"
#include "Math/Vector.h"
#include "Renderer/Utils/Font.h"
#include "UIComponent.h"

namespace Cherry
{
	class CHERRY_API Label : public UIElement
	{
	public:
		Label(std::string filepath, std::string text, uint32_t fontSize, Vector2f position);
		Label(Shared<Font> font, std::string text, Vector2f position);

		inline std::string GetText()    { return m_Text;  };
		inline Vector4f GetColor()      { return m_Color; };
		inline Vector2f GetScale()      { return m_Scale; };
		inline Vector2f GetPosition()   { return m_Pos;   };

		inline uint32_t GetFontSize()   { return m_FontSize; };

		inline void SetText(std::string text)  { m_Text  = text;  };
		inline void SetColor(Vector4f color)   { m_Color = color; };
		inline void SetScale(Vector2f scale)   { m_Scale = scale; };
		inline void SetPosition(Vector2f pos)  { m_Pos   = pos;   };

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
