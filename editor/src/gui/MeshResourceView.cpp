#include "MeshResourceView.h"

namespace yage
{
MeshResourceView::MeshResourceView()
{
}

MeshResourceView::~MeshResourceView()
{
}

void MeshResourceView::constructFrame(bool independent)
{
    MeshPtr mesh = std::static_pointer_cast<Mesh>(m_resource);
    if (independent)
    {
        ImGui::Begin("Resource View", m_open);
    }
    ResourceView::constructFrame(false);

    ImGui::DragFloat3("AABB_max", mesh->getAABB().max.data.data);
    ImGui::DragFloat3("AABB_min", mesh->getAABB().min.data.data);
    ImGui::LabelText("Vertex Buffer size", std::to_string(mesh->getVertexBuffer()->getSize()).c_str());

    if (independent)
    {
        ImGui::End();
    }
}

} // namespace yage