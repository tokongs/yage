#pragma once
#include <memory>
#include <string>
#include <GL/glew.h>
#include "Resource.h"

namespace yage
{
/**
 * @brief A wrapper class around a opengl texture
 * 
 */
class Texture : public Resource
{
  static const int TextureUnit0 = GL_TEXTURE0;

public:
  Texture(float width, float height, const void *data, int format);
  ~Texture();

  void bind();

  void loadData(float width, float height, const void *data, int format);

  void setTextureUnit(int unit);
  void setWrapping(int wrap);
  void setFiltering(int filtering);

  int getWrapping();
  int getFiltering();
  unsigned int getTextureUnit();

  std::string getType() override;

private:
  void setOptions();

  unsigned int m_gl_object_id;

  unsigned int m_texture_unit;

  unsigned int m_wrapping;
  unsigned int m_filtering;

  std::string m_resource_type = "Texture_Resource";
};

typedef std::shared_ptr<Texture> TexturePtr;
} // namespace yage