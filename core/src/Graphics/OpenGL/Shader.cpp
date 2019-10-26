#include <Shader.h>
namespace yage
{
Shader::Shader(std::string code, ShaderType type)
    : mType(type), mCode(code)
{
    const char *c_code = code.c_str();
    int success;
    char info_log[512];

    // vertex Shader

    YAGE_INFO("Compiling shader");

    if (mType == ShaderType::VERTEX_SHADER)
    {
        mGlObjectId = glCreateShader(GL_VERTEX_SHADER);
    }
    else if (mType == ShaderType::FRAGMENT_SHADER)
    {
        mGlObjectId = glCreateShader(GL_FRAGMENT_SHADER);
    }
    glShaderSource(mGlObjectId, 1, &c_code, NULL);
    glCompileShader(mGlObjectId);
    // print compile errors if any

    glGetShaderiv(mGlObjectId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(mGlObjectId, 512, NULL, info_log);
        YAGE_ERROR(info_log);
        return;
    };
   YAGE_INFO("Shader successfully complied with id: " + std::to_string(mGlObjectId));
}

Shader::Shader(){
    
}

Shader::~Shader()
{
   YAGE_INFO("Deleting shader with id: " + std::to_string(mGlObjectId));
    glDeleteShader(mGlObjectId);
}

unsigned int Shader::getGLObjectId()
{
    return mGlObjectId;
}
} // namespace yage