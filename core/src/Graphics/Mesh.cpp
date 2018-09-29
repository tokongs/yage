#include "Mesh.h"

namespace yage
{
Mesh::Mesh(VertexBufferPtr buffer)
    : m_vertex_buffer(buffer)
{
}

Mesh::~Mesh()
{
}

VertexBufferPtr Mesh::getVertexBuffer()
{
    return m_vertex_buffer;
}

glm::vec3 Mesh::getAABB()
{
    return m_aabb;
}

} // namespace yage