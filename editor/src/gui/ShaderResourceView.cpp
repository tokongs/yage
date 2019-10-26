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
    Shader* shader =(Shader*)(mResource);
    if (independent)
    {
       ImGui::Begin("Shader Resource View", &mOpen);
    }
    ResourceView::constructFrame(false);
    ImGui::LabelText("OpenGL ID", std::to_string(shader->getGLObjectId()).c_str());

    if (independent)
    {
        ImGui::End();
    }
}
} // namespace yage