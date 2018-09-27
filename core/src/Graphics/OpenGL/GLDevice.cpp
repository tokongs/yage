#include <GLDevice.h>

namespace yage
{

DEFINE_LOGGERS(GLDevice)
GLDevice::GLDevice()
{

    INIT_LOGGERS(GLDevice);

    //Load GL extensions
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        LOG(GLDevice, error, "Failed to initialize glew");
    }

    //Setup opengl
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(gl_debug_message_callback, 0);
}

GLDevice::~GLDevice(){

}

void GLDevice::setClearColor(glm::vec4 color){
    glClearColor(color.r, color.g, color.b, color.a);
}

void GLDevice::clearBuffers(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLAPIENTRY gl_debug_message_callback(GLenum source, GLenum type, GLuint id, GLenum severity,
                                          GLsizei length, const GLchar *message, const void *userParam)
{
    if(type == GL_DEBUG_TYPE_ERROR){
        LOG(GLDevice, error, "OpenGL Error(" + std::to_string(severity) + "): " + message);
    }
    
    else{
        LOG(GLDevice, info, "OpenGL Debug Callback(type: " + std::to_string(type) + ", severity: " + std::to_string(severity)+ "): " + message);
    }
}

} // namespace yage