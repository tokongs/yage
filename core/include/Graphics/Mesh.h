#pragma once
#include "config.h"
#include "VertexBuffer.h"
#include "glm/vec3.hpp"
#include "Resource.h"
#include <memory>
#include <string>
#include "Logger.h"

namespace yage
{
struct aabb
{
    glm::vec3 min, max;
};
class Mesh : public Resource
{
  public:
    Mesh(VertexBuffer* buffer);
    ~Mesh();

    VertexBuffer *getVertexBuffer();
    aabb getAABB();

  private:
    VertexBuffer *mVertexBuffer;
    aabb mAABB;
};
} // namespace yage