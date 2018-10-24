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
        ImGui::Begin("Resource View", m_open.get());
    }
    ResourceView::constructFrame(false);

    glm::vec3 max = mesh->getAABB().max;
    glm::vec3 min = mesh->getAABB().min;

    ImGui::DragFloat3("AABB_max", glm::value_ptr(max));
    ImGui::DragFloat3("AABB_min", glm::value_ptr(min));
    ImGui::LabelText("Vertex Buffer size", std::to_string(mesh->getVertexBuffer()->getSize()).c_str());

    if (independent)
    {
        ImGui::End();
    }
}

} // namespace yage