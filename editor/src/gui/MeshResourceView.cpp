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
    Ref<Mesh> mesh = mResource;
    if (independent)
    {
        ImGui::Begin("Resource View", &mOpen);
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