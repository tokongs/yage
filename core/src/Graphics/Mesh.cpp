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

aabb Mesh::getAABB()
{
    return m_aabb;
}
} // namespace yage