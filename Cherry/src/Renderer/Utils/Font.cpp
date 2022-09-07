#include "epch.h"
#include "Font.h"
#include "Renderer/Renderer2D.h"
#include "core/Application.h"

namespace Cherry
{
    Font::Font(std::string filepath, uint32_t fontSize)
        : m_FontSize(fontSize)
    {
        
        m_FtTexture = texture_atlas_new(512, 512, 4);
        m_FtFont = texture_font_new_from_file(m_FtTexture, fontSize, filepath.c_str());
        
        CH_ASSERT(m_FtFont, "Failed to load font!");

        TextureParams params;
        params.format = TextureFormat::RGBA;

        params.minFilter = TextureFilter::Nearest;
        params.magFilter = TextureFilter::Nearest;

        params.wrap = TextureWrap::ClampToEdge;

        texture_font_load_glyphs(m_FtFont, " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");

        m_Texture = Texture::Create(512, 512, params);
        m_Texture->SetData(m_FtTexture->data);

        m_Characters = std::unordered_map<char, Character>();
        m_Characters.reserve(128);

        float width  = Application::GetApplication().GetWindow()->GetWidth();
        float height = Application::GetApplication().GetWindow()->GetHeight();

        // TODO: Support for non-ASCII characters
        for (int i = 0; i < 128; i++)
        {
            char c = i;
            texture_glyph_t* glyph = texture_font_get_glyph(m_FtFont, &c);

            SubTexture subTex = {
                m_Texture.Get(),
                { glyph->s0, glyph->t0 },
                { glyph->s0, glyph->t1 },
                { glyph->s1, glyph->t1 },
                { glyph->s1, glyph->t0 }
            };

            Character character;
            character.advance = glyph->advance_x / width;
            character.bearing = Vector2f(glyph->offset_x / width, glyph->offset_y / height);
            character.size    = Vector2f(glyph->width / width, glyph->height / height);
            
            character.texture = subTex;

            m_Characters[c] = character;
        }
    }

    float Font::GetWidth(std::string string)
    {
        float result = 0.0f;

        for (int i = 0; i < string.size(); i++)
        {
            char c = i;
            if (i > 0)
            {
                float kerning = texture_glyph_get_kerning(texture_font_get_glyph(m_FtFont, &string[i]), &string[i - 1]);
                result += kerning / Application::GetApplication().GetWindow()->GetWidth();
            }

            result += m_Characters[c].advance;
        }

        return result;
    }

    void Font::RenderText(const Vector2f& pos, const std::string& text)
    {
        float x = pos.x;

        for (int i = 0; i < text.length(); i++)
        {
            Character c = m_Characters[text[i]];
            
            if (i > 0)
            {
                float kerning = texture_glyph_get_kerning(texture_font_get_glyph(m_FtFont, &text[i]), &text[i - 1]);
                x += kerning / 1200.0f;
            }

            Vector2f coord1 = { x + c.bearing.x, pos.y + c.bearing.y };
            Vector2f coord2 = { coord1.x + c.size.x, coord1.y - c.size.y };

            Renderer2D::DrawChar(coord1, coord2, pos, { 3, 3 }, c.texture);
            x += c.advance;
        }
    }

    void Font::RenderText(const Vector2f& pos, const std::string& text, const Vector4f& color, const Vector2f& scale)
    {
        float x = pos.x;

        for (int i = 0; i < text.length(); i++)
        {
            Character c = m_Characters[text[i]];

            if (i > 0)
            {
                float kerning = texture_glyph_get_kerning(texture_font_get_glyph(m_FtFont, &text[i]), &text[i - 1]);
                x += kerning / 1200.0f;
            }

            Vector2f coord1 = { x + c.bearing.x, pos.y + c.bearing.y };
            Vector2f coord2 = { coord1.x + c.size.x, coord1.y - c.size.y };

            Renderer2D::DrawChar(coord1, coord2, pos, scale, c.texture, color);
            x += c.advance;
        }
    }

}
