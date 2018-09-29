#pragma once
#include "config.h"
#include "VertexBuffer.h"
#include "glm/vec3.hpp"
#include "Resource.h"
#include <memory>
#include <string>

namespace yage
{
class Mesh : public Resource
{
    public:
    Mesh(VertexBufferPtr);
    ~Mesh();

    VertexBufferPtr getVertexBuffer();
    glm::vec3 getAABB();

    private:
    VertexBufferPtr m_vertex_buffer;
    glm::vec3 m_aabb;
    
    DECLARE_LOGGERS;
};

typedef std::shared_ptr<Mesh> MeshPtr;
} // namespace yage