#include "epch.h"
#include "label.h"

namespace Cherry
{

	Label::Label(std::string filepath, std::string text, uint32_t fontSize, Vector2f position)
		: m_FontSize(fontSize), m_Font(new Font(filepath, m_FontSize)), m_Text(text)
	{
		m_Scale = { 1.0f, 1.0f };
		m_Color = { 1.0f, 1.0f, 1.0f, 1.0f };
	}

	Label::Label(Shared<Font> font, std::string text, Vector2f position)
		: m_Font(font), m_FontSize(m_Font->GetFontSize()), m_Text(text)
	{
		m_Scale = { 1.0f, 1.0f };
		m_Color = { 1.0f, 1.0f, 1.0f, 1.0f };
	}

	void Label::OnUpdate()
	{
		m_Font->RenderText(m_Pos, m_Text, m_Color, m_Scale);
	}
}
