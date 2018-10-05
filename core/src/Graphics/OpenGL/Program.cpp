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
    glDeleteProgram(m_gl_object_id);
}

void Program::activate()
{
    glUseProgram(m_gl_object_id);
}

void Program::attachShaders(std::vector<int> shaders)
{

    for (int i = 0; i < shaders.size(); i++)
    {
        ShaderPtr shader = ResourceManager::getInstance().getResource<Shader>(shaders[i]);
        LOG(Program, info, "Linking " + shader->getName() + " to program " + std::to_string(m_gl_object_id));
        glAttachShader(m_gl_object_id, shader->getGLObjectId());
        glLinkProgram(m_gl_object_id);
    }

    GLint success;
    char info_log[512];

    glGetProgramiv(m_gl_object_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_gl_object_id, 512, NULL, info_log);
        LOG(Program, error, info_log);
    }
    else
    {
        LOG(Program, info, "Shader linking successfull.");
    }
}

std::string Program::getType()
{
    return m_type;
}
} // namespace yage