#pragma once
#include <GL/glew.h>
#include <memory>
#include <vector>
#include <string>
#include "config.h"
#include "Shader.h"
#include "Resource.h"
#include "ResourceManager.h"

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

  void attachShaders(std::vector<int> shaders);
  void activate();

  std::string getType() override;

private:
  GLuint m_gl_object_id;
  ShaderPtr m_vertex_shader = nullptr;
  ShaderPtr m_fragment_shader = nullptr;
  std::string m_type;
  DECLARE_LOGGERS
};
typedef std::shared_ptr<Program> ProgramPtr;
} // namespace yage