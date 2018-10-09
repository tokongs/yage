#include "ShaderResourceView.h"

namespace yage
{
ShaderResourceView::ShaderResourceView()
{
}

ShaderResourceView::~ShaderResourceView()
{
}

void ShaderResourceView::constructFrame(bool independent)
{
    ShaderPtr shader = std::static_pointer_cast<Shader>(m_resource);
    if (independent)
    {
       ImGui::Begin("Shader Resource View", m_open);
    }
    ResourceView::constructFrame(false);
    ImGui::LabelText("OpenGL ID", std::to_string(shader->getGLObjectId()).c_str());

    if (independent)
    {
        ImGui::End();
    }
}
} // namespace yage