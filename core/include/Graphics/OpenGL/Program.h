#pragma once
#include <GL/glew.h>
#include <memory>
#include "config.h"
#include "Shader.h"
#include "Resource.h"

namespace yage
{
/**
     * @brief Takes in shaders and links them to a program
     * 
     */
class Program : public Resource
{
  public:
    Program();
    ~Program();

    void attachShader(ShaderPtr shader);
    void activate();

  private:
    GLuint m_gl_object_id;
    ShaderPtr m_vertex_shader = nullptr;
    ShaderPtr m_fragment_shader = nullptr;

    DECLARE_LOGGERS
};
    typedef std::shared_ptr<Program> ProgramPtr;
} // namespace yage