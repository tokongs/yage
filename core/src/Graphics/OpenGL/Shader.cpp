#include <Shader.h>
namespace yage
{
DEFINE_LOGGERS(Shader)
Shader::Shader(const char *vertex_code, const char *fragment_code)
{

    INIT_LOGGERS(Shader);


    unsigned int vertex, fragment;
    int success;
    char info_log[512];

    // vertex Shader

    CONSOLE_LOGGER(Shader, info, "Compiling vertex shader");
    FILE_LOGGER(Shader, info, "Compiling vertex shader");

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertex_code, NULL);
    glCompileShader(vertex);
    // print compile errors if any

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, info_log);
        CONSOLE_LOGGER(Shader, error, info_log);
        FILE_LOGGER(Shader, error, info_log);
    };

    CONSOLE_LOGGER(Shader, info, "Compiling fragment shader");
    FILE_LOGGER(Shader, info, "Compiling fragment shader");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragment_code, NULL);
    glCompileShader(fragment);

    // print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, info_log);
        CONSOLE_LOGGER(Shader, error, info_log);
        FILE_LOGGER(Shader, error, info_log);
    };


    
    // shader Program
    m_gl_object_id = glCreateProgram();
    CONSOLE_LOGGER(Shader, info, "Linking program with id: " + std::to_string(m_gl_object_id));
    FILE_LOGGER(Shader, info, "Linking program with id: " + std::to_string(m_gl_object_id));
    glAttachShader(m_gl_object_id, vertex);
    glAttachShader(m_gl_object_id, fragment);
    glLinkProgram(m_gl_object_id);
    // print linking errors if any
    glGetProgramiv(m_gl_object_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_gl_object_id, 512, NULL, info_log);
        CONSOLE_LOGGER(Shader, error, info_log);
        FILE_LOGGER(Shader, error, info_log);
    }else{
        CONSOLE_LOGGER(Shader, info, "Shader creations successfull.");
        FILE_LOGGER(Shader, info, "Shader creations successfull.");
    }

    // delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader(){
    glDeleteProgram(m_gl_object_id);
}

void Shader::activate()
{
    glUseProgram(m_gl_object_id);
}
} // namespace yage