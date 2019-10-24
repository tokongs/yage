#include "Mesh.h"

namespace yage
{
Mesh::Mesh(int id, std::string name, std::string file_path, VertexBufferPtr buffer)
    :Resource(id, name, file_path), m_vertex_buffer(buffer)
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