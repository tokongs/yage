#include <Shader.h>
namespace yage
{
Shader::Shader(int id, std::string name, std::string file_path ,std::string code, ShaderType type)
    : Resource(id, name, file_path), m_type(type), m_code(code)
{
    const char *c_code = code.c_str();
    int success;
    char info_log[512];

    // vertex Shader

    YAGE_INFO("Compiling shader");

    if (m_type == ShaderType::VERTEX_SHADER)
    {
        m_gl_object_id = glCreateShader(GL_VERTEX_SHADER);
    }
    else if (m_type == ShaderType::FRAGMENT_SHADER)
    {
        m_gl_object_id = glCreateShader(GL_FRAGMENT_SHADER);
    }
    glShaderSource(m_gl_object_id, 1, &c_code, NULL);
    glCompileShader(m_gl_object_id);
    // print compile errors if any

    glGetShaderiv(m_gl_object_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(m_gl_object_id, 512, NULL, info_log);
        YAGE_ERROR(info_log);
        return;
    };
   YAGE_INFO("Shader successfully complied with id: " + std::to_string(m_gl_object_id));
}

Shader::Shader(){
    
}

Shader::~Shader()
{
   YAGE_INFO("Deleting shader with id: " + std::to_string(m_gl_object_id));
    glDeleteShader(m_gl_object_id);
}

unsigned int Shader::getGLObjectId()
{
    return m_gl_object_id;
}
} // namespace yage