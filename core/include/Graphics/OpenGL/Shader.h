
#pragma once
#include <GL/glew.h>
#include <string>
#include <iostream>
#include <memory>
#include "config.h"
#include "Resource.h"
#include "Logger.h"
namespace yage
{

enum ShaderType
{
  VERTEX_SHADER,
  FRAGMENT_SHADER
};

struct ShaderUniform
{
  int size;
  unsigned int type;
  unsigned int index;
  unsigned int location;
  std::string name;
};

class Shader : public Resource
{
public:
  /**
     * @brief Creates and compiles a vertex and fragment shader
     * 
     * @param vertexCode as a string
     * @param fragmentCode as a string
     */
  Shader(std::string code, ShaderType type);
  Shader();
  ~Shader();

  unsigned int getGLObjectId();

private:
  std::string mCode;

  unsigned int mGlObjectId;

  ShaderType mType;
};
} // namespace yage