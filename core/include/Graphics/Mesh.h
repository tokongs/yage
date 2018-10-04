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
    Mesh();
    ~Mesh();

    VertexBufferPtr getVertexBuffer();
    glm::vec3 getAABB();

    std::string getType() override;


    private:
    VertexBufferPtr m_vertex_buffer;
    glm::vec3 m_aabb;
    std::string m_resource_type = "Mesh";
    
    DECLARE_LOGGERS;
};

typedef std::shared_ptr<Mesh> MeshPtr;
} // namespace yage