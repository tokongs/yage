#include "Program.h"

namespace yage
{
Program::Program()
{
    mGlObjectId = glCreateProgram();
   YAGE_INFO("Created program with id: " + std::to_string(mGlObjectId));
}

Program::~Program()
{
   YAGE_INFO("Deleting program with id: " + std::to_string(mGlObjectId));
    glDeleteProgram(mGlObjectId);
}

void Program::activate()
{
    glUseProgram(mGlObjectId);
}

void Program::attachShaders(std::vector<int> shaders)
{

    for (int i = 0; i < shaders.size(); i++)
    {
        Shader* shader = ResourceManager::getInstance().getResource<Shader>(shaders[i]);
        YAGE_INFO("Linking " + shader->getName() + " to program " + std::to_string(mGlObjectId));
        glAttachShader(mGlObjectId, shader->getGLObjectId());
        glLinkProgram(mGlObjectId);
    }

    GLint success;
    char info_log[512];

    glGetProgramiv(mGlObjectId, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(mGlObjectId, 512, NULL, info_log);
        YAGE_ERROR(info_log);
        return;
    }
    else
    {
       YAGE_INFO("Shader linking successfull.");
    }

    mapUniforms();
}

void Program::mapUniforms()
{
    int num_uniforms;
    glGetProgramiv(mGlObjectId, GL_ACTIVE_UNIFORMS, &num_uniforms);

    for (int i = 0; i < num_uniforms; i++)
    {
        ShaderUniform uniform;
        uniform.index = i;

        char name[30];
        int length = 0;
        glGetActiveUniform(mGlObjectId, i, 30, &length, &(uniform.size), &(uniform.type), name);
        uniform.name = name;
        uniform.name = uniform.name.substr(0, length);
        uniform.location = getUniformLocation(uniform.name);

        mUniforms[uniform.name] = uniform;
    }
}

int Program::getUniformLocation(std::string name)
{
    return glGetUniformLocation(mGlObjectId, name.c_str());
}

void Program::setInt(std::string name, int value)
{
    auto uniform_it = mUniforms.find(name);

    glProgramUniform1i(mGlObjectId, uniform_it->second.location, value);
}

void Program::setFloat(std::string name, float value)
{
    auto uniform_it = mUniforms.find(name);
    if (!uniformIsActive(uniform_it, name) ||
        !typeIsCorrect(uniform_it->second.type, GL_FLOAT))
    {
        return;
    }
    glProgramUniform1f(mGlObjectId, uniform_it->second.location, value);
}

void Program::setVec2(std::string name, glm::vec2 value)
{
    auto uniform_it = mUniforms.find(name);
    if (!uniformIsActive(uniform_it, name) ||
        !typeIsCorrect(uniform_it->second.type, GL_FLOAT_VEC2))
    {
        return;
    }
    glProgramUniform2f(mGlObjectId, uniform_it->second.location, value.x, value.y);
}

void Program::setVec3(std::string name, glm::vec3 value)
{
    auto uniform_it = mUniforms.find(name);
    if (!uniformIsActive(uniform_it, name) ||
        !typeIsCorrect(uniform_it->second.type, GL_FLOAT_VEC3))
    {
        return;
    }
    glProgramUniform3f(mGlObjectId, uniform_it->second.location, value.x, value.y, value.z);
}

void Program::setVec4(std::string name, glm::vec4 value)
{
    auto uniform_it = mUniforms.find(name);
    if (!uniformIsActive(uniform_it, name) ||
        !typeIsCorrect(uniform_it->second.type, GL_FLOAT_VEC4))
    {
        return;
    }
    glProgramUniform4f(mGlObjectId, uniform_it->second.location, value.x, value.y, value.z, value.w);
}

void Program::setMat4(std::string name, glm::mat4 value)
{
    auto uniform_it = mUniforms.find(name);
    if (!uniformIsActive(uniform_it, name) ||
        !typeIsCorrect(uniform_it->second.type, GL_FLOAT_MAT4))
    {
        return;
    }
    glProgramUniformMatrix4fv(mGlObjectId, uniform_it->second.location, 1, false, glm::value_ptr(value));
}

bool Program::uniformIsActive(std::unordered_map<std::string, ShaderUniform>::iterator uniform_it, std::string name)
{
    if (uniform_it == mUniforms.end())
    {
        YAGE_WARN("Trying to set inactive or non-existent uniform (int) with name: " + name);
        return false;
    }

    return true;
}

bool Program::typeIsCorrect(unsigned int type, unsigned int requested_type)
{
    if (type != requested_type)
    {
        YAGE_WARN("Trying to set uniform of type " + std::to_string(type) + "to value of type" + std::to_string(requested_type));
        return false;
    }

    return true;
}

} // namespace yage