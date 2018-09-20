
#pragma once
#include <GL/glew.h>
#include <string>
#include <config.h>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h" 
#include <iostream>

namespace yage
{
class Shader
{
public:
  /**
     * @brief Creates and compiles a vertex and fragment shader
     * 
     * @param vertexCode as a string
     * @param fragmentCode as a string
     */
  Shader(const char* vertex_code, const char* fragment_code);
  ~Shader();

  /**
     * @brief Set this shader to the active shader
     * 
     */
  void activate();

private:
  std::string m_vertex_code;
  std::string m_fragment_code;
  
  GLuint m_gl_object_id;
  
  DECLARE_LOGGERS;
};
} // namespace yage