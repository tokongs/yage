#include <GLDevice.h>

namespace yage
{
GLDevice::GLDevice()
{
   YAGE_INFO("Creating GL Device and initializing glew.")
    //Load GL extensions
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
       YAGE_ERROR("Failed to initialize glew");
    }

    //Setup opengl
    glEnable(GL_DEBUG_OUTPUT);
    glCullFace( GL_BACK );
    glEnable(GL_CULL_FACE);
    glDebugMessageCallback((GLDEBUGPROC)gl_debug_message_callback, nullptr);
}

GLDevice::~GLDevice(){
   YAGE_INFO("Destroying GL Device and initializing glew.")

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
    switch(type){
        case GL_DEBUG_TYPE_ERROR:
                YAGE_ERROR("OpenGL Error(" + std::to_string(severity) + "): " + message);
            break;
        default:
                YAGE_INFO("OpenGL Debug Callback(type: " + std::to_string(type) + ", severity: " + std::to_string(severity)+ "): " + message);
            break;
    }
}

} // namespace yage