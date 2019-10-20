#pragma once
#include <GL/glew.h>
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
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

  /**
   * @brief Attaches a set of shaders to this program. The shaders need to 
   * be of differing types.
   * 
   * @param shaders 
   */
  void attachShaders(std::vector<int> shaders);
  /**
   * @brief Activate this program for use in rendering
   * 
   */
  void activate();


  /**
   * @brief Set an int uniform
   * 
   * @param value
   * @param name 
   */
  void setInt(std::string name, int value);

  /**
   * @brief Set a float uniform
   * 
   * @param value
   * @param name 
   */
  void setFloat(std::string name, float value);

  /**
   * @brief Set a vector2(f) uniform
   * 
   * @param name 
   */

  void setVec2(std::string name, glm::vec2);

  /**
   * @brief SSet a vector3(f) uniform
   * 
   * @param name 
   */
  void setVec3(std::string name, glm::vec3);

  /**
   * @brief Set a vector4(f) uniform
   * 
   * @param name 
   */
  void setVec4(std::string name, glm::vec4);

  /**
   * @brief Set a 4x4 matrix uniform
   * 
   * @param name 
   */
  void setMat4(std::string name, glm::mat4);

  /**
   * @brief Returns a shader Uniform With the matching name.
   * Return an empty object if there is no matching name
   * 
   * @param name 
   * @return ShaderUniform 
   */
  ShaderUniform getUniform(std::string name);

private:
  /**
   * @brief Makes a map of the available uniform variables in this program.
   * 
   */
  void mapUniforms();

  /**
   * @brief Get the Uniform location. Wrapper around glGetUniformLocation
   * 
   * @param name 
   * @return int 
   */
  int getUniformLocation(std::string name);

  /**
   * @brief Check if uniform is inactive of non-existent
   * 
   * @param requested_type 
   */
  bool uniformIsActive(std::unordered_map<std::string, ShaderUniform>::iterator uniform_it, std::string name);

  /**
 * @brief Check if the uniform is the same as the requested type
 * 
 * @param uniform 
 * @param requested_type 
 */
  bool typeIsCorrect(unsigned int type, unsigned int requested_type);

  unsigned int m_gl_object_id;
  ShaderPtr m_vertex_shader = nullptr;
  ShaderPtr m_fragment_shader = nullptr;
  DECLARE_LOGGERS;

  std::unordered_map<std::string, ShaderUniform> m_uniforms;
};
typedef std::shared_ptr<Program> ProgramPtr;
} // namespace yage