#include "Program.h"

namespace yage
{
DEFINE_LOGGERS(Program)
Program::Program()
{
    INIT_LOGGERS(Program);
    m_gl_object_id = glCreateProgram();
    LOG(Program, info, "Created program with id: " + std::to_string(m_gl_object_id));
}

Program::~Program()
{
    LOG(Program, info, "Deleting program with id: " + std::to_string(m_gl_object_id));
    FLUSH_LOGGERS(Program);
    glDeleteProgram(m_gl_object_id);
}

void Program::activate()
{
    glUseProgram(m_gl_object_id);
}

void Program::attachShaders(std::vector<ShaderPtr> shaders)
{

    for (int i = 0; i < shaders.size(); i++)
    {
        LOG(Program, info, "Linking " + shaders[i]->getName() + " to program " + std::to_string(m_gl_object_id));
        glAttachShader(m_gl_object_id, shaders[i]->getGLObjectId());
        glLinkProgram(m_gl_object_id);
    }

    GLint success;
    char info_log[512];

    glGetProgramiv(m_gl_object_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_gl_object_id, 512, NULL, info_log);
        LOG(Program, error, info_log);
        return;
    }
    else
    {
        LOG(Program, info, "Shader linking successfull.");
    }

    mapUniforms();
}

void Program::mapUniforms()
{
    int num_uniforms;
    glGetProgramiv(m_gl_object_id, GL_ACTIVE_UNIFORMS, &num_uniforms);

    for (int i = 0; i < num_uniforms; i++)
    {
        ShaderUniform uniform;
        uniform.index = i;

        char name[30];
        int length = 0;
        glGetActiveUniform(m_gl_object_id, i, 30, &length, &(uniform.size), &(uniform.type), name);
        uniform.name = name;
        uniform.name = uniform.name.substr(0, length);
        uniform.location = getUniformLocation(uniform.name);

        m_uniforms[uniform.name] = uniform;
    }
}

int Program::getUniformLocation(std::string name)
{
    return glGetUniformLocation(m_gl_object_id, name.c_str());
}

void Program::setInt(std::string name, int value)
{
    auto uniform_it = m_uniforms.find(name);

    glProgramUniform1i(m_gl_object_id, uniform_it->second.location, value);
}

void Program::setFloat(std::string name, float value)
{
    auto uniform_it = m_uniforms.find(name);
    if (!uniformIsActive(uniform_it, name) ||
        !typeIsCorrect(uniform_it->second.type, GL_FLOAT))
    {
        return;
    }
    glProgramUniform1f(m_gl_object_id, uniform_it->second.location, value);
}

void Program::setVec2(std::string name, glm::vec2 value)
{
    auto uniform_it = m_uniforms.find(name);
    if (!uniformIsActive(uniform_it, name) ||
        !typeIsCorrect(uniform_it->second.type, GL_FLOAT_VEC2))
    {
        return;
    }
    glProgramUniform2f(m_gl_object_id, uniform_it->second.location, value.x, value.y);
}

void Program::setVec3(std::string name, glm::vec3 value)
{
    auto uniform_it = m_uniforms.find(name);
    if (!uniformIsActive(uniform_it, name) ||
        !typeIsCorrect(uniform_it->second.type, GL_FLOAT_VEC3))
    {
        return;
    }
    glProgramUniform3f(m_gl_object_id, uniform_it->second.location, value.x, value.y, value.z);
}

void Program::setVec4(std::string name, glm::vec4 value)
{
    auto uniform_it = m_uniforms.find(name);
    if (!uniformIsActive(uniform_it, name) ||
        !typeIsCorrect(uniform_it->second.type, GL_FLOAT_VEC4))
    {
        return;
    }
    glProgramUniform4f(m_gl_object_id, uniform_it->second.location, value.x, value.y, value.z, value.w);
}

void Program::setMat4(std::string name, glm::mat4 value)
{
    auto uniform_it = m_uniforms.find(name);
    if (!uniformIsActive(uniform_it, name) ||
        !typeIsCorrect(uniform_it->second.type, GL_FLOAT_MAT4))
    {
        return;
    }
    glProgramUniformMatrix4fv(m_gl_object_id, uniform_it->second.location, 1, false, glm::value_ptr(value));
}

bool Program::uniformIsActive(std::unordered_map<std::string, ShaderUniform>::iterator uniform_it, std::string name)
{
    if (uniform_it == m_uniforms.end())
    {
        LOG(Program, warn, "Trying to set inactive or non-existent uniform (int) with name: " + name);
        return false;
    }

    return true;
}

bool Program::typeIsCorrect(unsigned int type, unsigned int requested_type)
{
    if (type != requested_type)
    {
        LOG(Program, warn, "Trying to set uniform of type " + std::to_string(type) + "to value of type" + std::to_string(requested_type));
        return false;
    }

    return true;
}
} // namespace yage