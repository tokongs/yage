#include "Mesh.h"

namespace yage
{
Mesh::Mesh(VertexBufferPtr buffer)
    : m_vertex_buffer(buffer)
{
}

Mesh::Mesh(){
    
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


std::string Mesh::getType(){
    return m_resource_type;
}
} // namespace yage