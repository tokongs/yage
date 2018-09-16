#include <GLDevice.h>

namespace yage
{

std::shared_ptr<spdlog::logger> GLDevice::console_logger = NULL;
std::shared_ptr<spdlog::logger> GLDevice::file_logger = NULL;
GLDevice::GLDevice()
{

//setup loggers
#ifdef DEBUG
    if (!GLDevice::console_logger)
        GLDevice::console_logger = spdlog::stdout_color_mt("gl_device_console_logger");

    if (!GLDevice::file_logger)
        try
        {
            GLDevice::file_logger = spdlog::basic_logger_mt("gl_device_file_logger", "default.txt");
        }
        catch (const spdlog::spdlog_ex &ex)
        {
            std::cout << "Failed to start window logger: " << ex.what() << std::endl;
        }
#endif

    //Load GL extensions
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
#ifdef DEBUG
        console_logger->error("Failed to initialize glew");
#endif
    }

    //Setup opengl
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(gl_debug_message_callback, 0);
}

GLDevice::~GLDevice(){

}

void GLAPIENTRY gl_debug_message_callback(GLenum source, GLenum type, GLuint id, GLenum severity,
                                          GLsizei length, const GLchar *message, const void *userParam)
{
#ifdef DEBUG
    if (type == GL_DEBUG_TYPE_ERROR)
        GLDevice::console_logger->error("GL DEBUG CALLBACK. severity: {0}, message{1}", severity, message);
    else
        GLDevice::console_logger->info("GL DEBUG CALLBACK. type{0}, severity: {1}, message{2}", type, severity, message);

#endif
}

} // namespace yage