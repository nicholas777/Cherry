#include "epch.h"
#include "Font.h"
#include "Renderer/Renderer2D.h"

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

        m_SubTextures = std::unordered_map<char, SubTexture>();
        m_SubTextures.reserve(128);
    }

    // TODO: Make this not scuffed
    void Font::RenderText(const Vector2f& pos, const std::string& text)
    {
        float x = pos.x;

        for (int i = 0; i < text.length(); i++)
        {
            char c = text[i];
            texture_glyph_t* glyph = texture_font_get_glyph(m_FtFont, &c);
            
            if (i > 0)
            {
                float kerning = texture_glyph_get_kerning(glyph, &text[i - 1]);
                x += kerning / 1200.0f;
            }

            Vector2f coord1 = { x + glyph->offset_x / 1200.0f, pos.y + glyph->offset_y / 800.0f };
            Vector2f coord2 = { coord1.x + glyph->width / 1200.0f, coord1.y - glyph->height / 800.0f };

            SubTexture subTex = {
                m_Texture.Get(),
                { glyph->s0, glyph->t0 },
                { glyph->s0, glyph->t1 },
                { glyph->s1, glyph->t1 },
                { glyph->s1, glyph->t0 }
            };

            Renderer2D::DrawChar(coord1, coord2, pos, { 5, 5 }, subTex);
            x += glyph->advance_x / 1200.0f;
        }
    }

    void Font::RenderText(const Vector2f& pos, const std::string& text, const Vector4f& color, const Vector2f& scale)
    {
        float x = pos.x;

        for (int i = 0; i < text.length(); i++)
        {
            char c = text[i];
            texture_glyph_t* glyph = texture_font_get_glyph(m_FtFont, &c);

            if (i > 0)
            {
                float kerning = texture_glyph_get_kerning(glyph, &text[i - 1]);
                x += kerning * scale.x / 1200.0f;
            }

            Vector2f coord1 = { x + glyph->offset_x / 1200.0f, pos.y + glyph->offset_y / 800.0f };;
            Vector2f coord2 = { coord1.x + glyph->width / 1200.0f, coord1.y - glyph->height / 800.0f };

            coord1 *= scale;
            coord2 *= scale;

            SubTexture subTex = {
                m_Texture.Get(),
                { glyph->s0, glyph->t0 },
                { glyph->s0, glyph->t1 },
                { glyph->s1, glyph->t1 },
                { glyph->s1, glyph->t0 }
            };

            Renderer2D::DrawChar(coord1, coord2, pos, { 5, 5 }, subTex, color);
            x += glyph->advance_x * scale.x / 1200.0f;
        }
    }

}
