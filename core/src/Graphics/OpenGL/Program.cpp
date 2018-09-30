#include "Program.h"

namespace yage
{
DEFINE_LOGGERS(Program)
Program::Program()
{   
    INIT_LOGGERS(Program);
    m_gl_object_id = glCreateProgram();
    LOG(Program, info, "Created program with id: " + std::to_string(m_gl_object_id));
    LOG(Program, info, "Created program with id: " + std::to_string(m_gl_object_id));
}

Program::~Program()
{
    LOG(Program, info, "Deleting program with id: " + std::to_string(m_gl_object_id));
    glDeleteProgram(m_gl_object_id);
}

void Program::activate(){
    glUseProgram(m_gl_object_id);
}

void Program::attachShader(ShaderPtr shader){
    LOG(Program, info, "Linking " + shader->getName() + " to program " + std::to_string(m_gl_object_id));
    glAttachShader(m_gl_object_id, shader->getGLObjectId());
    glLinkProgram(m_gl_object_id);
    // print linking errors if any

    GLint success;
    char info_log[512];

    glGetProgramiv(m_gl_object_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_gl_object_id, 512, NULL, info_log);
        LOG(Program, error, info_log);
    }else{
        LOG(Program, info, "Shader creations successfull.");
    }
}

} // namespace yage