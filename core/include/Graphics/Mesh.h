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
    Mesh(int id, std::string name, std::string file_path, VertexBufferPtr vertexBufferPtr);
    Mesh();
    ~Mesh();

    VertexBufferPtr getVertexBuffer();
    aabb getAABB();

  private:
    VertexBufferPtr m_vertex_buffer;
    aabb m_aabb;
};

typedef std::shared_ptr<Mesh> MeshPtr;
} // namespace yage