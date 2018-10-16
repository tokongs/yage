#include <Window.h>
namespace yage
{
DEFINE_LOGGERS(Window);
Window::Window(WindowDesc desc)
{
    m_window_desc = desc;

    //Create loggers
    INIT_LOGGERS(Window);
    //Initialize GLFW
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit())
    {
        LOG(Window, error, "Failed to initialize GLFW");
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
        LOG(Window, error, "Failed to create GLFW window");
        return;
    }

    glfwSetKeyCallback(m_window_handle, glfw_key_callback);
    glfwSetCursorPosCallback(m_window_handle, glfw_cursor_position_callback);
    glfwSetCursorEnterCallback(m_window_handle, glfw_cursor_enter_callback);
    glfwSetMouseButtonCallback(m_window_handle, glfw_mouse_button_callback);

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

std::shared_ptr<GLDevice> Window::getGraphicsDevice()
{
    return m_device;
}

GLFWwindow *Window::getWindowHandle()
{
    return m_window_handle;
}

void glfw_error_callback(int error, const char *description)
{
    LOG(Window, error, "GLFW ERROR: " + std::to_string(error) + description);
}
 
} // namespace yage
