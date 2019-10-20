#pragma once
#include "config.h"
#include "VertexBuffer.h"
#include "glm/vec3.hpp"
#include "Resource.h"
#include <memory>
#include <string>

namespace yage
{
struct aabb
{
    glm::vec3 min, max;
};
class Mesh : public Resource
{
  public:
    Mesh(VertexBufferPtr);
    Mesh();
    ~Mesh();

    VertexBufferPtr getVertexBuffer();
    aabb getAABB();

  private:
    VertexBufferPtr m_vertex_buffer;
    aabb m_aabb;

    DECLARE_LOGGERS;
};

typedef std::shared_ptr<Mesh> MeshPtr;
} // namespace yage