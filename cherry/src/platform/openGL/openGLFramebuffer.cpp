#include "openGLFramebuffer.h"

#include "debug/profiler.h"
#include "epch.h"

#include <glad/glad.h>

namespace Cherry {
    static bool IsDepthAttachment(FramebufferAttachment attachment) {
        return attachment.format == FramebufferTextureFormat::Depth24Stencil8;
    }

    OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferData& data)
        : m_Data(data), m_Attachments(data.attachments) {
        RegenerateFramebuffer();
    }

    OpenGLFramebuffer::~OpenGLFramebuffer() {
        glDeleteFramebuffers(1, &m_FramebufferID);
    }

    int OpenGLFramebuffer::ReadPixel(uint32_t attachmentIndex, uint32_t x, uint32_t y) {
        // TODO: Extend this to allow for multiple pixel formats
        glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
        int value;
        glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &value);

        uint32_t error = glGetError();
        return value;
    }

    void OpenGLFramebuffer::Resize(Vector2f size) {
        m_Data.width = size.x;
        m_Data.height = size.y;

        RegenerateFramebuffer();
    }

    void OpenGLFramebuffer::Bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);
    }

    void OpenGLFramebuffer::Unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFramebuffer::RegenerateFramebuffer() {
        CH_PROFILE_FUNC();

        if (m_FramebufferID) {
            glDeleteFramebuffers(1, &m_FramebufferID);

            glDeleteTextures(1, &m_DepthAttachment);
            glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());

            m_DepthAttachment = 0;
            m_ColorAttachments.clear();
        }

        glGenFramebuffers(1, &m_FramebufferID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);

        m_AttachmentsGL = new uint32_t[m_Attachments.size()];
        glGenTextures(m_Attachments.size(), m_AttachmentsGL);

        int colorAttachments = 0;
        for (int i = 0; i < m_Attachments.size(); i++) {
            FramebufferAttachment attachment = m_Attachments[i];

            if (IsDepthAttachment(attachment)) {
                glBindTexture(GL_TEXTURE_2D, m_AttachmentsGL[i]);
                glTextureStorage2D(m_AttachmentsGL[i], 1, GL_DEPTH24_STENCIL8, m_Data.width,
                                   m_Data.height);

                glTextureParameteri(m_AttachmentsGL[i], GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTextureParameteri(m_AttachmentsGL[i], GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D,
                                       m_AttachmentsGL[i], 0);

                m_DepthAttachment = m_AttachmentsGL[i];
                m_DepthAttachmentData = m_Attachments[i];

            } else {
                glBindTexture(GL_TEXTURE_2D, m_AttachmentsGL[i]);

                switch (attachment.format) {
                    case FramebufferTextureFormat::RGBA8:
                        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Data.width, m_Data.height, 0,
                                     GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

                        glTextureParameteri(m_AttachmentsGL[i], GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                        glTextureParameteri(m_AttachmentsGL[i], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

                        glFramebufferTexture2D(GL_FRAMEBUFFER,
                                               GL_COLOR_ATTACHMENT0 + colorAttachments,
                                               GL_TEXTURE_2D, m_AttachmentsGL[i], 0);

                        m_ColorAttachments.push_back(m_AttachmentsGL[i]);
                        m_ColorAttachmentsData.push_back(m_Attachments[i]);

                        colorAttachments++;
                        break;

                    case FramebufferTextureFormat::RedInteger:
                        glTexImage2D(GL_TEXTURE_2D, 0, GL_R32I, m_Data.width, m_Data.height, 0,
                                     GL_RED_INTEGER, GL_UNSIGNED_BYTE, nullptr);

                        glTextureParameteri(m_AttachmentsGL[i], GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                        glTextureParameteri(m_AttachmentsGL[i], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

                        glFramebufferTexture2D(GL_FRAMEBUFFER,
                                               GL_COLOR_ATTACHMENT0 + colorAttachments,
                                               GL_TEXTURE_2D, m_AttachmentsGL[i], 0);

                        m_ColorAttachments.push_back(m_AttachmentsGL[i]);
                        m_ColorAttachmentsData.push_back(m_Attachments[i]);

                        colorAttachments++;

                        break;

                    case FramebufferTextureFormat::Invalid:
                        CH_ASSERT(false, "Invalid framebuffer texture format!");
                }
            }
        }

        if (m_ColorAttachments.size() > 1) {
            CH_ASSERT(m_ColorAttachments.size() <= 4,
                      "Too many framebuffer color attachment, only four is supported");
            GLenum attachments[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1,
                                      GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
            glDrawBuffers(m_ColorAttachments.size(), attachments);
        } else if (m_ColorAttachments.size() == 0) {
            glDrawBuffer(GL_NONE);
        }

        CH_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,
                  "Incomplete framebuffer");
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

}
