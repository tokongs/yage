#include "Mesh.h"

namespace yage
{
Mesh::Mesh(VertexBuffer* vertexBuffer)
:mVertexBuffer(vertexBuffer)
{
}


Mesh::~Mesh()
{
    if(mVertexBuffer){
        delete mVertexBuffer;
    }
}

VertexBuffer* Mesh::getVertexBuffer()
{
    return mVertexBuffer;
}

aabb Mesh::getAABB()
{
    return mAABB;
}
} // namespace yage