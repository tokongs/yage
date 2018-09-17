#include <Window.h>
namespace yage
{
std::shared_ptr<spdlog::logger> Window::console_logger = NULL;
std::shared_ptr<spdlog::logger> Window::file_logger = NULL;
Window::Window(WindowDesc desc)
{
    m_window_desc = desc;

    //Create loggers
#ifdef DEBUG
    if(!Window::console_logger)
        Window::console_logger = spdlog::stdout_color_mt("window_console_logger");

    if(!Window::file_logger)
        try
        {
            Window::file_logger = spdlog::basic_logger_mt("window_file_logger", "default.txt");
        }
        catch (const spdlog::spdlog_ex &ex)
        {
            std::cout << "Failed to start window logger: " << ex.what() << std::endl;
        }
#endif
    //Initialize GLFW
    glfwSetErrorCallback(glfw_error_callback);
    
    if (!glfwInit())
    {
#ifdef DEBUG
        Window::console_logger->error("Failed to initialize GLFW. See logs/default.log");
#endif
        return;
    }

    //create GLFW window and OpenGL context
    glfwWindowHint(GLFW_RESIZABLE, m_window_desc.resizable);
    glfwWindowHint(GLFW_VISIBLE, m_window_desc.visible);
    glfwWindowHint(GLFW_DECORATED, m_window_desc.decorated);
    glfwWindowHint(GLFW_FLOATING, m_window_desc.floating);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

#ifdef DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

    if (m_window_desc.fullscreen)
        m_window_handle = glfwCreateWindow(m_window_desc.width, m_window_desc.height, m_window_desc.title.c_str(), glfwGetPrimaryMonitor(), NULL);
    else
        m_window_handle = glfwCreateWindow(m_window_desc.width, m_window_desc.height, m_window_desc.title.c_str(), NULL, NULL);

    if (!m_window_handle)
    {
        glfwTerminate();
#ifdef DEBUG
        Window::console_logger->error("Failed to create GLFW window. See logs/default.log");
#endif
        return;
    }

    //Make the created OpenGL context the current context
    glfwMakeContextCurrent(m_window_handle);

    m_device = std::make_shared<GLDevice>();
}

Window::~Window()
{
    glfwTerminate();
}

void Window::update()
{
    glfwPollEvents();
    glfwSwapBuffers(m_window_handle);
}

bool Window::shouldClose()
{
    return glfwWindowShouldClose(m_window_handle);
}

void Window::resize(int width, int height)
{
    m_window_desc.width = width;
    m_window_desc.height = height;
    glfwSetWindowSize(m_window_handle, width, height);
}

std::shared_ptr<GLDevice> Window::getGraphicsDevice(){
    return m_device;
}

void glfw_error_callback(int error, const char *description)
{
    Window::file_logger->error("GLFW ERROR {0}: {1}", error, description);
    Window::file_logger->flush();

}
}