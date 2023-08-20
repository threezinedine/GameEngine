#include <GL/glew.h>
#include <glfw/glfw3.h>
#include <imgui.h>
#include "NTTEngineImGuiTools/NTTEngineImGuiTools.hpp"

namespace ntt
{
    ImGuiImage::ImGuiImage()
    {
        glGenTextures(1, &id_);
        glBindTexture(GL_TEXTURE_2D, id_);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    void ImGuiImage::Bind()
    {
        glBindTexture(GL_TEXTURE_2D, id_);
    }

    void ImGuiImage::UnBind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    ImGuiImage::~ImGuiImage()
    {
        glDeleteTextures(1, &id_);
    }

    void ImGuiImage::SetImage(cv::Mat image)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.cols, 
            image.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, image.data);
        ImGui::Image(reinterpret_cast<void*>(id_), ImVec2(image.cols, image.rows));
    }
} // namespace ntt
